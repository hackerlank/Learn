/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLotteryInfo.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 抽奖信息
	 */
	public final class SLotteryInfo
	{
		public var strName:String; //玩家
		public var dwLotteryID:uint; //(无符号32位整数)奖励ID(对应配置表)

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, dwLotteryID:uint):SLotteryInfo
		{
			var s_:SLotteryInfo = new SLotteryInfo();
			s_.strName = strName;
			s_.dwLotteryID = dwLotteryID;
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
				topXml = <SLotteryInfo _name_={name_} strName={strName} dwLotteryID={dwLotteryID}/>;
			else
				topXml = <SLotteryInfo strName={strName} dwLotteryID={dwLotteryID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strName = strName;
			obj_.dwLotteryID = dwLotteryID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLotteryInfo
		{
			var s_:SLotteryInfo = new SLotteryInfo();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwLotteryID:uint = bytes.readUnsignedInt();
			s_.dwLotteryID = dwLotteryID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLotteryInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLotteryInfo> = new Vector.<SLotteryInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLotteryInfo = SLotteryInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwLotteryID);
		}

		public static function vectorToByteArray(vec:Vector.<SLotteryInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLotteryInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
