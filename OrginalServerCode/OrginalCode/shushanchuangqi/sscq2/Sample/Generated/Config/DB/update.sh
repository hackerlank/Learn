#!/bin/bash
#H,U,P,PT,DBD will be exported by server

function update_object()
{
    echo "update [BEGIN]:"
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_05_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_10_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_15_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_20_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_20_2.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/qf_2014_01_23_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_25_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_25_2.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_30_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_01_31_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_02_01_ModifyGVar.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/yhsupdate_2015_02_02_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/qf_2015_02_10_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/qf_2015_02_25_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_02_11_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_02_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_04_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_06_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_06_2.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_07_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_10_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_10_2.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_13_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_17_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_18_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_21_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/st_2015_03_05_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/st_2015_03_05_2.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/st_2015_03_11_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/st_2015_03_24_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/st_2015_03_31_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_10_AddDgnStarAward.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/ljrupdate_2015_03_18_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/ljrupdate_2015_03_18_2.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_03_09_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_3_11_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_3_20.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/ljrupdate_2015_03_25_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_03_26_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_03_26_AddStone.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_04_08_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/ljrupdate_2015_04_02_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/st2015_04_08_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_04_13_AddLadderRobot.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_04_16_UpArena.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/yhs_add_szIconDel.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/qf_2015_04_23_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/qf_2015_04_30_1.sql
    #    mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_05_12_1.sql
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_05_12_1.sql    # 创建散仙被动技能表
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_05_18_1.sql    # 创建装备法宝表
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_05_20_1.sql    # 装备法宝表增加qwRoleID字段
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_05_20_AddShipRate.sql    # 加入运船倍率
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/qf_2015_05_21_1.sql        # 法宝增加字段 
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_05_21_AddShipRateForReport.sql    # 加入运船倍率
    #     mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_06_01_deletedataforcehua.sql #重置英雄本，索妖塔，斗剑
         mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_06_06_1.sql    # tbldiscount表中增加qwMarkID字段
         mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_06_09_1.sql        # tblroleguilddata表增加字段byMemberLastRank 
         mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/cjhupdate_2015_06_11_1.sql     # create tblroleshenglingprize
         mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_06_10_1.sql        # 创建tbllingshanshopbuylog表 
         mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_06_16_1.sql        # 清除过期的帮派战数据
         mysql -h$1 -u$2 -p$3 -P$4 -D$5 < updates/update_2015_06_16_deletedataforcehua.sql 
    echo "update [DONE]"
}
update_object $1 $2 $3 $4 $5 $6
