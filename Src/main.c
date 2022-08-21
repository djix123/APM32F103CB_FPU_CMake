/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.2
 *
 * @date        2022-01-05
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "main.h"
#include "apm32f10x.h"
#include "apm32f10x_gpio.h"
#include "apm32f10x_rcm.h"
#include "apm32f10x_usart.h"
#include <stdio.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup GPIO_Toggle
  @{
  */

/** @defgroup GPIO_Toggle_Functions
  @{
  */

int _write(int fd, char *ch, int len)
{
   for(int i=0; i<len; i++) {
       while(USART_ReadStatusFlag(USART1, USART_FLAG_TXBE) == RESET);
       USART_TxData(USART1, *(ch+i));
   }
   return len;
}

volatile uint32_t ticks = 0;

void fpu_enable(void);
void usart_init(void);

void apm_led_init(void);
void apm_led_toggle(void);

float x[2] = {2.0,2.0};
float y[2] = {3.0,3.0};

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    SysTick_Config(SystemCoreClock / 1000);

    fpu_enable();
    apm_led_init();
    usart_init();

    uint32_t count = 0;
    float result = 0.0f;
    float angle = -2.0f * 3.1459f;

    while (1)
    {
        Delay(1000);
        apm_led_toggle();

        result = sc_math_sin(angle);
        printf("Loop...%ld, sin(%0.4f) = %0.4f\r\n", count, angle, result);

        angle += 0.1f;
        if(angle > 2.0f * 3.1459f) {
            angle = -2.0f * 3.1459f;
        }
        count++;
    }
}

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
void Delay(uint32_t ms)
{
    uint32_t delay = ticks + ms;
    while(delay > ticks);
}

void fpu_enable(void)
{
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_FPU);
    RCM->CFG |= BIT27;
}

void usart_init(void)
{
    GPIO_Config_T GPIO_configStruct;
    USART_Config_T USART_configStruct;

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1);

    GPIO_configStruct.mode = GPIO_MODE_AF_PP;
    GPIO_configStruct.pin = GPIO_PIN_9;
    GPIO_configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_configStruct);

    GPIO_configStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_configStruct.pin = GPIO_PIN_10;
    GPIO_Config(GPIOA, &GPIO_configStruct);

    USART_configStruct.baudRate = 115200;
    USART_configStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    USART_configStruct.mode = USART_MODE_TX_RX;
    USART_configStruct.parity = USART_PARITY_NONE;
    USART_configStruct.stopBits = USART_STOP_BIT_1;
    USART_configStruct.wordLength = USART_WORD_LEN_8B;
    USART_Config(USART1, &USART_configStruct);

    USART_Enable(USART1);
}

void apm_led_init(void)
{
    GPIO_Config_T configStruct;

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);

    configStruct.pin = GPIO_PIN_2;
    configStruct.mode = GPIO_MODE_OUT_PP;
    configStruct.speed = GPIO_SPEED_50MHz;

    GPIO_Config(GPIOB, &configStruct);
    GPIOB->BC = GPIO_PIN_2;
}


void apm_led_toggle(void)
{
    GPIOB->ODATA ^= GPIO_PIN_2;
}

/**@} end of group GPIO_Toggle_Functions */
/**@} end of group GPIO_Toggle */
/**@} end of group Examples */
