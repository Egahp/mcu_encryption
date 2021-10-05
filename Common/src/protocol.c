/**
  ******************************************************************************
  * @file          protocol.c
  * @brief         对 HID 通信简单的封装
  * @author        Egahp
  *                2687434412@qq.com
  * @version       1.0
  * @date          2021.10.05
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
  * 1.0|Egahp|2021.10.05|创建文件
  ******************************************************************************
  */


/* include -------------------------------------------------------------------*/
#include "protocol.h"
/* marco ---------------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/

/* declare -------------------------------------------------------------------*/

/* variable ------------------------------------------------------------------*/

/* code ----------------------------------------------------------------------*/

/*!< 

packet size 64byte

    | byte 0,1  |       byte 6 - 63 |
    | crc 16    |       data        |
 */

uint8_t me_protocol_packet_transmit()
{
    return 0;
}

uint32_t me_protocol_transmit(uint8_t *data, uint32_t size, uint32_t packet_size, uint8_t (*packet_transmit)(uint8_t *data))
{

}

uint32_t me_protocol_receive(uint8_t *data, uint32_t size, uint32_t packet_size)
{

}



/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/
