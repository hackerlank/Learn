package payserver;

import java.nio.channels.SocketChannel;  
import java.nio.ByteBuffer;
import ProtoMsgData.Pay;
import java.nio.ByteOrder;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import com.alipay.config.AlipayConfig;
import com.alipay.util.AlipayCore;
import com.alipay.sign.RSA;
import com.alipay.util.UtilDate;
import ProtoMsgData.Business;
import com.alipay.util.AlipayNotify;
import java.net.URLDecoder;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import com.utils.*;
import com.tenpay.util.ConstantUtil;
import com.tenpay.AccessTokenRequestHandler;
import java.util.SortedMap;
import java.util.TreeMap;
import com.tenpay.util.WXUtil;

/**
 * 支付任务连接
 * @author flyer
 *
 */
public class PayTask
{
	//生成任务ID
	private static long s_uniqueID = 0L;
	//消息缓存大小
	public static int s_buffer = 1024;
	//连接唯一id
	private long m_id = 0;
	//连接状态
	private int m_status = 0;
	//验证标识
	private boolean m_verify = false;
	//套接字
	private SocketChannel m_socket = null;
    //心跳此时
    private int m_heratTime = 0;
    //时间戳
    private long m_time = 0;
    //心跳间隔
    private static int s_grap = 100;
    //心跳断开连接
    private static int s_terminateTime = 10;
    //订单信息
    private Map<String,String> m_orderMap;
    //微信订单
    private Map<String,String> m_tenOrderMap;
    //互斥锁
    private Lock m_lock = null;
	
	/**
	 * 连接构造函数
	 * @param socket
	 */
	public PayTask(SocketChannel socket)
	{
		m_socket = socket;
		m_id = generalID();
        m_orderMap = new HashMap<String,String>();
        m_tenOrderMap = new HashMap<String,String>();
        m_lock = new ReentrantLock();
	}
	
	/**
	 * 生成唯一连接ID
	 * @return
	 */
	public static long generalID()
	{
		long uniqueID = (++s_uniqueID);
		return uniqueID;
	}
	
	/**
	 * 获得连接ID
	 * @return
	 */
	public long getID()
	{
		return m_id;
	}
	
	public SocketChannel getSocket()
	{
		return m_socket;
	}
	
	/**
	 * 处理接收到的消息
	 * @return
	 */
	public boolean parseMessage()
	{
		ByteBuffer buffer = ByteBuffer.allocate(s_buffer);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
		try
		{
            m_socket.read(buffer);
            return MessageProcess.getInstance().unpackAndDispatcherMessage(this,buffer);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
		return true;
	}
	
	/**
	 * 支付返回消息
	 * @return
	 */
	public boolean payReturn()
	{
		Pay.AckPay.Builder builder = Pay.AckPay.newBuilder();
		builder.setCharid(0L);
		builder.setMoney(0);
		builder.setId(0L);
		builder.setRet(false);
		Pay.AckPay ackPay = builder.build();  
		return sendMsg(ackPay);
	}
	
	public boolean sendMsg(final com.google.protobuf.GeneratedMessage message)
	{
		boolean ret = false;
		ByteBuffer buffer = MessageProcess.getInstance().packMessage(message);
        if(buffer != null || !isTerminate())
		{
            m_lock.lock();
			try
			{
				m_socket.write(buffer);
                m_socket.socket().getOutputStream().flush();
                ret = true;
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
            m_lock.unlock();
		}
        return ret;
	}
	
	/**
	 * 验证连接的合法性
	 * @param reqVerify
	 * @return
	 */
	public boolean verify(final Pay.ReqPayServerVerify reqVerify)
	{
		Pay.AckPayServerVerify.Builder builder = Pay.AckPayServerVerify.newBuilder();
		builder.setIp(reqVerify.getIp());
		builder.setPort(reqVerify.getPort());
		builder.setRet(true);
		Pay.AckPayServerVerify ackVerify = builder.build(); 
		m_verify = sendMsg(ackVerify);
		return m_verify;
	}

    public boolean terminate()
    {
        PayServer.getInstance().remove(m_socket);
        try
        {
            m_socket.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }

    private boolean grapTime()
    {
        Date date = new Date();
        long now = date.getTime();
        if(now - m_time < s_grap)
        {
            return false;
        }
        m_time = now;
        return true;
    }


    //服务器发出心跳
    public boolean ackHeartBeat()
    {
        boolean ret = false;;
        if(grapTime() == false)
        {
            return ret;
        }
        Pay.AckHeartBeat.Builder builder = Pay.AckHeartBeat.newBuilder();
        Pay.AckHeartBeat ackHearBeat = builder.build();
        if(sendMsg(ackHearBeat))
        {
        	m_heratTime += 1;
        	ret = true;
        }
        return ret;
    }
    
    //收到客户端回应
    public void reqHeartBeat()
    {
        m_heratTime = 0;
    }

    //是否需要断开连接
    public boolean isTerminate()
    {
        return m_heratTime > s_terminateTime ? true : false;
    }


    //支付订单
    public String ackPay(final Business.ReqPayOrder reqPayOrder)
    {
        String orderTag = String.valueOf(reqPayOrder.getCharid());
        Business.AckPayOrder.Builder builder = Business.AckPayOrder.newBuilder();
        for(int cnt = 0;cnt != reqPayOrder.getOrderCount();++cnt)
        {
            orderTag += ",";
            orderTag += String.valueOf(reqPayOrder.getOrder(cnt)); 
            builder.addOrder(reqPayOrder.getOrder(cnt));
        }
        String orderID = null;
        Log.getInstance().debug("accept begin:" + String.valueOf(reqPayOrder.getPayfortype()));
        if(reqPayOrder.getPayfortype() == Business.PayForType.PFT_Alip)
        {
            orderID = ackPayAlip(builder,reqPayOrder.getMoney()); 
        }
        else
        {
            orderID = tenReqPay(builder,reqPayOrder.getMoney());
        }
        Log.getInstance().debug("accept end:" + String.valueOf(reqPayOrder.getPayfortype()));
        builder.setCharid(reqPayOrder.getCharid());
        builder.setPayfortype(reqPayOrder.getPayfortype());

        Business.AckPayOrder message = builder.build();
        if(sendMsg(message))
        {
        	 if(reqPayOrder.getPayfortype() == Business.PayForType.PFT_Alip)
             {
                 m_orderMap.put(orderID,orderTag);
             }
             else
             {
                 m_tenOrderMap.put(orderID,orderTag);
             }
        }
        else
        {
        	 orderID = null;
        }
        Log.getInstance().debug("生成支付订单:(" + String.valueOf(reqPayOrder.getPayfortype()) + Long.toString(m_id) + ":" + orderID + ":" + orderTag + ")");
        return orderID;
    }

    //支付宝支付订单
    private String ackPayAlip(Business.AckPayOrder.Builder builder,int money)
    {
        String orderID = UtilDate.getOrderNum();
        Map<String,String> argMap = new HashMap<String,String>();
        String ipInfo = "http://" + PayServer.s_ip + ":" + PayServer.s_tomcatPort + "/CleanPayServer/AliPayNotify.jsp";
        argMap.put("notify_url",ipInfo);
        argMap.put("out_trade_no",orderID);
        argMap.put("total_fee",PayServer.s_test ? "0.01" : String.valueOf(money));

        Map<String,String> filterArgMap = AlipayCore.paraFilter(argMap);
        String argLine = AlipayCore.createLinkString(filterArgMap);
        builder.setPayinfo(argLine);
        return orderID;
    }

    //微信支付订单
    private String tenReqPay(Business.AckPayOrder.Builder builder,int money)
    {
        String out_trade_no = null;
        try
        {
            HttpServletRequest request = null;
            HttpServletResponse response = null;

            //接收财付通通知的URL
            String notify_url = "http://" + PayServer.s_ip + ":" + PayServer.s_tomcatPort + "/CleanPayServer/TenPayNotify.jsp";

            //---------------生成订单号 开始------------------------
            //当前时间 yyyyMMddHHmmss
            String currTime = TenpayUtil.getCurrTime();
            //8位日期
            String strTime = currTime.substring(8, currTime.length());
            //四位随机数
            String strRandom = TenpayUtil.buildRandom(4) + "";
            //10位序列号,可以自行调整。
            String strReq = strTime + strRandom;
            //订单号，此处用时间加随机数生成，商户根据自己情况调整，只要保持全局唯一就行
            out_trade_no = strReq;
            //---------------生成订单号 结束------------------------

            RequestHandler requestHandler = new RequestHandler(request,response);
            String token = AccessTokenRequestHandler.getAccessToken();
            Log.getInstance().debug("微信支付获取token=======================:" + token);
            requestHandler.init(ConstantUtil.APP_ID,ConstantUtil.APP_SECRET,ConstantUtil.PARTNER_KEY);
            
            SortedMap<String, String> packageParams = new TreeMap<String, String>();  
            String body = "兔汉斯居家保洁";
            String spbill_create_ip = "127.0.0.1";
            String trade_type = "APP";
            String noncestr = WXUtil.getNonceStr();
            String timestamp = WXUtil.getTimeStamp();
            //转化成分
            int totalFee = PayServer.s_test ? 1 : money * 100;
            packageParams.put("appid",ConstantUtil.APP_ID );
            packageParams.put("mch_id", ConstantUtil.PARTNER);
            packageParams.put("nonce_str", noncestr);
            packageParams.put("body", body);
            packageParams.put("out_trade_no", out_trade_no);
            packageParams.put("total_fee",String.valueOf(totalFee));
            packageParams.put("spbill_create_ip", spbill_create_ip);
            packageParams.put("notify_url", notify_url);
            packageParams.put("trade_type", trade_type);
            String sign = requestHandler.createSign(packageParams);


            String createOrderURL = "https://api.mch.weixin.qq.com/pay/unifiedorder";
            String signXml = "<xml>"+
                             "<appid>"+ConstantUtil.APP_ID+"</appid>"+
                             "<mch_id>"+ConstantUtil.PARTNER+"</mch_id>"+
                             "<nonce_str>"+noncestr+"</nonce_str>"+
                             "<sign>"+sign+"</sign>"+
                             "<out_trade_no>"+out_trade_no+"</out_trade_no>"+
                             "<total_fee>"+totalFee+"</total_fee>"+
                             "<spbill_create_ip>"+spbill_create_ip+"</spbill_create_ip>"+
                             "<notify_url>"+notify_url+"</notify_url>"+
                             "<body>"+body+"</body>"+
                             "<trade_type>"+trade_type+"</trade_type>"+
                             "</xml>";
            Log.getInstance().debug("xml:" + signXml);
            String prepayid = GetWxOrderno.getPayNo(createOrderURL,signXml);
            Log.getInstance().debug("prepayid:" + prepayid);

            SortedMap<String, String> finalpackage = new TreeMap();
            finalpackage.put("appid", ConstantUtil.APP_ID);
            finalpackage.put("timestamp", timestamp);
            finalpackage.put("noncestr", noncestr);
            finalpackage.put("package", "Sign=WXPay");
            finalpackage.put("partnerid", ConstantUtil.PARTNER);
            finalpackage.put("prepayid", prepayid);
            builder.setPayinfo(requestHandler.genPackage(finalpackage));
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return out_trade_no;
    }

    //充值函数
    public String ackRecharge(final Business.ReqRecharge reqRecharge)
    {
        String orderTag = String.valueOf(reqRecharge.getCharid());
        Business.AckRecharge.Builder builder = Business.AckRecharge.newBuilder();
        String orderID = null;
        if(reqRecharge.getPayfortype() == Business.PayForType.PFT_Alip)
        {
            orderID = ackRechargeAlip(builder,reqRecharge.getMoney()); 
        }
        else
        {
            orderID = tenReqRecharge(builder,reqRecharge.getMoney());
        }
        builder.setCharid(reqRecharge.getCharid());
        builder.setPayfortype(reqRecharge.getPayfortype());

        Business.AckRecharge message = builder.build();
        if(sendMsg(message))
        {
        	   if(reqRecharge.getPayfortype() == Business.PayForType.PFT_Alip)
               {
                   m_orderMap.put(orderID,orderTag);
               }
               else
               {
                   m_tenOrderMap.put(orderID,orderTag);
               }
        }
        else
        {
        	orderID = null;
        }
        Log.getInstance().debug("生成充值订单:(" + String.valueOf(reqRecharge.getPayfortype()) + ":" + Long.toString(m_id) + ":" + orderID + ":" + orderTag + ")");
        return orderID;
    }

    //支付宝充值函数
    private String ackRechargeAlip(Business.AckRecharge.Builder builder,int money)
    {
        String orderID = UtilDate.getOrderNum();
        Map<String,String> argMap = new HashMap<String,String>();
        String ipInfo = "http://" + PayServer.s_ip + ":" + PayServer.s_tomcatPort + "/CleanPayServer/AliPayNotify.jsp";
        argMap.put("notify_url",ipInfo);
        argMap.put("out_trade_no",orderID);
        argMap.put("total_fee",PayServer.s_test ? "0.01" : String.valueOf(money));

        Map<String,String> filterArgMap = AlipayCore.paraFilter(argMap);
        String argLine = AlipayCore.createLinkString(filterArgMap);
        builder.setPayinfo(argLine);
        return orderID;
    }

    //微信充值
    private String tenReqRecharge(Business.AckRecharge.Builder builder,int money)
    {
        String out_trade_no = null;
        try
        {
            HttpServletRequest request = null;
            HttpServletResponse response = null;

            //接收财付通通知的URL
            String notify_url = "http://" + PayServer.s_ip + ":" + PayServer.s_tomcatPort + "/CleanPayServer/TenPayNotify.jsp";

            //---------------生成订单号 开始------------------------
            //当前时间 yyyyMMddHHmmss
            String currTime = TenpayUtil.getCurrTime();
            //8位日期
            String strTime = currTime.substring(8, currTime.length());
            //四位随机数
            String strRandom = TenpayUtil.buildRandom(4) + "";
            //10位序列号,可以自行调整。
            String strReq = strTime + strRandom;
            //订单号，此处用时间加随机数生成，商户根据自己情况调整，只要保持全局唯一就行
            out_trade_no = strReq;
            //---------------生成订单号 结束------------------------

            RequestHandler requestHandler = new RequestHandler(request,response);
            String token = AccessTokenRequestHandler.getAccessToken();
            Log.getInstance().debug("微信支付获取token=======================:" + token);
            requestHandler.init(ConstantUtil.APP_ID,ConstantUtil.APP_SECRET,ConstantUtil.PARTNER_KEY);
            
            SortedMap<String, String> packageParams = new TreeMap<String, String>();  
            String body = "兔汉斯居家保洁";
            String spbill_create_ip = "127.0.0.1";
            String trade_type = "APP";
            String noncestr = WXUtil.getNonceStr();
            String timestamp = WXUtil.getTimeStamp();
            //转化成分
            int totalFee = PayServer.s_test ? 1 : money * 100;
            packageParams.put("appid",ConstantUtil.APP_ID );
            packageParams.put("mch_id", ConstantUtil.PARTNER);
            packageParams.put("nonce_str", noncestr);
            packageParams.put("body", body);
            packageParams.put("out_trade_no", out_trade_no);
            packageParams.put("total_fee",String.valueOf(totalFee));
            packageParams.put("spbill_create_ip", spbill_create_ip);
            packageParams.put("notify_url", notify_url);
            packageParams.put("trade_type", trade_type);
            String sign = requestHandler.createSign(packageParams);


            String createOrderURL = "https://api.mch.weixin.qq.com/pay/unifiedorder";
            String signXml = "<xml>"+
                             "<appid>"+ConstantUtil.APP_ID+"</appid>"+
                             "<mch_id>"+ConstantUtil.PARTNER+"</mch_id>"+
                             "<nonce_str>"+noncestr+"</nonce_str>"+
                             "<sign>"+sign+"</sign>"+
                             "<out_trade_no>"+out_trade_no+"</out_trade_no>"+
                             "<total_fee>"+totalFee+"</total_fee>"+
                             "<spbill_create_ip>"+spbill_create_ip+"</spbill_create_ip>"+
                             "<notify_url>"+notify_url+"</notify_url>"+
                             "<body>"+body+"</body>"+
                             "<trade_type>"+trade_type+"</trade_type>"+
                             "</xml>";
            Log.getInstance().debug("xml:" + signXml);
            String prepayid = GetWxOrderno.getPayNo(createOrderURL,signXml);
            Log.getInstance().debug("prepayid:" + prepayid);

            SortedMap<String, String> finalpackage = new TreeMap();
            finalpackage.put("appid", ConstantUtil.APP_ID);
            finalpackage.put("timestamp", timestamp);
            finalpackage.put("noncestr", noncestr);
            finalpackage.put("package", "Sign=WXPay");
            finalpackage.put("partnerid", ConstantUtil.PARTNER);
            finalpackage.put("prepayid", prepayid);
            builder.setPayinfo(requestHandler.genPackage(finalpackage));
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return out_trade_no;
    }

    //处理支付宝的http消息
    public boolean parseAlipNotify(Map<String,String> paraMap,String payType)
    {
        boolean ret = false;
        do
        {
            m_lock.lock();
            try
            {
                String orderID = paraMap.get("out_trade_no");
                long money = (long)(Double.parseDouble(paraMap.get("total_fee")));
                money /= 100;
                if(money < 1)
                {
                    money = 1;
                }
                String orderTag = m_orderMap.get(orderID);
                String [] orderArry = orderTag.split(",");
                Long charID = Long.parseLong(orderArry[0]);
                if(charID == 0)
                {
                    break;
                }
                if(orderArry.length > 1)
                {
                    Business.AckPayOrderReturn.Builder builder = Business.AckPayOrderReturn.newBuilder(); 
                    builder.setCharid(charID);
                    for(int cnt = 1;cnt < orderArry.length;cnt++)
                    {
                        builder.addOrder(Long.parseLong(orderArry[cnt]));
                    }
                    builder.setMoney(money);
                    Business.AckPayOrderReturn message = builder.build();
                    if(sendMsg(message))
                    {
                    	m_orderMap.remove(paraMap.get("out_trade_no"));
                    	ret = true;
                    }
                }
                else
                {
                    Business.AckRechargeReturn.Builder builder = Business.AckRechargeReturn.newBuilder(); 
                    builder.setCharid(charID);
                    builder.setMoney((int)money);
                    Business.AckRechargeReturn message = builder.build();
                    if(sendMsg(message))
                    {
                    	m_orderMap.remove(paraMap.get("out_trade_no"));
                    	ret = true;
                    }
                    payType = "充值";
                }
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
            m_lock.unlock();
        }while(false);
        return ret;
    }

    //处理微信的http消息
    public boolean parseTenNotify(Map<String,String> paraMap,String payType)
    {
        boolean ret = false;
        do
        {
            m_lock.lock();
            try
            {
                String orderID = paraMap.get("out_trade_no");
                long money = (long)(Double.parseDouble(paraMap.get("total_fee")));
                money /= 100;
                if(money < 1)
                {
                    money = 1;
                }
                String orderTag = m_tenOrderMap.get(orderID);
                String [] orderArry = orderTag.split(",");
                Long charID = Long.parseLong(orderArry[0]);
                if(charID == 0)
                {
                    break;
                }
                if(orderArry.length > 1)
                {
                    Business.AckPayOrderReturn.Builder builder = Business.AckPayOrderReturn.newBuilder(); 
                    builder.setCharid(charID);
                    builder.setPayfortype(Business.PayForType.PFT_Ten);
                    for(int cnt = 1;cnt < orderArry.length;cnt++)
                    {
                        builder.addOrder(Long.parseLong(orderArry[cnt]));
                    }
                    builder.setMoney(money);
                    Business.AckPayOrderReturn message = builder.build();
                    if(sendMsg(message))
                    {
                    	m_tenOrderMap.remove(paraMap.get("out_trade_no"));
                    	ret = true;
                    	
                    }
                }
                else
                {
                    Business.AckRechargeReturn.Builder builder = Business.AckRechargeReturn.newBuilder(); 
                    builder.setCharid(charID);
                    builder.setMoney((int)money);
                    builder.setPayfortype(Business.PayForType.PFT_Ten);
                    Business.AckRechargeReturn message = builder.build();
                    if(sendMsg(message))
                    {
                    	m_tenOrderMap.remove(paraMap.get("out_trade_no"));
                    	ret = true;
                    }
                    payType = "充值";
                }
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
            m_lock.unlock();
        }while(false);
        return ret;
    }
}
