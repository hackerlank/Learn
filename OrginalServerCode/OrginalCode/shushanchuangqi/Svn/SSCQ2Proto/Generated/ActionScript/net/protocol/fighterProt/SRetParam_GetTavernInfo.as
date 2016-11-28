/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTavernInfo.as
//  Purpose:      获取客栈信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 获取客栈信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTavernInfo
	{
		public var dwDrawCount:uint; //(无符号32位整数)免费求签次数
		public var vecTavernInfo:Vector.<STavernInfo>; //具体客栈信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTavernInfo _name_={name_} dwDrawCount={dwDrawCount}/>;
			else
				topXml = <SRetParam_GetTavernInfo dwDrawCount={dwDrawCount}/>;
			if(vecTavernInfo != null)
			{
				var vecTavernInfoXml:XML = <Vec_STavernInfo _name_="vecTavernInfo"/>;
				for each(var s1:STavernInfo in vecTavernInfo)
					vecTavernInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTavernInfoXml);
			}
			return topXml;
		}
	}
}
