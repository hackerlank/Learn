/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    PlayerShipForList.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 列表信息
	 */
	public final class PlayerShipForList
	{
		public var qwInsID:BigInteger; //(无符号64位整数)金船唯一ID
		public var qwOwer:BigInteger; //(无符号64位整数)金船拥有者
		public var wShipId:uint; //(无符号16位整数)船模板
		public var byChannel:uint; //(无符号8位整数)航道
		public var dwBeginTimer:uint; //(无符号32位整数)开船时间
		public var dwEndTimer:uint; //(无符号32位整数)结束时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInsID:BigInteger, qwOwer:BigInteger, wShipId:uint, byChannel:uint, dwBeginTimer:uint, 
			dwEndTimer:uint):PlayerShipForList
		{
			var s_:PlayerShipForList = new PlayerShipForList();
			s_.qwInsID = qwInsID;
			s_.qwOwer = qwOwer;
			s_.wShipId = wShipId;
			s_.byChannel = byChannel;
			s_.dwBeginTimer = dwBeginTimer;
			s_.dwEndTimer = dwEndTimer;
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
				topXml = <PlayerShipForList _name_={name_} qwInsID={qwInsID} qwOwer={qwOwer} wShipId={wShipId} byChannel={byChannel} dwBeginTimer={dwBeginTimer}
				 dwEndTimer={dwEndTimer}/>;
			else
				topXml = <PlayerShipForList qwInsID={qwInsID} qwOwer={qwOwer} wShipId={wShipId} byChannel={byChannel} dwBeginTimer={dwBeginTimer}
				 dwEndTimer={dwEndTimer}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInsID = qwInsID;
			obj_.qwOwer = qwOwer;
			obj_.wShipId = wShipId;
			obj_.byChannel = byChannel;
			obj_.dwBeginTimer = dwBeginTimer;
			obj_.dwEndTimer = dwEndTimer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):PlayerShipForList
		{
			var s_:PlayerShipForList = new PlayerShipForList();
			var qwInsID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInsID = qwInsID;
			var qwOwer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwer = qwOwer;
			var wShipId:uint = bytes.readUnsignedShort();
			s_.wShipId = wShipId;
			var byChannel:uint = bytes.readUnsignedByte();
			s_.byChannel = byChannel;
			var dwBeginTimer:uint = bytes.readUnsignedInt();
			s_.dwBeginTimer = dwBeginTimer;
			var dwEndTimer:uint = bytes.readUnsignedInt();
			s_.dwEndTimer = dwEndTimer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<PlayerShipForList>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<PlayerShipForList> = new Vector.<PlayerShipForList>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:PlayerShipForList = PlayerShipForList.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInsID);
			BytesUtil.writeUInt64(bytes, qwOwer);
			bytes.writeShort(wShipId);
			bytes.writeByte(byChannel);
			bytes.writeUnsignedInt(dwBeginTimer);
			bytes.writeUnsignedInt(dwEndTimer);
		}

		public static function vectorToByteArray(vec:Vector.<PlayerShipForList>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:PlayerShipForList in vec)
				s.toByteArray(bytes);
		}
	}
}
