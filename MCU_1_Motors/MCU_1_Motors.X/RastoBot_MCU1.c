#include "RastoBot_MCU1.h"
/* GLOBALS */

ECP_Message motorsMessage;
Rarray sendPacket;

Rarray recvPacket;
ECP_Message recvMessage;

/* STATIC FUNCTIONS ***********************************************************/
static void MCU1_DoTasks(void);
static void MCU1_DoMessageAction(ECP_Message * msg);

/* TASKS */
// This function should run all tasks

/******************************************************************************/


/******************************************************************************/

/* Init function */
void MCU1_Init(void)
{
    RarrayCreate(&sendPacket, RARRAY_SIZE_MAX);
    RarrayCreate(&recvPacket, RARRAY_SIZE_MAX);
    PWM_Init();
    Stepper_Init(STEPPER_RIGHT_WHEEL, STEPPER_FULL_STEP, STEPPER_CW);
    Stepper_Init(STEPPER_LEFT_WHEEL, STEPPER_FULL_STEP, STEPPER_CCW);
    //Stepper_Init(STEPPER_LEVELING, STEPPER_FULL_STEP, STEPPER_CW);
}
uint16_t loopCounter = 0;
static void MCU1_DoTasks(void)
{
    Stepper_Step(STEPPER_RIGHT_WHEEL);
    Stepper_Step(STEPPER_LEFT_WHEEL);
}

// Main MCU loop - should be called every 10ms
void MCU1_Loop(void)
{
    MCU1_DoTasks();
    loopCounter++;
}
