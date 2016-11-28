/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SWActConfig.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活动具体配置信息
	 */
	public final class SWActConfig
	{
		public var wWActID:uint; //(无符号16位整数)活动ID
		public var wCfgID:uint; //(无符号16位整数)活动配置ID
		public var eWactPrizeType:uint; //(枚举类型：EWActPrizeType)奖励类型
		public var vecItemConfig:Vector.<SItemConfig>; //奖励道具列表

		/**
		 * 辅助创建函数
		 */
		public static function create(wWActID:uint, wCfgID:uint, eWactPrizeType:uint, vecItemConfig:Vector.<SItemConfig>):SWActConfig
		{
			var s_:SWActConfig = new SWActConfig();
			s_.wWActID = wWActID;
			s_.wCfgID = wCfgID;
			s_.eWactPrizeType = eWactPrizeType;
			s_.vecItemConfig = vecItemConfig;
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
				topXml = <SWActConfig _name_={name_} wWActID={wWActID} wCfgID={wCfgID} eWactPrizeType={eWactPrizeType}/>;
			else
				topXml = <SWActConfig wWActID={wWActID} wCfgID={wCfgID} eWactPrizeType={eWactPrizeType}/>;
			if(vecItemConfig != null)
			{
				var vecItemConfigXml:XML = <Vec_SItemConfig _name_="vecItemConfig"/>;
				for each(var s1:SItemConfig in vecItemConfig)
					vecItemConfigXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemConfigXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wWActID = wWActID;
			obj_.wCfgID = wCfgID;
			obj_.eWactPrizeType = eWactPrizeType;
			obj_.vecItemConfig = vecItemConfig;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SWActConfig
		{
			var s_:SWActConfig = new SWActConfig();
			var wWActID:uint = bytes.readUnsignedShort();
			s_.wWActID = wWActID;
			var wCfgID:uint = bytes.readUnsignedShort();
			s_.wCfgID = wCfgID;
			var eWactPrizeType:uint = bytes.readUnsignedByte();
			s_.eWactPrizeType = eWactPrizeType;
			var vecItemConfig:Vector.<SItemConfig> = SItemConfig.vectorFromByteArray(bytes);
			s_.vecItemConfig = vecItemConfig;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SWActConfig>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SWActConfig> = new Vector.<SWActConfig>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SWActConfig = SWActConfig.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wWActID);
			bytes.writeShort(wCfgID);
			bytes.writeByte(eWactPrizeType);
			SItemConfig.vectorToByteArray(vecItemConfig, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SWActConfig>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SWActConfig in vec)
				s.toByteArray(bytes);
		}
	}
}
