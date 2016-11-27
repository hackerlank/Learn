#ifndef _RecordCommand_h_
#define _RecordCommand_h_

#include "zNullCmd.h"
#include "Command.h"
#include "CharBase.h"
#include "common.h"
#include "messageType.h"
#include "CharBase.h"

#pragma pack(1)

namespace CMD
{

    namespace RECORD
    {

        struct FamilyBase
        {
            QWORD m_familyID;
            QWORD m_charid;
            char m_strName[50];
            DWORD m_icon;
            DWORD  m_limmitType;
            DWORD m_lowLevel;
            DWORD m_highLevel;
            DWORD m_level;
            DWORD m_ranking;
            DWORD m_lastranking;
            char m_notice[500];
            DWORD m_createtime;
            DWORD m_score;
            DWORD m_contributionlast;
            char m_orderlist[50];

            FamilyBase()
            {
                m_familyID = 0;
                m_charid = 0;
                m_icon = 0;
                m_limmitType = 0;
                m_lowLevel = 0;
                m_highLevel = 0;
                m_level = 1;
                m_ranking =0;
                m_lastranking = 0;
                m_createtime = 0;
                m_score = 0;
                m_contributionlast = 0;
                memset(m_strName,0,sizeof(m_strName));
                memset(m_notice,0,sizeof(m_notice));
                memset(m_orderlist,0,sizeof(m_orderlist));
            }

        }__attribute__ ((packed));
        struct FamilyApplyData
        {

            QWORD m_ID;
            DWORD m_timer;
            FamilyApplyData()
            {
                m_ID = 0;
                m_timer =0;
            }

        }__attribute__ ((packed));
        struct FamilyMemberData
        {
            DWORD m_contributionlast; 
            DWORD m_contributionranklast;
            DWORD m_isgetaward;
            DWORD m_contribution; 
            FamilyMemberData()
            {
                m_contributionlast = 0;
                m_contributionranklast = 0;
                m_isgetaward = 0;
                m_contribution = 0;
            }

        }__attribute__ ((packed));

        struct ServerNoticeData
        {
            QWORD m_ID;
            DWORD m_time;
            DWORD m_lang;
            char m_notice[500];
            ServerNoticeData()
            {
                m_ID = 0;
                m_time = 0;
                m_lang = 0;
                memset(m_notice,0,sizeof(m_notice));
            }

        }__attribute__ ((packed));

        struct RecordNull : t_NullCmd
        {
            RecordNull()
            {
                cmd = RECORDCMD;
            }
        };

        //////////////////////////////////////////////////////////////
        /// 登陆档案服务器指令
        //////////////////////////////////////////////////////////////
        const BYTE PARA_LOGIN = 1;
        struct t_LoginRecord : RecordNull 
        {
            WORD wdServerID;
            WORD wdServerType;
            t_LoginRecord()	
            {
                para = PARA_LOGIN;
                wdServerID = 0;
                wdServerType = 0;
            }
        };
        //////////////////////////////////////////////////////////////
        /// 登陆档案服务器指令
        //////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////
        /// 档案服务器和网关交互的指令
        //////////////////////////////////////////////////////////////
        const BYTE PARA_GATE_CREATECHAR  = 2;
        struct t_CreateChar_GateRecord : public RecordNull 
        {
            AccountInfo accountInfo;
            t_CreateChar_GateRecord()  
            {
                para = PARA_GATE_CREATECHAR;
            };
        };

        const BYTE PARA_GATE_CREATECHAR_RETURN = 3;
        struct t_CreateChar_Return_GateRecord : public RecordNull 
        {
            AccountInfo accountInfo;
            QWORD charID;
            BYTE retcode;						/// 返回代码，0成功 1失败 2账号已有角色 3角色名称重复

            t_CreateChar_Return_GateRecord() 
            {
                para = PARA_GATE_CREATECHAR_RETURN;
                charID = 0;
                retcode = 0;
            };
        };		

        //////////////////////////////////////////////////////////////
        /// 档案服务器和网关交互的指令
        //////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////
        /// 档案服务器和场景交互的指令
        //////////////////////////////////////////////////////////////

        const BYTE PARA_SCENE_FRESHUSER = 5; 
        struct t_freshUser_SceneRecord : RecordNull 
        {   
            QWORD charid;
            DWORD accid;
            DWORD scene_id;

            t_freshUser_SceneRecord()
            {
                para = PARA_SCENE_FRESHUSER;
                charid = 0;
                accid = 0;
                scene_id = 0;
            }
        };

        // 克隆角色，向数据库插入记录
        const BYTE PARA_CLONE_USER_WRITE = 6; 
        struct t_Clone_WriteUser_SceneRecord : RecordNull 
        {   
            DWORD accid;
            QWORD charid;/// 角色
            char prefix[MAX_NAMESIZE];
            DWORD start_index;
            DWORD finish_index;
            CharBase    charbase;               /// 存档的基本信息
            DWORD      dataSize;                ///存档二进制的大小
            char        data[0];                ///存档的二进制数据
            t_Clone_WriteUser_SceneRecord() 
            {   
                para = PARA_CLONE_USER_WRITE;
                bzero(&charbase , sizeof(charbase));
                dataSize = 0;
                accid = 0;
                charid = 0;
                bzero(prefix,MAX_NAMESIZE);
                start_index = 0;
                finish_index = 0;
            }
            DWORD getSize() {return sizeof(*this) + dataSize;}
        };

        //////////////////////////////////////////////////////////////
        /// 档案服务器和场景交互的指令
        //////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////
        /// 档案服务器和Super服务器交互的指令开始
        //////////////////////////////////////////////////////////////


    };

};

#pragma pack()

#endif

