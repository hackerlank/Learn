/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqFighterXinFaInfo.as
//  Purpose:      请求散仙心法
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 请求散仙心法的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqFighterXinFaInfo
	{
		public var vecFighterXinFa:Vector.<SXinFaInfo>; //散仙已经学会的心法信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqFighterXinFaInfo _name_={name_}/>;
			else
				topXml = <SRetParam_ReqFighterXinFaInfo/>;
			if(vecFighterXinFa != null)
			{
				var vecFighterXinFaXml:XML = <Vec_SXinFaInfo _name_="vecFighterXinFa"/>;
				for each(var s1:SXinFaInfo in vecFighterXinFa)
					vecFighterXinFaXml.appendChild(s1.toXML());
				topXml.appendChild(vecFighterXinFaXml);
			}
			return topXml;
		}
	}
}
