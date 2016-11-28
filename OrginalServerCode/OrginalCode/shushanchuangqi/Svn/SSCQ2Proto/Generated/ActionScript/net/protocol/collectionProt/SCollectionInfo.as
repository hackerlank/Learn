/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCollectionInfo.as
//  Purpose:      收藏协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.collectionProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * EDataType:eTypeCollectionInfo
	 */
	public final class SCollectionInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var wCollectionID:uint; //(无符号16位整数)收藏ID
		public var dwCount:uint; //(无符号32位整数)0是否完成
		public var dwProcess:uint; //(无符号32位整数)当前进度(持续型事件记录数据)
		public var dwFinishTime:uint; //(无符号32位整数)完成时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wCollectionID:uint, dwCount:uint, dwProcess:uint, dwFinishTime:uint):SCollectionInfo
		{
			var s_:SCollectionInfo = new SCollectionInfo();
			s_.qwRoleID = qwRoleID;
			s_.wCollectionID = wCollectionID;
			s_.dwCount = dwCount;
			s_.dwProcess = dwProcess;
			s_.dwFinishTime = dwFinishTime;
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
				topXml = <SCollectionInfo _name_={name_} qwRoleID={qwRoleID} wCollectionID={wCollectionID} dwCount={dwCount} dwProcess={dwProcess} dwFinishTime={dwFinishTime}/>;
			else
				topXml = <SCollectionInfo qwRoleID={qwRoleID} wCollectionID={wCollectionID} dwCount={dwCount} dwProcess={dwProcess} dwFinishTime={dwFinishTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wCollectionID = wCollectionID;
			obj_.dwCount = dwCount;
			obj_.dwProcess = dwProcess;
			obj_.dwFinishTime = dwFinishTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCollectionInfo
		{
			var s_:SCollectionInfo = new SCollectionInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wCollectionID:uint = bytes.readUnsignedShort();
			s_.wCollectionID = wCollectionID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var dwProcess:uint = bytes.readUnsignedInt();
			s_.dwProcess = dwProcess;
			var dwFinishTime:uint = bytes.readUnsignedInt();
			s_.dwFinishTime = dwFinishTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCollectionInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCollectionInfo> = new Vector.<SCollectionInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCollectionInfo = SCollectionInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wCollectionID);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeUnsignedInt(dwProcess);
			bytes.writeUnsignedInt(dwFinishTime);
		}

		public static function vectorToByteArray(vec:Vector.<SCollectionInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCollectionInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
