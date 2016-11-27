package payserver;
import java.lang.*;

public class SignalProcess
{
    private Thread m_shutdownHook;
    private static SignalProcess s_instance = null;

    private SignalProcess()
    {
    }

    public static SignalProcess getInstance()
    {
        if(s_instance == null)
        {
            s_instance = new SignalProcess();
        }
        return s_instance;
    }

    public void addShutdownHook()
    {
        if(m_shutdownHook == null)
        {
            m_shutdownHook = new Thread("BootStrapShutdownHook")
            {
                public void run()
                {
                    System.out.println("ShutdownHook Executed...");
                }
            };
            m_shutdownHook.setDaemon(true);
            Runtime.getRuntime().addShutdownHook(m_shutdownHook);
        }
    }
}
