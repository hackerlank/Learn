/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectBase.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗基础效果类型
	 */
	public class SEffectBase
	{
		public var vecFighterID:Vector.<uint>; //(无符号8位整数)表现这个效果的fighter(255表示为场景)

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectBase;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectBase _name_={name_}/>;
			else
				topXml = <SEffectBase/>;
			if(vecFighterID != null)
			{
				var vecFighterIDXml:XML = <Vec_UINT8 _name_="vecFighterID"/>;
				var text1:String = "";
				for each(var value1:uint in vecFighterID)
					text1 += "[" + value1 + "]";
				vecFighterIDXml.appendChild(text1);
				topXml.appendChild(vecFighterIDXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecFighterID = vecFighterID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectBase
		{
			var s_:SEffectBase = new SEffectBase();
			var vecFighterID:Vector.<uint> = BytesUtil.readVecUByte(bytes);
			s_.vecFighterID = vecFighterID;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SEffectBase
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SEffectBase;
			switch(eType)
			{
				case EType_SEffectBase.eType_SEffectBase:
					s = SEffectBase.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectDecHP:
					s = SEffectDecHP.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectAddStatus:
					s = SEffectAddStatus.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectAddHP:
					s = SEffectAddHP.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectRelive:
					s = SEffectRelive.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectCounter:
					s = SEffectCounter.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectStateBuffAdd:
					s = SEffectStateBuffAdd.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectStateBuffEffect:
					s = SEffectStateBuffEffect.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectStateBuffDec:
					s = SEffectStateBuffDec.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectStateBuffLast:
					s = SEffectStateBuffLast.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectAttrBuffAdd:
					s = SEffectAttrBuffAdd.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectAttrBuffDec:
					s = SEffectAttrBuffDec.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectDied:
					s = SEffectDied.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectShieldAbsorb:
					s = SEffectShieldAbsorb.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectTriggerExecute:
					s = SEffectTriggerExecute.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectSycHP:
					s = SEffectSycHP.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectSycAura:
					s = SEffectSycAura.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectSycCombine:
					s = SEffectSycCombine.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectCombineSlot:
					s = SEffectCombineSlot.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectBrokenShield:
					s = SEffectBrokenShield.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectSummon:
					s = SEffectSummon.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectDialog:
					s = SEffectDialog.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectTransform:
					s = SEffectTransform.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectPartBroken:
					s = SEffectPartBroken.fromByteArray(bytes);
					break;
				case EType_SEffectBase.eType_SEffectBuffAction:
					s = SEffectBuffAction.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SEffectBase:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectBase> = new Vector.<SEffectBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectBase = SEffectBase.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SEffectBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectBase> = new Vector.<SEffectBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectBase = SEffectBase.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeVecUByte(bytes, vecFighterID);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectBase in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SEffectBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectBase in vec)
				s.superToByteArray(bytes);
		}
	}
}
