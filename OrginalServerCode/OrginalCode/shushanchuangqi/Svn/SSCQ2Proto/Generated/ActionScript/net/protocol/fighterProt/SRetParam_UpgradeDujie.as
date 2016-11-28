/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UpgradeDujie.as
//  Purpose:      渡劫升级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 渡劫升级的返回的参数组成的结构体
	 */
	public final class SRetParam_UpgradeDujie
	{
		public var eResult:uint; //(枚举类型：EDujieResult)结果
		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UpgradeDujie _name_={name_} eResult={eResult} qwInstID={qwInstID}/>;
			else
				topXml = <SRetParam_UpgradeDujie eResult={eResult} qwInstID={qwInstID}/>;
			return topXml;
		}
	}
}
