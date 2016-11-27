package payserver;
import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.io.*;

import servlet.AlipayServlet;

public class Log 
{
	//名称
	private String m_fileName = null;
	//日志追加符号
	private String m_tag = null;
	//单例
	private static Log s_instance = null;
	//互斥锁对象
	private static Object s_lock = new Object();
	//文件流
	private FileOutputStream m_fp = null;
	//buffer流
	private BufferedWriter m_out = null;
	//debug等级
	private Map<String, Long> m_levelMap = null;
	//日志等级
	private int m_level = 0;
	//是否写在屏幕上
	private boolean m_writeScreen = true;
	//互斥锁
	private Lock m_lock = null;
	//上一个日志时间
	private int m_hour = 0;
	
	/**
	 * 构造
	 */
	private Log()
	{
		m_levelMap = new HashMap<String, Long>();
		m_lock = new ReentrantLock();
		init();
	}
	
	/**
	 * 获得单例
	 * @return
	 */
	public static Log getInstance()
	{
		if(s_instance == null)
		{
			s_instance = new Log();
		}
		return s_instance;
	}
	
	/**
	 * 初始化等级map
	 */
	private void init()
	{
		m_levelMap.put("debug:", 0L);
		m_levelMap.put("info:", 1L);
		m_levelMap.put("warn:", 2L);
		m_levelMap.put("error:", 3L);
	}
	
	/**
	 * 设置文件名
	 * @param fileName
	 */
	public void setFileName(final String fileName)
	{
		m_fileName = fileName;
	}
	
	/**
	 * 设置日志等级
	 * @param level
	 */
	public void setLevel(final int level)
	{
		m_level = level;
	}
	
	public void setWriteScene(final boolean flag)
	{
		m_writeScreen = flag;
	}
	/**
	 * 生成新的日志
	 */
	private void changeLog()
	{
		Date now = new Date();
		Calendar cal = Calendar.getInstance();
		int nowHour = cal.get(Calendar.HOUR_OF_DAY);
		if(m_hour != nowHour || m_fp == null)
		{
			m_hour = nowHour;
	        String temp = String.valueOf(cal.get(Calendar.YEAR));
	        temp += String.valueOf(cal.get(Calendar.MONTH) + 1);
	        temp += String.valueOf(cal.get(Calendar.DATE));
	        temp += String.valueOf(cal.get(Calendar.HOUR_OF_DAY));
	        m_tag = temp;
	        
			synchronized(s_lock)
			{
				String logDir = AlipayServlet.s_logFile + "/";
				//创建文件夹
				File fileDir = new File(logDir);
				if  (!fileDir .exists()  && !fileDir .isDirectory()) 
				{
					fileDir .mkdir();   
				}
				String tempFileName = logDir + "/" + m_fileName + "_" + m_tag + ".log";
			    File file = new File(tempFileName);
			    try
			    {
			    	if(m_fp != null)
		        	{
		        		m_fp.close();
		        	}
		        	if(m_out != null)
		        	{
		        		m_out.close();
		        	}
		        	if(!file.exists())    
				    { 
				    	file.createNewFile();
				    }
		        	m_fp = new FileOutputStream(tempFileName);
				    OutputStreamWriter outPut = new OutputStreamWriter(m_fp,"UTF-8");
				    m_out = new BufferedWriter(outPut);
			    }
			    catch(Exception e)
			    {
			    	e.printStackTrace();
			    }
			}
		}
		
	}
	
	/**
	 * 生成日志爱格式
	 * @param pattern
	 * @return
	 */
	private String time(String pattern)
	{
		Calendar cal = Calendar.getInstance();
		int year = cal.get(Calendar.YEAR);//获取年份
        int month = cal.get(Calendar.MONTH) + 1;//获取月份 
        int day = cal.get(Calendar.DATE);//获取日 
        int hour = cal.get(Calendar.HOUR_OF_DAY);//小时,注意时区
        int minute = cal.get(Calendar.MINUTE);//分           
        int second = cal.get(Calendar.SECOND);//秒 
		String format = String.valueOf(year);
		format += String.valueOf(month);
		format += String.valueOf(day);
		format += "-";
		format += String.valueOf(hour) + ":" ;
		format += String.valueOf(minute) + ":" ;
		format += String.valueOf(second);
		
		format += " payserver" + " " + pattern;
		return format;
	}
	
	/**
	 * debug
	 * @param arg
	 */
	public void debug(String arg)
	{
		logger("debug:",arg);
	}
	
	/**
	 * info
	 * @param arg
	 */
	public void info(String arg)
	{
		logger("info:",arg);
	}
	
	/**
	 * warn
	 * @param arg
	 */
	public void warn(String arg)
	{
		logger("warn:",arg);
	}
	
	/**
	 * error
	 * @param arg
	 */
	public void error(String arg)
	{
		logger("error:",arg);
	}
	
	/**
	 * 写日志
	 * @param level
	 * @param arg
	 */
	private void logger(String level,String arg)
	{
		if(m_levelMap.get(level) == null || m_levelMap.get(level) < m_level)
		{
			return;
		}
		m_lock.lock();
		changeLog();
		String format = time(level) + arg;
		try
		{
			m_out.newLine();
			m_out.write(format);
			m_out.flush();
			if(m_writeScreen)
			{
				System.out.println(format);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();  
		}
		m_lock.unlock();
	}

}
