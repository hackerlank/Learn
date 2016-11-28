/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCaveCoreInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 洞府阵眼信息
	 */
	public final class SCaveCoreInfo
	{
		public var eType:uint; //(枚举类型：ENGBCaveCore)阵眼类型
		public var vecPlayerInfo:Vector.<SPlayerPanelInfo>; //占领者信息（数量只能为0/1）

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, vecPlayerInfo:Vector.<SPlayerPanelInfo>):SCaveCoreInfo
		{
			var s_:SCaveCoreInfo = new SCaveCoreInfo();
			s_.eType = eType;
			s_.vecPlayerInfo = vecPlayerInfo;
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
				topXml = <SCaveCoreInfo _name_={name_} eType={eType}/>;
			else
				topXml = <SCaveCoreInfo eType={eType}/>;
			if(vecPlayerInfo != null)
			{
				var vecPlayerInfoXml:XML = <Vec_SPlayerPanelInfo _name_="vecPlayerInfo"/>;
				for each(var s1:SPlayerPanelInfo in vecPlayerInfo)
					vecPlayerInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlayerInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.vecPlayerInfo = vecPlayerInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCaveCoreInfo
		{
			var s_:SCaveCoreInfo = new SCaveCoreInfo();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var vecPlayerInfo:Vector.<SPlayerPanelInfo> = SPlayerPanelInfo.vectorFromByteArray(bytes);
			s_.vecPlayerInfo = vecPlayerInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCaveCoreInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCaveCoreInfo> = new Vector.<SCaveCoreInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCaveCoreInfo = SCaveCoreInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			SPlayerPanelInfo.vectorToByteArray(vecPlayerInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SCaveCoreInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCaveCoreInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
