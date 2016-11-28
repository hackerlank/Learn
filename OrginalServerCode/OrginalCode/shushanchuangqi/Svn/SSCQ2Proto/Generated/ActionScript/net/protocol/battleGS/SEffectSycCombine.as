/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectSycCombine.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 同步连携值
	 */
	public final class SEffectSycCombine extends SEffectBase
	{
		public var iCombine:int; //(有符号32位整数)当前连携值
		public var vecSycType:Vector.<uint>; //(无符号8位整数)更改方式（见ECombineType）)

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectSycCombine;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectSycCombine _name_={name_} iCombine={iCombine}/>;
			else
				topXml = <SEffectSycCombine iCombine={iCombine}/>;
			if(vecSycType != null)
			{
				var vecSycTypeXml:XML = <Vec_UINT8 _name_="vecSycType"/>;
				var text1:String = "";
				for each(var value1:uint in vecSycType)
					text1 += "[" + value1 + "]";
				vecSycTypeXml.appendChild(text1);
				topXml.appendChild(vecSycTypeXml);
			}
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
			obj_.iCombine = iCombine;
			obj_.vecSycType = vecSycType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectSycCombine
		{
			var s_:SEffectSycCombine = new SEffectSycCombine();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var iCombine:int = bytes.readInt();
			s_.iCombine = iCombine;
			var vecSycType:Vector.<uint> = BytesUtil.readVecUByte(bytes);
			s_.vecSycType = vecSycType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectSycCombine>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectSycCombine> = new Vector.<SEffectSycCombine>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectSycCombine = SEffectSycCombine.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeInt(iCombine);
			BytesUtil.writeVecUByte(bytes, vecSycType);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectSycCombine>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectSycCombine in vec)
				s.toByteArray(bytes);
		}
	}
}
