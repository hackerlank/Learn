/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SXiheRequest.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 羲和神车的请求帮助信息
	 */
	public final class SXiheRequest
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //请求玩家的名字
		public var byReqColor:uint; //(无符号8位整数)请求玩家的名字颜色
		public var byPos:uint; //(无符号8位整数)货物顺序索引(0~7)
		public var byTruckID:uint; //(无符号8位整数)货号ID
		public var bystatus:uint; //(无符号8位整数)状态
		public var strHelpName:String; //帮助玩家的名字
		public var byHelpColor:uint; //(无符号8位整数)帮助者名字颜色

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, strName:String, byReqColor:uint, byPos:uint, byTruckID:uint, 
			bystatus:uint, strHelpName:String, byHelpColor:uint):SXiheRequest
		{
			var s_:SXiheRequest = new SXiheRequest();
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.byReqColor = byReqColor;
			s_.byPos = byPos;
			s_.byTruckID = byTruckID;
			s_.bystatus = bystatus;
			s_.strHelpName = strHelpName;
			s_.byHelpColor = byHelpColor;
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
				topXml = <SXiheRequest _name_={name_} qwRoleID={qwRoleID} strName={strName} byReqColor={byReqColor} byPos={byPos} byTruckID={byTruckID}
				 bystatus={bystatus} strHelpName={strHelpName} byHelpColor={byHelpColor}/>;
			else
				topXml = <SXiheRequest qwRoleID={qwRoleID} strName={strName} byReqColor={byReqColor} byPos={byPos} byTruckID={byTruckID}
				 bystatus={bystatus} strHelpName={strHelpName} byHelpColor={byHelpColor}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.byReqColor = byReqColor;
			obj_.byPos = byPos;
			obj_.byTruckID = byTruckID;
			obj_.bystatus = bystatus;
			obj_.strHelpName = strHelpName;
			obj_.byHelpColor = byHelpColor;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SXiheRequest
		{
			var s_:SXiheRequest = new SXiheRequest();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byReqColor:uint = bytes.readUnsignedByte();
			s_.byReqColor = byReqColor;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var byTruckID:uint = bytes.readUnsignedByte();
			s_.byTruckID = byTruckID;
			var bystatus:uint = bytes.readUnsignedByte();
			s_.bystatus = bystatus;
			var strHelpName:String = BytesUtil.readString(bytes);
			s_.strHelpName = strHelpName;
			var byHelpColor:uint = bytes.readUnsignedByte();
			s_.byHelpColor = byHelpColor;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SXiheRequest>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SXiheRequest> = new Vector.<SXiheRequest>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SXiheRequest = SXiheRequest.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byReqColor);
			bytes.writeByte(byPos);
			bytes.writeByte(byTruckID);
			bytes.writeByte(bystatus);
			BytesUtil.writeString(bytes, strHelpName);
			bytes.writeByte(byHelpColor);
		}

		public static function vectorToByteArray(vec:Vector.<SXiheRequest>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SXiheRequest in vec)
				s.toByteArray(bytes);
		}
	}
}
