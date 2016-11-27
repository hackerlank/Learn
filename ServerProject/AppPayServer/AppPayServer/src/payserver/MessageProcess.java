package payserver;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;
import java.nio.ByteOrder;
import ProtoMsgData.Pay;
import ProtoMsgData.Business;

/**
 * 消息处理单例
 * @author flyer
 *
 */
public class MessageProcess {
	//单例实例
	private static MessageProcess s_instance = null;
	//处理消息类名对应类描述符
	private Map<String, com.google.protobuf.Descriptors.Descriptor> m_protoNameToDiscriptorMap = null;
	
	private MessageProcess()
	{
	}
	
	public boolean init()
	{
		m_protoNameToDiscriptorMap = new HashMap<String, com.google.protobuf.Descriptors.Descriptor>();
        m_protoNameToDiscriptorMap.put("ReqPayServerVerify",Pay.ReqPayServerVerify.getDescriptor());
        m_protoNameToDiscriptorMap.put("ReqHeartBeat",Pay.ReqHeartBeat.getDescriptor());
        m_protoNameToDiscriptorMap.put("ReqPayOrder",Business.ReqPayOrder.getDescriptor());
        m_protoNameToDiscriptorMap.put("ReqRecharge",Business.ReqRecharge.getDescriptor());
		return true;
	}
	/**
	 * 单例接口
	 * @return
	 */
	public static MessageProcess getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new MessageProcess();
			s_instance.init();
		}
		return s_instance;
	}
	
	/**
	 * 封装发送去的消息包
	 * @param message
	 * @param send
	 * @return
	 */
	public ByteBuffer packMessage(final com.google.protobuf.GeneratedMessage message)
	{
		byte messageType = 0;
		com.google.protobuf.Descriptors.Descriptor descriptor = message.getDescriptorForType();
		long cmdKey = CmdFunManager.getInstance().getCmdKey(descriptor.getName());
		if(cmdKey == 0)
		{
			return null;
		}
        byte[] result = message.toByteArray();
        ByteBuffer buffer = ByteBuffer.allocate(4+1+4+result.length);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.putInt(4+1+4+result.length);
        buffer.put(messageType);
        buffer.putInt((int)cmdKey);
        buffer.put(result);
        if(descriptor.getName().equals("AckHeartBeat") == false)
        {
		    String log = "发送消息[name:" + descriptor.getName() + "]" + " len:" + String.valueOf(buffer.position());
		    Log.getInstance().debug(log);
        }
        buffer.flip();
		return buffer;
	}

    /**
	 * 解析出消息包
	 * @param buffer
	 * @return
	 */
    public boolean unpackAndDispatcherMessage(PayTask payTask,ByteBuffer buffer)
	{
        boolean ret = false;
        buffer.flip();
		if(buffer.limit() == 0 || buffer.limit() != buffer.getInt())
		{
			return ret;
		}
		byte messageType = buffer.get();
		if(messageType != 0)
		{
			return ret;
		}
		int cmdKey = buffer.getInt();
		String protoName = CmdFunManager.getInstance().getProtoName(cmdKey);
		if(protoName.isEmpty())
		{
			return ret;
		}
		if(m_protoNameToDiscriptorMap.get(protoName) == null)
		{
			return ret;
		}
		com.google.protobuf.Descriptors.Descriptor descriptor = m_protoNameToDiscriptorMap.get(protoName);
		try
		{
            byte[] arry = new byte[buffer.limit() - buffer.position()];
            buffer.get(arry);
            if(protoName.equals("ReqHeartBeat") == false)
            {
                String log = "接受消息[name:" + protoName +  "]" + "len:" + String.valueOf(buffer.position());
                Log.getInstance().debug(log);
            }
            return Dispatcher.getInstance().dispatcher(payTask,protoName,arry); 
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return ret;
		}
	}
}
