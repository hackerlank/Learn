/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterCombination.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家的散仙组合信息
	 */
	public final class SFighterCombination
	{
		public var byGroupID:uint; //(无符号8位整数)散仙组合ID
		public var byGroupLvl:uint; //(无符号8位整数)散仙组合等级
		public var dwGroupExp:uint; //(无符号32位整数)散仙组合当前经验值
		public var byInLineUp:uint; //(无符号8位整数)是否出战在阵型(0未出战 1已出战)
		public var byInEMei:uint; //(无符号8位整数)是否出战在守卫峨眉(0未出战 1已出战)

		/**
		 * 辅助创建函数
		 */
		public static function create(byGroupID:uint, byGroupLvl:uint, dwGroupExp:uint, byInLineUp:uint, byInEMei:uint):SFighterCombination
		{
			var s_:SFighterCombination = new SFighterCombination();
			s_.byGroupID = byGroupID;
			s_.byGroupLvl = byGroupLvl;
			s_.dwGroupExp = dwGroupExp;
			s_.byInLineUp = byInLineUp;
			s_.byInEMei = byInEMei;
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
				topXml = <SFighterCombination _name_={name_} byGroupID={byGroupID} byGroupLvl={byGroupLvl} dwGroupExp={dwGroupExp} byInLineUp={byInLineUp} byInEMei={byInEMei}/>;
			else
				topXml = <SFighterCombination byGroupID={byGroupID} byGroupLvl={byGroupLvl} dwGroupExp={dwGroupExp} byInLineUp={byInLineUp} byInEMei={byInEMei}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byGroupID = byGroupID;
			obj_.byGroupLvl = byGroupLvl;
			obj_.dwGroupExp = dwGroupExp;
			obj_.byInLineUp = byInLineUp;
			obj_.byInEMei = byInEMei;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterCombination
		{
			var s_:SFighterCombination = new SFighterCombination();
			var byGroupID:uint = bytes.readUnsignedByte();
			s_.byGroupID = byGroupID;
			var byGroupLvl:uint = bytes.readUnsignedByte();
			s_.byGroupLvl = byGroupLvl;
			var dwGroupExp:uint = bytes.readUnsignedInt();
			s_.dwGroupExp = dwGroupExp;
			var byInLineUp:uint = bytes.readUnsignedByte();
			s_.byInLineUp = byInLineUp;
			var byInEMei:uint = bytes.readUnsignedByte();
			s_.byInEMei = byInEMei;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterCombination>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterCombination> = new Vector.<SFighterCombination>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterCombination = SFighterCombination.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byGroupID);
			bytes.writeByte(byGroupLvl);
			bytes.writeUnsignedInt(dwGroupExp);
			bytes.writeByte(byInLineUp);
			bytes.writeByte(byInEMei);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterCombination>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterCombination in vec)
				s.toByteArray(bytes);
		}
	}
}
