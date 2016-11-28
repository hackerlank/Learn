/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPubGuildAllInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派公共数据（用于服务端读取加载常驻内存的基础数据）
	 */
	public final class SPubGuildAllInfo
	{
		public var sGuildListInfo:SGuildListInfo; //帮派列表数据
		public var sGuildBattleInfo:SDBGuildBattleInfo; //帮派战数据

		/**
		 * 辅助创建函数
		 */
		public static function create(sGuildListInfo:SGuildListInfo, sGuildBattleInfo:SDBGuildBattleInfo):SPubGuildAllInfo
		{
			var s_:SPubGuildAllInfo = new SPubGuildAllInfo();
			s_.sGuildListInfo = sGuildListInfo;
			s_.sGuildBattleInfo = sGuildBattleInfo;
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
				topXml = <SPubGuildAllInfo _name_={name_}/>;
			else
				topXml = <SPubGuildAllInfo/>;
			if(sGuildListInfo != null)
				topXml.appendChild(sGuildListInfo.toXML("sGuildListInfo"));
			if(sGuildBattleInfo != null)
				topXml.appendChild(sGuildBattleInfo.toXML("sGuildBattleInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.sGuildListInfo = sGuildListInfo;
			obj_.sGuildBattleInfo = sGuildBattleInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPubGuildAllInfo
		{
			var s_:SPubGuildAllInfo = new SPubGuildAllInfo();
			var sGuildListInfo:SGuildListInfo = SGuildListInfo.fromByteArray(bytes);
			s_.sGuildListInfo = sGuildListInfo;
			var sGuildBattleInfo:SDBGuildBattleInfo = SDBGuildBattleInfo.fromByteArray(bytes);
			s_.sGuildBattleInfo = sGuildBattleInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPubGuildAllInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPubGuildAllInfo> = new Vector.<SPubGuildAllInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPubGuildAllInfo = SPubGuildAllInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			sGuildListInfo.toByteArray(bytes);
			sGuildBattleInfo.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPubGuildAllInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPubGuildAllInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
