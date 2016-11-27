package payserver;
import ProtoMsgData.Pay;
import java.nio.ByteBuffer;
import ProtoMsgData.Business;

public class Dispatcher 
{
	private static Dispatcher s_instance = null;
	private Dispatcher()
	{
	}
	
	/**
	 * 单例接口
	 * @return
	 */
	public static Dispatcher getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new Dispatcher();
		}
		return s_instance;
	}
	
	/**
	 * 分发消息
	 * @param payTask
	 * @param message
	 * @return
	 */
	public boolean dispatcher(PayTask payTask,String messageName,byte[] arry)
	{
		boolean ret = false;
        if(messageName.equals("ReqPayServerVerify"))
        {
            try
            {
                Pay.ReqPayServerVerify.Builder builder = Pay.ReqPayServerVerify.newBuilder();
                builder.mergeFrom(arry);
                Pay.ReqPayServerVerify message = builder.build();
                ret = payTask.verify(message);
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
            if(ret == true)
            {

            }
        }
        else if(messageName.equals("ReqHeartBeat"))
        {
            try
            {
                Pay.ReqHeartBeat.Builder builder = Pay.ReqHeartBeat.newBuilder();
                builder.mergeFrom(arry);
                Pay.ReqHeartBeat message = builder.build();
                payTask.reqHeartBeat();
                ret = true;
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }
        else if(messageName.equals("ReqPayOrder"))
        {
            try
            {
                Business.ReqPayOrder.Builder builder = Business.ReqPayOrder.newBuilder();
                builder.mergeFrom(arry);
                Business.ReqPayOrder message = builder.build();
                String orderID = payTask.ackPay(message);
                if(orderID != null)
                {
                    PayTaskManager.getInstance().insertOrder(orderID,payTask.getID());
                    ret = true;
                }
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }
        else if(messageName.equals("ReqRecharge"))
        {
            try
            {
                Business.ReqRecharge.Builder builder = Business.ReqRecharge.newBuilder();
                builder.mergeFrom(arry);
                Business.ReqRecharge message = builder.build();
                String orderID = payTask.ackRecharge(message);
                if(orderID != null)
                {
                    PayTaskManager.getInstance().insertOrder(orderID,payTask.getID());
                    ret = true;
                }
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }
        else
        {
        	Log.getInstance().error("[分发消息] " + messageName + "没有处理函数");
        }
		return ret;

	}
}
