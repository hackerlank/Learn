/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    MulCond.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 多重条件信息
	 */
	public final class MulCond
	{
		public var vecCond:Vector.<DgnSucCond>; //多重条件

		/**
		 * 辅助创建函数
		 */
		public static function create(vecCond:Vector.<DgnSucCond>):MulCond
		{
			var s_:MulCond = new MulCond();
			s_.vecCond = vecCond;
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
				topXml = <MulCond _name_={name_}/>;
			else
				topXml = <MulCond/>;
			if(vecCond != null)
			{
				var vecCondXml:XML = <Vec_DgnSucCond _name_="vecCond"/>;
				for each(var s1:DgnSucCond in vecCond)
					vecCondXml.appendChild(s1.toXML());
				topXml.appendChild(vecCondXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.vecCond = vecCond;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):MulCond
		{
			var s_:MulCond = new MulCond();
			var vecCond:Vector.<DgnSucCond> = DgnSucCond.superVectorFromByteArray(bytes);
			s_.vecCond = vecCond;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<MulCond>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<MulCond> = new Vector.<MulCond>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:MulCond = MulCond.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			DgnSucCond.superVectorToByteArray(vecCond, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<MulCond>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:MulCond in vec)
				s.toByteArray(bytes);
		}
	}
}
