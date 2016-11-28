/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetBattleArray.as
//  Purpose:      获取阵信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	/**
	 * 获取阵信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetBattleArray
	{
		public var vecBattleArray:Vector.<SBattleArray>; //阵信息列表
		public var vecBattleArrayAttackCnt:Vector.<SBattleArrayAttackCnt>; //攻击阵图信息
		public var dwBuyCnt:uint; //(无符号32位整数)可用的次数
		public var dwDayBuyCnt:uint; //(无符号32位整数)当天购买次数
		public var dwFailCd:uint; //(无符号32位整数)战败cd

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetBattleArray _name_={name_} dwBuyCnt={dwBuyCnt} dwDayBuyCnt={dwDayBuyCnt} dwFailCd={dwFailCd}/>;
			else
				topXml = <SRetParam_GetBattleArray dwBuyCnt={dwBuyCnt} dwDayBuyCnt={dwDayBuyCnt} dwFailCd={dwFailCd}/>;
			if(vecBattleArray != null)
			{
				var vecBattleArrayXml:XML = <Vec_SBattleArray _name_="vecBattleArray"/>;
				for each(var s1:SBattleArray in vecBattleArray)
					vecBattleArrayXml.appendChild(s1.toXML());
				topXml.appendChild(vecBattleArrayXml);
			}
			if(vecBattleArrayAttackCnt != null)
			{
				var vecBattleArrayAttackCntXml:XML = <Vec_SBattleArrayAttackCnt _name_="vecBattleArrayAttackCnt"/>;
				for each(var s2:SBattleArrayAttackCnt in vecBattleArrayAttackCnt)
					vecBattleArrayAttackCntXml.appendChild(s2.toXML());
				topXml.appendChild(vecBattleArrayAttackCntXml);
			}
			return topXml;
		}
	}
}
