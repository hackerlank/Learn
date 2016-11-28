/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_EquipTitle.as
//  Purpose:      刷新称号列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.titleProt
{
	/**
	 * 刷新称号列表的返回的参数组成的结构体
	 */
	public final class SRetParam_EquipTitle
	{
		public var eResult:uint; //(枚举类型：ETitleResult)操作结果
		public var wId:uint; //(无符号16位整数)称号ID
		public var byPos:uint; //(无符号8位整数)装备位置

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_EquipTitle _name_={name_} eResult={eResult} wId={wId} byPos={byPos}/>;
			else
				topXml = <SRetParam_EquipTitle eResult={eResult} wId={wId} byPos={byPos}/>;
			return topXml;
		}
	}
}
