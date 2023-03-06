namespace RastoBot_ControlPanel
{
    partial class Form1
    {
        static SerialPortComm serialPort = new SerialPortComm();

        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button_Open = new System.Windows.Forms.Button();
            this.combo_Ports = new System.Windows.Forms.ComboBox();
            this.combo_Speeds = new System.Windows.Forms.ComboBox();
            this.textBox_Log = new System.Windows.Forms.TextBox();
            this.button_Disconnect = new System.Windows.Forms.Button();
            this.tempBox = new System.Windows.Forms.GroupBox();
            this.tb_humid3 = new System.Windows.Forms.TextBox();
            this.tb_humid2 = new System.Windows.Forms.TextBox();
            this.tb_humid1 = new System.Windows.Forms.TextBox();
            this.tb_humid0 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tb_temperature3 = new System.Windows.Forms.TextBox();
            this.tb_temperature2 = new System.Windows.Forms.TextBox();
            this.tb_temperature1 = new System.Windows.Forms.TextBox();
            this.tb_temperature0 = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox_battVoltage = new System.Windows.Forms.TextBox();
            this.textBox_ExtVoltage = new System.Windows.Forms.TextBox();
            this.textBox_current0 = new System.Windows.Forms.TextBox();
            this.textBox_current1 = new System.Windows.Forms.TextBox();
            this.textBox_current2 = new System.Windows.Forms.TextBox();
            this.textBox_current3 = new System.Windows.Forms.TextBox();
            this.checkBox_TiltSensor = new System.Windows.Forms.CheckBox();
            this.textBox_rain = new System.Windows.Forms.TextBox();
            this.textBox_light = new System.Windows.Forms.TextBox();
            this.checkBox_powerOut0 = new System.Windows.Forms.CheckBox();
            this.checkBox_powerOut1 = new System.Windows.Forms.CheckBox();
            this.checkBox_powerOut2 = new System.Windows.Forms.CheckBox();
            this.checkBox_powerOut3 = new System.Windows.Forms.CheckBox();
            this.checkBox_powerOut4 = new System.Windows.Forms.CheckBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.checkBox_led0 = new System.Windows.Forms.CheckBox();
            this.checkBox_led2 = new System.Windows.Forms.CheckBox();
            this.checkBox_led1 = new System.Windows.Forms.CheckBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.progressBar_mainMotor = new System.Windows.Forms.ProgressBar();
            this.trackBar_mainMotorSpeed = new System.Windows.Forms.TrackBar();
            this.button_setMainMotorSpeed = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.tempBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_mainMotorSpeed)).BeginInit();
            this.groupBox7.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Port:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(180, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "Speed:";
            // 
            // button_Open
            // 
            this.button_Open.Location = new System.Drawing.Point(364, 22);
            this.button_Open.Name = "button_Open";
            this.button_Open.Size = new System.Drawing.Size(75, 23);
            this.button_Open.TabIndex = 2;
            this.button_Open.Text = "Open";
            this.button_Open.UseVisualStyleBackColor = true;
            this.button_Open.Click += new System.EventHandler(this.button_Open_Click);
            // 
            // combo_Ports
            // 
            this.combo_Ports.FormattingEnabled = true;
            this.combo_Ports.Location = new System.Drawing.Point(53, 22);
            this.combo_Ports.Name = "combo_Ports";
            this.combo_Ports.Size = new System.Drawing.Size(121, 23);
            this.combo_Ports.TabIndex = 3;
            // 
            // combo_Speeds
            // 
            this.combo_Speeds.FormattingEnabled = true;
            this.combo_Speeds.Items.AddRange(new object[] {
            "256000",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.combo_Speeds.Location = new System.Drawing.Point(228, 22);
            this.combo_Speeds.Name = "combo_Speeds";
            this.combo_Speeds.Size = new System.Drawing.Size(121, 23);
            this.combo_Speeds.TabIndex = 4;
            // 
            // textBox_Log
            // 
            this.textBox_Log.Location = new System.Drawing.Point(805, 12);
            this.textBox_Log.MaxLength = 10000;
            this.textBox_Log.Multiline = true;
            this.textBox_Log.Name = "textBox_Log";
            this.textBox_Log.Size = new System.Drawing.Size(317, 328);
            this.textBox_Log.TabIndex = 5;
            // 
            // button_Disconnect
            // 
            this.button_Disconnect.Enabled = false;
            this.button_Disconnect.Location = new System.Drawing.Point(460, 22);
            this.button_Disconnect.Name = "button_Disconnect";
            this.button_Disconnect.Size = new System.Drawing.Size(75, 23);
            this.button_Disconnect.TabIndex = 6;
            this.button_Disconnect.Text = "Disconnect";
            this.button_Disconnect.UseVisualStyleBackColor = true;
            this.button_Disconnect.Click += new System.EventHandler(this.button_Disconnect_Click);
            // 
            // tempBox
            // 
            this.tempBox.Controls.Add(this.tb_humid3);
            this.tempBox.Controls.Add(this.tb_humid2);
            this.tempBox.Controls.Add(this.tb_humid1);
            this.tempBox.Controls.Add(this.tb_humid0);
            this.tempBox.Controls.Add(this.label8);
            this.tempBox.Controls.Add(this.label7);
            this.tempBox.Controls.Add(this.label6);
            this.tempBox.Controls.Add(this.label5);
            this.tempBox.Controls.Add(this.label4);
            this.tempBox.Controls.Add(this.label3);
            this.tempBox.Controls.Add(this.tb_temperature3);
            this.tempBox.Controls.Add(this.tb_temperature2);
            this.tempBox.Controls.Add(this.tb_temperature1);
            this.tempBox.Controls.Add(this.tb_temperature0);
            this.tempBox.Location = new System.Drawing.Point(180, 184);
            this.tempBox.Name = "tempBox";
            this.tempBox.Size = new System.Drawing.Size(258, 172);
            this.tempBox.TabIndex = 7;
            this.tempBox.TabStop = false;
            this.tempBox.Text = "DHT11/22 sensors";
            // 
            // tb_humid3
            // 
            this.tb_humid3.Location = new System.Drawing.Point(173, 133);
            this.tb_humid3.Name = "tb_humid3";
            this.tb_humid3.ReadOnly = true;
            this.tb_humid3.Size = new System.Drawing.Size(51, 23);
            this.tb_humid3.TabIndex = 14;
            // 
            // tb_humid2
            // 
            this.tb_humid2.Location = new System.Drawing.Point(173, 104);
            this.tb_humid2.Name = "tb_humid2";
            this.tb_humid2.ReadOnly = true;
            this.tb_humid2.Size = new System.Drawing.Size(51, 23);
            this.tb_humid2.TabIndex = 13;
            // 
            // tb_humid1
            // 
            this.tb_humid1.Location = new System.Drawing.Point(173, 75);
            this.tb_humid1.Name = "tb_humid1";
            this.tb_humid1.ReadOnly = true;
            this.tb_humid1.Size = new System.Drawing.Size(51, 23);
            this.tb_humid1.TabIndex = 12;
            // 
            // tb_humid0
            // 
            this.tb_humid0.Location = new System.Drawing.Point(173, 46);
            this.tb_humid0.Name = "tb_humid0";
            this.tb_humid0.ReadOnly = true;
            this.tb_humid0.Size = new System.Drawing.Size(51, 23);
            this.tb_humid0.TabIndex = 11;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(159, 28);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(78, 15);
            this.label8.TabIndex = 10;
            this.label8.Text = "Humidity [%]";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(57, 28);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(92, 15);
            this.label7.TabIndex = 9;
            this.label7.Text = "Temperature [C]";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 136);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(51, 15);
            this.label6.TabIndex = 8;
            this.label6.Text = "Sensor 3";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 107);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(51, 15);
            this.label5.TabIndex = 7;
            this.label5.Text = "Sensor 2";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 78);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(51, 15);
            this.label4.TabIndex = 6;
            this.label4.Text = "Sensor 1";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 15);
            this.label3.TabIndex = 5;
            this.label3.Text = "Sensor 0";
            // 
            // tb_temperature3
            // 
            this.tb_temperature3.Location = new System.Drawing.Point(71, 133);
            this.tb_temperature3.Name = "tb_temperature3";
            this.tb_temperature3.ReadOnly = true;
            this.tb_temperature3.Size = new System.Drawing.Size(51, 23);
            this.tb_temperature3.TabIndex = 3;
            // 
            // tb_temperature2
            // 
            this.tb_temperature2.Location = new System.Drawing.Point(71, 104);
            this.tb_temperature2.Name = "tb_temperature2";
            this.tb_temperature2.ReadOnly = true;
            this.tb_temperature2.Size = new System.Drawing.Size(51, 23);
            this.tb_temperature2.TabIndex = 2;
            // 
            // tb_temperature1
            // 
            this.tb_temperature1.Location = new System.Drawing.Point(71, 75);
            this.tb_temperature1.Name = "tb_temperature1";
            this.tb_temperature1.ReadOnly = true;
            this.tb_temperature1.Size = new System.Drawing.Size(51, 23);
            this.tb_temperature1.TabIndex = 1;
            // 
            // tb_temperature0
            // 
            this.tb_temperature0.Location = new System.Drawing.Point(71, 46);
            this.tb_temperature0.Name = "tb_temperature0";
            this.tb_temperature0.ReadOnly = true;
            this.tb_temperature0.Size = new System.Drawing.Size(51, 23);
            this.tb_temperature0.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.combo_Ports);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.button_Disconnect);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.button_Open);
            this.groupBox1.Controls.Add(this.combo_Speeds);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(550, 60);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection";
            // 
            // textBox_battVoltage
            // 
            this.textBox_battVoltage.Location = new System.Drawing.Point(61, 26);
            this.textBox_battVoltage.Name = "textBox_battVoltage";
            this.textBox_battVoltage.ReadOnly = true;
            this.textBox_battVoltage.Size = new System.Drawing.Size(51, 23);
            this.textBox_battVoltage.TabIndex = 15;
            // 
            // textBox_ExtVoltage
            // 
            this.textBox_ExtVoltage.Location = new System.Drawing.Point(61, 55);
            this.textBox_ExtVoltage.Name = "textBox_ExtVoltage";
            this.textBox_ExtVoltage.ReadOnly = true;
            this.textBox_ExtVoltage.Size = new System.Drawing.Size(51, 23);
            this.textBox_ExtVoltage.TabIndex = 16;
            // 
            // textBox_current0
            // 
            this.textBox_current0.Location = new System.Drawing.Point(82, 27);
            this.textBox_current0.Name = "textBox_current0";
            this.textBox_current0.ReadOnly = true;
            this.textBox_current0.Size = new System.Drawing.Size(51, 23);
            this.textBox_current0.TabIndex = 17;
            // 
            // textBox_current1
            // 
            this.textBox_current1.Location = new System.Drawing.Point(82, 53);
            this.textBox_current1.Name = "textBox_current1";
            this.textBox_current1.ReadOnly = true;
            this.textBox_current1.Size = new System.Drawing.Size(51, 23);
            this.textBox_current1.TabIndex = 18;
            // 
            // textBox_current2
            // 
            this.textBox_current2.Location = new System.Drawing.Point(82, 82);
            this.textBox_current2.Name = "textBox_current2";
            this.textBox_current2.ReadOnly = true;
            this.textBox_current2.Size = new System.Drawing.Size(51, 23);
            this.textBox_current2.TabIndex = 19;
            // 
            // textBox_current3
            // 
            this.textBox_current3.Location = new System.Drawing.Point(82, 111);
            this.textBox_current3.Name = "textBox_current3";
            this.textBox_current3.ReadOnly = true;
            this.textBox_current3.Size = new System.Drawing.Size(51, 23);
            this.textBox_current3.TabIndex = 20;
            // 
            // checkBox_TiltSensor
            // 
            this.checkBox_TiltSensor.AutoSize = true;
            this.checkBox_TiltSensor.Enabled = false;
            this.checkBox_TiltSensor.Location = new System.Drawing.Point(339, 102);
            this.checkBox_TiltSensor.Name = "checkBox_TiltSensor";
            this.checkBox_TiltSensor.Size = new System.Drawing.Size(80, 19);
            this.checkBox_TiltSensor.TabIndex = 21;
            this.checkBox_TiltSensor.Text = "Tilt Sensor";
            this.checkBox_TiltSensor.UseVisualStyleBackColor = true;
            // 
            // textBox_rain
            // 
            this.textBox_rain.Location = new System.Drawing.Point(92, 26);
            this.textBox_rain.Name = "textBox_rain";
            this.textBox_rain.ReadOnly = true;
            this.textBox_rain.Size = new System.Drawing.Size(51, 23);
            this.textBox_rain.TabIndex = 22;
            // 
            // textBox_light
            // 
            this.textBox_light.Location = new System.Drawing.Point(92, 55);
            this.textBox_light.Name = "textBox_light";
            this.textBox_light.ReadOnly = true;
            this.textBox_light.Size = new System.Drawing.Size(51, 23);
            this.textBox_light.TabIndex = 23;
            // 
            // checkBox_powerOut0
            // 
            this.checkBox_powerOut0.AutoSize = true;
            this.checkBox_powerOut0.Enabled = false;
            this.checkBox_powerOut0.Location = new System.Drawing.Point(17, 52);
            this.checkBox_powerOut0.Name = "checkBox_powerOut0";
            this.checkBox_powerOut0.Size = new System.Drawing.Size(54, 19);
            this.checkBox_powerOut0.TabIndex = 24;
            this.checkBox_powerOut0.Text = "Fan 0";
            this.checkBox_powerOut0.UseVisualStyleBackColor = true;
            // 
            // checkBox_powerOut1
            // 
            this.checkBox_powerOut1.AutoSize = true;
            this.checkBox_powerOut1.Enabled = false;
            this.checkBox_powerOut1.Location = new System.Drawing.Point(17, 77);
            this.checkBox_powerOut1.Name = "checkBox_powerOut1";
            this.checkBox_powerOut1.Size = new System.Drawing.Size(54, 19);
            this.checkBox_powerOut1.TabIndex = 25;
            this.checkBox_powerOut1.Text = "Fan 1";
            this.checkBox_powerOut1.UseVisualStyleBackColor = true;
            // 
            // checkBox_powerOut2
            // 
            this.checkBox_powerOut2.AutoSize = true;
            this.checkBox_powerOut2.Enabled = false;
            this.checkBox_powerOut2.Location = new System.Drawing.Point(17, 102);
            this.checkBox_powerOut2.Name = "checkBox_powerOut2";
            this.checkBox_powerOut2.Size = new System.Drawing.Size(54, 19);
            this.checkBox_powerOut2.TabIndex = 26;
            this.checkBox_powerOut2.Text = "Fan 2";
            this.checkBox_powerOut2.UseVisualStyleBackColor = true;
            // 
            // checkBox_powerOut3
            // 
            this.checkBox_powerOut3.AutoSize = true;
            this.checkBox_powerOut3.Enabled = false;
            this.checkBox_powerOut3.Location = new System.Drawing.Point(17, 127);
            this.checkBox_powerOut3.Name = "checkBox_powerOut3";
            this.checkBox_powerOut3.Size = new System.Drawing.Size(54, 19);
            this.checkBox_powerOut3.TabIndex = 27;
            this.checkBox_powerOut3.Text = "Fan 3";
            this.checkBox_powerOut3.UseVisualStyleBackColor = true;
            // 
            // checkBox_powerOut4
            // 
            this.checkBox_powerOut4.AutoSize = true;
            this.checkBox_powerOut4.Location = new System.Drawing.Point(595, 33);
            this.checkBox_powerOut4.Name = "checkBox_powerOut4";
            this.checkBox_powerOut4.Size = new System.Drawing.Size(112, 19);
            this.checkBox_powerOut4.TabIndex = 28;
            this.checkBox_powerOut4.Text = "Emergency light";
            this.checkBox_powerOut4.UseVisualStyleBackColor = true;
            this.checkBox_powerOut4.CheckedChanged += new System.EventHandler(this.checkBox_powerOut4_CheckedChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(609, 78);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 29;
            this.button1.Text = "Beep";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(11, 29);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(44, 15);
            this.label9.TabIndex = 15;
            this.label9.Text = "Battery";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 60);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(49, 15);
            this.label10.TabIndex = 30;
            this.label10.Text = "External";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.textBox_battVoltage);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.textBox_ExtVoltage);
            this.groupBox2.Location = new System.Drawing.Point(12, 78);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(133, 90);
            this.groupBox2.TabIndex = 31;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Voltages";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.textBox_current3);
            this.groupBox3.Controls.Add(this.textBox_current0);
            this.groupBox3.Controls.Add(this.textBox_current1);
            this.groupBox3.Controls.Add(this.textBox_current2);
            this.groupBox3.Location = new System.Drawing.Point(12, 184);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(152, 143);
            this.groupBox3.TabIndex = 32;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Current sensors";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(44, 114);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(32, 15);
            this.label14.TabIndex = 34;
            this.label14.Text = "Total";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 85);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(70, 15);
            this.label13.TabIndex = 33;
            this.label13.Text = "Main motor";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(20, 56);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(56, 15);
            this.label12.TabIndex = 32;
            this.label12.Text = "Stepper 1";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(21, 30);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(56, 15);
            this.label11.TabIndex = 31;
            this.label11.Text = "Stepper 0";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(19, 29);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(67, 15);
            this.label15.TabIndex = 35;
            this.label15.Text = "Rain sensor";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(15, 58);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(71, 15);
            this.label16.TabIndex = 36;
            this.label16.Text = "Light sensor";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label15);
            this.groupBox4.Controls.Add(this.label16);
            this.groupBox4.Controls.Add(this.textBox_rain);
            this.groupBox4.Controls.Add(this.textBox_light);
            this.groupBox4.Location = new System.Drawing.Point(161, 78);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(160, 90);
            this.groupBox4.TabIndex = 37;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Voltage div. sensors";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(17, 22);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(107, 19);
            this.checkBox1.TabIndex = 38;
            this.checkBox1.Text = "Manual control";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.checkBox1);
            this.groupBox5.Controls.Add(this.checkBox_powerOut1);
            this.groupBox5.Controls.Add(this.checkBox_powerOut0);
            this.groupBox5.Controls.Add(this.checkBox_powerOut2);
            this.groupBox5.Controls.Add(this.checkBox_powerOut3);
            this.groupBox5.Location = new System.Drawing.Point(12, 345);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(136, 160);
            this.groupBox5.TabIndex = 39;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Fans";
            // 
            // checkBox_led0
            // 
            this.checkBox_led0.AutoSize = true;
            this.checkBox_led0.Enabled = false;
            this.checkBox_led0.Location = new System.Drawing.Point(6, 22);
            this.checkBox_led0.Name = "checkBox_led0";
            this.checkBox_led0.Size = new System.Drawing.Size(57, 19);
            this.checkBox_led0.TabIndex = 40;
            this.checkBox_led0.Text = "LED_0";
            this.checkBox_led0.UseVisualStyleBackColor = true;
            this.checkBox_led0.CheckedChanged += new System.EventHandler(this.checkBox_led0_CheckedChanged);
            // 
            // checkBox_led2
            // 
            this.checkBox_led2.AutoSize = true;
            this.checkBox_led2.Location = new System.Drawing.Point(6, 72);
            this.checkBox_led2.Name = "checkBox_led2";
            this.checkBox_led2.Size = new System.Drawing.Size(57, 19);
            this.checkBox_led2.TabIndex = 41;
            this.checkBox_led2.Text = "LED_2";
            this.checkBox_led2.UseVisualStyleBackColor = true;
            this.checkBox_led2.CheckedChanged += new System.EventHandler(this.checkBox_led2_CheckedChanged);
            // 
            // checkBox_led1
            // 
            this.checkBox_led1.AutoSize = true;
            this.checkBox_led1.Enabled = false;
            this.checkBox_led1.Location = new System.Drawing.Point(6, 47);
            this.checkBox_led1.Name = "checkBox_led1";
            this.checkBox_led1.Size = new System.Drawing.Size(57, 19);
            this.checkBox_led1.TabIndex = 42;
            this.checkBox_led1.Text = "LED_1";
            this.checkBox_led1.UseVisualStyleBackColor = true;
            this.checkBox_led1.CheckedChanged += new System.EventHandler(this.checkBox_led1_CheckedChanged);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.checkBox_led1);
            this.groupBox6.Controls.Add(this.checkBox_led0);
            this.groupBox6.Controls.Add(this.checkBox_led2);
            this.groupBox6.Location = new System.Drawing.Point(713, 12);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(71, 100);
            this.groupBox6.TabIndex = 43;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "LEDs";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(534, 397);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 23);
            this.comboBox1.TabIndex = 44;
            // 
            // progressBar_mainMotor
            // 
            this.progressBar_mainMotor.Location = new System.Drawing.Point(13, 62);
            this.progressBar_mainMotor.Name = "progressBar_mainMotor";
            this.progressBar_mainMotor.Size = new System.Drawing.Size(201, 32);
            this.progressBar_mainMotor.Step = 1;
            this.progressBar_mainMotor.TabIndex = 45;
            // 
            // trackBar_mainMotorSpeed
            // 
            this.trackBar_mainMotorSpeed.Location = new System.Drawing.Point(13, 22);
            this.trackBar_mainMotorSpeed.Maximum = 100;
            this.trackBar_mainMotorSpeed.Name = "trackBar_mainMotorSpeed";
            this.trackBar_mainMotorSpeed.Size = new System.Drawing.Size(104, 45);
            this.trackBar_mainMotorSpeed.TabIndex = 46;
            // 
            // button_setMainMotorSpeed
            // 
            this.button_setMainMotorSpeed.Location = new System.Drawing.Point(139, 22);
            this.button_setMainMotorSpeed.Name = "button_setMainMotorSpeed";
            this.button_setMainMotorSpeed.Size = new System.Drawing.Size(75, 23);
            this.button_setMainMotorSpeed.TabIndex = 47;
            this.button_setMainMotorSpeed.Text = "Set speed";
            this.button_setMainMotorSpeed.UseVisualStyleBackColor = true;
            this.button_setMainMotorSpeed.Click += new System.EventHandler(this.button_setMainMotorSpeed_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.button_setMainMotorSpeed);
            this.groupBox7.Controls.Add(this.progressBar_mainMotor);
            this.groupBox7.Controls.Add(this.trackBar_mainMotorSpeed);
            this.groupBox7.Location = new System.Drawing.Point(180, 367);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(226, 100);
            this.groupBox7.TabIndex = 48;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Main motor";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1134, 647);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.checkBox_powerOut4);
            this.Controls.Add(this.checkBox_TiltSensor);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tempBox);
            this.Controls.Add(this.textBox_Log);
            this.Name = "Form1";
            this.Text = "RastoBot Control Panel";
            this.tempBox.ResumeLayout(false);
            this.tempBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_mainMotorSpeed)).EndInit();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        private Label label2;
        private Button button_Open;
        private ComboBox combo_Ports;
        private ComboBox combo_Speeds;
        private TextBox textBox_Log;
        private Button button_Disconnect;

        private RastoBot rastoBot = new RastoBot(serialPort);
        private GroupBox tempBox;
        private TextBox tb_temperature3;
        private TextBox tb_temperature2;
        private TextBox tb_temperature1;
        private TextBox tb_temperature0;

        Thread uiUpdater = new Thread(UiUpdater);
        private GroupBox groupBox1;
        private Label label6;
        private Label label5;
        private Label label4;
        private Label label3;
        private TextBox tb_humid3;
        private TextBox tb_humid2;
        private TextBox tb_humid1;
        private TextBox tb_humid0;
        private Label label8;
        private Label label7;
        private TextBox textBox_battVoltage;
        private TextBox textBox_ExtVoltage;
        private TextBox textBox_current0;
        private TextBox textBox_current1;
        private TextBox textBox_current2;
        private TextBox textBox_current3;
        private CheckBox checkBox_TiltSensor;
        private TextBox textBox_rain;
        private TextBox textBox_light;
        private CheckBox checkBox_powerOut0;
        private CheckBox checkBox_powerOut1;
        private CheckBox checkBox_powerOut2;
        private CheckBox checkBox_powerOut3;
        private CheckBox checkBox_powerOut4;
        private Button button1;
        private Label label9;
        private Label label10;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private Label label12;
        private Label label11;
        private Label label14;
        private Label label13;
        private Label label15;
        private Label label16;
        private GroupBox groupBox4;
        private CheckBox checkBox1;
        private GroupBox groupBox5;
        private CheckBox checkBox_led0;
        private CheckBox checkBox_led2;
        private CheckBox checkBox_led1;
        private GroupBox groupBox6;
        private ComboBox comboBox1;
        private ProgressBar progressBar_mainMotor;
        private TrackBar trackBar_mainMotorSpeed;
        private Button button_setMainMotorSpeed;
        private GroupBox groupBox7;
    }
}