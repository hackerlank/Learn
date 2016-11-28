/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STavernInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 客栈信息
	 */
	public final class STavernInfo
	{
		public var wID:uint; //(无符号16位整数)客栈ID
		public var vecFighterInfo:Vector.<SHeroFighterInTavernInfo>; //客栈中散仙信息

		/**
		 * 辅助创建函数
		 */
		public static function create(wID:uint, vecFighterInfo:Vector.<SHeroFighterInTavernInfo>):STavernInfo
		{
			var s_:STavernInfo = new STavernInfo();
			s_.wID = wID;
			s_.vecFighterInfo = vecFighterInfo;
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
				topXml = <STavernInfo _name_={name_} wID={wID}/>;
			else
				topXml = <STavernInfo wID={wID}/>;
			if(vecFighterInfo != null)
			{
				var vecFighterInfoXml:XML = <Vec_SHeroFighterInTavernInfo _name_="vecFighterInfo"/>;
				for each(var s1:SHeroFighterInTavernInfo in vecFighterInfo)
					vecFighterInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecFighterInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wID = wID;
			obj_.vecFighterInfo = vecFighterInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STavernInfo
		{
			var s_:STavernInfo = new STavernInfo();
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var vecFighterInfo:Vector.<SHeroFighterInTavernInfo> = SHeroFighterInTavernInfo.vectorFromByteArray(bytes);
			s_.vecFighterInfo = vecFighterInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STavernInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STavernInfo> = new Vector.<STavernInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STavernInfo = STavernInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wID);
			SHeroFighterInTavernInfo.vectorToByteArray(vecFighterInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<STavernInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STavernInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
