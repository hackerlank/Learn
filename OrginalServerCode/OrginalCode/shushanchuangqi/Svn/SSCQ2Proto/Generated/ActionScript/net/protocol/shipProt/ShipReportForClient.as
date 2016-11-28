/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    ShipReportForClient.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 金船战报客户端信息
	 */
	public final class ShipReportForClient
	{
		public var stInfo:ShipReport; //战报信息
		public var eResult:uint; //(枚举类型：battleGS.EBattleResult)
		public var strOwerName:String; //金船拥有者名字
		public var strDefenseName:String; //金船护卫名字
		public var strRoBIdName:String; //金船抢劫者名字

		/**
		 * 辅助创建函数
		 */
		public static function create(stInfo:ShipReport, eResult:uint, strOwerName:String, strDefenseName:String, strRoBIdName:String):ShipReportForClient
		{
			var s_:ShipReportForClient = new ShipReportForClient();
			s_.stInfo = stInfo;
			s_.eResult = eResult;
			s_.strOwerName = strOwerName;
			s_.strDefenseName = strDefenseName;
			s_.strRoBIdName = strRoBIdName;
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
				topXml = <ShipReportForClient _name_={name_} eResult={eResult} strOwerName={strOwerName} strDefenseName={strDefenseName} strRoBIdName={strRoBIdName}/>;
			else
				topXml = <ShipReportForClient eResult={eResult} strOwerName={strOwerName} strDefenseName={strDefenseName} strRoBIdName={strRoBIdName}/>;
			if(stInfo != null)
				topXml.appendChild(stInfo.toXML("stInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.stInfo = stInfo;
			obj_.eResult = eResult;
			obj_.strOwerName = strOwerName;
			obj_.strDefenseName = strDefenseName;
			obj_.strRoBIdName = strRoBIdName;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):ShipReportForClient
		{
			var s_:ShipReportForClient = new ShipReportForClient();
			var stInfo:ShipReport = ShipReport.fromByteArray(bytes);
			s_.stInfo = stInfo;
			var eResult:uint = bytes.readUnsignedByte();
			s_.eResult = eResult;
			var strOwerName:String = BytesUtil.readString(bytes);
			s_.strOwerName = strOwerName;
			var strDefenseName:String = BytesUtil.readString(bytes);
			s_.strDefenseName = strDefenseName;
			var strRoBIdName:String = BytesUtil.readString(bytes);
			s_.strRoBIdName = strRoBIdName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<ShipReportForClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<ShipReportForClient> = new Vector.<ShipReportForClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:ShipReportForClient = ShipReportForClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			stInfo.toByteArray(bytes);
			bytes.writeByte(eResult);
			BytesUtil.writeString(bytes, strOwerName);
			BytesUtil.writeString(bytes, strDefenseName);
			BytesUtil.writeString(bytes, strRoBIdName);
		}

		public static function vectorToByteArray(vec:Vector.<ShipReportForClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:ShipReportForClient in vec)
				s.toByteArray(bytes);
		}
	}
}
