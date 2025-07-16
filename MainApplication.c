/*
 * MainApplication.c
 *
 *  Created on: Nov 23, 2018
 *      Author: Omar Hosny
 */

#include "libs/STD_TYPES.h"
#include "libs/Registers.h"
#include "utils/BIT_LIB.h"
#include "DIO_driver/DIO_int.h"
#include "UltraSonic_driver/UltraSonic_int.h"
#include "Timer1_driver/Timer1_int.h"
#include "Extint_driver/Extint_int.h"
#include "LCD_driver/LCD_int.h"
#include "Timer0_driver/Timer0_int.h"
#include "MotorDriver_driver/MotorDriver_int.h"
#include "DecisionMaker.h"
#include "RTOS/RTOS.h"
#include "avr/delay.h"
#define  F_CPU 12000000

u16 device1Val=0,device2Val=0,device3Val=0;
u8 metalVal;
void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void Task5(void);

void main(void)
{
	DIO_voidInit();
	Timer0_voidInit();
	Timer1_voidInit();
	Extint_voidInit();
	UltraSonic_voidInit();
	MotorDriver_voidInit();
	createTask(0, 600, 0, Task1);
	createTask(4, 600, 1, Task2);
	createTask(8, 600, 2, Task3);
	createTask(11, 3, 3, Task4);
	createTask(12,2,4,Task5);
	startSchedular();
	while(1)
	{

	}

}

void Task1(void)
{
	UltraSonic_u8Trigger(UltraSonic_enuDevice1);
}

void Task2(void)
{
	UltraSonic_u8Trigger(UltraSonic_enuDevice2);
}

void Task3(void)
{
	UltraSonic_u8Trigger(UltraSonic_enuDevice3);
}

void Task4(void)
{
	UltraSonic_u8GetVal(UltraSonic_enuDevice1,&device1Val, Centimeter);
	UltraSonic_u8GetVal(UltraSonic_enuDevice2,&device2Val, Centimeter);
	UltraSonic_u8GetVal(UltraSonic_enuDevice3,&device3Val, Centimeter);
	MakeUltraSonicDecision(device1Val, device3Val, device2Val);

}
void Task5(void)
{
	DIO_u8GetPinValue(DIO_enuPin16,&metalVal);
	MakeMotorDecision(metalVal);
}

