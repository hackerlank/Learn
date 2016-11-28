/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRareTrumpData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 稀有的法宝信息
	 */
	public final class SRareTrumpData
	{
		public var wItemID:uint; //(无符号16位整数)法宝模板
		public var byTrumpLvl:uint; //(无符号8位整数)法宝等级
		public var bySelected:uint; //(无符号8位整数)是否出战

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, byTrumpLvl:uint, bySelected:uint):SRareTrumpData
		{
			var s_:SRareTrumpData = new SRareTrumpData();
			s_.wItemID = wItemID;
			s_.byTrumpLvl = byTrumpLvl;
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
				topXml = <SRareTrumpData _name_={name_} wItemID={wItemID} byTrumpLvl={byTrumpLvl} bySelected={bySelected}/>;
			else
				topXml = <SRareTrumpData wItemID={wItemID} byTrumpLvl={byTrumpLvl} bySelected={bySelected}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.byTrumpLvl = byTrumpLvl;
			obj_.bySelected = bySelected;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRareTrumpData
		{
			var s_:SRareTrumpData = new SRareTrumpData();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var byTrumpLvl:uint = bytes.readUnsignedByte();
			s_.byTrumpLvl = byTrumpLvl;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRareTrumpData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRareTrumpData> = new Vector.<SRareTrumpData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRareTrumpData = SRareTrumpData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeByte(byTrumpLvl);
			bytes.writeByte(bySelected);
		}

		public static function vectorToByteArray(vec:Vector.<SRareTrumpData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRareTrumpData in vec)
				s.toByteArray(bytes);
		}
	}
}
