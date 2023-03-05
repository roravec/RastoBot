using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RastoBot_ControlPanel
{
    public class SerialPortComm
    {
        public String OpenedPort = "";
        private List<string> _ports = new List<string>();
        public List<string> Ports { get { return _ports; } }
        private SerialPort? _serialPort;
        public SerialPort? SerialPort { get { return _serialPort; } }
        private bool _portOpen = false;
        /// <summary>
        /// Check if port is already open
        /// </summary>
        public bool PortOpen { get => _portOpen; set => _portOpen = value; }

        public delegate void delMessageReceived(byte[] text, uint size);
        public event delMessageReceived? eventMessageReceived = null;

        public SerialPortComm()
        {
        }
        public SerialPortComm(string portName, uint baudRate)
        {
            OpenedPort = portName;
            OpenPort(portName, baudRate);
        }

        public void ReloadComPorts()
        {
            Ports.Clear();
            string[] ArrayComPortsNames = SerialPort.GetPortNames();
            foreach (string PortName in ArrayComPortsNames)
            {
                Ports.Add(PortName);
            }
        }
        public bool OpenPort(string portName, uint baudRate)
        {
            if (_portOpen) // port is already open
                return false;
            try
            {
                _serialPort = new SerialPort(portName, (Int32)baudRate, Parity.None, 8, StopBits.One);
                _serialPort.Handshake = Handshake.None;
                _serialPort.Open();
                if (_serialPort.IsOpen) // port was open successfuly
                {
                    _serialPort.DataReceived += DataReceived;
                    _portOpen = true;
                    return true;
                }
                else
                    return false;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                MessageBox.Show(ex.Message);
                return false;
            }
        }
        public bool ClosePort()
        {
            if (!_portOpen) // port is already closed
                return false;
            try
            {
                if (_serialPort is not null)
                    _serialPort.Close();
                if (_serialPort is null || !_serialPort.IsOpen) // port was closed
                {
                    _portOpen = false;
                    _serialPort = null;
                    return true;
                }
                else
                    return false;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return false;
            }
        }
        public void SendMessage(string message)
        {
            if (message == null || _serialPort is null || !PortOpen)
                return;
            _serialPort.WriteLine(message);
        }
        public void SendData(byte[] message, uint length)
        {
            if (message == null || _serialPort is null || !PortOpen)
                return;
            //_serialPort.BaseStream.
            //_serialPort.BaseStream.Flush();
            //SendBreak();
            _serialPort.Write(message, 0, (int)length);
        }
        public void SendBreak(uint lengthBytes = 2)
        {
            byte[] message = new byte[lengthBytes];
            for (int i = 0; i < lengthBytes; i++)
                message[i] = 0x00;
            SendData(message, lengthBytes);
        }
        static void udelay(long us)
        {
            var sw = System.Diagnostics.Stopwatch.StartNew();
            long v = (us * System.Diagnostics.Stopwatch.Frequency) / 1000000;
            while (sw.ElapsedTicks < v)
            {
            }
        }
        private void DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (_serialPort is null)
                return;
            int bytesReceived = _serialPort.BytesToRead;
            byte[] bdata = new byte[bytesReceived];
            _serialPort.Read(bdata, 0, bytesReceived);
            //string data = ByteArrayToHexString(bdata, bytesReceived);
            //string data = BitConverter.ToString(bdata);

            //string data = _serialPort.ReadLine();
            if (eventMessageReceived != null)
                eventMessageReceived(bdata, (uint)bytesReceived);
        }

        public static string ByteArrayToHexString(byte[] Bytes, int length)
        {
            StringBuilder Result = new StringBuilder(length * 2);
            string HexAlphabet = "0123456789ABCDEF";
            foreach (byte B in Bytes)
            {
                Result.Append(HexAlphabet[(int)(B >> 4)]);
                Result.Append(HexAlphabet[(int)(B & 0xF)]);
            }
            return Result.ToString();
        }
    }
}
