/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskCollectInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 收集道具的信息
	 */
	public final class STaskCollectInfo extends STaskInfo
	{
		public var wItemID:uint; //(无符号16位整数)道具的ID
		public var wItemCount:uint; //(无符号16位整数)已搜集道具的数量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskCollectInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskCollectInfo _name_={name_} wItemID={wItemID} wItemCount={wItemCount}/>;
			else
				topXml = <STaskCollectInfo wItemID={wItemID} wItemCount={wItemCount}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.wItemCount = wItemCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskCollectInfo
		{
			var s_:STaskCollectInfo = new STaskCollectInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var wItemCount:uint = bytes.readUnsignedShort();
			s_.wItemCount = wItemCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskCollectInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskCollectInfo> = new Vector.<STaskCollectInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskCollectInfo = STaskCollectInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wItemID);
			bytes.writeShort(wItemCount);
		}

		public static function vectorToByteArray(vec:Vector.<STaskCollectInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskCollectInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
