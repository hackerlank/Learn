/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDujieData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 渡劫信息
	 */
	public final class SDujieData
	{
		public var byTemplateID:uint; //(无符号8位整数)渡劫模版Id
		public var byLevel:uint; //(无符号8位整数)渡劫等级

		/**
		 * 辅助创建函数
		 */
		public static function create(byTemplateID:uint, byLevel:uint):SDujieData
		{
			var s_:SDujieData = new SDujieData();
			s_.byTemplateID = byTemplateID;
			s_.byLevel = byLevel;
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
				topXml = <SDujieData _name_={name_} byTemplateID={byTemplateID} byLevel={byLevel}/>;
			else
				topXml = <SDujieData byTemplateID={byTemplateID} byLevel={byLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byTemplateID = byTemplateID;
			obj_.byLevel = byLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDujieData
		{
			var s_:SDujieData = new SDujieData();
			var byTemplateID:uint = bytes.readUnsignedByte();
			s_.byTemplateID = byTemplateID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDujieData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDujieData> = new Vector.<SDujieData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDujieData = SDujieData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byTemplateID);
			bytes.writeByte(byLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SDujieData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDujieData in vec)
				s.toByteArray(bytes);
		}
	}
}
