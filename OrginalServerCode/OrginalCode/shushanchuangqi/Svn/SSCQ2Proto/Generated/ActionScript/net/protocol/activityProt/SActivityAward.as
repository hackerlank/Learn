/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActivityAward.as
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 每日已领活力奖励
	 */
	public final class SActivityAward
	{
		public var byId:uint; //(无符号8位整数)奖励ID
		public var byVIP:uint; //(无符号8位整数)是否VIP

		/**
		 * 辅助创建函数
		 */
		public static function create(byId:uint, byVIP:uint):SActivityAward
		{
			var s_:SActivityAward = new SActivityAward();
			s_.byId = byId;
			s_.byVIP = byVIP;
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
				topXml = <SActivityAward _name_={name_} byId={byId} byVIP={byVIP}/>;
			else
				topXml = <SActivityAward byId={byId} byVIP={byVIP}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byId = byId;
			obj_.byVIP = byVIP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActivityAward
		{
			var s_:SActivityAward = new SActivityAward();
			var byId:uint = bytes.readUnsignedByte();
			s_.byId = byId;
			var byVIP:uint = bytes.readUnsignedByte();
			s_.byVIP = byVIP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActivityAward>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActivityAward> = new Vector.<SActivityAward>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActivityAward = SActivityAward.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byId);
			bytes.writeByte(byVIP);
		}

		public static function vectorToByteArray(vec:Vector.<SActivityAward>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActivityAward in vec)
				s.toByteArray(bytes);
		}
	}
}
