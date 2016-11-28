/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMallInfo.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 商城信息
	 */
	public final class SMallInfo
	{
		public var dwInstID:uint; //(无符号32位整数)商品编号
		public var strName:String; //商品名称
		public var wItemID:uint; //(无符号16位整数)物品ID
		public var dwItemCount:uint; //(无符号32位整数)物品数量
		public var eMoneyType:uint; //(枚举类型：protoCommon.EMoneyType)所需货币类型
		public var dwPrice:uint; //(无符号32位整数)价格
		public var byVIP:uint; //(无符号8位整数)VIP等级限制
		public var wIcon:uint; //(无符号16位整数)图标
		public var dwDayCntLimit:uint; //(无符号32位整数)限购数量

		/**
		 * 辅助创建函数
		 */
		public static function create(dwInstID:uint, strName:String, wItemID:uint, dwItemCount:uint, eMoneyType:uint, 
			dwPrice:uint, byVIP:uint, wIcon:uint, dwDayCntLimit:uint):SMallInfo
		{
			var s_:SMallInfo = new SMallInfo();
			s_.dwInstID = dwInstID;
			s_.strName = strName;
			s_.wItemID = wItemID;
			s_.dwItemCount = dwItemCount;
			s_.eMoneyType = eMoneyType;
			s_.dwPrice = dwPrice;
			s_.byVIP = byVIP;
			s_.wIcon = wIcon;
			s_.dwDayCntLimit = dwDayCntLimit;
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
				topXml = <SMallInfo _name_={name_} dwInstID={dwInstID} strName={strName} wItemID={wItemID} dwItemCount={dwItemCount} eMoneyType={eMoneyType}
				 dwPrice={dwPrice} byVIP={byVIP} wIcon={wIcon} dwDayCntLimit={dwDayCntLimit}/>;
			else
				topXml = <SMallInfo dwInstID={dwInstID} strName={strName} wItemID={wItemID} dwItemCount={dwItemCount} eMoneyType={eMoneyType}
				 dwPrice={dwPrice} byVIP={byVIP} wIcon={wIcon} dwDayCntLimit={dwDayCntLimit}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwInstID = dwInstID;
			obj_.strName = strName;
			obj_.wItemID = wItemID;
			obj_.dwItemCount = dwItemCount;
			obj_.eMoneyType = eMoneyType;
			obj_.dwPrice = dwPrice;
			obj_.byVIP = byVIP;
			obj_.wIcon = wIcon;
			obj_.dwDayCntLimit = dwDayCntLimit;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMallInfo
		{
			var s_:SMallInfo = new SMallInfo();
			var dwInstID:uint = bytes.readUnsignedInt();
			s_.dwInstID = dwInstID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var dwItemCount:uint = bytes.readUnsignedInt();
			s_.dwItemCount = dwItemCount;
			var eMoneyType:uint = bytes.readUnsignedByte();
			s_.eMoneyType = eMoneyType;
			var dwPrice:uint = bytes.readUnsignedInt();
			s_.dwPrice = dwPrice;
			var byVIP:uint = bytes.readUnsignedByte();
			s_.byVIP = byVIP;
			var wIcon:uint = bytes.readUnsignedShort();
			s_.wIcon = wIcon;
			var dwDayCntLimit:uint = bytes.readUnsignedInt();
			s_.dwDayCntLimit = dwDayCntLimit;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMallInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMallInfo> = new Vector.<SMallInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMallInfo = SMallInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwInstID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(dwItemCount);
			bytes.writeByte(eMoneyType);
			bytes.writeUnsignedInt(dwPrice);
			bytes.writeByte(byVIP);
			bytes.writeShort(wIcon);
			bytes.writeUnsignedInt(dwDayCntLimit);
		}

		public static function vectorToByteArray(vec:Vector.<SMallInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMallInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
