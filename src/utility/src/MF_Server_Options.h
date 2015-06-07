/*****************************************************************
* Copyright (c)2009���Ϻ���������Ƽ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�MF_Server_Options.h
* �ļ���ʶ��
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
* ��    �ߣ�¬�ɽ�
* ������ڣ�2009-2-9
*
******************************************************************/
#ifndef _MF_SERVER_OPTIONS_H_
#define _MF_SERVER_OPTIONS_H_


#include "data_define.h"
#include "ace/ace_wchar.h"


class MF_Server_Options
{
public:
	static  const uint16_t   MF_DEFAULT_PORT = 20000;
	enum{
		RUN_DIRECT  = 0x01,
		RUN_PROCESS = 0x02,
		RUN_THREAD  = 0x03,	

	};

	enum{
		IPC_SOCKET     = 0x04,
		IPC_SHARED_MEM = 0x08,
	};

public:
	MF_Server_Options(void);
	virtual ~MF_Server_Options(void);

	virtual   int         parse_args(int argc , ACE_TCHAR *argv[]);

	int                   run_model(void){return run_model_;}
	string                name(void){return name_;}
	void                  name(string _name){name_= _name;}
	uint16_t              port(void){return port_;}
	bool                  is_run_back(void){return is_run_back_;}
    bool                  is_print_trace(void){return is_print_trace_;}
    bool                  is_print_debug(void){return is_print_debug_;}
    bool                  is_print_info(void){return is_print_info_;}
	uint32_t              log_priority_mask(void){return log_priority_mask_;}
private:	
	//�Ƿ��̨����
	bool                  is_run_back_;
    bool    is_print_trace_;
    bool    is_print_debug_;
    bool    is_print_info_;

	//�������ж˿ں�
	uint16_t              port_;

	//��������
	string                name_;

	//����ģʽ
	int                   run_model_;

	//��־���ȼ�
	uint32_t			  log_priority_mask_;

	
};

#endif