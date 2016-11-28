/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDemonFloorPage.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 镇守榜分页信息
	 */
	public final class SDemonFloorPage
	{
		public var wCurPage:uint; //(无符号16位整数)当前页码
		public var wMaxPage:uint; //(无符号16位整数)最大页码
		public var vecDemonFloorPlayer:Vector.<SDemonFloorPlayer>; //分页信息

		/**
		 * 辅助创建函数
		 */
		public static function create(wCurPage:uint, wMaxPage:uint, vecDemonFloorPlayer:Vector.<SDemonFloorPlayer>):SDemonFloorPage
		{
			var s_:SDemonFloorPage = new SDemonFloorPage();
			s_.wCurPage = wCurPage;
			s_.wMaxPage = wMaxPage;
			s_.vecDemonFloorPlayer = vecDemonFloorPlayer;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SDemonFloorPage _name_={name_} wCurPage={wCurPage} wMaxPage={wMaxPage}/>;
			else
				topXml = <SDemonFloorPage wCurPage={wCurPage} wMaxPage={wMaxPage}/>;
			if(vecDemonFloorPlayer != null)
			{
				var vecDemonFloorPlayerXml:XML = <Vec_SDemonFloorPlayer _name_="vecDemonFloorPlayer"/>;
				for each(var s1:SDemonFloorPlayer in vecDemonFloorPlayer)
					vecDemonFloorPlayerXml.appendChild(s1.toXML());
				topXml.appendChild(vecDemonFloorPlayerXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wCurPage = wCurPage;
			obj_.wMaxPage = wMaxPage;
			obj_.vecDemonFloorPlayer = vecDemonFloorPlayer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDemonFloorPage
		{
			var s_:SDemonFloorPage = new SDemonFloorPage();
			var wCurPage:uint = bytes.readUnsignedShort();
			s_.wCurPage = wCurPage;
			var wMaxPage:uint = bytes.readUnsignedShort();
			s_.wMaxPage = wMaxPage;
			var vecDemonFloorPlayer:Vector.<SDemonFloorPlayer> = SDemonFloorPlayer.vectorFromByteArray(bytes);
			s_.vecDemonFloorPlayer = vecDemonFloorPlayer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDemonFloorPage>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDemonFloorPage> = new Vector.<SDemonFloorPage>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDemonFloorPage = SDemonFloorPage.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wCurPage);
			bytes.writeShort(wMaxPage);
			SDemonFloorPlayer.vectorToByteArray(vecDemonFloorPlayer, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SDemonFloorPage>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDemonFloorPage in vec)
				s.toByteArray(bytes);
		}
	}
}
