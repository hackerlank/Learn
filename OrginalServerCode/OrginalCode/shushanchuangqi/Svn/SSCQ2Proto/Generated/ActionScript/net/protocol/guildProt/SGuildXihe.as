/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildXihe.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家羲和神车信息
	 */
	public final class SGuildXihe
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var vecTruckInfo:Vector.<STruckInfo>; //货号信息
		public var byStage:uint; //(无符号8位整数)EXiheStage当前阶段(0装货阶段 1任务冷却阶段 2等待玩家接取任务)
		public var dwEndTime:uint; //(无符号32位整数)当前阶段的结束时间
		public var byRequest:uint; //(无符号8位整数)已请求帮助的次数

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, vecTruckInfo:Vector.<STruckInfo>, byStage:uint, dwEndTime:uint, byRequest:uint):SGuildXihe
		{
			var s_:SGuildXihe = new SGuildXihe();
			s_.qwRoleID = qwRoleID;
			s_.vecTruckInfo = vecTruckInfo;
			s_.byStage = byStage;
			s_.dwEndTime = dwEndTime;
			s_.byRequest = byRequest;
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
				topXml = <SGuildXihe _name_={name_} qwRoleID={qwRoleID} byStage={byStage} dwEndTime={dwEndTime} byRequest={byRequest}/>;
			else
				topXml = <SGuildXihe qwRoleID={qwRoleID} byStage={byStage} dwEndTime={dwEndTime} byRequest={byRequest}/>;
			if(vecTruckInfo != null)
			{
				var vecTruckInfoXml:XML = <Vec_STruckInfo _name_="vecTruckInfo"/>;
				for each(var s1:STruckInfo in vecTruckInfo)
					vecTruckInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTruckInfoXml);
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
			obj_.vecTruckInfo = vecTruckInfo;
			obj_.byStage = byStage;
			obj_.dwEndTime = dwEndTime;
			obj_.byRequest = byRequest;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildXihe
		{
			var s_:SGuildXihe = new SGuildXihe();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var vecTruckInfo:Vector.<STruckInfo> = STruckInfo.vectorFromByteArray(bytes);
			s_.vecTruckInfo = vecTruckInfo;
			var byStage:uint = bytes.readUnsignedByte();
			s_.byStage = byStage;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			var byRequest:uint = bytes.readUnsignedByte();
			s_.byRequest = byRequest;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildXihe>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildXihe> = new Vector.<SGuildXihe>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildXihe = SGuildXihe.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			STruckInfo.vectorToByteArray(vecTruckInfo, bytes);
			bytes.writeByte(byStage);
			bytes.writeUnsignedInt(dwEndTime);
			bytes.writeByte(byRequest);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildXihe>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildXihe in vec)
				s.toByteArray(bytes);
		}
	}
}
