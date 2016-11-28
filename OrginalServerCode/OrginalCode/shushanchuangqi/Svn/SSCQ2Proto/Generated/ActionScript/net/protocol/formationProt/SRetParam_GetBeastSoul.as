/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetBeastSoul.as
//  Purpose:      获取兽魂信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import net.protocol.roleInfoDefine.SBeastSoulInfo;

	/**
	 * 获取兽魂信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetBeastSoul
	{
		public var eResult:uint; //(枚举类型：EBeastSoulResult)获取结果
		public var vecBeastSoul:Vector.<SBeastSoulInfo>; //兽魂信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetBeastSoul _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetBeastSoul eResult={eResult}/>;
			if(vecBeastSoul != null)
			{
				var vecBeastSoulXml:XML = <Vec_SBeastSoulInfo _name_="vecBeastSoul"/>;
				for each(var s1:SBeastSoulInfo in vecBeastSoul)
					vecBeastSoulXml.appendChild(s1.toXML());
				topXml.appendChild(vecBeastSoulXml);
			}
			return topXml;
		}
	}
}
