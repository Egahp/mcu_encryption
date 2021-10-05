/**
  ******************************************************************************
  * @file          xxtea.c
  * @brief         xxtea 加解密算法
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

/* marco ---------------------------------------------------------------------*/
#define MX (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z)

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
 *   @brief         xxtea 加密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xxtea_encrypt(uint8_t *data, uint8_t *key)
{
  uint8_t n = BLOCK_SIZE / 4;

  uint32_t delta = tea_get_delta();

  uint32_t *v = (uint32_t *)data;
  uint32_t *k = (uint32_t *)key;

  uint32_t z = v[n - 1];
  uint32_t y = v[0];
  uint32_t sum = 0;
  uint32_t e;

  uint8_t p;
  uint8_t q;

  q = 6 + 52 / n;

  while (q-- > 0)
  {
    sum += delta;
    e = sum >> 2 & 3;

    for (p = 0; p < n - 1; p++)
    {
      y = v[p + 1], z = v[p] += MX;
    }

    y = v[0];
    z = v[n - 1] += MX;
  }
}

/**
 *   @brief         xxtea 解密算法
 *   @param  data                   数据缓冲区
 *   @param  key                    秘钥
 */
void xxtea_decrypt(uint8_t *data, uint8_t *key)
{
  uint8_t n = BLOCK_SIZE / 4;

  uint32_t delta = tea_get_delta();

  uint32_t *v = (uint32_t *)data;
  uint32_t *k = (uint32_t *)key;

  uint32_t z = v[n - 1];
  uint32_t y = v[0];
  uint32_t sum = 0;
  uint32_t e;

  uint8_t p;
  uint8_t q;

  q = 6 + 52 / n;
  sum = q * delta;

  while (sum != 0)
  {
    e = sum >> 2 & 3;
    for (p = n - 1; p > 0; p--)
    {
      z = v[p - 1], y = v[p] -= MX;
    }

    z = v[n - 1];
    y = v[0] -= MX;
    sum -= delta;
  }
}

/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/
