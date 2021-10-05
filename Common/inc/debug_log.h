/**
  ******************************************************************************
  * @file          debug_log.h
  * @brief         debug log
  * @author        Egahp
  * @email         2687434412@qq.com
  * @version       1.0
  * @date          2021.07.06
  ******************************************************************************
  * @attention
  * 
  * <h2><center>&copy; Copyright 2020 Egahp.
  * All rights reserved.</center></h2>
  * 
  * @htmlonly 
  * <span style='font-weight: bold'>修订历史</span> 
  * @endhtmlonly
  * 版本|作者|时间|描述
  * ----|----|----|----
  * 1.0|Egahp|2021.07.06|创建文件
  ******************************************************************************
  */

#ifndef __DEBUG_LOG_H__
#define __DEBUG_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "SEGGER_RTT.h"

void debug_log_init(void);

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define __DEBUG_ENABLE

#ifdef __DEBUG_ENABLE
    void assert_handler(const char *x_string,const char *file,uint32_t line);
    #define ASSERT_PARAM(x)\
    if(!(x)){\
        assert_handler(#x,__FILENAME__,__LINE__);\
    }
    #define ASSERT_FUNC(x)\
    if(!(x)){\
        assert_handler(#x,__FILENAME__,__LINE__);\
    }
    #else 
    #define ASSERT_PARAM(x)
    #define ASSERT_FUNC(x)  x
#endif

#ifndef LOG_ERROR_CHANNEL
    #define LOG_ERROR_CHANNEL   0
#endif

#ifndef LOG_WARN_CHANNEL
    #define LOG_WARN_CHANNEL    0
#endif

#ifndef LOG_INFO_CHANNEL
    #define LOG_INFO_CHANNEL    0
#endif

#ifndef LOG_DEBUG_CHANNEL
    #define LOG_DEBUG_CHANNEL   0
#endif

#ifndef LOG_ERROR_TERMINAL
    #define LOG_ERROR_TERMINAL  0
#endif

#ifndef LOG_WARN_TERMINAL
    #define LOG_WARN_TERMINAL   0
#endif

#ifndef LOG_INFO_TERMINAL
    #define LOG_INFO_TERMINAL   0
#endif

#ifndef LOG_DEBUG_TERMINAL
    #define LOG_DEBUG_TERMINAL  0
#endif

#ifndef LOG_ERROR_COLOR
    #define LOG_ERROR_COLOR     RTT_CTRL_TEXT_BRIGHT_RED
#endif

#ifndef LOG_WARN_COLOR
    #define LOG_WARN_COLOR     RTT_CTRL_TEXT_BRIGHT_YELLOW
#endif

#ifndef LOG_INFO_COLOR
    #define LOG_INFO_COLOR     RTT_CTRL_TEXT_BRIGHT_GREEN
#endif

#ifndef LOG_DEBUG_COLOR
    #define LOG_DEBUG_COLOR     RTT_CTRL_TEXT_BRIGHT_MAGENTA
#endif

#ifdef __DEBUG_ENABLE
    #define LOG_ERROR(  format, ...)    SEGGER_RTT_SetTerminal(LOG_ERROR_TERMINAL);\
                                        SEGGER_RTT_printf(LOG_ERROR_CHANNEL,"%s[E]>> ",LOG_ERROR_COLOR);\
                                        SEGGER_RTT_printf(LOG_ERROR_CHANNEL,format, ##__VA_ARGS__); 

    #define LOG_WARN(   format, ...)    SEGGER_RTT_SetTerminal(LOG_WARN_TERMINAL);\
                                        SEGGER_RTT_printf(LOG_WARN_CHANNEL,"%s[W]>> ",LOG_WARN_COLOR);\
                                        SEGGER_RTT_printf(LOG_WARN_CHANNEL ,format, ##__VA_ARGS__)

    #define LOG_INFO(   format, ...)    SEGGER_RTT_SetTerminal(LOG_INFO_TERMINAL);\
                                        SEGGER_RTT_printf(LOG_INFO_CHANNEL,"%s[I]>> ",LOG_INFO_COLOR);\
                                        SEGGER_RTT_printf(LOG_INFO_CHANNEL ,format, ##__VA_ARGS__)

    #define LOG_DEBUG(  format, ...)    SEGGER_RTT_SetTerminal(LOG_DEBUG_TERMINAL);\
                                        SEGGER_RTT_printf(LOG_DEBUG_CHANNEL,"%s[D]>> ",LOG_DEBUG_COLOR);\
                                        SEGGER_RTT_printf(LOG_DEBUG_CHANNEL,format, ##__VA_ARGS__)
#else
    #define LOG_ERROR(  format, ...)   
    #define LOG_WARN(   format, ...)
    #define LOG_INFO(   format, ...)
    #define LOG_DEBUG(  format, ...)
#endif



#include "config.h"

#if ((ME_DEBUG_ENABLE == 1) && (ME_DEBUG_LEVEL >= 3))
    #define LOG_D                   LOG_DEBUG
#else
    #define LOG_D(  format, ...)
#endif

#if ((ME_DEBUG_ENABLE == 1) && (ME_DEBUG_LEVEL >= 2))
    #define LOG_I                   LOG_INFO
#else
    #define LOG_I(  format, ...)
#endif

#if ((ME_DEBUG_ENABLE == 1) && (ME_DEBUG_LEVEL >= 1))
    #define LOG_W                   LOG_WARN
#else
    #define LOG_W(  format, ...)
#endif

#if ((ME_DEBUG_ENABLE == 1) && (ME_DEBUG_LEVEL >= 0))
    #define LOG_E                   LOG_ERROR
#else
    #define LOG_E(  format, ...)
#endif


#ifdef __cplusplus
}
#endif

#endif
/************************ (C) COPYRIGHT 2020 Egahp *****END OF FILE*************/
