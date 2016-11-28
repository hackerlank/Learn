/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SArenaPlayerBaseDataUpdate.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 竞技场更新信息
	 */
	public final class SArenaPlayerBaseDataUpdate
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var stBaseData:SArenaPlayerBaseData; //基本竞技场信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, stBaseData:SArenaPlayerBaseData):SArenaPlayerBaseDataUpdate
		{
			var s_:SArenaPlayerBaseDataUpdate = new SArenaPlayerBaseDataUpdate();
			s_.qwRoleID = qwRoleID;
			s_.stBaseData = stBaseData;
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
				topXml = <SArenaPlayerBaseDataUpdate _name_={name_} qwRoleID={qwRoleID}/>;
			else
				topXml = <SArenaPlayerBaseDataUpdate qwRoleID={qwRoleID}/>;
			if(stBaseData != null)
				topXml.appendChild(stBaseData.toXML("stBaseData"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.stBaseData = stBaseData;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SArenaPlayerBaseDataUpdate
		{
			var s_:SArenaPlayerBaseDataUpdate = new SArenaPlayerBaseDataUpdate();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var stBaseData:SArenaPlayerBaseData = SArenaPlayerBaseData.fromByteArray(bytes);
			s_.stBaseData = stBaseData;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SArenaPlayerBaseDataUpdate>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SArenaPlayerBaseDataUpdate> = new Vector.<SArenaPlayerBaseDataUpdate>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SArenaPlayerBaseDataUpdate = SArenaPlayerBaseDataUpdate.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			stBaseData.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SArenaPlayerBaseDataUpdate>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SArenaPlayerBaseDataUpdate in vec)
				s.toByteArray(bytes);
		}
	}
}
