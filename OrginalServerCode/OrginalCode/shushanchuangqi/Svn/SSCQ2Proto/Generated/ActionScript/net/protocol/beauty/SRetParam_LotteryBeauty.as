/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_LotteryBeauty.as
//  Purpose:      抽奖
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import net.protocol.itemProt.SItemGenInfo;

	/**
	 * 抽奖的返回的参数组成的结构体
	 */
	public final class SRetParam_LotteryBeauty
	{
		public var eRet:uint; //(枚举类型：EBeautyRet)操作结果
		public var vecItemGenInfo:Vector.<SItemGenInfo>; //物品列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_LotteryBeauty _name_={name_} eRet={eRet}/>;
			else
				topXml = <SRetParam_LotteryBeauty eRet={eRet}/>;
			if(vecItemGenInfo != null)
			{
				var vecItemGenInfoXml:XML = <Vec_SItemGenInfo _name_="vecItemGenInfo"/>;
				for each(var s1:SItemGenInfo in vecItemGenInfo)
					vecItemGenInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemGenInfoXml);
			}
			return topXml;
		}
	}
}
