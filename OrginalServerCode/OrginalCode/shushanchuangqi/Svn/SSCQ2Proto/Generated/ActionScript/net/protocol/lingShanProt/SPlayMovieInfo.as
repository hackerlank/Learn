/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayMovieInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 动画播放信息
	 */
	public final class SPlayMovieInfo
	{
		public var vecPlayerMoveInfo:Vector.<SPlayerMoveInfo>; //玩家移动路径
		public var vecPathCollideInfo:Vector.<SPathCollideInfo>; //路径碰撞
		public var vecGridCollideInfo:Vector.<SGridCollideInfo>; //格子碰撞
		public var vecRoomPlayInfo:Vector.<SRoomPlayInfo>; //玩家信息

		/**
		 * 辅助创建函数
		 */
		public static function create(vecPlayerMoveInfo:Vector.<SPlayerMoveInfo>, vecPathCollideInfo:Vector.<SPathCollideInfo>, vecGridCollideInfo:Vector.<SGridCollideInfo>, vecRoomPlayInfo:Vector.<SRoomPlayInfo>):SPlayMovieInfo
		{
			var s_:SPlayMovieInfo = new SPlayMovieInfo();
			s_.vecPlayerMoveInfo = vecPlayerMoveInfo;
			s_.vecPathCollideInfo = vecPathCollideInfo;
			s_.vecGridCollideInfo = vecGridCollideInfo;
			s_.vecRoomPlayInfo = vecRoomPlayInfo;
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
				topXml = <SPlayMovieInfo _name_={name_}/>;
			else
				topXml = <SPlayMovieInfo/>;
			if(vecPlayerMoveInfo != null)
			{
				var vecPlayerMoveInfoXml:XML = <Vec_SPlayerMoveInfo _name_="vecPlayerMoveInfo"/>;
				for each(var s1:SPlayerMoveInfo in vecPlayerMoveInfo)
					vecPlayerMoveInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlayerMoveInfoXml);
			}
			if(vecPathCollideInfo != null)
			{
				var vecPathCollideInfoXml:XML = <Vec_SPathCollideInfo _name_="vecPathCollideInfo"/>;
				for each(var s2:SPathCollideInfo in vecPathCollideInfo)
					vecPathCollideInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecPathCollideInfoXml);
			}
			if(vecGridCollideInfo != null)
			{
				var vecGridCollideInfoXml:XML = <Vec_SGridCollideInfo _name_="vecGridCollideInfo"/>;
				for each(var s3:SGridCollideInfo in vecGridCollideInfo)
					vecGridCollideInfoXml.appendChild(s3.toXML());
				topXml.appendChild(vecGridCollideInfoXml);
			}
			if(vecRoomPlayInfo != null)
			{
				var vecRoomPlayInfoXml:XML = <Vec_SRoomPlayInfo _name_="vecRoomPlayInfo"/>;
				for each(var s4:SRoomPlayInfo in vecRoomPlayInfo)
					vecRoomPlayInfoXml.appendChild(s4.toXML());
				topXml.appendChild(vecRoomPlayInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecPlayerMoveInfo = vecPlayerMoveInfo;
			obj_.vecPathCollideInfo = vecPathCollideInfo;
			obj_.vecGridCollideInfo = vecGridCollideInfo;
			obj_.vecRoomPlayInfo = vecRoomPlayInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayMovieInfo
		{
			var s_:SPlayMovieInfo = new SPlayMovieInfo();
			var vecPlayerMoveInfo:Vector.<SPlayerMoveInfo> = SPlayerMoveInfo.vectorFromByteArray(bytes);
			s_.vecPlayerMoveInfo = vecPlayerMoveInfo;
			var vecPathCollideInfo:Vector.<SPathCollideInfo> = SPathCollideInfo.vectorFromByteArray(bytes);
			s_.vecPathCollideInfo = vecPathCollideInfo;
			var vecGridCollideInfo:Vector.<SGridCollideInfo> = SGridCollideInfo.vectorFromByteArray(bytes);
			s_.vecGridCollideInfo = vecGridCollideInfo;
			var vecRoomPlayInfo:Vector.<SRoomPlayInfo> = SRoomPlayInfo.vectorFromByteArray(bytes);
			s_.vecRoomPlayInfo = vecRoomPlayInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayMovieInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayMovieInfo> = new Vector.<SPlayMovieInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayMovieInfo = SPlayMovieInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			SPlayerMoveInfo.vectorToByteArray(vecPlayerMoveInfo, bytes);
			SPathCollideInfo.vectorToByteArray(vecPathCollideInfo, bytes);
			SGridCollideInfo.vectorToByteArray(vecGridCollideInfo, bytes);
			SRoomPlayInfo.vectorToByteArray(vecRoomPlayInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayMovieInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayMovieInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
