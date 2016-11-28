/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskMonsterInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 杀死怪物的信息
	 */
	public final class STaskMonsterInfo extends STaskInfo
	{
		public var wMonsterID:uint; //(无符号16位整数)怪物的ID
		public var wMonsterCount:uint; //(无符号16位整数)已杀怪物的数量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskMonsterInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskMonsterInfo _name_={name_} wMonsterID={wMonsterID} wMonsterCount={wMonsterCount}/>;
			else
				topXml = <STaskMonsterInfo wMonsterID={wMonsterID} wMonsterCount={wMonsterCount}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wMonsterID = wMonsterID;
			obj_.wMonsterCount = wMonsterCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskMonsterInfo
		{
			var s_:STaskMonsterInfo = new STaskMonsterInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wMonsterID:uint = bytes.readUnsignedShort();
			s_.wMonsterID = wMonsterID;
			var wMonsterCount:uint = bytes.readUnsignedShort();
			s_.wMonsterCount = wMonsterCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskMonsterInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskMonsterInfo> = new Vector.<STaskMonsterInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskMonsterInfo = STaskMonsterInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wMonsterID);
			bytes.writeShort(wMonsterCount);
		}

		public static function vectorToByteArray(vec:Vector.<STaskMonsterInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskMonsterInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
