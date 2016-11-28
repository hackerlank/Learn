/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEventInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 事件信息
	 */
	public final class SEventInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var byActClassID:uint; //(无符号8位整数)活动类型ID
		public var dwEventInstID:uint; //(无符号32位整数)事件实例ID
		public var dwApplyID:uint; //(无符号32位整数)具体活动ID
		public var wEventStatus:uint; //(无符号16位整数)事件状态
		public var bySave:uint; //(无符号8位整数)是否存数据库
		public var dwParam1:uint; //(无符号32位整数)统计参数1
		public var dwParam2:int; //(有符号32位整数)统计参数2
		public var dwStartTime:uint; //(无符号32位整数)开始时间
		public var dwEndTime:uint; //(无符号32位整数)结束时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byActClassID:uint, dwEventInstID:uint, dwApplyID:uint, wEventStatus:uint, 
			bySave:uint, dwParam1:uint, dwParam2:int, dwStartTime:uint, dwEndTime:uint):SEventInfo
		{
			var s_:SEventInfo = new SEventInfo();
			s_.qwRoleID = qwRoleID;
			s_.byActClassID = byActClassID;
			s_.dwEventInstID = dwEventInstID;
			s_.dwApplyID = dwApplyID;
			s_.wEventStatus = wEventStatus;
			s_.bySave = bySave;
			s_.dwParam1 = dwParam1;
			s_.dwParam2 = dwParam2;
			s_.dwStartTime = dwStartTime;
			s_.dwEndTime = dwEndTime;
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
				topXml = <SEventInfo _name_={name_} qwRoleID={qwRoleID} byActClassID={byActClassID} dwEventInstID={dwEventInstID} dwApplyID={dwApplyID} wEventStatus={wEventStatus}
				 bySave={bySave} dwParam1={dwParam1} dwParam2={dwParam2} dwStartTime={dwStartTime} dwEndTime={dwEndTime}/>;
			else
				topXml = <SEventInfo qwRoleID={qwRoleID} byActClassID={byActClassID} dwEventInstID={dwEventInstID} dwApplyID={dwApplyID} wEventStatus={wEventStatus}
				 bySave={bySave} dwParam1={dwParam1} dwParam2={dwParam2} dwStartTime={dwStartTime} dwEndTime={dwEndTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byActClassID = byActClassID;
			obj_.dwEventInstID = dwEventInstID;
			obj_.dwApplyID = dwApplyID;
			obj_.wEventStatus = wEventStatus;
			obj_.bySave = bySave;
			obj_.dwParam1 = dwParam1;
			obj_.dwParam2 = dwParam2;
			obj_.dwStartTime = dwStartTime;
			obj_.dwEndTime = dwEndTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEventInfo
		{
			var s_:SEventInfo = new SEventInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byActClassID:uint = bytes.readUnsignedByte();
			s_.byActClassID = byActClassID;
			var dwEventInstID:uint = bytes.readUnsignedInt();
			s_.dwEventInstID = dwEventInstID;
			var dwApplyID:uint = bytes.readUnsignedInt();
			s_.dwApplyID = dwApplyID;
			var wEventStatus:uint = bytes.readUnsignedShort();
			s_.wEventStatus = wEventStatus;
			var bySave:uint = bytes.readUnsignedByte();
			s_.bySave = bySave;
			var dwParam1:uint = bytes.readUnsignedInt();
			s_.dwParam1 = dwParam1;
			var dwParam2:int = bytes.readInt();
			s_.dwParam2 = dwParam2;
			var dwStartTime:uint = bytes.readUnsignedInt();
			s_.dwStartTime = dwStartTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEventInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEventInfo> = new Vector.<SEventInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEventInfo = SEventInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byActClassID);
			bytes.writeUnsignedInt(dwEventInstID);
			bytes.writeUnsignedInt(dwApplyID);
			bytes.writeShort(wEventStatus);
			bytes.writeByte(bySave);
			bytes.writeUnsignedInt(dwParam1);
			bytes.writeInt(dwParam2);
			bytes.writeUnsignedInt(dwStartTime);
			bytes.writeUnsignedInt(dwEndTime);
		}

		public static function vectorToByteArray(vec:Vector.<SEventInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEventInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
