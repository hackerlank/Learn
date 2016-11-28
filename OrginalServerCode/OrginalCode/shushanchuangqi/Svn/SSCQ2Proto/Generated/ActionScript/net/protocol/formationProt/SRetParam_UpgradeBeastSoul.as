/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UpgradeBeastSoul.as
//  Purpose:      升级兽魂
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import net.protocol.roleInfoDefine.SBeastSoulInfo;

	/**
	 * 升级兽魂的返回的参数组成的结构体
	 */
	public final class SRetParam_UpgradeBeastSoul
	{
		public var eResult:uint; //(枚举类型：EBeastSoulResult)获取结果
		public var vecBeastSoul:Vector.<SBeastSoulInfo>; //兽魂信息
		public var vecItem:Vector.<SBeastSoulItem>; //包裹或仓库中道具的列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UpgradeBeastSoul _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_UpgradeBeastSoul eResult={eResult}/>;
			if(vecBeastSoul != null)
			{
				var vecBeastSoulXml:XML = <Vec_SBeastSoulInfo _name_="vecBeastSoul"/>;
				for each(var s1:SBeastSoulInfo in vecBeastSoul)
					vecBeastSoulXml.appendChild(s1.toXML());
				topXml.appendChild(vecBeastSoulXml);
			}
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SBeastSoulItem _name_="vecItem"/>;
				for each(var s2:SBeastSoulItem in vecItem)
					vecItemXml.appendChild(s2.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}
	}
}
