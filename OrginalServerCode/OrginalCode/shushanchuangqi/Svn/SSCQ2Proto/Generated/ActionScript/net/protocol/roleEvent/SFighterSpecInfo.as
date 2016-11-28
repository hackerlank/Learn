/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterSpecInfo.as
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import net.protocol.itemProt.SItem;
	import net.protocol.fighterProt.SFighterInfo;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 面板散仙信息
	 */
	public final class SFighterSpecInfo
	{
		public var oEquips:Vector.<SItem>; //散仙所有装备信息
		public var oFighterInfo:SFighterInfo; //散仙基本信息

		/**
		 * 辅助创建函数
		 */
		public static function create(oEquips:Vector.<SItem>, oFighterInfo:SFighterInfo):SFighterSpecInfo
		{
			var s_:SFighterSpecInfo = new SFighterSpecInfo();
			s_.oEquips = oEquips;
			s_.oFighterInfo = oFighterInfo;
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
				topXml = <SFighterSpecInfo _name_={name_}/>;
			else
				topXml = <SFighterSpecInfo/>;
			if(oEquips != null)
			{
				var oEquipsXml:XML = <Vec_SItem _name_="oEquips"/>;
				for each(var s1:SItem in oEquips)
					oEquipsXml.appendChild(s1.toXML());
				topXml.appendChild(oEquipsXml);
			}
			if(oFighterInfo != null)
				topXml.appendChild(oFighterInfo.toXML("oFighterInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.oEquips = oEquips;
			obj_.oFighterInfo = oFighterInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterSpecInfo
		{
			var s_:SFighterSpecInfo = new SFighterSpecInfo();
			var oEquips:Vector.<SItem> = SItem.superVectorFromByteArray(bytes);
			s_.oEquips = oEquips;
			var oFighterInfo:SFighterInfo = SFighterInfo.fromByteArray(bytes);
			s_.oFighterInfo = oFighterInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterSpecInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterSpecInfo> = new Vector.<SFighterSpecInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterSpecInfo = SFighterSpecInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			SItem.superVectorToByteArray(oEquips, bytes);
			oFighterInfo.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterSpecInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterSpecInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
