/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildAllInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派完整信息
	 */
	public final class SGuildAllInfo
	{
		public var sBaseInfo:SGuildBaseInfo; //基本信息
		public var vecMemberInfo:Vector.<SGuildUserInfo>; //帮派成员信息
		public var vecApplyInfo:Vector.<SGuildApplyInfo>; //帮派申请信息
		public var vecBuildingInfo:Vector.<SGuildBuildingInfo>; //帮派建筑信息
		public var vecAuthority:Vector.<SGuildAuthorityInfo>; //帮派可选权限信息
		public var vecTech:Vector.<SGuildTechInfo>; //帮派科技信息
		public var sStatueInfo:SGuildStatueInfo; //帮派神像信息
		public var vecLogInfo:Vector.<SGuildLogInfo>; //帮派日志信息

		/**
		 * 辅助创建函数
		 */
		public static function create(sBaseInfo:SGuildBaseInfo, vecMemberInfo:Vector.<SGuildUserInfo>, vecApplyInfo:Vector.<SGuildApplyInfo>, vecBuildingInfo:Vector.<SGuildBuildingInfo>, vecAuthority:Vector.<SGuildAuthorityInfo>, 
			vecTech:Vector.<SGuildTechInfo>, sStatueInfo:SGuildStatueInfo, vecLogInfo:Vector.<SGuildLogInfo>):SGuildAllInfo
		{
			var s_:SGuildAllInfo = new SGuildAllInfo();
			s_.sBaseInfo = sBaseInfo;
			s_.vecMemberInfo = vecMemberInfo;
			s_.vecApplyInfo = vecApplyInfo;
			s_.vecBuildingInfo = vecBuildingInfo;
			s_.vecAuthority = vecAuthority;
			s_.vecTech = vecTech;
			s_.sStatueInfo = sStatueInfo;
			s_.vecLogInfo = vecLogInfo;
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
				topXml = <SGuildAllInfo _name_={name_}/>;
			else
				topXml = <SGuildAllInfo/>;
			if(sBaseInfo != null)
				topXml.appendChild(sBaseInfo.toXML("sBaseInfo"));
			if(vecMemberInfo != null)
			{
				var vecMemberInfoXml:XML = <Vec_SGuildUserInfo _name_="vecMemberInfo"/>;
				for each(var s2:SGuildUserInfo in vecMemberInfo)
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
			if(vecTech != null)
			{
				var vecTechXml:XML = <Vec_SGuildTechInfo _name_="vecTech"/>;
				for each(var s6:SGuildTechInfo in vecTech)
					vecTechXml.appendChild(s6.toXML());
				topXml.appendChild(vecTechXml);
			}
			if(sStatueInfo != null)
				topXml.appendChild(sStatueInfo.toXML("sStatueInfo"));
			if(vecLogInfo != null)
			{
				var vecLogInfoXml:XML = <Vec_SGuildLogInfo _name_="vecLogInfo"/>;
				for each(var s8:SGuildLogInfo in vecLogInfo)
					vecLogInfoXml.appendChild(s8.toXML());
				topXml.appendChild(vecLogInfoXml);
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
			obj_.vecTech = vecTech;
			obj_.sStatueInfo = sStatueInfo;
			obj_.vecLogInfo = vecLogInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildAllInfo
		{
			var s_:SGuildAllInfo = new SGuildAllInfo();
			var sBaseInfo:SGuildBaseInfo = SGuildBaseInfo.fromByteArray(bytes);
			s_.sBaseInfo = sBaseInfo;
			var vecMemberInfo:Vector.<SGuildUserInfo> = SGuildUserInfo.vectorFromByteArray(bytes);
			s_.vecMemberInfo = vecMemberInfo;
			var vecApplyInfo:Vector.<SGuildApplyInfo> = SGuildApplyInfo.vectorFromByteArray(bytes);
			s_.vecApplyInfo = vecApplyInfo;
			var vecBuildingInfo:Vector.<SGuildBuildingInfo> = SGuildBuildingInfo.vectorFromByteArray(bytes);
			s_.vecBuildingInfo = vecBuildingInfo;
			var vecAuthority:Vector.<SGuildAuthorityInfo> = SGuildAuthorityInfo.vectorFromByteArray(bytes);
			s_.vecAuthority = vecAuthority;
			var vecTech:Vector.<SGuildTechInfo> = SGuildTechInfo.vectorFromByteArray(bytes);
			s_.vecTech = vecTech;
			var sStatueInfo:SGuildStatueInfo = SGuildStatueInfo.fromByteArray(bytes);
			s_.sStatueInfo = sStatueInfo;
			var vecLogInfo:Vector.<SGuildLogInfo> = SGuildLogInfo.vectorFromByteArray(bytes);
			s_.vecLogInfo = vecLogInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildAllInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildAllInfo> = new Vector.<SGuildAllInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildAllInfo = SGuildAllInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			sBaseInfo.toByteArray(bytes);
			SGuildUserInfo.vectorToByteArray(vecMemberInfo, bytes);
			SGuildApplyInfo.vectorToByteArray(vecApplyInfo, bytes);
			SGuildBuildingInfo.vectorToByteArray(vecBuildingInfo, bytes);
			SGuildAuthorityInfo.vectorToByteArray(vecAuthority, bytes);
			SGuildTechInfo.vectorToByteArray(vecTech, bytes);
			sStatueInfo.toByteArray(bytes);
			SGuildLogInfo.vectorToByteArray(vecLogInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildAllInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildAllInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
