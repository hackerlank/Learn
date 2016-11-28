/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGRBattleInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派战排名
	 */
	public final class SGRBattleInfo extends SGuildRankInfo
	{
		public var dwBattleScore:uint; //(无符号32位整数)帮派战积分

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SGRBattleInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGRBattleInfo _name_={name_} dwBattleScore={dwBattleScore}/>;
			else
				topXml = <SGRBattleInfo dwBattleScore={dwBattleScore}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.dwBattleScore = dwBattleScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGRBattleInfo
		{
			var s_:SGRBattleInfo = new SGRBattleInfo();
			var base_:SGuildRankInfo = SGuildRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwBattleScore:uint = bytes.readUnsignedInt();
			s_.dwBattleScore = dwBattleScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGRBattleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGRBattleInfo> = new Vector.<SGRBattleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGRBattleInfo = SGRBattleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwBattleScore);
		}

		public static function vectorToByteArray(vec:Vector.<SGRBattleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGRBattleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
