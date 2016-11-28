/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMonsterRank.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行榜
	 */
	public final class SMonsterRank
	{
		public var eRank:uint; //(枚举类型：EMonsterRank)排名
		public var vecRankInfo:Vector.<SMonsterRankInfo>; //数据

		/**
		 * 辅助创建函数
		 */
		public static function create(eRank:uint, vecRankInfo:Vector.<SMonsterRankInfo>):SMonsterRank
		{
			var s_:SMonsterRank = new SMonsterRank();
			s_.eRank = eRank;
			s_.vecRankInfo = vecRankInfo;
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
				topXml = <SMonsterRank _name_={name_} eRank={eRank}/>;
			else
				topXml = <SMonsterRank eRank={eRank}/>;
			if(vecRankInfo != null)
			{
				var vecRankInfoXml:XML = <Vec_SMonsterRankInfo _name_="vecRankInfo"/>;
				for each(var s1:SMonsterRankInfo in vecRankInfo)
					vecRankInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecRankInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eRank = eRank;
			obj_.vecRankInfo = vecRankInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMonsterRank
		{
			var s_:SMonsterRank = new SMonsterRank();
			var eRank:uint = bytes.readUnsignedByte();
			s_.eRank = eRank;
			var vecRankInfo:Vector.<SMonsterRankInfo> = SMonsterRankInfo.vectorFromByteArray(bytes);
			s_.vecRankInfo = vecRankInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMonsterRank>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMonsterRank> = new Vector.<SMonsterRank>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMonsterRank = SMonsterRank.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eRank);
			SMonsterRankInfo.vectorToByteArray(vecRankInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SMonsterRank>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMonsterRank in vec)
				s.toByteArray(bytes);
		}
	}
}
