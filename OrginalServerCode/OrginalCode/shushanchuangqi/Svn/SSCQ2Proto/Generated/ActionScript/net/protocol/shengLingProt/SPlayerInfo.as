/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerInfo.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家信息
	 */
	public final class SPlayerInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var byCurLevel:uint; //(无符号8位整数)玩家当前所在层
		public var byCurIndex:uint; //(无符号8位整数)玩家当前所在层格子ID
		public var byPreLevel:uint; //(无符号8位整数)玩家上一次所在层
		public var byPreIndex:uint; //(无符号8位整数)玩家上一次所在层格子ID
		public var byBuy:uint; //(无符号8位整数)玩家购买生命数
		public var byUse:uint; //(无符号8位整数)玩家当前使用生命数
		public var byNext:uint; //(无符号8位整数)是否进入下一层
		public var vecGrid:Vector.<SGrid>; //格子数据

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byCurLevel:uint, byCurIndex:uint, byPreLevel:uint, byPreIndex:uint, 
			byBuy:uint, byUse:uint, byNext:uint, vecGrid:Vector.<SGrid>):SPlayerInfo
		{
			var s_:SPlayerInfo = new SPlayerInfo();
			s_.qwRoleID = qwRoleID;
			s_.byCurLevel = byCurLevel;
			s_.byCurIndex = byCurIndex;
			s_.byPreLevel = byPreLevel;
			s_.byPreIndex = byPreIndex;
			s_.byBuy = byBuy;
			s_.byUse = byUse;
			s_.byNext = byNext;
			s_.vecGrid = vecGrid;
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
				topXml = <SPlayerInfo _name_={name_} qwRoleID={qwRoleID} byCurLevel={byCurLevel} byCurIndex={byCurIndex} byPreLevel={byPreLevel} byPreIndex={byPreIndex}
				 byBuy={byBuy} byUse={byUse} byNext={byNext}/>;
			else
				topXml = <SPlayerInfo qwRoleID={qwRoleID} byCurLevel={byCurLevel} byCurIndex={byCurIndex} byPreLevel={byPreLevel} byPreIndex={byPreIndex}
				 byBuy={byBuy} byUse={byUse} byNext={byNext}/>;
			if(vecGrid != null)
			{
				var vecGridXml:XML = <Vec_SGrid _name_="vecGrid"/>;
				for each(var s1:SGrid in vecGrid)
					vecGridXml.appendChild(s1.toXML());
				topXml.appendChild(vecGridXml);
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
			obj_.byCurLevel = byCurLevel;
			obj_.byCurIndex = byCurIndex;
			obj_.byPreLevel = byPreLevel;
			obj_.byPreIndex = byPreIndex;
			obj_.byBuy = byBuy;
			obj_.byUse = byUse;
			obj_.byNext = byNext;
			obj_.vecGrid = vecGrid;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerInfo
		{
			var s_:SPlayerInfo = new SPlayerInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byCurLevel:uint = bytes.readUnsignedByte();
			s_.byCurLevel = byCurLevel;
			var byCurIndex:uint = bytes.readUnsignedByte();
			s_.byCurIndex = byCurIndex;
			var byPreLevel:uint = bytes.readUnsignedByte();
			s_.byPreLevel = byPreLevel;
			var byPreIndex:uint = bytes.readUnsignedByte();
			s_.byPreIndex = byPreIndex;
			var byBuy:uint = bytes.readUnsignedByte();
			s_.byBuy = byBuy;
			var byUse:uint = bytes.readUnsignedByte();
			s_.byUse = byUse;
			var byNext:uint = bytes.readUnsignedByte();
			s_.byNext = byNext;
			var vecGrid:Vector.<SGrid> = SGrid.vectorFromByteArray(bytes);
			s_.vecGrid = vecGrid;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerInfo> = new Vector.<SPlayerInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerInfo = SPlayerInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byCurLevel);
			bytes.writeByte(byCurIndex);
			bytes.writeByte(byPreLevel);
			bytes.writeByte(byPreIndex);
			bytes.writeByte(byBuy);
			bytes.writeByte(byUse);
			bytes.writeByte(byNext);
			SGrid.vectorToByteArray(vecGrid, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
