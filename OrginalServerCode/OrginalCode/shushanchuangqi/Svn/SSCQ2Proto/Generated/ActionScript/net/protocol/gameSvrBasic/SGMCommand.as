/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGMCommand.as
//  Purpose:      GameServer的基本协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * GM命令
	 */
	public final class SGMCommand
	{
		public var strCmd:String; //命令
		public var strName:String; //名称
		public var strDesc:String; //描述

		/**
		 * 辅助创建函数
		 */
		public static function create(strCmd:String, strName:String, strDesc:String):SGMCommand
		{
			var s_:SGMCommand = new SGMCommand();
			s_.strCmd = strCmd;
			s_.strName = strName;
			s_.strDesc = strDesc;
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
				topXml = <SGMCommand _name_={name_} strCmd={strCmd} strName={strName} strDesc={strDesc}/>;
			else
				topXml = <SGMCommand strCmd={strCmd} strName={strName} strDesc={strDesc}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strCmd = strCmd;
			obj_.strName = strName;
			obj_.strDesc = strDesc;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGMCommand
		{
			var s_:SGMCommand = new SGMCommand();
			var strCmd:String = BytesUtil.readString(bytes);
			s_.strCmd = strCmd;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var strDesc:String = BytesUtil.readString(bytes);
			s_.strDesc = strDesc;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGMCommand>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGMCommand> = new Vector.<SGMCommand>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGMCommand = SGMCommand.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strCmd);
			BytesUtil.writeString(bytes, strName);
			BytesUtil.writeString(bytes, strDesc);
		}

		public static function vectorToByteArray(vec:Vector.<SGMCommand>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGMCommand in vec)
				s.toByteArray(bytes);
		}
	}
}
