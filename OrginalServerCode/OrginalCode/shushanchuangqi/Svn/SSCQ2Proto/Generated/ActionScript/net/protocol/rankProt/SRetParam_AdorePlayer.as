/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_AdorePlayer.as
//  Purpose:      崇拜玩家
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	/**
	 * 崇拜玩家的返回的参数组成的结构体
	 */
	public final class SRetParam_AdorePlayer
	{
		public var eResult:uint; //(枚举类型：ERankResult)崇拜结果
		public var dwCount:uint; //(无符号32位整数)崇拜数量
		public var dwSelfCount:uint; //(无符号32位整数)自己剩余崇拜数量

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_AdorePlayer _name_={name_} eResult={eResult} dwCount={dwCount} dwSelfCount={dwSelfCount}/>;
			else
				topXml = <SRetParam_AdorePlayer eResult={eResult} dwCount={dwCount} dwSelfCount={dwSelfCount}/>;
			return topXml;
		}
	}
}
