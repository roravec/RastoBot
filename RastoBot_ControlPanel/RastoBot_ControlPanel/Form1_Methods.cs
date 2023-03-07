﻿using ErmaCommProtocol;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
            uint iBaudRate = uint.Parse(baudRate);
            if (serialPort.OpenPort(comPort, iBaudRate)) // port was opened successful
            {
                AddLogMessage("Port " + comPort + " is open with baudrate " + iBaudRate + ".");
                serialPort.eventMessageReceived += SerialMessageReceived;
                serialPort.eventMessageReceived += rastoBot.SerialMessageReceived;
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
            serialPort.eventMessageReceived -= SerialMessageReceived;
            serialPort.eventMessageReceived -= rastoBot.SerialMessageReceived;
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
        public static string Truncate(string variable, int Length)
        {
            if (string.IsNullOrEmpty(variable)) return variable;
            return variable.Length <= Length ? variable : variable.Substring(0, Length);
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
                textBox_Log.Text = message + "\r\n" + Truncate(textBox_Log.Text, 1000);
            }
        }
        delegate void ChangeTextBoxValueCallback(TextBox tb, string text);
        public void ChangeTextBoxValue(TextBox tb, string text)
        {
            if (tb == null)
                return;
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (tb.InvokeRequired)
            {
                ChangeTextBoxValueCallback d = new ChangeTextBoxValueCallback(ChangeTextBoxValue);
                this.Invoke(d, new object[] { tb, text });
            }
            else
            {
                tb.Text = text;
            }
        }
        delegate void ChangeCheckBoxValueCallback(CheckBox tb, bool value);
        public void ChangeCheckBoxValue(CheckBox tb, bool value)
        {
            if (tb == null)
                return;
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (tb.InvokeRequired)
            {
                ChangeCheckBoxValueCallback d = new ChangeCheckBoxValueCallback(ChangeCheckBoxValue);
                this.Invoke(d, new object[] { tb, value });
            }
            else
            {
                //tb.Text = text;
                tb.Checked = value;
            }
        }

        delegate void ChangeProgressBarValueCallback(ProgressBar tb, int value);
        public void ChangeProgressBarValue(ProgressBar tb, int value)
        {
            if (tb == null)
                return;
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (tb.InvokeRequired)
            {
                ChangeProgressBarValueCallback d = new ChangeProgressBarValueCallback(ChangeProgressBarValue);
                this.Invoke(d, new object[] { tb, value });
            }
            else
            {
                //tb.Text = text;
                tb.Value = value;
            }
        }

        public void SerialMessageReceived(byte [] text, uint size)
        {
            string data = ByteArrayToHexString(text, (int)size);
            AddLogMessage("Received (" + size + "B): " + data);
        }
        public static string ByteArrayToHexString(byte[] Bytes, int length)
        {
            StringBuilder Result = new StringBuilder(length * 2);
            string HexAlphabet = "0123456789ABCDEF";

            int i = 0;
            foreach (byte B in Bytes)
            {
                Result.Append("["+i+"]");
                Result.Append(HexAlphabet[(int)(B >> 4)]);
                Result.Append(HexAlphabet[(int)(B & 0xF)]);
                Result.Append(' ');
                i++;
            }
            return Result.ToString();
        }
        public CheckBox GetCheckBoxManualControl()
        {
            return checkBox1;
        }
        public CheckBox GetCheckBoxFan0()
        {
            return checkBox_powerOut0;
        }
        public CheckBox GetCheckBoxFan1()
        {
            return checkBox_powerOut1;
        }
        public CheckBox GetCheckBoxFan2()
        {
            return checkBox_powerOut2;
        }
        public CheckBox GetCheckBoxFan3()
        {
            return checkBox_powerOut3;
        }
        public CheckBox GetCheckBoxEmergencyLight()
        {
            return checkBox_powerOut4;
        }
        public void RastoBotMsgDecoded(uint command)
        {
            UpdateUI();
        }
        public void UpdateUI()
        {
            UpdateSensors(rastoBot.sensors, rastoBot.motors);
        }
        public void UpdateSensors(MCU_0_Sensors sensors, MCU_1_Motors motors)
        {
            if (sensors == null)
                return;
            ChangeTextBoxValue(tb_temperature0, sensors.temperatures[0].ToString());
            ChangeTextBoxValue(tb_temperature1, sensors.temperatures[1].ToString());
            ChangeTextBoxValue(tb_temperature2, sensors.temperatures[2].ToString());
            ChangeTextBoxValue(tb_temperature3, sensors.temperatures[3].ToString());

            ChangeTextBoxValue(tb_humid0, sensors.humidities[0].ToString());
            ChangeTextBoxValue(tb_humid1, sensors.humidities[1].ToString());
            ChangeTextBoxValue(tb_humid2, sensors.humidities[2].ToString());
            ChangeTextBoxValue(tb_humid3, sensors.humidities[3].ToString());

            ChangeTextBoxValue(textBox_battVoltage, sensors.batteryVoltage.ToString());
            ChangeTextBoxValue(textBox_ExtVoltage, sensors.externalVoltage.ToString());

            ChangeTextBoxValue(textBox_rain, sensors.rainSensor.ToString());
            ChangeTextBoxValue(textBox_light, sensors.lightSensor.ToString());

            ChangeTextBoxValue(textBox_current0, sensors.currentSensors[0].ToString());
            ChangeTextBoxValue(textBox_current1, sensors.currentSensors[1].ToString());
            ChangeTextBoxValue(textBox_current2, sensors.currentSensors[2].ToString());
            ChangeTextBoxValue(textBox_current3, sensors.currentSensors[3].ToString());

            ChangeCheckBoxValue(checkBox_TiltSensor, sensors.tiltSensor);

            if (!checkBox1.Checked) // auto check Fans only in automatic control
            {
                ChangeCheckBoxValue(checkBox_powerOut0, sensors.powerOutputs[0]);
                ChangeCheckBoxValue(checkBox_powerOut1, sensors.powerOutputs[1]);
                ChangeCheckBoxValue(checkBox_powerOut2, sensors.powerOutputs[2]);
                ChangeCheckBoxValue(checkBox_powerOut3, sensors.powerOutputs[3]);
            }
            ChangeCheckBoxValue(checkBox_powerOut4, sensors.powerOutputs[4]);

            ChangeProgressBarValue(progressBar_mainMotor, motors.mainMotorSpeed);
        }

        public static void UiUpdater()
        {
            Thread.Sleep(100);
            if (Program.form1 != null)
            {
            }

        }
    }
}
