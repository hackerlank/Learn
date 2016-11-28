/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGemstone.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 宝石信息
	 */
	public final class SGemstone extends SItem
	{
		public var qwOwnerID:BigInteger; //(无符号64位整数)散仙唯一ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SItem.eType_SGemstone;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGemstone _name_={name_} qwOwnerID={qwOwnerID}/>;
			else
				topXml = <SGemstone qwOwnerID={qwOwnerID}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.qwOwnerID = qwOwnerID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGemstone
		{
			var s_:SGemstone = new SGemstone();
			var base_:SItem = SItem.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGemstone>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGemstone> = new Vector.<SGemstone>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGemstone = SGemstone.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
		}

		public static function vectorToByteArray(vec:Vector.<SGemstone>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGemstone in vec)
				s.toByteArray(bytes);
		}
	}
}
