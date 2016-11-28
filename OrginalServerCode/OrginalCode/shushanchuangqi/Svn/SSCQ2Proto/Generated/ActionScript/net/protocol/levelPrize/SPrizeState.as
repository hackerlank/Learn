/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrizeState.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 奖励状态
	 */
	public final class SPrizeState
	{
		public var byIndex:uint; //(无符号8位整数)领奖
		public var eStatus:uint; //(枚举类型：ELevelActStatus)奖励状态

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, eStatus:uint):SPrizeState
		{
			var s_:SPrizeState = new SPrizeState();
			s_.byIndex = byIndex;
			s_.eStatus = eStatus;
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
				topXml = <SPrizeState _name_={name_} byIndex={byIndex} eStatus={eStatus}/>;
			else
				topXml = <SPrizeState byIndex={byIndex} eStatus={eStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.eStatus = eStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrizeState
		{
			var s_:SPrizeState = new SPrizeState();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var eStatus:uint = bytes.readUnsignedByte();
			s_.eStatus = eStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrizeState>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrizeState> = new Vector.<SPrizeState>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrizeState = SPrizeState.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			bytes.writeByte(eStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SPrizeState>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrizeState in vec)
				s.toByteArray(bytes);
		}
	}
}
