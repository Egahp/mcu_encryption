/**
  ******************************************************************************
  * @file          st7789_1_14.h
  * @brief         st7789 1.14 寸 TFT 驱动
  * @author        Egahp
  *                2687434412@qq.com
  * @version       1.0
  * @date          2021.10.06
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
  * 1.0|Egahp|2021.10.06|创建文件
  ******************************************************************************
  */


#ifndef __ST7789_1_14_H__
#define __ST7789_1_14_H__
/* include -------------------------------------------------------------------*/
#include "stdint.h"

/* marco ---------------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/

/* declare -------------------------------------------------------------------*/

/* variable ------------------------------------------------------------------*/

/* code ----------------------------------------------------------------------*/

void lcd_init(void);
void lcd_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *color);
void lcd_draw_point(uint16_t x, uint16_t y);


#endif
/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/