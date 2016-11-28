/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleFighterStream.as
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 散仙信息
	 */
	public final class SRoleFighterStream
	{
		public var oMainFighter:SFighterSpecInfo; //主散仙的信息
		public var oFighters:Vector.<SFighterSpecInfo>; //所有散仙的信息

		/**
		 * 辅助创建函数
		 */
		public static function create(oMainFighter:SFighterSpecInfo, oFighters:Vector.<SFighterSpecInfo>):SRoleFighterStream
		{
			var s_:SRoleFighterStream = new SRoleFighterStream();
			s_.oMainFighter = oMainFighter;
			s_.oFighters = oFighters;
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
				topXml = <SRoleFighterStream _name_={name_}/>;
			else
				topXml = <SRoleFighterStream/>;
			if(oMainFighter != null)
				topXml.appendChild(oMainFighter.toXML("oMainFighter"));
			if(oFighters != null)
			{
				var oFightersXml:XML = <Vec_SFighterSpecInfo _name_="oFighters"/>;
				for each(var s2:SFighterSpecInfo in oFighters)
					oFightersXml.appendChild(s2.toXML());
				topXml.appendChild(oFightersXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.oMainFighter = oMainFighter;
			obj_.oFighters = oFighters;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleFighterStream
		{
			var s_:SRoleFighterStream = new SRoleFighterStream();
			var oMainFighter:SFighterSpecInfo = SFighterSpecInfo.fromByteArray(bytes);
			s_.oMainFighter = oMainFighter;
			var oFighters:Vector.<SFighterSpecInfo> = SFighterSpecInfo.vectorFromByteArray(bytes);
			s_.oFighters = oFighters;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleFighterStream>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleFighterStream> = new Vector.<SRoleFighterStream>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleFighterStream = SRoleFighterStream.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			oMainFighter.toByteArray(bytes);
			SFighterSpecInfo.vectorToByteArray(oFighters, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleFighterStream>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleFighterStream in vec)
				s.toByteArray(bytes);
		}
	}
}
