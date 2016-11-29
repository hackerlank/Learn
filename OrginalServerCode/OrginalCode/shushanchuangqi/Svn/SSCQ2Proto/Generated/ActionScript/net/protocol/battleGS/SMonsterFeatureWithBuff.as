/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMonsterFeatureWithBuff.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 带Buff的怪物信息
	 */
	public final class SMonsterFeatureWithBuff extends SFeatureBase
	{
		public var wMonsterID:uint; //(无符号16位整数)配置表里面的英雄ID，根据ID可以取到怪物外观资源
		public var vecBuffInfo:Vector.<SBattleBuffInfo>; //战斗外的Buff信息

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SFeatureBase.eType_SMonsterFeatureWithBuff;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SMonsterFeatureWithBuff _name_={name_} wMonsterID={wMonsterID}/>;
			else
				topXml = <SMonsterFeatureWithBuff wMonsterID={wMonsterID}/>;
			if(vecBuffInfo != null)
			{
				var vecBuffInfoXml:XML = <Vec_SBattleBuffInfo _name_="vecBuffInfo"/>;
				for each(var s1:SBattleBuffInfo in vecBuffInfo)
					vecBuffInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBuffInfoXml);
			}
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
			obj_.wMonsterID = wMonsterID;
			obj_.vecBuffInfo = vecBuffInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMonsterFeatureWithBuff
		{
			var s_:SMonsterFeatureWithBuff = new SMonsterFeatureWithBuff();
			var base_:SFeatureBase = SFeatureBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var wMonsterID:uint = bytes.readUnsignedShort();
			s_.wMonsterID = wMonsterID;
			var vecBuffInfo:Vector.<SBattleBuffInfo> = SBattleBuffInfo.vectorFromByteArray(bytes);
			s_.vecBuffInfo = vecBuffInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMonsterFeatureWithBuff>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMonsterFeatureWithBuff> = new Vector.<SMonsterFeatureWithBuff>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMonsterFeatureWithBuff = SMonsterFeatureWithBuff.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wMonsterID);
			SBattleBuffInfo.vectorToByteArray(vecBuffInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SMonsterFeatureWithBuff>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMonsterFeatureWithBuff in vec)
				s.toByteArray(bytes);
		}
	}
}