<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="com.tenpay.RequestHandler" %>
<%@ page import="com.tenpay.ResponseHandler" %>   
<%@ page import="com.tenpay.client.ClientResponseHandler" %>    
<%@ page import="com.tenpay.client.TenpayHttpClient" %>
<%@ page import="com.tenpay.client.ClientResponseHandler" %>
<%@ page import="com.tenpay.util.ConstantUtil" %>
<%@ page import="java.util.*"%>
<%@ page import="payserver.PayTaskManager"%>
<%@ page import="payserver.Log"%>
<%@ page import="java.io.InputStream"%>
<%@ page import="java.io.PrintWriter"%>



<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<%
//---------------------------------------------------------
//财付通支付通知（后台通知）示例，商户按照此文档进行开发即可
//---------------------------------------------------------
//商户号
String partner = ConstantUtil.PARTNER;

//密钥
String key = ConstantUtil.PARTNER_KEY;


//创建支付应答对象
ClientResponseHandler resHandler = new ClientResponseHandler();
resHandler.setKey(key);
InputStream input = request.getInputStream();
StringBuffer bufferStr = new StringBuffer(2048);
byte[] buffer = new byte[2048];
int i = input.read(buffer);
for(int j = 0;j < i;j++)
{
	bufferStr.append((char) buffer[j]);
}
resHandler.setContent(bufferStr.toString());
//判断签名
if(resHandler.isTenpaySign()) {
	
	//通知id
	String notify_id = resHandler.getParameter("notify_id");
	
	//创建请求对象
	RequestHandler queryReq = new RequestHandler(null, null);
	//通信对象
	TenpayHttpClient httpClient = new TenpayHttpClient();
	//应答对象
	ClientResponseHandler queryRes = new ClientResponseHandler();
	

	//通过通知ID查询，确保通知来至财付通
	queryReq.init();
	queryReq.setKey(key);
	queryReq.setGateUrl("https://gw.tenpay.com/gateway/verifynotifyid.xml");
	queryReq.setParameter("partner", partner);
	queryReq.setParameter("notify_id", notify_id);
	
	//通信对象
	httpClient.setTimeOut(5);
	//设置请求内容
	httpClient.setReqContent(queryReq.getRequestURL());
	System.out.println("queryReq:" + queryReq.getRequestURL());
	//后台调用
	if(httpClient.call())
	{
		PayTaskManager.getInstance().parseTenNotify(resHandler.getAllParameters());
		//------------------------------
		//处理业务开始
		//------------------------------
		
		//处理业务完毕
		//------------------------------
		String retXml = "<xml>"+
						"<return_code>"+"SUCCESS"+"</return_code>"+
						"<return_msg>"+"OK"+"</return_msg>"+
						"</xml>";
						
		out.println(retXml);
		out.flush();
		out.close();
	} 
}
else
{
	Log.getInstance().debug("通知签名验证失败");
}
%>
