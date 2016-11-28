/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ShotOffHelpTripod.as
//  Purpose:      踢出九疑鼎协助者
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	/**
	 * 踢出九疑鼎协助者的返回的参数组成的结构体
	 */
	public final class SRetParam_ShotOffHelpTripod
	{
		public var eResult:uint; //(枚举类型：ETripodType)结果
		public var byPos:uint; //(无符号8位整数)协助位置(0,1,2)
		public var byType:uint; //(无符号8位整数)0散仙 1玩家

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ShotOffHelpTripod _name_={name_} eResult={eResult} byPos={byPos} byType={byType}/>;
			else
				topXml = <SRetParam_ShotOffHelpTripod eResult={eResult} byPos={byPos} byType={byType}/>;
			return topXml;
		}
	}
}
