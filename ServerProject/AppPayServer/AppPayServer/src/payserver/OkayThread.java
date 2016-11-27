package payserver;

/**
 * 主逻辑线程
 * @author flyer
 *
 */
public class OkayThread extends Thread
{
	private static OkayThread s_instance = null;
	private OkayThread()
	{
	}
	public static OkayThread getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new OkayThread();
		}
		return s_instance;
	}
	
	/**
	 * 线程处理函数
	 */
	public void run()
	{
		while(true)
		{
            PayTaskManager.getInstance().loop();
			try
			{
				Thread.sleep(2000);
			}
			catch(Exception e)
			{
				e.printStackTrace();
				Thread.interrupted();
				break;
			}
		}
	}
}
