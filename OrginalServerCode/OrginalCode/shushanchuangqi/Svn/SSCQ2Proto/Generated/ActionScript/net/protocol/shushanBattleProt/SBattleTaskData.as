/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleTaskData.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 任务数据结构
	 */
	public final class SBattleTaskData
	{
		public var byTaskID:uint; //(无符号8位整数)任务ID
		public var byAward:uint; //(无符号8位整数)荣誉奖励值
		public var byComplete:uint; //(无符号8位整数)是否完成(0否,1是)

		/**
		 * 辅助创建函数
		 */
		public static function create(byTaskID:uint, byAward:uint, byComplete:uint):SBattleTaskData
		{
			var s_:SBattleTaskData = new SBattleTaskData();
			s_.byTaskID = byTaskID;
			s_.byAward = byAward;
			s_.byComplete = byComplete;
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
				topXml = <SBattleTaskData _name_={name_} byTaskID={byTaskID} byAward={byAward} byComplete={byComplete}/>;
			else
				topXml = <SBattleTaskData byTaskID={byTaskID} byAward={byAward} byComplete={byComplete}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byTaskID = byTaskID;
			obj_.byAward = byAward;
			obj_.byComplete = byComplete;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleTaskData
		{
			var s_:SBattleTaskData = new SBattleTaskData();
			var byTaskID:uint = bytes.readUnsignedByte();
			s_.byTaskID = byTaskID;
			var byAward:uint = bytes.readUnsignedByte();
			s_.byAward = byAward;
			var byComplete:uint = bytes.readUnsignedByte();
			s_.byComplete = byComplete;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleTaskData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleTaskData> = new Vector.<SBattleTaskData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleTaskData = SBattleTaskData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byTaskID);
			bytes.writeByte(byAward);
			bytes.writeByte(byComplete);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleTaskData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleTaskData in vec)
				s.toByteArray(bytes);
		}
	}
}
