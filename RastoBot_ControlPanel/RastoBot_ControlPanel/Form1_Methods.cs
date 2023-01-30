using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RastoBot_ControlPanel
{
    public partial class Form1 : Form
    {
        private void ReloadComPorts()
        {
            combo_Ports.Items.Clear();
            serialPort.ReloadComPorts();
            foreach (string comPort in serialPort.Ports)
            {
                combo_Ports.Items.Add(comPort);
            }
            if (combo_Ports.Items.Count > 0)
                combo_Ports.SelectedIndex = 0;
        }
        /// <summary>
        /// Open serial port connection
        /// </summary>
        /// <param name="comPort"></param>
        /// <param name="baudRate"></param>
        private void OpenPort(string comPort, string baudRate)
        {
            int iBaudRate = int.Parse(baudRate);
            //Ncv = new NCV78343ns.NCV78343(comPort, iBaudRate);
            if (serialPort.OpenPort(comPort, iBaudRate)) // port was opened successful
            //if (Ncv.UART.PortOpen) // port was opened successful
            {
                AddLogMessage("Port " + comPort + " is open.");
                serialPort.eventMessageReceived += SerialMessageReceived;
                button_Open.Enabled = false;
                combo_Speeds.Enabled = false;
                combo_Ports.Enabled = false;
                button_Disconnect.Enabled = true;
                //button_send.Enabled = true;
                //textBox_messageToSend.Enabled = true;
            }
            else                                    // port was not open, error
            {
                MessageBox.Show("Error opening com port.");
            }
        }
        /// <summary>
        /// Close active port connection
        /// </summary>
        private void ClosePort()
        {
            serialPort.ClosePort();
            AddLogMessage("Port " + serialPort.OpenedPort + " was closed.");
            serialPort.eventMessageReceived += SerialMessageReceived;
            button_Open.Enabled = true;
            combo_Speeds.Enabled = true;
            combo_Ports.Enabled = true;
            button_Disconnect.Enabled = false;
        }
        private void SendComMessage(string message)
        {
            serialPort.SendMessage(message);
            AddLogMessage("Sent");
            //Ncv.GetTestData();
            //AddLogMessage(ByteArrayToHexString(Ncv.GetFrameTestData().GetArray(), Ncv.GetFrameTestData().Length));
            //Ncv.UART.SendMessage(message);
        }
        delegate void AddMessageCallback(string message);
        private void AddLogMessage(string message)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.textBox_Log.InvokeRequired)
            {
                AddMessageCallback d = new AddMessageCallback(AddLogMessage);
                this.Invoke(d, new object[] { message });
            }
            else
            {
                textBox_Log.Text = message + "\r\n" + textBox_Log.Text;
            }
        }

        private void SerialMessageReceived(string text)
        {
            AddLogMessage("Received: " + text);
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
