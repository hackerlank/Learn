/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GeCollectionInfo.as
//  Purpose:      获取收藏信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.collectionProt
{
	/**
	 * 获取收藏信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GeCollectionInfo
	{
		public var vecCollectionInfo:Vector.<SCollectionInfo>; //收藏榜信息
		public var wLevel:uint; //(无符号16位整数)收藏等级
		public var dwAP:uint; //(无符号32位整数)收藏点

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GeCollectionInfo _name_={name_} wLevel={wLevel} dwAP={dwAP}/>;
			else
				topXml = <SRetParam_GeCollectionInfo wLevel={wLevel} dwAP={dwAP}/>;
			if(vecCollectionInfo != null)
			{
				var vecCollectionInfoXml:XML = <Vec_SCollectionInfo _name_="vecCollectionInfo"/>;
				for each(var s1:SCollectionInfo in vecCollectionInfo)
					vecCollectionInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecCollectionInfoXml);
			}
			return topXml;
		}
	}
}
