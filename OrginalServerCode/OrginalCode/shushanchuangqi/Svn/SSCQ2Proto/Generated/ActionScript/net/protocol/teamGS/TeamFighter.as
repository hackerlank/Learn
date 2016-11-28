/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamFighter.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import net.protocol.battleGS.SFeatureBase;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 房间里的战斗对象
	 */
	public class TeamFighter
	{
		public var pFeature:SFeatureBase; //外观信息
		public var dwFighterPower:uint; //(无符号32位整数)战斗力
		public var byPos:uint; //(无符号8位整数)在玩家将序列的位置

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_TeamFighter.eType_TeamFighter;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <TeamFighter _name_={name_} dwFighterPower={dwFighterPower} byPos={byPos}/>;
			else
				topXml = <TeamFighter dwFighterPower={dwFighterPower} byPos={byPos}/>;
			if(pFeature != null)
				topXml.appendChild(pFeature.toXML("pFeature"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.pFeature = pFeature;
			obj_.dwFighterPower = dwFighterPower;
			obj_.byPos = byPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamFighter
		{
			var s_:TeamFighter = new TeamFighter();
			var pFeature:SFeatureBase = SFeatureBase.superFromByteArray(bytes);
			s_.pFeature = pFeature;
			var dwFighterPower:uint = bytes.readUnsignedInt();
			s_.dwFighterPower = dwFighterPower;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):TeamFighter
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:TeamFighter;
			switch(eType)
			{
				case EType_TeamFighter.eType_TeamFighter:
					s = TeamFighter.fromByteArray(bytes);
					break;
				case EType_TeamFighter.eType_CommonFighter:
					s = CommonFighter.fromByteArray(bytes);
					break;
				case EType_TeamFighter.eType_FormationFighter:
					s = FormationFighter.fromByteArray(bytes);
					break;
				case EType_TeamFighter.eType_BeautyFighter:
					s = BeautyFighter.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_TeamFighter:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamFighter> = new Vector.<TeamFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamFighter = TeamFighter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<TeamFighter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamFighter> = new Vector.<TeamFighter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamFighter = TeamFighter.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			pFeature.superToByteArray(bytes);
			bytes.writeUnsignedInt(dwFighterPower);
			bytes.writeByte(byPos);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<TeamFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamFighter in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<TeamFighter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamFighter in vec)
				s.superToByteArray(bytes);
		}
	}
}
