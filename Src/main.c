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

/** @addtogroup Examples
  @{
  */

/** @addtogroup GPIO_Toggle
  @{
  */

/** @defgroup GPIO_Toggle_Functions
  @{
  */

volatile uint32_t ticks = 0;

void fpu_enable(void);

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

    //fpu_enable();
    apm_led_init();

    //float result = 0.0f;

    while (1)
    {
        Delay(200);
        apm_led_toggle();

        //result = sc_math_dot(x, y, 2);
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
