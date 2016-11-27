#ifndef _SceneCommand_h_
#define _SceneCommand_h_

#include "zNullCmd.h"
#include "messageType.h"
#include "Command.h"
#include "CharBase.h"

#pragma pack(1)

namespace CMD
{

    namespace SCENE
    {
        struct SceneNull : t_NullCmd
        {
            SceneNull()
            {
                cmd = SCENECMD;
            }
        };

        const BYTE PARA_LOGIN = 1;
        struct t_LoginScene : SceneNull 
        {
            WORD wdServerID;
            WORD wdServerType;
            t_LoginScene()
            {
                para = PARA_LOGIN;
                wdServerID = 0;
                wdServerType = 0;
            }
        };

        const BYTE PARA_REFRESH_LOGIN_SCENE = 2;
        struct t_Refresh_LoginScene : SceneNull 
        {
            QWORD charid;
            DWORD dwSceneTempID;
            t_Refresh_LoginScene()
            {
                para = PARA_REFRESH_LOGIN_SCENE;
                charid = 0;
                dwSceneTempID = 0;
            }
        };

        const BYTE PARA_FORWARD_SCENE = 3;
        struct t_Scene_ForwardScene : SceneNull
        {
            QWORD charid;
            DWORD accid;
            DWORD size;
            char data[0];

            t_Scene_ForwardScene()
            {
                para = PARA_FORWARD_SCENE;
                charid = 0;
                accid = 0;
                size = 0;
            }
        };

        const BYTE PARA_SCENE_USER = 4;
        struct t_User_FromScene : SceneNull
        {
            QWORD charid;
            DWORD size;
            char data[0];

            t_User_FromScene()
            {
                para = PARA_SCENE_USER;
                charid = 0;
                size = 0;
            }
        };

        const BYTE PARA_START_OK_SCENE_GATE = 5;
        struct t_StartOKSceneGate : SceneNull
        {
            t_StartOKSceneGate()
            {
                para = PARA_START_OK_SCENE_GATE;
            }
        };
        //gate->secscene
        const BYTE PARA_REG_USER_GATE_SCENE = 9; 
        struct t_regUser_Gatescene : SceneNull
        {
            QWORD charid;
            BYTE byCreate;
            AccountInfo accountInfo;
            t_regUser_Gatescene()
            {
                para = PARA_REG_USER_GATE_SCENE; 
                charid = 0;
                byCreate = 0;
            };
        };

        const BYTE PARA_UNREG_USER_GATE_SCENE = 10;
        enum {
               UNREGUSER_RET_LOGOUT = 0,
        };
        struct t_unregUser_gatescene : SceneNull
        {
            QWORD charid;
            BYTE retcode;
            t_unregUser_gatescene()
            {
                para = PARA_UNREG_USER_GATE_SCENE;
                charid = 0;
                retcode = 0;
            }
        };
    };
};

#pragma pack()

#endif
