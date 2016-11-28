/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildUserDevote.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派成员贡献
	 */
	public final class SGuildUserDevote
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)ID
		public var strName:String; //名字
		public var strLevel:String; //职务
		public var dwScore:uint; //(无符号32位整数)积分

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, strName:String, strLevel:String, dwScore:uint):SGuildUserDevote
		{
			var s_:SGuildUserDevote = new SGuildUserDevote();
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.strLevel = strLevel;
			s_.dwScore = dwScore;
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
				topXml = <SGuildUserDevote _name_={name_} qwRoleID={qwRoleID} strName={strName} strLevel={strLevel} dwScore={dwScore}/>;
			else
				topXml = <SGuildUserDevote qwRoleID={qwRoleID} strName={strName} strLevel={strLevel} dwScore={dwScore}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.strLevel = strLevel;
			obj_.dwScore = dwScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildUserDevote
		{
			var s_:SGuildUserDevote = new SGuildUserDevote();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var strLevel:String = BytesUtil.readString(bytes);
			s_.strLevel = strLevel;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildUserDevote>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildUserDevote> = new Vector.<SGuildUserDevote>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildUserDevote = SGuildUserDevote.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			BytesUtil.writeString(bytes, strLevel);
			bytes.writeUnsignedInt(dwScore);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildUserDevote>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildUserDevote in vec)
				s.toByteArray(bytes);
		}
	}
}
