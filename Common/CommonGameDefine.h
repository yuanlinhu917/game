/******************************************************************************/
#ifndef _COMMONGAMEDEFINE_H_
#define _COMMONGAMEDEFINE_H_
/******************************************************************************/

/******************************************************************************/
//��Ϸ�߼���
/******************************************************************************/
namespace MG
{
	#define		MAX_ACCOUNT_LONGIN_NAME_LEN		32
	#define		MAX_ACCOUNT_LONGIN_PSW_LEN		32
	#define		MAX_ACCOUNT_SUPER_PSW_LEN		32
	#define		MAX_CHARACTER_NAME_LEN			32		//�佫����
	#define		MAX_TROOP_NAME_LEN				32		//��������
	#define		MAX_COMMON_NAME_LEN				32
	#define		MAX_SERVER_NAME_LEN				64
	#define		MAX_VERSION_NUM_LEN				64
	#define     MAX_CLAN_HOMELANDNAME_LEN		32
	#define     MAX_CLAN_NAME					32
	#define		MAX_CAMPAIGN_NAME				32		//ս�۵�����
	#define		MAX_PVE_NAME					32		//PVE������
    
    #define     MAX_CHAT_CONTENT_ROW_COUNT      1000   //�����ʾ����������
    #define     MAX_CHAT_CONTENT_ROW_SIZE       30      //ÿһ����ʾ���ַ���
    #define     MAX_CHAT_CONTENT_ENTER_LEN      100     //һ��������������ַ���

	#define		MAX_REGION_NAME					32		//��������
	#define		MAX_CHARACTER_MODEL_NAME_LEN	32		//��ɫģ��
	
	#define		MAX_ART_MAP_RES_PATH_NAME		64		//�ͻ��˳�����Դ
    #define     DB_RECORD_ATTR_NUM              6       //DB����Ҫ��¼�佫��������Ը���
    #define     MainGenreal_dead_default_recover_hp_val  1  //���佫�������Զ�����Ļ�Ѫ����ս������������߳�ս����ͼ��    
	/******************************************************************************/


	typedef 	I32					NetIdType;							//�� ���� ��ID������
	typedef		U64					ServerUniqueFlagIdType;				// ������Flag����
	typedef		U32					ServerIdType;						// ������ID

	typedef 	U64					AccountIdType;						//�� �˺� ��
	typedef 	U64					GameObjectIdType;					//�� ���е�Ԫ�� ��


	typedef 	U64					PlayerIdType;						//�� ��� ��ID������
	typedef		U64					ClanIdType;							//�� ���� ��ID������	�� ��DB��ȡ ��
	typedef		GameObjectIdType	PlayerCharacterIdType;				//�� ��ɫ ��ID������	�� ��DB��ȡ ��

	typedef		GameObjectIdType	ThirdhPartCharacterIdType;			//�� ��������ɫ ��	ID������
	typedef		GameObjectIdType	MonsterIdType;						//�� ���� ��		ID������
	
	//�°汾 ����
	typedef		GameObjectIdType	TroopSoldierIdType;					//�� ʿ�� ��	ID������
	typedef		GameObjectIdType	TroopIdType;						//�� ���� ��	ID������
	typedef		GameObjectIdType	TroopGroupIdType;					//�� ������ ��	ID������
	typedef		GameObjectIdType	ArmyIdType;							//�� ���� ��	ID������
	typedef		GameObjectIdType	CampIdType;							//�� ��Ӫ ��	ID������

	typedef		GameObjectIdType	TroopGroupIdType;					//�� ���� ��ID������----�ɰ汾
	typedef		GameObjectIdType	BuildingIdType;						//�� ս�������� ��ID������

	
	//typedef 	U64				MapObjectIdType;					//
	//typedef 	U64				PlaceObjectIdType;					//

	//����ͼ�����
	typedef		U16				GameObjectIndexIdInSceneType;		//MapServer Scene���GameObject ����id

	typedef 	U32				RegionIdType;						// MapObject, PlaceObject ͳһ��
	typedef		I32				ArtMapResIdType;					//
	typedef		I32				ArtPointResId;						//��ת�� 
	typedef 	RegionIdType	MapDistributionIdType;				//��ͼ�ֲ�
	typedef 	RegionIdType	MapIdType;	
	typedef 	RegionIdType	PlaceIdType;//
	typedef 	RegionIdType	AreaIdType;//

	typedef 	RegionIdType	InstanceIdType;					// �� ���� ��ID������
	typedef 	RegionIdType	InstanceUIdType;				// �� ���� ��ID��ʵ������ Ψһ

	//Relation
	typedef		I32				RelationIdType;

	//�����������
	typedef 	I32				DistrictIdType;						//�� ���� ��ID������
	typedef 	I32				DistrictTreeIdType;					//�� ������ ��ID������
	
	typedef 	U64				IdType;
	typedef 	U64				CampaignIdType;
	typedef 	I32				QuestIdType;

    //�����ߡ����
    typedef 	U64				ItemIdType;
    typedef 	U32				ItemTempID;

	//�����ܡ����
	typedef 	U32				SkillIdType;

	//���ñ�ģ��ID
	typedef		U32				TemplateIDType;
	typedef		TemplateIDType	ClanTemplateIDType;
		
	/******************************************************************************/

	const	I32	 MAX_QUEST_RECIEVE_NUM	= 10;					//	��ҿ��Խ��ܵ������������
	const	I32	 MAX_QUEST_ALL_NUM		= 2000;					//	�������������

	const Char16 TriggerVersion[] = L"ver1.0";

    /******************************************************************************/
    enum HEADDAMAGE_TYPE
    {
        HEADDAMAGE_TYPE_NULL,

        HEADDAMAGE_TYPE_HP,         
        HEADDAMAGE_TYPE_MP,
        HEADDAMAGE_TYPE_SP,
        HEADDAMAGE_TYPE_ALL,
        HEADDAMAGE_TYPE_MISS, 

        HEADDAMAGE_TYPE_MAX  
    };

    enum HEADDAMAGE_STATE
    {
        HEADDAMAGE_STATE_NULL,

        HEADDAMAGE_STATE_NORMAL,
        HEADDAMAGE_STATE_FADEOUT,

        HEADDAMAGE_STATE_MAX
    };

    enum ACCOUNT_OPERATE_TYPE
    {
        ACCOUNT_OPERATE_NULL,

        ACCOUNT_OPERATE_CREATE,               //�ʺŴ���
        ACCOUNT_OPERATE_DELETE,               //�ʺ�ɾ��
        ACCOUNT_OPERATE_LOGIN,                //�ʺŵ���
        ACCOUNT_OPERATE_LOGOUT,               //�ʺŵǳ�

        ACCOUNT_OPERATE_MAX
    };

	enum PLAYERCHARACTER_OPERATE_TYPE
	{
		PLAYERCHARACTER_OPERATE_NULL,

		PLAYERCHARACTER_OPERATE_CREATE,               //�佫����
		PLAYERCHARACTER_OPERATE_DELETE,               //�佫ɾ��
		PLAYERCHARACTER_OPERATE_LOGIN,                //�佫����
		PLAYERCHARACTER_OPERATE_LOGOUT,               //�佫�ǳ�

		PLAYERCHARACTER_OPERATE_MAX
	};

	enum PLAY_ANIMATION_TYPE
	{
		PLAY_ANIMATION_NULL,
		PLAY_ANIMATION_STAND,
		PLAY_ANIMATION_ATTACK,
		PLAY_ANIMATION_WALK,
		PLAY_ANIMATION_RUN,
		PLAY_ANIMATION_HURT,
		PLAY_ANIMATION_DIE,
	};

    //��Ҫ����Ľṹ��
    struct AttrData
    {
        UInt    attrId;                     //����id
        Flt     attrVal;                    //����ֵ
    };
    struct AttrData_INFO
    {
        static const Int dataSize = sizeof (AttrData);
    };

	struct LineUpSettingInfo
	{
		static const Int line_up_busy_lc_account_login_start_count = 16;				//��¼Login�Ŷ�
		static const Int line_up_busy_fc_account_login_start_count = 8;					//�ʺŵ�¼FrontServer�Ŷ�
		static const Int line_up_busy_fc_create_clan_start_count = 32;					//���������Ŷ�
		static const Int line_up_busy_fc_del_clan_start_count = 32;						//ɾ�������Ŷ�
		static const Int line_up_busy_fc_create_character_start_count = 32;				//������ɫ�Ŷ�
		static const Int line_up_busy_fc_join_game_start_count = 8;						//������Ϸ��ͼ�Ŷ�
	};
    
}


/******************************************************************************/
#endif

