/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBeastSoulData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import net.protocol.roleInfoDefine.SBeastSoulInfo;
	import net.protocol.protoCommon.SFtAttrMod;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 兽魂
	 */
	public final class SBeastSoulData
	{
		public var vecBeasSoulInfo:Vector.<SBeastSoulInfo>; //兽魂
		public var vecAttr:Vector.<SFtAttrMod>; //兽魂属性

		/**
		 * 辅助创建函数
		 */
		public static function create(vecBeasSoulInfo:Vector.<SBeastSoulInfo>, vecAttr:Vector.<SFtAttrMod>):SBeastSoulData
		{
			var s_:SBeastSoulData = new SBeastSoulData();
			s_.vecBeasSoulInfo = vecBeasSoulInfo;
			s_.vecAttr = vecAttr;
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
				topXml = <SBeastSoulData _name_={name_}/>;
			else
				topXml = <SBeastSoulData/>;
			if(vecBeasSoulInfo != null)
			{
				var vecBeasSoulInfoXml:XML = <Vec_SBeastSoulInfo _name_="vecBeasSoulInfo"/>;
				for each(var s1:SBeastSoulInfo in vecBeasSoulInfo)
					vecBeasSoulInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBeasSoulInfoXml);
			}
			if(vecAttr != null)
			{
				var vecAttrXml:XML = <Vec_SFtAttrMod _name_="vecAttr"/>;
				for each(var s2:SFtAttrMod in vecAttr)
					vecAttrXml.appendChild(s2.toXML());
				topXml.appendChild(vecAttrXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecBeasSoulInfo = vecBeasSoulInfo;
			obj_.vecAttr = vecAttr;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBeastSoulData
		{
			var s_:SBeastSoulData = new SBeastSoulData();
			var vecBeasSoulInfo:Vector.<SBeastSoulInfo> = SBeastSoulInfo.vectorFromByteArray(bytes);
			s_.vecBeasSoulInfo = vecBeasSoulInfo;
			var vecAttr:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.vecAttr = vecAttr;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBeastSoulData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBeastSoulData> = new Vector.<SBeastSoulData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBeastSoulData = SBeastSoulData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			SBeastSoulInfo.vectorToByteArray(vecBeasSoulInfo, bytes);
			SFtAttrMod.vectorToByteArray(vecAttr, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBeastSoulData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBeastSoulData in vec)
				s.toByteArray(bytes);
		}
	}
}
