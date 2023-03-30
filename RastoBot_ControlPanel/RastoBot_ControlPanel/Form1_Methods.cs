using ErmaCommProtocol;
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
        private void EnablePanelContents(Panel panel, bool enabled)
        {
            foreach (Control ctrl in panel.Controls)
            {
                ctrl.Enabled = enabled;
            }
        }
        private void DisablePanelContents(Panel panel, bool enabled)
        {
            foreach (Control ctrl in panel.Controls)
            {
                ctrl.Enabled = enabled;
            }
        }
        private void ButtonsDisable(Control ct)
        {
            foreach (Control c in ct.Controls)
            {
                if (c is Button)
                {
                    c.Enabled = false;
                }
            }
            button_Open.Enabled = true;

            button_initWheels.Enabled = false;
            button_setMainMotorSpeed.Enabled = false;
            button_StepperDisable.Enabled = false;
            button_stepperEnable.Enabled = false;
            button_stepperOperMode.Enabled = false;
            button_stepperSpeed.Enabled = false;
            button_stepperStepMode.Enabled = false;
            button_wheelsApplySpeed.Enabled = false;
            button_wheelsStepsToMakeApply.Enabled = false;
            button_stepperDirMode.Enabled = false;
            button_stepperStepsToMake.Enabled = false;
            button_demo1.Enabled= false;
            button_demo2.Enabled= false;
            button_levelingGoTo.Enabled = false;
            button_levelingRefRun.Enabled = false;
        }
        private void ButtonsEnable(Control ct)
        {
            foreach (Control c in ct.Controls)
            {
                if (c is Button)
                {
                    c.Enabled = true;
                }
            }

            button_initWheels.Enabled = true;
            button_setMainMotorSpeed.Enabled = true;
            button_StepperDisable.Enabled = true;
            button_stepperEnable.Enabled = true;
            button_stepperOperMode.Enabled = true;
            button_stepperSpeed.Enabled = true;
            button_stepperStepMode.Enabled = true;
            button_wheelsApplySpeed.Enabled = true;
            button_wheelsStepsToMakeApply.Enabled = true;
            button_stepperDirMode.Enabled = true;
            button_stepperStepsToMake.Enabled = true;
            button_demo1.Enabled = true;
            button_demo2.Enabled = true;
            button_levelingGoTo.Enabled = true;
            button_levelingRefRun.Enabled = true;
        }
        private void ReloadComPorts()
        {
            ButtonsDisable(this);
            combo_Ports.Items.Clear();
            serialPort.ReloadComPorts();
            foreach (string comPort in serialPort.Ports)
            {
                combo_Ports.Items.Add(comPort);
            }
            if (combo_Ports.Items.Count > 0)
                combo_Ports.SelectedIndex = 0;

            comboBox_Stepper.SelectedIndex= 0;
            comboBox_direction.SelectedIndex= 0;
            comboBox_OperMode.SelectedIndex= 0;
            comboBox_stepMode.SelectedIndex= 0;
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
                ButtonsEnable(this);
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
            ButtonsDisable(this);
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
        public int GetStepperMotorIndex()
        {
           return comboBox_Stepper.SelectedIndex;
        }
        public int GetStepperOperModeIndex()
        {
            return comboBox_OperMode.SelectedIndex;
        }
        public int GetStepperStepModeIndex()
        {
            return comboBox_stepMode.SelectedIndex;
        }
        public int GetStepperDirIndex()
        {
            return comboBox_direction.SelectedIndex;
        }
        public int GetLevelingPosition()
        {
            String textboxValue = textBox_levelingGoToPos.Text;
            Int32 i = 0;
            if (!String.IsNullOrWhiteSpace(textboxValue) && // Not empty
                Int32.TryParse(textboxValue, out i))
            { // Valid integer
              // The textbox had a valid integer. i=1
            }
            else
            {
                // The texbox had a bogus value. i=default(Int32)=0
                // You can also specify a different fallback value here.
            }
            return i;
        }
        public int GetStepperSpeed()
        {
            String textboxValue = textBox_steperSpeed.Text;
            Int32 i=0;
            if (!String.IsNullOrWhiteSpace(textboxValue) && // Not empty
                Int32.TryParse(textboxValue, out i))
            { // Valid integer
              // The textbox had a valid integer. i=1
            }
            else
            {
                // The texbox had a bogus value. i=default(Int32)=0
                // You can also specify a different fallback value here.
            }
            return i;
        }
        public int GetStepperStepsToMake()
        {
            String textboxValue = textBox_stepperStepsToMake.Text;
            Int32 i = 0;
            if (!String.IsNullOrWhiteSpace(textboxValue) && // Not empty
                Int32.TryParse(textboxValue, out i))
            { // Valid integer
              // The textbox had a valid integer. i=1
            }
            else
            {
                // The texbox had a bogus value. i=default(Int32)=0
                // You can also specify a different fallback value here.
            }
            return i;
        }
        public int GetWheelsSpeed()
        {
            String textboxValue = textBox_wheelsSpeed.Text;
            Int32 i = 0;
            if (!String.IsNullOrWhiteSpace(textboxValue) && // Not empty
                Int32.TryParse(textboxValue, out i))
            { // Valid integer
              // The textbox had a valid integer. i=1
            }
            else
            {
                // The texbox had a bogus value. i=default(Int32)=0
                // You can also specify a different fallback value here.
            }
            return i;
        }
        public int GetWheelsStepsToMake()
        {
            String textboxValue = textBox_wheelsStepsToMake.Text;
            Int32 i = 0;
            if (!String.IsNullOrWhiteSpace(textboxValue) && // Not empty
                Int32.TryParse(textboxValue, out i))
            { // Valid integer
              // The textbox had a valid integer. i=1
            }
            else
            {
                // The texbox had a bogus value. i=default(Int32)=0
                // You can also specify a different fallback value here.
            }
            return i;
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

            ChangeTextBoxValue(textBox_battVoltage, rastoBot.GetVoltage(sensors.batteryVoltage).ToString());
            ChangeTextBoxValue(textBox_ExtVoltage, rastoBot.GetVoltage(sensors.externalVoltage).ToString());

            ChangeTextBoxValue(textBox_rain, sensors.rainSensor.ToString());
            ChangeTextBoxValue(textBox_light, sensors.lightSensor.ToString());

            ChangeTextBoxValue(textBox_current0, rastoBot.GetCurrentValue(sensors.currentSensors[0]).ToString());
            ChangeTextBoxValue(textBox_current1, rastoBot.GetCurrentValue(sensors.currentSensors[1]).ToString());
            ChangeTextBoxValue(textBox_current2, rastoBot.GetCurrentValue(sensors.currentSensors[2]).ToString());
            ChangeTextBoxValue(textBox_current3, rastoBot.GetCurrentValue(sensors.currentSensors[3]).ToString());

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

            ChangeTextBoxValue(textBox_accel_X, rastoBot.gyro.accelX.ToString());
            ChangeTextBoxValue(textBox_accel_Y, rastoBot.gyro.accelY.ToString());
            ChangeTextBoxValue(textBox_accel_Z, rastoBot.gyro.accelZ.ToString());
            ChangeTextBoxValue(textBox_gyro_X, rastoBot.gyro.gyroX.ToString());
            ChangeTextBoxValue(textBox_gyro_Y, rastoBot.gyro.gyroY.ToString());
            ChangeTextBoxValue(textBox_gyro_Z, rastoBot.gyro.gyroZ.ToString());
            ChangeTextBoxValue(textBox_compass_X, rastoBot.gyro.magnetX.ToString());
            ChangeTextBoxValue(textBox_compass_Y, rastoBot.gyro.magnetY.ToString());
            ChangeTextBoxValue(textBox_compass_Z, rastoBot.gyro.magnetZ.ToString());
            ChangeTextBoxValue(textBox_perimWire, rastoBot.gyro.perimeterWire.ToString());
            ChangeTextBoxValue(textBox_azimuth, rastoBot.gyro.azimuth.ToString());
            //ChangeTextBoxValue(textBox_compassTemp, rastoBot.gyro.temperature.ToString());

            ChangeTextBoxValue(textBox_gpsAlt, rastoBot.gps.altitude.ToString());
            ChangeTextBoxValue(textBox_gpsCourse, rastoBot.gps.course.ToString());
            ChangeTextBoxValue(textBox_gpsSatellites, rastoBot.gps.satellites.ToString());
            ChangeTextBoxValue(textBox_gpsSpeed, rastoBot.gps.speed.ToString());
            String latString = "";
            if (rastoBot.gps.latDir)
                latString = "-";
            String longString = "";
            if (rastoBot.gps.lonDir)
                longString = "-";
            latString += rastoBot.gps.latitude.ToString();
            longString += rastoBot.gps.longitude.ToString();
            ChangeTextBoxValue(textBox_gpsLat, latString);
            ChangeTextBoxValue(textBox_gpsLong, longString);
            ChangeTextBoxValue(textBox_gpsHour, rastoBot.gps.hours.ToString());
            ChangeTextBoxValue(textBox_gpsSec, rastoBot.gps.seconds.ToString());
            ChangeTextBoxValue(textBox_gpsMin, rastoBot.gps.minutes.ToString());
            ChangeTextBoxValue(textBox_gpsDay, rastoBot.gps.day.ToString());
            ChangeTextBoxValue(textBox_gpsMonth, rastoBot.gps.month.ToString());
            ChangeTextBoxValue(textBox_gpsYear, rastoBot.gps.year.ToString());
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
