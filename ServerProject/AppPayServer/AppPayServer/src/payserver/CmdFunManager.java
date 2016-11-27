package payserver;

import java.util.Map;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.util.HashMap;

/**
 * 消息指令管理类,单例模式
 * @author flyer
 *
 */

public class CmdFunManager
{
	//单例实例
	private static CmdFunManager s_instance = null;
	//指令ID对应proto消息名字
	private Map<Long, String> m_protoKeyNameMap = null;
	//proto消息名字对应指令ID
	private Map<String, Long> m_protoNameKeyMap = null;
	
	/**
	 * 单例构造
	 */
	private CmdFunManager()
	{
		m_protoKeyNameMap = new HashMap<Long, String>();
		m_protoNameKeyMap = new HashMap<String,Long>();
	}
	
	/**
	 * 单例获得接口
	 * @return
	 */
	public static CmdFunManager getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new CmdFunManager();
		}
		return s_instance;
	}
	
	/**
	 * 获得指令ID
	 * @param protoName proto消息名称
	 * @return
	 */
	public Long getCmdKey(final String protoName)
	{
		long key = 0L;
		if(m_protoNameKeyMap.get(protoName) != null)
		{
			key = m_protoNameKeyMap.get(protoName);
		}
		return key;
	}
	
	/**
	 * 获得proto消息名字
	 * @param cmdKey 指令ID
	 * @return
	 */
	public String getProtoName(final long cmdKey)
	{
		String protoName = new String();
		if(m_protoKeyNameMap.get(cmdKey) != null)
		{
			protoName = m_protoKeyNameMap.get(cmdKey);
		}
		return protoName;
	}
	
	/**
	 * 用左移的方法合成值
	 * @param logicID 逻辑ID
	 * @param cmdID 指令ID
	 * @return
	 */
	private long hasKey(final int logicID,final int cmdID)
	{
		long key = logicID;
		key <<= 8;
		key += cmdID;
		return key;
	}

	/**
	 * 读取指令map表
	 * @param xmlFile 文件名
	 * @return true 读取成功，否则失败
	 */
	public boolean init(final String xmlFile)
	{
		boolean ret = true;
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		try
		{
			DocumentBuilder db = dbf.newDocumentBuilder();
			Document doc = db.parse(xmlFile);
			NodeList nodelist = doc.getElementsByTagName("RegisterProto");

			for (int i = 0; i < nodelist.getLength(); i++)
			{
				Node childNode = nodelist.item(i); 
				NodeList nodelistTemp = childNode.getChildNodes();
				for(int cnt = 0; cnt < nodelistTemp.getLength(); cnt++)
				{
					Node tempNode = nodelistTemp.item(cnt);
					if(tempNode.getNodeType() != Node.ELEMENT_NODE)
					{
						continue;
					}
					Element elem = (Element) tempNode;
					int value = Integer.parseInt(elem.getAttribute("value"));
					for (Node node = tempNode.getFirstChild(); node != null; node = node.getNextSibling())
					{
						if (node.getNodeType() == Node.ELEMENT_NODE) 
						{
							Element elemTemp = (Element) node;
							String protoName = elemTemp.getAttribute("proto");
							int valueTemp = Integer.parseInt(elemTemp.getAttribute("value"));
							m_protoKeyNameMap.put(hasKey(value,valueTemp),protoName);
							m_protoNameKeyMap.put(protoName,hasKey(value,valueTemp));
						}
					}
				}
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
			ret = false;
		}
		return ret;
	}
	
	/**
	 * log消息
	 */
	public void log()
	{
		Log.getInstance().debug("test the messageMap begin");
		
		String log = "test the key to message begin(" + String.valueOf(m_protoKeyNameMap.size()) + ")";
		Log.getInstance().debug(log);
		for (Map.Entry<Long, String> entry : m_protoKeyNameMap.entrySet())
		{
			log = "key:" + String.valueOf(entry.getKey()) + " message:" + entry.getValue();
			Log.getInstance().debug(log);
		}
		log = "test the key to message end(" + String.valueOf(m_protoKeyNameMap.size()) + ")";
		Log.getInstance().debug(log);
		
		
		log = "test the message to key begin(" + String.valueOf(m_protoNameKeyMap.size()) + ")";
		Log.getInstance().debug(log);
		for (Map.Entry<String, Long> entry : m_protoNameKeyMap.entrySet())
		{
			log = "key:" + entry.getKey() + " message:" + String.valueOf(entry.getValue());
			Log.getInstance().debug(log);
		}
		log = "test the message to key begin(" + String.valueOf(m_protoNameKeyMap.size()) + ")";
		Log.getInstance().debug(log);
		
		Log.getInstance().debug("test the messageMap end");
	}

}
