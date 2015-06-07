/*****************************************************************
* Copyright (c)2009，上海美峰数码科技有限公司
* All rights reserved.
* 
* 文件名称：MF_Server_Options.h
* 文件标识：
* 摘    要：
* 
* 当前版本：1.0
* 作    者：卢松洁
* 完成日期：2009-2-9
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
	//是否后台运行
	bool                  is_run_back_;
    bool    is_print_trace_;
    bool    is_print_debug_;
    bool    is_print_info_;

	//服务运行端口号
	uint16_t              port_;

	//服务名字
	string                name_;

	//运行模式
	int                   run_model_;

	//日志优先级
	uint32_t			  log_priority_mask_;

	
};

#endif