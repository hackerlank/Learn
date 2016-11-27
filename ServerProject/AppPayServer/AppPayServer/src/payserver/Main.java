package payserver;

/**
 * 程序入口
 * @author flyer
 *
 */
public class Main extends Thread
{
	private static Main s_instance = null;
	private Main() 
	{
	}
	
	public static Main getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new Main();
		}
		return s_instance;
	}
	/**
	 * 线程处理函数
	 */
	public void run()
	{
		PayServer.getInstance().init();
        SignalProcess.getInstance().addShutdownHook();
		OkayThread.getInstance().setDaemon(true);
		OkayThread.getInstance().start();
		//Client.getInstance().setDaemon(true);
		//Client.getInstance().start();
        Log.getInstance().info("支付服务器启动完毕!");
        while(true)
        {
            PayServer.getInstance().accept();
        }
	}
}
