/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMailBaseAttachment.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 邮件附件
	 */
	public class SMailBaseAttachment
	{
		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SMailBaseAttachment.eType_SMailBaseAttachment;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SMailBaseAttachment _name_={name_}/>;
			else
				topXml = <SMailBaseAttachment/>;
			return topXml;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMailBaseAttachment
		{
			var s_:SMailBaseAttachment = new SMailBaseAttachment();
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SMailBaseAttachment
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SMailBaseAttachment;
			switch(eType)
			{
				case EType_SMailBaseAttachment.eType_SMailBaseAttachment:
					s = SMailBaseAttachment.fromByteArray(bytes);
					break;
				case EType_SMailBaseAttachment.eType_SItemAttachment:
					s = SItemAttachment.fromByteArray(bytes);
					break;
				case EType_SMailBaseAttachment.eType_SItemBaseCT:
					s = SItemBaseCT.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SMailBaseAttachment:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMailBaseAttachment>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMailBaseAttachment> = new Vector.<SMailBaseAttachment>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMailBaseAttachment = SMailBaseAttachment.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SMailBaseAttachment>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMailBaseAttachment> = new Vector.<SMailBaseAttachment>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMailBaseAttachment = SMailBaseAttachment.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SMailBaseAttachment>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMailBaseAttachment in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SMailBaseAttachment>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMailBaseAttachment in vec)
				s.superToByteArray(bytes);
		}
	}
}
