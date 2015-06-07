/*****************************************************************
* Copyright (c)2009���Ϻ���������Ƽ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�MF_Log.cpp
* �ļ���ʶ��
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
* ��    �ߣ�¬�ɽ�
* ������ڣ�2009-3-16
*
******************************************************************/


#include "MF_Log.h"
#include "MF_Server_Options.h"

#include "ace/OS.h"
#include "ace/Date_Time.h"
#include "ace/Select_Reactor.h"
#include "ace/Service_Config.h"



#include <fstream>
#include <sstream>

MF_Log::MF_Log(MF_Server_Options& options):options_(options),log_stream_(0),output_stream_(0)
{

}

MF_Log::~MF_Log(void)
{
	close();

}


int  MF_Log::open(LOGGING_TYPE type)
{

	//string param("-f log.conf");
	//if(ACE_Service_Config::open(options_.name().c_str(), ACE_DEFAULT_LOGGER_KEY, 1, 0, 1) == -1){
	//	MF_ERROR("ACE_Service_Config::open() == -1!");
	//	return -1;
	//}
	//ACE_Service_Config::process_file("log.conf");

	//u_long priority_mask = ACE_LOG_MSG->priority_mask (ACE_Log_Msg::PROCESS);
	//ACE_CLR_BITS(priority_mask,LM_TRACE);
	//ACE_LOG_MSG->priority_mask(priority_mask,ACE_Log_Msg::PROCESS);

	return 0;
//	ACE_Service_Config::process_file()
	////������߳�ģʽ
	//if(options_.run_model() == MF_Server_Options::RUN_THREAD){
	//	u_long priority_mask = ACE_LOG_MSG->priority_mask (ACE_Log_Msg::THREAD);
	//	ACE_CLR_BITS(priority_mask,options_.log_priority_mask());
	//	ACE_LOG_MSG->priority_mask(priority_mask,ACE_Log_Msg::THREAD);
	//}
	////����ǽ���ģʽ
	//else if(options_.run_model() == MF_Server_Options::RUN_DIRECT){
	/*	u_long priority_mask = ACE_LOG_MSG->priority_mask (ACE_Log_Msg::PROCESS);
		ACE_CLR_BITS(priority_mask,options_.log_priority_mask());
		ACE_LOG_MSG->priority_mask(priority_mask,ACE_Log_Msg::PROCESS);*/


	//	switch(type)
	//	{
	//	case TYPE_DEAMON:
	//		to_daemon();
	//		break;
	//	case TYPE_SYSLOG:
	//		to_syslog();
	//		break;
	//	case TYPE_STDERR:
	//		to_stderr();
	//		break;
	//	case TYPE_FILE:
	//		to_file();
	//		break;
	//	case TYPE_OSTREAM:
	//		to_stream();
	//		break;
	//	case TYPE_CALLBACK:
	//		//to_callback()
	//		break;
	//	default:
	//		break;
	//	}
	return 0;
}

void   MF_Log::close(void)
{
	ACE_LOG_MSG->clr_flags(ACE_Log_Msg::OSTREAM);
	if(log_stream_){
		delete log_stream_;
	}
}

void  MF_Log::to_daemon(void)
{

	ACE_LOG_MSG->open(options_.name().c_str(), ACE_Log_Msg::LOGGER, ACE_DEFAULT_LOGGER_KEY);
}

void  MF_Log::to_syslog(void)
{
	ACE_LOG_MSG->open (options_.name().c_str(), ACE_Log_Msg::SYSLOG, options_.name().c_str());
}

void  MF_Log::to_stream(void)
{

}

void  MF_Log::to_file (void)
{

	
	//������־Ŀ¼
	if(!ACE_OS::opendir("log")){
		ACE_OS::mkdir("log");
	}

	//��־��
	log_stream_ = new std::ofstream;

	//������־����
	std::ostringstream str_log;	
	ACE_Time_Value time = ACE_OS::gettimeofday();
	ACE_Date_Time now(time);
	str_log <<"log/"<<options_.name()<<"_"<<options_.port()<<"_"<<now.year()<<now.month()<<now.day()<<"_"<<now.hour()<<now.minute()<<now.second()<<".log";

	//������־�ļ�
	log_stream_->open(str_log.str().c_str(), ios::out | ios::trunc);


	//������־����������
	ACE_LOG_MSG->clr_flags (ACE_Log_Msg::STDERR| ACE_Log_Msg::LOGGER);
	ACE_LOG_MSG->set_flags (ACE_Log_Msg::OSTREAM);
	ACE_LOG_MSG->msg_ostream (log_stream_); 
}

void  MF_Log::to_stderr(void)
{
	ACE_LOG_MSG->clr_flags(ACE_Log_Msg::OSTREAM | ACE_Log_Msg::LOGGER);
	ACE_LOG_MSG->set_flags (ACE_Log_Msg::STDERR);
}