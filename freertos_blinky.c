 /* @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"


/* Sets up system hardware */
static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();
Board_Buttons_Init();

/* Initial LED0 state is off */
Board_LED_Set(0, false);
Board_LED_Set(1, false);
Board_LED_Set(2, false);

}


static const char *vLEDTask1 = "task1";
static const char *vLEDTask2 = "task2";
static const char *vLEDTask3 = "task3";



static void vLEDTask(void *pvParameters)
{
	puts("tick");
		char *LEDSet1;
		char *LEDSet2;
		char *LEDSet3;
		LEDSet1 = (char*) pvParameters;
		LEDSet2 = (char*) pvParameters;
		LEDSet3 = (char*) pvParameters;



		portTickType xLastWakeTime;
		unsigned int  xFrequency= 1000;
		xLastWakeTime = xTaskGetTickCount ();


while (1)
      {

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		Board_LED_Set(2,true); //blue on
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		Board_LED_Set(2,false); //blue off
		vTaskDelayUntil(&xLastWakeTime, xFrequency);



		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		Board_LED_Set(1,true); //green on
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		Board_LED_Set(1,false); //green off
		vTaskDelayUntil(&xLastWakeTime, xFrequency);


		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		Board_LED_Set(0,true); //red on
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		Board_LED_Set(0,false); //red off
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	  }
}


//*****Driver Code*****//

int main(void)
{
prvSetupHardware();

/* LED1 toggle thread */
xTaskCreate(vLEDTask, "task1",configMINIMAL_STACK_SIZE, (void*)vLEDTask1, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);
/* LED2 toggle thread */
xTaskCreate(vLEDTask, "task2",configMINIMAL_STACK_SIZE, (void*)vLEDTask2 , (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);
/* LED3 toggle thread */
xTaskCreate(vLEDTask, "task3",configMINIMAL_STACK_SIZE, (void*)vLEDTask3, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

/* Start the scheduler */
vTaskStartScheduler();

/* Should never arrive here */
return 1;
}


/**
 * @}
 */
