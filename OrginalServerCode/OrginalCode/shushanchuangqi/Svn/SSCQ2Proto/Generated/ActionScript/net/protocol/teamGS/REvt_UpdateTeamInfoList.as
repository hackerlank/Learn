/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateTeamInfoList.as
//  Purpose:      协议:竞技场协议, 函数:房间列表更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数UpdateTeamInfoList[房间列表更新]的接收事件
	 */
	public final class REvt_UpdateTeamInfoList extends Event
	{
		public static const DATA_RECEIVE:String = "TeamGS_UpdateTeamInfoList";
		public static const DATA_ERROR:String = "TeamGS_UpdateTeamInfoList_Error";

		public var eOpType:uint; //(枚举类型：TeamListOP)操作类型
		public var vecInfo:Vector.<TeamInfoForList>; //修改的数据

		public function REvt_UpdateTeamInfoList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateTeamInfoList eOpType={eOpType}/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_TeamInfoForList _name_="vecInfo"/>;
				for each(var s1:TeamInfoForList in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
