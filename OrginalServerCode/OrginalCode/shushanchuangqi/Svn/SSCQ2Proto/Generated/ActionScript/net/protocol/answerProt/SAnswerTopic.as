/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAnswerTopic.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 答题题目信息
	 */
	public final class SAnswerTopic
	{
		public var byIndex:uint; //(无符号8位整数)编号
		public var dwTopicID:uint; //(无符号32位整数)题目ID
		public var byAnswer1:uint; //(无符号8位整数)答案1
		public var byAnswer2:uint; //(无符号8位整数)答案2
		public var byAnswer3:uint; //(无符号8位整数)答案3
		public var byAnswer4:uint; //(无符号8位整数)答案4
		public var sTimeInfo:SAnswerTime; //题目时间
		public var dwRemain:uint; //(无符号32位整数)剩余题目数

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, dwTopicID:uint, byAnswer1:uint, byAnswer2:uint, byAnswer3:uint, 
			byAnswer4:uint, sTimeInfo:SAnswerTime, dwRemain:uint):SAnswerTopic
		{
			var s_:SAnswerTopic = new SAnswerTopic();
			s_.byIndex = byIndex;
			s_.dwTopicID = dwTopicID;
			s_.byAnswer1 = byAnswer1;
			s_.byAnswer2 = byAnswer2;
			s_.byAnswer3 = byAnswer3;
			s_.byAnswer4 = byAnswer4;
			s_.sTimeInfo = sTimeInfo;
			s_.dwRemain = dwRemain;
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
				topXml = <SAnswerTopic _name_={name_} byIndex={byIndex} dwTopicID={dwTopicID} byAnswer1={byAnswer1} byAnswer2={byAnswer2} byAnswer3={byAnswer3}
				 byAnswer4={byAnswer4} dwRemain={dwRemain}/>;
			else
				topXml = <SAnswerTopic byIndex={byIndex} dwTopicID={dwTopicID} byAnswer1={byAnswer1} byAnswer2={byAnswer2} byAnswer3={byAnswer3}
				 byAnswer4={byAnswer4} dwRemain={dwRemain}/>;
			if(sTimeInfo != null)
				topXml.appendChild(sTimeInfo.toXML("sTimeInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.dwTopicID = dwTopicID;
			obj_.byAnswer1 = byAnswer1;
			obj_.byAnswer2 = byAnswer2;
			obj_.byAnswer3 = byAnswer3;
			obj_.byAnswer4 = byAnswer4;
			obj_.sTimeInfo = sTimeInfo;
			obj_.dwRemain = dwRemain;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAnswerTopic
		{
			var s_:SAnswerTopic = new SAnswerTopic();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var dwTopicID:uint = bytes.readUnsignedInt();
			s_.dwTopicID = dwTopicID;
			var byAnswer1:uint = bytes.readUnsignedByte();
			s_.byAnswer1 = byAnswer1;
			var byAnswer2:uint = bytes.readUnsignedByte();
			s_.byAnswer2 = byAnswer2;
			var byAnswer3:uint = bytes.readUnsignedByte();
			s_.byAnswer3 = byAnswer3;
			var byAnswer4:uint = bytes.readUnsignedByte();
			s_.byAnswer4 = byAnswer4;
			var sTimeInfo:SAnswerTime = SAnswerTime.fromByteArray(bytes);
			s_.sTimeInfo = sTimeInfo;
			var dwRemain:uint = bytes.readUnsignedInt();
			s_.dwRemain = dwRemain;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAnswerTopic>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAnswerTopic> = new Vector.<SAnswerTopic>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAnswerTopic = SAnswerTopic.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			bytes.writeUnsignedInt(dwTopicID);
			bytes.writeByte(byAnswer1);
			bytes.writeByte(byAnswer2);
			bytes.writeByte(byAnswer3);
			bytes.writeByte(byAnswer4);
			sTimeInfo.toByteArray(bytes);
			bytes.writeUnsignedInt(dwRemain);
		}

		public static function vectorToByteArray(vec:Vector.<SAnswerTopic>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAnswerTopic in vec)
				s.toByteArray(bytes);
		}
	}
}
