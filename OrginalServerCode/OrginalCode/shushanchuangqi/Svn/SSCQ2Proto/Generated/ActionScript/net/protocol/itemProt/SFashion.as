/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFashion.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 时装信息
	 */
	public final class SFashion extends SItem
	{
		public var byLevel:uint; //(无符号8位整数)时装等级
		public var dwExp:uint; //(无符号32位整数)时装经验
		public var bySelected:uint; //(无符号8位整数)是否选中
		public var byHide:uint; //(无符号8位整数)是否隐藏

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SItem.eType_SFashion;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SFashion _name_={name_} byLevel={byLevel} dwExp={dwExp} bySelected={bySelected} byHide={byHide}/>;
			else
				topXml = <SFashion byLevel={byLevel} dwExp={dwExp} bySelected={bySelected} byHide={byHide}/>;
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
			obj_.byLevel = byLevel;
			obj_.dwExp = dwExp;
			obj_.bySelected = bySelected;
			obj_.byHide = byHide;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFashion
		{
			var s_:SFashion = new SFashion();
			var base_:SItem = SItem.fromByteArray(bytes);
			base_.copyTo(s_);
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			var byHide:uint = bytes.readUnsignedByte();
			s_.byHide = byHide;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFashion>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFashion> = new Vector.<SFashion>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFashion = SFashion.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwExp);
			bytes.writeByte(bySelected);
			bytes.writeByte(byHide);
		}

		public static function vectorToByteArray(vec:Vector.<SFashion>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFashion in vec)
				s.toByteArray(bytes);
		}
	}
}
