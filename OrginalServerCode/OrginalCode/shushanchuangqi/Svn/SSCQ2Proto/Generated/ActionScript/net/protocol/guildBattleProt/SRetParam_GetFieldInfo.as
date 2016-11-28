/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFieldInfo.as
//  Purpose:      帮派战场信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	/**
	 * 帮派战场信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFieldInfo
	{
		public var eResult:uint; //(枚举类型：EGBResult)返回结果
		public var vecFieldInfo:Vector.<SFieldInfo>; //帮派战场信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFieldInfo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetFieldInfo eResult={eResult}/>;
			if(vecFieldInfo != null)
			{
				var vecFieldInfoXml:XML = <Vec_SFieldInfo _name_="vecFieldInfo"/>;
				for each(var s1:SFieldInfo in vecFieldInfo)
					vecFieldInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecFieldInfoXml);
			}
			return topXml;
		}
	}
}
