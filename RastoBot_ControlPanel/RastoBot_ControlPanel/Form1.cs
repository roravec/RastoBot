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
    }
}