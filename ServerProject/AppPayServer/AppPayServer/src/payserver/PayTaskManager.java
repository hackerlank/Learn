package payserver;

import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.*;

import com.alipay.util.AlipayCore;
import com.alipay.util.AlipayNotify;

import java.net.URLDecoder;

import com.alipay.config.AlipayConfig;
import com.utils.GetWxOrderno;

/**
 * 连接管理器
 * 
 * @author flyer
 *
 */
public class PayTaskManager {
	// 单例实例
	private static PayTaskManager s_instance;
	// map容器
	private Map<Long, PayTask> m_payTaskMap = null;
	//localport对应task的唯一ID
	private Map<Long, Long> m_localPortMap = null;
    //订单id对应taskID
    private Map<String,Long> m_orderTaskMap = null;

	/**
	 * 构造函数
	 */
	private PayTaskManager() {
		m_payTaskMap = new HashMap<Long, PayTask>();
		m_localPortMap = new HashMap<Long, Long>();
        m_orderTaskMap = new HashMap<String,Long>();
	}

	/**
	 * 单例接口
	 * 
	 * @return
	 */
	public static PayTaskManager getInstance() {
		if (s_instance == null) {
			s_instance = new PayTaskManager();
		}
		return s_instance;
	}

	/**
	 * 获得连接
	 * 
	 * @param id
	 * @return
	 */
	public PayTask getPayTask(final long id) {
		PayTask ret = null;
		if (m_payTaskMap.get(id) != null) {
			ret = m_payTaskMap.get(id);
		}
		return ret;
	}

	public PayTask getPayTaskByLocalPort(final long localPort) {
		PayTask ret = null;
		if (m_localPortMap.get(localPort) != null) {
			ret = getPayTask(m_localPortMap.get(localPort));
		}
		return ret;
	}

	/**
	 * 插入连接
	 * 
	 * @param payTask
	 * @return
	 */
	public boolean addPayTask(SocketChannel socket) {
        PayTask payTask = new PayTask(socket);
		long localPort = socket.socket().getPort();
		boolean ret = m_payTaskMap.get(payTask.getID()) != null ? true : false;
		ret = m_localPortMap.get(localPort) == null ? true : false;
        String log = "[支付服务器] 加入新连接(" + localPort + "," + payTask.getID() + "," + ret + ")";
		if (ret) 
        {
			m_localPortMap.put(localPort, payTask.getID());
			m_payTaskMap.put(payTask.getID(), payTask);
		}
        Log.getInstance().debug(log);
		return ret;
	}

    public boolean removeTask(PayTask payTask)
    {
        m_localPortMap.remove(payTask.getSocket().socket().getPort());
        m_localPortMap.remove(payTask.getID());
        return true;
    }

    public void loop()
    {
        Vector<Long> vecDel = new Vector<Long>();
        for (Map.Entry<Long, PayTask> entry : m_payTaskMap.entrySet()) {
			PayTask temp = entry.getValue();
            if(temp.isTerminate())
            {
                vecDel.add(entry.getKey());
            }
            else
            {
                temp.ackHeartBeat();
            }
		}
        for(int index = 0;index < vecDel.size();++index)
        {
            long key = vecDel.get(index);
            if(m_payTaskMap.get(key) != null)
            {
                PayTask task = m_payTaskMap.get(key);
                task.terminate();
                removeTask(task);
            }
        }
    }

    public void insertOrder(String orderID,Long taskID)
    {
    	logTaskOrderMap();
        m_orderTaskMap.put(orderID,taskID);
        Log.getInstance().debug("插入人和订单:（" + orderID + ":" + Long.toString(taskID) + ")");
        logTaskOrderMap();
    }
    
    //处理支付宝的notify消息
    public boolean parseAlipNotify(Map<String,String> paraMap)
    {
        boolean ret = false;
        String paraArg = null;
        String payType = "支付宝";
        do
        {
            try
            {
            	paraArg = AlipayCore.createLinkString(paraMap);
                if(AlipayNotify.verify(paraMap) == false)
                {
                    Log.getInstance().debug("签名验证没有通过");
                    break;
                }
                if(paraMap.get("out_trade_no") == null)
                {
                    Log.getInstance().debug("notify中没有系统订单号");
                    break;
                }
                logTaskOrderMap();
                String orderID = paraMap.get("out_trade_no");
                if(m_orderTaskMap.get(orderID) == null)
                {
                    Log.getInstance().debug("订单号没有找到对应的task(" + orderID + ")");
                    break;
                }
                Long taskID = m_orderTaskMap.get(orderID);
                PayTask payTask = getPayTask(taskID);
                if(payTask == null)
                {
                    Log.getInstance().debug("找不到task实例(" + orderID + ":" + String.valueOf(taskID) + ")");
                    break;
                }
                ret = payTask.parseAlipNotify(paraMap,payType); 
                m_orderTaskMap.remove(orderID);
                logTaskOrderMap();
            }
            catch(Exception e)
            {
                e.printStackTrace();
                break;
            }
        }while(false);
        String arg =  paraArg == null ? "错误" : paraArg;
        String log = "notify处理结束:(" + payType + ":" + String.valueOf(ret) + ":" + arg + ")";
        Log.getInstance().debug(log);
        return ret;
    }
    
    //处理微信的notify消息
    public boolean parseTenNotify( Map<String,String> paraMap)
    {
        boolean ret = false;
        String paraArg = null;
        String payType = "微信";
        do
        {
            try
            {
            	paraArg = AlipayCore.createLinkString(paraMap);
                if(paraMap.get("out_trade_no") == null)
                {
                    Log.getInstance().debug("notify中没有系统订单号");
                    break;
                }
                String orderID = paraMap.get("out_trade_no");
                if(m_orderTaskMap.get(orderID) == null)
                {
                    Log.getInstance().debug("订单号没有找到对应的task(" + orderID + ")");
                    break;
                }
                Long taskID = m_orderTaskMap.get(orderID);
                PayTask payTask = getPayTask(taskID);
                if(payTask == null)
                {
                    Log.getInstance().debug("找不到task实例(" + orderID + ":" + String.valueOf(taskID) + ")");
                    break;
                }
                ret = payTask.parseTenNotify(paraMap,payType); 
                m_orderTaskMap.remove(orderID);
            }
            catch(Exception e)
            {
                e.printStackTrace();
                break;
            }
        }while(false);
        String arg =  paraArg == null ? "错误" : paraArg;
        String log = "notify处理结束:(" + payType + ":" + String.valueOf(ret) + ":" + arg + ")";
        Log.getInstance().debug(log);
        return ret;
    }
    
    public void logTaskOrderMap()
    {
    	for (Map.Entry<String, Long> entry : m_orderTaskMap.entrySet()) 
    	{
    		Log.getInstance().debug("遗留订单任务键值对:(" + entry.getKey() + ":" + entry.getValue() + ")");
 		}
    }
}
