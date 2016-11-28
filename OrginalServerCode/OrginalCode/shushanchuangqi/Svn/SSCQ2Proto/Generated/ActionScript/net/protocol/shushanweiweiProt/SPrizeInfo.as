/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrizeInfo.as
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanweiweiProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 奖励信息
	 */
	public final class SPrizeInfo
	{
		public var eType:uint; //(枚举类型：EPkgType)奖励类型
		public var dwCount:uint; //(无符号32位整数)当前人数
		public var bListen:Boolean; //微博是否收听
		public var bResult:Boolean; //个人奖励是否领取
		public var wResult:uint; //(无符号16位整数)全服奖励领取结果

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, dwCount:uint, bListen:Boolean, bResult:Boolean, wResult:uint):SPrizeInfo
		{
			var s_:SPrizeInfo = new SPrizeInfo();
			s_.eType = eType;
			s_.dwCount = dwCount;
			s_.bListen = bListen;
			s_.bResult = bResult;
			s_.wResult = wResult;
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
				topXml = <SPrizeInfo _name_={name_} eType={eType} dwCount={dwCount} bListen={bListen} bResult={bResult} wResult={wResult}/>;
			else
				topXml = <SPrizeInfo eType={eType} dwCount={dwCount} bListen={bListen} bResult={bResult} wResult={wResult}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.dwCount = dwCount;
			obj_.bListen = bListen;
			obj_.bResult = bResult;
			obj_.wResult = wResult;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrizeInfo
		{
			var s_:SPrizeInfo = new SPrizeInfo();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var bListen:Boolean = bytes.readBoolean();
			s_.bListen = bListen;
			var bResult:Boolean = bytes.readBoolean();
			s_.bResult = bResult;
			var wResult:uint = bytes.readUnsignedShort();
			s_.wResult = wResult;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrizeInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrizeInfo> = new Vector.<SPrizeInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrizeInfo = SPrizeInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeBoolean(bListen);
			bytes.writeBoolean(bResult);
			bytes.writeShort(wResult);
		}

		public static function vectorToByteArray(vec:Vector.<SPrizeInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrizeInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
