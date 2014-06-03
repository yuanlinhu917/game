/******************************************************************************/
#ifndef _VERSIONSWITCH_H_
#define _VERSIONSWITCH_H_
/******************************************************************************/

/******************************************************************************/
//��Ϸ����
/******************************************************************************/
//MG Encrypt Key
#define ENCRYPT_KEY1	0x111A630D
#define ENCRYPT_KEY2	0x12A2B0B5
#define ENCRYPT_KEY3	0x1A5378FF
#define ENCRYPT_KEY4	0x1DCCD2E3

/******************************************************************************/
//��Ϸ�汾����
#define _SCHINESE
/******************************************************************************/
#define GAME_APP_TITLE_PART1		L" - Ver. "
#define GAME_APP_TITLE_PART2		L" ��"
#define GAME_APP_TITLE_PART3		L"�� "
//CH -- ���w����
//TH -- ���w����
//JP -- ����
//EN -- Ӣ��
//District Setting
//�؅^̖. �Y��Ƭ̖�a. �汾̖�a. �����Δ� 
#ifdef _SCHINESE	//China
    #define CLIENT_VERSION_NUMBER		"CH.20121217"
    #define SERVER_VERSION_NUMBER		"CH.20121217"
    #define _MG_RELEASE_20121217
#endif
#ifdef _TCHINESE	//Taiwan, Hong Kong
    #define CLIENT_VERSION_NUMBER		"TH.20121217"
    #define SERVER_VERSION_NUMBER		"TH.20121217"
#endif

/******************************************************************************/
//��Ϸ�߼�����
/******************************************************************************/
#ifdef _MG_RELEASE_20121217

    // ------------------------------------------------------------------
    //@ use
    // ------------------------------------------------------------------
    #define _SYSTEM_GM_				    // ����ָ��
    #define _CHECK_VER_					// �汾���
    #define _SYSTEM_ACCELERATION_HACK_	// ������
    #define _SYSTEM_GM_TOOL_            // GM����
    #define _USE_MAX_LVL
    // -------------------------------------------------------------------
    //@ unUse
    /* -------------------------------------------------------------------
    #define _SYSTEM_GUILD_              // ����
    #define _SYSTEM_AUCTION_            // ����
    #define _SYSTEM_RMBSHOP_            // �̳�
    #define _SYSTEM_MAIL_				// �]��

    #define _SYSTEM_FCM_				// ������
    #define _SYSTEM_NAVI_               // ����
    #define _SYSTEM_INLAY_              // ��Ƕ
    #define _SYSTEM_TALENT_             // �츳  

    #define _LOG_SERVER_				// log������
    #define _USE_AI_SERVER		        // Boss�Ƿ�ʹ��AIServer
    ------------------------------------------------------------------- */
#endif

/******************************************************************************/
#endif

