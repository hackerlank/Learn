/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqTHBattlePrepareInfo.as
//  Purpose:      请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	/**
	 * 请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqTHBattlePrepareInfo
	{
		public var byKillNum:uint; //(无符号8位整数)剩余击杀次数
		public var dwCurBossHP:uint; //(无符号32位整数)当前BOSS血量
		public var dwTotalTimes:uint; //(无符号32位整数)寻宝时间
		public var vecTHAwardInfo:Vector.<STHAwardInfo>; //寻宝奖励信息
		public var vecTHBuffInfo:Vector.<STHBuffInfo>; //Buff信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqTHBattlePrepareInfo _name_={name_} byKillNum={byKillNum} dwCurBossHP={dwCurBossHP} dwTotalTimes={dwTotalTimes}/>;
			else
				topXml = <SRetParam_ReqTHBattlePrepareInfo byKillNum={byKillNum} dwCurBossHP={dwCurBossHP} dwTotalTimes={dwTotalTimes}/>;
			if(vecTHAwardInfo != null)
			{
				var vecTHAwardInfoXml:XML = <Vec_STHAwardInfo _name_="vecTHAwardInfo"/>;
				for each(var s1:STHAwardInfo in vecTHAwardInfo)
					vecTHAwardInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTHAwardInfoXml);
			}
			if(vecTHBuffInfo != null)
			{
				var vecTHBuffInfoXml:XML = <Vec_STHBuffInfo _name_="vecTHBuffInfo"/>;
				for each(var s2:STHBuffInfo in vecTHBuffInfo)
					vecTHBuffInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecTHBuffInfoXml);
			}
			return topXml;
		}
	}
}
