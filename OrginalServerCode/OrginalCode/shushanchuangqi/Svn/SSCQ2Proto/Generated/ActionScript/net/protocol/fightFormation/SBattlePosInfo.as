/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattlePosInfo.as
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵型信息
	 */
	public final class SBattlePosInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)散仙唯一ID
		public var byPos:int; //(有符号8位整数)位置

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, byPos:int):SBattlePosInfo
		{
			var s_:SBattlePosInfo = new SBattlePosInfo();
			s_.qwInstID = qwInstID;
			s_.byPos = byPos;
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
				topXml = <SBattlePosInfo _name_={name_} qwInstID={qwInstID} byPos={byPos}/>;
			else
				topXml = <SBattlePosInfo qwInstID={qwInstID} byPos={byPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.byPos = byPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattlePosInfo
		{
			var s_:SBattlePosInfo = new SBattlePosInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var byPos:int = bytes.readByte();
			s_.byPos = byPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattlePosInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattlePosInfo> = new Vector.<SBattlePosInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattlePosInfo = SBattlePosInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeByte(byPos);
		}

		public static function vectorToByteArray(vec:Vector.<SBattlePosInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattlePosInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
