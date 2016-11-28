/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCittaData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 心法数据
	 */
	public final class SCittaData
	{
		public var dwCittaID:uint; //(无符号32位整数)心法ID
		public var byLevel:uint; //(无符号8位整数)等级

		/**
		 * 辅助创建函数
		 */
		public static function create(dwCittaID:uint, byLevel:uint):SCittaData
		{
			var s_:SCittaData = new SCittaData();
			s_.dwCittaID = dwCittaID;
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
				topXml = <SCittaData _name_={name_} dwCittaID={dwCittaID} byLevel={byLevel}/>;
			else
				topXml = <SCittaData dwCittaID={dwCittaID} byLevel={byLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwCittaID = dwCittaID;
			obj_.byLevel = byLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCittaData
		{
			var s_:SCittaData = new SCittaData();
			var dwCittaID:uint = bytes.readUnsignedInt();
			s_.dwCittaID = dwCittaID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCittaData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCittaData> = new Vector.<SCittaData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCittaData = SCittaData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwCittaID);
			bytes.writeByte(byLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SCittaData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCittaData in vec)
				s.toByteArray(bytes);
		}
	}
}
