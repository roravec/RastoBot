#include "RastoBot.h"

ECP_Message *   RastoBot_Encode_Sensors(ECP_Message * out, MCU_0_Sensors * sensors)
{
    out->command = ECP_COMMAND_SENSORS_STATUS;
    out->subCommand = 0;
    out->data[0] = (uint8_t)(sensors->batteryVoltage>>8);
    out->data[1] = (uint8_t)sensors->batteryVoltage;
    out->data[2] = (uint8_t)(sensors->externalVoltage>>8);
    out->data[3] = (uint8_t)sensors->externalVoltage;
    out->data[4] = (uint8_t)sensors->temperatures[0];
    out->data[5] = (uint8_t)sensors->temperatures[1];
    out->data[6] = (uint8_t)sensors->temperatures[2];
    out->data[7] = (uint8_t)sensors->temperatures[3];
    out->data[8] = (uint8_t)sensors->humidities[0];
    out->data[9] = (uint8_t)sensors->humidities[1];
    out->data[10] = (uint8_t)sensors->humidities[2];
    out->data[11] = (uint8_t)sensors->humidities[3];
    out->data[12] = (uint8_t)(sensors->currentSensors[0]>>8);
    out->data[13] = (uint8_t)sensors->currentSensors[0];
    out->data[14] = (uint8_t)(sensors->currentSensors[1]>>8);
    out->data[15] = (uint8_t)sensors->currentSensors[1];
    out->data[16] = (uint8_t)(sensors->currentSensors[2]>>8);
    out->data[17] = (uint8_t)sensors->currentSensors[2];
    out->data[18] = (uint8_t)(sensors->currentSensors[3]>>8);
    out->data[19] = (uint8_t)sensors->currentSensors[3];
    out->data[20] = (uint8_t)(sensors->rainSensor>>8);
    out->data[21] = (uint8_t)sensors->rainSensor;
    out->data[22] = (uint8_t)(sensors->lightSensor>>8);
    out->data[23] = (uint8_t)sensors->lightSensor;

    out->data[24] = 0;
    out->data[24] = sensors->powerOutputs[0] | 
            (sensors->powerOutputs[1] << 1) |
            (sensors->powerOutputs[2] << 2) |
            (sensors->powerOutputs[3] << 3) |
            (sensors->powerOutputs[4] << 4);
    
    out->data[25] = 0;
    out->data[25] = sensors->externalInputDetected | 
            (sensors->buzzer << 1) |
            (sensors->tiltSensor << 2) |
            (sensors->chargingEnabled << 3) |
            (sensors->fanManualControl << 4);
    
    out->dlc = ECP_COMMAND_SENSORS_STATUS_DLC;
    return out;
}
MCU_0_Sensors * RastoBot_Decode_Sensors(MCU_0_Sensors * sensorsOut, ECP_Message * in)
{
    sensorsOut->batteryVoltage = in->data[1] | (in->data[0] << 8);
    sensorsOut->externalVoltage = in->data[3] | (in->data[2] << 8);
    sensorsOut->temperatures[0] = in->data[4];
    sensorsOut->temperatures[1] = in->data[5];
    sensorsOut->temperatures[2] = in->data[6];
    sensorsOut->temperatures[3] = in->data[7];
    sensorsOut->humidities[0] = in->data[8];
    sensorsOut->humidities[1] = in->data[9];
    sensorsOut->humidities[2] = in->data[10];
    sensorsOut->humidities[3] = in->data[11];
    
    sensorsOut->currentSensors[0] = in->data[13] | (in->data[12] << 8);
    sensorsOut->currentSensors[1] = in->data[15] | (in->data[14] << 8);
    sensorsOut->currentSensors[2] = in->data[17] | (in->data[16] << 8);
    sensorsOut->currentSensors[3] = in->data[19] | (in->data[18] << 8);
    
    sensorsOut->rainSensor = in->data[21] | (in->data[20] << 8);
    sensorsOut->lightSensor = in->data[23] | (in->data[22] << 8);
    
    sensorsOut->powerOutputs[0] = (_Bool)in->data[24];
    sensorsOut->powerOutputs[1] = (_Bool)(in->data[24] >> 1);
    sensorsOut->powerOutputs[2] = (_Bool)(in->data[24] >> 2);
    sensorsOut->powerOutputs[3] = (_Bool)(in->data[24] >> 3);
    sensorsOut->powerOutputs[4] = (_Bool)(in->data[24] >> 4);
    
    sensorsOut->externalInputDetected = (_Bool)in->data[25];
    sensorsOut->buzzer = (_Bool)(in->data[25] >> 1);
    sensorsOut->tiltSensor = (_Bool)(in->data[25] >> 2);
    sensorsOut->chargingEnabled = (_Bool)(in->data[25] >> 3);
    sensorsOut->fanManualControl = (_Bool)(in->data[25] >> 4);
    return sensorsOut;
}

ECP_Message *   RastoBot_Encode_Motors(ECP_Message * out, MCU_1_Motors * motors)
{
    out->command = ECP_COMMAND_MOTORS_STATUS;
    out->subCommand = 0;
    
    out->data[0] = (uint8_t)(motors->mainMotorSpeed);
    
    out->data[1] = (uint8_t)(motors->levelingPosition>>8);
    out->data[2] = (uint8_t)motors->levelingPosition;
    
    out->data[3] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[4] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[5] = (uint8_t)motors->stepperSpeed[0];
    
    out->data[6] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[7] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[8] = (uint8_t)motors->stepperSpeed[0];
    
    out->data[9] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[10] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[11] = (uint8_t)motors->stepperSpeed[0];
    
    out->dlc = ECP_COMMAND_MOTORS_STATUS_DLC;
    return out;
}
MCU_1_Motors * RastoBot_Decode_Motors(MCU_1_Motors * motorsOut, ECP_Message * in)
{
    motorsOut->mainMotorSpeed = in->data[0];
    motorsOut->levelingPosition = in->data[2] | (in->data[1] << 8);
    
    motorsOut->stepperEnabled[0] = (_Bool)in->data[3];
    motorsOut->stepperDirection[0] = (_Bool)(in->data[3] >> 1);
    motorsOut->stepperStepMode[0] = (_Bool)(in->data[3] >> 2);
    motorsOut->stepperOperMode[0] = (_Bool)(in->data[3] >> 4);
    motorsOut->stepperSpeed[0] = in->data[5] | (in->data[4] << 8);
    
    motorsOut->stepperEnabled[1] = (_Bool)in->data[6];
    motorsOut->stepperDirection[1] = (_Bool)(in->data[6] >> 1);
    motorsOut->stepperStepMode[1] = (_Bool)(in->data[6] >> 2);
    motorsOut->stepperOperMode[1] = (_Bool)(in->data[6] >> 4);
    motorsOut->stepperSpeed[1] = in->data[8] | (in->data[7] << 8);
    
    motorsOut->stepperEnabled[2] = (_Bool)in->data[9];
    motorsOut->stepperDirection[2] = (_Bool)(in->data[9] >> 1);
    motorsOut->stepperStepMode[2] = (_Bool)(in->data[9] >> 2);
    motorsOut->stepperOperMode[2] = (_Bool)(in->data[9] >> 4);
    motorsOut->stepperSpeed[2] = in->data[11] | (in->data[10] << 8);
    
    return motorsOut;
}

ECP_Message * RastoBot_Encode_WheelsMotorControl(ECP_Message * out, MCU_1_WheelsMotorControl * wheelsControl)
{
    out->command = ECP_COMMAND_MOTORS_SET;
    out->subCommand = 200;
    
    out->data[0] = (wheelsControl->stepperEnabled[0]) | 
            (wheelsControl->stepperDirection[0] << 1) | 
            (wheelsControl->stepperStepMode[0] << 2) | 
            (wheelsControl->stepperOperMode[0] << 4);
    out->data[1] = (wheelsControl->stepperEnabled[1]) | 
            (wheelsControl->stepperDirection[1] << 1) | 
            (wheelsControl->stepperStepMode[1] << 2) | 
            (wheelsControl->stepperOperMode[1] << 4);
    
    out->data[2] = (uint8_t)(wheelsControl->stepperSpeed[0]>>8);
    out->data[3] = (uint8_t)wheelsControl->stepperSpeed[0];
    out->data[4] = (uint8_t)(wheelsControl->stepperSpeed[1]>>8);
    out->data[5] = (uint8_t)wheelsControl->stepperSpeed[1];
    
    out->data[6] = (uint8_t)(wheelsControl->stepperSteps[0]>>24);
    out->data[7] = (uint8_t)(wheelsControl->stepperSteps[0]>>16);
    out->data[8] = (uint8_t)(wheelsControl->stepperSteps[0]>>8);
    out->data[9] = (uint8_t)wheelsControl->stepperSteps[0];
    
    out->data[10] = (uint8_t)(wheelsControl->stepperSteps[1]>>24);
    out->data[11] = (uint8_t)(wheelsControl->stepperSteps[1]>>16);
    out->data[12] = (uint8_t)(wheelsControl->stepperSteps[1]>>8);
    out->data[13] = (uint8_t)wheelsControl->stepperSteps[1];
    
    out->dlc = ECP_COMMAND_WHEELS_SET_DLC;
    
    return out;
}

MCU_1_WheelsMotorControl * RastoBot_Decode_WheelsMotorControl(MCU_1_WheelsMotorControl * wheelsControl, ECP_Message * in)
{
    wheelsControl->stepperEnabled[0] = (_Bool)in->data[0];
    wheelsControl->stepperDirection[0] = (_Bool)(in->data[0] >> 1);
    wheelsControl->stepperStepMode[0] = (_Bool)(in->data[0] >> 2);
    wheelsControl->stepperOperMode[0] = (_Bool)(in->data[0] >> 4);
    
    wheelsControl->stepperEnabled[1] = (_Bool)in->data[1];
    wheelsControl->stepperDirection[1] = (_Bool)(in->data[1] >> 1);
    wheelsControl->stepperStepMode[1] = (_Bool)(in->data[1] >> 2);
    wheelsControl->stepperOperMode[1] = (_Bool)(in->data[1] >> 4);
    
    
    wheelsControl->stepperSpeed[0] = in->data[3] | (in->data[2] << 8);
    wheelsControl->stepperSpeed[1] = in->data[5] | (in->data[4] << 8);
    
    wheelsControl->stepperSteps[0] = in->data[9] | (in->data[8] << 8) | (in->data[7] << 16) | (in->data[6] << 24);
    wheelsControl->stepperSteps[1] = in->data[13] | (in->data[12] << 8) | (in->data[11] << 16) | (in->data[10] << 24);
    
    return wheelsControl;
}