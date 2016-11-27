#ifndef SCENE_SERVER_H
#define SCENE_SERVER_H

#include "base/baseSubService.h"
#include "sceneTimeTick.h"

class SceneServer : public SubNetService
{
	private:
		friend class SingletonBase<Service,false>;
		SceneServer();
		~SceneServer();

		/// @brief 停机保存数据
		void finalSave();

		/// @brief 命令统计开关
		void switchAnalysis(const bool switchFlg);
	public:
		static SceneServer &getInstance()
		{
			return Service::getInstance<SceneServer>();
		}
		
		/// @brieif 设置重新加载配置标记
		void reloadConfig();
		
		bool init();

		/// @brief 检测服务器是否停机
		void checkFinal();

		/// @brief 服务器进程结束
		void final();

		/// @brief 服务器启动
		void startUpOver();
		
		/// @brief 重新加载配置
		void checkAndReloadConfig();
		
		/// @brief 接收一个新连接
		void newTcpTask(const int sock,const struct sockaddr_in *addr);

		/// @brief 下面是处理各种服务器的消息
		bool msgParse_SuperService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_ZoneService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_FLServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_ChatServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_NameServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_GMServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_UserServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_InfoServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
	private:
		/// 重新加载配置标记
		static bool s_reloadConfig;
		/// 等待停机结束
		static bool s_waitFinal;
		/// 服务器初始化标志
		static bool s_initOK;
};

#endif
		

