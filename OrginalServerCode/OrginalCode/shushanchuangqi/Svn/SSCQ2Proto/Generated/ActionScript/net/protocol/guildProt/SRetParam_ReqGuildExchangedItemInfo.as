/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqGuildExchangedItemInfo.as
//  Purpose:      请求帮派兑换物品信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	/**
	 * 请求帮派兑换物品信息的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqGuildExchangedItemInfo
	{
		public var vecLingShanType:Vector.<uint>; //(无符号8位整数)灵山类型
		public var vecGuildExchangedItem:Vector.<SGuildExchangedItem>; //兑换物品信息
		public var dwGUildAllMemberExchangedItemNum:uint; //(无符号32位整数)帮派所有成员兑换物品总数量
		public var dwPlayerExchangedItemNum:uint; //(无符号32位整数)玩家兑换物品总数量
		public var eMemberLastRank:uint; //(枚举类型：EMemberRank)玩家上一次帮派职位

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqGuildExchangedItemInfo _name_={name_} dwGUildAllMemberExchangedItemNum={dwGUildAllMemberExchangedItemNum} dwPlayerExchangedItemNum={dwPlayerExchangedItemNum} eMemberLastRank={eMemberLastRank}/>;
			else
				topXml = <SRetParam_ReqGuildExchangedItemInfo dwGUildAllMemberExchangedItemNum={dwGUildAllMemberExchangedItemNum} dwPlayerExchangedItemNum={dwPlayerExchangedItemNum} eMemberLastRank={eMemberLastRank}/>;
			if(vecLingShanType != null)
			{
				var vecLingShanTypeXml:XML = <Vec_UINT8 _name_="vecLingShanType"/>;
				var text1:String = "";
				for each(var value1:uint in vecLingShanType)
					text1 += "[" + value1 + "]";
				vecLingShanTypeXml.appendChild(text1);
				topXml.appendChild(vecLingShanTypeXml);
			}
			if(vecGuildExchangedItem != null)
			{
				var vecGuildExchangedItemXml:XML = <Vec_SGuildExchangedItem _name_="vecGuildExchangedItem"/>;
				for each(var s2:SGuildExchangedItem in vecGuildExchangedItem)
					vecGuildExchangedItemXml.appendChild(s2.toXML());
				topXml.appendChild(vecGuildExchangedItemXml);
			}
			return topXml;
		}
	}
}
