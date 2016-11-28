/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGMMailTarget.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 收件人信息
	 */
	public final class SGMMailTarget
	{
		public var qwTargetID:BigInteger; //(无符号64位整数)收件人ID
		public var strTarget:String; //收件人名

		/**
		 * 辅助创建函数
		 */
		public static function create(qwTargetID:BigInteger, strTarget:String):SGMMailTarget
		{
			var s_:SGMMailTarget = new SGMMailTarget();
			s_.qwTargetID = qwTargetID;
			s_.strTarget = strTarget;
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
				topXml = <SGMMailTarget _name_={name_} qwTargetID={qwTargetID} strTarget={strTarget}/>;
			else
				topXml = <SGMMailTarget qwTargetID={qwTargetID} strTarget={strTarget}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwTargetID = qwTargetID;
			obj_.strTarget = strTarget;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGMMailTarget
		{
			var s_:SGMMailTarget = new SGMMailTarget();
			var qwTargetID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwTargetID = qwTargetID;
			var strTarget:String = BytesUtil.readString(bytes);
			s_.strTarget = strTarget;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGMMailTarget>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGMMailTarget> = new Vector.<SGMMailTarget>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGMMailTarget = SGMMailTarget.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwTargetID);
			BytesUtil.writeString(bytes, strTarget);
		}

		public static function vectorToByteArray(vec:Vector.<SGMMailTarget>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGMMailTarget in vec)
				s.toByteArray(bytes);
		}
	}
}
