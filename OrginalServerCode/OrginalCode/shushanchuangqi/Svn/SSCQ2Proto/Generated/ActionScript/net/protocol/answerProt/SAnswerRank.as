/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAnswerRank.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排名信息
	 */
	public final class SAnswerRank
	{
		public var dwRank:uint; //(无符号32位整数)玩家排名
		public var strName:String; //玩家名字
		public var dwScore:uint; //(无符号32位整数)玩家积分

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRank:uint, strName:String, dwScore:uint):SAnswerRank
		{
			var s_:SAnswerRank = new SAnswerRank();
			s_.dwRank = dwRank;
			s_.strName = strName;
			s_.dwScore = dwScore;
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
				topXml = <SAnswerRank _name_={name_} dwRank={dwRank} strName={strName} dwScore={dwScore}/>;
			else
				topXml = <SAnswerRank dwRank={dwRank} strName={strName} dwScore={dwScore}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwRank = dwRank;
			obj_.strName = strName;
			obj_.dwScore = dwScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAnswerRank
		{
			var s_:SAnswerRank = new SAnswerRank();
			var dwRank:uint = bytes.readUnsignedInt();
			s_.dwRank = dwRank;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAnswerRank>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAnswerRank> = new Vector.<SAnswerRank>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAnswerRank = SAnswerRank.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwRank);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwScore);
		}

		public static function vectorToByteArray(vec:Vector.<SAnswerRank>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAnswerRank in vec)
				s.toByteArray(bytes);
		}
	}
}
