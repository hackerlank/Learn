/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCombData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 组合
	 */
	public final class SCombData
	{
		public var byGroupID:uint; //(无符号8位整数)组合ID
		public var byLevel:uint; //(无符号8位整数)组合等级
		public var bySelected:uint; //(无符号8位整数)是否出战

		/**
		 * 辅助创建函数
		 */
		public static function create(byGroupID:uint, byLevel:uint, bySelected:uint):SCombData
		{
			var s_:SCombData = new SCombData();
			s_.byGroupID = byGroupID;
			s_.byLevel = byLevel;
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
				topXml = <SCombData _name_={name_} byGroupID={byGroupID} byLevel={byLevel} bySelected={bySelected}/>;
			else
				topXml = <SCombData byGroupID={byGroupID} byLevel={byLevel} bySelected={bySelected}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byGroupID = byGroupID;
			obj_.byLevel = byLevel;
			obj_.bySelected = bySelected;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCombData
		{
			var s_:SCombData = new SCombData();
			var byGroupID:uint = bytes.readUnsignedByte();
			s_.byGroupID = byGroupID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCombData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCombData> = new Vector.<SCombData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCombData = SCombData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byGroupID);
			bytes.writeByte(byLevel);
			bytes.writeByte(bySelected);
		}

		public static function vectorToByteArray(vec:Vector.<SCombData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCombData in vec)
				s.toByteArray(bytes);
		}
	}
}
