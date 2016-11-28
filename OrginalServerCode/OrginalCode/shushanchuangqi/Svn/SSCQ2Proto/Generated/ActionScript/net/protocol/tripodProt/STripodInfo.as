/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STripodInfo.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家的九疑鼎数据
	 */
	public final class STripodInfo
	{
		public var byTripodID:uint; //(无符号8位整数)九疑鼎ID
		public var byLevel:uint; //(无符号8位整数)九疑鼎等级
		public var dwExp:uint; //(无符号32位整数)九疑鼎当前经验值
		public var wFireID:uint; //(无符号16位整数)火种ID
		public var byFireLvl:uint; //(无符号8位整数)火种等级(品质)
		public var dwStartTime:uint; //(无符号32位整数)上一次结算时间
		public var dwShanfengTime:uint; //(无符号32位整数)上一次扇风时间(为0未扇风)
		public var dwSoul:uint; //(无符号32位整数)当前已结算的总元气值
		public var dwLine:uint; //(无符号32位整数)产物加成系数（万分比）

		/**
		 * 辅助创建函数
		 */
		public static function create(byTripodID:uint, byLevel:uint, dwExp:uint, wFireID:uint, byFireLvl:uint, 
			dwStartTime:uint, dwShanfengTime:uint, dwSoul:uint, dwLine:uint):STripodInfo
		{
			var s_:STripodInfo = new STripodInfo();
			s_.byTripodID = byTripodID;
			s_.byLevel = byLevel;
			s_.dwExp = dwExp;
			s_.wFireID = wFireID;
			s_.byFireLvl = byFireLvl;
			s_.dwStartTime = dwStartTime;
			s_.dwShanfengTime = dwShanfengTime;
			s_.dwSoul = dwSoul;
			s_.dwLine = dwLine;
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
				topXml = <STripodInfo _name_={name_} byTripodID={byTripodID} byLevel={byLevel} dwExp={dwExp} wFireID={wFireID} byFireLvl={byFireLvl}
				 dwStartTime={dwStartTime} dwShanfengTime={dwShanfengTime} dwSoul={dwSoul} dwLine={dwLine}/>;
			else
				topXml = <STripodInfo byTripodID={byTripodID} byLevel={byLevel} dwExp={dwExp} wFireID={wFireID} byFireLvl={byFireLvl}
				 dwStartTime={dwStartTime} dwShanfengTime={dwShanfengTime} dwSoul={dwSoul} dwLine={dwLine}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byTripodID = byTripodID;
			obj_.byLevel = byLevel;
			obj_.dwExp = dwExp;
			obj_.wFireID = wFireID;
			obj_.byFireLvl = byFireLvl;
			obj_.dwStartTime = dwStartTime;
			obj_.dwShanfengTime = dwShanfengTime;
			obj_.dwSoul = dwSoul;
			obj_.dwLine = dwLine;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STripodInfo
		{
			var s_:STripodInfo = new STripodInfo();
			var byTripodID:uint = bytes.readUnsignedByte();
			s_.byTripodID = byTripodID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var wFireID:uint = bytes.readUnsignedShort();
			s_.wFireID = wFireID;
			var byFireLvl:uint = bytes.readUnsignedByte();
			s_.byFireLvl = byFireLvl;
			var dwStartTime:uint = bytes.readUnsignedInt();
			s_.dwStartTime = dwStartTime;
			var dwShanfengTime:uint = bytes.readUnsignedInt();
			s_.dwShanfengTime = dwShanfengTime;
			var dwSoul:uint = bytes.readUnsignedInt();
			s_.dwSoul = dwSoul;
			var dwLine:uint = bytes.readUnsignedInt();
			s_.dwLine = dwLine;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STripodInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STripodInfo> = new Vector.<STripodInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STripodInfo = STripodInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byTripodID);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwExp);
			bytes.writeShort(wFireID);
			bytes.writeByte(byFireLvl);
			bytes.writeUnsignedInt(dwStartTime);
			bytes.writeUnsignedInt(dwShanfengTime);
			bytes.writeUnsignedInt(dwSoul);
			bytes.writeUnsignedInt(dwLine);
		}

		public static function vectorToByteArray(vec:Vector.<STripodInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STripodInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
