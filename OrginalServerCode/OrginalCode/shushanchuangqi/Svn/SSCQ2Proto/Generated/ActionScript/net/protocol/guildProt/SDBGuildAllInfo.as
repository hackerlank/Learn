/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDBGuildAllInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派完整信息(数据库传来的内部协议)
	 */
	public final class SDBGuildAllInfo
	{
		public var sBaseInfo:SGuildBaseInfo; //基本信息
		public var vecMemberInfo:Vector.<SDBGuildUserInfo>; //帮派成员信息
		public var vecApplyInfo:Vector.<SGuildApplyInfo>; //帮派申请信息
		public var vecBuildingInfo:Vector.<SGuildBuildingInfo>; //帮派建筑信息
		public var vecAuthority:Vector.<SGuildAuthorityInfo>; //帮派可选权限信息
		public var sStatueInfo:SGuildStatueInfo; //帮派神像信息
		public var vecLogInfo:Vector.<SGuildLogInfo>; //帮派日志信息
		public var vecLingShanShopBuyLogInfo:Vector.<SGuildLogInfo>; //帮派灵山商店购买日志信息

		/**
		 * 辅助创建函数
		 */
		public static function create(sBaseInfo:SGuildBaseInfo, vecMemberInfo:Vector.<SDBGuildUserInfo>, vecApplyInfo:Vector.<SGuildApplyInfo>, vecBuildingInfo:Vector.<SGuildBuildingInfo>, vecAuthority:Vector.<SGuildAuthorityInfo>, 
			sStatueInfo:SGuildStatueInfo, vecLogInfo:Vector.<SGuildLogInfo>, vecLingShanShopBuyLogInfo:Vector.<SGuildLogInfo>):SDBGuildAllInfo
		{
			var s_:SDBGuildAllInfo = new SDBGuildAllInfo();
			s_.sBaseInfo = sBaseInfo;
			s_.vecMemberInfo = vecMemberInfo;
			s_.vecApplyInfo = vecApplyInfo;
			s_.vecBuildingInfo = vecBuildingInfo;
			s_.vecAuthority = vecAuthority;
			s_.sStatueInfo = sStatueInfo;
			s_.vecLogInfo = vecLogInfo;
			s_.vecLingShanShopBuyLogInfo = vecLingShanShopBuyLogInfo;
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
				topXml = <SDBGuildAllInfo _name_={name_}/>;
			else
				topXml = <SDBGuildAllInfo/>;
			if(sBaseInfo != null)
				topXml.appendChild(sBaseInfo.toXML("sBaseInfo"));
			if(vecMemberInfo != null)
			{
				var vecMemberInfoXml:XML = <Vec_SDBGuildUserInfo _name_="vecMemberInfo"/>;
				for each(var s2:SDBGuildUserInfo in vecMemberInfo)
					vecMemberInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecMemberInfoXml);
			}
			if(vecApplyInfo != null)
			{
				var vecApplyInfoXml:XML = <Vec_SGuildApplyInfo _name_="vecApplyInfo"/>;
				for each(var s3:SGuildApplyInfo in vecApplyInfo)
					vecApplyInfoXml.appendChild(s3.toXML());
				topXml.appendChild(vecApplyInfoXml);
			}
			if(vecBuildingInfo != null)
			{
				var vecBuildingInfoXml:XML = <Vec_SGuildBuildingInfo _name_="vecBuildingInfo"/>;
				for each(var s4:SGuildBuildingInfo in vecBuildingInfo)
					vecBuildingInfoXml.appendChild(s4.toXML());
				topXml.appendChild(vecBuildingInfoXml);
			}
			if(vecAuthority != null)
			{
				var vecAuthorityXml:XML = <Vec_SGuildAuthorityInfo _name_="vecAuthority"/>;
				for each(var s5:SGuildAuthorityInfo in vecAuthority)
					vecAuthorityXml.appendChild(s5.toXML());
				topXml.appendChild(vecAuthorityXml);
			}
			if(sStatueInfo != null)
				topXml.appendChild(sStatueInfo.toXML("sStatueInfo"));
			if(vecLogInfo != null)
			{
				var vecLogInfoXml:XML = <Vec_SGuildLogInfo _name_="vecLogInfo"/>;
				for each(var s7:SGuildLogInfo in vecLogInfo)
					vecLogInfoXml.appendChild(s7.toXML());
				topXml.appendChild(vecLogInfoXml);
			}
			if(vecLingShanShopBuyLogInfo != null)
			{
				var vecLingShanShopBuyLogInfoXml:XML = <Vec_SGuildLogInfo _name_="vecLingShanShopBuyLogInfo"/>;
				for each(var s8:SGuildLogInfo in vecLingShanShopBuyLogInfo)
					vecLingShanShopBuyLogInfoXml.appendChild(s8.toXML());
				topXml.appendChild(vecLingShanShopBuyLogInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.sBaseInfo = sBaseInfo;
			obj_.vecMemberInfo = vecMemberInfo;
			obj_.vecApplyInfo = vecApplyInfo;
			obj_.vecBuildingInfo = vecBuildingInfo;
			obj_.vecAuthority = vecAuthority;
			obj_.sStatueInfo = sStatueInfo;
			obj_.vecLogInfo = vecLogInfo;
			obj_.vecLingShanShopBuyLogInfo = vecLingShanShopBuyLogInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDBGuildAllInfo
		{
			var s_:SDBGuildAllInfo = new SDBGuildAllInfo();
			var sBaseInfo:SGuildBaseInfo = SGuildBaseInfo.fromByteArray(bytes);
			s_.sBaseInfo = sBaseInfo;
			var vecMemberInfo:Vector.<SDBGuildUserInfo> = SDBGuildUserInfo.vectorFromByteArray(bytes);
			s_.vecMemberInfo = vecMemberInfo;
			var vecApplyInfo:Vector.<SGuildApplyInfo> = SGuildApplyInfo.vectorFromByteArray(bytes);
			s_.vecApplyInfo = vecApplyInfo;
			var vecBuildingInfo:Vector.<SGuildBuildingInfo> = SGuildBuildingInfo.vectorFromByteArray(bytes);
			s_.vecBuildingInfo = vecBuildingInfo;
			var vecAuthority:Vector.<SGuildAuthorityInfo> = SGuildAuthorityInfo.vectorFromByteArray(bytes);
			s_.vecAuthority = vecAuthority;
			var sStatueInfo:SGuildStatueInfo = SGuildStatueInfo.fromByteArray(bytes);
			s_.sStatueInfo = sStatueInfo;
			var vecLogInfo:Vector.<SGuildLogInfo> = SGuildLogInfo.vectorFromByteArray(bytes);
			s_.vecLogInfo = vecLogInfo;
			var vecLingShanShopBuyLogInfo:Vector.<SGuildLogInfo> = SGuildLogInfo.vectorFromByteArray(bytes);
			s_.vecLingShanShopBuyLogInfo = vecLingShanShopBuyLogInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDBGuildAllInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDBGuildAllInfo> = new Vector.<SDBGuildAllInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDBGuildAllInfo = SDBGuildAllInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			sBaseInfo.toByteArray(bytes);
			SDBGuildUserInfo.vectorToByteArray(vecMemberInfo, bytes);
			SGuildApplyInfo.vectorToByteArray(vecApplyInfo, bytes);
			SGuildBuildingInfo.vectorToByteArray(vecBuildingInfo, bytes);
			SGuildAuthorityInfo.vectorToByteArray(vecAuthority, bytes);
			sStatueInfo.toByteArray(bytes);
			SGuildLogInfo.vectorToByteArray(vecLogInfo, bytes);
			SGuildLogInfo.vectorToByteArray(vecLingShanShopBuyLogInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SDBGuildAllInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDBGuildAllInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
