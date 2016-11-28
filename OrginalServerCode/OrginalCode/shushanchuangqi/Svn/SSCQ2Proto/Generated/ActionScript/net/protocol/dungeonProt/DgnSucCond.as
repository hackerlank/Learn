/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    DgnSucCond.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 副本条件
	 */
	public class DgnSucCond
	{
		public var wCondId:uint; //(无符号16位整数)条件ID
		public var eStatus:uint; //(枚举类型：EDgnCondStatus)0,未达成，1表示已达成，2表示已失败

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_DgnSucCond.eType_DgnSucCond;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <DgnSucCond _name_={name_} wCondId={wCondId} eStatus={eStatus}/>;
			else
				topXml = <DgnSucCond wCondId={wCondId} eStatus={eStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wCondId = wCondId;
			obj_.eStatus = eStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):DgnSucCond
		{
			var s_:DgnSucCond = new DgnSucCond();
			var wCondId:uint = bytes.readUnsignedShort();
			s_.wCondId = wCondId;
			var eStatus:uint = bytes.readUnsignedByte();
			s_.eStatus = eStatus;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):DgnSucCond
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:DgnSucCond;
			switch(eType)
			{
				case EType_DgnSucCond.eType_DgnSucCond:
					s = DgnSucCond.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucMonster:
					s = SucMonster.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucGather:
					s = SucGather.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucTurns:
					s = SucTurns.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucInTimer:
					s = SucInTimer.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucMonsterInTimer:
					s = SucMonsterInTimer.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucGatherInTimer:
					s = SucGatherInTimer.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucFightWithMonsterMinTimes:
					s = SucFightWithMonsterMinTimes.fromByteArray(bytes);
					break;
				case EType_DgnSucCond.eType_SucArriveArea:
					s = SucArriveArea.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_DgnSucCond:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<DgnSucCond>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<DgnSucCond> = new Vector.<DgnSucCond>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:DgnSucCond = DgnSucCond.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<DgnSucCond>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<DgnSucCond> = new Vector.<DgnSucCond>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:DgnSucCond = DgnSucCond.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wCondId);
			bytes.writeByte(eStatus);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<DgnSucCond>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:DgnSucCond in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<DgnSucCond>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:DgnSucCond in vec)
				s.superToByteArray(bytes);
		}
	}
}
