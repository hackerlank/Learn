// =====================================================================================
//
//       Filename:  EquipTrumpProtS.h
//
//    Description:  装备法宝相关协议
//
//        Version:  1.0
//        Created:  05/18/2015 03:52:14 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================


#ifndef EQUIP_TRUMP_PROT_S_H
#define EQUIP_TRUMP_PROT_S_H

#include "EquipTrumpProtSvr.h"

using namespace NEquipTrumpProt;

class CEquipTrumpProtS : public CEquipTrumpProtSvr
{
    public:
        //接收：获得所有装备法宝
        virtual bool OnRecv_GetAllEquipTrump(
                UINT64 qwOwnerID, //散仙唯一ID（0表示获取所有散仙法宝）
                shared_func<SGetAllEquipTrumpAck>& fnAck //返回回调函数
                );
        //接收：请求穿上装备法宝
        virtual bool OnRecv_Wear(
                UINT64 qwOwnerID, //散仙唯一ID
                UINT64 qwInstID, //装备法宝唯一ID
                shared_func<SWearAck>& fnAck //返回回调函数
                );
        //接收：请求一键穿上装备法宝
        virtual bool OnRecv_WearOneKey(
                UINT64 qwOwnerID, //散仙唯一ID
                shared_func<SWearOneKeyAck>& fnAck //返回回调函数
                );
        //接收：请求脱下装备法宝
        virtual bool OnRecv_TakeOff(
                UINT64 qwInstID, //装备法宝唯一ID
                INT16 wIndex, //-1：右击脱下；其他：包裹的位置
                shared_func<STakeOffAck>& fnAck //返回回调函数
                );
        //接收：交换法宝
        virtual bool OnRecv_Swap(
                UINT64 qwOwnerID, //散仙唯一ID
                UINT64 qwInstID, //装备法宝唯一ID
                INT16 wIndex, //-1：右击脱下；其他：包裹的位置
                shared_func<SSwapAck>& fnAck //返回回调函数
                );
        //接收：请求合成装备法宝
        virtual bool OnRecv_MergeEquipTrump(
                UINT16 wItemID, //制作装备法宝模版ID
                UINT16 wCount, //数量
                shared_func<SMergeEquipTrumpAck>& fnAck //返回回调函数
                );
        //接收：请求分解装备法宝
        virtual bool OnRecv_BreakEquipTrump(
                const TVecUINT64& vecInstID, //物品唯一ID
                shared_func<SBreakEquipTrumpAck>& fnAck //返回回调函数
                );
        //接收：装备法宝强化
        virtual bool OnRecv_Intensify(
                UINT64 qwInstID, //装备法宝唯一ID
                ETIntensifyType eType, //强化类型
                shared_func<SIntensifyAck>& fnAck //返回回调函数
                );
        //接收：装备法宝一键强化
        virtual bool OnRecv_IntensifyOneKey(
                UINT64 qwInstID, //装备法宝唯一ID
                ETIntensifyType eType, //强化类型
                shared_func<SIntensifyOneKeyAck>& fnAck //返回回调函数
                );
        //接收：装备法宝洗炼
        virtual bool OnRecv_ShuffleResult(
                UINT64 qwInstID, //装备法宝唯一ID
                UINT32 dwLock, //锁定属性（按位锁定 0x110 锁定2，3位）
                shared_func<SShuffleResultAck>& fnAck //返回回调函数
                );
};

extern CEquipTrumpProtS g_EquipTrumpProtS;
#endif // #ifndef EQUIP_TRUMP_PROT_S_H
