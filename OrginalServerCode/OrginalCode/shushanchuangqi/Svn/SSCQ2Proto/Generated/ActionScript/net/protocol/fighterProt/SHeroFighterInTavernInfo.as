/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SHeroFighterInTavernInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 客栈散仙信息
	 */
	public final class SHeroFighterInTavernInfo
	{
		public var wID:uint; //(无符号16位整数)散仙ID
		public var bHired:Boolean; //是否已招募

		/**
		 * 辅助创建函数
		 */
		public static function create(wID:uint, bHired:Boolean):SHeroFighterInTavernInfo
		{
			var s_:SHeroFighterInTavernInfo = new SHeroFighterInTavernInfo();
			s_.wID = wID;
			s_.bHired = bHired;
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
				topXml = <SHeroFighterInTavernInfo _name_={name_} wID={wID} bHired={bHired}/>;
			else
				topXml = <SHeroFighterInTavernInfo wID={wID} bHired={bHired}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wID = wID;
			obj_.bHired = bHired;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SHeroFighterInTavernInfo
		{
			var s_:SHeroFighterInTavernInfo = new SHeroFighterInTavernInfo();
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var bHired:Boolean = bytes.readBoolean();
			s_.bHired = bHired;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SHeroFighterInTavernInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SHeroFighterInTavernInfo> = new Vector.<SHeroFighterInTavernInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SHeroFighterInTavernInfo = SHeroFighterInTavernInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wID);
			bytes.writeBoolean(bHired);
		}

		public static function vectorToByteArray(vec:Vector.<SHeroFighterInTavernInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SHeroFighterInTavernInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
