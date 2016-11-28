/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGrid.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 格子数据
	 */
	public final class SGrid
	{
		public var byIndex:uint; //(无符号8位整数)格子ID
		public var byLevel:uint; //(无符号8位整数)格子所在层
		public var eGridType:uint; //(枚举类型：EGridType)格子类型
		public var wNoteID:uint; //(无符号16位整数)格子记录数据
		public var bFinished:Boolean; //是否完成
		public var bRandom:Boolean; //是否随机格子

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, byLevel:uint, eGridType:uint, wNoteID:uint, bFinished:Boolean, 
			bRandom:Boolean):SGrid
		{
			var s_:SGrid = new SGrid();
			s_.byIndex = byIndex;
			s_.byLevel = byLevel;
			s_.eGridType = eGridType;
			s_.wNoteID = wNoteID;
			s_.bFinished = bFinished;
			s_.bRandom = bRandom;
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
				topXml = <SGrid _name_={name_} byIndex={byIndex} byLevel={byLevel} eGridType={eGridType} wNoteID={wNoteID} bFinished={bFinished}
				 bRandom={bRandom}/>;
			else
				topXml = <SGrid byIndex={byIndex} byLevel={byLevel} eGridType={eGridType} wNoteID={wNoteID} bFinished={bFinished}
				 bRandom={bRandom}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.byLevel = byLevel;
			obj_.eGridType = eGridType;
			obj_.wNoteID = wNoteID;
			obj_.bFinished = bFinished;
			obj_.bRandom = bRandom;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGrid
		{
			var s_:SGrid = new SGrid();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var eGridType:uint = bytes.readUnsignedByte();
			s_.eGridType = eGridType;
			var wNoteID:uint = bytes.readUnsignedShort();
			s_.wNoteID = wNoteID;
			var bFinished:Boolean = bytes.readBoolean();
			s_.bFinished = bFinished;
			var bRandom:Boolean = bytes.readBoolean();
			s_.bRandom = bRandom;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGrid>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGrid> = new Vector.<SGrid>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGrid = SGrid.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			bytes.writeByte(byLevel);
			bytes.writeByte(eGridType);
			bytes.writeShort(wNoteID);
			bytes.writeBoolean(bFinished);
			bytes.writeBoolean(bRandom);
		}

		public static function vectorToByteArray(vec:Vector.<SGrid>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGrid in vec)
				s.toByteArray(bytes);
		}
	}
}
