/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SHorseData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 坐骑信息
	 */
	public final class SHorseData
	{
		public var dwHorseID:uint; //(无符号32位整数)坐骑id
		public var byHorseLvl:uint; //(无符号8位整数)坐骑等级
		public var bySelected:uint; //(无符号8位整数)0-不跟随 1-跟随

		/**
		 * 辅助创建函数
		 */
		public static function create(dwHorseID:uint, byHorseLvl:uint, bySelected:uint):SHorseData
		{
			var s_:SHorseData = new SHorseData();
			s_.dwHorseID = dwHorseID;
			s_.byHorseLvl = byHorseLvl;
			s_.bySelected = bySelected;
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
				topXml = <SHorseData _name_={name_} dwHorseID={dwHorseID} byHorseLvl={byHorseLvl} bySelected={bySelected}/>;
			else
				topXml = <SHorseData dwHorseID={dwHorseID} byHorseLvl={byHorseLvl} bySelected={bySelected}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwHorseID = dwHorseID;
			obj_.byHorseLvl = byHorseLvl;
			obj_.bySelected = bySelected;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SHorseData
		{
			var s_:SHorseData = new SHorseData();
			var dwHorseID:uint = bytes.readUnsignedInt();
			s_.dwHorseID = dwHorseID;
			var byHorseLvl:uint = bytes.readUnsignedByte();
			s_.byHorseLvl = byHorseLvl;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SHorseData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SHorseData> = new Vector.<SHorseData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SHorseData = SHorseData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwHorseID);
			bytes.writeByte(byHorseLvl);
			bytes.writeByte(bySelected);
		}

		public static function vectorToByteArray(vec:Vector.<SHorseData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SHorseData in vec)
				s.toByteArray(bytes);
		}
	}
}
