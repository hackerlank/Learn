/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SNpcTaskState.as
//  Purpose:      NPC相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * NPC的任务状态
	 */
	public final class SNpcTaskState
	{
		public var wNpcID:uint; //(无符号16位整数)NPC的ID
		public var eNpcTaskState:uint; //(枚举类型：taskProt.ENpcTaskState)任务状态

		/**
		 * 辅助创建函数
		 */
		public static function create(wNpcID:uint, eNpcTaskState:uint):SNpcTaskState
		{
			var s_:SNpcTaskState = new SNpcTaskState();
			s_.wNpcID = wNpcID;
			s_.eNpcTaskState = eNpcTaskState;
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
				topXml = <SNpcTaskState _name_={name_} wNpcID={wNpcID} eNpcTaskState={eNpcTaskState}/>;
			else
				topXml = <SNpcTaskState wNpcID={wNpcID} eNpcTaskState={eNpcTaskState}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wNpcID = wNpcID;
			obj_.eNpcTaskState = eNpcTaskState;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SNpcTaskState
		{
			var s_:SNpcTaskState = new SNpcTaskState();
			var wNpcID:uint = bytes.readUnsignedShort();
			s_.wNpcID = wNpcID;
			var eNpcTaskState:uint = bytes.readUnsignedByte();
			s_.eNpcTaskState = eNpcTaskState;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SNpcTaskState>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SNpcTaskState> = new Vector.<SNpcTaskState>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SNpcTaskState = SNpcTaskState.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wNpcID);
			bytes.writeByte(eNpcTaskState);
		}

		public static function vectorToByteArray(vec:Vector.<SNpcTaskState>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SNpcTaskState in vec)
				s.toByteArray(bytes);
		}
	}
}
