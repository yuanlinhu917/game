/*****************************************************************
* Copyright (c)2009，上海美峰数码科技有限公司
* All rights reserved.
* 
* 文件名称：MF_Log.h
* 文件标识：
* 摘    要：
* 
* 当前版本：1.0
* 作    者：卢松洁
* 完成日期：2009-3-10
*
******************************************************************/
#ifndef _MF_LOG_H_
#define _MF_LOG_H_

#include "ace/streams.h"
#include "ace/Log_Msg.h"
#include "ace/Log_Msg_Callback.h"

#include "data_define.h"

class MF_Server_Options;
class MF_Log
{
public:
    enum LOGGING_TYPE
    {
        TYPE_SYSLOG   = 1,
        TYPE_DEAMON   = 2,
        TYPE_OSTREAM  = 3,
        TYPE_STDERR   = 4,
        TYPE_CALLBACK = 5,
        TYPE_FILE     = 6,
    };
public:
    MF_Log(MF_Server_Options& options);
    MF_VIRTUAL ~MF_Log(void);


    MF_VIRTUAL int   open(LOGGING_TYPE type);
    MF_VIRTUAL void  close(void);
    void to_file (void);

private:
    void to_daemon(void);
    void to_syslog(void);
    void to_stream(void);
    void to_stderr(void);
    ACE_Log_Msg_Callback * to_callback(ACE_Log_Msg_Callback *callback);

private:
    MF_Server_Options&  options_;
    ofstream *          log_stream_;
    ACE_OSTREAM_TYPE *  output_stream_;
    
};

class Trace
{
public:
    Trace (const ACE_TCHAR *prefix,
        const ACE_TCHAR *name,
        int line,
        const ACE_TCHAR *file)
    {
        this->prefix_ = prefix;
        this->name_   = name;
        this->line_   = line;
        this->file_   = file;

        ACE_Log_Msg *lm = ACE_LOG_MSG;
        if (lm->tracing_enabled ()
            && lm->trace_active () == 0)
        {
            lm->trace_active (1);
            ACE_DEBUG
                ((LM_TRACE,
                ACE_TEXT ("%s%*s[%T:%t:%M ] calling %s in file `%s'")
                ACE_TEXT (" on line %d\n"),
                this->prefix_,
                Trace::nesting_indent_ * lm->inc (),
                ACE_TEXT (""),
                this->name_,
                this->file_,
                this->line_));
            lm->trace_active (0);
        }
    }

    void setLine (int line)
    {
        this->line_ = line;
    }

    ~Trace (void)
    {
        ACE_Log_Msg *lm = ACE_LOG_MSG;
        if (lm->tracing_enabled ()
            && lm->trace_active () == 0)
        {
            lm->trace_active (1);
            ACE_DEBUG
                ((LM_TRACE,
                ACE_TEXT ("%s%*s[%T:%t:%M ] leaving %s in file `%s'")
                ACE_TEXT (" on line %d\n"),
                this->prefix_,
                Trace::nesting_indent_ * lm->dec (),
                ACE_TEXT (""),
                this->name_,
                this->file_,
                this->line_));
            lm->trace_active (0);
        }
    }

private:
    enum { nesting_indent_ = 3 };

    const ACE_TCHAR *prefix_;
    const ACE_TCHAR *name_;
    const ACE_TCHAR *file_;
    int line_;
};
// Listing 1

// Listing 2 code/ch03
#define TRACE_PREFIX       ACE_TEXT ("")

#if defined (TRACE)
#undef TRACE
#endif /* TRACE */

#if (MF_NTRACE == 1)
#    define MF_TRACE(X)
#    define MF_TRACE_RETURN(V)     return V;
#    define MF_TRACE_RETURN_VOID()
#else
#    define MF_TRACE(X)
//
// //Trace ____ (TRACE_PREFIX,
//  //ACE_TEXT (X),
//  //__LINE__,
//  //ACE_TEXT (__FILE__))

#    define MF_TRACE_RETURN(V)                    \
    do { ____.setLine(__LINE__); return V; } while (0)

#    define MF_TRACE_RETURN_VOID()                \
    do { ____.setLine(__LINE__); } while (0)
#endif
// Listing 2

//////////////////////////////////////////////////


#define DEBUG_PREFIX       ACE_TEXT ("[%T:%t:%M] ")
#define INFO_PREFIX        ACE_TEXT ("%I[%T:%t:%M] ")
#define NOTICE_PREFIX      ACE_TEXT ("[%T:%t:%M] ")
#define WARNING_PREFIX     ACE_TEXT ("[%T:%t:%M][%N:%l] ")
#define ERROR_PREFIX       ACE_TEXT ("[%T:%t:%M][%N:%l] ")
#define CRITICAL_PREFIX    ACE_TEXT ("[%T:%t:%M][%N:%l] ")
#define ALERT_PREFIX       ACE_TEXT ("[%T:%t:%M][%N:%l] ")
#define EMERGENCY_PREFIX   ACE_TEXT ("[%T:%t:%M][%N:%l] ")


#define MF_DEBUG(...)     \
    ACE_DEBUG(( LM_DEBUG, \
    DEBUG_PREFIX          \
    __VA_ARGS__))

#define MF_INFO( ...)     \
    ACE_DEBUG(( LM_INFO,  \
    INFO_PREFIX           \
    __VA_ARGS__))

#define MF_NOTICE( ...)     \
    ACE_DEBUG(( LM_NOTICE,  \
    NOTICE_PREFIX           \
    __VA_ARGS__))

#define MF_WARNING( ...)     \
    ACE_DEBUG(( LM_WARNING,  \
    WARNING_PREFIX           \
    __VA_ARGS__))

#define MF_ERROR( ...)     \
    ACE_DEBUG(( LM_ERROR,  \
    ERROR_PREFIX           \
    __VA_ARGS__))

#define MF_CRITICAL( ...)     \
    ACE_DEBUG(( LM_CRITICAL,  \
    CRITICAL_PREFIX           \
    __VA_ARGS__))

#define MF_ALERT( ...)     \
    ACE_DEBUG(( LM_ALERT,  \
    ALERT_PREFIX           \
    __VA_ARGS__))

#define MF_EMERGENCY( ...)     \
    ACE_DEBUG(( LM_EMERGENCY,  \
    EMERGENCY_PREFIX           \
    __VA_ARGS__))




#endif
