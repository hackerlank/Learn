/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetState.as
//  Purpose:      获取帮派战状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	/**
	 * 获取帮派战状态的返回的参数组成的结构体
	 */
	public final class SRetParam_GetState
	{
		public var eState:uint; //(枚举类型：ENGBState)当前帮派战状态
		public var dwRemainTime:uint; //(无符号32位整数)新帮派战剩余时间
		public var vecInfo:Vector.<SMountainPanelInfo>; //各个灵山信息
		public var eMountainType:uint; //(枚举类型：ENGBMountain)自己所在战斗信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetState _name_={name_} eState={eState} dwRemainTime={dwRemainTime} eMountainType={eMountainType}/>;
			else
				topXml = <SRetParam_GetState eState={eState} dwRemainTime={dwRemainTime} eMountainType={eMountainType}/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SMountainPanelInfo _name_="vecInfo"/>;
				for each(var s1:SMountainPanelInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
