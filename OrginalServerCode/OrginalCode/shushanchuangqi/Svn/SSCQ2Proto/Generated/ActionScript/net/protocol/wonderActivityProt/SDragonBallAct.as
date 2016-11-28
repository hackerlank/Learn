/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDragonBallAct.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 七星龙珠活动信息
	 */
	public final class SDragonBallAct
	{
		public var dwBeginTime:uint; //(无符号32位整数)活动开始时间
		public var dwEndTime:uint; //(无符号32位整数)活动结束时间
		public var dwRecharge:uint; //(无符号32位整数)今日充值仙石数
		public var byIdx:uint; //(无符号8位整数)第几期活动
		public var byDay:uint; //(无符号8位整数)今日完成的龙珠数
		public var byAll:uint; //(无符号8位整数)完成的龙珠总数
		public var byRemain:uint; //(无符号8位整数)今日之前剩余可点亮的龙珠数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwBeginTime:uint, dwEndTime:uint, dwRecharge:uint, byIdx:uint, byDay:uint, 
			byAll:uint, byRemain:uint):SDragonBallAct
		{
			var s_:SDragonBallAct = new SDragonBallAct();
			s_.dwBeginTime = dwBeginTime;
			s_.dwEndTime = dwEndTime;
			s_.dwRecharge = dwRecharge;
			s_.byIdx = byIdx;
			s_.byDay = byDay;
			s_.byAll = byAll;
			s_.byRemain = byRemain;
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
				topXml = <SDragonBallAct _name_={name_} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwRecharge={dwRecharge} byIdx={byIdx} byDay={byDay}
				 byAll={byAll} byRemain={byRemain}/>;
			else
				topXml = <SDragonBallAct dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwRecharge={dwRecharge} byIdx={byIdx} byDay={byDay}
				 byAll={byAll} byRemain={byRemain}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwBeginTime = dwBeginTime;
			obj_.dwEndTime = dwEndTime;
			obj_.dwRecharge = dwRecharge;
			obj_.byIdx = byIdx;
			obj_.byDay = byDay;
			obj_.byAll = byAll;
			obj_.byRemain = byRemain;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDragonBallAct
		{
			var s_:SDragonBallAct = new SDragonBallAct();
			var dwBeginTime:uint = bytes.readUnsignedInt();
			s_.dwBeginTime = dwBeginTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			var dwRecharge:uint = bytes.readUnsignedInt();
			s_.dwRecharge = dwRecharge;
			var byIdx:uint = bytes.readUnsignedByte();
			s_.byIdx = byIdx;
			var byDay:uint = bytes.readUnsignedByte();
			s_.byDay = byDay;
			var byAll:uint = bytes.readUnsignedByte();
			s_.byAll = byAll;
			var byRemain:uint = bytes.readUnsignedByte();
			s_.byRemain = byRemain;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDragonBallAct>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDragonBallAct> = new Vector.<SDragonBallAct>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDragonBallAct = SDragonBallAct.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwBeginTime);
			bytes.writeUnsignedInt(dwEndTime);
			bytes.writeUnsignedInt(dwRecharge);
			bytes.writeByte(byIdx);
			bytes.writeByte(byDay);
			bytes.writeByte(byAll);
			bytes.writeByte(byRemain);
		}

		public static function vectorToByteArray(vec:Vector.<SDragonBallAct>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDragonBallAct in vec)
				s.toByteArray(bytes);
		}
	}
}
