/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDBBubbleInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 气泡信息
	 */
	public final class SDBBubbleInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var qwTransID:BigInteger; //(无符号64位整数)唯一流水ID
		public var wMsgID:uint; //(无符号16位整数)气泡ID
		public var dwTime:uint; //(无符号32位整数)气泡时间
		public var vecParam:Vector.<BigInteger>; //(有符号64位整数)整型变量
		public var vecString:Vector.<String>; //字符串型变量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwTransID:BigInteger, wMsgID:uint, dwTime:uint, vecParam:Vector.<BigInteger>, 
			vecString:Vector.<String>):SDBBubbleInfo
		{
			var s_:SDBBubbleInfo = new SDBBubbleInfo();
			s_.qwRoleID = qwRoleID;
			s_.qwTransID = qwTransID;
			s_.wMsgID = wMsgID;
			s_.dwTime = dwTime;
			s_.vecParam = vecParam;
			s_.vecString = vecString;
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
				topXml = <SDBBubbleInfo _name_={name_} qwRoleID={qwRoleID} qwTransID={qwTransID} wMsgID={wMsgID} dwTime={dwTime}/>;
			else
				topXml = <SDBBubbleInfo qwRoleID={qwRoleID} qwTransID={qwTransID} wMsgID={wMsgID} dwTime={dwTime}/>;
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
			obj_.qwTransID = qwTransID;
			obj_.wMsgID = wMsgID;
			obj_.dwTime = dwTime;
			obj_.vecParam = vecParam;
			obj_.vecString = vecString;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDBBubbleInfo
		{
			var s_:SDBBubbleInfo = new SDBBubbleInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwTransID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwTransID = qwTransID;
			var wMsgID:uint = bytes.readUnsignedShort();
			s_.wMsgID = wMsgID;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var vecParam:Vector.<BigInteger> = BytesUtil.readVecInt64(bytes);
			s_.vecParam = vecParam;
			var vecString:Vector.<String> = BytesUtil.readVecString(bytes);
			s_.vecString = vecString;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDBBubbleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDBBubbleInfo> = new Vector.<SDBBubbleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDBBubbleInfo = SDBBubbleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwTransID);
			bytes.writeShort(wMsgID);
			bytes.writeUnsignedInt(dwTime);
			BytesUtil.writeVecInt64(bytes, vecParam);
			BytesUtil.writeVecString(bytes, vecString);
		}

		public static function vectorToByteArray(vec:Vector.<SDBBubbleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDBBubbleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
