//
// Created by steve on 4/27/22.
//
#include <stdint.h>
#include <stdbool.h>
#include <printing_help.h>
#include <stdlib.h>
#include "stm32wbxx_hal.h"

// to poll for transfer complete
extern DMA_HandleTypeDef hdma_spi2_tx;


static void set_led_number_to_rgb(int32_t, int32_t i, int32_t i1, int32_t i2);

// args is guaranteed certain large size.
// guaranteed to be zero pointers to terminate arg list
uint8_t at_command_handler_led_write(uint8_t **args){

    #define NUM_ARGS 4
    if(args[NUM_ARGS - 1] == 0){
        log_debug_stringln("NEED 4 ARGS, FAIL");
        return 1;
    }

    int32_t led_num   = parse_num_arg(args[0]);
    int32_t led_r_val = parse_num_arg(args[1]);
    int32_t led_g_val = parse_num_arg(args[2]);
    int32_t led_b_val = parse_num_arg(args[3]);

    if(led_num > 10){
        log_debug_stringln("LED NUMBER MUST BE 0-8, FAIL");
        return 1;
    }

    if(led_r_val > 255 || led_g_val > 255 || led_b_val > 255 ){
        log_debug_stringln("LED RGB VALUES MUST BE 0-255, FAIL");
        return 2;
    }


    log_debug_stringln("LED COMMAND");
    set_led_number_to_rgb(led_num, led_r_val, led_g_val, led_b_val);
    return 0;
}

#include <stm32wbxx_ll_gpio.h>
#include "printing_help.h"
#include "i2c.h"
#include "trakid.h"
#include "spi.h"

static void set_led_number_to_rgb(int32_t led_num, int32_t led_r_val, int32_t led_g_val, int32_t led_b_val)
{
    static int init_already = 0;
    if(0 == init_already){
        // repeatedly initializing causes red blinks on LED 0

        init_already = 1;
        log_debug_stringln("INITIALIZING GPIO");
        MX_GPIO_Init();

        log_debug_stringln("Enable LED Power");
        LL_GPIO_SetOutputPin(x5V0_EN_GPIO_Port, x5V0_EN_Pin);

        log_debug_stringln("Initialize SPI DMA");
        MX_DMA_Init();

        MX_SPI2_Init();
    }

    log_debug_stringln("CLEAR LEDs");
    clear_LED_Array(1,1);
    while(HAL_DMA_STATE_BUSY == HAL_DMA_GetState(&hdma_spi2_tx)) {;}
    HAL_Delay(5);

    log_debug_stringln("SET TO VALUE");
    load_LED_Array(led_num, led_r_val, led_g_val, led_b_val);
    update_LED_Array();
    while(HAL_DMA_STATE_BUSY == HAL_DMA_GetState(&hdma_spi2_tx)) {;}
    HAL_Delay(5);
}

