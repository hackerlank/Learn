/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STruckInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 羲和神车的货号信息
	 */
	public final class STruckInfo
	{
		public var byTruckID:uint; //(无符号8位整数)货号id
		public var byStatus:uint; //(无符号8位整数)EXiheTaskStatus货号状态(0未完成装货 1已请求帮助 2已完成装货)
		public var byPos:uint; //(无符号8位整数)货物顺序索引(0~7)
		public var strName:String; //status为3时,完成装货的玩家名字(注:自己完成为空,不存储)
		public var byColor:uint; //(无符号8位整数)帮助者玩家颜色

		/**
		 * 辅助创建函数
		 */
		public static function create(byTruckID:uint, byStatus:uint, byPos:uint, strName:String, byColor:uint):STruckInfo
		{
			var s_:STruckInfo = new STruckInfo();
			s_.byTruckID = byTruckID;
			s_.byStatus = byStatus;
			s_.byPos = byPos;
			s_.strName = strName;
			s_.byColor = byColor;
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
				topXml = <STruckInfo _name_={name_} byTruckID={byTruckID} byStatus={byStatus} byPos={byPos} strName={strName} byColor={byColor}/>;
			else
				topXml = <STruckInfo byTruckID={byTruckID} byStatus={byStatus} byPos={byPos} strName={strName} byColor={byColor}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byTruckID = byTruckID;
			obj_.byStatus = byStatus;
			obj_.byPos = byPos;
			obj_.strName = strName;
			obj_.byColor = byColor;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STruckInfo
		{
			var s_:STruckInfo = new STruckInfo();
			var byTruckID:uint = bytes.readUnsignedByte();
			s_.byTruckID = byTruckID;
			var byStatus:uint = bytes.readUnsignedByte();
			s_.byStatus = byStatus;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STruckInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STruckInfo> = new Vector.<STruckInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STruckInfo = STruckInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byTruckID);
			bytes.writeByte(byStatus);
			bytes.writeByte(byPos);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byColor);
		}

		public static function vectorToByteArray(vec:Vector.<STruckInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STruckInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
