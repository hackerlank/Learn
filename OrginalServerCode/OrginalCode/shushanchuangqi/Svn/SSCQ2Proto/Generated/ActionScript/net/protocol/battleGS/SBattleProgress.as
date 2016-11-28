/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleProgress.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 某个fighter一次出手
	 */
	public final class SBattleProgress
	{
		public var vecCasterIndex:Vector.<uint>; //(无符号8位整数)主犯(255代表入场技能或者场景技能
		public var vEffectsBefore:Vector.<SEffectBase>; //主犯施法前的效果列表
		public var dwSkillID:uint; //(无符号32位整数)技能ID
		public var vTargetID:Vector.<uint>; //(无符号8位整数)所有目标ID
		public var vTargetIDEx:Vector.<uint>; //(无符号8位整数)波及目标ID
		public var vTargetPos:Vector.<SBattleTargetPos>; //技能主执行覆盖区域位置
		public var vSkillEffects:Vector.<SEffectBase>; //技能效果列表
		public var vEffectsAfter:Vector.<SEffectBase>; //主犯施法后效果列表

		/**
		 * 辅助创建函数
		 */
		public static function create(vecCasterIndex:Vector.<uint>, vEffectsBefore:Vector.<SEffectBase>, dwSkillID:uint, vTargetID:Vector.<uint>, vTargetIDEx:Vector.<uint>, 
			vTargetPos:Vector.<SBattleTargetPos>, vSkillEffects:Vector.<SEffectBase>, vEffectsAfter:Vector.<SEffectBase>):SBattleProgress
		{
			var s_:SBattleProgress = new SBattleProgress();
			s_.vecCasterIndex = vecCasterIndex;
			s_.vEffectsBefore = vEffectsBefore;
			s_.dwSkillID = dwSkillID;
			s_.vTargetID = vTargetID;
			s_.vTargetIDEx = vTargetIDEx;
			s_.vTargetPos = vTargetPos;
			s_.vSkillEffects = vSkillEffects;
			s_.vEffectsAfter = vEffectsAfter;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SBattleProgress _name_={name_} dwSkillID={dwSkillID}/>;
			else
				topXml = <SBattleProgress dwSkillID={dwSkillID}/>;
			if(vecCasterIndex != null)
			{
				var vecCasterIndexXml:XML = <Vec_UINT8 _name_="vecCasterIndex"/>;
				var text1:String = "";
				for each(var value1:uint in vecCasterIndex)
					text1 += "[" + value1 + "]";
				vecCasterIndexXml.appendChild(text1);
				topXml.appendChild(vecCasterIndexXml);
			}
			if(vEffectsBefore != null)
			{
				var vEffectsBeforeXml:XML = <Vec_SEffectBase _name_="vEffectsBefore"/>;
				for each(var s2:SEffectBase in vEffectsBefore)
					vEffectsBeforeXml.appendChild(s2.toXML());
				topXml.appendChild(vEffectsBeforeXml);
			}
			if(vTargetID != null)
			{
				var vTargetIDXml:XML = <Vec_UINT8 _name_="vTargetID"/>;
				var text3:String = "";
				for each(var value3:uint in vTargetID)
					text3 += "[" + value3 + "]";
				vTargetIDXml.appendChild(text3);
				topXml.appendChild(vTargetIDXml);
			}
			if(vTargetIDEx != null)
			{
				var vTargetIDExXml:XML = <Vec_UINT8 _name_="vTargetIDEx"/>;
				var text4:String = "";
				for each(var value4:uint in vTargetIDEx)
					text4 += "[" + value4 + "]";
				vTargetIDExXml.appendChild(text4);
				topXml.appendChild(vTargetIDExXml);
			}
			if(vTargetPos != null)
			{
				var vTargetPosXml:XML = <Vec_SBattleTargetPos _name_="vTargetPos"/>;
				for each(var s5:SBattleTargetPos in vTargetPos)
					vTargetPosXml.appendChild(s5.toXML());
				topXml.appendChild(vTargetPosXml);
			}
			if(vSkillEffects != null)
			{
				var vSkillEffectsXml:XML = <Vec_SEffectBase _name_="vSkillEffects"/>;
				for each(var s6:SEffectBase in vSkillEffects)
					vSkillEffectsXml.appendChild(s6.toXML());
				topXml.appendChild(vSkillEffectsXml);
			}
			if(vEffectsAfter != null)
			{
				var vEffectsAfterXml:XML = <Vec_SEffectBase _name_="vEffectsAfter"/>;
				for each(var s7:SEffectBase in vEffectsAfter)
					vEffectsAfterXml.appendChild(s7.toXML());
				topXml.appendChild(vEffectsAfterXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecCasterIndex = vecCasterIndex;
			obj_.vEffectsBefore = vEffectsBefore;
			obj_.dwSkillID = dwSkillID;
			obj_.vTargetID = vTargetID;
			obj_.vTargetIDEx = vTargetIDEx;
			obj_.vTargetPos = vTargetPos;
			obj_.vSkillEffects = vSkillEffects;
			obj_.vEffectsAfter = vEffectsAfter;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleProgress
		{
			var s_:SBattleProgress = new SBattleProgress();
			var vecCasterIndex:Vector.<uint> = BytesUtil.readVecUByte(bytes);
			s_.vecCasterIndex = vecCasterIndex;
			var vEffectsBefore:Vector.<SEffectBase> = SEffectBase.superVectorFromByteArray(bytes);
			s_.vEffectsBefore = vEffectsBefore;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var vTargetID:Vector.<uint> = BytesUtil.readVecUByte(bytes);
			s_.vTargetID = vTargetID;
			var vTargetIDEx:Vector.<uint> = BytesUtil.readVecUByte(bytes);
			s_.vTargetIDEx = vTargetIDEx;
			var vTargetPos:Vector.<SBattleTargetPos> = SBattleTargetPos.vectorFromByteArray(bytes);
			s_.vTargetPos = vTargetPos;
			var vSkillEffects:Vector.<SEffectBase> = SEffectBase.superVectorFromByteArray(bytes);
			s_.vSkillEffects = vSkillEffects;
			var vEffectsAfter:Vector.<SEffectBase> = SEffectBase.superVectorFromByteArray(bytes);
			s_.vEffectsAfter = vEffectsAfter;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleProgress>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleProgress> = new Vector.<SBattleProgress>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleProgress = SBattleProgress.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeVecUByte(bytes, vecCasterIndex);
			SEffectBase.superVectorToByteArray(vEffectsBefore, bytes);
			bytes.writeUnsignedInt(dwSkillID);
			BytesUtil.writeVecUByte(bytes, vTargetID);
			BytesUtil.writeVecUByte(bytes, vTargetIDEx);
			SBattleTargetPos.vectorToByteArray(vTargetPos, bytes);
			SEffectBase.superVectorToByteArray(vSkillEffects, bytes);
			SEffectBase.superVectorToByteArray(vEffectsAfter, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleProgress>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleProgress in vec)
				s.toByteArray(bytes);
		}
	}
}
