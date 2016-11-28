/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActivityOpt.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活动中心数据库记录
	 */
	public final class SActivityOpt
	{
		public var dwActID:uint; //(无符号32位整数)活动ID
		public var byIndex:uint; //(无符号8位整数)场次
		public var strName:String; //活动名字
		public var dwSync:uint; //(无符号32位整数)活动时间 同步
		public var dwAlarm:uint; //(无符号32位整数)活动公告时间
		public var dwReady:uint; //(无符号32位整数)活动准备时间
		public var dwBegin:uint; //(无符号32位整数)活动开始时间
		public var dwEnd:uint; //(无符号32位整数)活动结束时间
		public var bSync:Boolean; //是否同步Game
		public var dwOptTime:uint; //(无符号32位整数)操作时间

		/**
		 * 辅助创建函数
		 */
		public static function create(dwActID:uint, byIndex:uint, strName:String, dwSync:uint, dwAlarm:uint, 
			dwReady:uint, dwBegin:uint, dwEnd:uint, bSync:Boolean, dwOptTime:uint):SActivityOpt
		{
			var s_:SActivityOpt = new SActivityOpt();
			s_.dwActID = dwActID;
			s_.byIndex = byIndex;
			s_.strName = strName;
			s_.dwSync = dwSync;
			s_.dwAlarm = dwAlarm;
			s_.dwReady = dwReady;
			s_.dwBegin = dwBegin;
			s_.dwEnd = dwEnd;
			s_.bSync = bSync;
			s_.dwOptTime = dwOptTime;
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
				topXml = <SActivityOpt _name_={name_} dwActID={dwActID} byIndex={byIndex} strName={strName} dwSync={dwSync} dwAlarm={dwAlarm}
				 dwReady={dwReady} dwBegin={dwBegin} dwEnd={dwEnd} bSync={bSync} dwOptTime={dwOptTime}/>;
			else
				topXml = <SActivityOpt dwActID={dwActID} byIndex={byIndex} strName={strName} dwSync={dwSync} dwAlarm={dwAlarm}
				 dwReady={dwReady} dwBegin={dwBegin} dwEnd={dwEnd} bSync={bSync} dwOptTime={dwOptTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwActID = dwActID;
			obj_.byIndex = byIndex;
			obj_.strName = strName;
			obj_.dwSync = dwSync;
			obj_.dwAlarm = dwAlarm;
			obj_.dwReady = dwReady;
			obj_.dwBegin = dwBegin;
			obj_.dwEnd = dwEnd;
			obj_.bSync = bSync;
			obj_.dwOptTime = dwOptTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActivityOpt
		{
			var s_:SActivityOpt = new SActivityOpt();
			var dwActID:uint = bytes.readUnsignedInt();
			s_.dwActID = dwActID;
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwSync:uint = bytes.readUnsignedInt();
			s_.dwSync = dwSync;
			var dwAlarm:uint = bytes.readUnsignedInt();
			s_.dwAlarm = dwAlarm;
			var dwReady:uint = bytes.readUnsignedInt();
			s_.dwReady = dwReady;
			var dwBegin:uint = bytes.readUnsignedInt();
			s_.dwBegin = dwBegin;
			var dwEnd:uint = bytes.readUnsignedInt();
			s_.dwEnd = dwEnd;
			var bSync:Boolean = bytes.readBoolean();
			s_.bSync = bSync;
			var dwOptTime:uint = bytes.readUnsignedInt();
			s_.dwOptTime = dwOptTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActivityOpt>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActivityOpt> = new Vector.<SActivityOpt>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActivityOpt = SActivityOpt.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwActID);
			bytes.writeByte(byIndex);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwSync);
			bytes.writeUnsignedInt(dwAlarm);
			bytes.writeUnsignedInt(dwReady);
			bytes.writeUnsignedInt(dwBegin);
			bytes.writeUnsignedInt(dwEnd);
			bytes.writeBoolean(bSync);
			bytes.writeUnsignedInt(dwOptTime);
		}

		public static function vectorToByteArray(vec:Vector.<SActivityOpt>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActivityOpt in vec)
				s.toByteArray(bytes);
		}
	}
}
