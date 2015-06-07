/*****************************************************************
* Copyright (c)2009���Ϻ���������Ƽ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�MF_Server_Options.cpp
* �ļ���ʶ��
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
* ��    �ߣ�¬�ɽ�
* ������ڣ�2009-3-16
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

	//��ȡ��������
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

	//�����������
    ACE_Get_Opt opt(argc, argv, ":p:btdi", 0);

	for (int c; (c = opt()) != -1;) {
		switch(c) {
        case 'p'://p�������÷�������Ķ˿ں�
            this->port_ = ACE_OS::atoi(opt.opt_arg());
            break;
		case 'b': //b������ʾ��̨����,��־��ӡ���ļ���
			this->is_run_back_ = true;
			break;
        case 't': //b������ʾ��̨����,��־��ӡ���ļ���
            this->is_print_trace_ = true;
            break;
        case 'd': //b������ʾ��̨����,��־��ӡ���ļ���
            this->is_print_debug_ = true;
            break;
        case 'i': //b������ʾ��̨����,��־��ӡ���ļ���
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