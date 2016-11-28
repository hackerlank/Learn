/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSkillDBInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库同步到游戏服务器的技能信息
	 */
	public final class SSkillDBInfo
	{
		public var qwOwnerID:BigInteger; //(无符号64位整数)将唯一ID
		public var dwUpSkill1:uint; //(无符号32位整数)使用中的技能1
		public var dwUpSkill2:uint; //(无符号32位整数)使用中的技能2
		public var dwUpSkill3:uint; //(无符号32位整数)使用中的技能3
		public var dwUpSkill4:uint; //(无符号32位整数)使用中的技能4
		public var dwUpSkill5:uint; //(无符号32位整数)使用中的技能5
		public var dwUpSkill6:uint; //(无符号32位整数)使用中的技能6
		public var dwSkill1:uint; //(无符号32位整数)技能1
		public var dwSkill2:uint; //(无符号32位整数)技能2
		public var dwSkill3:uint; //(无符号32位整数)技能3
		public var dwSkill4:uint; //(无符号32位整数)技能4
		public var dwSkill5:uint; //(无符号32位整数)技能5
		public var dwSkill6:uint; //(无符号32位整数)技能6
		public var dwSkill7:uint; //(无符号32位整数)技能7
		public var dwSkill8:uint; //(无符号32位整数)技能8
		public var dwSkill9:uint; //(无符号32位整数)技能9
		public var dwRune1:uint; //(无符号32位整数)符文1
		public var dwRune2:uint; //(无符号32位整数)符文2
		public var dwRune3:uint; //(无符号32位整数)符文3
		public var dwRune4:uint; //(无符号32位整数)符文4
		public var dwRune5:uint; //(无符号32位整数)符文5
		public var dwRune6:uint; //(无符号32位整数)符文6
		public var dwRune7:uint; //(无符号32位整数)符文7
		public var dwRune8:uint; //(无符号32位整数)符文8
		public var dwRune9:uint; //(无符号32位整数)符文9
		public var dwSkillAdv1:uint; //(无符号32位整数)技能进阶1
		public var dwSkillAdv2:uint; //(无符号32位整数)技能进阶2
		public var dwSkillAdv3:uint; //(无符号32位整数)技能进阶3
		public var dwSkillAdv4:uint; //(无符号32位整数)技能进阶4
		public var dwSkillAdv5:uint; //(无符号32位整数)技能进阶5
		public var dwSkillAdv6:uint; //(无符号32位整数)技能进阶6
		public var dwSkillAdv7:uint; //(无符号32位整数)技能进阶7
		public var dwSkillAdv8:uint; //(无符号32位整数)技能进阶8
		public var dwSkillAdv9:uint; //(无符号32位整数)技能进阶9

		/**
		 * 辅助创建函数
		 */
		public static function create(qwOwnerID:BigInteger, dwUpSkill1:uint, dwUpSkill2:uint, dwUpSkill3:uint, dwUpSkill4:uint, 
			dwUpSkill5:uint, dwUpSkill6:uint, dwSkill1:uint, dwSkill2:uint, dwSkill3:uint, 
			dwSkill4:uint, dwSkill5:uint, dwSkill6:uint, dwSkill7:uint, dwSkill8:uint, 
			dwSkill9:uint, dwRune1:uint, dwRune2:uint, dwRune3:uint, dwRune4:uint, 
			dwRune5:uint, dwRune6:uint, dwRune7:uint, dwRune8:uint, dwRune9:uint, 
			dwSkillAdv1:uint, dwSkillAdv2:uint, dwSkillAdv3:uint, dwSkillAdv4:uint, dwSkillAdv5:uint, 
			dwSkillAdv6:uint, dwSkillAdv7:uint, dwSkillAdv8:uint, dwSkillAdv9:uint):SSkillDBInfo
		{
			var s_:SSkillDBInfo = new SSkillDBInfo();
			s_.qwOwnerID = qwOwnerID;
			s_.dwUpSkill1 = dwUpSkill1;
			s_.dwUpSkill2 = dwUpSkill2;
			s_.dwUpSkill3 = dwUpSkill3;
			s_.dwUpSkill4 = dwUpSkill4;
			s_.dwUpSkill5 = dwUpSkill5;
			s_.dwUpSkill6 = dwUpSkill6;
			s_.dwSkill1 = dwSkill1;
			s_.dwSkill2 = dwSkill2;
			s_.dwSkill3 = dwSkill3;
			s_.dwSkill4 = dwSkill4;
			s_.dwSkill5 = dwSkill5;
			s_.dwSkill6 = dwSkill6;
			s_.dwSkill7 = dwSkill7;
			s_.dwSkill8 = dwSkill8;
			s_.dwSkill9 = dwSkill9;
			s_.dwRune1 = dwRune1;
			s_.dwRune2 = dwRune2;
			s_.dwRune3 = dwRune3;
			s_.dwRune4 = dwRune4;
			s_.dwRune5 = dwRune5;
			s_.dwRune6 = dwRune6;
			s_.dwRune7 = dwRune7;
			s_.dwRune8 = dwRune8;
			s_.dwRune9 = dwRune9;
			s_.dwSkillAdv1 = dwSkillAdv1;
			s_.dwSkillAdv2 = dwSkillAdv2;
			s_.dwSkillAdv3 = dwSkillAdv3;
			s_.dwSkillAdv4 = dwSkillAdv4;
			s_.dwSkillAdv5 = dwSkillAdv5;
			s_.dwSkillAdv6 = dwSkillAdv6;
			s_.dwSkillAdv7 = dwSkillAdv7;
			s_.dwSkillAdv8 = dwSkillAdv8;
			s_.dwSkillAdv9 = dwSkillAdv9;
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
				topXml = <SSkillDBInfo _name_={name_} qwOwnerID={qwOwnerID} dwUpSkill1={dwUpSkill1} dwUpSkill2={dwUpSkill2} dwUpSkill3={dwUpSkill3} dwUpSkill4={dwUpSkill4}
				 dwUpSkill5={dwUpSkill5} dwUpSkill6={dwUpSkill6} dwSkill1={dwSkill1} dwSkill2={dwSkill2} dwSkill3={dwSkill3}
				 dwSkill4={dwSkill4} dwSkill5={dwSkill5} dwSkill6={dwSkill6} dwSkill7={dwSkill7} dwSkill8={dwSkill8}
				 dwSkill9={dwSkill9} dwRune1={dwRune1} dwRune2={dwRune2} dwRune3={dwRune3} dwRune4={dwRune4}
				 dwRune5={dwRune5} dwRune6={dwRune6} dwRune7={dwRune7} dwRune8={dwRune8} dwRune9={dwRune9}
				 dwSkillAdv1={dwSkillAdv1} dwSkillAdv2={dwSkillAdv2} dwSkillAdv3={dwSkillAdv3} dwSkillAdv4={dwSkillAdv4} dwSkillAdv5={dwSkillAdv5}
				 dwSkillAdv6={dwSkillAdv6} dwSkillAdv7={dwSkillAdv7} dwSkillAdv8={dwSkillAdv8} dwSkillAdv9={dwSkillAdv9}/>;
			else
				topXml = <SSkillDBInfo qwOwnerID={qwOwnerID} dwUpSkill1={dwUpSkill1} dwUpSkill2={dwUpSkill2} dwUpSkill3={dwUpSkill3} dwUpSkill4={dwUpSkill4}
				 dwUpSkill5={dwUpSkill5} dwUpSkill6={dwUpSkill6} dwSkill1={dwSkill1} dwSkill2={dwSkill2} dwSkill3={dwSkill3}
				 dwSkill4={dwSkill4} dwSkill5={dwSkill5} dwSkill6={dwSkill6} dwSkill7={dwSkill7} dwSkill8={dwSkill8}
				 dwSkill9={dwSkill9} dwRune1={dwRune1} dwRune2={dwRune2} dwRune3={dwRune3} dwRune4={dwRune4}
				 dwRune5={dwRune5} dwRune6={dwRune6} dwRune7={dwRune7} dwRune8={dwRune8} dwRune9={dwRune9}
				 dwSkillAdv1={dwSkillAdv1} dwSkillAdv2={dwSkillAdv2} dwSkillAdv3={dwSkillAdv3} dwSkillAdv4={dwSkillAdv4} dwSkillAdv5={dwSkillAdv5}
				 dwSkillAdv6={dwSkillAdv6} dwSkillAdv7={dwSkillAdv7} dwSkillAdv8={dwSkillAdv8} dwSkillAdv9={dwSkillAdv9}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwOwnerID = qwOwnerID;
			obj_.dwUpSkill1 = dwUpSkill1;
			obj_.dwUpSkill2 = dwUpSkill2;
			obj_.dwUpSkill3 = dwUpSkill3;
			obj_.dwUpSkill4 = dwUpSkill4;
			obj_.dwUpSkill5 = dwUpSkill5;
			obj_.dwUpSkill6 = dwUpSkill6;
			obj_.dwSkill1 = dwSkill1;
			obj_.dwSkill2 = dwSkill2;
			obj_.dwSkill3 = dwSkill3;
			obj_.dwSkill4 = dwSkill4;
			obj_.dwSkill5 = dwSkill5;
			obj_.dwSkill6 = dwSkill6;
			obj_.dwSkill7 = dwSkill7;
			obj_.dwSkill8 = dwSkill8;
			obj_.dwSkill9 = dwSkill9;
			obj_.dwRune1 = dwRune1;
			obj_.dwRune2 = dwRune2;
			obj_.dwRune3 = dwRune3;
			obj_.dwRune4 = dwRune4;
			obj_.dwRune5 = dwRune5;
			obj_.dwRune6 = dwRune6;
			obj_.dwRune7 = dwRune7;
			obj_.dwRune8 = dwRune8;
			obj_.dwRune9 = dwRune9;
			obj_.dwSkillAdv1 = dwSkillAdv1;
			obj_.dwSkillAdv2 = dwSkillAdv2;
			obj_.dwSkillAdv3 = dwSkillAdv3;
			obj_.dwSkillAdv4 = dwSkillAdv4;
			obj_.dwSkillAdv5 = dwSkillAdv5;
			obj_.dwSkillAdv6 = dwSkillAdv6;
			obj_.dwSkillAdv7 = dwSkillAdv7;
			obj_.dwSkillAdv8 = dwSkillAdv8;
			obj_.dwSkillAdv9 = dwSkillAdv9;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSkillDBInfo
		{
			var s_:SSkillDBInfo = new SSkillDBInfo();
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var dwUpSkill1:uint = bytes.readUnsignedInt();
			s_.dwUpSkill1 = dwUpSkill1;
			var dwUpSkill2:uint = bytes.readUnsignedInt();
			s_.dwUpSkill2 = dwUpSkill2;
			var dwUpSkill3:uint = bytes.readUnsignedInt();
			s_.dwUpSkill3 = dwUpSkill3;
			var dwUpSkill4:uint = bytes.readUnsignedInt();
			s_.dwUpSkill4 = dwUpSkill4;
			var dwUpSkill5:uint = bytes.readUnsignedInt();
			s_.dwUpSkill5 = dwUpSkill5;
			var dwUpSkill6:uint = bytes.readUnsignedInt();
			s_.dwUpSkill6 = dwUpSkill6;
			var dwSkill1:uint = bytes.readUnsignedInt();
			s_.dwSkill1 = dwSkill1;
			var dwSkill2:uint = bytes.readUnsignedInt();
			s_.dwSkill2 = dwSkill2;
			var dwSkill3:uint = bytes.readUnsignedInt();
			s_.dwSkill3 = dwSkill3;
			var dwSkill4:uint = bytes.readUnsignedInt();
			s_.dwSkill4 = dwSkill4;
			var dwSkill5:uint = bytes.readUnsignedInt();
			s_.dwSkill5 = dwSkill5;
			var dwSkill6:uint = bytes.readUnsignedInt();
			s_.dwSkill6 = dwSkill6;
			var dwSkill7:uint = bytes.readUnsignedInt();
			s_.dwSkill7 = dwSkill7;
			var dwSkill8:uint = bytes.readUnsignedInt();
			s_.dwSkill8 = dwSkill8;
			var dwSkill9:uint = bytes.readUnsignedInt();
			s_.dwSkill9 = dwSkill9;
			var dwRune1:uint = bytes.readUnsignedInt();
			s_.dwRune1 = dwRune1;
			var dwRune2:uint = bytes.readUnsignedInt();
			s_.dwRune2 = dwRune2;
			var dwRune3:uint = bytes.readUnsignedInt();
			s_.dwRune3 = dwRune3;
			var dwRune4:uint = bytes.readUnsignedInt();
			s_.dwRune4 = dwRune4;
			var dwRune5:uint = bytes.readUnsignedInt();
			s_.dwRune5 = dwRune5;
			var dwRune6:uint = bytes.readUnsignedInt();
			s_.dwRune6 = dwRune6;
			var dwRune7:uint = bytes.readUnsignedInt();
			s_.dwRune7 = dwRune7;
			var dwRune8:uint = bytes.readUnsignedInt();
			s_.dwRune8 = dwRune8;
			var dwRune9:uint = bytes.readUnsignedInt();
			s_.dwRune9 = dwRune9;
			var dwSkillAdv1:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv1 = dwSkillAdv1;
			var dwSkillAdv2:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv2 = dwSkillAdv2;
			var dwSkillAdv3:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv3 = dwSkillAdv3;
			var dwSkillAdv4:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv4 = dwSkillAdv4;
			var dwSkillAdv5:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv5 = dwSkillAdv5;
			var dwSkillAdv6:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv6 = dwSkillAdv6;
			var dwSkillAdv7:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv7 = dwSkillAdv7;
			var dwSkillAdv8:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv8 = dwSkillAdv8;
			var dwSkillAdv9:uint = bytes.readUnsignedInt();
			s_.dwSkillAdv9 = dwSkillAdv9;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSkillDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSkillDBInfo> = new Vector.<SSkillDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSkillDBInfo = SSkillDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeUnsignedInt(dwUpSkill1);
			bytes.writeUnsignedInt(dwUpSkill2);
			bytes.writeUnsignedInt(dwUpSkill3);
			bytes.writeUnsignedInt(dwUpSkill4);
			bytes.writeUnsignedInt(dwUpSkill5);
			bytes.writeUnsignedInt(dwUpSkill6);
			bytes.writeUnsignedInt(dwSkill1);
			bytes.writeUnsignedInt(dwSkill2);
			bytes.writeUnsignedInt(dwSkill3);
			bytes.writeUnsignedInt(dwSkill4);
			bytes.writeUnsignedInt(dwSkill5);
			bytes.writeUnsignedInt(dwSkill6);
			bytes.writeUnsignedInt(dwSkill7);
			bytes.writeUnsignedInt(dwSkill8);
			bytes.writeUnsignedInt(dwSkill9);
			bytes.writeUnsignedInt(dwRune1);
			bytes.writeUnsignedInt(dwRune2);
			bytes.writeUnsignedInt(dwRune3);
			bytes.writeUnsignedInt(dwRune4);
			bytes.writeUnsignedInt(dwRune5);
			bytes.writeUnsignedInt(dwRune6);
			bytes.writeUnsignedInt(dwRune7);
			bytes.writeUnsignedInt(dwRune8);
			bytes.writeUnsignedInt(dwRune9);
			bytes.writeUnsignedInt(dwSkillAdv1);
			bytes.writeUnsignedInt(dwSkillAdv2);
			bytes.writeUnsignedInt(dwSkillAdv3);
			bytes.writeUnsignedInt(dwSkillAdv4);
			bytes.writeUnsignedInt(dwSkillAdv5);
			bytes.writeUnsignedInt(dwSkillAdv6);
			bytes.writeUnsignedInt(dwSkillAdv7);
			bytes.writeUnsignedInt(dwSkillAdv8);
			bytes.writeUnsignedInt(dwSkillAdv9);
		}

		public static function vectorToByteArray(vec:Vector.<SSkillDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSkillDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
