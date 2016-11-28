/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDemonTowerDB.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
 {
	import net.protocol.Message.ProtocolMessageProt71;
	/**
	 * 数据更新类型
	 */
	public final class EDemonTowerDB
	{
		public static const eDemonTowerDB_Add:uint = 1; //添加
		public static const eDemonTowerDB_Update:uint = 2; //更新
		public static const eDemonTowerDB_Delete:uint = 3; //删除
		public static const end:uint = eDemonTowerDB_Delete;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDemonTowerDB_Add:
					return ProtocolMessageProt71.eDemonTowerDB_Add;
				case eDemonTowerDB_Update:
					return ProtocolMessageProt71.eDemonTowerDB_Update;
				case eDemonTowerDB_Delete:
					return ProtocolMessageProt71.eDemonTowerDB_Delete;
				default:
					return "Unknown Error";
			}
		}
	}
}
