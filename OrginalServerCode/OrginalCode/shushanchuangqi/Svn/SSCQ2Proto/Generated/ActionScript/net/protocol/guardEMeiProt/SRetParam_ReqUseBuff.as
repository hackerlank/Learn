/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqUseBuff.as
//  Purpose:      请求使用Buff
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	/**
	 * 请求使用Buff的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqUseBuff
	{
		public var vecGEMBattleFighterInfo:Vector.<SGEMBattleFighterInfo>; //守卫峨眉参战散仙信息
		public var vecGEMBuffInfo:Vector.<SGEMBuffInfo>; //守卫峨眉Buff信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqUseBuff _name_={name_}/>;
			else
				topXml = <SRetParam_ReqUseBuff/>;
			if(vecGEMBattleFighterInfo != null)
			{
				var vecGEMBattleFighterInfoXml:XML = <Vec_SGEMBattleFighterInfo _name_="vecGEMBattleFighterInfo"/>;
				for each(var s1:SGEMBattleFighterInfo in vecGEMBattleFighterInfo)
					vecGEMBattleFighterInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGEMBattleFighterInfoXml);
			}
			if(vecGEMBuffInfo != null)
			{
				var vecGEMBuffInfoXml:XML = <Vec_SGEMBuffInfo _name_="vecGEMBuffInfo"/>;
				for each(var s2:SGEMBuffInfo in vecGEMBuffInfo)
					vecGEMBuffInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecGEMBuffInfoXml);
			}
			return topXml;
		}
	}
}
