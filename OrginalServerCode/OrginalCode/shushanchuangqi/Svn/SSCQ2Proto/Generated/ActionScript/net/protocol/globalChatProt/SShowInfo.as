/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SShowInfo.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 炫耀信息
	 */
	public final class SShowInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)唯一ID
		public var strShowInfo:ByteArray; //展示信息序列化

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, strShowInfo:ByteArray):SShowInfo
		{
			var s_:SShowInfo = new SShowInfo();
			s_.qwInstID = qwInstID;
			s_.strShowInfo = strShowInfo;
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
				topXml = <SShowInfo _name_={name_} qwInstID={qwInstID} strShowInfo={BytesUtil.bytes2String(strShowInfo)}/>;
			else
				topXml = <SShowInfo qwInstID={qwInstID} strShowInfo={BytesUtil.bytes2String(strShowInfo)}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.strShowInfo = strShowInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SShowInfo
		{
			var s_:SShowInfo = new SShowInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var strShowInfo:ByteArray = BytesUtil.readBytes(bytes);
			s_.strShowInfo = strShowInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SShowInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SShowInfo> = new Vector.<SShowInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SShowInfo = SShowInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			BytesUtil.writeBytes(bytes, strShowInfo);
		}

		public static function vectorToByteArray(vec:Vector.<SShowInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SShowInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
