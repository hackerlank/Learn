/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FlushNewEnemy.as
//  Purpose:      请求刷将
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求刷将的返回的参数组成的结构体
	 */
	public final class SRetParam_FlushNewEnemy
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求刷将返回
		public var wSelfReflush:uint; //(无符号16位整数)当前购买刷新次数
		public var wSelfFreeReflush:uint; //(无符号16位整数)当前VIP免费刷新次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FlushNewEnemy _name_={name_} eResult={eResult} wSelfReflush={wSelfReflush} wSelfFreeReflush={wSelfFreeReflush}/>;
			else
				topXml = <SRetParam_FlushNewEnemy eResult={eResult} wSelfReflush={wSelfReflush} wSelfFreeReflush={wSelfFreeReflush}/>;
			return topXml;
		}
	}
}
