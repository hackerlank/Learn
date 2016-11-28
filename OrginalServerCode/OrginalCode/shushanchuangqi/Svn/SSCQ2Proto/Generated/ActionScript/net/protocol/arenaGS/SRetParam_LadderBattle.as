/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_LadderBattle.as
//  Purpose:      请求天梯挑战
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求天梯挑战的返回的参数组成的结构体
	 */
	public final class SRetParam_LadderBattle
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求刷将返回
		public var bySuc:uint; //(无符号8位整数)0,失败，1成功
		public var vecFlushFigter:Vector.<SFlushFitherForClient>; //最近刷的对手
		public var dwSelfRank:uint; //(无符号32位整数)自己排名
		public var dwLadderTimes:uint; //(无符号16位整数)今日挑战天梯次数
		public var dwLadderCDTimer:uint; //(无符号32位整数)冷却时间戳
		public var dwMinLadderRank:uint; //(无符号32位整数)天梯最好排名,0表示无排名
		public var dwLadderBuyTimes:uint; //(无符号32位整数)购买的天梯挑战次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_LadderBattle _name_={name_} eResult={eResult} bySuc={bySuc} dwSelfRank={dwSelfRank} dwLadderTimes={dwLadderTimes}
				 dwLadderCDTimer={dwLadderCDTimer} dwMinLadderRank={dwMinLadderRank} dwLadderBuyTimes={dwLadderBuyTimes}/>;
			else
				topXml = <SRetParam_LadderBattle eResult={eResult} bySuc={bySuc} dwSelfRank={dwSelfRank} dwLadderTimes={dwLadderTimes}
				 dwLadderCDTimer={dwLadderCDTimer} dwMinLadderRank={dwMinLadderRank} dwLadderBuyTimes={dwLadderBuyTimes}/>;
			if(vecFlushFigter != null)
			{
				var vecFlushFigterXml:XML = <Vec_SFlushFitherForClient _name_="vecFlushFigter"/>;
				for each(var s1:SFlushFitherForClient in vecFlushFigter)
					vecFlushFigterXml.appendChild(s1.toXML());
				topXml.appendChild(vecFlushFigterXml);
			}
			return topXml;
		}
	}
}
