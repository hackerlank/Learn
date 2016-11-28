/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SysMailSendTxt.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 系统邮件标题，及其内容
	 */
	public final class SysMailSendTxt
	{
		public var dwstrMsgID:uint; //(无符号32位整数)消息ID
		public var vecParam:Vector.<String>; //参数列表

		/**
		 * 辅助创建函数
		 */
		public static function create(dwstrMsgID:uint, vecParam:Vector.<String>):SysMailSendTxt
		{
			var s_:SysMailSendTxt = new SysMailSendTxt();
			s_.dwstrMsgID = dwstrMsgID;
			s_.vecParam = vecParam;
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
				topXml = <SysMailSendTxt _name_={name_} dwstrMsgID={dwstrMsgID}/>;
			else
				topXml = <SysMailSendTxt dwstrMsgID={dwstrMsgID}/>;
			if(vecParam != null)
			{
				var vecParamXml:XML = <Vec_string _name_="vecParam"/>;
				var text1:String = "";
				for each(var value1:String in vecParam)
					text1 += "[" + value1 + "]";
				vecParamXml.appendChild(text1);
				topXml.appendChild(vecParamXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwstrMsgID = dwstrMsgID;
			obj_.vecParam = vecParam;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SysMailSendTxt
		{
			var s_:SysMailSendTxt = new SysMailSendTxt();
			var dwstrMsgID:uint = bytes.readUnsignedInt();
			s_.dwstrMsgID = dwstrMsgID;
			var vecParam:Vector.<String> = BytesUtil.readVecString(bytes);
			s_.vecParam = vecParam;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SysMailSendTxt>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SysMailSendTxt> = new Vector.<SysMailSendTxt>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SysMailSendTxt = SysMailSendTxt.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwstrMsgID);
			BytesUtil.writeVecString(bytes, vecParam);
		}

		public static function vectorToByteArray(vec:Vector.<SysMailSendTxt>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SysMailSendTxt in vec)
				s.toByteArray(bytes);
		}
	}
}
