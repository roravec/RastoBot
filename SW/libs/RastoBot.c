#include "RastoBot.h"
/******************************************************************************/
/* MCU0 Messages **************************************************************/
/******************************************************************************/
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
    uint8_t index = 0;
    if (in->subCommand == 0 || in->subCommand == 1)
    {
        index = 0;
        if (in->subCommand == 0) index = 0;
        sensorsOut->batteryVoltage = in->data[index+1] | (in->data[index+0] << 8);
        sensorsOut->externalVoltage = in->data[index+3] | (in->data[index+2] << 8);
        sensorsOut->temperatures[0] = in->data[index+4];
        sensorsOut->temperatures[1] = in->data[index+5];
        sensorsOut->temperatures[2] = in->data[index+6];
        sensorsOut->temperatures[3] = in->data[index+7];
    }
    if (in->subCommand == 0 || in->subCommand == 3)
    {
        index = 0;
        if (in->subCommand == 0) index = 12;
        sensorsOut->currentSensors[0] = in->data[index+1] | (in->data[index+0] << 8);
        sensorsOut->currentSensors[1] = in->data[index+3] | (in->data[index+2] << 8);
        sensorsOut->currentSensors[2] = in->data[index+5] | (in->data[index+4] << 8);
        sensorsOut->currentSensors[3] = in->data[index+7] | (in->data[index+6] << 8);
    }
    
    if (in->subCommand == 0 || in->subCommand == 2)
    {
        index = 0;
        if (in->subCommand == 0) index = 8;
        sensorsOut->humidities[0] = in->data[index+0];
        sensorsOut->humidities[1] = in->data[index+1];
        sensorsOut->humidities[2] = in->data[index+2];
        sensorsOut->humidities[3] = in->data[index+3];
        if (in->subCommand == 0) index = 16;
        sensorsOut->rainSensor = in->data[index+5] | (in->data[index+4] << 8);
        sensorsOut->lightSensor = in->data[index+7] | (in->data[index+6] << 8);
    }
    if (in->subCommand == 0 || in->subCommand == 4)
    {
        index = 0;
        if (in->subCommand == 0) index = 24;
        sensorsOut->powerOutputs[0] = (_Bool)in->data[index+0];
        sensorsOut->powerOutputs[1] = (_Bool)(in->data[index+0] >> 1);
        sensorsOut->powerOutputs[2] = (_Bool)(in->data[index+0] >> 2);
        sensorsOut->powerOutputs[3] = (_Bool)(in->data[index+0] >> 3);
        sensorsOut->powerOutputs[4] = (_Bool)(in->data[index+0] >> 4);

        sensorsOut->externalInputDetected = (_Bool)in->data[index+1];
        sensorsOut->buzzer = (_Bool)(in->data[index+1] >> 1);
        sensorsOut->tiltSensor = (_Bool)(in->data[index+1] >> 2);
        sensorsOut->chargingEnabled = (_Bool)(in->data[index+1] >> 3);
        sensorsOut->fanManualControl = (_Bool)(in->data[index+1] >> 4);
    }
    return sensorsOut;
}

ECP_Message *   RastoBot_Encode_Sensors_1(ECP_Message * out, MCU_0_Sensors * sensors)
{
    out->command = ECP_COMMAND_SENSORS_STATUS;
    out->subCommand = 1;
    out->data[0] = (uint8_t)(sensors->batteryVoltage>>8);
    out->data[1] = (uint8_t)sensors->batteryVoltage;
    out->data[2] = (uint8_t)(sensors->externalVoltage>>8);
    out->data[3] = (uint8_t)sensors->externalVoltage;
    out->data[4] = (uint8_t)sensors->temperatures[0];
    out->data[5] = (uint8_t)sensors->temperatures[1];
    out->data[6] = (uint8_t)sensors->temperatures[2];
    out->data[7] = (uint8_t)sensors->temperatures[3];
    
    out->dlc = 8;
    return out;
}
ECP_Message *   RastoBot_Encode_Sensors_2(ECP_Message * out, MCU_0_Sensors * sensors)
{
    out->command = ECP_COMMAND_SENSORS_STATUS;
    out->subCommand = 2;
    out->data[0] = (uint8_t)sensors->humidities[0];
    out->data[1] = (uint8_t)sensors->humidities[1];
    out->data[2] = (uint8_t)sensors->humidities[2];
    out->data[3] = (uint8_t)sensors->humidities[3];
    out->data[4] = (uint8_t)(sensors->rainSensor>>8);
    out->data[5] = (uint8_t)sensors->rainSensor;
    out->data[6] = (uint8_t)(sensors->lightSensor>>8);
    out->data[7] = (uint8_t)sensors->lightSensor;

    out->dlc = 8;
    return out;
}
ECP_Message *   RastoBot_Encode_Sensors_3(ECP_Message * out, MCU_0_Sensors * sensors)
{
    out->command = ECP_COMMAND_SENSORS_STATUS;
    out->subCommand = 3;

    out->data[0] = (uint8_t)(sensors->currentSensors[0]>>8);
    out->data[1] = (uint8_t)sensors->currentSensors[0];
    out->data[2] = (uint8_t)(sensors->currentSensors[1]>>8);
    out->data[3] = (uint8_t)sensors->currentSensors[1];
    out->data[4] = (uint8_t)(sensors->currentSensors[2]>>8);
    out->data[5] = (uint8_t)sensors->currentSensors[2];
    out->data[6] = (uint8_t)(sensors->currentSensors[3]>>8);
    out->data[7] = (uint8_t)sensors->currentSensors[3];
    
    out->dlc = 8;
    return out;
}
ECP_Message *   RastoBot_Encode_Sensors_4(ECP_Message * out, MCU_0_Sensors * sensors)
{
    out->command = ECP_COMMAND_SENSORS_STATUS;
    out->subCommand = 4;

    out->data[0] = 0;
    out->data[0] = sensors->powerOutputs[0] | 
            (sensors->powerOutputs[1] << 1) |
            (sensors->powerOutputs[2] << 2) |
            (sensors->powerOutputs[3] << 3) |
            (sensors->powerOutputs[4] << 4);
    
    out->data[1] = 0;
    out->data[1] = sensors->externalInputDetected | 
            (sensors->buzzer << 1) |
            (sensors->tiltSensor << 2) |
            (sensors->chargingEnabled << 3) |
            (sensors->fanManualControl << 4);
    
    out->dlc = 2;
    return out;
}

/******************************************************************************/
/* MCU1 Messages **************************************************************/
/******************************************************************************/
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
ECP_Message *   RastoBot_Encode_Motors_1(ECP_Message * out, MCU_1_Motors * motors)
{
    out->command = ECP_COMMAND_MOTORS_STATUS;
    out->subCommand = 1;
    
    out->data[0] = (uint8_t)(motors->mainMotorSpeed);
    
    out->data[1] = (uint8_t)(motors->levelingPosition>>8);
    out->data[2] = (uint8_t)motors->levelingPosition;
    
    out->data[3] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[4] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[5] = (uint8_t)motors->stepperSpeed[0];
    
    out->dlc = 6;
    return out;
}
ECP_Message *   RastoBot_Encode_Motors_2(ECP_Message * out, MCU_1_Motors * motors)
{
    out->command = ECP_COMMAND_MOTORS_STATUS;
    out->subCommand = 2;
    
    out->data[1] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[2] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[3] = (uint8_t)motors->stepperSpeed[0];
    
    out->data[4] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[5] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[6] = (uint8_t)motors->stepperSpeed[0];
    
    out->dlc = 7;
    return out;
}

MCU_1_Motors * RastoBot_Decode_Motors(MCU_1_Motors * motorsOut, ECP_Message * in)
{
    uint8_t index = 0;
    if (in->subCommand == 0 || in->subCommand == 1)
    {
        index = 0;
        if (in->subCommand == 0) index = 0;
        motorsOut->mainMotorSpeed = in->data[0];
        motorsOut->levelingPosition = in->data[2] | (in->data[1] << 8);

        motorsOut->stepperEnabled[0] = (_Bool)in->data[3];
        motorsOut->stepperDirection[0] = (_Bool)(in->data[3] >> 1);
        motorsOut->stepperStepMode[0] = (_Bool)(in->data[3] >> 2);
        motorsOut->stepperOperMode[0] = (_Bool)(in->data[3] >> 4);
        motorsOut->stepperSpeed[0] = in->data[5] | (in->data[4] << 8);
    }
    if (in->subCommand == 0 || in->subCommand == 2)
    {
        if (in->subCommand == 0) index = 6;
        motorsOut->stepperEnabled[1] = (_Bool)in->data[index+0];
        motorsOut->stepperDirection[1] = (_Bool)(in->data[index+0] >> 1);
        motorsOut->stepperStepMode[1] = (_Bool)(in->data[index+0] >> 2);
        motorsOut->stepperOperMode[1] = (_Bool)(in->data[index+0] >> 4);
        motorsOut->stepperSpeed[1] = in->data[index+2] | (in->data[index+1] << 8);

        motorsOut->stepperEnabled[2] = (_Bool)in->data[index+3];
        motorsOut->stepperDirection[2] = (_Bool)(in->data[index+3] >> 1);
        motorsOut->stepperStepMode[2] = (_Bool)(in->data[index+3] >> 2);
        motorsOut->stepperOperMode[2] = (_Bool)(in->data[index+3] >> 4);
        motorsOut->stepperSpeed[2] = in->data[index+5] | (in->data[index+4] << 8);
    }
    
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

    out->dlc = 6;
    
    return out;
}
ECP_Message * RastoBot_Encode_WheelsMotorSteps(ECP_Message * out, MCU_1_WheelsMotorControl * wheelsControl)
{
    out->command = ECP_COMMAND_MOTORS_SET;
    out->subCommand = 201;
    /* Steps */
    
    out->data[0] = (uint8_t)(wheelsControl->stepperSteps[0]>>24);
    out->data[1] = (uint8_t)(wheelsControl->stepperSteps[0]>>16);
    out->data[2] = (uint8_t)(wheelsControl->stepperSteps[0]>>8);
    out->data[3] = (uint8_t)wheelsControl->stepperSteps[0];
    
    out->data[4] = (uint8_t)(wheelsControl->stepperSteps[1]>>24);
    out->data[5] = (uint8_t)(wheelsControl->stepperSteps[1]>>16);
    out->data[6] = (uint8_t)(wheelsControl->stepperSteps[1]>>8);
    out->data[7] = (uint8_t)wheelsControl->stepperSteps[1];
    
    out->dlc = 8;
    
    return out;
}

MCU_1_WheelsMotorControl * RastoBot_Decode_WheelsMotorControl(MCU_1_WheelsMotorControl * wheelsControl, ECP_Message * in)
{
    // SubCommand 200
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
    
    return wheelsControl;
}
MCU_1_WheelsMotorControl * RastoBot_Decode_WheelsMotorSteps(MCU_1_WheelsMotorControl * wheelsControl, ECP_Message * in)
{
    // SubCommand 201
    wheelsControl->stepperSteps[0] = in->data[3] | (in->data[2] << 8) | (in->data[1] << 16) | (in->data[0] << 24);
    wheelsControl->stepperSteps[1] = in->data[7] | (in->data[6] << 8) | (in->data[5] << 16) | (in->data[4] << 24);
    
    return wheelsControl;
}

/******************************************************************************/
/* MCU2 Messages **************************************************************/
/******************************************************************************/

ECP_Message * RastoBot_Encode_Gyro(ECP_Message * out, MCU_2_GyroData * data)
{
    out->command = ECP_COMMAND_GYRO_STATUS;
    out->subCommand = 201;
    
    out->data[0] = (uint8_t)(data->magnetX>>8);
    out->data[1] = (uint8_t)data->magnetX;
    out->data[2] = (uint8_t)(data->magnetY>>8);
    out->data[3] = (uint8_t)data->magnetY;
    out->data[4] = (uint8_t)(data->magnetZ>>8);
    out->data[5] = (uint8_t)data->magnetZ;
    out->data[6] = (uint8_t)(data->accelX>>8);
    out->data[7] = (uint8_t)data->accelX;
    out->data[8] = (uint8_t)(data->accelY>>8);
    out->data[9] = (uint8_t)data->accelY;
    out->data[10] = (uint8_t)(data->accelZ>>8);
    out->data[11] = (uint8_t)data->accelZ;
    out->data[12] = (uint8_t)(data->gyroX>>8);
    out->data[13] = (uint8_t)data->gyroX;
    out->data[14] = (uint8_t)(data->gyroY>>8);
    out->data[15] = (uint8_t)data->gyroY;
    out->data[16] = (uint8_t)(data->gyroZ>>8);
    out->data[17] = (uint8_t)data->gyroZ;
    out->data[18] = (uint8_t)(data->azimuth>>8);
    out->data[19] = (uint8_t)data->azimuth;
    out->data[20] = (uint8_t)(data->temperature>>8);
    out->data[21] = (uint8_t)data->temperature;
    out->data[22] = (uint8_t)(data->perimeterWire>>8);
    out->data[23] = (uint8_t)data->perimeterWire;
    
    out->dlc = 24;
    
    return out;
}
MCU_2_GyroData * RastoBot_Decode_Gyro(MCU_2_GyroData * gyro, ECP_Message * in)
{
    // SubCommand 201
    gyro->magnetX =         in->data[1] | (in->data[0] << 8);
    gyro->magnetY =         in->data[3] | (in->data[2] << 8);
    gyro->magnetZ =         in->data[5] | (in->data[4] << 8);
    gyro->accelX =          in->data[7] | (in->data[6] << 8);
    gyro->accelY =          in->data[9] | (in->data[8] << 8);
    gyro->accelZ =          in->data[11] | (in->data[10] << 8);
    gyro->gyroX =           in->data[13] | (in->data[12] << 8);
    gyro->gyroY =           in->data[15] | (in->data[14] << 8);
    gyro->gyroZ =           in->data[17] | (in->data[16] << 8);
    gyro->azimuth =         in->data[19] | (in->data[18] << 8);
    gyro->temperature =     in->data[21] | (in->data[20] << 8);
    gyro->perimeterWire =   in->data[23] | (in->data[22] << 8);
    
    return gyro;
}

ECP_Message * RastoBot_Encode_Lidar(ECP_Message * out, MCU_2_LidarData * data)
{
    out->command = ECP_COMMAND_LIDAR_STATUS;
    out->subCommand = 201;
    
    out->data[0] = (uint8_t)(data->angleIndex>>8);
    out->data[1] = (uint8_t)data->angleIndex;
    out->data[2] = (uint8_t)(data->rpm>>8);
    out->data[3] = (uint8_t)data->rpm;
    out->data[4] = (uint8_t)(data->intensity[0]>>8);
    out->data[5] = (uint8_t)data->intensity[0];
    out->data[6] = (uint8_t)(data->intensity[1]>>8);
    out->data[7] = (uint8_t)data->intensity[1];
    out->data[8] = (uint8_t)(data->intensity[2]>>8);
    out->data[9] = (uint8_t)data->intensity[2];
    out->data[10] = (uint8_t)(data->intensity[3]>>8);
    out->data[11] = (uint8_t)data->intensity[3];
    out->data[12] = (uint8_t)(data->intensity[4]>>8);
    out->data[13] = (uint8_t)data->intensity[4];
    out->data[14] = (uint8_t)(data->intensity[5]>>8);
    out->data[15] = (uint8_t)data->intensity[5];
    out->data[16] = (uint8_t)(data->distance[0]>>8);
    out->data[17] = (uint8_t)data->distance[0];
    out->data[18] = (uint8_t)(data->distance[1]>>8);
    out->data[19] = (uint8_t)data->distance[1];
    out->data[20] = (uint8_t)(data->distance[2]>>8);
    out->data[21] = (uint8_t)data->distance[2];
    out->data[22] = (uint8_t)(data->distance[3]>>8);
    out->data[23] = (uint8_t)data->distance[3];
    out->data[24] = (uint8_t)(data->distance[4]>>8);
    out->data[25] = (uint8_t)data->distance[4];
    out->data[26] = (uint8_t)(data->distance[5]>>8);
    out->data[27] = (uint8_t)data->distance[5];
    
    out->dlc = 28;
    
    return out;
}
MCU_2_LidarData * RastoBot_Decode_Lidar(MCU_2_LidarData * lidar, ECP_Message * in)
{
    // SubCommand 201
    lidar->angleIndex =         in->data[1] | (in->data[0] << 8);
    lidar->rpm =                in->data[3] | (in->data[2] << 8);
    lidar->intensity[0] =       in->data[5] | (in->data[4] << 8);
    lidar->intensity[1] =       in->data[7] | (in->data[6] << 8);
    lidar->intensity[2] =       in->data[9] | (in->data[8] << 8);
    lidar->intensity[3] =       in->data[11] | (in->data[10] << 8);
    lidar->intensity[4] =       in->data[13] | (in->data[12] << 8);
    lidar->intensity[5] =       in->data[15] | (in->data[14] << 8);
    lidar->distance[0] =        in->data[17] | (in->data[16] << 8);
    lidar->distance[1] =        in->data[19] | (in->data[18] << 8);
    lidar->distance[2] =        in->data[21] | (in->data[20] << 8);
    lidar->distance[3] =        in->data[23] | (in->data[22] << 8);
    lidar->distance[4] =        in->data[25] | (in->data[24] << 8);
    lidar->distance[5] =        in->data[27] | (in->data[26] << 8);
    
    return lidar;
}

ECP_Message * RastoBot_Encode_Position(
        ECP_Message * out, 
        MCU_2_LidarData * lidar, 
        MCU_2_GyroData * gyro, 
        MCU_2_GPSData * gps)
{
    out->command = ECP_COMMAND_POSITION_STATUS;
    out->subCommand = 201;
    
    // Lidar
    out->data[0] = (uint8_t)(lidar->angleIndex>>8);
    out->data[1] = (uint8_t)lidar->angleIndex;
    out->data[2] = (uint8_t)(lidar->rpm>>8);
    out->data[3] = (uint8_t)lidar->rpm;
    out->data[4] = (uint8_t)(lidar->intensity[0]>>8);
    out->data[5] = (uint8_t)lidar->intensity[0];
    out->data[6] = (uint8_t)(lidar->intensity[1]>>8);
    out->data[7] = (uint8_t)lidar->intensity[1];
    out->data[8] = (uint8_t)(lidar->intensity[2]>>8);
    out->data[9] = (uint8_t)lidar->intensity[2];
    out->data[10] = (uint8_t)(lidar->intensity[3]>>8);
    out->data[11] = (uint8_t)lidar->intensity[3];
    out->data[12] = (uint8_t)(lidar->intensity[4]>>8);
    out->data[13] = (uint8_t)lidar->intensity[4];
    out->data[14] = (uint8_t)(lidar->intensity[5]>>8);
    out->data[15] = (uint8_t)lidar->intensity[5];
    out->data[16] = (uint8_t)(lidar->distance[0]>>8);
    out->data[17] = (uint8_t)lidar->distance[0];
    out->data[18] = (uint8_t)(lidar->distance[1]>>8);
    out->data[19] = (uint8_t)lidar->distance[1];
    out->data[20] = (uint8_t)(lidar->distance[2]>>8);
    out->data[21] = (uint8_t)lidar->distance[2];
    out->data[22] = (uint8_t)(lidar->distance[3]>>8);
    out->data[23] = (uint8_t)lidar->distance[3];
    out->data[24] = (uint8_t)(lidar->distance[4]>>8);
    out->data[25] = (uint8_t)lidar->distance[4];
    out->data[26] = (uint8_t)(lidar->distance[5]>>8);
    out->data[27] = (uint8_t)lidar->distance[5];
    
    // Gyro
    out->data[28] = (uint8_t)(gyro->magnetX>>8);
    out->data[29] = (uint8_t)gyro->magnetX;
    out->data[30] = (uint8_t)(gyro->magnetY>>8);
    out->data[31] = (uint8_t)gyro->magnetY;
    out->data[32] = (uint8_t)(gyro->magnetZ>>8);
    out->data[33] = (uint8_t)gyro->magnetZ;
    out->data[34] = (uint8_t)(gyro->accelX>>8);
    out->data[35] = (uint8_t)gyro->accelX;
    out->data[36] = (uint8_t)(gyro->accelY>>8);
    out->data[37] = (uint8_t)gyro->accelY;
    out->data[38] = (uint8_t)(gyro->accelZ>>8);
    out->data[39] = (uint8_t)gyro->accelZ;
    out->data[40] = (uint8_t)(gyro->gyroX>>8);
    out->data[41] = (uint8_t)gyro->gyroX;
    out->data[42] = (uint8_t)(gyro->gyroY>>8);
    out->data[43] = (uint8_t)gyro->gyroY;
    out->data[44] = (uint8_t)(gyro->gyroZ>>8);
    out->data[45] = (uint8_t)gyro->gyroZ;
    out->data[46] = (uint8_t)(gyro->azimuth>>8);
    out->data[47] = (uint8_t)gyro->azimuth;
    out->data[48] = (uint8_t)(gyro->temperature>>8);
    out->data[49] = (uint8_t)gyro->temperature;
    out->data[50] = (uint8_t)(gyro->perimeterWire>>8);
    out->data[51] = (uint8_t)gyro->perimeterWire;
    
    // GPS
    uint8_t * latitude;
    latitude = (uint8_t*)&gps->latitude;
    uint8_t * longitude;
    longitude = (uint8_t*)&gps->longitude;
    
    out->data[52] = *latitude++;
    out->data[53] = *latitude++;
    out->data[54] = *latitude++;
    out->data[55] = *latitude;
    out->data[56] = *longitude++;
    out->data[57] = *longitude++;
    out->data[58] = *longitude++;
    out->data[59] = *longitude;
    out->data[60] = gps->latDir | (gps->lonDir << 1) | (gps->satellites << 2);
    out->data[61] = gps->seconds;
    out->data[62] = gps->minutes;
    out->data[63] = gps->hours;
    out->dlc = 64;
    
//        // Lidar
//    out->data[0] = 0;
//    out->data[1] = 0;
//    out->data[2] = 0;
//    out->data[3] = 0;
//    out->data[4] = 0;
//    out->data[5] = 0;
//    out->data[6] = 0;
//    out->data[7] = 0;
//    out->data[8] = 0;
//    out->data[9] = 0;
//    out->data[10] = 0;
//    out->data[11] = 0;
//    out->data[12] = 0;
//    out->data[13] = 0;
//    out->data[14] = 0;
//    out->data[15] = 0;
//    out->data[16] = 0;
//    out->data[17] = 0;
//    out->data[18] = 0;
//    out->data[19] = 0;
//    out->data[20] = 0;
//    out->data[21] = 0;
//    out->data[22] = 0;
//    out->data[23] = 0;
//    out->data[24] = 0;
//    out->data[25] = 0;
//    out->data[26] = 0;
//    out->data[27] = 0;
//    out->data[28] = 0;
//    out->data[29] = 0;
//    out->data[30] = 0;
//    out->data[31] = 0;
//    out->data[32] = 0;
//    out->data[33] = 0;
//    out->data[34] = 0;
//    out->data[35] = 0;
//    out->data[36] = 0;
//    out->data[37] = 0;
//    out->data[38] = 0;
//    out->data[39] = 0;
//    out->data[40] = 0;
//    out->data[41] = 0;
//    out->data[42] = 0;
//    out->data[43] = 0;
//    out->data[44] = 0;
//    out->data[45] = 0;
//    out->data[46] = 0;
//    out->data[47] = 0;
//    out->data[48] = 0;
//    out->data[49] = 0;
//    out->data[50] = 0;
//    out->data[51] = 0;
//    out->data[52] = 0;
//    out->data[53] = 0;
//    out->data[54] = 0;
//    out->data[55] = 0;
//    out->data[56] = 0;
//    out->data[57] = 0;
//    out->data[58] = 0;
//    out->data[59] = 0;
//    out->data[60] = 0;
//    out->data[61] = 0;
//    out->data[62] = 0;
//    out->data[63] = 0;
//    out->dlc = 64;
    
    return out;
}

void RastoBot_Decode_Position(
        MCU_2_LidarData * lidar, 
        MCU_2_GyroData * gyro, 
        MCU_2_GPSData * gps, 
        ECP_Message * in)
{
    // Lidar
    lidar->angleIndex =         in->data[1] | (in->data[0] << 8);
    lidar->rpm =                in->data[3] | (in->data[2] << 8);
    lidar->intensity[0] =       in->data[5] | (in->data[4] << 8);
    lidar->intensity[1] =       in->data[7] | (in->data[6] << 8);
    lidar->intensity[2] =       in->data[9] | (in->data[8] << 8);
    lidar->intensity[3] =       in->data[11] | (in->data[10] << 8);
    lidar->intensity[4] =       in->data[13] | (in->data[12] << 8);
    lidar->intensity[5] =       in->data[15] | (in->data[14] << 8);
    lidar->distance[0] =        in->data[17] | (in->data[16] << 8);
    lidar->distance[1] =        in->data[19] | (in->data[18] << 8);
    lidar->distance[2] =        in->data[21] | (in->data[20] << 8);
    lidar->distance[3] =        in->data[23] | (in->data[22] << 8);
    lidar->distance[4] =        in->data[25] | (in->data[24] << 8);
    lidar->distance[5] =        in->data[27] | (in->data[26] << 8);
    
    // Gyro
    gyro->magnetX =             in->data[29] | (in->data[28] << 8);
    gyro->magnetY =             in->data[31] | (in->data[30] << 8);
    gyro->magnetZ =             in->data[33] | (in->data[32] << 8);
    gyro->accelX =              in->data[35] | (in->data[34] << 8);
    gyro->accelY =              in->data[37] | (in->data[36] << 8);
    gyro->accelZ =              in->data[39] | (in->data[38] << 8);
    gyro->gyroX =               in->data[41] | (in->data[40] << 8);
    gyro->gyroY =               in->data[43] | (in->data[42] << 8);
    gyro->gyroZ =               in->data[45] | (in->data[44] << 8);
    gyro->azimuth =             in->data[47] | (in->data[46] << 8);
    gyro->temperature =         in->data[49] | (in->data[48] << 8);
    gyro->perimeterWire =       in->data[51] | (in->data[50] << 8);
     // GPS
    uint8_t latitude[4];
    uint8_t longitude[4];
    latitude[0] = in->data[52];
    latitude[1] = in->data[53];
    latitude[2] = in->data[54];
    latitude[3] = in->data[55];
    longitude[0] = in->data[56];
    longitude[1] = in->data[57];
    longitude[2] = in->data[58];
    longitude[3] = in->data[59];
    
    gps->satellites = (uint8_t)(in->data[60] >> 2);
    gps->latDir = (uint8_t)(in->data[60] & 1);
    gps->lonDir = (uint8_t)(in->data[60] >> 1) & 1;
    gps->seconds = in->data[61];
    gps->minutes = in->data[62];
    gps->hours = in->data[63];
}

ECP_Message *   RastoBot_Encode_SensorsMotors(ECP_Message * out, MCU_0_Sensors * sensors, MCU_1_Motors * motors)
{
    out->command = ECP_COMMAND_SENSORSMOTORS_STATUS;
    out->subCommand = 0;
    out->data[0] = (uint8_t)(sensors->batteryVoltage>>8);
    out->data[1] = (uint8_t)sensors->batteryVoltage;
    out->data[2] = (uint8_t)(sensors->externalVoltage>>8);
    out->data[3] = (uint8_t)sensors->externalVoltage;
    out->data[4] = (int8_t)sensors->temperatures[0];
    out->data[5] = (int8_t)sensors->temperatures[1];
    out->data[6] = (int8_t)sensors->temperatures[2];
    out->data[7] = (int8_t)sensors->temperatures[3];
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
    
    out->data[26] = (uint8_t)(motors->mainMotorSpeed);
    
    out->data[27] = (uint8_t)(motors->levelingPosition>>8);
    out->data[28] = (uint8_t)motors->levelingPosition;
    
    out->data[29] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[30] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[31] = (uint8_t)motors->stepperSpeed[0];
    
    out->data[32] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[33] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[34] = (uint8_t)motors->stepperSpeed[0];
    
    out->data[35] = (motors->stepperEnabled[0]) | 
            (motors->stepperDirection[0] << 1) | 
            (motors->stepperStepMode[0] << 2) | 
            (motors->stepperOperMode[0] << 4);
    out->data[36] = (uint8_t)(motors->stepperSpeed[0]>>8);
    out->data[37] = (uint8_t)motors->stepperSpeed[0];
    
    out->dlc = 38;
    return out;
}

void RastoBot_Decode_SensorsMotors(MCU_0_Sensors * sensorsOut, MCU_1_Motors * motorsOut, ECP_Message * in)
{
    uint8_t index = 0;
    // sensors
    if (in->subCommand == 0) index = 0;
    sensorsOut->batteryVoltage = in->data[index+1] | (in->data[index+0] << 8);
    sensorsOut->externalVoltage = in->data[index+3] | (in->data[index+2] << 8);
    sensorsOut->temperatures[0] = in->data[index+4];
    sensorsOut->temperatures[1] = in->data[index+5];
    sensorsOut->temperatures[2] = in->data[index+6];
    sensorsOut->temperatures[3] = in->data[index+7];
    
    if (in->subCommand == 0) index = 8;
    sensorsOut->humidities[0] = in->data[index+0];
    sensorsOut->humidities[1] = in->data[index+1];
    sensorsOut->humidities[2] = in->data[index+2];
    sensorsOut->humidities[3] = in->data[index+3];

    if (in->subCommand == 0) index = 12;
    sensorsOut->currentSensors[0] = in->data[index+1] | (in->data[index+0] << 8);
    sensorsOut->currentSensors[1] = in->data[index+3] | (in->data[index+2] << 8);
    sensorsOut->currentSensors[2] = in->data[index+5] | (in->data[index+4] << 8);
    sensorsOut->currentSensors[3] = in->data[index+7] | (in->data[index+6] << 8);

    if (in->subCommand == 0) index = 16;
    sensorsOut->rainSensor = in->data[index+5] | (in->data[index+4] << 8);
    sensorsOut->lightSensor = in->data[index+7] | (in->data[index+6] << 8);

    if (in->subCommand == 0) index = 24;
    sensorsOut->powerOutputs[0] = (_Bool)in->data[index+0];
    sensorsOut->powerOutputs[1] = (_Bool)(in->data[index+0] >> 1);
    sensorsOut->powerOutputs[2] = (_Bool)(in->data[index+0] >> 2);
    sensorsOut->powerOutputs[3] = (_Bool)(in->data[index+0] >> 3);
    sensorsOut->powerOutputs[4] = (_Bool)(in->data[index+0] >> 4);

    sensorsOut->externalInputDetected = (_Bool)in->data[index+1];
    sensorsOut->buzzer = (_Bool)(in->data[index+1] >> 1);
    sensorsOut->tiltSensor = (_Bool)(in->data[index+1] >> 2);
    sensorsOut->chargingEnabled = (_Bool)(in->data[index+1] >> 3);
    sensorsOut->fanManualControl = (_Bool)(in->data[index+1] >> 4);

    // motors
    if (in->subCommand == 0) index = 26;
    motorsOut->mainMotorSpeed = in->data[index+0];
    motorsOut->levelingPosition = in->data[index+2] | (in->data[index+1] << 8);

    motorsOut->stepperEnabled[0] = (_Bool)in->data[index+3];
    motorsOut->stepperDirection[0] = (_Bool)(in->data[index+3] >> 1);
    motorsOut->stepperStepMode[0] = (_Bool)(in->data[index+3] >> 2);
    motorsOut->stepperOperMode[0] = (_Bool)(in->data[index+3] >> 4);
    motorsOut->stepperSpeed[0] = in->data[index+5] | (in->data[index+4] << 8);

    if (in->subCommand == 0) index = 32;
    motorsOut->stepperEnabled[1] = (_Bool)in->data[index+0];
    motorsOut->stepperDirection[1] = (_Bool)(in->data[index+0] >> 1);
    motorsOut->stepperStepMode[1] = (_Bool)(in->data[index+0] >> 2);
    motorsOut->stepperOperMode[1] = (_Bool)(in->data[index+0] >> 4);
    motorsOut->stepperSpeed[1] = in->data[index+2] | (in->data[index+1] << 8);

    motorsOut->stepperEnabled[2] = (_Bool)in->data[index+3];
    motorsOut->stepperDirection[2] = (_Bool)(in->data[index+3] >> 1);
    motorsOut->stepperStepMode[2] = (_Bool)(in->data[index+3] >> 2);
    motorsOut->stepperOperMode[2] = (_Bool)(in->data[index+3] >> 4);
    motorsOut->stepperSpeed[2] = in->data[index+5] | (in->data[index+4] << 8);
}

void Lidar_ParseData(MCU_2_LidarData * lidarDataOut, uint8_t * data, uint8_t size)
{
    if (size < LIDAR_FIX_DATALOAD) return;
    
    lidarDataOut->angleIndex =  data[1];
    lidarDataOut->rpm =         (uint16_t)(data[2] | (data[3] << 8));
    
    lidarDataOut->intensity[0] = (uint16_t)(data[4] | (data[5] << 8));
    lidarDataOut->distance[0] =  (uint16_t)(data[6] | (data[7] << 8));
    lidarDataOut->intensity[1] = (uint16_t)(data[4] | (data[5] << 8));
    lidarDataOut->distance[1] =  (uint16_t)(data[6] | (data[7] << 8));
    lidarDataOut->intensity[2] = (uint16_t)(data[4] | (data[5] << 8));
    lidarDataOut->distance[2] =  (uint16_t)(data[6] | (data[7] << 8));
    lidarDataOut->intensity[3] = (uint16_t)(data[4] | (data[5] << 8));
    lidarDataOut->distance[3] =  (uint16_t)(data[6] | (data[7] << 8));
    lidarDataOut->intensity[4] = (uint16_t)(data[4] | (data[5] << 8));
    lidarDataOut->distance[4] =  (uint16_t)(data[6] | (data[7] << 8));
    lidarDataOut->intensity[5] = (uint16_t)(data[4] | (data[5] << 8));
    lidarDataOut->distance[5] =  (uint16_t)(data[6] | (data[7] << 8));
}