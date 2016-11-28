/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STripodLog.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 九疑鼎历史日志
	 */
	public final class STripodLog
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)九疑鼎的所属玩家的ID
		public var wMsgID:uint; //(无符号16位整数)对应日志ID（详见Message）
		public var vecParam:Vector.<BigInteger>; //(有符号64位整数)整型变量
		public var vecString:Vector.<String>; //字符串型变量
		public var dwTime:uint; //(无符号32位整数)日志时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wMsgID:uint, vecParam:Vector.<BigInteger>, vecString:Vector.<String>, dwTime:uint):STripodLog
		{
			var s_:STripodLog = new STripodLog();
			s_.qwRoleID = qwRoleID;
			s_.wMsgID = wMsgID;
			s_.vecParam = vecParam;
			s_.vecString = vecString;
			s_.dwTime = dwTime;
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
				topXml = <STripodLog _name_={name_} qwRoleID={qwRoleID} wMsgID={wMsgID} dwTime={dwTime}/>;
			else
				topXml = <STripodLog qwRoleID={qwRoleID} wMsgID={wMsgID} dwTime={dwTime}/>;
			if(vecParam != null)
			{
				var vecParamXml:XML = <Vec_INT64 _name_="vecParam"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecParam)
					text1 += "[" + value1 + "]";
				vecParamXml.appendChild(text1);
				topXml.appendChild(vecParamXml);
			}
			if(vecString != null)
			{
				var vecStringXml:XML = <Vec_string _name_="vecString"/>;
				var text2:String = "";
				for each(var value2:String in vecString)
					text2 += "[" + value2 + "]";
				vecStringXml.appendChild(text2);
				topXml.appendChild(vecStringXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wMsgID = wMsgID;
			obj_.vecParam = vecParam;
			obj_.vecString = vecString;
			obj_.dwTime = dwTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STripodLog
		{
			var s_:STripodLog = new STripodLog();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wMsgID:uint = bytes.readUnsignedShort();
			s_.wMsgID = wMsgID;
			var vecParam:Vector.<BigInteger> = BytesUtil.readVecInt64(bytes);
			s_.vecParam = vecParam;
			var vecString:Vector.<String> = BytesUtil.readVecString(bytes);
			s_.vecString = vecString;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STripodLog>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STripodLog> = new Vector.<STripodLog>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STripodLog = STripodLog.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wMsgID);
			BytesUtil.writeVecInt64(bytes, vecParam);
			BytesUtil.writeVecString(bytes, vecString);
			bytes.writeUnsignedInt(dwTime);
		}

		public static function vectorToByteArray(vec:Vector.<STripodLog>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STripodLog in vec)
				s.toByteArray(bytes);
		}
	}
}
