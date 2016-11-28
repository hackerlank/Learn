/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMailSummary.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 邮件摘要列表
	 */
	public final class SMailSummary
	{
		public var uMailID:BigInteger; //(无符号64位整数)邮件ID
		public var eMailType:uint; //(枚举类型：EMailType)邮件类型
		public var eMailState:uint; //(枚举类型：EMailState)邮件状态
		public var uSendTime:uint; //(无符号32位整数)邮件发送时间
		public var byHasAttachment:uint; //(无符号8位整数)0:没有   1:有
		public var strTitle:String; //邮件标题
		public var strSendName:String; //发送者

		/**
		 * 辅助创建函数
		 */
		public static function create(uMailID:BigInteger, eMailType:uint, eMailState:uint, uSendTime:uint, byHasAttachment:uint, 
			strTitle:String, strSendName:String):SMailSummary
		{
			var s_:SMailSummary = new SMailSummary();
			s_.uMailID = uMailID;
			s_.eMailType = eMailType;
			s_.eMailState = eMailState;
			s_.uSendTime = uSendTime;
			s_.byHasAttachment = byHasAttachment;
			s_.strTitle = strTitle;
			s_.strSendName = strSendName;
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
				topXml = <SMailSummary _name_={name_} uMailID={uMailID} eMailType={eMailType} eMailState={eMailState} uSendTime={uSendTime} byHasAttachment={byHasAttachment}
				 strTitle={strTitle} strSendName={strSendName}/>;
			else
				topXml = <SMailSummary uMailID={uMailID} eMailType={eMailType} eMailState={eMailState} uSendTime={uSendTime} byHasAttachment={byHasAttachment}
				 strTitle={strTitle} strSendName={strSendName}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.uMailID = uMailID;
			obj_.eMailType = eMailType;
			obj_.eMailState = eMailState;
			obj_.uSendTime = uSendTime;
			obj_.byHasAttachment = byHasAttachment;
			obj_.strTitle = strTitle;
			obj_.strSendName = strSendName;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMailSummary
		{
			var s_:SMailSummary = new SMailSummary();
			var uMailID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.uMailID = uMailID;
			var eMailType:uint = bytes.readUnsignedByte();
			s_.eMailType = eMailType;
			var eMailState:uint = bytes.readUnsignedByte();
			s_.eMailState = eMailState;
			var uSendTime:uint = bytes.readUnsignedInt();
			s_.uSendTime = uSendTime;
			var byHasAttachment:uint = bytes.readUnsignedByte();
			s_.byHasAttachment = byHasAttachment;
			var strTitle:String = BytesUtil.readString(bytes);
			s_.strTitle = strTitle;
			var strSendName:String = BytesUtil.readString(bytes);
			s_.strSendName = strSendName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMailSummary>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMailSummary> = new Vector.<SMailSummary>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMailSummary = SMailSummary.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, uMailID);
			bytes.writeByte(eMailType);
			bytes.writeByte(eMailState);
			bytes.writeUnsignedInt(uSendTime);
			bytes.writeByte(byHasAttachment);
			BytesUtil.writeString(bytes, strTitle);
			BytesUtil.writeString(bytes, strSendName);
		}

		public static function vectorToByteArray(vec:Vector.<SMailSummary>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMailSummary in vec)
				s.toByteArray(bytes);
		}
	}
}
