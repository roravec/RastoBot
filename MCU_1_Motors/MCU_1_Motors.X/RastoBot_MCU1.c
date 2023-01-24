#include "RastoBot_MCU1.h"
/* GLOBALS */
MCU_1_Motors statusData;

uint8_t sendPacketArr[ECP_MAX_PACKET_LEN];
Rarray sendPacket;
ECP_Message sendMessage;

static Stepper steppers[MCU1_STEPPERS];

/* STATIC FUNCTIONS ***********************************************************/
static void MCU1_DoTasks(void);
static void MCU1_DoMessageAction(ECP_Message * msg);

/* TASKS */
// This function should run all tasks
static void MCU1_TaskMotorControl(void);
static void MCU1_TaskLogData(void);
static void MCU1_TaskSendStatusData(void);
static void MCU1_TaskCheckForNewReceivedData(void);

/******************************************************************************/


/******************************************************************************/

/* Init function */
void MCU1_Init(void)
{
    RarrayCreate(&sendPacket, sendPacketArr, ECP_MAX_PACKET_LEN);
    PWM_Init();
    UART_Init();
    Stepper_Init(&steppers[0], STEPPER_RIGHT_WHEEL,     STEPPER_QUARTER_STEP, STEPPER_CW);
    Stepper_Init(&steppers[1], STEPPER_LEFT_WHEEL,      STEPPER_QUARTER_STEP, STEPPER_CCW);
    Stepper_Init(&steppers[2], STEPPER_LEVELING,        STEPPER_QUARTER_STEP, STEPPER_CW);
    MCU1_SetStepperEnable(STEPPER_RIGHT_WHEEL);
    MCU1_SetStepperEnable(STEPPER_LEFT_WHEEL);
    MCU1_SetStepperEnable(STEPPER_LEVELING);
    
}
uint16_t loopCounter = 0;

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
/* Stepper motors */
void MCU1_SetStepperDirection(uint8_t stepperHwId, StepperDirection dir)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_ChangeDirection(stepper, dir);
    statusData.stepperDirection[stepperHwId] = dir;
}
void MCU1_SetStepperSpeed(uint8_t stepperHwId, uint16_t speed)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_ChangeSpeed(stepper, speed);
    statusData.stepperSpeed[stepperHwId] = speed;
}
void MCU1_SetStepperMakeSteps(uint8_t stepperHwId, uint32_t steps)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_MakeSteps(stepper, steps);
    //statusData.stepperStepsToMake[stepperHwId] = steps;
}
void MCU1_SetStepperStepMode(uint8_t stepperHwId, StepperStepMode mode)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_ChangeDirection(stepper, mode);
    statusData.stepperStepMode[stepperHwId] = mode;
}
void MCU1_SetStepperOperMode(uint8_t stepperHwId, StepperOperMode mode)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_ChangeOperMode(stepper, mode);
    statusData.stepperOperMode[stepperHwId] = mode;
}
void MCU1_SetStepperStop(uint8_t stepperHwId)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_Stop(stepper);
    statusData.stepperOperMode[stepperHwId] = stepper->opMode;
    //statusData.stepperStepsToMake[stepperHwId] = 0;
}
void MCU1_SetStepperEnable(uint8_t stepperHwId)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_Enable(stepper);
    statusData.stepperEnabled[stepperHwId] = 1;
}
void MCU1_SetStepperDisable(uint8_t stepperHwId)
{
    Stepper * stepper = MCU1_GetStepperByHwId(stepperHwId);
    Stepper_Disable(stepper);
    statusData.stepperEnabled[stepperHwId] = 0;
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

static void MCU1_DoTasks(void)
{
    if (loopCounter % MCU1_LOG_DATA_TO_STRUCT_EVERY == 0)
        MCU1_TaskLogData();
    if (loopCounter % MCU1_MOTOR_CONTROL_EVERY == 0)
        MCU1_TaskMotorControl();
    if (loopCounter % MCU1_CHECK_NEW_MESSAGES_EVERY == 0)
        MCU1_TaskCheckForNewReceivedData();
    if (loopCounter % MCU1_CHECK_NEW_MESSAGES_EVERY == 0)
        MCU1_TaskSendStatusData();
}

static void MCU1_TaskMotorControl(void)
{
    Stepper_Step(&steppers[STEPPER_LEFT_WHEEL]);
    Stepper_Step(&steppers[STEPPER_RIGHT_WHEEL]);
    Stepper_Step(&steppers[STEPPER_LEVELING]);
}

static void MCU1_TaskLogData(void)
{
}

static void MCU1_TaskSendStatusData(void)
{
    RastoBot_Encode_Motors(&sendMessage, &statusData);
    ECP_Encode(&sendMessage, &sendPacket);
    UART_WriteData(sendPacket.data, sendPacket.size);
}

static ECP_Message * msg;  // pointer to message to process
static void MCU1_TaskCheckForNewReceivedData(void)
{
    while ((msg = ECP_MessageDequeue()) != 0) // check if we have some message to process in queue
    {
        // a new message has been received and decoded. Let's process it...
        MCU1_DoMessageAction(msg);      // do requested action
        ECP_MarkMessageAsComplete(msg); // mark message as processed. It will free up space in queue.
    }
}

/* MESSAGE ACTION*/
static void MCU1_DoMessageAction(ECP_Message * msg)
{
    if (msg->command == ECP_COMMAND_MOTORS_SET)
    {
        switch (msg->subCommand)
        {
            default: break;
        }
    }
}