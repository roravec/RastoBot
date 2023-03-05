using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ErmaCommProtocol
{
    using uint8_t = Byte;
    using uint16_t = UInt16;
    using uint32_t = UInt32;

    public enum ECP_MessageType { ECP_COMDATA=0, ECP_COMMAND };
    public enum ECP_PacketValidity { 
        ECP_UNKNOWN = 0,
        ECP_VALID,
        ECP_INVALID_CRC,
        ECP_INVALID_HEADER,
        ECP_INVALID_FOOTER,
        ECP_INVALID_PACKET_SIZE,
        ECP_INVALID_DATA_SIZE
    }

    internal class ECP_Buffer
    {
        public bool         startByteDetected = false;
        public bool         stopByteDetected = false;
        public bool         patternDetected = false ;
        public uint8_t[]    buffer = new uint8_t[ErmaCommProtocol.ECP_MAX_DATA_BYTES];
        public uint8_t      command = 0;
        public uint8_t      subCommand = 0;
        public uint8_t      dlc = 0 ;
        public uint8_t      crc = 0;
        public uint16_t     size = 0;
    }

    public class ECP_Message
    {
        public uint8_t      command;
        public uint8_t      subCommand;
        public uint8_t      dlc;
        public uint8_t[]    data = new uint8_t[ErmaCommProtocol.ECP_MAX_DATA_BYTES];
        public ECP_MessageType msgType;
    }
    static class ErmaCommProtocol
    {
        private const uint8_t ECP_EMPTY_DATA = 0x00;
        private const uint8_t ECP_CRC_START_VALUE = 0x55;
        private const bool ECP_AVOID_CRC_CHECK_ON_RCV = true;
        public const uint16_t ECP_MAX_DATA_BYTES = 255;
        private const uint8_t ECP_START_BYTE = 0x01;
        private const uint8_t ECP_STOP_BYTE = 0x04;
        private const uint8_t ECP_COMMAND_LEN = 4;
        private const uint8_t ECP_DLC_LEN = 1;
        private const uint8_t ECP_CRC_LEN = 1;
        private const uint8_t ECP_PATTERN_LEN = (1 + ECP_COMMAND_LEN + ECP_DLC_LEN);
        private const uint8_t ECP_MIN_PACKET_LEN = (2 + ECP_COMMAND_LEN + ECP_DLC_LEN + ECP_CRC_LEN);
        private const uint16_t ECP_MAX_PACKET_LEN = (2 + ECP_COMMAND_LEN + ECP_DLC_LEN + ECP_MAX_DATA_BYTES + ECP_CRC_LEN);
        private const uint16_t ECP_PACKET_LEN_WO_DATA = (2 + ECP_COMMAND_LEN + ECP_DLC_LEN + ECP_CRC_LEN);
        public static uint16_t ECP_PACKET_LEN_KNOWN_DLC(uint8_t dlc)
        {
            return (uint16_t)(2 + ECP_COMMAND_LEN + ECP_DLC_LEN + dlc + ECP_CRC_LEN);
        }

        public static ECP_Message CreateMessage(uint8_t command, uint8_t subCommand, uint8_t[] data, uint8_t dlc)
        {
            ECP_Message messOut = new ECP_Message();
            messOut.command = command;
            messOut.subCommand = subCommand;
            messOut.data = data;
            messOut.dlc = dlc;
            messOut.msgType = ECP_MessageType.ECP_COMDATA;
            return messOut;
        }
        public static ECP_Message CreateMessageCommand(uint8_t command, uint8_t subCommand)
        {
            ECP_Message messOut = new ECP_Message();
            messOut.command = command;
            messOut.subCommand = subCommand;
            messOut.msgType = ECP_MessageType.ECP_COMMAND;
            messOut.dlc = 0;
            return messOut;
        }

        public static ECP_Message? ECP_Decode(uint8_t[] ecpRaw, uint16_t ecpRawLen)
        {
            if (ecpRawLen < ECP_MIN_PACKET_LEN) // invalid length
                return null;
            ECP_Message messOut = new ECP_Message();
            messOut.command = ecpRaw[1];
            messOut.subCommand = ecpRaw[3];
            messOut.dlc = ecpRaw[5];
            messOut.msgType = messOut.dlc > 0 ? ECP_MessageType.ECP_COMDATA : ECP_MessageType.ECP_COMMAND;
            if (messOut.dlc > 0 && ecpRawLen == ECP_MIN_PACKET_LEN + messOut.dlc)
            {
                for (uint8_t i = 0, j = 6; i < messOut.dlc; i++)
                    messOut.data[i] = ecpRaw[j + i];
            }
            return messOut;
        }

        public static uint8_t[] ECP_EncodeExtended(ECP_Message message, uint8_t minDataLen)
        {
            uint8_t[] outArr = new uint8_t[ECP_MAX_DATA_BYTES+8];
            uint16_t currentIndex = 0;
            outArr[currentIndex++] = ECP_START_BYTE;
            outArr[currentIndex++] = message.command;
            uint16_t tempIndex = (ushort)(currentIndex - 1);
            outArr[currentIndex++] = (byte)~outArr[tempIndex];
            outArr[currentIndex++] = message.subCommand;
            tempIndex = (ushort)(currentIndex - 1);
            outArr[currentIndex++] = (byte)~outArr[tempIndex];
            outArr[currentIndex++] = message.dlc > minDataLen ? message.dlc : minDataLen;
            uint16_t dataIndex = 0;
            for (uint16_t j = currentIndex; dataIndex < message.dlc && dataIndex < ECP_MAX_DATA_BYTES; dataIndex++)
                outArr[currentIndex++] = message.data[dataIndex];
            for (; dataIndex < minDataLen; dataIndex++)
                outArr[currentIndex++] = ECP_EMPTY_DATA;
            //    for (;dataIndex < ECP_FIXED_DATA_SIZE;dataIndex++)
            //        out->data[currentIndex++] = ECP_EMPTY_DATA;
            uint8_t crc = ECP_CRC_START_VALUE;
            for (uint16_t i = 0; i < currentIndex; i++)
                crc ^= outArr[i];
            outArr[currentIndex++] = crc;
            outArr[currentIndex++] = ECP_STOP_BYTE;
            Array.Resize(ref outArr, currentIndex);
            return outArr;
        }

        public static ECP_PacketValidity ECP_CheckPacketValidity(uint8_t [] packet, uint16_t len)
        {
            if (len < ECP_MIN_PACKET_LEN) return ECP_PacketValidity.ECP_INVALID_PACKET_SIZE;
            uint8_t dlc = ECP_GetDLCFromPacket(packet, 0);
            if (dlc != len - (ECP_PATTERN_LEN + ECP_CRC_LEN + 1)) return ECP_PacketValidity.ECP_INVALID_DATA_SIZE;
            if (!ECP_DetectHeadPatternAtIndexArr(packet, ECP_PATTERN_LEN)) return ECP_PacketValidity.ECP_INVALID_HEADER;
            if (packet[len - 1] != ECP_STOP_BYTE) return ECP_PacketValidity.ECP_INVALID_FOOTER;
            if (!ECP_CheckCRCAtIndexArr(packet, dlc, ECP_GetCRCIndex(0, dlc))) return ECP_PacketValidity.ECP_INVALID_CRC;
            return ECP_PacketValidity.ECP_VALID;
        }

        private static uint8_t ECP_GetDLCFromPacket(uint8_t[] data, uint16_t packetStartIndex)
        {
            if (data.Length < ECP_PATTERN_LEN - 1)
                return 0;
            return data[ECP_PATTERN_LEN - 1 + packetStartIndex];
        }

        private static uint8_t ECP_GetCRCIndex(uint8_t packetStartIndex, uint16_t dlc)
        {
            return (byte)(packetStartIndex + dlc + ECP_PATTERN_LEN + ECP_DLC_LEN);
        }

        private static bool ECP_DetectHeadPatternAtIndexArr(uint8_t[] data, uint16_t startIndex)
        {
            if (startIndex >= ECP_PATTERN_LEN)
            {
                uint8_t index = (byte)(startIndex - (ECP_PATTERN_LEN)); // set index at beginning of the packet
                uint8_t negdat0 = (byte)~data[index + 1];
                uint8_t negdat1 = (byte)~data[index + 3];
                if (data[index] == ECP_START_BYTE &&
                        negdat0 == data[(index + 2)] &&
                        negdat1 == data[(index + 4)])
                {
                    return true;
                }
            }
            return false;
        }

        private static bool ECP_CheckCRCAtIndexArr(uint8_t [] data, uint8_t dlc, uint16_t index)
        {
            if (index >= dlc + ECP_PATTERN_LEN)
            {
                uint8_t actualCrc = ECP_CalculateCRCFromPacket(data, dlc, 0);
                uint8_t crcFromPacket = ECP_GetCRCFromPacket(data, dlc, 0);
                if (ECP_AVOID_CRC_CHECK_ON_RCV)
                    return true;
                if (crcFromPacket == actualCrc)
                    return true;
            }
            return false;
        }
        private static uint8_t ECP_GetCRCFromPacket(uint8_t [] data, uint8_t dlc, uint8_t packetStartIndex)
        {
            return data[ECP_PATTERN_LEN + packetStartIndex + dlc + ECP_DLC_LEN];
        }
        private static uint8_t ECP_CalculateCRCFromPacket(uint8_t [] data, uint8_t dlc, uint16_t startIndex)
        {
            uint8_t actualCrc = ECP_CRC_START_VALUE;
            for (uint16_t i = startIndex; i <= startIndex + dlc + ECP_PATTERN_LEN; i++)
            {
                actualCrc ^= data[i];
            }
            return actualCrc;
        }

        public static IEnumerable<IEnumerable<T>> Split<T>(this T[] arr, int size)
        {
            for (var i = 0; i < arr.Length / size + 1; i++)
            {
                yield return arr.Skip(i * size).Take(size);
            }
        }
    }
}
