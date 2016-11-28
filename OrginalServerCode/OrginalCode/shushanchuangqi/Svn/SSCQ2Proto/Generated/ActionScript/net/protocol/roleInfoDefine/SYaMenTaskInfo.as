/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SYaMenTaskInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 衙门任务
	 */
	public final class SYaMenTaskInfo
	{
		public var dwHoly:uint; //(无符号32位整数)圣义值
		public var byHolyLevel:uint; //(无符号8位整数)圣义等级
		public var byBuyTimes:uint; //(无符号8位整数)购买的衙门任务数
		public var dwFlushTask1:uint; //(无符号32位整数)刷的任务
		public var eState1:uint; //(枚举类型：yaMenTaskProt.EYaMenTaskState)任务状态
		public var dwFlushTask2:uint; //(无符号32位整数)刷的任务
		public var eState2:uint; //(枚举类型：yaMenTaskProt.EYaMenTaskState)任务状态
		public var dwFlushTask3:uint; //(无符号32位整数)刷的任务
		public var eState3:uint; //(枚举类型：yaMenTaskProt.EYaMenTaskState)任务状态
		public var dwFlushTask4:uint; //(无符号32位整数)刷的任务
		public var eState4:uint; //(枚举类型：yaMenTaskProt.EYaMenTaskState)任务状态
		public var dwFlushTask5:uint; //(无符号32位整数)刷的任务
		public var eState5:uint; //(枚举类型：yaMenTaskProt.EYaMenTaskState)任务状态

		/**
		 * 辅助创建函数
		 */
		public static function create(dwHoly:uint, byHolyLevel:uint, byBuyTimes:uint, dwFlushTask1:uint, eState1:uint, 
			dwFlushTask2:uint, eState2:uint, dwFlushTask3:uint, eState3:uint, dwFlushTask4:uint, 
			eState4:uint, dwFlushTask5:uint, eState5:uint):SYaMenTaskInfo
		{
			var s_:SYaMenTaskInfo = new SYaMenTaskInfo();
			s_.dwHoly = dwHoly;
			s_.byHolyLevel = byHolyLevel;
			s_.byBuyTimes = byBuyTimes;
			s_.dwFlushTask1 = dwFlushTask1;
			s_.eState1 = eState1;
			s_.dwFlushTask2 = dwFlushTask2;
			s_.eState2 = eState2;
			s_.dwFlushTask3 = dwFlushTask3;
			s_.eState3 = eState3;
			s_.dwFlushTask4 = dwFlushTask4;
			s_.eState4 = eState4;
			s_.dwFlushTask5 = dwFlushTask5;
			s_.eState5 = eState5;
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
				topXml = <SYaMenTaskInfo _name_={name_} dwHoly={dwHoly} byHolyLevel={byHolyLevel} byBuyTimes={byBuyTimes} dwFlushTask1={dwFlushTask1} eState1={eState1}
				 dwFlushTask2={dwFlushTask2} eState2={eState2} dwFlushTask3={dwFlushTask3} eState3={eState3} dwFlushTask4={dwFlushTask4}
				 eState4={eState4} dwFlushTask5={dwFlushTask5} eState5={eState5}/>;
			else
				topXml = <SYaMenTaskInfo dwHoly={dwHoly} byHolyLevel={byHolyLevel} byBuyTimes={byBuyTimes} dwFlushTask1={dwFlushTask1} eState1={eState1}
				 dwFlushTask2={dwFlushTask2} eState2={eState2} dwFlushTask3={dwFlushTask3} eState3={eState3} dwFlushTask4={dwFlushTask4}
				 eState4={eState4} dwFlushTask5={dwFlushTask5} eState5={eState5}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwHoly = dwHoly;
			obj_.byHolyLevel = byHolyLevel;
			obj_.byBuyTimes = byBuyTimes;
			obj_.dwFlushTask1 = dwFlushTask1;
			obj_.eState1 = eState1;
			obj_.dwFlushTask2 = dwFlushTask2;
			obj_.eState2 = eState2;
			obj_.dwFlushTask3 = dwFlushTask3;
			obj_.eState3 = eState3;
			obj_.dwFlushTask4 = dwFlushTask4;
			obj_.eState4 = eState4;
			obj_.dwFlushTask5 = dwFlushTask5;
			obj_.eState5 = eState5;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SYaMenTaskInfo
		{
			var s_:SYaMenTaskInfo = new SYaMenTaskInfo();
			var dwHoly:uint = bytes.readUnsignedInt();
			s_.dwHoly = dwHoly;
			var byHolyLevel:uint = bytes.readUnsignedByte();
			s_.byHolyLevel = byHolyLevel;
			var byBuyTimes:uint = bytes.readUnsignedByte();
			s_.byBuyTimes = byBuyTimes;
			var dwFlushTask1:uint = bytes.readUnsignedInt();
			s_.dwFlushTask1 = dwFlushTask1;
			var eState1:uint = bytes.readUnsignedByte();
			s_.eState1 = eState1;
			var dwFlushTask2:uint = bytes.readUnsignedInt();
			s_.dwFlushTask2 = dwFlushTask2;
			var eState2:uint = bytes.readUnsignedByte();
			s_.eState2 = eState2;
			var dwFlushTask3:uint = bytes.readUnsignedInt();
			s_.dwFlushTask3 = dwFlushTask3;
			var eState3:uint = bytes.readUnsignedByte();
			s_.eState3 = eState3;
			var dwFlushTask4:uint = bytes.readUnsignedInt();
			s_.dwFlushTask4 = dwFlushTask4;
			var eState4:uint = bytes.readUnsignedByte();
			s_.eState4 = eState4;
			var dwFlushTask5:uint = bytes.readUnsignedInt();
			s_.dwFlushTask5 = dwFlushTask5;
			var eState5:uint = bytes.readUnsignedByte();
			s_.eState5 = eState5;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SYaMenTaskInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SYaMenTaskInfo> = new Vector.<SYaMenTaskInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SYaMenTaskInfo = SYaMenTaskInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwHoly);
			bytes.writeByte(byHolyLevel);
			bytes.writeByte(byBuyTimes);
			bytes.writeUnsignedInt(dwFlushTask1);
			bytes.writeByte(eState1);
			bytes.writeUnsignedInt(dwFlushTask2);
			bytes.writeByte(eState2);
			bytes.writeUnsignedInt(dwFlushTask3);
			bytes.writeByte(eState3);
			bytes.writeUnsignedInt(dwFlushTask4);
			bytes.writeByte(eState4);
			bytes.writeUnsignedInt(dwFlushTask5);
			bytes.writeByte(eState5);
		}

		public static function vectorToByteArray(vec:Vector.<SYaMenTaskInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SYaMenTaskInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
