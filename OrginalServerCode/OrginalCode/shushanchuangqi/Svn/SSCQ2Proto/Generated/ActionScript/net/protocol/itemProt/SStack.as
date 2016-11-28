/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SStack.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 堆叠道具的信息，只用于识别
	 */
	public final class SStack extends SItem
	{
		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SItem.eType_SStack;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SStack _name_={name_}/>;
			else
				topXml = <SStack/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SStack
		{
			var s_:SStack = new SStack();
			var base_:SItem = SItem.fromByteArray(bytes);
			base_.copyTo(s_);
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SStack>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SStack> = new Vector.<SStack>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SStack = SStack.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SStack>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SStack in vec)
				s.toByteArray(bytes);
		}
	}
}
