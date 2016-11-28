/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEquipTrump.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 装备的信息
	 */
	public final class SEquipTrump extends SItem
	{
		public var qwOwnerID:BigInteger; //(无符号64位整数)散仙唯一ID，属于散仙的物品时有效
		public var byIntensifyLvl:uint; //(无符号8位整数)当前强化等级
		public var byIntensifyLvlMax:uint; //(无符号8位整数)可强的最高等级
		public var dwBlessing:uint; //(无符号32位整数)强化祝福值
		public var vecShuffleInfo:Vector.<SShuffleInfo>; //洗炼信息
		public var vecNowReplace:Vector.<SShuffleInfo>; //可替换的洗炼信息
		public var dwXiLianBlessing:uint; //(无符号32位整数)洗练祝福值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SItem.eType_SEquipTrump;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEquipTrump _name_={name_} qwOwnerID={qwOwnerID} byIntensifyLvl={byIntensifyLvl} byIntensifyLvlMax={byIntensifyLvlMax} dwBlessing={dwBlessing} dwXiLianBlessing={dwXiLianBlessing}/>;
			else
				topXml = <SEquipTrump qwOwnerID={qwOwnerID} byIntensifyLvl={byIntensifyLvl} byIntensifyLvlMax={byIntensifyLvlMax} dwBlessing={dwBlessing} dwXiLianBlessing={dwXiLianBlessing}/>;
			if(vecShuffleInfo != null)
			{
				var vecShuffleInfoXml:XML = <Vec_SShuffleInfo _name_="vecShuffleInfo"/>;
				for each(var s1:SShuffleInfo in vecShuffleInfo)
					vecShuffleInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecShuffleInfoXml);
			}
			if(vecNowReplace != null)
			{
				var vecNowReplaceXml:XML = <Vec_SShuffleInfo _name_="vecNowReplace"/>;
				for each(var s2:SShuffleInfo in vecNowReplace)
					vecNowReplaceXml.appendChild(s2.toXML());
				topXml.appendChild(vecNowReplaceXml);
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
			obj_.qwOwnerID = qwOwnerID;
			obj_.byIntensifyLvl = byIntensifyLvl;
			obj_.byIntensifyLvlMax = byIntensifyLvlMax;
			obj_.dwBlessing = dwBlessing;
			obj_.vecShuffleInfo = vecShuffleInfo;
			obj_.vecNowReplace = vecNowReplace;
			obj_.dwXiLianBlessing = dwXiLianBlessing;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEquipTrump
		{
			var s_:SEquipTrump = new SEquipTrump();
			var base_:SItem = SItem.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var byIntensifyLvl:uint = bytes.readUnsignedByte();
			s_.byIntensifyLvl = byIntensifyLvl;
			var byIntensifyLvlMax:uint = bytes.readUnsignedByte();
			s_.byIntensifyLvlMax = byIntensifyLvlMax;
			var dwBlessing:uint = bytes.readUnsignedInt();
			s_.dwBlessing = dwBlessing;
			var vecShuffleInfo:Vector.<SShuffleInfo> = SShuffleInfo.vectorFromByteArray(bytes);
			s_.vecShuffleInfo = vecShuffleInfo;
			var vecNowReplace:Vector.<SShuffleInfo> = SShuffleInfo.vectorFromByteArray(bytes);
			s_.vecNowReplace = vecNowReplace;
			var dwXiLianBlessing:uint = bytes.readUnsignedInt();
			s_.dwXiLianBlessing = dwXiLianBlessing;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEquipTrump>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEquipTrump> = new Vector.<SEquipTrump>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEquipTrump = SEquipTrump.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeByte(byIntensifyLvl);
			bytes.writeByte(byIntensifyLvlMax);
			bytes.writeUnsignedInt(dwBlessing);
			SShuffleInfo.vectorToByteArray(vecShuffleInfo, bytes);
			SShuffleInfo.vectorToByteArray(vecNowReplace, bytes);
			bytes.writeUnsignedInt(dwXiLianBlessing);
		}

		public static function vectorToByteArray(vec:Vector.<SEquipTrump>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEquipTrump in vec)
				s.toByteArray(bytes);
		}
	}
}
