/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_Answer.as
//  Purpose:      玩家答题
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	/**
	 * 玩家答题的返回的参数组成的结构体
	 */
	public final class SRetParam_Answer
	{
		public var dwIndex:uint; //(无符号32位整数)题目
		public var eResult:uint; //(枚举类型：EAnswerResult)答题结果返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_Answer _name_={name_} dwIndex={dwIndex} eResult={eResult}/>;
			else
				topXml = <SRetParam_Answer dwIndex={dwIndex} eResult={eResult}/>;
			return topXml;
		}
	}
}
