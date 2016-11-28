/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_AttackBattleArray.as
//  Purpose:      攻击阵图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	/**
	 * 攻击阵图的返回的参数组成的结构体
	 */
	public final class SRetParam_AttackBattleArray
	{
		public var eBattleArrayRet:uint; //(枚举类型：EBattleArrayRet)操作结果
		public var dwFailCd:uint; //(无符号32位整数)战败cd

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_AttackBattleArray _name_={name_} eBattleArrayRet={eBattleArrayRet} dwFailCd={dwFailCd}/>;
			else
				topXml = <SRetParam_AttackBattleArray eBattleArrayRet={eBattleArrayRet} dwFailCd={dwFailCd}/>;
			return topXml;
		}
	}
}
