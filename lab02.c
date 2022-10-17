/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

void print_student_id_task(void *pvParameter)
{
	for( ;; )
	{
		printf("1915834\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS );
	}
	 vTaskDelete ( NULL ) ;
}

void press_button_task(void *pvParameter)
{
	int count_debound=0;
	bool wait=false;
	for( ;; )
	{
		gpio_set_direction(GPIO_NUM_18, GPIO_MODE_INPUT);
		gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLUP_ONLY);
		if(wait==false){
			if (gpio_get_level(GPIO_NUM_18) == 0) {
				wait=true;
				count_debound++;
			}
		} else {
			count_debound++;
			if(count_debound==15){
				if(gpio_get_level(GPIO_NUM_18) == 0){
					printf("ESP32\n");
				}
				count_debound=0;
				wait=false;
			}
		}
			vTaskDelay(10 / portTICK_PERIOD_MS );
	}
	vTaskDelete ( NULL ) ;
}

void app_main(void)
{
    xTaskCreate(&print_student_id_task, "print_student_id_task", 2048, NULL, 3, NULL);
    xTaskCreate(&press_button_task, "press_button_task", 2048, NULL, 5, NULL);
}
