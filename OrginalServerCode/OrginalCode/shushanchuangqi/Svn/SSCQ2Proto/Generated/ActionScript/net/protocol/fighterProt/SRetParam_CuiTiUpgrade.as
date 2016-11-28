/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_CuiTiUpgrade.as
//  Purpose:      淬体升级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 淬体升级的返回的参数组成的结构体
	 */
	public final class SRetParam_CuiTiUpgrade
	{
		public var eResult:uint; //(枚举类型：ECuiTiResult)结果
		public var byLevel:uint; //(无符号8位整数)当前淬体等级

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_CuiTiUpgrade _name_={name_} eResult={eResult} byLevel={byLevel}/>;
			else
				topXml = <SRetParam_CuiTiUpgrade eResult={eResult} byLevel={byLevel}/>;
			return topXml;
		}
	}
}
