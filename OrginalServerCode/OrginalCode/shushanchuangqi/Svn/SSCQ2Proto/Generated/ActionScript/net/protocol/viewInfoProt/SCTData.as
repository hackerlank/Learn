/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCTData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 淬体（装备）信息
	 */
	public final class SCTData
	{
		public var byLianPi:uint; //(无符号8位整数)炼皮
		public var byTongJin:uint; //(无符号8位整数)通筋
		public var byQiangJi:uint; //(无符号8位整数)强肌
		public var byDuanGu:uint; //(无符号8位整数)锻骨
		public var byHuoLuo:uint; //(无符号8位整数)活络
		public var byXiSui:uint; //(无符号8位整数)洗髓

		/**
		 * 辅助创建函数
		 */
		public static function create(byLianPi:uint, byTongJin:uint, byQiangJi:uint, byDuanGu:uint, byHuoLuo:uint, 
			byXiSui:uint):SCTData
		{
			var s_:SCTData = new SCTData();
			s_.byLianPi = byLianPi;
			s_.byTongJin = byTongJin;
			s_.byQiangJi = byQiangJi;
			s_.byDuanGu = byDuanGu;
			s_.byHuoLuo = byHuoLuo;
			s_.byXiSui = byXiSui;
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
				topXml = <SCTData _name_={name_} byLianPi={byLianPi} byTongJin={byTongJin} byQiangJi={byQiangJi} byDuanGu={byDuanGu} byHuoLuo={byHuoLuo}
				 byXiSui={byXiSui}/>;
			else
				topXml = <SCTData byLianPi={byLianPi} byTongJin={byTongJin} byQiangJi={byQiangJi} byDuanGu={byDuanGu} byHuoLuo={byHuoLuo}
				 byXiSui={byXiSui}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byLianPi = byLianPi;
			obj_.byTongJin = byTongJin;
			obj_.byQiangJi = byQiangJi;
			obj_.byDuanGu = byDuanGu;
			obj_.byHuoLuo = byHuoLuo;
			obj_.byXiSui = byXiSui;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCTData
		{
			var s_:SCTData = new SCTData();
			var byLianPi:uint = bytes.readUnsignedByte();
			s_.byLianPi = byLianPi;
			var byTongJin:uint = bytes.readUnsignedByte();
			s_.byTongJin = byTongJin;
			var byQiangJi:uint = bytes.readUnsignedByte();
			s_.byQiangJi = byQiangJi;
			var byDuanGu:uint = bytes.readUnsignedByte();
			s_.byDuanGu = byDuanGu;
			var byHuoLuo:uint = bytes.readUnsignedByte();
			s_.byHuoLuo = byHuoLuo;
			var byXiSui:uint = bytes.readUnsignedByte();
			s_.byXiSui = byXiSui;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCTData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCTData> = new Vector.<SCTData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCTData = SCTData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byLianPi);
			bytes.writeByte(byTongJin);
			bytes.writeByte(byQiangJi);
			bytes.writeByte(byDuanGu);
			bytes.writeByte(byHuoLuo);
			bytes.writeByte(byXiSui);
		}

		public static function vectorToByteArray(vec:Vector.<SCTData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCTData in vec)
				s.toByteArray(bytes);
		}
	}
}
