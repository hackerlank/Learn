/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleAllStatus.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家在所有活动中的信息
	 */
	public final class SRoleAllStatus
	{
		public var wActID:uint; //(无符号16位整数)活动ID
		public var vecAllState:Vector.<SRoleStatus>; //状态

		/**
		 * 辅助创建函数
		 */
		public static function create(wActID:uint, vecAllState:Vector.<SRoleStatus>):SRoleAllStatus
		{
			var s_:SRoleAllStatus = new SRoleAllStatus();
			s_.wActID = wActID;
			s_.vecAllState = vecAllState;
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
				topXml = <SRoleAllStatus _name_={name_} wActID={wActID}/>;
			else
				topXml = <SRoleAllStatus wActID={wActID}/>;
			if(vecAllState != null)
			{
				var vecAllStateXml:XML = <Vec_SRoleStatus _name_="vecAllState"/>;
				for each(var s1:SRoleStatus in vecAllState)
					vecAllStateXml.appendChild(s1.toXML());
				topXml.appendChild(vecAllStateXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wActID = wActID;
			obj_.vecAllState = vecAllState;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleAllStatus
		{
			var s_:SRoleAllStatus = new SRoleAllStatus();
			var wActID:uint = bytes.readUnsignedShort();
			s_.wActID = wActID;
			var vecAllState:Vector.<SRoleStatus> = SRoleStatus.vectorFromByteArray(bytes);
			s_.vecAllState = vecAllState;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleAllStatus>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleAllStatus> = new Vector.<SRoleAllStatus>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleAllStatus = SRoleAllStatus.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wActID);
			SRoleStatus.vectorToByteArray(vecAllState, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleAllStatus>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleAllStatus in vec)
				s.toByteArray(bytes);
		}
	}
}
