/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECittaResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 心法操作结果
	 */
	public final class ECittaResult
	{
		public static const eCittaSuccess:uint = 0; //心法操作成功
		public static const eCittaFailed:uint = 1; //心法操作失败
		public static const eCittaPackFull:uint = 2; //心法操作时背包已满
		public static const eCittaMaterialLack:uint = 3; //材料不足
		public static const eCittaSlotNotEmpty:uint = 4; //心法槽已满
		public static const eCittaSlotEmpty:uint = 5; //心法槽为空
		public static const eCittaSilverLack:uint = 6; //银币不足
		public static const end:uint = eCittaSilverLack;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCittaSuccess:
					return ProtocolMessageProt18.eCittaSuccess;
				case eCittaFailed:
					return ProtocolMessageProt18.eCittaFailed;
				case eCittaPackFull:
					return ProtocolMessageProt18.eCittaPackFull;
				case eCittaMaterialLack:
					return ProtocolMessageProt18.eCittaMaterialLack;
				case eCittaSlotNotEmpty:
					return ProtocolMessageProt18.eCittaSlotNotEmpty;
				case eCittaSlotEmpty:
					return ProtocolMessageProt18.eCittaSlotEmpty;
				case eCittaSilverLack:
					return ProtocolMessageProt18.eCittaSilverLack;
				default:
					return "Unknown Error";
			}
		}
	}
}
