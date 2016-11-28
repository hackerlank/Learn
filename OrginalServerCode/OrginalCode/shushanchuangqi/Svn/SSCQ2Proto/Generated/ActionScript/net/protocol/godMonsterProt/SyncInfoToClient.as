/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SyncInfoToClient.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 发送给客户端的数据
	 */
	public final class SyncInfoToClient
	{
		public var ePeroid:uint; //(枚举类型：EMonsterPeroid)神兽阶段
		public var dwPersonScore:uint; //(无符号32位整数)个人总积分
		public var dwGuildScore:uint; //(无符号32位整数)帮派总积分
		public var dwPersonDevote:uint; //(无符号32位整数)个人贡献值
		public var dwPersonRank:uint; //(无符号32位整数)个人总排名
		public var dwGuildRank:uint; //(无符号32位整数)帮派总排名
		public var dwFruit:uint; //(无符号32位整数)朱果数量
		public var vecPrize:Vector.<SMonsterPrize>; //奖励数据
		public var vecRank:Vector.<SMonsterRank>; //排行榜数据
		public var vecUser:Vector.<SGuildUserDevote>; //成员贡献数据
		public var vecLimitPrize:Vector.<SLimitPrize>; //玩家限购礼包数据

		/**
		 * 辅助创建函数
		 */
		public static function create(ePeroid:uint, dwPersonScore:uint, dwGuildScore:uint, dwPersonDevote:uint, dwPersonRank:uint, 
			dwGuildRank:uint, dwFruit:uint, vecPrize:Vector.<SMonsterPrize>, vecRank:Vector.<SMonsterRank>, vecUser:Vector.<SGuildUserDevote>, 
			vecLimitPrize:Vector.<SLimitPrize>):SyncInfoToClient
		{
			var s_:SyncInfoToClient = new SyncInfoToClient();
			s_.ePeroid = ePeroid;
			s_.dwPersonScore = dwPersonScore;
			s_.dwGuildScore = dwGuildScore;
			s_.dwPersonDevote = dwPersonDevote;
			s_.dwPersonRank = dwPersonRank;
			s_.dwGuildRank = dwGuildRank;
			s_.dwFruit = dwFruit;
			s_.vecPrize = vecPrize;
			s_.vecRank = vecRank;
			s_.vecUser = vecUser;
			s_.vecLimitPrize = vecLimitPrize;
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
				topXml = <SyncInfoToClient _name_={name_} ePeroid={ePeroid} dwPersonScore={dwPersonScore} dwGuildScore={dwGuildScore} dwPersonDevote={dwPersonDevote} dwPersonRank={dwPersonRank}
				 dwGuildRank={dwGuildRank} dwFruit={dwFruit}/>;
			else
				topXml = <SyncInfoToClient ePeroid={ePeroid} dwPersonScore={dwPersonScore} dwGuildScore={dwGuildScore} dwPersonDevote={dwPersonDevote} dwPersonRank={dwPersonRank}
				 dwGuildRank={dwGuildRank} dwFruit={dwFruit}/>;
			if(vecPrize != null)
			{
				var vecPrizeXml:XML = <Vec_SMonsterPrize _name_="vecPrize"/>;
				for each(var s1:SMonsterPrize in vecPrize)
					vecPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecPrizeXml);
			}
			if(vecRank != null)
			{
				var vecRankXml:XML = <Vec_SMonsterRank _name_="vecRank"/>;
				for each(var s2:SMonsterRank in vecRank)
					vecRankXml.appendChild(s2.toXML());
				topXml.appendChild(vecRankXml);
			}
			if(vecUser != null)
			{
				var vecUserXml:XML = <Vec_SGuildUserDevote _name_="vecUser"/>;
				for each(var s3:SGuildUserDevote in vecUser)
					vecUserXml.appendChild(s3.toXML());
				topXml.appendChild(vecUserXml);
			}
			if(vecLimitPrize != null)
			{
				var vecLimitPrizeXml:XML = <Vec_SLimitPrize _name_="vecLimitPrize"/>;
				for each(var s4:SLimitPrize in vecLimitPrize)
					vecLimitPrizeXml.appendChild(s4.toXML());
				topXml.appendChild(vecLimitPrizeXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.ePeroid = ePeroid;
			obj_.dwPersonScore = dwPersonScore;
			obj_.dwGuildScore = dwGuildScore;
			obj_.dwPersonDevote = dwPersonDevote;
			obj_.dwPersonRank = dwPersonRank;
			obj_.dwGuildRank = dwGuildRank;
			obj_.dwFruit = dwFruit;
			obj_.vecPrize = vecPrize;
			obj_.vecRank = vecRank;
			obj_.vecUser = vecUser;
			obj_.vecLimitPrize = vecLimitPrize;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SyncInfoToClient
		{
			var s_:SyncInfoToClient = new SyncInfoToClient();
			var ePeroid:uint = bytes.readUnsignedByte();
			s_.ePeroid = ePeroid;
			var dwPersonScore:uint = bytes.readUnsignedInt();
			s_.dwPersonScore = dwPersonScore;
			var dwGuildScore:uint = bytes.readUnsignedInt();
			s_.dwGuildScore = dwGuildScore;
			var dwPersonDevote:uint = bytes.readUnsignedInt();
			s_.dwPersonDevote = dwPersonDevote;
			var dwPersonRank:uint = bytes.readUnsignedInt();
			s_.dwPersonRank = dwPersonRank;
			var dwGuildRank:uint = bytes.readUnsignedInt();
			s_.dwGuildRank = dwGuildRank;
			var dwFruit:uint = bytes.readUnsignedInt();
			s_.dwFruit = dwFruit;
			var vecPrize:Vector.<SMonsterPrize> = SMonsterPrize.vectorFromByteArray(bytes);
			s_.vecPrize = vecPrize;
			var vecRank:Vector.<SMonsterRank> = SMonsterRank.vectorFromByteArray(bytes);
			s_.vecRank = vecRank;
			var vecUser:Vector.<SGuildUserDevote> = SGuildUserDevote.vectorFromByteArray(bytes);
			s_.vecUser = vecUser;
			var vecLimitPrize:Vector.<SLimitPrize> = SLimitPrize.vectorFromByteArray(bytes);
			s_.vecLimitPrize = vecLimitPrize;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SyncInfoToClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SyncInfoToClient> = new Vector.<SyncInfoToClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SyncInfoToClient = SyncInfoToClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(ePeroid);
			bytes.writeUnsignedInt(dwPersonScore);
			bytes.writeUnsignedInt(dwGuildScore);
			bytes.writeUnsignedInt(dwPersonDevote);
			bytes.writeUnsignedInt(dwPersonRank);
			bytes.writeUnsignedInt(dwGuildRank);
			bytes.writeUnsignedInt(dwFruit);
			SMonsterPrize.vectorToByteArray(vecPrize, bytes);
			SMonsterRank.vectorToByteArray(vecRank, bytes);
			SGuildUserDevote.vectorToByteArray(vecUser, bytes);
			SLimitPrize.vectorToByteArray(vecLimitPrize, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SyncInfoToClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SyncInfoToClient in vec)
				s.toByteArray(bytes);
		}
	}
}
