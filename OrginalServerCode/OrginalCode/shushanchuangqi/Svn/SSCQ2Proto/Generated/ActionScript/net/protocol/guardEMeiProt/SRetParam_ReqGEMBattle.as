/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqGEMBattle.as
//  Purpose:      请求守卫峨眉战斗
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	/**
	 * 请求守卫峨眉战斗的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqGEMBattle
	{
		public var eGEMBattleRet:int; //(枚举类型：EGEMBattleRet)战斗结果
		public var sGEMPrepareBattleInfo:SGEMPrepareBattleInfo; //守卫峨眉下一波准备战斗信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqGEMBattle _name_={name_} eGEMBattleRet={eGEMBattleRet}/>;
			else
				topXml = <SRetParam_ReqGEMBattle eGEMBattleRet={eGEMBattleRet}/>;
			if(sGEMPrepareBattleInfo != null)
				topXml.appendChild(sGEMPrepareBattleInfo.toXML("sGEMPrepareBattleInfo"));
			return topXml;
		}
	}
}
