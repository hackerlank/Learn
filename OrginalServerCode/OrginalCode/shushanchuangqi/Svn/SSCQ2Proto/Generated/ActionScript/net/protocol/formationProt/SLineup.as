/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLineup.as
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵型信息
	 */
	public final class SLineup
	{
		public var qwInstID:BigInteger; //(无符号64位整数)散仙唯一ID
		public var iPos:int; //(有符号32位整数)位置

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, iPos:int):SLineup
		{
			var s_:SLineup = new SLineup();
			s_.qwInstID = qwInstID;
			s_.iPos = iPos;
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
				topXml = <SLineup _name_={name_} qwInstID={qwInstID} iPos={iPos}/>;
			else
				topXml = <SLineup qwInstID={qwInstID} iPos={iPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.iPos = iPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLineup
		{
			var s_:SLineup = new SLineup();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var iPos:int = bytes.readInt();
			s_.iPos = iPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLineup>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLineup> = new Vector.<SLineup>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLineup = SLineup.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeInt(iPos);
		}

		public static function vectorToByteArray(vec:Vector.<SLineup>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLineup in vec)
				s.toByteArray(bytes);
		}
	}
}
