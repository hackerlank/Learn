/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ArenaChallengeReq.as
//  Purpose:      请求挑战
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import com.hurlant.math.BigInteger;

	/**
	 * 请求挑战的返回的参数组成的结构体
	 */
	public final class SRetParam_ArenaChallengeReq
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求挑战返回
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var bySuc:uint; //(无符号8位整数)0,表示挑战失败，1表示挑战成功
		public var dwScore:uint; //(无符号32位整数)当前积分
		public var dwRanking:uint; //(无符号32位整数)当前排名
		public var wChallenge:uint; //(无符号16位整数)今日挑战次数
		public var wChallengeBuyTimes:uint; //(无符号16位整数)购买的挑战次数
		public var dwCDTimer:uint; //(无符号32位整数)冷却时间戳

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ArenaChallengeReq _name_={name_} eResult={eResult} qwBattleID={qwBattleID} bySuc={bySuc} dwScore={dwScore} dwRanking={dwRanking}
				 wChallenge={wChallenge} wChallengeBuyTimes={wChallengeBuyTimes} dwCDTimer={dwCDTimer}/>;
			else
				topXml = <SRetParam_ArenaChallengeReq eResult={eResult} qwBattleID={qwBattleID} bySuc={bySuc} dwScore={dwScore} dwRanking={dwRanking}
				 wChallenge={wChallenge} wChallengeBuyTimes={wChallengeBuyTimes} dwCDTimer={dwCDTimer}/>;
			return topXml;
		}
	}
}
