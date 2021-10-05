/**
  ******************************************************************************
  * @file          xtea.c
  * @brief         xtea 加解密算法
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
#include "stdint.h"

#define BLOCK_SIZE 64

/* code ----------------------------------------------------------------------*/

/**
 *   @brief         获取 delta
 *   @return uint32_t delta
 */
static uint32_t tea_get_delta(void)
{
    uint32_t orign = 0xb5676ed5;
    uint32_t delta = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        delta |= ((orign & (0x00010001 << i)) << i);
        delta |= (((orign >> 8) & (0x00010001 << i)) << (i + 1));
    }

    return delta;
}

/**
 *   @brief         xtea 加密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xtea_encrypt(uint8_t *data, uint8_t *key)
{

    uint32_t delta = tea_get_delta();

    uint32_t *v = (uint32_t *)data;
    uint32_t *k = (uint32_t *)key;

    uint32_t v0;
    uint32_t v1;
    uint32_t sum;

    for (uint8_t block = 0; block < BLOCK_SIZE / 8; block++)
    {
        sum = 0;

        v0 = v[(block << 1) + 0];
        v1 = v[(block << 1) + 1];

        for (uint8_t i = 0; i < 32; i++)
        {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
        }

        v[(block << 1) + 0] = v0;
        v[(block << 1) + 1] = v1;
    }
}

/**
 *   @brief         xtea 解密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xtea_decrypt(uint8_t *data, uint8_t *key)
{

    uint32_t delta = tea_get_delta();

    uint32_t *v = (uint32_t *)data;
    uint32_t *k = (uint32_t *)key;

    uint32_t v0;
    uint32_t v1;
    uint32_t sum;

    for (uint8_t block = 0; block < BLOCK_SIZE / 8; block++)
    {
        sum = delta * 32;

        v0 = v[(block << 1) + 0];
        v1 = v[(block << 1) + 1];

        for (uint8_t i = 0; i < 32; i++)
        {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        }

        v[(block << 1) + 0] = v0;
        v[(block << 1) + 1] = v1;
    }
}

/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/
