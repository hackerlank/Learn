/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_JumpMap.as
//  Purpose:      请求跳地图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	/**
	 * 请求跳地图的返回的参数组成的结构体
	 */
	public final class SRetParam_JumpMap
	{
		public var byRet:uint; //(无符号8位整数)0成功
		public var wMapID:uint; //(无符号16位整数)地图ID
		public var byIndex:uint; //(无符号8位整数)地图序号,255表示任意地图

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_JumpMap _name_={name_} byRet={byRet} wMapID={wMapID} byIndex={byIndex}/>;
			else
				topXml = <SRetParam_JumpMap byRet={byRet} wMapID={wMapID} byIndex={byIndex}/>;
			return topXml;
		}
	}
}
