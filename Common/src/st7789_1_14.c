/**
  ******************************************************************************
  * @file          st7789_1_14.c
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


/* include -------------------------------------------------------------------*/
#include "spi.h"
#include "gpio.h"
#include "st7789_1_14.h"

/* marco ---------------------------------------------------------------------*/
#define LCD_ROTATION            180

#define LCD_HORIZONTAL_POINT    240
#define LCD_VERTICAL_POINT      135
#define LCD_POINT_SIZE          16

#if (LCD_ROTATION == 0 || LCD_ROTATION == 90)
#define LCD_WIDTH               LCD_VERTICAL_POINT
#define LCD_HEIGHT              LCD_HORIZONTAL_POINT
#elif (LCD_ROTATION == 180 || LCD_ROTATION == 270)
#define LCD_WIDTH               LCD_HORIZONTAL_POINT
#define LCD_HEIGHT              LCD_VERTICAL_POINT
#else
    #error "LCD ROTATION ERROR"
#endif

#define LCD_BASE_TRANSMIT(pdata, size)      HAL_SPI_Transmit(&hspi1, (pdata), (size), 1000)
// #define LCD_BASE_TRANSMIT(pdata, size)      HAL_SPI_Transmit_DMA(&hspi1, (pdata), (size))

#define LCD_CMD_SET()                       HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)
#define LCD_DAT_SET()                       HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)

#define LCD_PWR_ON()                        HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_SET)
#define LCD_PWR_OFF()                       HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_RESET)

#define LCD_RST_SET()                       HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET)
#define LCD_RST_RESET()                     HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET)

/* typedef -------------------------------------------------------------------*/

/* declare -------------------------------------------------------------------*/

/* variable ------------------------------------------------------------------*/
#define LCD_BUFFER_SIZE     2048
static uint64_t lcd_buffer[LCD_BUFFER_SIZE / 8];

/* code ----------------------------------------------------------------------*/

static void lcd_wc(uint8_t cmd)
{
    LCD_CMD_SET();

    LCD_BASE_TRANSMIT(&cmd, 1);
}

static void lcd_wd(uint8_t dat)
{
    LCD_DAT_SET();

    LCD_BASE_TRANSMIT(&dat, 1);
}

static void lcd_wd_halfword(uint16_t dat)
{
    uint8_t data[2];

    data[0] = dat >> 8;
    data[1] = dat;

    LCD_DAT_SET();

    LCD_BASE_TRANSMIT(data, 2);
}

static void lcd_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

#if (LCD_ROTATION == 0)
    lcd_wc(0x2a);
    lcd_wd_halfword(x1 + 52);
    lcd_wd_halfword(x2 + 52);

    lcd_wc(0x2b);
    lcd_wd_halfword(y1 + 40);
    lcd_wd_halfword(y2 + 40);

#elif (LCD_ROTATION == 90)
    lcd_wc(0x2a);
    lcd_wd_halfword(x1 + 53);
    lcd_wd_halfword(x2 + 53);

    lcd_wc(0x2b);
    lcd_wd_halfword(y1 + 40);
    lcd_wd_halfword(y2 + 40);

#elif (LCD_ROTATION == 180)
    lcd_wc(0x2a);
    lcd_wd_halfword(x1 + 40);
    lcd_wd_halfword(x2 + 40);

    lcd_wc(0x2b);
    lcd_wd_halfword(y1 + 53);
    lcd_wd_halfword(y2 + 53);

#elif (LCD_ROTATION == 270)
    lcd_wc(0x2a);
    lcd_wd_halfword(x1 + 40);
    lcd_wd_halfword(x2 + 40);

    lcd_wc(0x2b);
    lcd_wd_halfword(y1 + 52);
    lcd_wd_halfword(y2 + 52);

#else
    #error "LCD ROTATION ERROR"
#endif

    lcd_wc(0x2c);
}

void lcd_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *color)
{
    uint16_t i = 0;
    uint32_t size = 0;
    uint32_t size_reamin = 0;

    size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;

    if (size > LCD_BUFFER_SIZE)
    {
        size_reamin = size - LCD_BUFFER_SIZE;
        size = LCD_BUFFER_SIZE;
    }

    lcd_set_address(x1, y1, x2, y2);

    while(1)
    {
        for (i = 0; i < size / 2; i++)
        {
            ((uint8_t *)lcd_buffer)[2 * i] = *color >> 8;
            ((uint8_t *)lcd_buffer)[2 * i + 1] = *color;
            color++;
        }

        LCD_DAT_SET();
        LCD_BASE_TRANSMIT((uint8_t *)lcd_buffer, size);

        if (size_reamin == 0)
        {
            break;
        }

        if (size_reamin > LCD_BUFFER_SIZE)
        {
            size_reamin = size_reamin - LCD_BUFFER_SIZE;
        }
        else
        {
            size = size_reamin;
            size_reamin = 0;
        }
    }
}

void lcd_draw_point(uint16_t x, uint16_t y)
{
    lcd_set_address(x, y, x, y);
    lcd_wd_halfword(0xffff);
}

void lcd_init(void)
{
    LCD_PWR_OFF();
    HAL_Delay(120);

    LCD_RST_RESET();
    HAL_Delay(120);

    LCD_RST_SET();
    HAL_Delay(120);

    lcd_wc(0x11);   /*!< lcd sleep out */
    HAL_Delay(120);


    /*!< memory data access control */
#if (LCD_ROTATION == 0)
    lcd_wc(0x36);
    lcd_wd(0x00);

#elif (LCD_ROTATION == 90)
    lcd_wc(0x36);
    lcd_wd(0xC0);

#elif (LCD_ROTATION == 180)
    lcd_wc(0x36);
    lcd_wd(0x70);

#elif (LCD_ROTATION == 270)
    lcd_wc(0x36);
    lcd_wd(0xA0);

#else
    #error "LCD ROTATION ERROR"
#endif

    /*!< RGB 565 mode */
    lcd_wc(0x3A);
    lcd_wd(0x05);

    /*!< porch setting */
    lcd_wc(0xB2);
    lcd_wd(0x0C);
    lcd_wd(0x0C);
    lcd_wd(0x00);
    lcd_wd(0x33);
    lcd_wd(0x33);

    /*!< gate control */
    lcd_wc(0xB7);
    lcd_wd(0x35);

    /*!< vcom setting 1.625V */
    lcd_wc(0xBB);
    lcd_wd(0x19);

    /*!< lcm control */
    lcd_wc(0xC0);
    lcd_wd(0x2C);

    /*!< vdv and vrh cmd enable */
    lcd_wc(0xC2);
    lcd_wd(0x01);

    /*!< vrh set */
    lcd_wc(0xC3);
    lcd_wd(0x12);

    /*!< vdv set */
    lcd_wc(0xC4);
    lcd_wd(0x20);

    /*!< frame rate control in normal mode 60 Hz */
    lcd_wc(0xC6);
    lcd_wd(0x0F);

    /*!< power control 1 */
    lcd_wc(0xD0);
    lcd_wd(0xA4);
    lcd_wd(0xA1);

    /*!< positive voltage gamma control */
    lcd_wc(0xE0);
    lcd_wd(0xD0);
    lcd_wd(0x04);
    lcd_wd(0x0D);
    lcd_wd(0x11);
    lcd_wd(0x13);
    lcd_wd(0x2B);
    lcd_wd(0x3F);
    lcd_wd(0x54);
    lcd_wd(0x4C);
    lcd_wd(0x18);
    lcd_wd(0x0D);
    lcd_wd(0x0B);
    lcd_wd(0x1F);
    lcd_wd(0x23);

    /*!< negative voltage gamma control */
    lcd_wc(0xE1);
    lcd_wd(0xD0);
    lcd_wd(0x04);
    lcd_wd(0x0C);
    lcd_wd(0x11);
    lcd_wd(0x13);
    lcd_wd(0x2C);
    lcd_wd(0x3F);
    lcd_wd(0x44);
    lcd_wd(0x51);
    lcd_wd(0x2F);
    lcd_wd(0x1F);
    lcd_wd(0x1F);
    lcd_wd(0x20);
    lcd_wd(0x23);


    /*!< display inversion on */
    lcd_wc(0x21);

    /*!< sleep in */
    lcd_wc(0x29);

    lcd_set_address(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    LCD_PWR_ON();
}


/************************ (C) COPYRIGHT 2021 Egahp *****END OF FILE*************/
