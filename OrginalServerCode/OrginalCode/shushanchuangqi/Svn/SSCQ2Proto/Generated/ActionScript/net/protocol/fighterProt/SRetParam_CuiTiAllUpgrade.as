/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_CuiTiAllUpgrade.as
//  Purpose:      散仙淬体全体(六种)升级一次
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 散仙淬体全体(六种)升级一次的返回的参数组成的结构体
	 */
	public final class SRetParam_CuiTiAllUpgrade
	{
		public var eResult:uint; //(枚举类型：ECuiTiResult)结果
		public var vecLevel:Vector.<uint>; //(无符号8位整数)当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_CuiTiAllUpgrade _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_CuiTiAllUpgrade eResult={eResult}/>;
			if(vecLevel != null)
			{
				var vecLevelXml:XML = <Vec_UINT8 _name_="vecLevel"/>;
				var text1:String = "";
				for each(var value1:uint in vecLevel)
					text1 += "[" + value1 + "]";
				vecLevelXml.appendChild(text1);
				topXml.appendChild(vecLevelXml);
			}
			return topXml;
		}
	}
}
