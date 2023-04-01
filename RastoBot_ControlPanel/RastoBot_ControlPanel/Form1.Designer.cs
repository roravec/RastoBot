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
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label28 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
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
            this.comboBox_Stepper = new System.Windows.Forms.ComboBox();
            this.progressBar_mainMotor = new System.Windows.Forms.ProgressBar();
            this.trackBar_mainMotorSpeed = new System.Windows.Forms.TrackBar();
            this.button_setMainMotorSpeed = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.button_stepperStop = new System.Windows.Forms.Button();
            this.button_stepperStepsToMake = new System.Windows.Forms.Button();
            this.button_StepperInit = new System.Windows.Forms.Button();
            this.button_stepperSpeed = new System.Windows.Forms.Button();
            this.button_stepperDirMode = new System.Windows.Forms.Button();
            this.button_stepperStepMode = new System.Windows.Forms.Button();
            this.button_stepperOperMode = new System.Windows.Forms.Button();
            this.button_StepperDisable = new System.Windows.Forms.Button();
            this.button_stepperEnable = new System.Windows.Forms.Button();
            this.label22 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.textBox_stepperStepsToMake = new System.Windows.Forms.TextBox();
            this.textBox_steperSpeed = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.comboBox_direction = new System.Windows.Forms.ComboBox();
            this.comboBox_stepMode = new System.Windows.Forms.ComboBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.comboBox_OperMode = new System.Windows.Forms.ComboBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.checkBox_s2move = new System.Windows.Forms.CheckBox();
            this.checkBox_s1move = new System.Windows.Forms.CheckBox();
            this.button_initWheels = new System.Windows.Forms.Button();
            this.button_wheelsStepsToMakeApply = new System.Windows.Forms.Button();
            this.checkBox_s0move = new System.Windows.Forms.CheckBox();
            this.button_wheelsApplySpeed = new System.Windows.Forms.Button();
            this.textBox_wheelsSpeed = new System.Windows.Forms.TextBox();
            this.label23 = new System.Windows.Forms.Label();
            this.textBox_wheelsStepsToMake = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.button_levelingGoTo = new System.Windows.Forms.Button();
            this.button_levelingRefRun = new System.Windows.Forms.Button();
            this.textBox_levelingGoToPos = new System.Windows.Forms.TextBox();
            this.label31 = new System.Windows.Forms.Label();
            this.button_demo1 = new System.Windows.Forms.Button();
            this.button_demo2 = new System.Windows.Forms.Button();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.label45 = new System.Windows.Forms.Label();
            this.textBox_azimuth = new System.Windows.Forms.TextBox();
            this.label46 = new System.Windows.Forms.Label();
            this.textBox_perimWire = new System.Windows.Forms.TextBox();
            this.label37 = new System.Windows.Forms.Label();
            this.label38 = new System.Windows.Forms.Label();
            this.textBox_accel_Y = new System.Windows.Forms.TextBox();
            this.label42 = new System.Windows.Forms.Label();
            this.textBox_accel_Z = new System.Windows.Forms.TextBox();
            this.label43 = new System.Windows.Forms.Label();
            this.textBox_accel_X = new System.Windows.Forms.TextBox();
            this.label33 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.textBox_gyro_Y = new System.Windows.Forms.TextBox();
            this.label35 = new System.Windows.Forms.Label();
            this.textBox_gyro_Z = new System.Windows.Forms.TextBox();
            this.label36 = new System.Windows.Forms.Label();
            this.textBox_gyro_X = new System.Windows.Forms.TextBox();
            this.label41 = new System.Windows.Forms.Label();
            this.label40 = new System.Windows.Forms.Label();
            this.textBox_compass_Y = new System.Windows.Forms.TextBox();
            this.label39 = new System.Windows.Forms.Label();
            this.textBox_compass_Z = new System.Windows.Forms.TextBox();
            this.label32 = new System.Windows.Forms.Label();
            this.textBox_compass_X = new System.Windows.Forms.TextBox();
            this.groupBox14 = new System.Windows.Forms.GroupBox();
            this.label47 = new System.Windows.Forms.Label();
            this.textBox_gpsSatellites = new System.Windows.Forms.TextBox();
            this.textBox_gpsHour = new System.Windows.Forms.TextBox();
            this.label61 = new System.Windows.Forms.Label();
            this.textBox_gpsLat = new System.Windows.Forms.TextBox();
            this.textBox_gpsSec = new System.Windows.Forms.TextBox();
            this.label49 = new System.Windows.Forms.Label();
            this.label60 = new System.Windows.Forms.Label();
            this.label48 = new System.Windows.Forms.Label();
            this.textBox_gpsAlt = new System.Windows.Forms.TextBox();
            this.textBox_gpsMin = new System.Windows.Forms.TextBox();
            this.label59 = new System.Windows.Forms.Label();
            this.textBox_gpsLong = new System.Windows.Forms.TextBox();
            this.label51 = new System.Windows.Forms.Label();
            this.label58 = new System.Windows.Forms.Label();
            this.textBox_gpsSpeed = new System.Windows.Forms.TextBox();
            this.textBox_gpsDay = new System.Windows.Forms.TextBox();
            this.label52 = new System.Windows.Forms.Label();
            this.label57 = new System.Windows.Forms.Label();
            this.textBox_gpsCourse = new System.Windows.Forms.TextBox();
            this.textBox_gpsYear = new System.Windows.Forms.TextBox();
            this.label53 = new System.Windows.Forms.Label();
            this.label56 = new System.Windows.Forms.Label();
            this.textBox_gpsMonth = new System.Windows.Forms.TextBox();
            this.label54 = new System.Windows.Forms.Label();
            this.label55 = new System.Windows.Forms.Label();
            this.groupBox15 = new System.Windows.Forms.GroupBox();
            this.label44 = new System.Windows.Forms.Label();
            this.tempBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_mainMotorSpeed)).BeginInit();
            this.groupBox7.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.groupBox13.SuspendLayout();
            this.groupBox14.SuspendLayout();
            this.groupBox15.SuspendLayout();
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
            this.combo_Ports.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
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
            this.textBox_Log.Location = new System.Drawing.Point(15, 23);
            this.textBox_Log.MaxLength = 10000;
            this.textBox_Log.Multiline = true;
            this.textBox_Log.Name = "textBox_Log";
            this.textBox_Log.Size = new System.Drawing.Size(366, 800);
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
            this.tempBox.Location = new System.Drawing.Point(12, 194);
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
            this.textBox_battVoltage.Size = new System.Drawing.Size(47, 23);
            this.textBox_battVoltage.TabIndex = 15;
            // 
            // textBox_ExtVoltage
            // 
            this.textBox_ExtVoltage.Location = new System.Drawing.Point(61, 55);
            this.textBox_ExtVoltage.Name = "textBox_ExtVoltage";
            this.textBox_ExtVoltage.ReadOnly = true;
            this.textBox_ExtVoltage.Size = new System.Drawing.Size(47, 23);
            this.textBox_ExtVoltage.TabIndex = 16;
            // 
            // textBox_current0
            // 
            this.textBox_current0.Location = new System.Drawing.Point(82, 27);
            this.textBox_current0.Name = "textBox_current0";
            this.textBox_current0.ReadOnly = true;
            this.textBox_current0.Size = new System.Drawing.Size(42, 23);
            this.textBox_current0.TabIndex = 17;
            // 
            // textBox_current1
            // 
            this.textBox_current1.Location = new System.Drawing.Point(82, 53);
            this.textBox_current1.Name = "textBox_current1";
            this.textBox_current1.ReadOnly = true;
            this.textBox_current1.Size = new System.Drawing.Size(42, 23);
            this.textBox_current1.TabIndex = 18;
            // 
            // textBox_current2
            // 
            this.textBox_current2.Location = new System.Drawing.Point(82, 82);
            this.textBox_current2.Name = "textBox_current2";
            this.textBox_current2.ReadOnly = true;
            this.textBox_current2.Size = new System.Drawing.Size(42, 23);
            this.textBox_current2.TabIndex = 19;
            // 
            // textBox_current3
            // 
            this.textBox_current3.Location = new System.Drawing.Point(82, 111);
            this.textBox_current3.Name = "textBox_current3";
            this.textBox_current3.ReadOnly = true;
            this.textBox_current3.Size = new System.Drawing.Size(42, 23);
            this.textBox_current3.TabIndex = 20;
            // 
            // checkBox_TiltSensor
            // 
            this.checkBox_TiltSensor.AutoSize = true;
            this.checkBox_TiltSensor.Enabled = false;
            this.checkBox_TiltSensor.Location = new System.Drawing.Point(14, 23);
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
            this.checkBox_powerOut0.CheckedChanged += new System.EventHandler(this.checkBox_powerOut0_CheckedChanged);
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
            this.checkBox_powerOut1.CheckedChanged += new System.EventHandler(this.checkBox_powerOut1_CheckedChanged);
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
            this.checkBox_powerOut2.CheckedChanged += new System.EventHandler(this.checkBox_powerOut2_CheckedChanged);
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
            this.checkBox_powerOut3.CheckedChanged += new System.EventHandler(this.checkBox_powerOut3_CheckedChanged);
            // 
            // checkBox_powerOut4
            // 
            this.checkBox_powerOut4.AutoSize = true;
            this.checkBox_powerOut4.Location = new System.Drawing.Point(14, 48);
            this.checkBox_powerOut4.Name = "checkBox_powerOut4";
            this.checkBox_powerOut4.Size = new System.Drawing.Size(112, 19);
            this.checkBox_powerOut4.TabIndex = 28;
            this.checkBox_powerOut4.Text = "Emergency light";
            this.checkBox_powerOut4.UseVisualStyleBackColor = true;
            this.checkBox_powerOut4.CheckedChanged += new System.EventHandler(this.checkBox_powerOut4_CheckedChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(604, 20);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(98, 51);
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
            this.groupBox2.Controls.Add(this.label30);
            this.groupBox2.Controls.Add(this.label29);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.textBox_battVoltage);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.textBox_ExtVoltage);
            this.groupBox2.Location = new System.Drawing.Point(12, 88);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(133, 90);
            this.groupBox2.TabIndex = 31;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Voltages";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(108, 63);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(14, 15);
            this.label30.TabIndex = 40;
            this.label30.Text = "V";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(108, 34);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(14, 15);
            this.label29.TabIndex = 39;
            this.label29.Text = "V";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label28);
            this.groupBox3.Controls.Add(this.label27);
            this.groupBox3.Controls.Add(this.label26);
            this.groupBox3.Controls.Add(this.label25);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.textBox_current3);
            this.groupBox3.Controls.Add(this.textBox_current0);
            this.groupBox3.Controls.Add(this.textBox_current1);
            this.groupBox3.Controls.Add(this.textBox_current2);
            this.groupBox3.Location = new System.Drawing.Point(339, 635);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(162, 143);
            this.groupBox3.TabIndex = 32;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Current sensors";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(124, 119);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(26, 15);
            this.label28.TabIndex = 38;
            this.label28.Text = "mA";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(124, 90);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(26, 15);
            this.label27.TabIndex = 37;
            this.label27.Text = "mA";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(124, 61);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(26, 15);
            this.label26.TabIndex = 36;
            this.label26.Text = "mA";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(124, 35);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(26, 15);
            this.label25.TabIndex = 35;
            this.label25.Text = "mA";
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
            this.groupBox4.Location = new System.Drawing.Point(542, 88);
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
            this.checkBox1.Size = new System.Drawing.Size(66, 19);
            this.checkBox1.TabIndex = 38;
            this.checkBox1.Text = "Manual";
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
            this.groupBox5.Location = new System.Drawing.Point(614, 194);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(88, 172);
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
            this.groupBox6.Location = new System.Drawing.Point(584, 517);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(71, 100);
            this.groupBox6.TabIndex = 43;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "LEDs";
            // 
            // comboBox_Stepper
            // 
            this.comboBox_Stepper.AutoCompleteCustomSource.AddRange(new string[] {
            "Wheel 1",
            "Wheel 2",
            "Leveling"});
            this.comboBox_Stepper.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_Stepper.FormattingEnabled = true;
            this.comboBox_Stepper.Items.AddRange(new object[] {
            "Wheel_L",
            "Wheel_R",
            "Leveling"});
            this.comboBox_Stepper.Location = new System.Drawing.Point(71, 22);
            this.comboBox_Stepper.Name = "comboBox_Stepper";
            this.comboBox_Stepper.Size = new System.Drawing.Size(153, 23);
            this.comboBox_Stepper.TabIndex = 44;
            // 
            // progressBar_mainMotor
            // 
            this.progressBar_mainMotor.Location = new System.Drawing.Point(13, 62);
            this.progressBar_mainMotor.Name = "progressBar_mainMotor";
            this.progressBar_mainMotor.Size = new System.Drawing.Size(201, 28);
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
            this.groupBox7.Location = new System.Drawing.Point(339, 517);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(226, 100);
            this.groupBox7.TabIndex = 48;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Main motor";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.button_stepperStop);
            this.groupBox8.Controls.Add(this.button_stepperStepsToMake);
            this.groupBox8.Controls.Add(this.button_StepperInit);
            this.groupBox8.Controls.Add(this.button_stepperSpeed);
            this.groupBox8.Controls.Add(this.button_stepperDirMode);
            this.groupBox8.Controls.Add(this.button_stepperStepMode);
            this.groupBox8.Controls.Add(this.button_stepperOperMode);
            this.groupBox8.Controls.Add(this.button_StepperDisable);
            this.groupBox8.Controls.Add(this.button_stepperEnable);
            this.groupBox8.Controls.Add(this.label22);
            this.groupBox8.Controls.Add(this.label21);
            this.groupBox8.Controls.Add(this.textBox_stepperStepsToMake);
            this.groupBox8.Controls.Add(this.textBox_steperSpeed);
            this.groupBox8.Controls.Add(this.label20);
            this.groupBox8.Controls.Add(this.label19);
            this.groupBox8.Controls.Add(this.comboBox_direction);
            this.groupBox8.Controls.Add(this.comboBox_stepMode);
            this.groupBox8.Controls.Add(this.label18);
            this.groupBox8.Controls.Add(this.label17);
            this.groupBox8.Controls.Add(this.comboBox_OperMode);
            this.groupBox8.Controls.Add(this.comboBox_Stepper);
            this.groupBox8.Location = new System.Drawing.Point(12, 381);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(315, 236);
            this.groupBox8.TabIndex = 49;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Individual stepper motor control";
            // 
            // button_stepperStop
            // 
            this.button_stepperStop.Location = new System.Drawing.Point(157, 51);
            this.button_stepperStop.Name = "button_stepperStop";
            this.button_stepperStop.Size = new System.Drawing.Size(67, 23);
            this.button_stepperStop.TabIndex = 62;
            this.button_stepperStop.Text = "Stop";
            this.button_stepperStop.UseVisualStyleBackColor = true;
            this.button_stepperStop.Click += new System.EventHandler(this.button_stepperStop_Click);
            // 
            // button_stepperStepsToMake
            // 
            this.button_stepperStepsToMake.Location = new System.Drawing.Point(231, 203);
            this.button_stepperStepsToMake.Name = "button_stepperStepsToMake";
            this.button_stepperStepsToMake.Size = new System.Drawing.Size(67, 23);
            this.button_stepperStepsToMake.TabIndex = 61;
            this.button_stepperStepsToMake.Text = "Apply";
            this.button_stepperStepsToMake.UseVisualStyleBackColor = true;
            this.button_stepperStepsToMake.Click += new System.EventHandler(this.button_stepperStepsToMake_Click);
            // 
            // button_StepperInit
            // 
            this.button_StepperInit.Location = new System.Drawing.Point(71, 51);
            this.button_StepperInit.Name = "button_StepperInit";
            this.button_StepperInit.Size = new System.Drawing.Size(77, 23);
            this.button_StepperInit.TabIndex = 63;
            this.button_StepperInit.Text = "Reset";
            this.button_StepperInit.UseVisualStyleBackColor = true;
            this.button_StepperInit.Click += new System.EventHandler(this.button_StepperInit_Click);
            // 
            // button_stepperSpeed
            // 
            this.button_stepperSpeed.Location = new System.Drawing.Point(231, 174);
            this.button_stepperSpeed.Name = "button_stepperSpeed";
            this.button_stepperSpeed.Size = new System.Drawing.Size(67, 23);
            this.button_stepperSpeed.TabIndex = 60;
            this.button_stepperSpeed.Text = "Apply";
            this.button_stepperSpeed.UseVisualStyleBackColor = true;
            this.button_stepperSpeed.Click += new System.EventHandler(this.button_stepperSpeed_Click);
            // 
            // button_stepperDirMode
            // 
            this.button_stepperDirMode.Location = new System.Drawing.Point(231, 145);
            this.button_stepperDirMode.Name = "button_stepperDirMode";
            this.button_stepperDirMode.Size = new System.Drawing.Size(67, 23);
            this.button_stepperDirMode.TabIndex = 59;
            this.button_stepperDirMode.Text = "Apply";
            this.button_stepperDirMode.UseVisualStyleBackColor = true;
            this.button_stepperDirMode.Click += new System.EventHandler(this.button_stepperDirMode_Click);
            // 
            // button_stepperStepMode
            // 
            this.button_stepperStepMode.Location = new System.Drawing.Point(231, 116);
            this.button_stepperStepMode.Name = "button_stepperStepMode";
            this.button_stepperStepMode.Size = new System.Drawing.Size(67, 23);
            this.button_stepperStepMode.TabIndex = 58;
            this.button_stepperStepMode.Text = "Apply";
            this.button_stepperStepMode.UseVisualStyleBackColor = true;
            this.button_stepperStepMode.Click += new System.EventHandler(this.button_stepperStepMode_Click);
            // 
            // button_stepperOperMode
            // 
            this.button_stepperOperMode.Location = new System.Drawing.Point(231, 87);
            this.button_stepperOperMode.Name = "button_stepperOperMode";
            this.button_stepperOperMode.Size = new System.Drawing.Size(67, 23);
            this.button_stepperOperMode.TabIndex = 57;
            this.button_stepperOperMode.Text = "Apply";
            this.button_stepperOperMode.UseVisualStyleBackColor = true;
            this.button_stepperOperMode.Click += new System.EventHandler(this.button_stepperOperMode_Click);
            // 
            // button_StepperDisable
            // 
            this.button_StepperDisable.Location = new System.Drawing.Point(231, 51);
            this.button_StepperDisable.Name = "button_StepperDisable";
            this.button_StepperDisable.Size = new System.Drawing.Size(67, 23);
            this.button_StepperDisable.TabIndex = 56;
            this.button_StepperDisable.Text = "Disable";
            this.button_StepperDisable.UseVisualStyleBackColor = true;
            this.button_StepperDisable.Click += new System.EventHandler(this.button_StepperDisable_Click);
            // 
            // button_stepperEnable
            // 
            this.button_stepperEnable.Location = new System.Drawing.Point(231, 21);
            this.button_stepperEnable.Name = "button_stepperEnable";
            this.button_stepperEnable.Size = new System.Drawing.Size(67, 23);
            this.button_stepperEnable.TabIndex = 55;
            this.button_stepperEnable.Text = "Enable";
            this.button_stepperEnable.UseVisualStyleBackColor = true;
            this.button_stepperEnable.Click += new System.EventHandler(this.button_stepperEnable_Click);
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(16, 206);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(81, 15);
            this.label22.TabIndex = 54;
            this.label22.Text = "Steps to make";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(58, 177);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(39, 15);
            this.label21.TabIndex = 53;
            this.label21.Text = "Speed";
            // 
            // textBox_stepperStepsToMake
            // 
            this.textBox_stepperStepsToMake.Location = new System.Drawing.Point(103, 203);
            this.textBox_stepperStepsToMake.Name = "textBox_stepperStepsToMake";
            this.textBox_stepperStepsToMake.PlaceholderText = "Number";
            this.textBox_stepperStepsToMake.Size = new System.Drawing.Size(121, 23);
            this.textBox_stepperStepsToMake.TabIndex = 52;
            this.textBox_stepperStepsToMake.Text = "1000";
            // 
            // textBox_steperSpeed
            // 
            this.textBox_steperSpeed.Location = new System.Drawing.Point(103, 174);
            this.textBox_steperSpeed.MaxLength = 4;
            this.textBox_steperSpeed.Name = "textBox_steperSpeed";
            this.textBox_steperSpeed.PlaceholderText = "Number";
            this.textBox_steperSpeed.Size = new System.Drawing.Size(121, 23);
            this.textBox_steperSpeed.TabIndex = 51;
            this.textBox_steperSpeed.Text = "1023";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(42, 145);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(55, 15);
            this.label20.TabIndex = 50;
            this.label20.Text = "Direction";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(33, 119);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(64, 15);
            this.label19.TabIndex = 49;
            this.label19.Text = "Step Mode";
            // 
            // comboBox_direction
            // 
            this.comboBox_direction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_direction.FormattingEnabled = true;
            this.comboBox_direction.Items.AddRange(new object[] {
            "CW",
            "CCW"});
            this.comboBox_direction.Location = new System.Drawing.Point(103, 145);
            this.comboBox_direction.Name = "comboBox_direction";
            this.comboBox_direction.Size = new System.Drawing.Size(121, 23);
            this.comboBox_direction.TabIndex = 48;
            // 
            // comboBox_stepMode
            // 
            this.comboBox_stepMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_stepMode.FormattingEnabled = true;
            this.comboBox_stepMode.Items.AddRange(new object[] {
            "Full",
            "Half",
            "Quarter",
            "Eighth"});
            this.comboBox_stepMode.Location = new System.Drawing.Point(103, 116);
            this.comboBox_stepMode.Name = "comboBox_stepMode";
            this.comboBox_stepMode.Size = new System.Drawing.Size(121, 23);
            this.comboBox_stepMode.TabIndex = 47;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(30, 90);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(67, 15);
            this.label18.TabIndex = 46;
            this.label18.Text = "Oper.Mode";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(25, 25);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(40, 15);
            this.label17.TabIndex = 15;
            this.label17.Text = "Motor";
            // 
            // comboBox_OperMode
            // 
            this.comboBox_OperMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_OperMode.FormattingEnabled = true;
            this.comboBox_OperMode.Items.AddRange(new object[] {
            "Continous",
            "On demand"});
            this.comboBox_OperMode.Location = new System.Drawing.Point(103, 87);
            this.comboBox_OperMode.Name = "comboBox_OperMode";
            this.comboBox_OperMode.Size = new System.Drawing.Size(121, 23);
            this.comboBox_OperMode.TabIndex = 45;
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.label44);
            this.groupBox9.Controls.Add(this.button_initWheels);
            this.groupBox9.Controls.Add(this.checkBox_s2move);
            this.groupBox9.Controls.Add(this.button_wheelsStepsToMakeApply);
            this.groupBox9.Controls.Add(this.checkBox_s1move);
            this.groupBox9.Controls.Add(this.button_wheelsApplySpeed);
            this.groupBox9.Controls.Add(this.textBox_wheelsSpeed);
            this.groupBox9.Controls.Add(this.label23);
            this.groupBox9.Controls.Add(this.textBox_wheelsStepsToMake);
            this.groupBox9.Controls.Add(this.checkBox_s0move);
            this.groupBox9.Controls.Add(this.label24);
            this.groupBox9.Location = new System.Drawing.Point(339, 381);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(363, 120);
            this.groupBox9.TabIndex = 50;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Wheels control";
            // 
            // checkBox_s2move
            // 
            this.checkBox_s2move.AutoSize = true;
            this.checkBox_s2move.Enabled = false;
            this.checkBox_s2move.Location = new System.Drawing.Point(201, 54);
            this.checkBox_s2move.Name = "checkBox_s2move";
            this.checkBox_s2move.Size = new System.Drawing.Size(38, 19);
            this.checkBox_s2move.TabIndex = 60;
            this.checkBox_s2move.Text = "S2";
            this.checkBox_s2move.UseVisualStyleBackColor = true;
            // 
            // checkBox_s1move
            // 
            this.checkBox_s1move.AutoSize = true;
            this.checkBox_s1move.Enabled = false;
            this.checkBox_s1move.Location = new System.Drawing.Point(157, 54);
            this.checkBox_s1move.Name = "checkBox_s1move";
            this.checkBox_s1move.Size = new System.Drawing.Size(38, 19);
            this.checkBox_s1move.TabIndex = 61;
            this.checkBox_s1move.Text = "S1";
            this.checkBox_s1move.UseVisualStyleBackColor = true;
            // 
            // button_initWheels
            // 
            this.button_initWheels.Location = new System.Drawing.Point(10, 22);
            this.button_initWheels.Name = "button_initWheels";
            this.button_initWheels.Size = new System.Drawing.Size(77, 23);
            this.button_initWheels.TabIndex = 69;
            this.button_initWheels.Text = "Init wheels";
            this.button_initWheels.UseVisualStyleBackColor = true;
            this.button_initWheels.Click += new System.EventHandler(this.button_initWheels_Click);
            // 
            // button_wheelsStepsToMakeApply
            // 
            this.button_wheelsStepsToMakeApply.Location = new System.Drawing.Point(233, 79);
            this.button_wheelsStepsToMakeApply.Name = "button_wheelsStepsToMakeApply";
            this.button_wheelsStepsToMakeApply.Size = new System.Drawing.Size(112, 31);
            this.button_wheelsStepsToMakeApply.TabIndex = 68;
            this.button_wheelsStepsToMakeApply.Text = "Apply";
            this.button_wheelsStepsToMakeApply.UseVisualStyleBackColor = true;
            this.button_wheelsStepsToMakeApply.Click += new System.EventHandler(this.button_wheelsStepsToMakeApply_Click);
            // 
            // checkBox_s0move
            // 
            this.checkBox_s0move.AutoSize = true;
            this.checkBox_s0move.Enabled = false;
            this.checkBox_s0move.Location = new System.Drawing.Point(113, 54);
            this.checkBox_s0move.Name = "checkBox_s0move";
            this.checkBox_s0move.Size = new System.Drawing.Size(38, 19);
            this.checkBox_s0move.TabIndex = 59;
            this.checkBox_s0move.Text = "S0";
            this.checkBox_s0move.UseVisualStyleBackColor = true;
            // 
            // button_wheelsApplySpeed
            // 
            this.button_wheelsApplySpeed.Location = new System.Drawing.Point(278, 23);
            this.button_wheelsApplySpeed.Name = "button_wheelsApplySpeed";
            this.button_wheelsApplySpeed.Size = new System.Drawing.Size(67, 23);
            this.button_wheelsApplySpeed.TabIndex = 67;
            this.button_wheelsApplySpeed.Text = "Apply";
            this.button_wheelsApplySpeed.UseVisualStyleBackColor = true;
            this.button_wheelsApplySpeed.Click += new System.EventHandler(this.button_wheelsApplySpeed_Click);
            // 
            // textBox_wheelsSpeed
            // 
            this.textBox_wheelsSpeed.Location = new System.Drawing.Point(214, 23);
            this.textBox_wheelsSpeed.MaxLength = 4;
            this.textBox_wheelsSpeed.Name = "textBox_wheelsSpeed";
            this.textBox_wheelsSpeed.PlaceholderText = "Number";
            this.textBox_wheelsSpeed.Size = new System.Drawing.Size(58, 23);
            this.textBox_wheelsSpeed.TabIndex = 63;
            this.textBox_wheelsSpeed.Text = "1023";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(73, 87);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(81, 15);
            this.label23.TabIndex = 66;
            this.label23.Text = "Steps to make";
            // 
            // textBox_wheelsStepsToMake
            // 
            this.textBox_wheelsStepsToMake.Location = new System.Drawing.Point(160, 84);
            this.textBox_wheelsStepsToMake.Name = "textBox_wheelsStepsToMake";
            this.textBox_wheelsStepsToMake.PlaceholderText = "Number";
            this.textBox_wheelsStepsToMake.Size = new System.Drawing.Size(59, 23);
            this.textBox_wheelsStepsToMake.TabIndex = 64;
            this.textBox_wheelsStepsToMake.Text = "1000";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(169, 26);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(39, 15);
            this.label24.TabIndex = 65;
            this.label24.Text = "Speed";
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.checkBox_powerOut4);
            this.groupBox10.Controls.Add(this.checkBox_TiltSensor);
            this.groupBox10.Location = new System.Drawing.Point(392, 88);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(131, 90);
            this.groupBox10.TabIndex = 51;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "Other sensors";
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.textBox_Log);
            this.groupBox11.Location = new System.Drawing.Point(729, 12);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(396, 838);
            this.groupBox11.TabIndex = 52;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Raw inbound data";
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.button_levelingGoTo);
            this.groupBox12.Controls.Add(this.button_levelingRefRun);
            this.groupBox12.Controls.Add(this.textBox_levelingGoToPos);
            this.groupBox12.Controls.Add(this.label31);
            this.groupBox12.Location = new System.Drawing.Point(166, 88);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(208, 90);
            this.groupBox12.TabIndex = 53;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "Leveling";
            // 
            // button_levelingGoTo
            // 
            this.button_levelingGoTo.Location = new System.Drawing.Point(111, 55);
            this.button_levelingGoTo.Name = "button_levelingGoTo";
            this.button_levelingGoTo.Size = new System.Drawing.Size(67, 23);
            this.button_levelingGoTo.TabIndex = 72;
            this.button_levelingGoTo.Text = "Go";
            this.button_levelingGoTo.UseVisualStyleBackColor = true;
            this.button_levelingGoTo.Click += new System.EventHandler(this.button_levelingGoTo_Click);
            // 
            // button_levelingRefRun
            // 
            this.button_levelingRefRun.Location = new System.Drawing.Point(90, 0);
            this.button_levelingRefRun.Name = "button_levelingRefRun";
            this.button_levelingRefRun.Size = new System.Drawing.Size(101, 23);
            this.button_levelingRefRun.TabIndex = 73;
            this.button_levelingRefRun.Text = "Reference run";
            this.button_levelingRefRun.UseVisualStyleBackColor = true;
            this.button_levelingRefRun.Click += new System.EventHandler(this.button_levelingRefRun_Click);
            // 
            // textBox_levelingGoToPos
            // 
            this.textBox_levelingGoToPos.Location = new System.Drawing.Point(13, 56);
            this.textBox_levelingGoToPos.MaxLength = 4;
            this.textBox_levelingGoToPos.Name = "textBox_levelingGoToPos";
            this.textBox_levelingGoToPos.PlaceholderText = "Number";
            this.textBox_levelingGoToPos.Size = new System.Drawing.Size(65, 23);
            this.textBox_levelingGoToPos.TabIndex = 70;
            this.textBox_levelingGoToPos.Text = "20";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(13, 38);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(125, 15);
            this.label31.TabIndex = 71;
            this.label31.Text = "Go to position (0 - 20):";
            // 
            // button_demo1
            // 
            this.button_demo1.Location = new System.Drawing.Point(13, 22);
            this.button_demo1.Name = "button_demo1";
            this.button_demo1.Size = new System.Drawing.Size(60, 29);
            this.button_demo1.TabIndex = 54;
            this.button_demo1.Text = "Demo 1";
            this.button_demo1.UseVisualStyleBackColor = true;
            this.button_demo1.Click += new System.EventHandler(this.button_demo1_Click);
            // 
            // button_demo2
            // 
            this.button_demo2.Location = new System.Drawing.Point(91, 23);
            this.button_demo2.Name = "button_demo2";
            this.button_demo2.Size = new System.Drawing.Size(60, 28);
            this.button_demo2.TabIndex = 55;
            this.button_demo2.Text = "Demo 2";
            this.button_demo2.UseVisualStyleBackColor = true;
            this.button_demo2.Click += new System.EventHandler(this.button_demo2_Click);
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.label45);
            this.groupBox13.Controls.Add(this.textBox_azimuth);
            this.groupBox13.Controls.Add(this.label46);
            this.groupBox13.Controls.Add(this.textBox_perimWire);
            this.groupBox13.Controls.Add(this.label37);
            this.groupBox13.Controls.Add(this.label38);
            this.groupBox13.Controls.Add(this.textBox_accel_Y);
            this.groupBox13.Controls.Add(this.label42);
            this.groupBox13.Controls.Add(this.textBox_accel_Z);
            this.groupBox13.Controls.Add(this.label43);
            this.groupBox13.Controls.Add(this.textBox_accel_X);
            this.groupBox13.Controls.Add(this.label33);
            this.groupBox13.Controls.Add(this.label34);
            this.groupBox13.Controls.Add(this.textBox_gyro_Y);
            this.groupBox13.Controls.Add(this.label35);
            this.groupBox13.Controls.Add(this.textBox_gyro_Z);
            this.groupBox13.Controls.Add(this.label36);
            this.groupBox13.Controls.Add(this.textBox_gyro_X);
            this.groupBox13.Controls.Add(this.label41);
            this.groupBox13.Controls.Add(this.label40);
            this.groupBox13.Controls.Add(this.textBox_compass_Y);
            this.groupBox13.Controls.Add(this.label39);
            this.groupBox13.Controls.Add(this.textBox_compass_Z);
            this.groupBox13.Controls.Add(this.label32);
            this.groupBox13.Controls.Add(this.textBox_compass_X);
            this.groupBox13.Location = new System.Drawing.Point(288, 194);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(306, 172);
            this.groupBox13.TabIndex = 56;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "Gyroscope data";
            // 
            // label45
            // 
            this.label45.AutoSize = true;
            this.label45.Location = new System.Drawing.Point(165, 136);
            this.label45.Name = "label45";
            this.label45.Size = new System.Drawing.Size(52, 15);
            this.label45.TabIndex = 67;
            this.label45.Text = "Azimuth";
            // 
            // textBox_azimuth
            // 
            this.textBox_azimuth.Location = new System.Drawing.Point(228, 133);
            this.textBox_azimuth.Name = "textBox_azimuth";
            this.textBox_azimuth.ReadOnly = true;
            this.textBox_azimuth.Size = new System.Drawing.Size(42, 23);
            this.textBox_azimuth.TabIndex = 66;
            // 
            // label46
            // 
            this.label46.AutoSize = true;
            this.label46.Location = new System.Drawing.Point(23, 136);
            this.label46.Name = "label46";
            this.label46.Size = new System.Drawing.Size(66, 15);
            this.label46.TabIndex = 65;
            this.label46.Text = "Perim. wire";
            // 
            // textBox_perimWire
            // 
            this.textBox_perimWire.Location = new System.Drawing.Point(100, 133);
            this.textBox_perimWire.Name = "textBox_perimWire";
            this.textBox_perimWire.ReadOnly = true;
            this.textBox_perimWire.Size = new System.Drawing.Size(42, 23);
            this.textBox_perimWire.TabIndex = 64;
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Location = new System.Drawing.Point(23, 100);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(39, 15);
            this.label37.TabIndex = 59;
            this.label37.Text = "Accel.";
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Location = new System.Drawing.Point(151, 100);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(14, 15);
            this.label38.TabIndex = 63;
            this.label38.Text = "Y";
            // 
            // textBox_accel_Y
            // 
            this.textBox_accel_Y.Location = new System.Drawing.Point(171, 97);
            this.textBox_accel_Y.Name = "textBox_accel_Y";
            this.textBox_accel_Y.ReadOnly = true;
            this.textBox_accel_Y.Size = new System.Drawing.Size(42, 23);
            this.textBox_accel_Y.TabIndex = 62;
            // 
            // label42
            // 
            this.label42.AutoSize = true;
            this.label42.Location = new System.Drawing.Point(228, 100);
            this.label42.Name = "label42";
            this.label42.Size = new System.Drawing.Size(14, 15);
            this.label42.TabIndex = 61;
            this.label42.Text = "Z";
            // 
            // textBox_accel_Z
            // 
            this.textBox_accel_Z.Location = new System.Drawing.Point(248, 97);
            this.textBox_accel_Z.Name = "textBox_accel_Z";
            this.textBox_accel_Z.ReadOnly = true;
            this.textBox_accel_Z.Size = new System.Drawing.Size(42, 23);
            this.textBox_accel_Z.TabIndex = 60;
            // 
            // label43
            // 
            this.label43.AutoSize = true;
            this.label43.Location = new System.Drawing.Point(80, 100);
            this.label43.Name = "label43";
            this.label43.Size = new System.Drawing.Size(14, 15);
            this.label43.TabIndex = 58;
            this.label43.Text = "X";
            // 
            // textBox_accel_X
            // 
            this.textBox_accel_X.Location = new System.Drawing.Point(100, 97);
            this.textBox_accel_X.Name = "textBox_accel_X";
            this.textBox_accel_X.ReadOnly = true;
            this.textBox_accel_X.Size = new System.Drawing.Size(42, 23);
            this.textBox_accel_X.TabIndex = 57;
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(30, 66);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(32, 15);
            this.label33.TabIndex = 52;
            this.label33.Text = "Gyro";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(151, 66);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(14, 15);
            this.label34.TabIndex = 56;
            this.label34.Text = "Y";
            // 
            // textBox_gyro_Y
            // 
            this.textBox_gyro_Y.Location = new System.Drawing.Point(171, 63);
            this.textBox_gyro_Y.Name = "textBox_gyro_Y";
            this.textBox_gyro_Y.ReadOnly = true;
            this.textBox_gyro_Y.Size = new System.Drawing.Size(42, 23);
            this.textBox_gyro_Y.TabIndex = 55;
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(228, 66);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(14, 15);
            this.label35.TabIndex = 54;
            this.label35.Text = "Z";
            // 
            // textBox_gyro_Z
            // 
            this.textBox_gyro_Z.Location = new System.Drawing.Point(248, 63);
            this.textBox_gyro_Z.Name = "textBox_gyro_Z";
            this.textBox_gyro_Z.ReadOnly = true;
            this.textBox_gyro_Z.Size = new System.Drawing.Size(42, 23);
            this.textBox_gyro_Z.TabIndex = 53;
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Location = new System.Drawing.Point(80, 66);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(14, 15);
            this.label36.TabIndex = 51;
            this.label36.Text = "X";
            // 
            // textBox_gyro_X
            // 
            this.textBox_gyro_X.Location = new System.Drawing.Point(100, 63);
            this.textBox_gyro_X.Name = "textBox_gyro_X";
            this.textBox_gyro_X.ReadOnly = true;
            this.textBox_gyro_X.Size = new System.Drawing.Size(42, 23);
            this.textBox_gyro_X.TabIndex = 50;
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Location = new System.Drawing.Point(6, 30);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(56, 15);
            this.label41.TabIndex = 39;
            this.label41.Text = "Compass";
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Location = new System.Drawing.Point(151, 30);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(14, 15);
            this.label40.TabIndex = 49;
            this.label40.Text = "Y";
            // 
            // textBox_compass_Y
            // 
            this.textBox_compass_Y.Location = new System.Drawing.Point(171, 27);
            this.textBox_compass_Y.Name = "textBox_compass_Y";
            this.textBox_compass_Y.ReadOnly = true;
            this.textBox_compass_Y.Size = new System.Drawing.Size(42, 23);
            this.textBox_compass_Y.TabIndex = 48;
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Location = new System.Drawing.Point(228, 30);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(14, 15);
            this.label39.TabIndex = 47;
            this.label39.Text = "Z";
            // 
            // textBox_compass_Z
            // 
            this.textBox_compass_Z.Location = new System.Drawing.Point(248, 27);
            this.textBox_compass_Z.Name = "textBox_compass_Z";
            this.textBox_compass_Z.ReadOnly = true;
            this.textBox_compass_Z.Size = new System.Drawing.Size(42, 23);
            this.textBox_compass_Z.TabIndex = 46;
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(80, 30);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(14, 15);
            this.label32.TabIndex = 33;
            this.label32.Text = "X";
            // 
            // textBox_compass_X
            // 
            this.textBox_compass_X.Location = new System.Drawing.Point(100, 27);
            this.textBox_compass_X.Name = "textBox_compass_X";
            this.textBox_compass_X.ReadOnly = true;
            this.textBox_compass_X.Size = new System.Drawing.Size(42, 23);
            this.textBox_compass_X.TabIndex = 32;
            // 
            // groupBox14
            // 
            this.groupBox14.Controls.Add(this.label47);
            this.groupBox14.Controls.Add(this.textBox_gpsSatellites);
            this.groupBox14.Controls.Add(this.textBox_gpsHour);
            this.groupBox14.Controls.Add(this.label61);
            this.groupBox14.Controls.Add(this.textBox_gpsLat);
            this.groupBox14.Controls.Add(this.textBox_gpsSec);
            this.groupBox14.Controls.Add(this.label49);
            this.groupBox14.Controls.Add(this.label60);
            this.groupBox14.Controls.Add(this.label48);
            this.groupBox14.Controls.Add(this.textBox_gpsAlt);
            this.groupBox14.Controls.Add(this.textBox_gpsMin);
            this.groupBox14.Controls.Add(this.label59);
            this.groupBox14.Controls.Add(this.textBox_gpsLong);
            this.groupBox14.Controls.Add(this.label51);
            this.groupBox14.Controls.Add(this.label58);
            this.groupBox14.Controls.Add(this.textBox_gpsSpeed);
            this.groupBox14.Controls.Add(this.textBox_gpsDay);
            this.groupBox14.Controls.Add(this.label52);
            this.groupBox14.Controls.Add(this.label57);
            this.groupBox14.Controls.Add(this.textBox_gpsCourse);
            this.groupBox14.Controls.Add(this.textBox_gpsYear);
            this.groupBox14.Controls.Add(this.label53);
            this.groupBox14.Controls.Add(this.label56);
            this.groupBox14.Controls.Add(this.textBox_gpsMonth);
            this.groupBox14.Controls.Add(this.label54);
            this.groupBox14.Controls.Add(this.label55);
            this.groupBox14.Location = new System.Drawing.Point(12, 635);
            this.groupBox14.Name = "groupBox14";
            this.groupBox14.Size = new System.Drawing.Size(315, 215);
            this.groupBox14.TabIndex = 57;
            this.groupBox14.TabStop = false;
            this.groupBox14.Text = "GPS";
            // 
            // label47
            // 
            this.label47.AutoSize = true;
            this.label47.Location = new System.Drawing.Point(28, 59);
            this.label47.Name = "label47";
            this.label47.Size = new System.Drawing.Size(26, 15);
            this.label47.TabIndex = 96;
            this.label47.Text = "Lat.";
            // 
            // textBox_gpsSatellites
            // 
            this.textBox_gpsSatellites.Location = new System.Drawing.Point(80, 22);
            this.textBox_gpsSatellites.Name = "textBox_gpsSatellites";
            this.textBox_gpsSatellites.ReadOnly = true;
            this.textBox_gpsSatellites.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsSatellites.TabIndex = 84;
            // 
            // textBox_gpsHour
            // 
            this.textBox_gpsHour.Location = new System.Drawing.Point(68, 141);
            this.textBox_gpsHour.Name = "textBox_gpsHour";
            this.textBox_gpsHour.ReadOnly = true;
            this.textBox_gpsHour.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsHour.TabIndex = 70;
            // 
            // label61
            // 
            this.label61.AutoSize = true;
            this.label61.Location = new System.Drawing.Point(48, 144);
            this.label61.Name = "label61";
            this.label61.Size = new System.Drawing.Size(16, 15);
            this.label61.TabIndex = 71;
            this.label61.Text = "H";
            // 
            // textBox_gpsLat
            // 
            this.textBox_gpsLat.Location = new System.Drawing.Point(60, 55);
            this.textBox_gpsLat.Name = "textBox_gpsLat";
            this.textBox_gpsLat.ReadOnly = true;
            this.textBox_gpsLat.Size = new System.Drawing.Size(95, 23);
            this.textBox_gpsLat.TabIndex = 95;
            // 
            // textBox_gpsSec
            // 
            this.textBox_gpsSec.Location = new System.Drawing.Point(216, 141);
            this.textBox_gpsSec.Name = "textBox_gpsSec";
            this.textBox_gpsSec.ReadOnly = true;
            this.textBox_gpsSec.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsSec.TabIndex = 73;
            // 
            // label49
            // 
            this.label49.AutoSize = true;
            this.label49.Location = new System.Drawing.Point(161, 26);
            this.label49.Name = "label49";
            this.label49.Size = new System.Drawing.Size(49, 15);
            this.label49.TabIndex = 92;
            this.label49.Text = "Altitude";
            // 
            // label60
            // 
            this.label60.AutoSize = true;
            this.label60.Location = new System.Drawing.Point(196, 144);
            this.label60.Name = "label60";
            this.label60.Size = new System.Drawing.Size(12, 15);
            this.label60.TabIndex = 74;
            this.label60.Text = "s";
            // 
            // label48
            // 
            this.label48.AutoSize = true;
            this.label48.Location = new System.Drawing.Point(17, 87);
            this.label48.Name = "label48";
            this.label48.Size = new System.Drawing.Size(37, 15);
            this.label48.TabIndex = 94;
            this.label48.Text = "Long.";
            // 
            // textBox_gpsAlt
            // 
            this.textBox_gpsAlt.Location = new System.Drawing.Point(216, 22);
            this.textBox_gpsAlt.Name = "textBox_gpsAlt";
            this.textBox_gpsAlt.ReadOnly = true;
            this.textBox_gpsAlt.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsAlt.TabIndex = 91;
            // 
            // textBox_gpsMin
            // 
            this.textBox_gpsMin.Location = new System.Drawing.Point(139, 141);
            this.textBox_gpsMin.Name = "textBox_gpsMin";
            this.textBox_gpsMin.ReadOnly = true;
            this.textBox_gpsMin.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsMin.TabIndex = 75;
            // 
            // label59
            // 
            this.label59.AutoSize = true;
            this.label59.Location = new System.Drawing.Point(119, 144);
            this.label59.Name = "label59";
            this.label59.Size = new System.Drawing.Size(18, 15);
            this.label59.TabIndex = 76;
            this.label59.Text = "M";
            // 
            // textBox_gpsLong
            // 
            this.textBox_gpsLong.Location = new System.Drawing.Point(60, 84);
            this.textBox_gpsLong.Name = "textBox_gpsLong";
            this.textBox_gpsLong.ReadOnly = true;
            this.textBox_gpsLong.Size = new System.Drawing.Size(95, 23);
            this.textBox_gpsLong.TabIndex = 93;
            // 
            // label51
            // 
            this.label51.AutoSize = true;
            this.label51.Location = new System.Drawing.Point(169, 88);
            this.label51.Name = "label51";
            this.label51.Size = new System.Drawing.Size(39, 15);
            this.label51.TabIndex = 90;
            this.label51.Text = "Speed";
            // 
            // label58
            // 
            this.label58.AutoSize = true;
            this.label58.Location = new System.Drawing.Point(8, 144);
            this.label58.Name = "label58";
            this.label58.Size = new System.Drawing.Size(33, 15);
            this.label58.TabIndex = 72;
            this.label58.Text = "Time";
            // 
            // textBox_gpsSpeed
            // 
            this.textBox_gpsSpeed.Location = new System.Drawing.Point(216, 84);
            this.textBox_gpsSpeed.Name = "textBox_gpsSpeed";
            this.textBox_gpsSpeed.ReadOnly = true;
            this.textBox_gpsSpeed.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsSpeed.TabIndex = 89;
            // 
            // textBox_gpsDay
            // 
            this.textBox_gpsDay.Location = new System.Drawing.Point(68, 177);
            this.textBox_gpsDay.Name = "textBox_gpsDay";
            this.textBox_gpsDay.ReadOnly = true;
            this.textBox_gpsDay.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsDay.TabIndex = 77;
            // 
            // label52
            // 
            this.label52.AutoSize = true;
            this.label52.Location = new System.Drawing.Point(166, 55);
            this.label52.Name = "label52";
            this.label52.Size = new System.Drawing.Size(44, 15);
            this.label52.TabIndex = 88;
            this.label52.Text = "Course";
            // 
            // label57
            // 
            this.label57.AutoSize = true;
            this.label57.Location = new System.Drawing.Point(48, 180);
            this.label57.Name = "label57";
            this.label57.Size = new System.Drawing.Size(15, 15);
            this.label57.TabIndex = 78;
            this.label57.Text = "D";
            // 
            // textBox_gpsCourse
            // 
            this.textBox_gpsCourse.Location = new System.Drawing.Point(216, 55);
            this.textBox_gpsCourse.Name = "textBox_gpsCourse";
            this.textBox_gpsCourse.ReadOnly = true;
            this.textBox_gpsCourse.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsCourse.TabIndex = 87;
            // 
            // textBox_gpsYear
            // 
            this.textBox_gpsYear.Location = new System.Drawing.Point(216, 177);
            this.textBox_gpsYear.Name = "textBox_gpsYear";
            this.textBox_gpsYear.ReadOnly = true;
            this.textBox_gpsYear.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsYear.TabIndex = 80;
            // 
            // label53
            // 
            this.label53.AutoSize = true;
            this.label53.Location = new System.Drawing.Point(13, 27);
            this.label53.Name = "label53";
            this.label53.Size = new System.Drawing.Size(53, 15);
            this.label53.TabIndex = 85;
            this.label53.Text = "Satellites";
            // 
            // label56
            // 
            this.label56.AutoSize = true;
            this.label56.Location = new System.Drawing.Point(196, 180);
            this.label56.Name = "label56";
            this.label56.Size = new System.Drawing.Size(14, 15);
            this.label56.TabIndex = 81;
            this.label56.Text = "Y";
            // 
            // textBox_gpsMonth
            // 
            this.textBox_gpsMonth.Location = new System.Drawing.Point(139, 177);
            this.textBox_gpsMonth.Name = "textBox_gpsMonth";
            this.textBox_gpsMonth.ReadOnly = true;
            this.textBox_gpsMonth.Size = new System.Drawing.Size(42, 23);
            this.textBox_gpsMonth.TabIndex = 82;
            // 
            // label54
            // 
            this.label54.AutoSize = true;
            this.label54.Location = new System.Drawing.Point(10, 180);
            this.label54.Name = "label54";
            this.label54.Size = new System.Drawing.Size(31, 15);
            this.label54.TabIndex = 79;
            this.label54.Text = "Date";
            // 
            // label55
            // 
            this.label55.AutoSize = true;
            this.label55.Location = new System.Drawing.Point(119, 180);
            this.label55.Name = "label55";
            this.label55.Size = new System.Drawing.Size(18, 15);
            this.label55.TabIndex = 83;
            this.label55.Text = "M";
            // 
            // groupBox15
            // 
            this.groupBox15.Controls.Add(this.button_demo2);
            this.groupBox15.Controls.Add(this.button_demo1);
            this.groupBox15.Location = new System.Drawing.Point(339, 784);
            this.groupBox15.Name = "groupBox15";
            this.groupBox15.Size = new System.Drawing.Size(363, 66);
            this.groupBox15.TabIndex = 58;
            this.groupBox15.TabStop = false;
            this.groupBox15.Text = "Demo runs";
            // 
            // label44
            // 
            this.label44.AutoSize = true;
            this.label44.Location = new System.Drawing.Point(6, 55);
            this.label44.Name = "label44";
            this.label44.Size = new System.Drawing.Size(101, 15);
            this.label44.TabIndex = 70;
            this.label44.Text = "Steppers in move:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1137, 862);
            this.Controls.Add(this.groupBox15);
            this.Controls.Add(this.groupBox14);
            this.Controls.Add(this.groupBox13);
            this.Controls.Add(this.groupBox12);
            this.Controls.Add(this.groupBox11);
            this.Controls.Add(this.groupBox10);
            this.Controls.Add(this.groupBox9);
            this.Controls.Add(this.groupBox8);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tempBox);
            this.Name = "Form1";
            this.Text = "RastoBot Control Panel v1";
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
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox10.ResumeLayout(false);
            this.groupBox10.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.groupBox12.ResumeLayout(false);
            this.groupBox12.PerformLayout();
            this.groupBox13.ResumeLayout(false);
            this.groupBox13.PerformLayout();
            this.groupBox14.ResumeLayout(false);
            this.groupBox14.PerformLayout();
            this.groupBox15.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private Label label1;
        private Label label2;
        private Button button_Open;
        private ComboBox combo_Ports;
        private ComboBox combo_Speeds;
        private TextBox textBox_Log;
        private Button button_Disconnect;

        private RastoBot rastoBot;
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
        private ComboBox comboBox_Stepper;
        private ProgressBar progressBar_mainMotor;
        private TrackBar trackBar_mainMotorSpeed;
        private Button button_setMainMotorSpeed;
        private GroupBox groupBox7;
        private GroupBox groupBox8;
        private Label label17;
        private ComboBox comboBox_OperMode;
        private Label label18;
        private Label label20;
        private Label label19;
        private ComboBox comboBox_direction;
        private ComboBox comboBox_stepMode;
        private Label label22;
        private Label label21;
        private TextBox textBox_stepperStepsToMake;
        private TextBox textBox_steperSpeed;
        private Button button_stepperEnable;
        private Button button_stepperStepsToMake;
        private Button button_stepperSpeed;
        private Button button_stepperDirMode;
        private Button button_stepperStepMode;
        private Button button_stepperOperMode;
        private Button button_StepperDisable;
        private Button button_stepperStop;
        private Button button_StepperInit;
        private GroupBox groupBox9;
        private Button button_wheelsStepsToMakeApply;
        private Button button_wheelsApplySpeed;
        private TextBox textBox_wheelsSpeed;
        private Label label23;
        private TextBox textBox_wheelsStepsToMake;
        private Label label24;
        private Button button_initWheels;
        private Label label28;
        private Label label27;
        private Label label26;
        private Label label25;
        private Label label30;
        private Label label29;
        private GroupBox groupBox10;
        private GroupBox groupBox11;
        private GroupBox groupBox12;
        private Button button_levelingGoTo;
        private Button button_levelingRefRun;
        private TextBox textBox_levelingGoToPos;
        private Label label31;
        private Button button_demo1;
        private Button button_demo2;
        private GroupBox groupBox13;
        private Label label40;
        private TextBox textBox_compass_Y;
        private Label label39;
        private TextBox textBox_compass_Z;
        private Label label32;
        private TextBox textBox_compass_X;
        private Label label37;
        private Label label38;
        private TextBox textBox_accel_Y;
        private Label label42;
        private TextBox textBox_accel_Z;
        private Label label43;
        private TextBox textBox_accel_X;
        private Label label33;
        private Label label34;
        private TextBox textBox_gyro_Y;
        private Label label35;
        private TextBox textBox_gyro_Z;
        private Label label36;
        private TextBox textBox_gyro_X;
        private Label label41;
        private Label label45;
        private TextBox textBox_azimuth;
        private Label label46;
        private TextBox textBox_perimWire;
        private GroupBox groupBox14;
        private Label label47;
        private TextBox textBox_gpsSatellites;
        private TextBox textBox_gpsLat;
        private TextBox textBox_gpsHour;
        private Label label48;
        private Label label61;
        private TextBox textBox_gpsLong;
        private TextBox textBox_gpsSec;
        private Label label49;
        private Label label60;
        private TextBox textBox_gpsAlt;
        private TextBox textBox_gpsMin;
        private Label label59;
        private Label label51;
        private Label label58;
        private TextBox textBox_gpsSpeed;
        private TextBox textBox_gpsDay;
        private Label label52;
        private Label label57;
        private TextBox textBox_gpsCourse;
        private TextBox textBox_gpsYear;
        private Label label53;
        private Label label56;
        private TextBox textBox_gpsMonth;
        private Label label54;
        private Label label55;
        private GroupBox groupBox15;
        private CheckBox checkBox_s2move;
        private CheckBox checkBox_s1move;
        private CheckBox checkBox_s0move;
        private Label label44;
    }
}