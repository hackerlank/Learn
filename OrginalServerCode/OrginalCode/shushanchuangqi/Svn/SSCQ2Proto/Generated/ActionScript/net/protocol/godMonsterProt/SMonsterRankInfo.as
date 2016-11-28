/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMonsterRankInfo.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行榜数据
	 */
	public final class SMonsterRankInfo
	{
		public var dwRank:uint; //(无符号32位整数)排名
		public var strName:String; //名字
		public var dwScore:uint; //(无符号32位整数)积分

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRank:uint, strName:String, dwScore:uint):SMonsterRankInfo
		{
			var s_:SMonsterRankInfo = new SMonsterRankInfo();
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
				topXml = <SMonsterRankInfo _name_={name_} dwRank={dwRank} strName={strName} dwScore={dwScore}/>;
			else
				topXml = <SMonsterRankInfo dwRank={dwRank} strName={strName} dwScore={dwScore}/>;
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

		public static function fromByteArray(bytes:ByteArray):SMonsterRankInfo
		{
			var s_:SMonsterRankInfo = new SMonsterRankInfo();
			var dwRank:uint = bytes.readUnsignedInt();
			s_.dwRank = dwRank;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMonsterRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMonsterRankInfo> = new Vector.<SMonsterRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMonsterRankInfo = SMonsterRankInfo.fromByteArray(bytes);
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

		public static function vectorToByteArray(vec:Vector.<SMonsterRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMonsterRankInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
