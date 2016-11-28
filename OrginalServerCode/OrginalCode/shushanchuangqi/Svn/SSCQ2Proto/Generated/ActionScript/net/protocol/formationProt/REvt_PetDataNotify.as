/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PetDataNotify.as
//  Purpose:      协议:阵灵相关协议, 函数:阵灵信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.events.Event;

	/**
	 * 函数PetDataNotify[阵灵信息]的接收事件
	 */
	public final class REvt_PetDataNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FormationProt_PetDataNotify";
		public static const DATA_ERROR:String = "FormationProt_PetDataNotify_Error";

		public var wPetID:uint; //(无符号16位整数)阵灵ID
		public var bySelected:uint; //(无符号8位整数)状态: 0-未启用 1-出战且显示 2-出战隐藏
		public var byLevel:uint; //(无符号8位整数)阵灵等级
		public var dwExp:uint; //(无符号32位整数)经验

		public function REvt_PetDataNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PetDataNotify wPetID={wPetID} bySelected={bySelected} byLevel={byLevel} dwExp={dwExp}/>;
			return topXml;
		}
	}
}
