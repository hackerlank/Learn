/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_IntensifyOneKey.as
//  Purpose:      装备法宝一键强化
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	/**
	 * 装备法宝一键强化的返回的参数组成的结构体
	 */
	public final class SRetParam_IntensifyOneKey
	{
		public var bSucess:Boolean; //成功/失败
		public var dwIntensifyCount:uint; //(无符号32位整数)强化次数（包括成功
		public var eResult:uint; //(枚举类型：EEquipTrumpIntensifyResult)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_IntensifyOneKey _name_={name_} bSucess={bSucess} dwIntensifyCount={dwIntensifyCount} eResult={eResult}/>;
			else
				topXml = <SRetParam_IntensifyOneKey bSucess={bSucess} dwIntensifyCount={dwIntensifyCount} eResult={eResult}/>;
			return topXml;
		}
	}
}
