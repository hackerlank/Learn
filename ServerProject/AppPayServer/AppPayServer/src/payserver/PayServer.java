package payserver;
import java.nio.channels.*; 
import java.net.InetSocketAddress;
import java.util.Iterator;
import java.util.Properties;
import java.nio.ByteBuffer;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStreamWriter;

import servlet.AlipayServlet;

import com.alipay.util.httpClient.*;

/**
 * 支付服务器
 * @author flyer
 *
 */
public class PayServer
{
	//支付服务器单例实例
	private static PayServer s_instance = null;
	//监听端口
	public static int s_port = 8014;
	//ip地址
	public static String s_ip = "114.80.207.171";
	//是否为测试
	public static boolean s_test = false;
	//tomcat开放端口
	public static int s_tomcatPort = 8080;
	//用于检测所有Channel状态的Selector  
    private Selector m_selector = null;  
	/**
	 * 单例模式
	 */
	private PayServer()
	{
	}
	
	/**
	 * 单例获得支付服务器实例
	 * @return
	 */
	public static PayServer getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new PayServer();
		}
		return s_instance;
	}

	
	/**
	 * 初始化支付服务器
	 * @return true表示成功
	 */
	public boolean init()
	{
		boolean ret = true;
		Log.getInstance().setFileName("payserver");
		CmdFunManager instance = CmdFunManager.getInstance();
		instance.init(AlipayServlet.s_cmdXmlFile);
		instance.log();
		try
		{ 
		    FileInputStream input = new FileInputStream(AlipayServlet.s_propFile);  
		    Properties prop= new Properties();  
		    prop.load(input);  
		    s_ip = prop.getProperty("ip");
		    s_port = Integer.parseInt(prop.getProperty("port"));  
		    s_test = Boolean.parseBoolean(prop.getProperty("test"));
		    s_tomcatPort = Integer.parseInt(prop.getProperty("tomcatport"));
			m_selector = Selector.open();  
	        //通过open方法来打开一个未绑定的ServerSocketChannel实例  
	        ServerSocketChannel server = ServerSocketChannel.open();  
	        InetSocketAddress address = new InetSocketAddress(s_ip,s_port);  
	        //将该ServerSocketChannel绑定到指定ip地址  
	        server.socket().bind(address);  
	        //设置ServerSocket以非阻塞方式工作  
	        server.configureBlocking(false);  
	        //将server注册到指定Selector对象  
	        server.register(m_selector, SelectionKey.OP_ACCEPT);  
	        Log.getInstance().debug("success register address:" + s_ip + "," + "port:" + s_port);
        }
		catch(Exception e)
        {
			e.printStackTrace();
        	ret = false;
        }
		return ret;
	}

    public boolean accept()
	{
		boolean ret = true;
		try
		{
            while(m_selector.select() > 0)
            { 
                //依次处理selector上的每个已选择的SelectionKey  
                Iterator<SelectionKey> it = m_selector.selectedKeys().iterator();
                SelectionKey task = (SelectionKey) it.next(); 

                //从selector上的已选择Key集中删除正在处理的SelectionKey  
                m_selector.selectedKeys().remove(task);  
                //如果sk对应的通信包含客户端的连接请求  
                if(task.isAcceptable())
                {  
                    ServerSocketChannel server = (ServerSocketChannel)task.channel();
                    //调用accept方法接受连接，产生服务器端对应的SocketChannel  
                    long localPort = server.socket().getLocalPort();
                    if(localPort == s_port)
                    {
                        SocketChannel newTask = server.accept();
                        if(newTask != null)
                        {
                            boolean flag = PayTaskManager.getInstance().addPayTask(newTask); 
                            if(flag)
                            {
                                newTask.configureBlocking(false);
                                newTask.register(m_selector,SelectionKey.OP_READ);
                            }
                        }
                    }
                    //将sk对应的Channel设置成准备接受其他请求  
                    task.interestOps(SelectionKey.OP_ACCEPT);  
                }  
                //可读
                else if(task.isReadable())
                {
                    SocketChannel tempSocket = (SocketChannel) task.channel();
                    long localPort = tempSocket.socket().getPort();
                    PayTask payTask = PayTaskManager.getInstance().getPayTaskByLocalPort(localPort);
                    if(payTask != null)
                    {
                        payTask.parseMessage();
                    }
                    task.interestOps(SelectionKey.OP_READ);
                }
            }
        }
        catch(Exception e)
        {
			e.printStackTrace();
        	ret = false;
        }
        return ret;
    }

    public void remove(SocketChannel task)
    {
        m_selector.selectedKeys().remove(task);
    }
}
