/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STripodHelp.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 九疑鼎的协助信息
	 */
	public final class STripodHelp
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)九疑鼎的所属玩家的ID
		public var vecFighterHelp:Vector.<SFighterHelpInfo>; //散仙协助信息
		public var vecPlayerHelp:Vector.<SPlayerHelpInfo>; //玩家协助信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, vecFighterHelp:Vector.<SFighterHelpInfo>, vecPlayerHelp:Vector.<SPlayerHelpInfo>):STripodHelp
		{
			var s_:STripodHelp = new STripodHelp();
			s_.qwRoleID = qwRoleID;
			s_.vecFighterHelp = vecFighterHelp;
			s_.vecPlayerHelp = vecPlayerHelp;
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
				topXml = <STripodHelp _name_={name_} qwRoleID={qwRoleID}/>;
			else
				topXml = <STripodHelp qwRoleID={qwRoleID}/>;
			if(vecFighterHelp != null)
			{
				var vecFighterHelpXml:XML = <Vec_SFighterHelpInfo _name_="vecFighterHelp"/>;
				for each(var s1:SFighterHelpInfo in vecFighterHelp)
					vecFighterHelpXml.appendChild(s1.toXML());
				topXml.appendChild(vecFighterHelpXml);
			}
			if(vecPlayerHelp != null)
			{
				var vecPlayerHelpXml:XML = <Vec_SPlayerHelpInfo _name_="vecPlayerHelp"/>;
				for each(var s2:SPlayerHelpInfo in vecPlayerHelp)
					vecPlayerHelpXml.appendChild(s2.toXML());
				topXml.appendChild(vecPlayerHelpXml);
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
			obj_.vecFighterHelp = vecFighterHelp;
			obj_.vecPlayerHelp = vecPlayerHelp;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STripodHelp
		{
			var s_:STripodHelp = new STripodHelp();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var vecFighterHelp:Vector.<SFighterHelpInfo> = SFighterHelpInfo.vectorFromByteArray(bytes);
			s_.vecFighterHelp = vecFighterHelp;
			var vecPlayerHelp:Vector.<SPlayerHelpInfo> = SPlayerHelpInfo.vectorFromByteArray(bytes);
			s_.vecPlayerHelp = vecPlayerHelp;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STripodHelp>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STripodHelp> = new Vector.<STripodHelp>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STripodHelp = STripodHelp.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			SFighterHelpInfo.vectorToByteArray(vecFighterHelp, bytes);
			SPlayerHelpInfo.vectorToByteArray(vecPlayerHelp, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<STripodHelp>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STripodHelp in vec)
				s.toByteArray(bytes);
		}
	}
}
