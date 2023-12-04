/*
 * toggleLed.c
 *
 *  Created on: Nov 29, 2023
 *      Author: lmchi
 */
#include "toggleLed.h"

void blinky_led1(void){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
void blinky_led2(void){
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
void blinky_led3(void){
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}
void blinky_led4(void){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
void blinky_led5(void){
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}
void blinky_led6(void){
	HAL_GPIO_TogglePin(LED6_GPIO_Port, LED6_Pin);
}

