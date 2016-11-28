/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    FighterProt.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SEquipTrump;
	import net.protocol.protoCommon.SFtAttrMod;
	import net.protocol.itemProt.SItem;
	import net.protocol.itemProt.SItemCount;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：道具相关协议
	 */
	public class FighterProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：散仙装备主动技能
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param dwSkillID (无符号32位整数)技能ID
		 * @param iSlot (有符号32位整数)技能槽 -1表示卸下技能
		 */
		public function send_FighterSkillEquipTo(qwInstID:BigInteger, dwSkillID:uint, iSlot:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_FighterSkillEquipTo = new SOrigParam_FighterSkillEquipTo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwSkillID);
			bytes_.writeInt(iSlot);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙技能升级
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param dwSkillID (无符号32位整数)技能ID
		 */
		public function send_FighterSkillLevelUp(qwInstID:BigInteger, dwSkillID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_FighterSkillLevelUp = new SOrigParam_FighterSkillLevelUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwSkillID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙被动技能升级
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param dwSkillID (无符号32位整数)技能ID
		 */
		public function send_FighterPassiveSkillLevelUp(qwInstID:BigInteger, dwSkillID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_FighterPassiveSkillLevelUp = new SOrigParam_FighterPassiveSkillLevelUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwSkillID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取客栈信息
		 */
		public function send_GetTavernInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GetTavernInfo = new SOrigParam_GetTavernInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：求签
		 * @param eType (枚举类型：EDrawType)求签类型
		 */
		public function send_Draw(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_Draw = new SOrigParam_Draw();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：招募
		 * @param wFighterID (无符号16位整数)将ID
		 */
		public function send_FighterRecruit(wFighterID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_FighterRecruit = new SOrigParam_FighterRecruit();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wFighterID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：淬体升级
		 * @param qwInstID (无符号64位整数)将唯一ID
		 * @param eCuiTiType (枚举类型：ECuiTiType)淬体类型
		 * @param byTimes (无符号8位整数)次数
		 */
		public function send_CuiTiUpgrade(qwInstID:BigInteger, eCuiTiType:uint, byTimes:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_CuiTiUpgrade = new SOrigParam_CuiTiUpgrade();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(eCuiTiType);
			bytes_.writeByte(byTimes);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙淬体全体(六种)升级一次
		 * @param qwInstID (无符号64位整数)将唯一ID
		 */
		public function send_CuiTiAllUpgrade(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_CuiTiAllUpgrade = new SOrigParam_CuiTiAllUpgrade();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：转移
		 * @param qwInstIDSrc (无符号64位整数)将唯一ID
		 * @param qwInstIDDst (无符号64位整数)将唯一ID
		 */
		public function send_FighterShift(qwInstIDSrc:BigInteger, qwInstIDDst:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_FighterShift = new SOrigParam_FighterShift();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstIDSrc);
			BytesUtil.writeUInt64(bytes_, qwInstIDDst);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：同步等级
		 * @param qwInstID (无符号64位整数)将唯一ID
		 * @param byGoalLvl (无符号8位整数)同步的目标等级
		 */
		public function send_FighterSyncLevel(qwInstID:BigInteger, byGoalLvl:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_FighterSyncLevel = new SOrigParam_FighterSyncLevel();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(byGoalLvl);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：渡劫升级
		 * @param qwInstID (无符号64位整数)将唯一ID
		 * @param byOneKey (无符号8位整数)是否一键(是>0 否=0)
		 */
		public function send_UpgradeDujie(qwInstID:BigInteger, byOneKey:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_UpgradeDujie = new SOrigParam_UpgradeDujie();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(byOneKey);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求散仙心法
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 */
		public function send_ReqFighterXinFaInfo(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_ReqFighterXinFaInfo = new SOrigParam_ReqFighterXinFaInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙学习心法
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param dwXinFaID (无符号32位整数)心法ID
		 */
		public function send_FighterActiveXinFa(qwInstID:BigInteger, dwXinFaID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_FighterActiveXinFa = new SOrigParam_FighterActiveXinFa();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwXinFaID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙心法升级
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param dwXinFaID (无符号32位整数)心法ID
		 */
		public function send_FighterXinFaLevelUp(qwInstID:BigInteger, dwXinFaID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_FighterXinFaLevelUp = new SOrigParam_FighterXinFaLevelUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwXinFaID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙心法散功
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param dwXinFaID (无符号32位整数)心法ID
		 */
		public function send_FighterXinFaDisperse(qwInstID:BigInteger, dwXinFaID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 15);
			var origParam_:SOrigParam_FighterXinFaDisperse = new SOrigParam_FighterXinFaDisperse();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwXinFaID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取玩家的所有散仙组合
		 */
		public function send_GetAllFighterCombination(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 16);
			var origParam_:SOrigParam_GetAllFighterCombination = new SOrigParam_GetAllFighterCombination();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：激活散仙组合
		 * @param byGroupID (无符号8位整数)散仙组合ID
		 */
		public function send_ActiveCombination(byGroupID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 17);
			var origParam_:SOrigParam_ActiveCombination = new SOrigParam_ActiveCombination();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 17;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byGroupID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：升级散仙组合
		 * @param byGroupID (无符号8位整数)散仙组合ID
		 * @param byOneKey (无符号8位整数)是否一键(是>0 否=0)
		 */
		public function send_UpgradeCombination(byGroupID:uint, byOneKey:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 18);
			var origParam_:SOrigParam_UpgradeCombination = new SOrigParam_UpgradeCombination();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 18;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byGroupID);
			bytes_.writeByte(byOneKey);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：装备散仙组合技能(连携技)
		 * @param byGroupID (无符号8位整数)散仙组合ID
		 * @param byType (无符号8位整数)1出战在阵型 2出战在守卫峨眉
		 */
		public function send_EquipToCombinationSkill(byGroupID:uint, byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 19);
			var origParam_:SOrigParam_EquipToCombinationSkill = new SOrigParam_EquipToCombinationSkill();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 19;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byGroupID);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙散功
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 */
		public function send_FighterDismiss(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 20);
			var origParam_:SOrigParam_FighterDismiss = new SOrigParam_FighterDismiss();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 20;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取购买散仙信息
		 */
		public function send_GetFighterBuyInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 21);
			var origParam_:SOrigParam_GetFighterBuyInfo = new SOrigParam_GetFighterBuyInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 21;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙购买
		 * @param wFighterID (无符号16位整数)将ID
		 */
		public function send_FighterBuy(wFighterID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 22);
			var origParam_:SOrigParam_FighterBuy = new SOrigParam_FighterBuy();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 22;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wFighterID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：装备技能返回
		private function _doRecv_SkillUpNotify(bytes:ByteArray):void
		{
			var dwSkillID:uint = bytes.readUnsignedInt(); //(无符号32位整数)技能ID
			var iSlot:int = bytes.readInt(); //(有符号32位整数)技能槽 -1表示卸下技能
			var event_:REvt_SkillUpNotify = new REvt_SkillUpNotify(REvt_SkillUpNotify.DATA_RECEIVE);
			event_.dwSkillID = dwSkillID;
			event_.iSlot = iSlot;
			dispatchEvent(event_);
		}

		//接收处理：增加新技能
		private function _doRecv_SkillAddNotify(bytes:ByteArray):void
		{
			var dwSkillID:uint = bytes.readUnsignedInt(); //(无符号32位整数)技能ID
			var event_:REvt_SkillAddNotify = new REvt_SkillAddNotify(REvt_SkillAddNotify.DATA_RECEIVE);
			event_.dwSkillID = dwSkillID;
			dispatchEvent(event_);
		}

		//接收处理：散仙血脉激活
		private function _doRecv_InstinctActiveNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)散仙唯一ID
			var vecInstinctIDRandom:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)血脉随机结果
			var vecInstinctIDRet:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)血脉最终结果
			var event_:REvt_InstinctActiveNotify = new REvt_InstinctActiveNotify(REvt_InstinctActiveNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.vecInstinctIDRandom = vecInstinctIDRandom;
			event_.vecInstinctIDRet = vecInstinctIDRet;
			dispatchEvent(event_);
		}

		//接收处理：招募散仙成功的弹框通知
		private function _doRecv_RecruitSuccNotify(bytes:ByteArray):void
		{
			var wFighterID:uint = bytes.readUnsignedShort(); //(无符号16位整数)散仙ID
			var event_:REvt_RecruitSuccNotify = new REvt_RecruitSuccNotify(REvt_RecruitSuccNotify.DATA_RECEIVE);
			event_.wFighterID = wFighterID;
			dispatchEvent(event_);
		}

		//接收处理：阵型位置变更
		private function _doRecv_FighterPosNotify(bytes:ByteArray):void
		{
			var vecPos:Vector.<SFighterPos> = SFighterPos.vectorFromByteArray(bytes); //阵型位置
			var event_:REvt_FighterPosNotify = new REvt_FighterPosNotify(REvt_FighterPosNotify.DATA_RECEIVE);
			event_.vecPos = vecPos;
			dispatchEvent(event_);
		}

		//接收处理：更新散仙的渡劫数据
		private function _doRecv_UpdateDujieValue(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将唯一ID
			var byDujieLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前渡劫等级
			var dwDujieExp:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前渡劫经验
			var dwSpiritPower:uint = bytes.readUnsignedInt(); //(无符号32位整数)元神力
			var event_:REvt_UpdateDujieValue = new REvt_UpdateDujieValue(REvt_UpdateDujieValue.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.byDujieLevel = byDujieLevel;
			event_.dwDujieExp = dwDujieExp;
			event_.dwSpiritPower = dwSpiritPower;
			dispatchEvent(event_);
		}

		//接收处理：心法数据更新通知
		private function _doRecv_XinFaNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将唯一ID
			var dwXinFaID:uint = bytes.readUnsignedInt(); //(无符号32位整数)心法ID
			var byXinFaLvl:uint = bytes.readUnsignedByte(); //(无符号8位整数)心法等级
			var iSlot:int = bytes.readInt(); //(有符号32位整数)心法槽 -1表示心法没装备
			var event_:REvt_XinFaNotify = new REvt_XinFaNotify(REvt_XinFaNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.dwXinFaID = dwXinFaID;
			event_.byXinFaLvl = byXinFaLvl;
			event_.iSlot = iSlot;
			dispatchEvent(event_);
		}

		//接收处理：散仙心法主卷等级满了添加一个天赋技能更新通知
		private function _doRecv_AddTalentSkillNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将唯一ID
			var byIdx:uint = bytes.readUnsignedByte(); //(无符号8位整数)技能槽idx
			var dwSkillID:uint = bytes.readUnsignedInt(); //(无符号32位整数)技能ID
			var event_:REvt_AddTalentSkillNotify = new REvt_AddTalentSkillNotify(REvt_AddTalentSkillNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.byIdx = byIdx;
			event_.dwSkillID = dwSkillID;
			dispatchEvent(event_);
		}

		//接收处理：散仙技能列表返回
		private function _doRecv_SkillListNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将唯一ID
			var VecFighterSkill:Vector.<SFighterSkill> = SFighterSkill.vectorFromByteArray(bytes); //技能ID
			var event_:REvt_SkillListNotify = new REvt_SkillListNotify(REvt_SkillListNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.VecFighterSkill = VecFighterSkill;
			dispatchEvent(event_);
		}

		//接收处理：玩家的散仙组合列表返回
		private function _doRecv_FighterCombinationNotify(bytes:ByteArray):void
		{
			var VecCombination:Vector.<SFighterCombination> = SFighterCombination.vectorFromByteArray(bytes); //散仙组合列表
			var event_:REvt_FighterCombinationNotify = new REvt_FighterCombinationNotify(REvt_FighterCombinationNotify.DATA_RECEIVE);
			event_.VecCombination = VecCombination;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：散仙装备主动技能
		private function _doReturn_FighterSkillEquipTo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterSkillEquipTo = new SRetParam_FighterSkillEquipTo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESkillResult)结果
			var vActiveSkill:Vector.<SFightSkillInfo> = SFightSkillInfo.vectorFromByteArray(bytes); //装备的主动技能
			retParam_.eResult = eResult;
			retParam_.vActiveSkill = vActiveSkill;
			var origParam_:SOrigParam_FighterSkillEquipTo = _sessionMgr.getData(sessionID_) as SOrigParam_FighterSkillEquipTo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterSkillEquipTo = new TEvt_FighterSkillEquipTo(TEvt_FighterSkillEquipTo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙装备主动技能
		private function _onTimeOut_FighterSkillEquipTo(sessionID:uint):void
		{
			var retParam:SRetParam_FighterSkillEquipTo = new SRetParam_FighterSkillEquipTo();
			var event_:TEvt_FighterSkillEquipTo = new TEvt_FighterSkillEquipTo(TEvt_FighterSkillEquipTo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙技能升级
		private function _doReturn_FighterSkillLevelUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterSkillLevelUp = new SRetParam_FighterSkillLevelUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESkillResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterSkillLevelUp = _sessionMgr.getData(sessionID_) as SOrigParam_FighterSkillLevelUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterSkillLevelUp = new TEvt_FighterSkillLevelUp(TEvt_FighterSkillLevelUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙技能升级
		private function _onTimeOut_FighterSkillLevelUp(sessionID:uint):void
		{
			var retParam:SRetParam_FighterSkillLevelUp = new SRetParam_FighterSkillLevelUp();
			var event_:TEvt_FighterSkillLevelUp = new TEvt_FighterSkillLevelUp(TEvt_FighterSkillLevelUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙被动技能升级
		private function _doReturn_FighterPassiveSkillLevelUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterPassiveSkillLevelUp = new SRetParam_FighterPassiveSkillLevelUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESkillResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterPassiveSkillLevelUp = _sessionMgr.getData(sessionID_) as SOrigParam_FighterPassiveSkillLevelUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterPassiveSkillLevelUp = new TEvt_FighterPassiveSkillLevelUp(TEvt_FighterPassiveSkillLevelUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙被动技能升级
		private function _onTimeOut_FighterPassiveSkillLevelUp(sessionID:uint):void
		{
			var retParam:SRetParam_FighterPassiveSkillLevelUp = new SRetParam_FighterPassiveSkillLevelUp();
			var event_:TEvt_FighterPassiveSkillLevelUp = new TEvt_FighterPassiveSkillLevelUp(TEvt_FighterPassiveSkillLevelUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取客栈信息
		private function _doReturn_GetTavernInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTavernInfo = new SRetParam_GetTavernInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwDrawCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)免费求签次数
			var vecTavernInfo:Vector.<STavernInfo> = STavernInfo.vectorFromByteArray(bytes); //具体客栈信息
			retParam_.dwDrawCount = dwDrawCount;
			retParam_.vecTavernInfo = vecTavernInfo;
			var origParam_:SOrigParam_GetTavernInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetTavernInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTavernInfo = new TEvt_GetTavernInfo(TEvt_GetTavernInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取客栈信息
		private function _onTimeOut_GetTavernInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetTavernInfo = new SRetParam_GetTavernInfo();
			var event_:TEvt_GetTavernInfo = new TEvt_GetTavernInfo(TEvt_GetTavernInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：求签
		private function _doReturn_Draw(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Draw = new SRetParam_Draw();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDrawResult)返回结果
			var vecItemGet:Vector.<SItemCount> = SItemCount.vectorFromByteArray(bytes); //求签获得物品
			retParam_.eResult = eResult;
			retParam_.vecItemGet = vecItemGet;
			var origParam_:SOrigParam_Draw = _sessionMgr.getData(sessionID_) as SOrigParam_Draw;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Draw = new TEvt_Draw(TEvt_Draw.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：求签
		private function _onTimeOut_Draw(sessionID:uint):void
		{
			var retParam:SRetParam_Draw = new SRetParam_Draw();
			var event_:TEvt_Draw = new TEvt_Draw(TEvt_Draw.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：招募
		private function _doReturn_FighterRecruit(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterRecruit = new SRetParam_FighterRecruit();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ERecruitResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterRecruit = _sessionMgr.getData(sessionID_) as SOrigParam_FighterRecruit;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterRecruit = new TEvt_FighterRecruit(TEvt_FighterRecruit.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：招募
		private function _onTimeOut_FighterRecruit(sessionID:uint):void
		{
			var retParam:SRetParam_FighterRecruit = new SRetParam_FighterRecruit();
			var event_:TEvt_FighterRecruit = new TEvt_FighterRecruit(TEvt_FighterRecruit.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：淬体升级
		private function _doReturn_CuiTiUpgrade(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CuiTiUpgrade = new SRetParam_CuiTiUpgrade();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECuiTiResult)结果
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前淬体等级
			retParam_.eResult = eResult;
			retParam_.byLevel = byLevel;
			var origParam_:SOrigParam_CuiTiUpgrade = _sessionMgr.getData(sessionID_) as SOrigParam_CuiTiUpgrade;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CuiTiUpgrade = new TEvt_CuiTiUpgrade(TEvt_CuiTiUpgrade.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：淬体升级
		private function _onTimeOut_CuiTiUpgrade(sessionID:uint):void
		{
			var retParam:SRetParam_CuiTiUpgrade = new SRetParam_CuiTiUpgrade();
			var event_:TEvt_CuiTiUpgrade = new TEvt_CuiTiUpgrade(TEvt_CuiTiUpgrade.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙淬体全体(六种)升级一次
		private function _doReturn_CuiTiAllUpgrade(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CuiTiAllUpgrade = new SRetParam_CuiTiAllUpgrade();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECuiTiResult)结果
			var vecLevel:Vector.<uint> = BytesUtil.readVecUByte(bytes); //(无符号8位整数)当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)
			retParam_.eResult = eResult;
			retParam_.vecLevel = vecLevel;
			var origParam_:SOrigParam_CuiTiAllUpgrade = _sessionMgr.getData(sessionID_) as SOrigParam_CuiTiAllUpgrade;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CuiTiAllUpgrade = new TEvt_CuiTiAllUpgrade(TEvt_CuiTiAllUpgrade.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙淬体全体(六种)升级一次
		private function _onTimeOut_CuiTiAllUpgrade(sessionID:uint):void
		{
			var retParam:SRetParam_CuiTiAllUpgrade = new SRetParam_CuiTiAllUpgrade();
			var event_:TEvt_CuiTiAllUpgrade = new TEvt_CuiTiAllUpgrade(TEvt_CuiTiAllUpgrade.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：转移
		private function _doReturn_FighterShift(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterShift = new SRetParam_FighterShift();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShiftResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterShift = _sessionMgr.getData(sessionID_) as SOrigParam_FighterShift;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterShift = new TEvt_FighterShift(TEvt_FighterShift.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：转移
		private function _onTimeOut_FighterShift(sessionID:uint):void
		{
			var retParam:SRetParam_FighterShift = new SRetParam_FighterShift();
			var event_:TEvt_FighterShift = new TEvt_FighterShift(TEvt_FighterShift.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：同步等级
		private function _doReturn_FighterSyncLevel(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterSyncLevel = new SRetParam_FighterSyncLevel();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESyncLevelResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterSyncLevel = _sessionMgr.getData(sessionID_) as SOrigParam_FighterSyncLevel;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterSyncLevel = new TEvt_FighterSyncLevel(TEvt_FighterSyncLevel.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：同步等级
		private function _onTimeOut_FighterSyncLevel(sessionID:uint):void
		{
			var retParam:SRetParam_FighterSyncLevel = new SRetParam_FighterSyncLevel();
			var event_:TEvt_FighterSyncLevel = new TEvt_FighterSyncLevel(TEvt_FighterSyncLevel.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：渡劫升级
		private function _doReturn_UpgradeDujie(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeDujie = new SRetParam_UpgradeDujie();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDujieResult)结果
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将唯一ID
			retParam_.eResult = eResult;
			retParam_.qwInstID = qwInstID;
			var origParam_:SOrigParam_UpgradeDujie = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeDujie;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeDujie = new TEvt_UpgradeDujie(TEvt_UpgradeDujie.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：渡劫升级
		private function _onTimeOut_UpgradeDujie(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeDujie = new SRetParam_UpgradeDujie();
			var event_:TEvt_UpgradeDujie = new TEvt_UpgradeDujie(TEvt_UpgradeDujie.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求散仙心法
		private function _doReturn_ReqFighterXinFaInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqFighterXinFaInfo = new SRetParam_ReqFighterXinFaInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFighterXinFa:Vector.<SXinFaInfo> = SXinFaInfo.vectorFromByteArray(bytes); //散仙已经学会的心法信息
			retParam_.vecFighterXinFa = vecFighterXinFa;
			var origParam_:SOrigParam_ReqFighterXinFaInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqFighterXinFaInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqFighterXinFaInfo = new TEvt_ReqFighterXinFaInfo(TEvt_ReqFighterXinFaInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求散仙心法
		private function _onTimeOut_ReqFighterXinFaInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqFighterXinFaInfo = new SRetParam_ReqFighterXinFaInfo();
			var event_:TEvt_ReqFighterXinFaInfo = new TEvt_ReqFighterXinFaInfo(TEvt_ReqFighterXinFaInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙学习心法
		private function _doReturn_FighterActiveXinFa(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterActiveXinFa = new SRetParam_FighterActiveXinFa();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EXinFaResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterActiveXinFa = _sessionMgr.getData(sessionID_) as SOrigParam_FighterActiveXinFa;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterActiveXinFa = new TEvt_FighterActiveXinFa(TEvt_FighterActiveXinFa.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙学习心法
		private function _onTimeOut_FighterActiveXinFa(sessionID:uint):void
		{
			var retParam:SRetParam_FighterActiveXinFa = new SRetParam_FighterActiveXinFa();
			var event_:TEvt_FighterActiveXinFa = new TEvt_FighterActiveXinFa(TEvt_FighterActiveXinFa.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙心法升级
		private function _doReturn_FighterXinFaLevelUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterXinFaLevelUp = new SRetParam_FighterXinFaLevelUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EXinFaResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterXinFaLevelUp = _sessionMgr.getData(sessionID_) as SOrigParam_FighterXinFaLevelUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterXinFaLevelUp = new TEvt_FighterXinFaLevelUp(TEvt_FighterXinFaLevelUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙心法升级
		private function _onTimeOut_FighterXinFaLevelUp(sessionID:uint):void
		{
			var retParam:SRetParam_FighterXinFaLevelUp = new SRetParam_FighterXinFaLevelUp();
			var event_:TEvt_FighterXinFaLevelUp = new TEvt_FighterXinFaLevelUp(TEvt_FighterXinFaLevelUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙心法散功
		private function _doReturn_FighterXinFaDisperse(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterXinFaDisperse = new SRetParam_FighterXinFaDisperse();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EXinFaResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterXinFaDisperse = _sessionMgr.getData(sessionID_) as SOrigParam_FighterXinFaDisperse;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterXinFaDisperse = new TEvt_FighterXinFaDisperse(TEvt_FighterXinFaDisperse.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙心法散功
		private function _onTimeOut_FighterXinFaDisperse(sessionID:uint):void
		{
			var retParam:SRetParam_FighterXinFaDisperse = new SRetParam_FighterXinFaDisperse();
			var event_:TEvt_FighterXinFaDisperse = new TEvt_FighterXinFaDisperse(TEvt_FighterXinFaDisperse.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取玩家的所有散仙组合
		private function _doReturn_GetAllFighterCombination(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllFighterCombination = new SRetParam_GetAllFighterCombination();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecCombinationInfo:Vector.<SFighterCombination> = SFighterCombination.vectorFromByteArray(bytes); //玩家的散仙组合信息
			retParam_.vecCombinationInfo = vecCombinationInfo;
			var origParam_:SOrigParam_GetAllFighterCombination = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllFighterCombination;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllFighterCombination = new TEvt_GetAllFighterCombination(TEvt_GetAllFighterCombination.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取玩家的所有散仙组合
		private function _onTimeOut_GetAllFighterCombination(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllFighterCombination = new SRetParam_GetAllFighterCombination();
			var event_:TEvt_GetAllFighterCombination = new TEvt_GetAllFighterCombination(TEvt_GetAllFighterCombination.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：激活散仙组合
		private function _doReturn_ActiveCombination(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ActiveCombination = new SRetParam_ActiveCombination();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECombinationResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ActiveCombination = _sessionMgr.getData(sessionID_) as SOrigParam_ActiveCombination;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ActiveCombination = new TEvt_ActiveCombination(TEvt_ActiveCombination.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：激活散仙组合
		private function _onTimeOut_ActiveCombination(sessionID:uint):void
		{
			var retParam:SRetParam_ActiveCombination = new SRetParam_ActiveCombination();
			var event_:TEvt_ActiveCombination = new TEvt_ActiveCombination(TEvt_ActiveCombination.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：升级散仙组合
		private function _doReturn_UpgradeCombination(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeCombination = new SRetParam_UpgradeCombination();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oCombinationInfo:SFighterCombination = SFighterCombination.fromByteArray(bytes); //当前升级的散仙组合信息
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECombinationResult)结果
			retParam_.oCombinationInfo = oCombinationInfo;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UpgradeCombination = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeCombination;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeCombination = new TEvt_UpgradeCombination(TEvt_UpgradeCombination.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：升级散仙组合
		private function _onTimeOut_UpgradeCombination(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeCombination = new SRetParam_UpgradeCombination();
			var event_:TEvt_UpgradeCombination = new TEvt_UpgradeCombination(TEvt_UpgradeCombination.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：装备散仙组合技能(连携技)
		private function _doReturn_EquipToCombinationSkill(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EquipToCombinationSkill = new SRetParam_EquipToCombinationSkill();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECombinationResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_EquipToCombinationSkill = _sessionMgr.getData(sessionID_) as SOrigParam_EquipToCombinationSkill;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EquipToCombinationSkill = new TEvt_EquipToCombinationSkill(TEvt_EquipToCombinationSkill.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：装备散仙组合技能(连携技)
		private function _onTimeOut_EquipToCombinationSkill(sessionID:uint):void
		{
			var retParam:SRetParam_EquipToCombinationSkill = new SRetParam_EquipToCombinationSkill();
			var event_:TEvt_EquipToCombinationSkill = new TEvt_EquipToCombinationSkill(TEvt_EquipToCombinationSkill.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙散功
		private function _doReturn_FighterDismiss(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterDismiss = new SRetParam_FighterDismiss();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDismissResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterDismiss = _sessionMgr.getData(sessionID_) as SOrigParam_FighterDismiss;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterDismiss = new TEvt_FighterDismiss(TEvt_FighterDismiss.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙散功
		private function _onTimeOut_FighterDismiss(sessionID:uint):void
		{
			var retParam:SRetParam_FighterDismiss = new SRetParam_FighterDismiss();
			var event_:TEvt_FighterDismiss = new TEvt_FighterDismiss(TEvt_FighterDismiss.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取购买散仙信息
		private function _doReturn_GetFighterBuyInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFighterBuyInfo = new SRetParam_GetFighterBuyInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFighterBuyInfo:Vector.<SFighterBuyInfo> = SFighterBuyInfo.vectorFromByteArray(bytes); //购买散仙信息
			retParam_.vecFighterBuyInfo = vecFighterBuyInfo;
			var origParam_:SOrigParam_GetFighterBuyInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetFighterBuyInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFighterBuyInfo = new TEvt_GetFighterBuyInfo(TEvt_GetFighterBuyInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取购买散仙信息
		private function _onTimeOut_GetFighterBuyInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetFighterBuyInfo = new SRetParam_GetFighterBuyInfo();
			var event_:TEvt_GetFighterBuyInfo = new TEvt_GetFighterBuyInfo(TEvt_GetFighterBuyInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙购买
		private function _doReturn_FighterBuy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterBuy = new SRetParam_FighterBuy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFighterBuyResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterBuy = _sessionMgr.getData(sessionID_) as SOrigParam_FighterBuy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterBuy = new TEvt_FighterBuy(TEvt_FighterBuy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙购买
		private function _onTimeOut_FighterBuy(sessionID:uint):void
		{
			var retParam:SRetParam_FighterBuy = new SRetParam_FighterBuy();
			var event_:TEvt_FighterBuy = new TEvt_FighterBuy(TEvt_FighterBuy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:FighterProt;

		public static function get instance():FighterProt
		{
			if(_instance == null)
				_instance = new FighterProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function FighterProt()
		{
			_protID = 20;
			_recvFuncList = [
				_doRecv_SkillUpNotify, //FuncID: 1
				_doRecv_SkillAddNotify, //FuncID: 2
				_doRecv_InstinctActiveNotify, //FuncID: 3
				_doRecv_RecruitSuccNotify, //FuncID: 4
				_doRecv_FighterPosNotify, //FuncID: 5
				_doRecv_UpdateDujieValue, //FuncID: 6
				_doRecv_XinFaNotify, //FuncID: 7
				_doRecv_AddTalentSkillNotify, //FuncID: 8
				_doRecv_SkillListNotify, //FuncID: 9
				_doRecv_FighterCombinationNotify //FuncID: 10
			];

			_retFuncList = [
				_doReturn_FighterSkillEquipTo, //FuncID: 1
				_doReturn_FighterSkillLevelUp, //FuncID: 2
				_doReturn_FighterPassiveSkillLevelUp, //FuncID: 3
				_doReturn_GetTavernInfo, //FuncID: 4
				_doReturn_Draw, //FuncID: 5
				_doReturn_FighterRecruit, //FuncID: 6
				_doReturn_CuiTiUpgrade, //FuncID: 7
				_doReturn_CuiTiAllUpgrade, //FuncID: 8
				_doReturn_FighterShift, //FuncID: 9
				_doReturn_FighterSyncLevel, //FuncID: 10
				_doReturn_UpgradeDujie, //FuncID: 11
				_doReturn_ReqFighterXinFaInfo, //FuncID: 12
				_doReturn_FighterActiveXinFa, //FuncID: 13
				_doReturn_FighterXinFaLevelUp, //FuncID: 14
				_doReturn_FighterXinFaDisperse, //FuncID: 15
				_doReturn_GetAllFighterCombination, //FuncID: 16
				_doReturn_ActiveCombination, //FuncID: 17
				_doReturn_UpgradeCombination, //FuncID: 18
				_doReturn_EquipToCombinationSkill, //FuncID: 19
				_doReturn_FighterDismiss, //FuncID: 20
				_doReturn_GetFighterBuyInfo, //FuncID: 21
				_doReturn_FighterBuy //FuncID: 22
			];

			_timeFuncList = [
				_onTimeOut_FighterSkillEquipTo, //FuncID: 1
				_onTimeOut_FighterSkillLevelUp, //FuncID: 2
				_onTimeOut_FighterPassiveSkillLevelUp, //FuncID: 3
				_onTimeOut_GetTavernInfo, //FuncID: 4
				_onTimeOut_Draw, //FuncID: 5
				_onTimeOut_FighterRecruit, //FuncID: 6
				_onTimeOut_CuiTiUpgrade, //FuncID: 7
				_onTimeOut_CuiTiAllUpgrade, //FuncID: 8
				_onTimeOut_FighterShift, //FuncID: 9
				_onTimeOut_FighterSyncLevel, //FuncID: 10
				_onTimeOut_UpgradeDujie, //FuncID: 11
				_onTimeOut_ReqFighterXinFaInfo, //FuncID: 12
				_onTimeOut_FighterActiveXinFa, //FuncID: 13
				_onTimeOut_FighterXinFaLevelUp, //FuncID: 14
				_onTimeOut_FighterXinFaDisperse, //FuncID: 15
				_onTimeOut_GetAllFighterCombination, //FuncID: 16
				_onTimeOut_ActiveCombination, //FuncID: 17
				_onTimeOut_UpgradeCombination, //FuncID: 18
				_onTimeOut_EquipToCombinationSkill, //FuncID: 19
				_onTimeOut_FighterDismiss, //FuncID: 20
				_onTimeOut_GetFighterBuyInfo, //FuncID: 21
				_onTimeOut_FighterBuy //FuncID: 22
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