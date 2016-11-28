/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UseCard.as
//  Purpose:      使用卡片
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 使用卡片的返回的参数组成的结构体
	 */
	public final class SRetParam_UseCard
	{
		public var sCard:SCard; //卡片信息
		public var sInfo:SPlayerInfo; //玩家数据
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var eResult:uint; //(枚举类型：EShengLingResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UseCard _name_={name_} qwBattleID={qwBattleID} eResult={eResult}/>;
			else
				topXml = <SRetParam_UseCard qwBattleID={qwBattleID} eResult={eResult}/>;
			if(sCard != null)
				topXml.appendChild(sCard.toXML("sCard"));
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
