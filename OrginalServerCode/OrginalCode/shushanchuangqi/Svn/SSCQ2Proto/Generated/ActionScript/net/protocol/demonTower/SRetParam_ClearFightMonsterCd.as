/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ClearFightMonsterCd.as
//  Purpose:      清除pve战斗cd
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	/**
	 * 清除pve战斗cd的返回的参数组成的结构体
	 */
	public final class SRetParam_ClearFightMonsterCd
	{
		public var bRet:uint; //(无符号8位整数)0成功 其他失败

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ClearFightMonsterCd _name_={name_} bRet={bRet}/>;
			else
				topXml = <SRetParam_ClearFightMonsterCd bRet={bRet}/>;
			return topXml;
		}
	}
}
