﻿namespace RastoBot_ControlPanel
{
    partial class Form1
    {
        SerialPortComm serialPort = new SerialPortComm();

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
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Port:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(177, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "Speed:";
            // 
            // button_Open
            // 
            this.button_Open.Location = new System.Drawing.Point(361, 6);
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
            this.combo_Ports.Location = new System.Drawing.Point(50, 6);
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
            this.combo_Speeds.Location = new System.Drawing.Point(225, 6);
            this.combo_Speeds.Name = "combo_Speeds";
            this.combo_Speeds.Size = new System.Drawing.Size(121, 23);
            this.combo_Speeds.TabIndex = 4;
            // 
            // textBox_Log
            // 
            this.textBox_Log.Location = new System.Drawing.Point(805, 12);
            this.textBox_Log.Multiline = true;
            this.textBox_Log.Name = "textBox_Log";
            this.textBox_Log.Size = new System.Drawing.Size(317, 328);
            this.textBox_Log.TabIndex = 5;
            // 
            // button_Disconnect
            // 
            this.button_Disconnect.Enabled = false;
            this.button_Disconnect.Location = new System.Drawing.Point(457, 6);
            this.button_Disconnect.Name = "button_Disconnect";
            this.button_Disconnect.Size = new System.Drawing.Size(75, 23);
            this.button_Disconnect.TabIndex = 6;
            this.button_Disconnect.Text = "Disconnect";
            this.button_Disconnect.UseVisualStyleBackColor = true;
            this.button_Disconnect.Click += new System.EventHandler(this.button_Disconnect_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1134, 647);
            this.Controls.Add(this.button_Disconnect);
            this.Controls.Add(this.textBox_Log);
            this.Controls.Add(this.combo_Speeds);
            this.Controls.Add(this.combo_Ports);
            this.Controls.Add(this.button_Open);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "RastoBot Control Panel";
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

        private RastoBot rastoBot = new RastoBot();
    }
}