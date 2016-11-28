/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SHorseInfo.as
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 坐骑信息
	 */
	public final class SHorseInfo
	{
		public var dwHorseID:uint; //(无符号32位整数)坐骑id
		public var dwHorseLevel:uint; //(无符号32位整数)坐骑等阶
		public var dwExp:uint; //(无符号32位整数)坐骑当前经验
		public var dwPos:uint; //(无符号32位整数)骑乘状态
		public var vecHorseID:Vector.<uint>; //(无符号32位整数)坐骑外观列表

		/**
		 * 辅助创建函数
		 */
		public static function create(dwHorseID:uint, dwHorseLevel:uint, dwExp:uint, dwPos:uint, vecHorseID:Vector.<uint>):SHorseInfo
		{
			var s_:SHorseInfo = new SHorseInfo();
			s_.dwHorseID = dwHorseID;
			s_.dwHorseLevel = dwHorseLevel;
			s_.dwExp = dwExp;
			s_.dwPos = dwPos;
			s_.vecHorseID = vecHorseID;
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
				topXml = <SHorseInfo _name_={name_} dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel} dwExp={dwExp} dwPos={dwPos}/>;
			else
				topXml = <SHorseInfo dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel} dwExp={dwExp} dwPos={dwPos}/>;
			if(vecHorseID != null)
			{
				var vecHorseIDXml:XML = <Vec_UINT32 _name_="vecHorseID"/>;
				var text1:String = "";
				for each(var value1:uint in vecHorseID)
					text1 += "[" + value1 + "]";
				vecHorseIDXml.appendChild(text1);
				topXml.appendChild(vecHorseIDXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwHorseID = dwHorseID;
			obj_.dwHorseLevel = dwHorseLevel;
			obj_.dwExp = dwExp;
			obj_.dwPos = dwPos;
			obj_.vecHorseID = vecHorseID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SHorseInfo
		{
			var s_:SHorseInfo = new SHorseInfo();
			var dwHorseID:uint = bytes.readUnsignedInt();
			s_.dwHorseID = dwHorseID;
			var dwHorseLevel:uint = bytes.readUnsignedInt();
			s_.dwHorseLevel = dwHorseLevel;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var dwPos:uint = bytes.readUnsignedInt();
			s_.dwPos = dwPos;
			var vecHorseID:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecHorseID = vecHorseID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SHorseInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SHorseInfo> = new Vector.<SHorseInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SHorseInfo = SHorseInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwHorseID);
			bytes.writeUnsignedInt(dwHorseLevel);
			bytes.writeUnsignedInt(dwExp);
			bytes.writeUnsignedInt(dwPos);
			BytesUtil.writeVecUInt(bytes, vecHorseID);
		}

		public static function vectorToByteArray(vec:Vector.<SHorseInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SHorseInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
