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
    }
}