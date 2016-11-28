/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SShengLingInfo.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemGenInfo;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家进入信息
	 */
	public final class SShengLingInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wPassword:uint; //(无符号16位整数)初始密码
		public var byDir:uint; //(无符号8位整数)玩家在棋盘中的方向（0表示反向，1表示正向）
		public var byLevel:uint; //(无符号8位整数)玩家当前所在层
		public var byIndex:uint; //(无符号8位整数)玩家当前所在层格子ID
		public var byBuyLife:uint; //(无符号8位整数)玩家购买生命数
		public var byUseLife:uint; //(无符号8位整数)玩家今日使用生命数
		public var byStep:uint; //(无符号8位整数)玩家在“三消”中剩余步数
		public var byScore:uint; //(无符号16位整数)玩家在“三消”中累计积分
		public var byBit:uint; //(无符号8位整数)玩家在“三消”中奖励领取状态，bit位表示从低到高
		public var byBuyLifeToday:uint; //(无符号8位整数)玩家今天购买生命数
		public var byFirst:uint; //(无符号8位整数)玩家是否第一次进入圣陵
		public var vecGrid:Vector.<SGrid>; //格子数据
		public var vecCard:Vector.<SCard>; //卡片数据
		public var vecItem:Vector.<SItemGenInfo>; //获得的奖励数据

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wPassword:uint, byDir:uint, byLevel:uint, byIndex:uint, 
			byBuyLife:uint, byUseLife:uint, byStep:uint, byScore:uint, byBit:uint, 
			byBuyLifeToday:uint, byFirst:uint, vecGrid:Vector.<SGrid>, vecCard:Vector.<SCard>, vecItem:Vector.<SItemGenInfo>):SShengLingInfo
		{
			var s_:SShengLingInfo = new SShengLingInfo();
			s_.qwRoleID = qwRoleID;
			s_.wPassword = wPassword;
			s_.byDir = byDir;
			s_.byLevel = byLevel;
			s_.byIndex = byIndex;
			s_.byBuyLife = byBuyLife;
			s_.byUseLife = byUseLife;
			s_.byStep = byStep;
			s_.byScore = byScore;
			s_.byBit = byBit;
			s_.byBuyLifeToday = byBuyLifeToday;
			s_.byFirst = byFirst;
			s_.vecGrid = vecGrid;
			s_.vecCard = vecCard;
			s_.vecItem = vecItem;
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
				topXml = <SShengLingInfo _name_={name_} qwRoleID={qwRoleID} wPassword={wPassword} byDir={byDir} byLevel={byLevel} byIndex={byIndex}
				 byBuyLife={byBuyLife} byUseLife={byUseLife} byStep={byStep} byScore={byScore} byBit={byBit}
				 byBuyLifeToday={byBuyLifeToday} byFirst={byFirst}/>;
			else
				topXml = <SShengLingInfo qwRoleID={qwRoleID} wPassword={wPassword} byDir={byDir} byLevel={byLevel} byIndex={byIndex}
				 byBuyLife={byBuyLife} byUseLife={byUseLife} byStep={byStep} byScore={byScore} byBit={byBit}
				 byBuyLifeToday={byBuyLifeToday} byFirst={byFirst}/>;
			if(vecGrid != null)
			{
				var vecGridXml:XML = <Vec_SGrid _name_="vecGrid"/>;
				for each(var s1:SGrid in vecGrid)
					vecGridXml.appendChild(s1.toXML());
				topXml.appendChild(vecGridXml);
			}
			if(vecCard != null)
			{
				var vecCardXml:XML = <Vec_SCard _name_="vecCard"/>;
				for each(var s2:SCard in vecCard)
					vecCardXml.appendChild(s2.toXML());
				topXml.appendChild(vecCardXml);
			}
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s3:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s3.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wPassword = wPassword;
			obj_.byDir = byDir;
			obj_.byLevel = byLevel;
			obj_.byIndex = byIndex;
			obj_.byBuyLife = byBuyLife;
			obj_.byUseLife = byUseLife;
			obj_.byStep = byStep;
			obj_.byScore = byScore;
			obj_.byBit = byBit;
			obj_.byBuyLifeToday = byBuyLifeToday;
			obj_.byFirst = byFirst;
			obj_.vecGrid = vecGrid;
			obj_.vecCard = vecCard;
			obj_.vecItem = vecItem;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SShengLingInfo
		{
			var s_:SShengLingInfo = new SShengLingInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wPassword:uint = bytes.readUnsignedShort();
			s_.wPassword = wPassword;
			var byDir:uint = bytes.readUnsignedByte();
			s_.byDir = byDir;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var byBuyLife:uint = bytes.readUnsignedByte();
			s_.byBuyLife = byBuyLife;
			var byUseLife:uint = bytes.readUnsignedByte();
			s_.byUseLife = byUseLife;
			var byStep:uint = bytes.readUnsignedByte();
			s_.byStep = byStep;
			var byScore:uint = bytes.readUnsignedShort();
			s_.byScore = byScore;
			var byBit:uint = bytes.readUnsignedByte();
			s_.byBit = byBit;
			var byBuyLifeToday:uint = bytes.readUnsignedByte();
			s_.byBuyLifeToday = byBuyLifeToday;
			var byFirst:uint = bytes.readUnsignedByte();
			s_.byFirst = byFirst;
			var vecGrid:Vector.<SGrid> = SGrid.vectorFromByteArray(bytes);
			s_.vecGrid = vecGrid;
			var vecCard:Vector.<SCard> = SCard.vectorFromByteArray(bytes);
			s_.vecCard = vecCard;
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes);
			s_.vecItem = vecItem;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SShengLingInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SShengLingInfo> = new Vector.<SShengLingInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SShengLingInfo = SShengLingInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wPassword);
			bytes.writeByte(byDir);
			bytes.writeByte(byLevel);
			bytes.writeByte(byIndex);
			bytes.writeByte(byBuyLife);
			bytes.writeByte(byUseLife);
			bytes.writeByte(byStep);
			bytes.writeShort(byScore);
			bytes.writeByte(byBit);
			bytes.writeByte(byBuyLifeToday);
			bytes.writeByte(byFirst);
			SGrid.vectorToByteArray(vecGrid, bytes);
			SCard.vectorToByteArray(vecCard, bytes);
			SItemGenInfo.vectorToByteArray(vecItem, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SShengLingInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SShengLingInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
