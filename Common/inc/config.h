/**
  ******************************************************************************
  * @file          config.h
  * @brief         配置文件
  * @author        Egahp
  *                2687434412@qq.com
  * @version       1.0
  * @date          2021.10.03
  ******************************************************************************
  * @attention
  * 
  * <h2><center>&copy; Copyright 2021 Egahp.
  * All rights reserved.</center></h2>
  * 
  * @htmlonly 
  * <span style='font-weight: bold'>History</span> 
  * @endhtmlonly
  * 版本|作者|时间|描述
  * ----|----|----|----
  * 1.0|Egahp|2021.10.03|创建文件
  ******************************************************************************
  */

#ifndef __CONFIG_H__
#define __CONFIG_H__


// <<< Use Configuration Wizard in Context Menu >>>

// <e> Debug 功能
#define ME_DEBUG_ENABLE                 1

// <o> 调试等级
// <0=> 仅错误
// <1=> 警告和错误
// <2=> 信息、警告和错误
// <3=> 全部调试信息
#define ME_DEBUG_LEVEL                  3

// </e>

// <o> 唯一ID地址
#define ME_ID_BASE                      0x1FFFF7ACUL

// <o> 唯一ID长度(bytes)
#define ME_ID_LENGTH                    12


// <<< end of configuration section >>>

#endif
/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/
