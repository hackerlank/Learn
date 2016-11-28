/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_EquipTrumpNotify.as
//  Purpose:      协议:道具相关协议, 函数:当前玩家角色的装备法宝通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SEquipTrump;

	/**
	 * 函数EquipTrumpNotify[当前玩家角色的装备法宝通知]的接收事件
	 */
	public final class REvt_EquipTrumpNotify extends Event
	{
		public static const DATA_RECEIVE:String = "EquipTrumpProt_EquipTrumpNotify";
		public static const DATA_ERROR:String = "EquipTrumpProt_EquipTrumpNotify_Error";

		public var qwOwnerID:BigInteger; //(无符号64位整数)散仙唯一ID
		public var eSlotType:int; //(枚举类型：EEquipTrumpSlotType)装备法宝位类型
		public var vecEquipTrump:Vector.<SEquipTrump>; //当前装备法宝的列表

		public function REvt_EquipTrumpNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_EquipTrumpNotify qwOwnerID={qwOwnerID} eSlotType={eSlotType}/>;
			if(vecEquipTrump != null)
			{
				var vecEquipTrumpXml:XML = <Vec_SEquipTrump _name_="vecEquipTrump"/>;
				for each(var s1:SEquipTrump in vecEquipTrump)
					vecEquipTrumpXml.appendChild(s1.toXML());
				topXml.appendChild(vecEquipTrumpXml);
			}
			return topXml;
		}
	}
}
