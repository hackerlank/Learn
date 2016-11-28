/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSweepItem.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.itemProt.SResource;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 扫荡日志信息
	 */
	public final class SSweepItem
	{
		public var wTurn:uint; //(无符号16位整数)当前扫荡轮数
		public var vecItemGenInfo:Vector.<SItemGenInfo>; //获得物品
		public var vecResource:Vector.<SResource>; //获得资源

		/**
		 * 辅助创建函数
		 */
		public static function create(wTurn:uint, vecItemGenInfo:Vector.<SItemGenInfo>, vecResource:Vector.<SResource>):SSweepItem
		{
			var s_:SSweepItem = new SSweepItem();
			s_.wTurn = wTurn;
			s_.vecItemGenInfo = vecItemGenInfo;
			s_.vecResource = vecResource;
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
				topXml = <SSweepItem _name_={name_} wTurn={wTurn}/>;
			else
				topXml = <SSweepItem wTurn={wTurn}/>;
			if(vecItemGenInfo != null)
			{
				var vecItemGenInfoXml:XML = <Vec_SItemGenInfo _name_="vecItemGenInfo"/>;
				for each(var s1:SItemGenInfo in vecItemGenInfo)
					vecItemGenInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemGenInfoXml);
			}
			if(vecResource != null)
			{
				var vecResourceXml:XML = <Vec_SResource _name_="vecResource"/>;
				for each(var s2:SResource in vecResource)
					vecResourceXml.appendChild(s2.toXML());
				topXml.appendChild(vecResourceXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wTurn = wTurn;
			obj_.vecItemGenInfo = vecItemGenInfo;
			obj_.vecResource = vecResource;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSweepItem
		{
			var s_:SSweepItem = new SSweepItem();
			var wTurn:uint = bytes.readUnsignedShort();
			s_.wTurn = wTurn;
			var vecItemGenInfo:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes);
			s_.vecItemGenInfo = vecItemGenInfo;
			var vecResource:Vector.<SResource> = SResource.vectorFromByteArray(bytes);
			s_.vecResource = vecResource;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSweepItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSweepItem> = new Vector.<SSweepItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSweepItem = SSweepItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wTurn);
			SItemGenInfo.vectorToByteArray(vecItemGenInfo, bytes);
			SResource.vectorToByteArray(vecResource, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SSweepItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSweepItem in vec)
				s.toByteArray(bytes);
		}
	}
}
