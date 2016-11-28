/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMailDetail.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 邮件详细信息
	 */
	public final class SMailDetail
	{
		public var qwMailID:BigInteger; //(无符号64位整数)邮件ID
		public var eMailState:uint; //(枚举类型：EMailState)邮件状态
		public var dwSendTime:uint; //(无符号32位整数)邮件发送时间
		public var byGeted:uint; //(无符号8位整数)255表示有附件，并且已经领取，其他为按位表示有附件的类型
		public var eMailType:uint; //(枚举类型：EMailType)邮件类型
		public var vecMailAttachment:Vector.<SMailBaseAttachment>; //附件
		public var strTitle:String; //邮件标题
		public var strSendName:String; //发送者
		public var strMessage:String; //信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwMailID:BigInteger, eMailState:uint, dwSendTime:uint, byGeted:uint, eMailType:uint, 
			vecMailAttachment:Vector.<SMailBaseAttachment>, strTitle:String, strSendName:String, strMessage:String):SMailDetail
		{
			var s_:SMailDetail = new SMailDetail();
			s_.qwMailID = qwMailID;
			s_.eMailState = eMailState;
			s_.dwSendTime = dwSendTime;
			s_.byGeted = byGeted;
			s_.eMailType = eMailType;
			s_.vecMailAttachment = vecMailAttachment;
			s_.strTitle = strTitle;
			s_.strSendName = strSendName;
			s_.strMessage = strMessage;
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
				topXml = <SMailDetail _name_={name_} qwMailID={qwMailID} eMailState={eMailState} dwSendTime={dwSendTime} byGeted={byGeted} eMailType={eMailType} strTitle={strTitle} strSendName={strSendName} strMessage={strMessage}/>;
			else
				topXml = <SMailDetail qwMailID={qwMailID} eMailState={eMailState} dwSendTime={dwSendTime} byGeted={byGeted} eMailType={eMailType} strTitle={strTitle} strSendName={strSendName} strMessage={strMessage}/>;
			if(vecMailAttachment != null)
			{
				var vecMailAttachmentXml:XML = <Vec_SMailBaseAttachment _name_="vecMailAttachment"/>;
				for each(var s1:SMailBaseAttachment in vecMailAttachment)
					vecMailAttachmentXml.appendChild(s1.toXML());
				topXml.appendChild(vecMailAttachmentXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwMailID = qwMailID;
			obj_.eMailState = eMailState;
			obj_.dwSendTime = dwSendTime;
			obj_.byGeted = byGeted;
			obj_.eMailType = eMailType;
			obj_.vecMailAttachment = vecMailAttachment;
			obj_.strTitle = strTitle;
			obj_.strSendName = strSendName;
			obj_.strMessage = strMessage;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMailDetail
		{
			var s_:SMailDetail = new SMailDetail();
			var qwMailID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwMailID = qwMailID;
			var eMailState:uint = bytes.readUnsignedByte();
			s_.eMailState = eMailState;
			var dwSendTime:uint = bytes.readUnsignedInt();
			s_.dwSendTime = dwSendTime;
			var byGeted:uint = bytes.readUnsignedByte();
			s_.byGeted = byGeted;
			var eMailType:uint = bytes.readUnsignedByte();
			s_.eMailType = eMailType;
			var vecMailAttachment:Vector.<SMailBaseAttachment> = SMailBaseAttachment.superVectorFromByteArray(bytes);
			s_.vecMailAttachment = vecMailAttachment;
			var strTitle:String = BytesUtil.readString(bytes);
			s_.strTitle = strTitle;
			var strSendName:String = BytesUtil.readString(bytes);
			s_.strSendName = strSendName;
			var strMessage:String = BytesUtil.readString(bytes);
			s_.strMessage = strMessage;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMailDetail>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMailDetail> = new Vector.<SMailDetail>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMailDetail = SMailDetail.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwMailID);
			bytes.writeByte(eMailState);
			bytes.writeUnsignedInt(dwSendTime);
			bytes.writeByte(byGeted);
			bytes.writeByte(eMailType);
			SMailBaseAttachment.superVectorToByteArray(vecMailAttachment, bytes);
			BytesUtil.writeString(bytes, strTitle);
			BytesUtil.writeString(bytes, strSendName);
			BytesUtil.writeString(bytes, strMessage);
		}

		public static function vectorToByteArray(vec:Vector.<SMailDetail>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMailDetail in vec)
				s.toByteArray(bytes);
		}
	}
}
