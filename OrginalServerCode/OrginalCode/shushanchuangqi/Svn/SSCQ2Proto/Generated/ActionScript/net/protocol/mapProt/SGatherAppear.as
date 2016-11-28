/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGatherAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 采集物的外观
	 */
	public final class SGatherAppear
	{
		public var wGatherID:uint; //(无符号16位整数)采集物类型ID
		public var wTotalNum:uint; //(无符号16位整数)采集总次数,特别的为-1表示，采集无数次,以下两个字段始终为0
		public var wReserverNum:uint; //(无符号16位整数)采集剩余次数
		public var wGatheringNum:uint; //(无符号16位整数)正在采集的人次

		/**
		 * 辅助创建函数
		 */
		public static function create(wGatherID:uint, wTotalNum:uint, wReserverNum:uint, wGatheringNum:uint):SGatherAppear
		{
			var s_:SGatherAppear = new SGatherAppear();
			s_.wGatherID = wGatherID;
			s_.wTotalNum = wTotalNum;
			s_.wReserverNum = wReserverNum;
			s_.wGatheringNum = wGatheringNum;
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
				topXml = <SGatherAppear _name_={name_} wGatherID={wGatherID} wTotalNum={wTotalNum} wReserverNum={wReserverNum} wGatheringNum={wGatheringNum}/>;
			else
				topXml = <SGatherAppear wGatherID={wGatherID} wTotalNum={wTotalNum} wReserverNum={wReserverNum} wGatheringNum={wGatheringNum}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wGatherID = wGatherID;
			obj_.wTotalNum = wTotalNum;
			obj_.wReserverNum = wReserverNum;
			obj_.wGatheringNum = wGatheringNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGatherAppear
		{
			var s_:SGatherAppear = new SGatherAppear();
			var wGatherID:uint = bytes.readUnsignedShort();
			s_.wGatherID = wGatherID;
			var wTotalNum:uint = bytes.readUnsignedShort();
			s_.wTotalNum = wTotalNum;
			var wReserverNum:uint = bytes.readUnsignedShort();
			s_.wReserverNum = wReserverNum;
			var wGatheringNum:uint = bytes.readUnsignedShort();
			s_.wGatheringNum = wGatheringNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGatherAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGatherAppear> = new Vector.<SGatherAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGatherAppear = SGatherAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wGatherID);
			bytes.writeShort(wTotalNum);
			bytes.writeShort(wReserverNum);
			bytes.writeShort(wGatheringNum);
		}

		public static function vectorToByteArray(vec:Vector.<SGatherAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGatherAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
