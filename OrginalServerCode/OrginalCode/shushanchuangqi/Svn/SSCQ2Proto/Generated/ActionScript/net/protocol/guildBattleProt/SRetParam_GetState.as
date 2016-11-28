/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetState.as
//  Purpose:      获取帮派战状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	/**
	 * 获取帮派战状态的返回的参数组成的结构体
	 */
	public final class SRetParam_GetState
	{
		public var eState:uint; //(枚举类型：EGBState)当前帮派战状态
		public var byBattleCount:uint; //(无符号8位整数)当前已经战斗的数量
		public var dwRemainTime:uint; //(无符号32位整数)当前状态剩余时间
		public var eSpotType:uint; //(枚举类型：EGBSpot)自己所在据点(不为None也可能在准备地图中)
		public var bGuildJoined:Boolean; //自己所在帮派是否已经参加
		public var eSelfSide:uint; //(枚举类型：EGBSide)自己所在帮派方向

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetState _name_={name_} eState={eState} byBattleCount={byBattleCount} dwRemainTime={dwRemainTime} eSpotType={eSpotType} bGuildJoined={bGuildJoined}
				 eSelfSide={eSelfSide}/>;
			else
				topXml = <SRetParam_GetState eState={eState} byBattleCount={byBattleCount} dwRemainTime={dwRemainTime} eSpotType={eSpotType} bGuildJoined={bGuildJoined}
				 eSelfSide={eSelfSide}/>;
			return topXml;
		}
	}
}
