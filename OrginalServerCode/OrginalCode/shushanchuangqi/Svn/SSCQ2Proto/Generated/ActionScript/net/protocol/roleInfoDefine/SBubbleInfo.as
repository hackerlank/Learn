/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBubbleInfo.as
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
	public final class SBubbleInfo
	{
		public var wMsgID:uint; //(无符号16位整数)气泡ID
		public var wMessageID:uint; //(无符号16位整数)消息ID
		public var byIndex:uint; //(无符号8位整数)气泡位置
		public var dwTime:uint; //(无符号32位整数)气泡时间
		public var vecParam:Vector.<BigInteger>; //(有符号64位整数)整型变量
		public var vecString:Vector.<String>; //字符串型变量

		/**
		 * 辅助创建函数
		 */
		public static function create(wMsgID:uint, wMessageID:uint, byIndex:uint, dwTime:uint, vecParam:Vector.<BigInteger>, 
			vecString:Vector.<String>):SBubbleInfo
		{
			var s_:SBubbleInfo = new SBubbleInfo();
			s_.wMsgID = wMsgID;
			s_.wMessageID = wMessageID;
			s_.byIndex = byIndex;
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
				topXml = <SBubbleInfo _name_={name_} wMsgID={wMsgID} wMessageID={wMessageID} byIndex={byIndex} dwTime={dwTime}/>;
			else
				topXml = <SBubbleInfo wMsgID={wMsgID} wMessageID={wMessageID} byIndex={byIndex} dwTime={dwTime}/>;
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
			obj_.wMsgID = wMsgID;
			obj_.wMessageID = wMessageID;
			obj_.byIndex = byIndex;
			obj_.dwTime = dwTime;
			obj_.vecParam = vecParam;
			obj_.vecString = vecString;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBubbleInfo
		{
			var s_:SBubbleInfo = new SBubbleInfo();
			var wMsgID:uint = bytes.readUnsignedShort();
			s_.wMsgID = wMsgID;
			var wMessageID:uint = bytes.readUnsignedShort();
			s_.wMessageID = wMessageID;
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var vecParam:Vector.<BigInteger> = BytesUtil.readVecInt64(bytes);
			s_.vecParam = vecParam;
			var vecString:Vector.<String> = BytesUtil.readVecString(bytes);
			s_.vecString = vecString;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBubbleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBubbleInfo> = new Vector.<SBubbleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBubbleInfo = SBubbleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wMsgID);
			bytes.writeShort(wMessageID);
			bytes.writeByte(byIndex);
			bytes.writeUnsignedInt(dwTime);
			BytesUtil.writeVecInt64(bytes, vecParam);
			BytesUtil.writeVecString(bytes, vecString);
		}

		public static function vectorToByteArray(vec:Vector.<SBubbleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBubbleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
