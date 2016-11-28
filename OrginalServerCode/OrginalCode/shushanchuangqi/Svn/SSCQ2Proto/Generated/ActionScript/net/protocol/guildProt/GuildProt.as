/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GuildProt.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：帮派相关协议
	 */
	public class GuildProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取帮派面板信息
		 */
		public function send_GetGuildInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetGuildInfo = new SOrigParam_GetGuildInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得帮派列表
		 * @param dwIndex (无符号32位整数)帮派索引
		 * @param dwCount (无符号32位整数)帮派个数
		 */
		public function send_GetGuildList(dwIndex:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetGuildList = new SOrigParam_GetGuildList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwIndex);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取帮派申请列表信息
		 */
		public function send_GetGuildApplyInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetGuildApplyInfo = new SOrigParam_GetGuildApplyInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：创建帮派
		 * @param strName 帮派名称
		 */
		public function send_CreateGuild(strName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_CreateGuild = new SOrigParam_CreateGuild();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：申请加入帮派
		 * @param qwGuildID (无符号64位整数)帮派ID
		 */
		public function send_ApplyGuild(qwGuildID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_ApplyGuild = new SOrigParam_ApplyGuild();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwGuildID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：通过加入申请
		 * @param qwRoleID (无符号64位整数)申请者ID
		 */
		public function send_AgreeApply(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_AgreeApply = new SOrigParam_AgreeApply();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：全部同意
		 */
		public function send_AgreeApplyAll(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_AgreeApplyAll = new SOrigParam_AgreeApplyAll();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：拒绝加入申请
		 * @param qwRoleID (无符号64位整数)申请者ID
		 */
		public function send_RejectApply(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_RejectApply = new SOrigParam_RejectApply();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：全部拒绝
		 */
		public function send_RejectApplyAll(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_RejectApplyAll = new SOrigParam_RejectApplyAll();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：邀请加入
		 * @param strName 被邀请者名字
		 */
		public function send_InviteApply(strName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_InviteApply = new SOrigParam_InviteApply();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得已申请帮派列表
		 */
		public function send_GetGuildApplyList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_GetGuildApplyList = new SOrigParam_GetGuildApplyList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：撤销帮派申请
		 * @param qwGuildID (无符号64位整数)帮派ID
		 */
		public function send_CancelApply(qwGuildID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_CancelApply = new SOrigParam_CancelApply();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwGuildID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：邀请回应
		 * @param qwGuildID (无符号64位整数)帮派ID
		 * @param bAgree 同意/拒绝
		 */
		public function send_InviteReply(qwGuildID:BigInteger, bAgree:Boolean, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_InviteReply = new SOrigParam_InviteReply();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwGuildID);
			bytes_.writeBoolean(bAgree);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：退出帮派
		 */
		public function send_QuitGuild(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_QuitGuild = new SOrigParam_QuitGuild();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：设置权限
		 * @param eRank (枚举类型：EMemberRank)职位
		 * @param dwAuthority (无符号32位整数)可选权限
		 */
		public function send_SetAuthority(eRank:uint, dwAuthority:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 15);
			var origParam_:SOrigParam_SetAuthority = new SOrigParam_SetAuthority();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eRank);
			bytes_.writeUnsignedInt(dwAuthority);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：编辑公告
		 * @param strInfo 公告信息
		 */
		public function send_EditInfo(strInfo:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 16);
			var origParam_:SOrigParam_EditInfo = new SOrigParam_EditInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strInfo);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：帮派成员操作
		 * @param qwRoleID (无符号64位整数)被设置者ID
		 * @param eOpType (枚举类型：EMemberOperateType)操作类型
		 */
		public function send_MemberOperate(qwRoleID:BigInteger, eOpType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 17);
			var origParam_:SOrigParam_MemberOperate = new SOrigParam_MemberOperate();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 17;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			bytes_.writeByte(eOpType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：弹劾回应
		 * @param qwGuildID (无符号64位整数)帮派ID
		 * @param bAgree 同意/拒绝
		 */
		public function send_ImpeachReply(qwGuildID:BigInteger, bAgree:Boolean, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 18);
			var origParam_:SOrigParam_ImpeachReply = new SOrigParam_ImpeachReply();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 18;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwGuildID);
			bytes_.writeBoolean(bAgree);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：发起弹劾
		 */
		public function send_LaunchImpeach(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 19);
			var origParam_:SOrigParam_LaunchImpeach = new SOrigParam_LaunchImpeach();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 19;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：搜索帮派
		 * @param strName 帮派名称
		 */
		public function send_SearchGuildByName(strName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 20);
			var origParam_:SOrigParam_SearchGuildByName = new SOrigParam_SearchGuildByName();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 20;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：根据帮主搜索帮派
		 * @param strOwnerName 帮主名称
		 */
		public function send_SearchGuildByOwnerName(strOwnerName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 21);
			var origParam_:SOrigParam_SearchGuildByOwnerName = new SOrigParam_SearchGuildByOwnerName();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 21;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strOwnerName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：根据帮主搜索帮派
		 * @param strName 帮派名称
		 * @param strOwnerName 帮主名称
		 */
		public function send_SearchGuildByBothName(strName:String, strOwnerName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 22);
			var origParam_:SOrigParam_SearchGuildByBothName = new SOrigParam_SearchGuildByBothName();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 22;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strName);
			BytesUtil.writeString(bytes_, strOwnerName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：提升帮派建筑等级
		 * @param eBuildingType (枚举类型：EBuildingType)帮派建筑类型
		 */
		public function send_UpgradeBuilding(eBuildingType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 23);
			var origParam_:SOrigParam_UpgradeBuilding = new SOrigParam_UpgradeBuilding();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 23;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eBuildingType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：提升帮派科技等级
		 * @param eType (枚举类型：ETechType)帮派科技类型
		 */
		public function send_UpgradeTech(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 24);
			var origParam_:SOrigParam_UpgradeTech = new SOrigParam_UpgradeTech();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 24;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：帮派捐献
		 * @param dwMoney (无符号32位整数)捐献数量
		 */
		public function send_Donate(dwMoney:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 25);
			var origParam_:SOrigParam_Donate = new SOrigParam_Donate();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 25;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwMoney);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：帮派供奉
		 * @param eType (枚举类型：EWorshipType)供奉类型
		 */
		public function send_Worship(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 26);
			var origParam_:SOrigParam_Worship = new SOrigParam_Worship();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 26;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：募集帮众
		 */
		public function send_Muster(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 27);
			var origParam_:SOrigParam_Muster = new SOrigParam_Muster();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 27;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取玩家的羲和神车信息
		 * @param qwUserID (无符号64位整数)玩家ID(可为自己ID也可为帮派成员ID)
		 */
		public function send_GetXiheInfo(qwUserID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 28;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家接受羲和神车任务
		 */
		public function send_AcceptXiheTask():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 29;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取自己帮派成员的羲和神车请求帮助列表
		 */
		public function send_GetXiheRequestInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 28);
			var origParam_:SOrigParam_GetXiheRequestInfo = new SOrigParam_GetXiheRequestInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 30;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：羲和神车装货
		 * @param byType (无符号8位整数)0:用道具装货 1:用仙石装货
		 * @param byPos (无符号8位整数)货物顺序索引(0~7)
		 */
		public function send_ShipGoods(byType:uint, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 29);
			var origParam_:SOrigParam_ShipGoods = new SOrigParam_ShipGoods();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 31;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：羲和神车发货
		 */
		public function send_DeliveryGoods(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 30);
			var origParam_:SOrigParam_DeliveryGoods = new SOrigParam_DeliveryGoods();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 32;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：羲和神车请求帮助装货
		 * @param byPos (无符号8位整数)货物顺序索引(0~7)
		 */
		public function send_RequestForHelp(byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 31);
			var origParam_:SOrigParam_RequestForHelp = new SOrigParam_RequestForHelp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 33;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：羲和神车帮众成员帮助装货
		 * @param byType (无符号8位整数)0:用道具装货 1:用仙石装货
		 * @param qwOtherID (无符号64位整数)玩家ID
		 * @param byPos (无符号8位整数)货物顺序索引(0~7)
		 */
		public function send_HelpShipGoods(byType:uint, qwOtherID:BigInteger, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 32);
			var origParam_:SOrigParam_HelpShipGoods = new SOrigParam_HelpShipGoods();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 34;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			BytesUtil.writeUInt64(bytes_, qwOtherID);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求帮派兑换物品信息
		 */
		public function send_ReqGuildExchangedItemInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 33);
			var origParam_:SOrigParam_ReqGuildExchangedItemInfo = new SOrigParam_ReqGuildExchangedItemInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 35;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求帮派兑换物品
		 * @param dwExchangeID (无符号32位整数)兑换id
		 * @param dwCount (无符号32位整数)兑换数量
		 */
		public function send_ReqGuildExchangeItem(dwExchangeID:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 34);
			var origParam_:SOrigParam_ReqGuildExchangeItem = new SOrigParam_ReqGuildExchangeItem();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 36;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwExchangeID);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求帮派兑换物品日志信息
		 */
		public function send_ReqGuildExchangeItemLogInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 35);
			var origParam_:SOrigParam_ReqGuildExchangeItemLogInfo = new SOrigParam_ReqGuildExchangeItemLogInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 37;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：帮派创建结果通知
		private function _doRecv_GuildCreateNotify(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECreateResult)创建结果
			var vecGuildInfo:Vector.<SGuildAllInfo> = SGuildAllInfo.vectorFromByteArray(bytes); //帮派信息(大小为0或者1)
			var event_:REvt_GuildCreateNotify = new REvt_GuildCreateNotify(REvt_GuildCreateNotify.DATA_RECEIVE);
			event_.eResult = eResult;
			event_.vecGuildInfo = vecGuildInfo;
			dispatchEvent(event_);
		}

		//接收处理：帮派信息更新
		private function _doRecv_GuildInfoNotify(bytes:ByteArray):void
		{
			var eDataType:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildDataType)帮派信息类型
			var vecGuildInfoBase:Vector.<SGuildInfoBase> = SGuildInfoBase.superVectorFromByteArray(bytes); //帮派信息
			var event_:REvt_GuildInfoNotify = new REvt_GuildInfoNotify(REvt_GuildInfoNotify.DATA_RECEIVE);
			event_.eDataType = eDataType;
			event_.vecGuildInfoBase = vecGuildInfoBase;
			dispatchEvent(event_);
		}

		//接收处理：帮派列表信息
		private function _doRecv_GuildListInfoNotify(bytes:ByteArray):void
		{
			var dwMaxGuildCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大帮派
			var dwCurGuildCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前帮派索引
			var vecGuildListInfo:Vector.<SGuildListInfo> = SGuildListInfo.vectorFromByteArray(bytes); //帮派列表信息
			var event_:REvt_GuildListInfoNotify = new REvt_GuildListInfoNotify(REvt_GuildListInfoNotify.DATA_RECEIVE);
			event_.dwMaxGuildCount = dwMaxGuildCount;
			event_.dwCurGuildCount = dwCurGuildCount;
			event_.vecGuildListInfo = vecGuildListInfo;
			dispatchEvent(event_);
		}

		//接收处理：帮派申请通过通知
		private function _doRecv_GuildApplyPassedNotify(bytes:ByteArray):void
		{
			var sGuildAllInfo:SGuildAllInfo = SGuildAllInfo.fromByteArray(bytes); //帮派信息
			var event_:REvt_GuildApplyPassedNotify = new REvt_GuildApplyPassedNotify(REvt_GuildApplyPassedNotify.DATA_RECEIVE);
			event_.sGuildAllInfo = sGuildAllInfo;
			dispatchEvent(event_);
		}

		//接收处理：帮派申请拒绝通知
		private function _doRecv_GuildApplyRejectNotify(bytes:ByteArray):void
		{
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帮派ID
			var event_:REvt_GuildApplyRejectNotify = new REvt_GuildApplyRejectNotify(REvt_GuildApplyRejectNotify.DATA_RECEIVE);
			event_.qwGuildID = qwGuildID;
			dispatchEvent(event_);
		}

		//接收处理：帮派被踢出通知
		private function _doRecv_GuildKickNotify(bytes:ByteArray):void
		{
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帮派ID
			var strName:String = BytesUtil.readString(bytes); //帮派名称
			var strKickName:String = BytesUtil.readString(bytes); //踢人者姓名
			var event_:REvt_GuildKickNotify = new REvt_GuildKickNotify(REvt_GuildKickNotify.DATA_RECEIVE);
			event_.qwGuildID = qwGuildID;
			event_.strName = strName;
			event_.strKickName = strKickName;
			dispatchEvent(event_);
		}

		//接收处理：玩家被邀请进入帮派通知
		private function _doRecv_GuildInviteNotify(bytes:ByteArray):void
		{
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帮派ID
			var strGuildName:String = BytesUtil.readString(bytes); //帮派名称
			var strInviterName:String = BytesUtil.readString(bytes); //邀请者名称
			var event_:REvt_GuildInviteNotify = new REvt_GuildInviteNotify(REvt_GuildInviteNotify.DATA_RECEIVE);
			event_.qwGuildID = qwGuildID;
			event_.strGuildName = strGuildName;
			event_.strInviterName = strInviterName;
			dispatchEvent(event_);
		}

		//接收处理：帮派弹劾通知
		private function _doRecv_GuildImpeachNotify(bytes:ByteArray):void
		{
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帮派ID
			var strLauncherName:String = BytesUtil.readString(bytes); //发起者姓名
			var strOwnerName:String = BytesUtil.readString(bytes); //帮主姓名
			var event_:REvt_GuildImpeachNotify = new REvt_GuildImpeachNotify(REvt_GuildImpeachNotify.DATA_RECEIVE);
			event_.qwGuildID = qwGuildID;
			event_.strLauncherName = strLauncherName;
			event_.strOwnerName = strOwnerName;
			dispatchEvent(event_);
		}

		//接收处理：帮派弹劾取消通知
		private function _doRecv_GuildImpeachSucceedNotify(bytes:ByteArray):void
		{
			var event_:REvt_GuildImpeachSucceedNotify = new REvt_GuildImpeachSucceedNotify(REvt_GuildImpeachSucceedNotify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：帮派弹劾取消通知
		private function _doRecv_GuildImpeachFailedNotify(bytes:ByteArray):void
		{
			var event_:REvt_GuildImpeachFailedNotify = new REvt_GuildImpeachFailedNotify(REvt_GuildImpeachFailedNotify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：帮派弹劾取消通知
		private function _doRecv_GuildImpeachCancelNotify(bytes:ByteArray):void
		{
			var event_:REvt_GuildImpeachCancelNotify = new REvt_GuildImpeachCancelNotify(REvt_GuildImpeachCancelNotify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：更新玩家羲和神车信息
		private function _doRecv_UpdateGuildXiheInfo(bytes:ByteArray):void
		{
			var sGuildXihe:SGuildXihe = SGuildXihe.fromByteArray(bytes); //玩家羲和神车信息
			var event_:REvt_UpdateGuildXiheInfo = new REvt_UpdateGuildXiheInfo(REvt_UpdateGuildXiheInfo.DATA_RECEIVE);
			event_.sGuildXihe = sGuildXihe;
			dispatchEvent(event_);
		}

		//接收处理：更新玩家羲和神车帮助信息
		private function _doRecv_GuildXiheHelpNotify(bytes:ByteArray):void
		{
			var byType:uint = bytes.readUnsignedByte(); //(无符号8位整数)0增加请求帮助信息 1删除帮助列表的信息 2删除请求帮助信息添加XX帮助信息
			var sXiheRequest:SXiheRequest = SXiheRequest.fromByteArray(bytes); //玩家羲和神车请求帮助的信息
			var event_:REvt_GuildXiheHelpNotify = new REvt_GuildXiheHelpNotify(REvt_GuildXiheHelpNotify.DATA_RECEIVE);
			event_.byType = byType;
			event_.sXiheRequest = sXiheRequest;
			dispatchEvent(event_);
		}

		//接收处理：帮派兑换物品更新
		private function _doRecv_GuildExchangedItemNotify(bytes:ByteArray):void
		{
			var vecGuildExchangedItem:Vector.<SGuildExchangedItem> = SGuildExchangedItem.vectorFromByteArray(bytes); //兑换物品信息
			var dwGUildAllMemberExchangedItemNum:uint = bytes.readUnsignedInt(); //(无符号32位整数)帮派所有成员兑换物品总数量
			var dwPlayerExchangedItemNum:uint = bytes.readUnsignedInt(); //(无符号32位整数)玩家兑换物品总数量
			var event_:REvt_GuildExchangedItemNotify = new REvt_GuildExchangedItemNotify(REvt_GuildExchangedItemNotify.DATA_RECEIVE);
			event_.vecGuildExchangedItem = vecGuildExchangedItem;
			event_.dwGUildAllMemberExchangedItemNum = dwGUildAllMemberExchangedItemNum;
			event_.dwPlayerExchangedItemNum = dwPlayerExchangedItemNum;
			dispatchEvent(event_);
		}

		//接收处理：帮派战兑换物品开始
		private function _doRecv_GuildExchangedItemBeginNotify(bytes:ByteArray):void
		{
			var vecLingShanType:Vector.<uint> = BytesUtil.readVecUByte(bytes); //(无符号8位整数)灵山类型
			var event_:REvt_GuildExchangedItemBeginNotify = new REvt_GuildExchangedItemBeginNotify(REvt_GuildExchangedItemBeginNotify.DATA_RECEIVE);
			event_.vecLingShanType = vecLingShanType;
			dispatchEvent(event_);
		}

		//接收处理：帮派兑换物品日志更新
		private function _doRecv_GuildExchangeItemLogNotify(bytes:ByteArray):void
		{
			var sGuildLogInfo:SGuildLogInfo = SGuildLogInfo.fromByteArray(bytes); //兑换物品日志信息
			var event_:REvt_GuildExchangeItemLogNotify = new REvt_GuildExchangeItemLogNotify(REvt_GuildExchangeItemLogNotify.DATA_RECEIVE);
			event_.sGuildLogInfo = sGuildLogInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取帮派面板信息
		private function _doReturn_GetGuildInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuildInfo = new SRetParam_GetGuildInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sGuildInfoBase:SGetGuildInfoBase = SGetGuildInfoBase.superFromByteArray(bytes); //返回结果
			retParam_.sGuildInfoBase = sGuildInfoBase;
			var origParam_:SOrigParam_GetGuildInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuildInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuildInfo = new TEvt_GetGuildInfo(TEvt_GetGuildInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取帮派面板信息
		private function _onTimeOut_GetGuildInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuildInfo = new SRetParam_GetGuildInfo();
			var event_:TEvt_GetGuildInfo = new TEvt_GetGuildInfo(TEvt_GetGuildInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得帮派列表
		private function _doReturn_GetGuildList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuildList = new SRetParam_GetGuildList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildResult)返回结果
			var sListInfo:SOtherGuildListInfo = SOtherGuildListInfo.fromByteArray(bytes); //帮派列表信息
			retParam_.eResult = eResult;
			retParam_.sListInfo = sListInfo;
			var origParam_:SOrigParam_GetGuildList = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuildList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuildList = new TEvt_GetGuildList(TEvt_GetGuildList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得帮派列表
		private function _onTimeOut_GetGuildList(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuildList = new SRetParam_GetGuildList();
			var event_:TEvt_GetGuildList = new TEvt_GetGuildList(TEvt_GetGuildList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取帮派申请列表信息
		private function _doReturn_GetGuildApplyInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuildApplyInfo = new SRetParam_GetGuildApplyInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildResult)返回结果
			var vecApplyInfo:Vector.<SGuildApplyInfo> = SGuildApplyInfo.vectorFromByteArray(bytes); //申请列表
			retParam_.eResult = eResult;
			retParam_.vecApplyInfo = vecApplyInfo;
			var origParam_:SOrigParam_GetGuildApplyInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuildApplyInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuildApplyInfo = new TEvt_GetGuildApplyInfo(TEvt_GetGuildApplyInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取帮派申请列表信息
		private function _onTimeOut_GetGuildApplyInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuildApplyInfo = new SRetParam_GetGuildApplyInfo();
			var event_:TEvt_GetGuildApplyInfo = new TEvt_GetGuildApplyInfo(TEvt_GetGuildApplyInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：创建帮派
		private function _doReturn_CreateGuild(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CreateGuild = new SRetParam_CreateGuild();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECreateResult)创建结果
			var vecGuildInfo:Vector.<SGuildAllInfo> = SGuildAllInfo.vectorFromByteArray(bytes); //帮派信息(大小为0或者1)
			retParam_.eResult = eResult;
			retParam_.vecGuildInfo = vecGuildInfo;
			var origParam_:SOrigParam_CreateGuild = _sessionMgr.getData(sessionID_) as SOrigParam_CreateGuild;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CreateGuild = new TEvt_CreateGuild(TEvt_CreateGuild.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：创建帮派
		private function _onTimeOut_CreateGuild(sessionID:uint):void
		{
			var retParam:SRetParam_CreateGuild = new SRetParam_CreateGuild();
			var event_:TEvt_CreateGuild = new TEvt_CreateGuild(TEvt_CreateGuild.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：申请加入帮派
		private function _doReturn_ApplyGuild(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ApplyGuild = new SRetParam_ApplyGuild();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)申请列表信息
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ApplyGuild = _sessionMgr.getData(sessionID_) as SOrigParam_ApplyGuild;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ApplyGuild = new TEvt_ApplyGuild(TEvt_ApplyGuild.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：申请加入帮派
		private function _onTimeOut_ApplyGuild(sessionID:uint):void
		{
			var retParam:SRetParam_ApplyGuild = new SRetParam_ApplyGuild();
			var event_:TEvt_ApplyGuild = new TEvt_ApplyGuild(TEvt_ApplyGuild.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：通过加入申请
		private function _doReturn_AgreeApply(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AgreeApply = new SRetParam_AgreeApply();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_AgreeApply = _sessionMgr.getData(sessionID_) as SOrigParam_AgreeApply;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AgreeApply = new TEvt_AgreeApply(TEvt_AgreeApply.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：通过加入申请
		private function _onTimeOut_AgreeApply(sessionID:uint):void
		{
			var retParam:SRetParam_AgreeApply = new SRetParam_AgreeApply();
			var event_:TEvt_AgreeApply = new TEvt_AgreeApply(TEvt_AgreeApply.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：全部同意
		private function _doReturn_AgreeApplyAll(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AgreeApplyAll = new SRetParam_AgreeApplyAll();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_AgreeApplyAll = _sessionMgr.getData(sessionID_) as SOrigParam_AgreeApplyAll;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AgreeApplyAll = new TEvt_AgreeApplyAll(TEvt_AgreeApplyAll.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：全部同意
		private function _onTimeOut_AgreeApplyAll(sessionID:uint):void
		{
			var retParam:SRetParam_AgreeApplyAll = new SRetParam_AgreeApplyAll();
			var event_:TEvt_AgreeApplyAll = new TEvt_AgreeApplyAll(TEvt_AgreeApplyAll.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：拒绝加入申请
		private function _doReturn_RejectApply(bytes:ByteArray):void
		{
			var retParam_:SRetParam_RejectApply = new SRetParam_RejectApply();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_RejectApply = _sessionMgr.getData(sessionID_) as SOrigParam_RejectApply;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_RejectApply = new TEvt_RejectApply(TEvt_RejectApply.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：拒绝加入申请
		private function _onTimeOut_RejectApply(sessionID:uint):void
		{
			var retParam:SRetParam_RejectApply = new SRetParam_RejectApply();
			var event_:TEvt_RejectApply = new TEvt_RejectApply(TEvt_RejectApply.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：全部拒绝
		private function _doReturn_RejectApplyAll(bytes:ByteArray):void
		{
			var retParam_:SRetParam_RejectApplyAll = new SRetParam_RejectApplyAll();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_RejectApplyAll = _sessionMgr.getData(sessionID_) as SOrigParam_RejectApplyAll;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_RejectApplyAll = new TEvt_RejectApplyAll(TEvt_RejectApplyAll.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：全部拒绝
		private function _onTimeOut_RejectApplyAll(sessionID:uint):void
		{
			var retParam:SRetParam_RejectApplyAll = new SRetParam_RejectApplyAll();
			var event_:TEvt_RejectApplyAll = new TEvt_RejectApplyAll(TEvt_RejectApplyAll.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：邀请加入
		private function _doReturn_InviteApply(bytes:ByteArray):void
		{
			var retParam_:SRetParam_InviteApply = new SRetParam_InviteApply();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_InviteApply = _sessionMgr.getData(sessionID_) as SOrigParam_InviteApply;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_InviteApply = new TEvt_InviteApply(TEvt_InviteApply.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：邀请加入
		private function _onTimeOut_InviteApply(sessionID:uint):void
		{
			var retParam:SRetParam_InviteApply = new SRetParam_InviteApply();
			var event_:TEvt_InviteApply = new TEvt_InviteApply(TEvt_InviteApply.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得已申请帮派列表
		private function _doReturn_GetGuildApplyList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuildApplyList = new SRetParam_GetGuildApplyList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			var vecGuildListInfo:Vector.<SGuildListInfo> = SGuildListInfo.vectorFromByteArray(bytes); //帮派列表信息
			retParam_.eResult = eResult;
			retParam_.vecGuildListInfo = vecGuildListInfo;
			var origParam_:SOrigParam_GetGuildApplyList = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuildApplyList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuildApplyList = new TEvt_GetGuildApplyList(TEvt_GetGuildApplyList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得已申请帮派列表
		private function _onTimeOut_GetGuildApplyList(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuildApplyList = new SRetParam_GetGuildApplyList();
			var event_:TEvt_GetGuildApplyList = new TEvt_GetGuildApplyList(TEvt_GetGuildApplyList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：撤销帮派申请
		private function _doReturn_CancelApply(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CancelApply = new SRetParam_CancelApply();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CancelApply = _sessionMgr.getData(sessionID_) as SOrigParam_CancelApply;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CancelApply = new TEvt_CancelApply(TEvt_CancelApply.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：撤销帮派申请
		private function _onTimeOut_CancelApply(sessionID:uint):void
		{
			var retParam:SRetParam_CancelApply = new SRetParam_CancelApply();
			var event_:TEvt_CancelApply = new TEvt_CancelApply(TEvt_CancelApply.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：邀请回应
		private function _doReturn_InviteReply(bytes:ByteArray):void
		{
			var retParam_:SRetParam_InviteReply = new SRetParam_InviteReply();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EApplyResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_InviteReply = _sessionMgr.getData(sessionID_) as SOrigParam_InviteReply;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_InviteReply = new TEvt_InviteReply(TEvt_InviteReply.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：邀请回应
		private function _onTimeOut_InviteReply(sessionID:uint):void
		{
			var retParam:SRetParam_InviteReply = new SRetParam_InviteReply();
			var event_:TEvt_InviteReply = new TEvt_InviteReply(TEvt_InviteReply.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：退出帮派
		private function _doReturn_QuitGuild(bytes:ByteArray):void
		{
			var retParam_:SRetParam_QuitGuild = new SRetParam_QuitGuild();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EQuitResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_QuitGuild = _sessionMgr.getData(sessionID_) as SOrigParam_QuitGuild;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_QuitGuild = new TEvt_QuitGuild(TEvt_QuitGuild.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：退出帮派
		private function _onTimeOut_QuitGuild(sessionID:uint):void
		{
			var retParam:SRetParam_QuitGuild = new SRetParam_QuitGuild();
			var event_:TEvt_QuitGuild = new TEvt_QuitGuild(TEvt_QuitGuild.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：设置权限
		private function _doReturn_SetAuthority(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SetAuthority = new SRetParam_SetAuthority();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESetAuthorityResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SetAuthority = _sessionMgr.getData(sessionID_) as SOrigParam_SetAuthority;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SetAuthority = new TEvt_SetAuthority(TEvt_SetAuthority.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：设置权限
		private function _onTimeOut_SetAuthority(sessionID:uint):void
		{
			var retParam:SRetParam_SetAuthority = new SRetParam_SetAuthority();
			var event_:TEvt_SetAuthority = new TEvt_SetAuthority(TEvt_SetAuthority.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：编辑公告
		private function _doReturn_EditInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EditInfo = new SRetParam_EditInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEditInfoResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_EditInfo = _sessionMgr.getData(sessionID_) as SOrigParam_EditInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EditInfo = new TEvt_EditInfo(TEvt_EditInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：编辑公告
		private function _onTimeOut_EditInfo(sessionID:uint):void
		{
			var retParam:SRetParam_EditInfo = new SRetParam_EditInfo();
			var event_:TEvt_EditInfo = new TEvt_EditInfo(TEvt_EditInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派成员操作
		private function _doReturn_MemberOperate(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MemberOperate = new SRetParam_MemberOperate();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EMemberOperateResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MemberOperate = _sessionMgr.getData(sessionID_) as SOrigParam_MemberOperate;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MemberOperate = new TEvt_MemberOperate(TEvt_MemberOperate.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派成员操作
		private function _onTimeOut_MemberOperate(sessionID:uint):void
		{
			var retParam:SRetParam_MemberOperate = new SRetParam_MemberOperate();
			var event_:TEvt_MemberOperate = new TEvt_MemberOperate(TEvt_MemberOperate.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：弹劾回应
		private function _doReturn_ImpeachReply(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ImpeachReply = new SRetParam_ImpeachReply();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EImpeachResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ImpeachReply = _sessionMgr.getData(sessionID_) as SOrigParam_ImpeachReply;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ImpeachReply = new TEvt_ImpeachReply(TEvt_ImpeachReply.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：弹劾回应
		private function _onTimeOut_ImpeachReply(sessionID:uint):void
		{
			var retParam:SRetParam_ImpeachReply = new SRetParam_ImpeachReply();
			var event_:TEvt_ImpeachReply = new TEvt_ImpeachReply(TEvt_ImpeachReply.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：发起弹劾
		private function _doReturn_LaunchImpeach(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LaunchImpeach = new SRetParam_LaunchImpeach();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EImpeachResult)弹劾结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_LaunchImpeach = _sessionMgr.getData(sessionID_) as SOrigParam_LaunchImpeach;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LaunchImpeach = new TEvt_LaunchImpeach(TEvt_LaunchImpeach.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：发起弹劾
		private function _onTimeOut_LaunchImpeach(sessionID:uint):void
		{
			var retParam:SRetParam_LaunchImpeach = new SRetParam_LaunchImpeach();
			var event_:TEvt_LaunchImpeach = new TEvt_LaunchImpeach(TEvt_LaunchImpeach.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：搜索帮派
		private function _doReturn_SearchGuildByName(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SearchGuildByName = new SRetParam_SearchGuildByName();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildResult)返回结果
			var vecGuildListInfo:Vector.<SGuildListInfo> = SGuildListInfo.vectorFromByteArray(bytes); //帮派列表信息
			retParam_.eResult = eResult;
			retParam_.vecGuildListInfo = vecGuildListInfo;
			var origParam_:SOrigParam_SearchGuildByName = _sessionMgr.getData(sessionID_) as SOrigParam_SearchGuildByName;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SearchGuildByName = new TEvt_SearchGuildByName(TEvt_SearchGuildByName.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：搜索帮派
		private function _onTimeOut_SearchGuildByName(sessionID:uint):void
		{
			var retParam:SRetParam_SearchGuildByName = new SRetParam_SearchGuildByName();
			var event_:TEvt_SearchGuildByName = new TEvt_SearchGuildByName(TEvt_SearchGuildByName.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：根据帮主搜索帮派
		private function _doReturn_SearchGuildByOwnerName(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SearchGuildByOwnerName = new SRetParam_SearchGuildByOwnerName();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildResult)返回结果
			var vecGuildListInfo:Vector.<SGuildListInfo> = SGuildListInfo.vectorFromByteArray(bytes); //帮派列表信息
			retParam_.eResult = eResult;
			retParam_.vecGuildListInfo = vecGuildListInfo;
			var origParam_:SOrigParam_SearchGuildByOwnerName = _sessionMgr.getData(sessionID_) as SOrigParam_SearchGuildByOwnerName;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SearchGuildByOwnerName = new TEvt_SearchGuildByOwnerName(TEvt_SearchGuildByOwnerName.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：根据帮主搜索帮派
		private function _onTimeOut_SearchGuildByOwnerName(sessionID:uint):void
		{
			var retParam:SRetParam_SearchGuildByOwnerName = new SRetParam_SearchGuildByOwnerName();
			var event_:TEvt_SearchGuildByOwnerName = new TEvt_SearchGuildByOwnerName(TEvt_SearchGuildByOwnerName.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：根据帮主搜索帮派
		private function _doReturn_SearchGuildByBothName(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SearchGuildByBothName = new SRetParam_SearchGuildByBothName();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildResult)返回结果
			var vecGuildListInfo:Vector.<SGuildListInfo> = SGuildListInfo.vectorFromByteArray(bytes); //帮派列表信息
			retParam_.eResult = eResult;
			retParam_.vecGuildListInfo = vecGuildListInfo;
			var origParam_:SOrigParam_SearchGuildByBothName = _sessionMgr.getData(sessionID_) as SOrigParam_SearchGuildByBothName;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SearchGuildByBothName = new TEvt_SearchGuildByBothName(TEvt_SearchGuildByBothName.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：根据帮主搜索帮派
		private function _onTimeOut_SearchGuildByBothName(sessionID:uint):void
		{
			var retParam:SRetParam_SearchGuildByBothName = new SRetParam_SearchGuildByBothName();
			var event_:TEvt_SearchGuildByBothName = new TEvt_SearchGuildByBothName(TEvt_SearchGuildByBothName.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：提升帮派建筑等级
		private function _doReturn_UpgradeBuilding(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeBuilding = new SRetParam_UpgradeBuilding();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EBuildingResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UpgradeBuilding = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeBuilding;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeBuilding = new TEvt_UpgradeBuilding(TEvt_UpgradeBuilding.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：提升帮派建筑等级
		private function _onTimeOut_UpgradeBuilding(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeBuilding = new SRetParam_UpgradeBuilding();
			var event_:TEvt_UpgradeBuilding = new TEvt_UpgradeBuilding(TEvt_UpgradeBuilding.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：提升帮派科技等级
		private function _doReturn_UpgradeTech(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeTech = new SRetParam_UpgradeTech();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETechResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UpgradeTech = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeTech;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeTech = new TEvt_UpgradeTech(TEvt_UpgradeTech.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：提升帮派科技等级
		private function _onTimeOut_UpgradeTech(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeTech = new SRetParam_UpgradeTech();
			var event_:TEvt_UpgradeTech = new TEvt_UpgradeTech(TEvt_UpgradeTech.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派捐献
		private function _doReturn_Donate(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Donate = new SRetParam_Donate();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDonateResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Donate = _sessionMgr.getData(sessionID_) as SOrigParam_Donate;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Donate = new TEvt_Donate(TEvt_Donate.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派捐献
		private function _onTimeOut_Donate(sessionID:uint):void
		{
			var retParam:SRetParam_Donate = new SRetParam_Donate();
			var event_:TEvt_Donate = new TEvt_Donate(TEvt_Donate.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派供奉
		private function _doReturn_Worship(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Worship = new SRetParam_Worship();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EStatueResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Worship = _sessionMgr.getData(sessionID_) as SOrigParam_Worship;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Worship = new TEvt_Worship(TEvt_Worship.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派供奉
		private function _onTimeOut_Worship(sessionID:uint):void
		{
			var retParam:SRetParam_Worship = new SRetParam_Worship();
			var event_:TEvt_Worship = new TEvt_Worship(TEvt_Worship.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：募集帮众
		private function _doReturn_Muster(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Muster = new SRetParam_Muster();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Muster = _sessionMgr.getData(sessionID_) as SOrigParam_Muster;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Muster = new TEvt_Muster(TEvt_Muster.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：募集帮众
		private function _onTimeOut_Muster(sessionID:uint):void
		{
			var retParam:SRetParam_Muster = new SRetParam_Muster();
			var event_:TEvt_Muster = new TEvt_Muster(TEvt_Muster.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取自己帮派成员的羲和神车请求帮助列表
		private function _doReturn_GetXiheRequestInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetXiheRequestInfo = new SRetParam_GetXiheRequestInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecXiheRequest:Vector.<SXiheRequest> = SXiheRequest.vectorFromByteArray(bytes); //玩家羲和神车请求帮助的信息
			retParam_.vecXiheRequest = vecXiheRequest;
			var origParam_:SOrigParam_GetXiheRequestInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetXiheRequestInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetXiheRequestInfo = new TEvt_GetXiheRequestInfo(TEvt_GetXiheRequestInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取自己帮派成员的羲和神车请求帮助列表
		private function _onTimeOut_GetXiheRequestInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetXiheRequestInfo = new SRetParam_GetXiheRequestInfo();
			var event_:TEvt_GetXiheRequestInfo = new TEvt_GetXiheRequestInfo(TEvt_GetXiheRequestInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：羲和神车装货
		private function _doReturn_ShipGoods(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ShipGoods = new SRetParam_ShipGoods();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildXiheResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ShipGoods = _sessionMgr.getData(sessionID_) as SOrigParam_ShipGoods;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ShipGoods = new TEvt_ShipGoods(TEvt_ShipGoods.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：羲和神车装货
		private function _onTimeOut_ShipGoods(sessionID:uint):void
		{
			var retParam:SRetParam_ShipGoods = new SRetParam_ShipGoods();
			var event_:TEvt_ShipGoods = new TEvt_ShipGoods(TEvt_ShipGoods.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：羲和神车发货
		private function _doReturn_DeliveryGoods(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DeliveryGoods = new SRetParam_DeliveryGoods();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildXiheResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_DeliveryGoods = _sessionMgr.getData(sessionID_) as SOrigParam_DeliveryGoods;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DeliveryGoods = new TEvt_DeliveryGoods(TEvt_DeliveryGoods.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：羲和神车发货
		private function _onTimeOut_DeliveryGoods(sessionID:uint):void
		{
			var retParam:SRetParam_DeliveryGoods = new SRetParam_DeliveryGoods();
			var event_:TEvt_DeliveryGoods = new TEvt_DeliveryGoods(TEvt_DeliveryGoods.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：羲和神车请求帮助装货
		private function _doReturn_RequestForHelp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_RequestForHelp = new SRetParam_RequestForHelp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildXiheResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_RequestForHelp = _sessionMgr.getData(sessionID_) as SOrigParam_RequestForHelp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_RequestForHelp = new TEvt_RequestForHelp(TEvt_RequestForHelp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：羲和神车请求帮助装货
		private function _onTimeOut_RequestForHelp(sessionID:uint):void
		{
			var retParam:SRetParam_RequestForHelp = new SRetParam_RequestForHelp();
			var event_:TEvt_RequestForHelp = new TEvt_RequestForHelp(TEvt_RequestForHelp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：羲和神车帮众成员帮助装货
		private function _doReturn_HelpShipGoods(bytes:ByteArray):void
		{
			var retParam_:SRetParam_HelpShipGoods = new SRetParam_HelpShipGoods();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildXiheResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_HelpShipGoods = _sessionMgr.getData(sessionID_) as SOrigParam_HelpShipGoods;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_HelpShipGoods = new TEvt_HelpShipGoods(TEvt_HelpShipGoods.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：羲和神车帮众成员帮助装货
		private function _onTimeOut_HelpShipGoods(sessionID:uint):void
		{
			var retParam:SRetParam_HelpShipGoods = new SRetParam_HelpShipGoods();
			var event_:TEvt_HelpShipGoods = new TEvt_HelpShipGoods(TEvt_HelpShipGoods.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求帮派兑换物品信息
		private function _doReturn_ReqGuildExchangedItemInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqGuildExchangedItemInfo = new SRetParam_ReqGuildExchangedItemInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecLingShanType:Vector.<uint> = BytesUtil.readVecUByte(bytes); //(无符号8位整数)灵山类型
			var vecGuildExchangedItem:Vector.<SGuildExchangedItem> = SGuildExchangedItem.vectorFromByteArray(bytes); //兑换物品信息
			var dwGUildAllMemberExchangedItemNum:uint = bytes.readUnsignedInt(); //(无符号32位整数)帮派所有成员兑换物品总数量
			var dwPlayerExchangedItemNum:uint = bytes.readUnsignedInt(); //(无符号32位整数)玩家兑换物品总数量
			var eMemberLastRank:uint = bytes.readUnsignedByte(); //(枚举类型：EMemberRank)玩家上一次帮派职位
			retParam_.vecLingShanType = vecLingShanType;
			retParam_.vecGuildExchangedItem = vecGuildExchangedItem;
			retParam_.dwGUildAllMemberExchangedItemNum = dwGUildAllMemberExchangedItemNum;
			retParam_.dwPlayerExchangedItemNum = dwPlayerExchangedItemNum;
			retParam_.eMemberLastRank = eMemberLastRank;
			var origParam_:SOrigParam_ReqGuildExchangedItemInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqGuildExchangedItemInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqGuildExchangedItemInfo = new TEvt_ReqGuildExchangedItemInfo(TEvt_ReqGuildExchangedItemInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求帮派兑换物品信息
		private function _onTimeOut_ReqGuildExchangedItemInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqGuildExchangedItemInfo = new SRetParam_ReqGuildExchangedItemInfo();
			var event_:TEvt_ReqGuildExchangedItemInfo = new TEvt_ReqGuildExchangedItemInfo(TEvt_ReqGuildExchangedItemInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求帮派兑换物品
		private function _doReturn_ReqGuildExchangeItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqGuildExchangeItem = new SRetParam_ReqGuildExchangeItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGuildExchangeRet)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ReqGuildExchangeItem = _sessionMgr.getData(sessionID_) as SOrigParam_ReqGuildExchangeItem;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqGuildExchangeItem = new TEvt_ReqGuildExchangeItem(TEvt_ReqGuildExchangeItem.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求帮派兑换物品
		private function _onTimeOut_ReqGuildExchangeItem(sessionID:uint):void
		{
			var retParam:SRetParam_ReqGuildExchangeItem = new SRetParam_ReqGuildExchangeItem();
			var event_:TEvt_ReqGuildExchangeItem = new TEvt_ReqGuildExchangeItem(TEvt_ReqGuildExchangeItem.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求帮派兑换物品日志信息
		private function _doReturn_ReqGuildExchangeItemLogInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqGuildExchangeItemLogInfo = new SRetParam_ReqGuildExchangeItemLogInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecGuildLogInfo:Vector.<SGuildLogInfo> = SGuildLogInfo.vectorFromByteArray(bytes); //兑换物品日志信息
			retParam_.vecGuildLogInfo = vecGuildLogInfo;
			var origParam_:SOrigParam_ReqGuildExchangeItemLogInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqGuildExchangeItemLogInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqGuildExchangeItemLogInfo = new TEvt_ReqGuildExchangeItemLogInfo(TEvt_ReqGuildExchangeItemLogInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求帮派兑换物品日志信息
		private function _onTimeOut_ReqGuildExchangeItemLogInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqGuildExchangeItemLogInfo = new SRetParam_ReqGuildExchangeItemLogInfo();
			var event_:TEvt_ReqGuildExchangeItemLogInfo = new TEvt_ReqGuildExchangeItemLogInfo(TEvt_ReqGuildExchangeItemLogInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GuildProt;

		public static function get instance():GuildProt
		{
			if(_instance == null)
				_instance = new GuildProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GuildProt()
		{
			_protID = 16;
			_recvFuncList = [
				_doRecv_GuildCreateNotify, //FuncID: 1
				_doRecv_GuildInfoNotify, //FuncID: 2
				_doRecv_GuildListInfoNotify, //FuncID: 3
				_doRecv_GuildApplyPassedNotify, //FuncID: 4
				_doRecv_GuildApplyRejectNotify, //FuncID: 5
				_doRecv_GuildKickNotify, //FuncID: 6
				_doRecv_GuildInviteNotify, //FuncID: 7
				_doRecv_GuildImpeachNotify, //FuncID: 8
				_doRecv_GuildImpeachSucceedNotify, //FuncID: 9
				_doRecv_GuildImpeachFailedNotify, //FuncID: 10
				_doRecv_GuildImpeachCancelNotify, //FuncID: 11
				_doRecv_UpdateGuildXiheInfo, //FuncID: 12
				_doRecv_GuildXiheHelpNotify, //FuncID: 13
				_doRecv_GuildExchangedItemNotify, //FuncID: 14
				_doRecv_GuildExchangedItemBeginNotify, //FuncID: 15
				_doRecv_GuildExchangeItemLogNotify //FuncID: 16
			];

			_retFuncList = [
				_doReturn_GetGuildInfo, //FuncID: 1
				_doReturn_GetGuildList, //FuncID: 2
				_doReturn_GetGuildApplyInfo, //FuncID: 3
				_doReturn_CreateGuild, //FuncID: 4
				_doReturn_ApplyGuild, //FuncID: 5
				_doReturn_AgreeApply, //FuncID: 6
				_doReturn_AgreeApplyAll, //FuncID: 7
				_doReturn_RejectApply, //FuncID: 8
				_doReturn_RejectApplyAll, //FuncID: 9
				_doReturn_InviteApply, //FuncID: 10
				_doReturn_GetGuildApplyList, //FuncID: 11
				_doReturn_CancelApply, //FuncID: 12
				_doReturn_InviteReply, //FuncID: 13
				_doReturn_QuitGuild, //FuncID: 14
				_doReturn_SetAuthority, //FuncID: 15
				_doReturn_EditInfo, //FuncID: 16
				_doReturn_MemberOperate, //FuncID: 17
				_doReturn_ImpeachReply, //FuncID: 18
				_doReturn_LaunchImpeach, //FuncID: 19
				_doReturn_SearchGuildByName, //FuncID: 20
				_doReturn_SearchGuildByOwnerName, //FuncID: 21
				_doReturn_SearchGuildByBothName, //FuncID: 22
				_doReturn_UpgradeBuilding, //FuncID: 23
				_doReturn_UpgradeTech, //FuncID: 24
				_doReturn_Donate, //FuncID: 25
				_doReturn_Worship, //FuncID: 26
				_doReturn_Muster, //FuncID: 27
				_doReturn_GetXiheRequestInfo, //FuncID: 28
				_doReturn_ShipGoods, //FuncID: 29
				_doReturn_DeliveryGoods, //FuncID: 30
				_doReturn_RequestForHelp, //FuncID: 31
				_doReturn_HelpShipGoods, //FuncID: 32
				_doReturn_ReqGuildExchangedItemInfo, //FuncID: 33
				_doReturn_ReqGuildExchangeItem, //FuncID: 34
				_doReturn_ReqGuildExchangeItemLogInfo //FuncID: 35
			];

			_timeFuncList = [
				_onTimeOut_GetGuildInfo, //FuncID: 1
				_onTimeOut_GetGuildList, //FuncID: 2
				_onTimeOut_GetGuildApplyInfo, //FuncID: 3
				_onTimeOut_CreateGuild, //FuncID: 4
				_onTimeOut_ApplyGuild, //FuncID: 5
				_onTimeOut_AgreeApply, //FuncID: 6
				_onTimeOut_AgreeApplyAll, //FuncID: 7
				_onTimeOut_RejectApply, //FuncID: 8
				_onTimeOut_RejectApplyAll, //FuncID: 9
				_onTimeOut_InviteApply, //FuncID: 10
				_onTimeOut_GetGuildApplyList, //FuncID: 11
				_onTimeOut_CancelApply, //FuncID: 12
				_onTimeOut_InviteReply, //FuncID: 13
				_onTimeOut_QuitGuild, //FuncID: 14
				_onTimeOut_SetAuthority, //FuncID: 15
				_onTimeOut_EditInfo, //FuncID: 16
				_onTimeOut_MemberOperate, //FuncID: 17
				_onTimeOut_ImpeachReply, //FuncID: 18
				_onTimeOut_LaunchImpeach, //FuncID: 19
				_onTimeOut_SearchGuildByName, //FuncID: 20
				_onTimeOut_SearchGuildByOwnerName, //FuncID: 21
				_onTimeOut_SearchGuildByBothName, //FuncID: 22
				_onTimeOut_UpgradeBuilding, //FuncID: 23
				_onTimeOut_UpgradeTech, //FuncID: 24
				_onTimeOut_Donate, //FuncID: 25
				_onTimeOut_Worship, //FuncID: 26
				_onTimeOut_Muster, //FuncID: 27
				_onTimeOut_GetXiheRequestInfo, //FuncID: 28
				_onTimeOut_ShipGoods, //FuncID: 29
				_onTimeOut_DeliveryGoods, //FuncID: 30
				_onTimeOut_RequestForHelp, //FuncID: 31
				_onTimeOut_HelpShipGoods, //FuncID: 32
				_onTimeOut_ReqGuildExchangedItemInfo, //FuncID: 33
				_onTimeOut_ReqGuildExchangeItem, //FuncID: 34
				_onTimeOut_ReqGuildExchangeItemLogInfo //FuncID: 35
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0 || funcID > _recvFuncList.length
				 || funcID < -_retFuncList.length)
				return false;
			var func:Function;
			if(funcID > 0)
				func = _recvFuncList[funcID - 1];
			else
				func = _retFuncList[-funcID - 1];
			if(func != null)
			{
				func(bytes);
				return true;
			}
			return false;
		}

		public override function onTimeOut(funcID:uint, sessionID:uint):void
		{
			if(funcID == 0 || funcID > _timeFuncList.length)
				return;
			_timeFuncList[funcID - 1](sessionID);
		}
	}
}