/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleRound.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 一个回合（所有队伍都出手一次）
	 */
	public final class SBattleRound
	{
		public var dwRounds:uint; //(无符号32位整数)当前回合数
		public var vTargets:Vector.<SBattleProgress>; //其它人出手

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRounds:uint, vTargets:Vector.<SBattleProgress>):SBattleRound
		{
			var s_:SBattleRound = new SBattleRound();
			s_.dwRounds = dwRounds;
			s_.vTargets = vTargets;
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
				topXml = <SBattleRound _name_={name_} dwRounds={dwRounds}/>;
			else
				topXml = <SBattleRound dwRounds={dwRounds}/>;
			if(vTargets != null)
			{
				var vTargetsXml:XML = <Vec_SBattleProgress _name_="vTargets"/>;
				for each(var s1:SBattleProgress in vTargets)
					vTargetsXml.appendChild(s1.toXML());
				topXml.appendChild(vTargetsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwRounds = dwRounds;
			obj_.vTargets = vTargets;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleRound
		{
			var s_:SBattleRound = new SBattleRound();
			var dwRounds:uint = bytes.readUnsignedInt();
			s_.dwRounds = dwRounds;
			var vTargets:Vector.<SBattleProgress> = SBattleProgress.vectorFromByteArray(bytes);
			s_.vTargets = vTargets;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleRound>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleRound> = new Vector.<SBattleRound>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleRound = SBattleRound.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwRounds);
			SBattleProgress.vectorToByteArray(vTargets, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleRound>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleRound in vec)
				s.toByteArray(bytes);
		}
	}
}
