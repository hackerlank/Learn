/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_AddScore.as
//  Purpose:      三消中积分累计
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	/**
	 * 三消中积分累计的返回的参数组成的结构体
	 */
	public final class SRetParam_AddScore
	{
		public var wNextPwd:uint; //(无符号16位整数)下一次密码
		public var byTotalStep:uint; //(无符号8位整数)剩余步数
		public var wTotalScore:uint; //(无符号16位整数)总积分
		public var eResult:uint; //(枚举类型：EShengLingResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_AddScore _name_={name_} wNextPwd={wNextPwd} byTotalStep={byTotalStep} wTotalScore={wTotalScore} eResult={eResult}/>;
			else
				topXml = <SRetParam_AddScore wNextPwd={wNextPwd} byTotalStep={byTotalStep} wTotalScore={wTotalScore} eResult={eResult}/>;
			return topXml;
		}
	}
}
