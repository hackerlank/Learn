/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleTargetPos.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 目标位置，由组ID和位置唯一能找到坐标
	 */
	public final class SBattleTargetPos
	{
		public var byGroupID:uint; //(无符号8位整数)组ID
		public var byPos:uint; //(无符号8位整数)位置ID

		/**
		 * 辅助创建函数
		 */
		public static function create(byGroupID:uint, byPos:uint):SBattleTargetPos
		{
			var s_:SBattleTargetPos = new SBattleTargetPos();
			s_.byGroupID = byGroupID;
			s_.byPos = byPos;
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
				topXml = <SBattleTargetPos _name_={name_} byGroupID={byGroupID} byPos={byPos}/>;
			else
				topXml = <SBattleTargetPos byGroupID={byGroupID} byPos={byPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byGroupID = byGroupID;
			obj_.byPos = byPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleTargetPos
		{
			var s_:SBattleTargetPos = new SBattleTargetPos();
			var byGroupID:uint = bytes.readUnsignedByte();
			s_.byGroupID = byGroupID;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleTargetPos>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleTargetPos> = new Vector.<SBattleTargetPos>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleTargetPos = SBattleTargetPos.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byGroupID);
			bytes.writeByte(byPos);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleTargetPos>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleTargetPos in vec)
				s.toByteArray(bytes);
		}
	}
}
