/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItemAttachment.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 物品附件
	 */
	public final class SItemAttachment extends SMailBaseAttachment
	{
		public var vecItemInfo:Vector.<SMailItemInfo>; //物品

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SMailBaseAttachment.eType_SItemAttachment;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SItemAttachment _name_={name_}/>;
			else
				topXml = <SItemAttachment/>;
			if(vecItemInfo != null)
			{
				var vecItemInfoXml:XML = <Vec_SMailItemInfo _name_="vecItemInfo"/>;
				for each(var s1:SMailItemInfo in vecItemInfo)
					vecItemInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemInfoXml);
			}
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecItemInfo = vecItemInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItemAttachment
		{
			var s_:SItemAttachment = new SItemAttachment();
			var base_:SMailBaseAttachment = SMailBaseAttachment.fromByteArray(bytes);
			var vecItemInfo:Vector.<SMailItemInfo> = SMailItemInfo.vectorFromByteArray(bytes);
			s_.vecItemInfo = vecItemInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItemAttachment>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItemAttachment> = new Vector.<SItemAttachment>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItemAttachment = SItemAttachment.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			SMailItemInfo.vectorToByteArray(vecItemInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SItemAttachment>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItemAttachment in vec)
				s.toByteArray(bytes);
		}
	}
}
