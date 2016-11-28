/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReFluseLadderEnemy.as
//  Purpose:      请求对手信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求对手信息的返回的参数组成的结构体
	 */
	public final class SRetParam_ReFluseLadderEnemy
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求刷将返回
		public var vecFlushFigter:Vector.<SFlushFitherForClient>; //最近刷的对手

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReFluseLadderEnemy _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_ReFluseLadderEnemy eResult={eResult}/>;
			if(vecFlushFigter != null)
			{
				var vecFlushFigterXml:XML = <Vec_SFlushFitherForClient _name_="vecFlushFigter"/>;
				for each(var s1:SFlushFitherForClient in vecFlushFigter)
					vecFlushFigterXml.appendChild(s1.toXML());
				topXml.appendChild(vecFlushFigterXml);
			}
			return topXml;
		}
	}
}
