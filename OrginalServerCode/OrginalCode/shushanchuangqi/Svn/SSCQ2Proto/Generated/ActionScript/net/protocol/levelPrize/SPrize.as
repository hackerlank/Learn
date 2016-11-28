/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrize.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import net.protocol.itemProt.SItemGenInfo;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 奖励
	 */
	public final class SPrize
	{
		public var byIndex:uint; //(无符号8位整数)第几个奖
		public var eState:uint; //(枚举类型：ELevelActStatus)第几个奖状态
		public var vecItem:Vector.<SItemGenInfo>; //物品

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, eState:uint, vecItem:Vector.<SItemGenInfo>):SPrize
		{
			var s_:SPrize = new SPrize();
			s_.byIndex = byIndex;
			s_.eState = eState;
			s_.vecItem = vecItem;
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
				topXml = <SPrize _name_={name_} byIndex={byIndex} eState={eState}/>;
			else
				topXml = <SPrize byIndex={byIndex} eState={eState}/>;
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s1:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.eState = eState;
			obj_.vecItem = vecItem;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrize
		{
			var s_:SPrize = new SPrize();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var eState:uint = bytes.readUnsignedByte();
			s_.eState = eState;
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes);
			s_.vecItem = vecItem;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrize>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrize> = new Vector.<SPrize>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrize = SPrize.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			bytes.writeByte(eState);
			SItemGenInfo.vectorToByteArray(vecItem, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPrize>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrize in vec)
				s.toByteArray(bytes);
		}
	}
}
