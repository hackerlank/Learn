/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFeedBackList.as
//  Purpose:      获取回馈列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
{
	/**
	 * 获取回馈列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFeedBackList
	{
		public var vecFeedBackInfo:Vector.<SFeedBackInfo>; //回馈信息列表
		public var vecSBuyDiscountInfo:Vector.<SBuyDiscountInfo>; //折扣限购信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFeedBackList _name_={name_}/>;
			else
				topXml = <SRetParam_GetFeedBackList/>;
			if(vecFeedBackInfo != null)
			{
				var vecFeedBackInfoXml:XML = <Vec_SFeedBackInfo _name_="vecFeedBackInfo"/>;
				for each(var s1:SFeedBackInfo in vecFeedBackInfo)
					vecFeedBackInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecFeedBackInfoXml);
			}
			if(vecSBuyDiscountInfo != null)
			{
				var vecSBuyDiscountInfoXml:XML = <Vec_SBuyDiscountInfo _name_="vecSBuyDiscountInfo"/>;
				for each(var s2:SBuyDiscountInfo in vecSBuyDiscountInfo)
					vecSBuyDiscountInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecSBuyDiscountInfoXml);
			}
			return topXml;
		}
	}
}
