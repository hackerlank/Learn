/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleStream.as
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 面板散仙信息
	 */
	public final class SRoleStream
	{
		public var oMainFighter:SFighterSpecInfo; //主散仙的信息

		/**
		 * 辅助创建函数
		 */
		public static function create(oMainFighter:SFighterSpecInfo):SRoleStream
		{
			var s_:SRoleStream = new SRoleStream();
			s_.oMainFighter = oMainFighter;
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
				topXml = <SRoleStream _name_={name_}/>;
			else
				topXml = <SRoleStream/>;
			if(oMainFighter != null)
				topXml.appendChild(oMainFighter.toXML("oMainFighter"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.oMainFighter = oMainFighter;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleStream
		{
			var s_:SRoleStream = new SRoleStream();
			var oMainFighter:SFighterSpecInfo = SFighterSpecInfo.fromByteArray(bytes);
			s_.oMainFighter = oMainFighter;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleStream>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleStream> = new Vector.<SRoleStream>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleStream = SRoleStream.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			oMainFighter.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleStream>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleStream in vec)
				s.toByteArray(bytes);
		}
	}
}
