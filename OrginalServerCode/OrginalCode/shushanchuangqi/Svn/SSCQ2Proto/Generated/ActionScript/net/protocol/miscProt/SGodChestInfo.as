/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGodChestInfo.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 刷宝箱信息
	 */
	public final class SGodChestInfo
	{
		public var byState:uint; //(无符号8位整数)状态
		public var byRount:uint; //(无符号8位整数)回合数
		public var dwTime:uint; //(无符号32位整数)倒计时数
		public var dwEnd:uint; //(无符号32位整数)活动结束时间

		/**
		 * 辅助创建函数
		 */
		public static function create(byState:uint, byRount:uint, dwTime:uint, dwEnd:uint):SGodChestInfo
		{
			var s_:SGodChestInfo = new SGodChestInfo();
			s_.byState = byState;
			s_.byRount = byRount;
			s_.dwTime = dwTime;
			s_.dwEnd = dwEnd;
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
				topXml = <SGodChestInfo _name_={name_} byState={byState} byRount={byRount} dwTime={dwTime} dwEnd={dwEnd}/>;
			else
				topXml = <SGodChestInfo byState={byState} byRount={byRount} dwTime={dwTime} dwEnd={dwEnd}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byState = byState;
			obj_.byRount = byRount;
			obj_.dwTime = dwTime;
			obj_.dwEnd = dwEnd;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGodChestInfo
		{
			var s_:SGodChestInfo = new SGodChestInfo();
			var byState:uint = bytes.readUnsignedByte();
			s_.byState = byState;
			var byRount:uint = bytes.readUnsignedByte();
			s_.byRount = byRount;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var dwEnd:uint = bytes.readUnsignedInt();
			s_.dwEnd = dwEnd;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGodChestInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGodChestInfo> = new Vector.<SGodChestInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGodChestInfo = SGodChestInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byState);
			bytes.writeByte(byRount);
			bytes.writeUnsignedInt(dwTime);
			bytes.writeUnsignedInt(dwEnd);
		}

		public static function vectorToByteArray(vec:Vector.<SGodChestInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGodChestInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
