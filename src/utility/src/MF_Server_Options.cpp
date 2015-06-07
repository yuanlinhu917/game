/*****************************************************************
* Copyright (c)2009，上海美峰数码科技有限公司
* All rights reserved.
* 
* 文件名称：MF_Server_Options.cpp
* 文件标识：
* 摘    要：
* 
* 当前版本：1.0
* 作    者：卢松洁
* 完成日期：2009-3-16
*
******************************************************************/
#include "ace/Get_Opt.h"

#include "MF_Server_Options.h"
#include "MF_Log.h"


MF_Server_Options::MF_Server_Options(void)
  : is_run_back_(false),
  is_print_trace_(false), is_print_debug_(false), is_print_info_(false),
  port_(0), run_model_(RUN_DIRECT), log_priority_mask_(0)
{
	MF_TRACE(" MF_Server_Options::MF_Server_Options");
}

MF_Server_Options::~MF_Server_Options(void)
{
	MF_TRACE(" MF_Server_Options::~MF_Server_Options");
}

int MF_Server_Options::parse_args(int argc, ACE_TCHAR *argv[])
{
	MF_TRACE(" MF_Server_Options::parse_args");

	//获取服务名字
	string str(argv[0]);
	string::size_type point_pos = str.rfind('.');
	if(point_pos == string::npos){
		point_pos = str.length();
	}
	string::size_type slash_pos = str.rfind('\\');
	if(slash_pos == string::npos){
		slash_pos = str.rfind('/');
	}
	slash_pos++;
	name_ = str.substr(slash_pos,point_pos-slash_pos);

	//处理命令参数
    ACE_Get_Opt opt(argc, argv, ":p:btdi", 0);

	for (int c; (c = opt()) != -1;) {
		switch(c) {
        case 'p'://p参数设置服务监听的端口号
            this->port_ = ACE_OS::atoi(opt.opt_arg());
            break;
		case 'b': //b参数表示后台处理,日志打印在文件中
			this->is_run_back_ = true;
			break;
        case 't': //b参数表示后台处理,日志打印在文件中
            this->is_print_trace_ = true;
            break;
        case 'd': //b参数表示后台处理,日志打印在文件中
            this->is_print_debug_ = true;
            break;
        case 'i': //b参数表示后台处理,日志打印在文件中
            this->is_print_info_ = true;
            break;
		case ':':
			MF_ERROR("-%c requires an argument\n" ,opt.opt_opt());
			return -1;
		default:
			MF_ERROR("Parse error(%d)\n",c);
			return -1;
		}
	}
	return 0;
}