/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    PlayerShipForClient.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 金船客户端信息
	 */
	public final class PlayerShipForClient
	{
		public var stInfo:PlayerShip; //金船信息
		public var strOwerName:String; //金船拥有者名字
		public var strGuipName:String; //金船拥有者帮派
		public var strDefenseName:String; //金船护卫名字
		public var strRoBIdName1:String; //金船抢劫者1名字
		public var strRoBIdName2:String; //金船抢劫者2名字
		public var strRoBIdName3:String; //金船抢劫者3名字

		/**
		 * 辅助创建函数
		 */
		public static function create(stInfo:PlayerShip, strOwerName:String, strGuipName:String, strDefenseName:String, strRoBIdName1:String, 
			strRoBIdName2:String, strRoBIdName3:String):PlayerShipForClient
		{
			var s_:PlayerShipForClient = new PlayerShipForClient();
			s_.stInfo = stInfo;
			s_.strOwerName = strOwerName;
			s_.strGuipName = strGuipName;
			s_.strDefenseName = strDefenseName;
			s_.strRoBIdName1 = strRoBIdName1;
			s_.strRoBIdName2 = strRoBIdName2;
			s_.strRoBIdName3 = strRoBIdName3;
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
				topXml = <PlayerShipForClient _name_={name_} strOwerName={strOwerName} strGuipName={strGuipName} strDefenseName={strDefenseName} strRoBIdName1={strRoBIdName1}
				 strRoBIdName2={strRoBIdName2} strRoBIdName3={strRoBIdName3}/>;
			else
				topXml = <PlayerShipForClient strOwerName={strOwerName} strGuipName={strGuipName} strDefenseName={strDefenseName} strRoBIdName1={strRoBIdName1}
				 strRoBIdName2={strRoBIdName2} strRoBIdName3={strRoBIdName3}/>;
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
			obj_.strOwerName = strOwerName;
			obj_.strGuipName = strGuipName;
			obj_.strDefenseName = strDefenseName;
			obj_.strRoBIdName1 = strRoBIdName1;
			obj_.strRoBIdName2 = strRoBIdName2;
			obj_.strRoBIdName3 = strRoBIdName3;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):PlayerShipForClient
		{
			var s_:PlayerShipForClient = new PlayerShipForClient();
			var stInfo:PlayerShip = PlayerShip.fromByteArray(bytes);
			s_.stInfo = stInfo;
			var strOwerName:String = BytesUtil.readString(bytes);
			s_.strOwerName = strOwerName;
			var strGuipName:String = BytesUtil.readString(bytes);
			s_.strGuipName = strGuipName;
			var strDefenseName:String = BytesUtil.readString(bytes);
			s_.strDefenseName = strDefenseName;
			var strRoBIdName1:String = BytesUtil.readString(bytes);
			s_.strRoBIdName1 = strRoBIdName1;
			var strRoBIdName2:String = BytesUtil.readString(bytes);
			s_.strRoBIdName2 = strRoBIdName2;
			var strRoBIdName3:String = BytesUtil.readString(bytes);
			s_.strRoBIdName3 = strRoBIdName3;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<PlayerShipForClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<PlayerShipForClient> = new Vector.<PlayerShipForClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:PlayerShipForClient = PlayerShipForClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			stInfo.toByteArray(bytes);
			BytesUtil.writeString(bytes, strOwerName);
			BytesUtil.writeString(bytes, strGuipName);
			BytesUtil.writeString(bytes, strDefenseName);
			BytesUtil.writeString(bytes, strRoBIdName1);
			BytesUtil.writeString(bytes, strRoBIdName2);
			BytesUtil.writeString(bytes, strRoBIdName3);
		}

		public static function vectorToByteArray(vec:Vector.<PlayerShipForClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:PlayerShipForClient in vec)
				s.toByteArray(bytes);
		}
	}
}
