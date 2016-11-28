/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRecharge.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * DB存储玩家充值仙石的结构体
	 */
	public final class SRecharge
	{
		public var strNo:String; //充值流水号
		public var qwRoleID:BigInteger; //(无符号64位整数)用户ID
		public var wGoldID:uint; //(无符号16位整数)仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])
		public var dwCount:uint; //(无符号32位整数)充值的仙石包数量
		public var dwGold:uint; //(无符号32位整数)充值的仙石总数
		public var byStatus:uint; //(无符号8位整数)仙石是否到账(0-准备/不成功 1-成功,2-补单成功)
		public var dwHappenedTime:uint; //(无符号32位整数)充值时间

		/**
		 * 辅助创建函数
		 */
		public static function create(strNo:String, qwRoleID:BigInteger, wGoldID:uint, dwCount:uint, dwGold:uint, 
			byStatus:uint, dwHappenedTime:uint):SRecharge
		{
			var s_:SRecharge = new SRecharge();
			s_.strNo = strNo;
			s_.qwRoleID = qwRoleID;
			s_.wGoldID = wGoldID;
			s_.dwCount = dwCount;
			s_.dwGold = dwGold;
			s_.byStatus = byStatus;
			s_.dwHappenedTime = dwHappenedTime;
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
				topXml = <SRecharge _name_={name_} strNo={strNo} qwRoleID={qwRoleID} wGoldID={wGoldID} dwCount={dwCount} dwGold={dwGold}
				 byStatus={byStatus} dwHappenedTime={dwHappenedTime}/>;
			else
				topXml = <SRecharge strNo={strNo} qwRoleID={qwRoleID} wGoldID={wGoldID} dwCount={dwCount} dwGold={dwGold}
				 byStatus={byStatus} dwHappenedTime={dwHappenedTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strNo = strNo;
			obj_.qwRoleID = qwRoleID;
			obj_.wGoldID = wGoldID;
			obj_.dwCount = dwCount;
			obj_.dwGold = dwGold;
			obj_.byStatus = byStatus;
			obj_.dwHappenedTime = dwHappenedTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRecharge
		{
			var s_:SRecharge = new SRecharge();
			var strNo:String = BytesUtil.readString(bytes);
			s_.strNo = strNo;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wGoldID:uint = bytes.readUnsignedShort();
			s_.wGoldID = wGoldID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var dwGold:uint = bytes.readUnsignedInt();
			s_.dwGold = dwGold;
			var byStatus:uint = bytes.readUnsignedByte();
			s_.byStatus = byStatus;
			var dwHappenedTime:uint = bytes.readUnsignedInt();
			s_.dwHappenedTime = dwHappenedTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRecharge>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRecharge> = new Vector.<SRecharge>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRecharge = SRecharge.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strNo);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wGoldID);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeUnsignedInt(dwGold);
			bytes.writeByte(byStatus);
			bytes.writeUnsignedInt(dwHappenedTime);
		}

		public static function vectorToByteArray(vec:Vector.<SRecharge>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRecharge in vec)
				s.toByteArray(bytes);
		}
	}
}
