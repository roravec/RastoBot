#include "RastoBot_MCU1.h"
/* GLOBALS */
MCU_1_Motors statusData;
MCU_1_WheelsMotorControl wheelsSetting;

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
void MCU1_LevelingReferenceRun(void)
{
}
void MCU1_LevelingGoToPosition(uint8_t position)
{
}
void MCU1_SetWheelSteppersByStruct()
{
    
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
            case 90: MCU1_SetMainMotorSpeed(msg->data[0]);
            case 0: MCU1_SetStepperDisable(0); break;
            case 10: MCU1_SetStepperDisable(1); break;
            case 20: MCU1_SetStepperDisable(2); break;
            case 1: MCU1_SetStepperEnable(0); break;
            case 11: MCU1_SetStepperEnable(1); break;
            case 21: MCU1_SetStepperEnable(2); break;
            
            case 2: MCU1_SetStepperDirection(0,STEPPER_CW); break;
            case 12: MCU1_SetStepperDirection(1,STEPPER_CW); break;
            case 22: MCU1_SetStepperDirection(2,STEPPER_CW); break;
            case 3: MCU1_SetStepperDirection(0,STEPPER_CCW); break;
            case 13: MCU1_SetStepperDirection(1,STEPPER_CCW); break;
            case 23: MCU1_SetStepperDirection(2,STEPPER_CCW); break;
            
            case 4: MCU1_SetStepperStepMode(0,STEPPER_FULL_STEP); break;
            case 14: MCU1_SetStepperStepMode(1,STEPPER_FULL_STEP); break;
            case 24: MCU1_SetStepperStepMode(2,STEPPER_FULL_STEP); break;
            case 5: MCU1_SetStepperStepMode(0,STEPPER_HALF_STEP); break;
            case 15: MCU1_SetStepperStepMode(1,STEPPER_HALF_STEP); break;
            case 25: MCU1_SetStepperStepMode(2,STEPPER_HALF_STEP); break;
            case 6: MCU1_SetStepperStepMode(0,STEPPER_QUARTER_STEP); break;
            case 16: MCU1_SetStepperStepMode(1,STEPPER_QUARTER_STEP); break;
            case 26: MCU1_SetStepperStepMode(2,STEPPER_QUARTER_STEP); break;
            case 7: MCU1_SetStepperStepMode(0,STEPPER_EIGHTH_STEP); break;
            case 17: MCU1_SetStepperStepMode(1,STEPPER_EIGHTH_STEP); break;
            case 27: MCU1_SetStepperStepMode(2,STEPPER_EIGHTH_STEP); break;
            
            case 8: MCU1_SetStepperOperMode(0,STEPPER_CONTINOUS); break;
            case 18: MCU1_SetStepperOperMode(1,STEPPER_CONTINOUS); break;
            case 28: MCU1_SetStepperOperMode(2,STEPPER_CONTINOUS); break;
            case 9: MCU1_SetStepperOperMode(0,STEPPER_STEPS_ON_DEMAND); break;
            case 19: MCU1_SetStepperOperMode(1,STEPPER_STEPS_ON_DEMAND); break;
            case 29: MCU1_SetStepperOperMode(2,STEPPER_STEPS_ON_DEMAND); break;
            
            case 100: MCU1_SetStepperStop(0); break;
            case 101: MCU1_SetStepperStop(1); break;
            case 102: MCU1_SetStepperStop(2); break;
            
            case 110: MCU1_SetStepperOperMode(0,STEPPER_CONTINOUS); break;
            case 111: MCU1_SetStepperOperMode(1,STEPPER_CONTINOUS); break;
            case 112: MCU1_SetStepperOperMode(2,STEPPER_CONTINOUS); break;
            
            case 120: MCU1_SetStepperSpeed(0,(msg->data[1]<<8|msg->data[0])); break;
            case 121: MCU1_SetStepperSpeed(1,(msg->data[1]<<8|msg->data[0])); break;
            case 122: MCU1_SetStepperSpeed(2,(msg->data[1]<<8|msg->data[0])); break;
            
            case 130: MCU1_SetStepperMakeSteps(0,(
                    msg->data[3]<<24 |
                    msg->data[2]<<16 |
                    msg->data[1]<<8  |
                    msg->data[0])); break;
            case 131: MCU1_SetStepperMakeSteps(1,(
                    msg->data[3]<<24 |
                    msg->data[2]<<16 |
                    msg->data[1]<<8  |
                    msg->data[0])); break;
            case 132: MCU1_SetStepperMakeSteps(2,(
                    msg->data[3]<<24 |
                    msg->data[2]<<16 |
                    msg->data[1]<<8  |
                    msg->data[0])); break;
            
            case 30: MCU1_LevelingReferenceRun(); break;
            case 31: MCU1_LevelingGoToPosition(msg->data[0]); break;
            
            case 200: RastoBot_Decode_WheelsMotorControl(&wheelsSetting,msg); 
                if (wheelsSetting.stepperEnabled[0]) MCU1_SetStepperEnable(0);
                else MCU1_SetStepperDisable(0);
                if (wheelsSetting.stepperEnabled[1]) MCU1_SetStepperEnable(1);
                else MCU1_SetStepperDisable(1);
                MCU1_SetStepperDirection(0,wheelsSetting.stepperDirection[0]);
                MCU1_SetStepperDirection(1,wheelsSetting.stepperDirection[1]);
                MCU1_SetStepperStepMode(0,wheelsSetting.stepperStepMode[0]);
                MCU1_SetStepperStepMode(1,wheelsSetting.stepperStepMode[1]);
                MCU1_SetStepperOperMode(0,wheelsSetting.stepperOperMode[0]);
                MCU1_SetStepperOperMode(1,wheelsSetting.stepperOperMode[1]);
                MCU1_SetStepperSpeed(0, wheelsSetting.stepperSpeed[0]);
                MCU1_SetStepperSpeed(1, wheelsSetting.stepperSpeed[1]);
                if (wheelsSetting.stepperSteps[0] > 0) MCU1_SetStepperMakeSteps(0, wheelsSetting.stepperSteps[0]);
                if (wheelsSetting.stepperSteps[1] > 0) MCU1_SetStepperMakeSteps(1, wheelsSetting.stepperSteps[1]);
                break;
            default: break;
        }
    }
}