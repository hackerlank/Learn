/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildLogInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 日志
	 */
	public final class SGuildLogInfo extends SGuildInfoBase
	{
		public var qwInstID:BigInteger; //(无符号64位整数)唯一流水ID
		public var eType:uint; //(枚举类型：ELogType)日志类型
		public var wMsgID:uint; //(无符号16位整数)消息ID
		public var vecParam:Vector.<BigInteger>; //(有符号64位整数)整型变量
		public var vecString:Vector.<String>; //字符串型变量
		public var dwTime:uint; //(无符号32位整数)日志时间

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildLogInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildLogInfo _name_={name_} qwInstID={qwInstID} eType={eType} wMsgID={wMsgID}
				 dwTime={dwTime}/>;
			else
				topXml = <SGuildLogInfo qwInstID={qwInstID} eType={eType} wMsgID={wMsgID}
				 dwTime={dwTime}/>;
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
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.qwInstID = qwInstID;
			obj_.eType = eType;
			obj_.wMsgID = wMsgID;
			obj_.vecParam = vecParam;
			obj_.vecString = vecString;
			obj_.dwTime = dwTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildLogInfo
		{
			var s_:SGuildLogInfo = new SGuildLogInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
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

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildLogInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildLogInfo> = new Vector.<SGuildLogInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildLogInfo = SGuildLogInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeByte(eType);
			bytes.writeShort(wMsgID);
			BytesUtil.writeVecInt64(bytes, vecParam);
			BytesUtil.writeVecString(bytes, vecString);
			bytes.writeUnsignedInt(dwTime);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildLogInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildLogInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
