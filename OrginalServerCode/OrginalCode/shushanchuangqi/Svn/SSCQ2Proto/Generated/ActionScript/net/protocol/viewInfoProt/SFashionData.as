/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFashionData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 时装信息
	 */
	public final class SFashionData
	{
		public var wItemID:uint; //(无符号16位整数)时装模板
		public var byFashionLvl:uint; //(无符号8位整数)时装等级
		public var bySelected:uint; //(无符号8位整数)是否选中

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, byFashionLvl:uint, bySelected:uint):SFashionData
		{
			var s_:SFashionData = new SFashionData();
			s_.wItemID = wItemID;
			s_.byFashionLvl = byFashionLvl;
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
				topXml = <SFashionData _name_={name_} wItemID={wItemID} byFashionLvl={byFashionLvl} bySelected={bySelected}/>;
			else
				topXml = <SFashionData wItemID={wItemID} byFashionLvl={byFashionLvl} bySelected={bySelected}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.byFashionLvl = byFashionLvl;
			obj_.bySelected = bySelected;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFashionData
		{
			var s_:SFashionData = new SFashionData();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var byFashionLvl:uint = bytes.readUnsignedByte();
			s_.byFashionLvl = byFashionLvl;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFashionData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFashionData> = new Vector.<SFashionData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFashionData = SFashionData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeByte(byFashionLvl);
			bytes.writeByte(bySelected);
		}

		public static function vectorToByteArray(vec:Vector.<SFashionData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFashionData in vec)
				s.toByteArray(bytes);
		}
	}
}
