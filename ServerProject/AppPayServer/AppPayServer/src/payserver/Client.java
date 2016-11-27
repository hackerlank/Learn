package payserver;

import java.net.Socket;

public class Client extends Thread{

	private static Client s_instance = null;
	private Client() 
	{
	}
	
	public static Client getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new Client();
		}
		return s_instance;
	}
	/**
	 * 线程处理函数
	 */
	public void run()
	{
        Log.getInstance().info("开始连接端口!");
        while(true)
        {
        	try
        	{
        		Socket socket = new Socket(PayServer.s_ip,PayServer.s_port);
        		Thread.sleep(5000);
        	}
        	catch(Exception e)
        	{
        		e.printStackTrace();
        	}
        }
	}
}
