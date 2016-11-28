/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetMathSelInfo.as
//  Purpose:      获取自己的比赛信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	/**
	 * 获取自己的比赛信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetMathSelInfo
	{
		public var eRet:uint; //(枚举类型：ELingShanOP)结果
		public var eStatus:uint; //(枚举类型：ELingShanStatus)当前状态
		public var oRoomPlayInfo:SRoomPlayInfo; //玩家地图信息
		public var fHPRate:Number; //(Float)血量百分比
		public var dwBoxCnt:uint; //(无符号16位整数)宝箱数量
		public var dwSuiYuan:uint; //(无符号32位整数)随缘值
		public var dwRoomID:uint; //(无符号32位整数)房间号
		public var dwFreshTurn:uint; //(无符号32位整数)至宝刷新剩余轮数
		public var dwModelID:uint; //(无符号32位整数)模型id

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetMathSelInfo _name_={name_} eRet={eRet} eStatus={eStatus} fHPRate={fHPRate} dwBoxCnt={dwBoxCnt}
				 dwSuiYuan={dwSuiYuan} dwRoomID={dwRoomID} dwFreshTurn={dwFreshTurn} dwModelID={dwModelID}/>;
			else
				topXml = <SRetParam_GetMathSelInfo eRet={eRet} eStatus={eStatus} fHPRate={fHPRate} dwBoxCnt={dwBoxCnt}
				 dwSuiYuan={dwSuiYuan} dwRoomID={dwRoomID} dwFreshTurn={dwFreshTurn} dwModelID={dwModelID}/>;
			if(oRoomPlayInfo != null)
				topXml.appendChild(oRoomPlayInfo.toXML("oRoomPlayInfo"));
			return topXml;
		}
	}
}
