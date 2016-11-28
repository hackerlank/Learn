/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_WareGemStone.as
//  Purpose:      穿戴宝石
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 穿戴宝石的返回的参数组成的结构体
	 */
	public final class SRetParam_WareGemStone
	{
		public var eResult:uint; //(枚举类型：EGemstoneResult)结果
		public var qwFighterID:BigInteger; //(无符号64位整数)将ID
		public var byPos:uint; //(无符号8位整数)穿戴位置
		public var Item:SGemstone; //宝石

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_WareGemStone _name_={name_} eResult={eResult} qwFighterID={qwFighterID} byPos={byPos}/>;
			else
				topXml = <SRetParam_WareGemStone eResult={eResult} qwFighterID={qwFighterID} byPos={byPos}/>;
			if(Item != null)
				topXml.appendChild(Item.toXML("Item"));
			return topXml;
		}
	}
}
