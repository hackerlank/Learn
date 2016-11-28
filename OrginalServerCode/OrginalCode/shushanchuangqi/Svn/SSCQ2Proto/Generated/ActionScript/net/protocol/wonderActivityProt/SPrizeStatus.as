/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrizeStatus.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 状态信息
	 */
	public final class SPrizeStatus
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wActID:uint; //(无符号16位整数)活动ID
		public var vecStatus:Vector.<uint>; //(无符号8位整数)活动状态

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wActID:uint, vecStatus:Vector.<uint>):SPrizeStatus
		{
			var s_:SPrizeStatus = new SPrizeStatus();
			s_.qwRoleID = qwRoleID;
			s_.wActID = wActID;
			s_.vecStatus = vecStatus;
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
				topXml = <SPrizeStatus _name_={name_} qwRoleID={qwRoleID} wActID={wActID}/>;
			else
				topXml = <SPrizeStatus qwRoleID={qwRoleID} wActID={wActID}/>;
			if(vecStatus != null)
			{
				var vecStatusXml:XML = <Vec_UINT8 _name_="vecStatus"/>;
				var text1:String = "";
				for each(var value1:uint in vecStatus)
					text1 += "[" + value1 + "]";
				vecStatusXml.appendChild(text1);
				topXml.appendChild(vecStatusXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wActID = wActID;
			obj_.vecStatus = vecStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrizeStatus
		{
			var s_:SPrizeStatus = new SPrizeStatus();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wActID:uint = bytes.readUnsignedShort();
			s_.wActID = wActID;
			var vecStatus:Vector.<uint> = BytesUtil.readVecUByte(bytes);
			s_.vecStatus = vecStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrizeStatus>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrizeStatus> = new Vector.<SPrizeStatus>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrizeStatus = SPrizeStatus.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wActID);
			BytesUtil.writeVecUByte(bytes, vecStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SPrizeStatus>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrizeStatus in vec)
				s.toByteArray(bytes);
		}
	}
}
