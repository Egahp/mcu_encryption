/**
  ******************************************************************************
  * @file          tea.h
  * @brief         tea 加解密算法
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

#ifndef __TEA_H__
#define __TEA_H__
/* include -------------------------------------------------------------------*/
#include "stdint.h"

/** @addtogroup TEA tea 加解密算法
 * @{
 */

/**
 *   @brief         tea 加密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void tea_encrypt(uint8_t *data, uint8_t *key);

/**
 *   @brief         tea 解密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void tea_decrypt(uint8_t *data, uint8_t *key);

/**
 *   @brief         xtea 加密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xtea_encrypt(uint8_t *data, uint8_t *key);

/**
 *   @brief         xtea 解密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xtea_decrypt(uint8_t *data, uint8_t *key);

/**
 *   @brief         xxtea 加密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xxtea_encrypt(uint8_t *data, uint8_t *key);

/**
 *   @brief         xxtea 解密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xxtea_decrypt(uint8_t *data, uint8_t *key);

/**
 * @}
 */

#endif
/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/
