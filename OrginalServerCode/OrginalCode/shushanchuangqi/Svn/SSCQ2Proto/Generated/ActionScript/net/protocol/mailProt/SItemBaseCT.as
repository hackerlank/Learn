/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItemBaseCT.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import net.protocol.itemProt.SItem;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 物品附件:具体物品对象
	 */
	public final class SItemBaseCT extends SMailBaseAttachment
	{
		public var vecItems:Vector.<SItem>; //物品

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SMailBaseAttachment.eType_SItemBaseCT;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SItemBaseCT _name_={name_}/>;
			else
				topXml = <SItemBaseCT/>;
			if(vecItems != null)
			{
				var vecItemsXml:XML = <Vec_SItem _name_="vecItems"/>;
				for each(var s1:SItem in vecItems)
					vecItemsXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemsXml);
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
			obj_.vecItems = vecItems;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItemBaseCT
		{
			var s_:SItemBaseCT = new SItemBaseCT();
			var base_:SMailBaseAttachment = SMailBaseAttachment.fromByteArray(bytes);
			var vecItems:Vector.<SItem> = SItem.superVectorFromByteArray(bytes);
			s_.vecItems = vecItems;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItemBaseCT>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItemBaseCT> = new Vector.<SItemBaseCT>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItemBaseCT = SItemBaseCT.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			SItem.superVectorToByteArray(vecItems, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SItemBaseCT>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItemBaseCT in vec)
				s.toByteArray(bytes);
		}
	}
}
