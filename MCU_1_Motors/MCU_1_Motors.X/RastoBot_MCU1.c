#include "RastoBot_MCU1.h"
/* GLOBALS */

ECP_Message motorsMessage;
Rarray sendPacket;

Rarray recvPacket;
ECP_Message recvMessage;

static Stepper steppers[MCU1_STEPPERS];

/* STATIC FUNCTIONS ***********************************************************/
static void MCU1_DoTasks(void);
static void MCU1_DoMessageAction(ECP_Message * msg);

/* TASKS */
// This function should run all tasks
static void MCU1_TaskCheckForNewReceivedData(void);
static void MCU1_TaskMotorControl(void);

/******************************************************************************/


/******************************************************************************/

/* Init function */
void MCU1_Init(void)
{
    RarrayCreate(&sendPacket, RARRAY_SIZE_MAX);
    RarrayCreate(&recvPacket, RARRAY_SIZE_MAX);
    PWM_Init();
    UART_Init();
    Stepper_Init(&steppers[0], STEPPER_RIGHT_WHEEL, STEPPER_FULL_STEP, STEPPER_CW);
    Stepper_Init(&steppers[1], STEPPER_LEFT_WHEEL, STEPPER_FULL_STEP, STEPPER_CCW);
    Stepper_Init(&steppers[2], STEPPER_LEVELING, STEPPER_FULL_STEP, STEPPER_CW);
}
uint16_t loopCounter = 0;
static void MCU1_DoTasks(void)
{
    if (loopCounter % MCU1_MOTOR_CONTROL_EVERY == 0)
        MCU1_TaskMotorControl();
    if (loopCounter % MCU1_CHECK_NEW_MESSAGES_EVERY == 0)
        MCU1_TaskCheckForNewReceivedData();
}

// Main MCU loop - should be called every 10ms
void MCU1_Loop(void)
{
    MCU1_DoTasks();
    loopCounter++;
}

void MCU1_SetMainMotorSpeed(uint8_t speed)
{
    PWM_SetDuty(speed);
}

Stepper * MCU1_GetStepperByHwId(uint8_t id)
{
    if (id<MCU1_STEPPERS)
    {
        return &steppers[id];
    }
    return 0;
}
/* Steppers */
void MCU1_SetStepperDirection(Stepper * stepper, StepperDirection dir)
{
    Stepper_ChangeDirection(stepper, dir);
}
void MCU1_SetStepperSpeed(Stepper * stepper, uint16_t speed)
{
    Stepper_ChangeSpeed(stepper, speed);
}
void MCU1_SetStepperStepMode(Stepper * stepper, StepperStepMode mode)
{
    Stepper_ChangeDirection(stepper, mode);
}
void MCU1_SetStepperEnable(Stepper * stepper)
{
    Stepper_Enable(stepper);
}
void MCU1_SetStepperDisable(Stepper * stepper)
{
    Stepper_Disable(stepper);
}

/* Limit switches */
_Bool MCU1_GetLimitSwitchUP(void)
{
    return LIMIT_SWITCH_UP_PORT;
}
_Bool MCU1_GetLimitSwitchDOWN(void)
{
    return LIMIT_SWITCH_BOTTOM_PORT;
}


/***********************************************************************/
/* TASKS - functions which are called only from loop to do basic tasks */
/* WARNING: Do not invoke this functions somewhere else */

static void MCU1_TaskCheckForNewReceivedData(void)
{
    if (!uartNewDataFlag) // proceed only if new data was received
        return;
    if (ECP_FindECPPacket(&uartBuffer, &recvPacket) == 0) // packet found
    {
        ECP_DecodeRarray(&recvMessage, &recvPacket);
        MCU1_DoMessageAction(&recvMessage);
    }
    uartNewDataFlag = 0;
}

static void MCU1_TaskMotorControl(void)
{
//    Stepper_Step(STEPPER_RIGHT_WHEEL);
//    Stepper_Step(STEPPER_LEFT_WHEEL);
}

/* MESSAGE ACTION*/
static void MCU1_DoMessageAction(ECP_Message * msg)
{
    if (msg->command == ECP_COMMAND_SENSORS_SET)
    {
        switch (msg->subCommand)
        {
            default: break;
        }
    }
}