namespace RastoBot_ControlPanel
{
    internal static class Program
    {
        public static Form1 form1 = null;
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            form1 = new Form1();
            Application.Run(form1);
        }
    }
}