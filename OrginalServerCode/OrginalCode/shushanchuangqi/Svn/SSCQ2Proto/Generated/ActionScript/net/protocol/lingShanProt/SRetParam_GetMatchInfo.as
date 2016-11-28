/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetMatchInfo.as
//  Purpose:      当前棋盘状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	/**
	 * 当前棋盘状态的返回的参数组成的结构体
	 */
	public final class SRetParam_GetMatchInfo
	{
		public var eRet:uint; //(枚举类型：ELingShanOP)结果
		public var vecBoxInfo:Vector.<SBoxInfo>; //地图箱子信息
		public var vecRoomPlayInfo:Vector.<SRoomPlayInfo>; //地图玩家信息
		public var vecRoomMonsterInfo:Vector.<SRoomMonsterInfo>; //地图怪物信息
		public var wRoomID:uint; //(无符号16位整数)房间id
		public var dwFreshTurn:uint; //(无符号32位整数)至宝刷新剩余轮数
		public var eStatus:uint; //(枚举类型：ELingShanStatus)当前状态
		public var dwParam:uint; //(无符号32位整数)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		public var dwTime:uint; //(无符号32位整数)服务器时间戳
		public var oPlayMovieInfo:SPlayMovieInfo; //动画播放信息
		public var vecTakePrizeLog:Vector.<STakePrizeLog>; //玩家奖励log列表
		public var dwTurn:uint; //(无符号32位整数)当前轮数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetMatchInfo _name_={name_} eRet={eRet} wRoomID={wRoomID}
				 dwFreshTurn={dwFreshTurn} eStatus={eStatus} dwParam={dwParam} dwTime={dwTime} dwTurn={dwTurn}/>;
			else
				topXml = <SRetParam_GetMatchInfo eRet={eRet} wRoomID={wRoomID}
				 dwFreshTurn={dwFreshTurn} eStatus={eStatus} dwParam={dwParam} dwTime={dwTime} dwTurn={dwTurn}/>;
			if(vecBoxInfo != null)
			{
				var vecBoxInfoXml:XML = <Vec_SBoxInfo _name_="vecBoxInfo"/>;
				for each(var s1:SBoxInfo in vecBoxInfo)
					vecBoxInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBoxInfoXml);
			}
			if(vecRoomPlayInfo != null)
			{
				var vecRoomPlayInfoXml:XML = <Vec_SRoomPlayInfo _name_="vecRoomPlayInfo"/>;
				for each(var s2:SRoomPlayInfo in vecRoomPlayInfo)
					vecRoomPlayInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecRoomPlayInfoXml);
			}
			if(vecRoomMonsterInfo != null)
			{
				var vecRoomMonsterInfoXml:XML = <Vec_SRoomMonsterInfo _name_="vecRoomMonsterInfo"/>;
				for each(var s3:SRoomMonsterInfo in vecRoomMonsterInfo)
					vecRoomMonsterInfoXml.appendChild(s3.toXML());
				topXml.appendChild(vecRoomMonsterInfoXml);
			}
			if(oPlayMovieInfo != null)
				topXml.appendChild(oPlayMovieInfo.toXML("oPlayMovieInfo"));
			if(vecTakePrizeLog != null)
			{
				var vecTakePrizeLogXml:XML = <Vec_STakePrizeLog _name_="vecTakePrizeLog"/>;
				for each(var s5:STakePrizeLog in vecTakePrizeLog)
					vecTakePrizeLogXml.appendChild(s5.toXML());
				topXml.appendChild(vecTakePrizeLogXml);
			}
			return topXml;
		}
	}
}
