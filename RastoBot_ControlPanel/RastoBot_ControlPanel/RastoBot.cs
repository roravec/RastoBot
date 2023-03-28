using ErmaCommProtocol;
using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace RastoBot_ControlPanel
{
    public class RastoBot
    {
        private const int CurrentSensorLimit = 70;

        public delegate void delMessageDecoded(uint command);
        public event delMessageDecoded? eventMessageDecoded = null;
        public const UInt16 fixedPacketSizeFromMCU3 = 72;
        public const UInt16 fixedDataSizeToMCU3 = 8;
        public byte[] defaultDataMCU3 = { 0, 0, 0, 0, 0, 0, 0, 0, };
        public enum MessageCommand {
            ECP_COMMAND_MOTORS_STATUS = 111,
            ECP_COMMAND_POSITION_STATUS = 124,
            ECP_COMMAND_SENSORSMOTORS_STATUS = 125,
            ECP_COMMAND_MAPUPDATE = 126,
            ECP_COMMAND_SENSORS_SET = 201,
            ECP_COMMAND_MOTORS_SET = 211,
            ECP_COMMAND_NAVIGATION_SET = 202
        };

        public enum ECP_COMMAND_SENSORS_SET
        {
            FAN_AUTO = 0,
            FAN_MANUAL = 1,
            TURN_ON_POWER_OUTPUT_0 = 10,
            TURN_ON_POWER_OUTPUT_1 = 11,
            TURN_ON_POWER_OUTPUT_2 = 12,
            TURN_ON_POWER_OUTPUT_3 = 13,
            TURN_ON_POWER_OUTPUT_4 = 14,
            TURN_OFF_POWER_OUTPUT_0 = 20,
            TURN_OFF_POWER_OUTPUT_1 = 21,
            TURN_OFF_POWER_OUTPUT_2 = 22,
            TURN_OFF_POWER_OUTPUT_3 = 23,
            TURN_OFF_POWER_OUTPUT_4 = 24,
            TURN_ON_LED_0 = 30,
            TURN_ON_LED_1 = 31,
            TURN_ON_LED_2 = 32,
            TURN_OFF_LED_0 = 40,
            TURN_OFF_LED_1 = 41,
            TURN_OFF_LED_2 = 42,
            TURN_ON_EXTERNAL_INPUT = 50,
            TURN_OFF_EXTERNAL_INPUT = 51,
            BUZZ_200MS = 100,
            BUZZ_400MS = 101,
            BUZZ_600MS = 102,
            BUZZ_800MS = 103,
            BUZZ_1000MS = 104,
            BUZZ_1500MS = 105
        };

        public enum ECP_COMMAND_MOTORS_SET
        {
            SET_MAIN_MOTOR_SPEED = 90,
            DISABLE_STEPPER_0 = 0,
            DISABLE_STEPPER_1 = 10,
            DISABLE_STEPPER_2 = 20,
            ENABLE_STEPPER_0 = 1,
            ENABLE_STEPPER_1 = 11,
            ENABLE_STEPPER_2 = 21,
            SET_DIRECTION_CW_0 = 2,
            SET_DIRECTION_CW_1 = 12,
            SET_DIRECTION_CW_2 = 22,
            SET_DIRECTION_CCW_0 = 3,
            SET_DIRECTION_CCW_1 = 13,
            SET_DIRECTION_CCW_2 = 23,
            SET_STEP_MODE_FULL_0 = 4,
            SET_STEP_MODE_FULL_1 = 14,
            SET_STEP_MODE_FULL_2 = 24,
            SET_STEP_MODE_HALF_0 = 5,
            SET_STEP_MODE_HALF_1 = 15,
            SET_STEP_MODE_HALF_2 = 25,
            SET_STEP_MODE_QUARTER_0 = 6,
            SET_STEP_MODE_QUARTER_1 = 16,
            SET_STEP_MODE_QUARTER_2 = 26,
            SET_STEP_MODE_EIGHTH_0 = 7,
            SET_STEP_MODE_EIGHTH_1 = 17,
            SET_STEP_MODE_EIGHTH_2 = 27,
            SET_OPER_MODE_CONTINOUS_0 = 8,
            SET_OPER_MODE_CONTINOUS_1 = 18,
            SET_OPER_MODE_CONTINOUS_2 = 28,
            SET_OPER_MODE_ON_DEMAND_0 = 9,
            SET_OPER_MODE_ON_DEMAND_1 = 19,
            SET_OPER_MODE_ON_DEMAND_2 = 29,
            STOP_STEPPER_0 = 100,
            STOP_STEPPER_1 = 101,
            STOP_STEPPER_2 = 102,
            SET_STEPPER_SPEED_0 = 120,
            SET_STEPPER_SPEED_1 = 121,
            SET_STEPPER_SPEED_2 = 122,
            MAKE_STEPS_0 = 130,
            MAKE_STEPS_1 = 131,
            MAKE_STEPS_2 = 132,
            MAKE_STEPS_WHEELS = 140,
            LEVELING_REFERENCE_RUN = 30,
            LEVELING_GO_TO = 31
        };

        public enum StepperDirection
        {
            CW=0, CCW=1
        };
        public enum StepperOperMode
        {
            Continous = 0, OnDemand = 1
        };
        public enum StepperStepMode
        {
            Full=0, Half, Quarter, Eighth
        };

        private SerialPortComm comPort = null;
        public MCU_0_Sensors sensors = new MCU_0_Sensors();
        public MCU_1_Motors motors = new MCU_1_Motors();
        public MCU_2_GyroData gyro = new MCU_2_GyroData();
        public MCU_2_GPSData gps = new MCU_2_GPSData();
        public MCU_2_LidarData lidar = new MCU_2_LidarData();

        private bool[] mcu0Leds = { false, false, false };
        private Form1 mainForm = null;

        public RastoBot(SerialPortComm comPort, Form1 iform1)
        {
            this.comPort = comPort;
            this.mainForm = iform1;
        }

        public void SerialMessageReceived(byte[] rawpacket, uint size)
        {
            ushort countPackets = (ushort)(size / fixedPacketSizeFromMCU3);
            var packets = rawpacket.Split((int)fixedPacketSizeFromMCU3);
            if (size < fixedPacketSizeFromMCU3) // invalid packet
                return;
            foreach (var packeta in packets)
            {
                var packet = packeta.ToArray<byte>();
                //byte[] packet = GetByteArray(text, (ushort)size);
                if (ErmaCommProtocol.ErmaCommProtocol.ECP_CheckPacketValidity(packet, (ushort)packet.Length) == ECP_PacketValidity.ECP_VALID)
                {
                    // packet is valid
                    ECP_Message msg = ErmaCommProtocol.ErmaCommProtocol.ECP_Decode(packet, (ushort)packet.Length);
                    if (msg != null)
                    {
                        // msg decoded correctly
                        MakeAction(msg);
                        if (eventMessageDecoded != null)
                            eventMessageDecoded(msg.command);
                    }
                }
            }
        }

        private void MakeAction(ECP_Message msg)
        {
            if (msg == null) { return; }
            switch (msg.command)
            {
                case (byte)MessageCommand.ECP_COMMAND_POSITION_STATUS:
                    RastoBot_Decode_Position(lidar, gyro, gps, msg);
                    lidar.UpdateLastTimeReceived();
                    gyro.UpdateLastTimeReceived();
                    gps.UpdateLastTimeReceived();
                    break;
                case (byte)MessageCommand.ECP_COMMAND_SENSORSMOTORS_STATUS:
                    RastoBot_Decode_SensorsMotors(sensors, motors, msg);
                    sensors.UpdateLastTimeReceived();
                    motors.UpdateLastTimeReceived();
                    break;
                case (byte)MessageCommand.ECP_COMMAND_MAPUPDATE:
                    break;
                default: break;
            }
        }

        private byte[] GetByteArray(string str, ushort size)
        {
            byte[] bytes = new byte[size];
            for (UInt16 i = 0; i < size; i++)
            {
                bytes[i] = (byte)str[i];
            }
            return bytes;
        }

        void RastoBot_Decode_SensorsMotors(MCU_0_Sensors sensorsOut, MCU_1_Motors motorsOut, ECP_Message msg)
        {
            byte index = 0;
            // sensors
            if (msg.subCommand == 0) index = 0;
            sensorsOut.batteryVoltage = (short)(msg.data[index + 1] | (msg.data[index + 0] << 8));
            sensorsOut.externalVoltage = (short)(msg.data[index + 3] | (msg.data[index + 2] << 8));
            sensorsOut.temperatures[0] = (sbyte)msg.data[index + 4];
            sensorsOut.temperatures[1] = (sbyte)msg.data[index + 5];
            sensorsOut.temperatures[2] = (sbyte)msg.data[index + 6];
            sensorsOut.temperatures[3] = (sbyte)msg.data[index + 7];

            if (msg.subCommand == 0) index = 8;
            sensorsOut.humidities[0] = msg.data[index + 0];
            sensorsOut.humidities[1] = msg.data[index + 1];
            sensorsOut.humidities[2] = msg.data[index + 2];
            sensorsOut.humidities[3] = msg.data[index + 3];

            if (msg.subCommand == 0) index = 12;
            sensorsOut.currentSensors[0] = (short)(msg.data[index + 1] | (msg.data[index + 0] << 8));
            sensorsOut.currentSensors[1] = (short)(msg.data[index + 3] | (msg.data[index + 2] << 8));
            sensorsOut.currentSensors[2] = (short)(msg.data[index + 5] | (msg.data[index + 4] << 8));
            sensorsOut.currentSensors[3] = (short)(msg.data[index + 7] | (msg.data[index + 6] << 8));

            if (msg.subCommand == 0) index = 16;
            sensorsOut.rainSensor = (ushort)(msg.data[index + 5] | (msg.data[index + 4] << 8));
            sensorsOut.lightSensor = (ushort)(msg.data[index + 7] | (msg.data[index + 6] << 8));

            if (msg.subCommand == 0) index = 24;
            sensorsOut.powerOutputs[0] = Convert.ToBoolean(msg.data[index + 0]);
            sensorsOut.powerOutputs[1] = Convert.ToBoolean(msg.data[index + 0] >> 1);
            sensorsOut.powerOutputs[2] = Convert.ToBoolean(msg.data[index + 0] >> 2);
            sensorsOut.powerOutputs[3] = Convert.ToBoolean(msg.data[index + 0] >> 3);
            sensorsOut.powerOutputs[4] = Convert.ToBoolean(msg.data[index + 0] >> 4);

            sensorsOut.externalInputDetected = Convert.ToBoolean(msg.data[index + 1]);
            sensorsOut.buzzer = Convert.ToBoolean(msg.data[index + 1] >> 1);
            sensorsOut.tiltSensor = Convert.ToBoolean(msg.data[index + 1] >> 2);
            sensorsOut.chargingEnabled = Convert.ToBoolean(msg.data[index + 1] >> 3);
            sensorsOut.fanManualControl = Convert.ToBoolean(msg.data[index + 1] >> 4);

            // motors
            if (msg.subCommand == 0) index = 26;
            motorsOut.mainMotorSpeed = msg.data[index + 0];
            motorsOut.levelingPosition = (ushort)(msg.data[index + 2] | (msg.data[index + 1] << 8));

            motorsOut.stepperEnabled[0] = Convert.ToBoolean(msg.data[index + 3]);
            motorsOut.stepperDirection[0] = Convert.ToBoolean(msg.data[index + 3] >> 1);
            motorsOut.stepperStepMode[0] = (byte)(msg.data[index + 3] >> 2);
            motorsOut.stepperOperMode[0] = (byte)(msg.data[index + 3] >> 4);
            motorsOut.stepperSpeed[0] = (ushort)(msg.data[index + 5] | (msg.data[index + 4] << 8));

            if (msg.subCommand == 0) index = 32;
            motorsOut.stepperEnabled[1] = Convert.ToBoolean(msg.data[index + 0]);
            motorsOut.stepperDirection[1] = Convert.ToBoolean(msg.data[index + 0] >> 1);
            motorsOut.stepperStepMode[1] = (byte)(msg.data[index + 0] >> 2);
            motorsOut.stepperOperMode[1] = (byte)(msg.data[index + 0] >> 4);
            motorsOut.stepperSpeed[1] = (ushort)(msg.data[index + 2] | (msg.data[index + 1] << 8));

            motorsOut.stepperEnabled[2] = Convert.ToBoolean(msg.data[index + 3]);
            motorsOut.stepperDirection[2] = Convert.ToBoolean(msg.data[index + 3] >> 1);
            motorsOut.stepperStepMode[2] = (byte)(msg.data[index + 3] >> 2);
            motorsOut.stepperOperMode[2] = (byte)(msg.data[index + 3] >> 4);
            motorsOut.stepperSpeed[2] = (ushort)(msg.data[index + 5] | (msg.data[index + 4] << 8));
        }

        void RastoBot_Decode_Position(
        MCU_2_LidarData lidar,
        MCU_2_GyroData gyro,
        MCU_2_GPSData gps,
        ECP_Message msg)
        {
            // Lidar
            lidar.angleIndex = (ushort)(msg.data[1] | (msg.data[0] << 8));
            lidar.rpm = (ushort)(msg.data[3] | (msg.data[2] << 8));
            lidar.intensity[0] = (ushort)(msg.data[5] | (msg.data[4] << 8));
            lidar.intensity[1] = (ushort)(msg.data[7] | (msg.data[6] << 8));
            lidar.intensity[2] = (ushort)(msg.data[9] | (msg.data[8] << 8));
            lidar.intensity[3] = (ushort)(msg.data[11] | (msg.data[10] << 8));
            lidar.intensity[4] = (ushort)(msg.data[13] | (msg.data[12] << 8));
            lidar.intensity[5] = (ushort)(msg.data[15] | (msg.data[14] << 8));
            lidar.distance[0] = (ushort)(msg.data[17] | (msg.data[16] << 8));
            lidar.distance[1] = (ushort)(msg.data[19] | (msg.data[18] << 8));
            lidar.distance[2] = (ushort)(msg.data[21] | (msg.data[20] << 8));
            lidar.distance[3] = (ushort)(msg.data[23] | (msg.data[22] << 8));
            lidar.distance[4] = (ushort)(msg.data[25] | (msg.data[24] << 8));
            lidar.distance[5] = (ushort)(msg.data[27] | (msg.data[26] << 8));

            // Gyro
            gyro.magnetX = (short)(msg.data[29] | (msg.data[28] << 8));
            gyro.magnetY = (short)(msg.data[31] | (msg.data[30] << 8));
            gyro.magnetZ = (short)(msg.data[33] | (msg.data[32] << 8));
            gyro.accelX = (short)(msg.data[35] | (msg.data[34] << 8));
            gyro.accelY = (short)(msg.data[37] | (msg.data[36] << 8));
            gyro.accelZ = (short)(msg.data[39] | (msg.data[38] << 8));
            gyro.gyroX = (short)(msg.data[41] | (msg.data[40] << 8));
            gyro.gyroY = (short)(msg.data[43] | (msg.data[42] << 8));
            gyro.gyroZ = (short)(msg.data[45] | (msg.data[44] << 8));
            gyro.azimuth = (short)(msg.data[47] | (msg.data[46] << 8));
            gyro.temperature = (short)(msg.data[49] | (msg.data[48] << 8));
            gyro.perimeterWire = (ushort)(msg.data[51] | (msg.data[50] << 8));
            // GPS
            byte[] latitude = new byte[4];
            byte[] longitude = new byte[4];
            latitude[0] = msg.data[52];
            latitude[1] = msg.data[53];
            latitude[2] = msg.data[54];
            latitude[3] = msg.data[55];
            longitude[0] = msg.data[56];
            longitude[1] = msg.data[57];
            longitude[2] = msg.data[58];
            longitude[3] = msg.data[59];

            gps.satellites = (byte)(msg.data[60] >> 2);
            gps.latDir = Convert.ToBoolean(msg.data[60] & 1);
            gps.lonDir = Convert.ToBoolean((msg.data[60] >> 1) & 1);
            gps.seconds = msg.data[61];
            gps.minutes = msg.data[62];
            gps.hours = msg.data[63];
        }

        public int GetCurrentValue(int currentFromSensor)
        {
            int middleValue = 512;
            int actualSensorValue = currentFromSensor - middleValue;
            int actualCurrent = (CurrentSensorLimit / middleValue) * actualSensorValue;
            return actualSensorValue;
        }

        public double GetVoltage(int sensorValue)
        {
            if (sensorValue == 0) return 0;
            // 467 = 15
            // 452 = 14.5
            // 436 = 14
            // 420 = 13.5
            // 408 = 13
            // 374 = 12

            double value  = 0.032 * sensorValue;
            return Math.Round(value, 1);
        }

        public void Task_SetMotorsInit(int stepperId)
        {
            Task_SetMotorsEnable(stepperId);
            Task_SetMotorsStepMode(stepperId, 3); // eighth
            Task_SetMotorsOperMode(stepperId, 1); // on demand
            Task_SetMotorsSpeed(stepperId, 1023); // 1023 full
        }
        public void Task_SetMotorsInitWheels()
        {
            Task_SetMotorsEnable(0);
            Task_SetMotorsStepMode(0,3); // eighth
            Task_SetMotorsOperMode(0,1); // on demand
            Task_SetMotorsDirection(0, 0); // CW
            Task_SetMotorsSpeed(0,1023); // 1023 full

            Task_SetMotorsEnable(1);
            Task_SetMotorsStepMode(1, 3); // eighth
            Task_SetMotorsOperMode(1, 1); // on demand
            Task_SetMotorsDirection(1, 1); // CW
            Task_SetMotorsSpeed(1, 1023); // 1023 full
        }
        public void Task_SetMotorsStop(int stepperId)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.STOP_STEPPER_0;
            if (stepperId == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.STOP_STEPPER_1;
            if (stepperId == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.STOP_STEPPER_2;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsEnable(int stepperId)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.ENABLE_STEPPER_0;
            if (stepperId == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.ENABLE_STEPPER_1;
            if (stepperId == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.ENABLE_STEPPER_2;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsDisable(int stepperId)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.DISABLE_STEPPER_0;
            if (stepperId == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.DISABLE_STEPPER_1;
            if (stepperId == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.DISABLE_STEPPER_2;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsStepMode(int stepperId, int stepMode)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_FULL_0;
            if (stepperId == 0)
            {
                if (stepMode == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_FULL_0;
                else if (stepMode == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_HALF_0;
                else if (stepMode == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_QUARTER_0;
                else if (stepMode == 3) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_EIGHTH_0;
            }
            if (stepperId == 1)
            {
                if (stepMode == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_FULL_1;
                else if (stepMode == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_HALF_1;
                else if (stepMode == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_QUARTER_1;
                else if (stepMode == 3) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_EIGHTH_1;
            }
            if (stepperId == 2)
            {
                if (stepMode == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_FULL_2;
                else if (stepMode == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_HALF_2;
                else if (stepMode == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_QUARTER_2;
                else if (stepMode == 3) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEP_MODE_EIGHTH_2;
            }
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsOperMode(int stepperId, int operMode)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_CONTINOUS_0;
            if (stepperId == 0)
            {
                if (operMode == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_CONTINOUS_0;
                else if (operMode == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_ON_DEMAND_0;
            }
            if (stepperId == 1)
            {
                if (operMode == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_CONTINOUS_1;
                else if (operMode == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_ON_DEMAND_1;
            }
            if (stepperId == 2)
            {
                if (operMode == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_CONTINOUS_2;
                else if (operMode == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_OPER_MODE_ON_DEMAND_2;
            }
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsDirection(int stepperId, int direction)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CW_0;
            if (stepperId == 0)
            {
                if (direction == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CW_0;
                else if (direction == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CCW_0;
            }
            if (stepperId == 1)
            {
                if (direction == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CW_1;
                else if (direction == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CCW_1;
            }
            if (stepperId == 2)
            {
                if (direction == 0) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CW_2;
                else if (direction == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_DIRECTION_CCW_2;
            }
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsSpeed(int stepperId, int speed)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEPPER_SPEED_0;
            if (stepperId == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEPPER_SPEED_1;
            if (stepperId == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_STEPPER_SPEED_2;
            var msg = CreateMessage(command, subCommand, Generate8ByteArray((byte)speed, (byte)(speed>>8)), 2);
            SendMessage(msg, comPort);
        }
        public void Task_SetMotorsStepsToMake(int stepperId, int steps)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.MAKE_STEPS_0;
            if (stepperId == 1) subCommand = (byte)ECP_COMMAND_MOTORS_SET.MAKE_STEPS_1;
            if (stepperId == 2) subCommand = (byte)ECP_COMMAND_MOTORS_SET.MAKE_STEPS_2;
            var msg = CreateMessage(command, subCommand, Generate8ByteArray((byte)steps, (byte)(steps >> 8), (byte)(steps >> 16), (byte)(steps >> 24)), 4);
            SendMessage(msg, comPort);
        }
        public void Task_SetWheelsStepsToMake(int steps)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.MAKE_STEPS_WHEELS;
            var msg = CreateMessage(command, subCommand, Generate8ByteArray((byte)steps, (byte)(steps >> 8), (byte)(steps >> 16), (byte)(steps >> 24)), 4);
            SendMessage(msg, comPort);
        }
        /**************************************************************/
        public void Task_SetMainMotorSpeed(int speed)
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_MOTORS_SET;
            byte subCommand = (byte)ECP_COMMAND_MOTORS_SET.SET_MAIN_MOTOR_SPEED;
            var msg = CreateMessage(command, subCommand, Generate8ByteArray((byte)speed), 1);
            SendMessage(msg, comPort);
        }
        /**************************************************************/
        public void Task_BeepBuzzer()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.BUZZ_400MS;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }

        public void Task_ToggleFanManualControl()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.FAN_AUTO;
            if (mainForm.GetCheckBoxManualControl().Checked)
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.FAN_MANUAL;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleFan0()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_POWER_OUTPUT_0;
            if (!mainForm.GetCheckBoxFan0().Checked)
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_POWER_OUTPUT_0;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleFan1()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_POWER_OUTPUT_1;
            if (!mainForm.GetCheckBoxFan1().Checked)
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_POWER_OUTPUT_1;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleFan2()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_POWER_OUTPUT_2;
            if (!mainForm.GetCheckBoxFan2().Checked)
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_POWER_OUTPUT_2;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleFan3()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_POWER_OUTPUT_3;
            if (!mainForm.GetCheckBoxFan3().Checked)
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_POWER_OUTPUT_3;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleEmergencyLight()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_POWER_OUTPUT_4;
            if (mainForm.GetCheckBoxEmergencyLight().Checked)
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_POWER_OUTPUT_4;
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleMCU0LED0()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_LED_0;
            if (mcu0Leds[0])
            {
                mcu0Leds[0] = false;
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_LED_0;
            }
            else
            {
                mcu0Leds[0] = true;
            }
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleMCU0LED1()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_LED_1;
            if (mcu0Leds[1])
            {
                mcu0Leds[1] = false;
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_LED_1;
            }
            else
            {
                mcu0Leds[1] = true;
            }
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }
        public void Task_ToggleMCU0LED2()
        {
            byte command = (byte)MessageCommand.ECP_COMMAND_SENSORS_SET;
            byte subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_ON_LED_2;
            if (mcu0Leds[2])
            {
                mcu0Leds[2] = false;
                subCommand = (byte)ECP_COMMAND_SENSORS_SET.TURN_OFF_LED_2;
            }
            else
            {
                mcu0Leds[2] = true;
            }
            var msg = CreateMessage(command, subCommand, defaultDataMCU3, 0);
            SendMessage(msg, comPort);
        }

        public ECP_Message CreateMessage(byte command, byte subCommand, byte[] data, byte dlc)
        {
            return ErmaCommProtocol.ErmaCommProtocol.CreateMessage(command, subCommand, data, dlc);
        }
        public void SendMessage(ECP_Message msg, SerialPortComm comPort)
        {
            if (comPort == null) { return; }
            var packet = ErmaCommProtocol.ErmaCommProtocol.ECP_EncodeExtended(msg, (byte)fixedDataSizeToMCU3);
            comPort.SendData(packet, (uint)packet.Length);
        }

        public static byte[] Generate8ByteArray(byte B0=0, byte B1 = 0, byte B2 = 0, byte B3 = 0, byte B4 = 0, byte B5 = 0, byte B6 = 0, byte B7 = 0)
        {
            byte[] bytes= new byte[8];
            bytes[0] = B0;
            bytes[1] = B1;
            bytes[2] = B2;
            bytes[3] = B3;
            bytes[4] = B4;
            bytes[5] = B5;
            bytes[6] = B6;
            bytes[7] = B7;
            return bytes;
        }
    }
    public class MCU_0_Sensors : CyclicDataPacket
    {
        public Int16 batteryVoltage;
        public Int16 externalVoltage;
        public bool externalInputDetected;
        public sbyte[] temperatures = new sbyte[4];
        public byte[] humidities = new byte[4];
        public Int16[] currentSensors = new Int16[4];
        public bool[] powerOutputs = new bool[5];
        public bool buzzer;
        public bool tiltSensor;
        public UInt16 rainSensor;
        public UInt16 lightSensor;
        public bool chargingEnabled;
        public bool fanManualControl;
    }

    public class MCU_1_Motors : CyclicDataPacket
    {
        public byte mainMotorSpeed; // percent
        public bool[] stepperEnabled =      new bool[3];
        public bool[] stepperDirection =    new bool[3];
        public byte[] stepperStepMode =     new byte[3];
        public byte[] stepperOperMode =     new byte[3];
        public UInt16[] stepperSpeed =      new UInt16[3];
        public UInt16 levelingPosition;
    }

    public class MCU_2_GyroData : CyclicDataPacket
    {
        public Int16 magnetX;
        public Int16 magnetY;
        public Int16 magnetZ;
        public Int16 accelX;
        public Int16 accelY;
        public Int16 accelZ;
        public Int16 gyroX;
        public Int16 gyroY;
        public Int16 gyroZ;
        public Int16 azimuth;
        public Int16 temperature;
        public UInt16 perimeterWire;
    }

    public class MCU_2_GPSData : CyclicDataPacket
    {
        public const UInt16 ECP_GPS_DATA_STRING_MAX_SIZE = 200;

        public byte seconds;
        public byte minutes;
        public byte hours;
        public byte day;
        public byte month;
        public byte year;
        public float latitude;
        public bool latDir;
        public float longitude;
        public bool lonDir;
        public float altitude;
        public byte satellites;
        public float speed;
        public float course;
        public byte[] dataString = new byte[ECP_GPS_DATA_STRING_MAX_SIZE];
    }

    public class MCU_2_LidarData : CyclicDataPacket
    {
        public UInt16 angleIndex;
        public UInt16 rpm;
        public UInt16 [] intensity = new UInt16[6];
        public UInt16 [] distance = new UInt16[6];
    }

    public class CyclicDataPacket
    {
        private DateTime lastTimeReceived = DateTime.MinValue;
        public void UpdateLastTimeReceived() { lastTimeReceived = DateTime.Now; }
        public DateTime GetLastTimeReceived() { return lastTimeReceived; }
    }
}
