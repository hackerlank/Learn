/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetCoutdown.as
//  Purpose:      获取活动开始倒计时
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	/**
	 * 获取活动开始倒计时的返回的参数组成的结构体
	 */
	public final class SRetParam_GetCoutdown
	{
		public var dwTime:uint; //(无符号32位整数)倒计时时间
		public var sPlayerInfo:SAnswerPlayer; //玩家信息
		public var bRet:Boolean; //是否开启面板

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetCoutdown _name_={name_} dwTime={dwTime} bRet={bRet}/>;
			else
				topXml = <SRetParam_GetCoutdown dwTime={dwTime} bRet={bRet}/>;
			if(sPlayerInfo != null)
				topXml.appendChild(sPlayerInfo.toXML("sPlayerInfo"));
			return topXml;
		}
	}
}
