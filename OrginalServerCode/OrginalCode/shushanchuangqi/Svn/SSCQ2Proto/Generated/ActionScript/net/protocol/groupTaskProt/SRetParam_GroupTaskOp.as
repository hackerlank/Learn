/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GroupTaskOp.as
//  Purpose:      请求操作
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	/**
	 * 请求操作的返回的参数组成的结构体
	 */
	public final class SRetParam_GroupTaskOp
	{
		public var eResult:uint; //(枚举类型：EGroupTaskResult)操作结果
		public var eState:uint; //(枚举类型：EGroupStudyState)当前清修状态

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GroupTaskOp _name_={name_} eResult={eResult} eState={eState}/>;
			else
				topXml = <SRetParam_GroupTaskOp eResult={eResult} eState={eState}/>;
			return topXml;
		}
	}
}
