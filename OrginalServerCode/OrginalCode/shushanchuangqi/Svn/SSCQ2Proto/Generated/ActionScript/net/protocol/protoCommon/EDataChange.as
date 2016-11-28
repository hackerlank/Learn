/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDataChange.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 数据变化类型
	 */
	public final class EDataChange
	{
		public static const eOpNone:uint = 0; //无变化
		public static const eOpAdd:uint = 1; //数据增加
		public static const eOpDel:uint = 2; //数据删除
		public static const eOpUpdate:uint = 3; //数据更新
		public static const eOpReplace:uint = 4; //数据替换
		public static const eOpAddIgnore:uint = 5; //数据仅新增
		public static const eOpMax:uint = 6; //最大值
		public static const end:uint = eOpMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eOpNone:
					return ProtocolMessageProt258.eOpNone;
				case eOpAdd:
					return ProtocolMessageProt258.eOpAdd;
				case eOpDel:
					return ProtocolMessageProt258.eOpDel;
				case eOpUpdate:
					return ProtocolMessageProt258.eOpUpdate;
				case eOpReplace:
					return ProtocolMessageProt258.eOpReplace;
				case eOpAddIgnore:
					return ProtocolMessageProt258.eOpAddIgnore;
				case eOpMax:
					return ProtocolMessageProt258.eOpMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
