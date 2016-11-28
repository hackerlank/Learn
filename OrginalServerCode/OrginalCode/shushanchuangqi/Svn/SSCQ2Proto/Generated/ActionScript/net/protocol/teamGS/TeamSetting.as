/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamSetting.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 队伍设定
	 */
	public final class TeamSetting
	{
		public var dwPassWord:uint; //(无符号32位整数)队伍密码

		/**
		 * 辅助创建函数
		 */
		public static function create(dwPassWord:uint):TeamSetting
		{
			var s_:TeamSetting = new TeamSetting();
			s_.dwPassWord = dwPassWord;
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
				topXml = <TeamSetting _name_={name_} dwPassWord={dwPassWord}/>;
			else
				topXml = <TeamSetting dwPassWord={dwPassWord}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwPassWord = dwPassWord;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamSetting
		{
			var s_:TeamSetting = new TeamSetting();
			var dwPassWord:uint = bytes.readUnsignedInt();
			s_.dwPassWord = dwPassWord;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamSetting>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamSetting> = new Vector.<TeamSetting>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamSetting = TeamSetting.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwPassWord);
		}

		public static function vectorToByteArray(vec:Vector.<TeamSetting>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamSetting in vec)
				s.toByteArray(bytes);
		}
	}
}
