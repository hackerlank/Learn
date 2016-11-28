/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPlayMovieInfo.as
//  Purpose:      获取动画播放信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	/**
	 * 获取动画播放信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPlayMovieInfo
	{
		public var eRet:uint; //(枚举类型：ELingShanOP)结果
		public var oPlayMovieInfo:SPlayMovieInfo; //动画播放信息
		public var vecTakePrizeLog:Vector.<STakePrizeLog>; //玩家奖励log列表
		public var wRoomID:uint; //(无符号16位整数)房间id
		public var dwTurn:uint; //(无符号32位整数)当前轮数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPlayMovieInfo _name_={name_} eRet={eRet} wRoomID={wRoomID} dwTurn={dwTurn}/>;
			else
				topXml = <SRetParam_GetPlayMovieInfo eRet={eRet} wRoomID={wRoomID} dwTurn={dwTurn}/>;
			if(oPlayMovieInfo != null)
				topXml.appendChild(oPlayMovieInfo.toXML("oPlayMovieInfo"));
			if(vecTakePrizeLog != null)
			{
				var vecTakePrizeLogXml:XML = <Vec_STakePrizeLog _name_="vecTakePrizeLog"/>;
				for each(var s2:STakePrizeLog in vecTakePrizeLog)
					vecTakePrizeLogXml.appendChild(s2.toXML());
				topXml.appendChild(vecTakePrizeLogXml);
			}
			return topXml;
		}
	}
}
