/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SXinFaInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 心法信息
	 */
	public final class SXinFaInfo
	{
		public var dwXinFaID:uint; //(无符号32位整数)心法ID
		public var byXinFaLvl:uint; //(无符号8位整数)心法等级
		public var iSlot:int; //(有符号32位整数)心法槽 -1表示心法没装备

		/**
		 * 辅助创建函数
		 */
		public static function create(dwXinFaID:uint, byXinFaLvl:uint, iSlot:int):SXinFaInfo
		{
			var s_:SXinFaInfo = new SXinFaInfo();
			s_.dwXinFaID = dwXinFaID;
			s_.byXinFaLvl = byXinFaLvl;
			s_.iSlot = iSlot;
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
				topXml = <SXinFaInfo _name_={name_} dwXinFaID={dwXinFaID} byXinFaLvl={byXinFaLvl} iSlot={iSlot}/>;
			else
				topXml = <SXinFaInfo dwXinFaID={dwXinFaID} byXinFaLvl={byXinFaLvl} iSlot={iSlot}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwXinFaID = dwXinFaID;
			obj_.byXinFaLvl = byXinFaLvl;
			obj_.iSlot = iSlot;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SXinFaInfo
		{
			var s_:SXinFaInfo = new SXinFaInfo();
			var dwXinFaID:uint = bytes.readUnsignedInt();
			s_.dwXinFaID = dwXinFaID;
			var byXinFaLvl:uint = bytes.readUnsignedByte();
			s_.byXinFaLvl = byXinFaLvl;
			var iSlot:int = bytes.readInt();
			s_.iSlot = iSlot;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SXinFaInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SXinFaInfo> = new Vector.<SXinFaInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SXinFaInfo = SXinFaInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwXinFaID);
			bytes.writeByte(byXinFaLvl);
			bytes.writeInt(iSlot);
		}

		public static function vectorToByteArray(vec:Vector.<SXinFaInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SXinFaInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
