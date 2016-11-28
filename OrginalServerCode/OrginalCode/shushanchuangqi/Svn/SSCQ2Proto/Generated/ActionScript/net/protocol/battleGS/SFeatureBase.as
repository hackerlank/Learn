/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFeatureBase.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 外观信息
	 */
	public class SFeatureBase
	{
		public var vecBuffID:Vector.<uint>; //(无符号16位整数)BUffID信息

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SFeatureBase.eType_SFeatureBase;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SFeatureBase _name_={name_}/>;
			else
				topXml = <SFeatureBase/>;
			if(vecBuffID != null)
			{
				var vecBuffIDXml:XML = <Vec_UINT16 _name_="vecBuffID"/>;
				var text1:String = "";
				for each(var value1:uint in vecBuffID)
					text1 += "[" + value1 + "]";
				vecBuffIDXml.appendChild(text1);
				topXml.appendChild(vecBuffIDXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecBuffID = vecBuffID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFeatureBase
		{
			var s_:SFeatureBase = new SFeatureBase();
			var vecBuffID:Vector.<uint> = BytesUtil.readVecUShort(bytes);
			s_.vecBuffID = vecBuffID;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SFeatureBase
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SFeatureBase;
			switch(eType)
			{
				case EType_SFeatureBase.eType_SFeatureBase:
					s = SFeatureBase.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SMonsterFeature:
					s = SMonsterFeature.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SPlayerFeature:
					s = SPlayerFeature.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SHeroFeature:
					s = SHeroFeature.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SFormationFeature:
					s = SFormationFeature.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SFieldFeature:
					s = SFieldFeature.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SBeautyFeature:
					s = SBeautyFeature.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SPlayerFeatureWithBuff:
					s = SPlayerFeatureWithBuff.fromByteArray(bytes);
					break;
				case EType_SFeatureBase.eType_SMonsterFeatureWithBuff:
					s = SMonsterFeatureWithBuff.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SFeatureBase:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFeatureBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFeatureBase> = new Vector.<SFeatureBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFeatureBase = SFeatureBase.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SFeatureBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFeatureBase> = new Vector.<SFeatureBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFeatureBase = SFeatureBase.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeVecUShort(bytes, vecBuffID);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFeatureBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFeatureBase in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SFeatureBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFeatureBase in vec)
				s.superToByteArray(bytes);
		}
	}
}
