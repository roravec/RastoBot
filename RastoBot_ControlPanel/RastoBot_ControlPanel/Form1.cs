namespace RastoBot_ControlPanel
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            if (combo_Speeds.Items.Count > 0)
                combo_Speeds.SelectedIndex = 0;
            ReloadComPorts();
            rastoBot = new RastoBot(serialPort, this);
            rastoBot.eventMessageDecoded += RastoBotMsgDecoded;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button_Open_Click(object sender, EventArgs e)
        {
            string comPort = combo_Ports.Text;
            string baudrate = combo_Speeds.Text;
            OpenPort(comPort, baudrate);
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort.ClosePort();
        }

        private void button_Disconnect_Click(object sender, EventArgs e)
        {
            ClosePort();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            rastoBot.Task_BeepBuzzer();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleFanManualControl();
            if (checkBox1.Checked)
            {
                checkBox_powerOut0.Enabled = true;
                checkBox_powerOut1.Enabled = true;
                checkBox_powerOut2.Enabled = true;
                checkBox_powerOut3.Enabled = true;
            }
            else
            {
                checkBox_powerOut0.Enabled = false;
                checkBox_powerOut1.Enabled = false;
                checkBox_powerOut2.Enabled = false;
                checkBox_powerOut3.Enabled = false;
            }
        }

        private void checkBox_powerOut4_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleEmergencyLight();
        }

        private void checkBox_led0_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleMCU0LED0();
        }

        private void checkBox_led1_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleMCU0LED1();
        }

        private void checkBox_led2_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleMCU0LED2();
        }

        private void button_setMainMotorSpeed_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMainMotorSpeed(trackBar_mainMotorSpeed.Value);
        }

        private void checkBox_powerOut0_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleFan0();
        }

        private void checkBox_powerOut1_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleFan1();
        }

        private void checkBox_powerOut2_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleFan2();
        }

        private void checkBox_powerOut3_CheckedChanged(object sender, EventArgs e)
        {
            rastoBot.Task_ToggleFan3();
        }

        private void button_stepperEnable_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsEnable(GetStepperMotorIndex());
        }

        private void button_StepperDisable_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsDisable(GetStepperMotorIndex());
        }

        private void button_StepperInit_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsInit(GetStepperMotorIndex());
        }

        private void button_stepperStop_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsStop(GetStepperMotorIndex());
        }

        private void button_stepperOperMode_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsOperMode(GetStepperMotorIndex(), GetStepperOperModeIndex());
        }

        private void button_stepperStepMode_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsStepMode(GetStepperMotorIndex(), GetStepperStepModeIndex());
        }

        private void button_stepperDirMode_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsDirection(GetStepperMotorIndex(), GetStepperDirIndex());
        }

        private void button_stepperSpeed_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsSpeed(GetStepperMotorIndex(), GetStepperSpeed());
        }

        private void button_stepperStepsToMake_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsStepsToMake(GetStepperMotorIndex(), GetStepperStepsToMake());
        }

        private void button_wheelsApplySpeed_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsStepsToMake(0, GetWheelsSpeed());
            rastoBot.Task_SetMotorsStepsToMake(1, GetWheelsSpeed());
        }

        private void button_wheelsStepsToMakeApply_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetWheelsStepsToMake(GetWheelsStepsToMake());
        }

        private void button_initWheels_Click(object sender, EventArgs e)
        {
            rastoBot.Task_SetMotorsInitWheels();
        }

        private void button_levelingRefRun_Click(object sender, EventArgs e)
        {
            rastoBot.Task_LevelingReferenceRun();
        }

        private void button_levelingGoTo_Click(object sender, EventArgs e)
        {
            rastoBot.Task_LevelingGoTo(GetLevelingPosition());
        }

        private void button_demo1_Click(object sender, EventArgs e)
        {

        }

        private void button_demo2_Click(object sender, EventArgs e)
        {

        }
    }
}