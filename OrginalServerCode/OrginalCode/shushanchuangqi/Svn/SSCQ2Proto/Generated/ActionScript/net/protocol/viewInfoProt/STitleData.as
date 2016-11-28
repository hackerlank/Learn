/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STitleData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 称号信息
	 */
	public final class STitleData
	{
		public var wTitleID:uint; //(无符号16位整数)称号ID
		public var bySelected:uint; //(无符号8位整数)是否选中

		/**
		 * 辅助创建函数
		 */
		public static function create(wTitleID:uint, bySelected:uint):STitleData
		{
			var s_:STitleData = new STitleData();
			s_.wTitleID = wTitleID;
			s_.bySelected = bySelected;
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
				topXml = <STitleData _name_={name_} wTitleID={wTitleID} bySelected={bySelected}/>;
			else
				topXml = <STitleData wTitleID={wTitleID} bySelected={bySelected}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wTitleID = wTitleID;
			obj_.bySelected = bySelected;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STitleData
		{
			var s_:STitleData = new STitleData();
			var wTitleID:uint = bytes.readUnsignedShort();
			s_.wTitleID = wTitleID;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STitleData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STitleData> = new Vector.<STitleData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STitleData = STitleData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wTitleID);
			bytes.writeByte(bySelected);
		}

		public static function vectorToByteArray(vec:Vector.<STitleData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STitleData in vec)
				s.toByteArray(bytes);
		}
	}
}
