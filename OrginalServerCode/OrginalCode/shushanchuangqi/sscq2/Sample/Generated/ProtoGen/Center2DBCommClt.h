/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Center2DBComm.h
//  Purpose:      CenterServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Center2DBComm.h"

namespace NCenter2DBComm
{

//协议类：CenterServer到DBServer的通信协议
class CCenter2DBCommClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：心跳
	bool Send_KeepAlive( //发送给当前协议处理的服务器
	);
	bool SendSvr_KeepAlive(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_KeepAlive( //只组包不发送
	);

	//发送：DBServer状态请求
	bool Send_GetStatus( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetStatus(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：插入玩家充值仙石信息(未创角预先充值)
	bool Send_InsertRecharge( //发送给当前协议处理的服务器
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	);
	bool SendSvr_InsertRecharge(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	);
	std::string& BuildPkg_InsertRecharge( //只组包不发送
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	);

	//发送：加载玩家未创角预先充值的仙石信息
	bool Send_LoadPrepaid( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecPrepaid& vecPrepaid //(返回值)玩家未创角预先值信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_LoadPrepaid(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecPrepaid& vecPrepaid //(返回值)玩家未创角预先值信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新玩家未创角预先充值信息
	bool Send_UpdatePrepaid( //发送给当前协议处理的服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		UINT64 qwRoleID, //玩家ID
		UINT32 dwGold //仙石数量
	);
	bool SendSvr_UpdatePrepaid(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		UINT64 qwRoleID, //玩家ID
		UINT32 dwGold //仙石数量
	);
	std::string& BuildPkg_UpdatePrepaid( //只组包不发送
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		UINT64 qwRoleID, //玩家ID
		UINT32 dwGold //仙石数量
	);

	//发送：替换帐号
	bool Send_ReplaceUser( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_ReplaceUser(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：加载离线玩家数据
	bool Send_LoadOffLineUserData( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet, //(返回值)0表示成功
			const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_LoadOffLineUserData(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet, //(返回值)0表示成功
			const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：一行数据更新
	bool Send_RoleDataUpdate( //发送给当前协议处理的服务器
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	);
	bool SendSvr_RoleDataUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	);
	std::string& BuildPkg_RoleDataUpdate( //只组包不发送
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	);

	//发送：获取排名信息
	bool Send_GetRankInfo( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetRankInfo(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetRankInfo( //只组包不发送
	);

	//发送：排行榜数据更新
	bool Send_RankDataUpdate( //发送给当前协议处理的服务器
		UINT64 qwInstID, //唯一ID
		NRankProt::ERankType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	bool SendSvr_RankDataUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwInstID, //唯一ID
		NRankProt::ERankType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	std::string& BuildPkg_RankDataUpdate( //只组包不发送
		UINT64 qwInstID, //唯一ID
		NRankProt::ERankType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);

	//发送：获取崇拜信息
	bool Send_GetAdoreInfo( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetAdoreInfo(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetAdoreInfo( //只组包不发送
	);

	//发送：崇拜数据更新
	bool Send_AdoreDataUpdate( //发送给当前协议处理的服务器
		UINT64 qwInstID, //唯一ID
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	bool SendSvr_AdoreDataUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwInstID, //唯一ID
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	std::string& BuildPkg_AdoreDataUpdate( //只组包不发送
		UINT64 qwInstID, //唯一ID
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);

	//发送：获取账号ID或主角色名请求
	bool Send_UserIDNameReq( //发送给当前协议处理的服务器
		NServerCommon::EUserReqType eType, //类型
		UINT64 qwUsrID, //帐号ID
		const std::string& strName, //主角色名称
		UINT64 qwUsrData //用户数据
	);
	bool SendSvr_UserIDNameReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NServerCommon::EUserReqType eType, //类型
		UINT64 qwUsrID, //帐号ID
		const std::string& strName, //主角色名称
		UINT64 qwUsrData //用户数据
	);
	std::string& BuildPkg_UserIDNameReq( //只组包不发送
		NServerCommon::EUserReqType eType, //类型
		UINT64 qwUsrID, //帐号ID
		const std::string& strName, //主角色名称
		UINT64 qwUsrData //用户数据
	);

	//发送：根据名字获取ID请求
	bool Send_GetUserIDFromName( //发送给当前协议处理的服务器
		const std::string& strName, //主角色名称
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(返回值)用户ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetUserIDFromName(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const std::string& strName, //主角色名称
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(返回值)用户ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获得邮件列表
	bool Send_GetAllMailList( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		UINT32 dwOverTime, //过期时间
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NMailProt::TVecMailDetail& vecMails //(返回值)邮件列表
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetAllMailList(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		UINT32 dwOverTime, //过期时间
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NMailProt::TVecMailDetail& vecMails //(返回值)邮件列表
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：保存邮件
	bool Send_SaveMail( //发送给当前协议处理的服务器
		UINT64 qwMailID, //邮件ID
		UINT64 qwReceiveID, //接受者ID
		UINT64 qwSenderID, //发送者ID
		const std::string& strSenderName, //发送者名字
		NMailProt::EMailType eMailType, //邮件类型
		NMailProt::EMailState eMailState, //邮件状态
		UINT32 dwSendTime, //发送时间
		const std::string& strTitle, //标题
		const std::string& strMsg, //邮件内容
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SaveMail(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwMailID, //邮件ID
		UINT64 qwReceiveID, //接受者ID
		UINT64 qwSenderID, //发送者ID
		const std::string& strSenderName, //发送者名字
		NMailProt::EMailType eMailType, //邮件类型
		NMailProt::EMailState eMailState, //邮件状态
		UINT32 dwSendTime, //发送时间
		const std::string& strTitle, //标题
		const std::string& strMsg, //邮件内容
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：删除邮件
	bool Send_DeleteMail( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		const TVecMailDelData& vecMailIDs, //邮件ID列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_DeleteMail(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		const TVecMailDelData& vecMailIDs, //邮件ID列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：保存系统邮件
	bool Send_SaveSystemMail( //发送给当前协议处理的服务器
		const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
		const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SaveSystemMail(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
		const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新邮件状态
	bool Send_UpdateMailStatus( //发送给当前协议处理的服务器
		UINT64 qwMailID, //邮件ID
		NMailProt::EMailState eMailState, //邮件状态
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_UpdateMailStatus(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwMailID, //邮件ID
		NMailProt::EMailState eMailState, //邮件状态
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：删除邮件附件
	bool Send_DelMailAttach( //发送给当前协议处理的服务器
		const MailDelData& stDelData, //删除提示
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_DelMailAttach(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const MailDelData& stDelData, //删除提示
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			INT8 byRet //(返回值)非0表示失败
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：查询玩家奖励状态
	bool Send_GetPrizeStatus( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NWonderActivityProt::TVecWonderPrize2DB& vecRet //(返回值)查询结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetPrizeStatus(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NWonderActivityProt::TVecWonderPrize2DB& vecRet //(返回值)查询结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：删除玩家数据
	bool Send_DelActPrizeData( //发送给当前协议处理的服务器
		UINT16 wActID //活动ID
	);
	bool SendSvr_DelActPrizeData(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT16 wActID //活动ID
	);
	std::string& BuildPkg_DelActPrizeData( //只组包不发送
		UINT16 wActID //活动ID
	);

	//发送：查询所有玩家信息
	bool Send_GetAllRoleLevel( //发送给当前协议处理的服务器
		UINT8 byType, //类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byTypeRet, //(返回值)类型
			const TVecRoleLevel& vecRoleLevel //(返回值)返回玩家等级
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetAllRoleLevel(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT8 byType, //类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byTypeRet, //(返回值)类型
			const TVecRoleLevel& vecRoleLevel //(返回值)返回玩家等级
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新玩家奖励状态
	bool Send_UpdatePrizeStatus( //发送给当前协议处理的服务器
		const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	bool SendSvr_UpdatePrizeStatus(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	std::string& BuildPkg_UpdatePrizeStatus( //只组包不发送
		const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);

	//发送：查询玩家保留信息
	bool Send_GetRetain( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NWonderActivityProt::TVecRetain& vecRet //(返回值)查询结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetRetain(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NWonderActivityProt::TVecRetain& vecRet //(返回值)查询结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新玩家保留信息
	bool Send_UpdateRetain( //发送给当前协议处理的服务器
		const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	bool SendSvr_UpdateRetain(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	std::string& BuildPkg_UpdateRetain( //只组包不发送
		const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);

	//发送：删除玩家保留数据
	bool Send_DelActRetainData( //发送给当前协议处理的服务器
		UINT16 wActID //活动ID
	);
	bool SendSvr_DelActRetainData(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT16 wActID //活动ID
	);
	std::string& BuildPkg_DelActRetainData( //只组包不发送
		UINT16 wActID //活动ID
	);

	//发送：请求所有UserID和name
	bool Send_GetAllUserIDAndName( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetAllUserIDAndName(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetAllUserIDAndName( //只组包不发送
	);

	//发送：请求所有公告
	bool Send_GetAllNotice( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetAllNotice(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetAllNotice( //只组包不发送
	);

	//发送：增加公告
	bool Send_AddNotice( //发送给当前协议处理的服务器
		const NPHPProt::SNotice& sNotice //公告内容
	);
	bool SendSvr_AddNotice(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NPHPProt::SNotice& sNotice //公告内容
	);
	std::string& BuildPkg_AddNotice( //只组包不发送
		const NPHPProt::SNotice& sNotice //公告内容
	);

	//发送：删除公告
	bool Send_DelNotice( //发送给当前协议处理的服务器
		UINT32 dwNoticeID //公告ID
	);
	bool SendSvr_DelNotice(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwNoticeID //公告ID
	);
	std::string& BuildPkg_DelNotice( //只组包不发送
		UINT32 dwNoticeID //公告ID
	);

	//发送：请求斗剑信息
	bool Send_GetAllArena( //发送给当前协议处理的服务器
		UINT32 dwPageSize //发送条数
	);
	bool SendSvr_GetAllArena(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize //发送条数
	);
	std::string& BuildPkg_GetAllArena( //只组包不发送
		UINT32 dwPageSize //发送条数
	);

	//发送：更新斗剑数据
	bool Send_UpdateAllArena( //发送给当前协议处理的服务器
		const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
	);
	bool SendSvr_UpdateAllArena(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
	);
	std::string& BuildPkg_UpdateAllArena( //只组包不发送
		const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
	);

	//发送：删除玩家斗剑数据
	bool Send_DelPlayerArena( //发送给当前协议处理的服务器
		const TVecUINT64& vecDel //删除玩家斗剑信息
	);
	bool SendSvr_DelPlayerArena(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT64& vecDel //删除玩家斗剑信息
	);
	std::string& BuildPkg_DelPlayerArena( //只组包不发送
		const TVecUINT64& vecDel //删除玩家斗剑信息
	);

	//发送：请求系统Var数据
	bool Send_GetGameVar( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar //(返回值)返回的Var
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetGameVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar //(返回值)返回的Var
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新系统Var数据
	bool Send_UpdateGameVar( //发送给当前协议处理的服务器
		const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
	);
	bool SendSvr_UpdateGameVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
	);
	std::string& BuildPkg_UpdateGameVar( //只组包不发送
		const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
	);

	//发送：增加系统Var数据
	bool Send_AddGameVar( //发送给当前协议处理的服务器
		const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
	);
	bool SendSvr_AddGameVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
	);
	std::string& BuildPkg_AddGameVar( //只组包不发送
		const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
	);

	//发送：删除Var数据
	bool Send_DelGameVar( //发送给当前协议处理的服务器
		UINT16 wVarID //删除的VarID
	);
	bool SendSvr_DelGameVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT16 wVarID //删除的VarID
	);
	std::string& BuildPkg_DelGameVar( //只组包不发送
		UINT16 wVarID //删除的VarID
	);

	//发送：根据玩家ID获得竞技基本数据
	bool Send_GetArenaFighterByID( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NArenaGS::SArenaFighter& stFighter //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetArenaFighterByID(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NArenaGS::SArenaFighter& stFighter //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获取镇妖塔信息（启动预加载调用）
	bool Send_GetDemonTowerInfo( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetDemonTowerInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新镇妖塔玩家信息
	bool Send_UpateDemonTowerInfo( //发送给当前协议处理的服务器
		NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
		const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
	);
	bool SendSvr_UpateDemonTowerInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
		const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
	);
	std::string& BuildPkg_UpateDemonTowerInfo( //只组包不发送
		NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
		const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
	);

	//发送：获取中心服数据
	bool Send_GetCenterData( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecCenterData& vecCenterData //(返回值)中心服数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetCenterData(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecCenterData& vecCenterData //(返回值)中心服数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新中心服数据
	bool Send_UpateCenterData( //发送给当前协议处理的服务器
		const SCenterData& oCenterData, //中心服数据
		bool bDelete //删除/更新
	);
	bool SendSvr_UpateCenterData(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SCenterData& oCenterData, //中心服数据
		bool bDelete //删除/更新
	);
	std::string& BuildPkg_UpateCenterData( //只组包不发送
		const SCenterData& oCenterData, //中心服数据
		bool bDelete //删除/更新
	);

	//发送：查看玩家私聊信息
	bool Send_GetWhisperInfo( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGlobalChatProt::SWhisperInfo& whisperInfo //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetWhisperInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGlobalChatProt::SWhisperInfo& whisperInfo //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获得玩家战报信息
	bool Send_GetBattleReport( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
		NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetBattleReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
		NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：增加玩家战报信息
	bool Send_AddBattleReport( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
		UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT64& vecBattleID //(返回值)删除的战报
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_AddBattleReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
		UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT64& vecBattleID //(返回值)删除的战报
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：重新加载表格
	bool Send_ReloadTable( //发送给当前协议处理的服务器
		const TVecString& vecTableName //表格名字
	);
	bool SendSvr_ReloadTable(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecString& vecTableName //表格名字
	);
	std::string& BuildPkg_ReloadTable( //只组包不发送
		const TVecString& vecTableName //表格名字
	);

	//发送：请求所有九疑鼎信息
	bool Send_GetAllTripod( //发送给当前协议处理的服务器
		UINT32 dwPageSize //发送条数
	);
	bool SendSvr_GetAllTripod(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize //发送条数
	);
	std::string& BuildPkg_GetAllTripod( //只组包不发送
		UINT32 dwPageSize //发送条数
	);

	//发送：请求所有九疑鼎的协助信息
	bool Send_GetAllTripodHelper( //发送给当前协议处理的服务器
		UINT32 dwPageSize //发送条数
	);
	bool SendSvr_GetAllTripodHelper(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize //发送条数
	);
	std::string& BuildPkg_GetAllTripodHelper( //只组包不发送
		UINT32 dwPageSize //发送条数
	);

	//发送：请求所有九疑鼎的动态信息
	bool Send_GetAllTripodLog( //发送给当前协议处理的服务器
		UINT32 dwPageSize //发送条数
	);
	bool SendSvr_GetAllTripodLog(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize //发送条数
	);
	std::string& BuildPkg_GetAllTripodLog( //只组包不发送
		UINT32 dwPageSize //发送条数
	);

	//发送：更新玩家九疑鼎信息
	bool Send_UpdateTripod( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
	);
	bool SendSvr_UpdateTripod(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
	);
	std::string& BuildPkg_UpdateTripod( //只组包不发送
		UINT64 qwRoleID, //玩家的ID
		const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
	);

	//发送：更新玩家九疑鼎协助信息
	bool Send_UpateTripodHelp( //发送给当前协议处理的服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
	);
	bool SendSvr_UpateTripodHelp(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
	);
	std::string& BuildPkg_UpateTripodHelp( //只组包不发送
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
	);

	//发送：更新玩家九疑鼎动态信息
	bool Send_UpdateTripodLog( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
	);
	bool SendSvr_UpdateTripodLog(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
	);
	std::string& BuildPkg_UpdateTripodLog( //只组包不发送
		UINT64 qwRoleID, //玩家的ID
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
	);

	//发送：增加离线事件
	bool Send_AddOffLineEvent( //发送给当前协议处理的服务器
		const TVecUINT64& vecRoleID, //玩家的ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件
	);
	bool SendSvr_AddOffLineEvent(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT64& vecRoleID, //玩家的ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件
	);
	std::string& BuildPkg_AddOffLineEvent( //只组包不发送
		const TVecUINT64& vecRoleID, //玩家的ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件
	);

	//发送：对玩家封号
	bool Send_FreezePlayer( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwFreezeTimer //封号
	);
	bool SendSvr_FreezePlayer(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwFreezeTimer //封号
	);
	std::string& BuildPkg_FreezePlayer( //只组包不发送
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwFreezeTimer //封号
	);

	//发送：对玩家禁言
	bool Send_ForbitChat( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwForbitTimer //禁言时间
	);
	bool SendSvr_ForbitChat(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwForbitTimer //禁言时间
	);
	std::string& BuildPkg_ForbitChat( //只组包不发送
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwForbitTimer //禁言时间
	);

	//发送：将玩家登录时IP写入数据库
	bool Send_UpdateLoginIP( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家的ID
		const std::string& strLoginIP //登录时IP
	);
	bool SendSvr_UpdateLoginIP(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家的ID
		const std::string& strLoginIP //登录时IP
	);
	std::string& BuildPkg_UpdateLoginIP( //只组包不发送
		UINT64 qwUserID, //玩家的ID
		const std::string& strLoginIP //登录时IP
	);

	//发送：请求拉取进入参数
	bool Send_GetPlatformParam( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetPlatformParam(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetPlatformParam( //只组包不发送
	);

	//发送：数据库查询
	bool Send_GetResult2DB( //发送给当前协议处理的服务器
		const SBaseCond& sBaseCond //查询条件
	);
	bool SendSvr_GetResult2DB(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SBaseCond& sBaseCond //查询条件
	);
	std::string& BuildPkg_GetResult2DB( //只组包不发送
		const SBaseCond& sBaseCond //查询条件
	);

	//发送：请求金船信息
	bool Send_GetAllShip( //发送给当前协议处理的服务器
		UINT32 dwPageSize //发送条数
	);
	bool SendSvr_GetAllShip(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize //发送条数
	);
	std::string& BuildPkg_GetAllShip( //只组包不发送
		UINT32 dwPageSize //发送条数
	);

	//发送：更新金船数据
	bool Send_UpdateShip( //发送给当前协议处理的服务器
		const NShipProt::PlayerShip& UpdateInfo //更新信息
	);
	bool SendSvr_UpdateShip(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NShipProt::PlayerShip& UpdateInfo //更新信息
	);
	std::string& BuildPkg_UpdateShip( //只组包不发送
		const NShipProt::PlayerShip& UpdateInfo //更新信息
	);

	//发送：删除金船数据
	bool Send_DelShip( //发送给当前协议处理的服务器
		UINT64 qwInsID //删除金船信息
	);
	bool SendSvr_DelShip(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwInsID //删除金船信息
	);
	std::string& BuildPkg_DelShip( //只组包不发送
		UINT64 qwInsID //删除金船信息
	);

	//发送：增加金船报告
	bool Send_AddShipReport( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //报告拥有者
		const NShipProt::ShipReport& sReport //报告内容
	);
	bool SendSvr_AddShipReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //报告拥有者
		const NShipProt::ShipReport& sReport //报告内容
	);
	std::string& BuildPkg_AddShipReport( //只组包不发送
		UINT64 qwRoleID, //报告拥有者
		const NShipProt::ShipReport& sReport //报告内容
	);

	//发送：删除金船报告
	bool Send_DelShipReport( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //报告拥有者
		UINT64 qwInsID //金船唯一ID
	);
	bool SendSvr_DelShipReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //报告拥有者
		UINT64 qwInsID //金船唯一ID
	);
	std::string& BuildPkg_DelShipReport( //只组包不发送
		UINT64 qwRoleID, //报告拥有者
		UINT64 qwInsID //金船唯一ID
	);

	//发送：天元神兽同步玩家信息
	bool Send_SyncMonsterUserInfo( //发送给当前协议处理的服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SGuildUser2DB& sUser //数据
	);
	bool SendSvr_SyncMonsterUserInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SGuildUser2DB& sUser //数据
	);
	std::string& BuildPkg_SyncMonsterUserInfo( //只组包不发送
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SGuildUser2DB& sUser //数据
	);

	//发送：获取天元神兽信息（启动预加载调用）
	bool Send_GetGodMonsterInfo( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGodMonsterProt::TVecGuildUser2DB& vecUser //(返回值)天元神兽玩家信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetGodMonsterInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGodMonsterProt::TVecGuildUser2DB& vecUser //(返回值)天元神兽玩家信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：天元神兽同步玩家限购礼包信息
	bool Send_SyncLimitPrizeInfo( //发送给当前协议处理的服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
	);
	bool SendSvr_SyncLimitPrizeInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
	);
	std::string& BuildPkg_SyncLimitPrizeInfo( //只组包不发送
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
	);

	//发送：获取天元神兽玩家限购礼包信息（启动预加载调用）
	bool Send_GetLimitPrizeInfo( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetLimitPrizeInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：运营活动中心同步信息
	bool Send_SyncActivityCenterInfo( //发送给当前协议处理的服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NProtoCommon::SActivityOpt& oActOpt //数据
	);
	bool SendSvr_SyncActivityCenterInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NProtoCommon::SActivityOpt& oActOpt //数据
	);
	std::string& BuildPkg_SyncActivityCenterInfo( //只组包不发送
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NProtoCommon::SActivityOpt& oActOpt //数据
	);

	//发送：运营活动中心操作（启动预加载调用）
	bool Send_GetActivityCenterInfo( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NProtoCommon::TVecActivityOpt& vecActOpt //(返回值)数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetActivityCenterInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NProtoCommon::TVecActivityOpt& vecActOpt //(返回值)数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：增加机器人新信息
	bool Send_AddLadderRobot( //发送给当前协议处理的服务器
		const NArenaGS::TVecLadderRobot& vecData //数据
	);
	bool SendSvr_AddLadderRobot(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NArenaGS::TVecLadderRobot& vecData //数据
	);
	std::string& BuildPkg_AddLadderRobot( //只组包不发送
		const NArenaGS::TVecLadderRobot& vecData //数据
	);

	//发送：增加机器人新信息
	bool Send_UpdateLadderRobot( //发送给当前协议处理的服务器
		const NArenaGS::SLadderRobot& SData //数据
	);
	bool SendSvr_UpdateLadderRobot(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NArenaGS::SLadderRobot& SData //数据
	);
	std::string& BuildPkg_UpdateLadderRobot( //只组包不发送
		const NArenaGS::SLadderRobot& SData //数据
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：返回查询结果
	virtual void OnRecv_SendResult2Cent(
		const SBaseCond& sCond, //查询条件
		const SBaseResult& sResult //查询结果
	) = 0;

	//接收：返回所有玩家ID和名字
	virtual void OnRecv_SendAllUserIDAndName(
		UINT32 dwTotalSize, //总条数
		const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
	) = 0;

	//接收：返回所有公告
	virtual void OnRecv_SendAllNotice(
		const NPHPProt::TVecNotice& vecNotice //公告内容
	) = 0;

	//接收：返回请求斗剑信息
	virtual void OnRecv_SendAllArena(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
	) = 0;

	//接收：返回机器人天梯排行信息
	virtual void OnRecv_SendAllRobot(
		const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
	) = 0;

	//接收：返回请求排行榜数据
	virtual void OnRecv_RankInitNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecRankInfo& vecRankInfo //更新信息
	) = 0;

	//接收：返回请求崇拜数据
	virtual void OnRecv_AdoreInitNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
	) = 0;

	//接收：返回所有九疑鼎信息
	virtual void OnRecv_SendAllTripod(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodData& vecSendData //更新信息
	) = 0;

	//接收：返回所有九疑鼎的协助信息
	virtual void OnRecv_SendAllTripodHelper(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodHelp& vecSendData //更新信息
	) = 0;

	//接收：返回所有九疑鼎的动态信息
	virtual void OnRecv_SendAllTripodLog(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodLog& vecSendData //更新信息
	) = 0;

	//接收：平台参数加载返回
	virtual void OnRecv_PlatformParamInfoNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecUINT64& vecRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
	) = 0;

	//接收：返回请求金船信息
	virtual void OnRecv_SendAllShip(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NShipProt::TVecPlayerShip& vecSendDate //更新信息
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 31; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_SendResult2Cent(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllUserIDAndName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllArena(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllRobot(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RankInitNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AdoreInitNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllTripod(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllTripodHelper(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllTripodLog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlatformParamInfoNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllShip(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_GetStatus(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetStatus(UINT32 dwSessionID);
	bool _DoReturn_LoadPrepaid(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_LoadPrepaid(UINT32 dwSessionID);
	bool _DoReturn_ReplaceUser(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_ReplaceUser(UINT32 dwSessionID);
	bool _DoReturn_LoadOffLineUserData(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_LoadOffLineUserData(UINT32 dwSessionID);
	bool _DoReturn_GetUserIDFromName(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetUserIDFromName(UINT32 dwSessionID);
	bool _DoReturn_GetAllMailList(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetAllMailList(UINT32 dwSessionID);
	bool _DoReturn_SaveMail(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SaveMail(UINT32 dwSessionID);
	bool _DoReturn_DeleteMail(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_DeleteMail(UINT32 dwSessionID);
	bool _DoReturn_SaveSystemMail(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SaveSystemMail(UINT32 dwSessionID);
	bool _DoReturn_UpdateMailStatus(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_UpdateMailStatus(UINT32 dwSessionID);
	bool _DoReturn_DelMailAttach(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_DelMailAttach(UINT32 dwSessionID);
	bool _DoReturn_GetPrizeStatus(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetPrizeStatus(UINT32 dwSessionID);
	bool _DoReturn_GetAllRoleLevel(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetAllRoleLevel(UINT32 dwSessionID);
	bool _DoReturn_GetRetain(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetRetain(UINT32 dwSessionID);
	bool _DoReturn_GetGameVar(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetGameVar(UINT32 dwSessionID);
	bool _DoReturn_GetArenaFighterByID(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetArenaFighterByID(UINT32 dwSessionID);
	bool _DoReturn_GetDemonTowerInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetDemonTowerInfo(UINT32 dwSessionID);
	bool _DoReturn_GetCenterData(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetCenterData(UINT32 dwSessionID);
	bool _DoReturn_GetWhisperInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetWhisperInfo(UINT32 dwSessionID);
	bool _DoReturn_GetBattleReport(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetBattleReport(UINT32 dwSessionID);
	bool _DoReturn_AddBattleReport(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_AddBattleReport(UINT32 dwSessionID);
	bool _DoReturn_GetGodMonsterInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetGodMonsterInfo(UINT32 dwSessionID);
	bool _DoReturn_GetLimitPrizeInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetLimitPrizeInfo(UINT32 dwSessionID);
	bool _DoReturn_GetActivityCenterInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetActivityCenterInfo(UINT32 dwSessionID);

private:
	typedef bool (CCenter2DBCommClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CCenter2DBCommClt::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCenter2DBComm
