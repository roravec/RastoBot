using ErmaCommProtocol;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RastoBot_ControlPanel
{
    public class RastoBot
    {
        MCU_0_Sensors   sensors = new MCU_0_Sensors();
        MCU_1_Motors    motors = new MCU_1_Motors();
        MCU_2_GyroData  gyro = new MCU_2_GyroData();
        MCU_2_GPSData   gps = new MCU_2_GPSData();
        MCU_2_LidarData lidar = new MCU_2_LidarData();

        public void SerialMessageReceived(string text, uint size)
        {
            byte[] packet = GetByteArray(text, (ushort)size);
            if (ErmaCommProtocol.ErmaCommProtocol.ECP_CheckPacketValidity(packet, (ushort)size) == ECP_PacketValidity.ECP_VALID)
            {
                // packet is valid
                ECP_Message msg = ErmaCommProtocol.ErmaCommProtocol.ECP_Decode(packet, (ushort)size);
                if (msg != null) 
                {
                    // msg decoded correctly
                    MakeAction(msg);
                }
            }
        }

        private void MakeAction(ECP_Message msg)
        {
            if (msg == null) { return; }
        }

        private byte[] GetByteArray(string str, ushort size)
        {
            byte[] bytes = new byte[size];
            for (UInt16 i = 0; i < size ;i++)
            {
                bytes[i] = (byte)str[i];
            }
            return bytes;
        }

        void RastoBot_Decode_SensorsMotors(ref MCU_0_Sensors sensorsOut, ref MCU_1_Motors motorsOut, ECP_Message msg)
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
        ref MCU_2_LidarData lidar,
        ref MCU_2_GyroData gyro,
        ref MCU_2_GPSData gps,
        ref ECP_Message msg)
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
            gps.lonDir = Convert.ToBoolean((msg.data[60] >> 1) &1);
            gps.seconds = msg.data[61];
            gps.minutes = msg.data[62];
            gps.hours = msg.data[63];
        }
    }
    public class MCU_0_Sensors
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

    public class MCU_1_Motors
    {
        public byte mainMotorSpeed; // percent
        public bool[] stepperEnabled =      new bool[3];
        public bool[] stepperDirection =    new bool[3];
        public byte[] stepperStepMode =     new byte[3];
        public byte[] stepperOperMode =     new byte[3];
        public UInt16[] stepperSpeed =      new UInt16[3];
        public UInt16 levelingPosition;
    }

    public class MCU_2_GyroData
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

    public class MCU_2_GPSData
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

    public class MCU_2_LidarData 
    {
        public UInt16 angleIndex;
        public UInt16 rpm;
        public UInt16 [] intensity = new UInt16[6];
        public UInt16 [] distance = new UInt16[6];
    }
}
