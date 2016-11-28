/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ChangeModel.as
//  Purpose:      更换模型信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	/**
	 * 更换模型信息的返回的参数组成的结构体
	 */
	public final class SRetParam_ChangeModel
	{
		public var eRet:uint; //(枚举类型：ELingShanOP)
		public var dwModelID:uint; //(无符号32位整数)模型id

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ChangeModel _name_={name_} eRet={eRet} dwModelID={dwModelID}/>;
			else
				topXml = <SRetParam_ChangeModel eRet={eRet} dwModelID={dwModelID}/>;
			return topXml;
		}
	}
}
