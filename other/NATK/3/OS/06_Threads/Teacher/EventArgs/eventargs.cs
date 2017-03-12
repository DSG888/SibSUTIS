using System;
using System.Threading;
using System.Windows.Forms;
//using System.ComponentModel;
using System.Drawing;

// Creates a class to throw the error.
 public class ErrorHandler : System.Windows.Forms.Form {

    // Inserts code to create a form with a button.

//My>
    public Button button1;
    public ErrorHandler()
    {
            button1 = new Button();
            button1.Size = new Size(40, 40);
            button1.Location = new Point(30, 30);
            button1.Text = "Click me";
            this.Controls.Add(button1);
            button1.Click += new EventHandler(button1_Click);
    }
//My<

    // Programs the button to throw the exception when clicked.
    private void button1_Click(object sender, System.EventArgs e) {
       throw new ArgumentException("The parameter was invalid");
    }

    public static void Main(string[] args) {
       // Creates an instance of the methods that will handle the exception.
       CustomExceptionHandler eh = new CustomExceptionHandler();

       // Adds the event handler to to the event.
       Application.ThreadException += new ThreadExceptionEventHandler(eh.OnThreadException);

       // Runs the application.
       Application.Run(new ErrorHandler());
    }
 }

 // Creates a class to handle the exception event.
 internal class CustomExceptionHandler {

    //Handles the exception event
    public void OnThreadException(object sender, ThreadExceptionEventArgs t) 
    {
       DialogResult result = DialogResult.Cancel;
       try {
          result = this.ShowThreadExceptionDialog(t.Exception);
       }
       catch {
          try {
             MessageBox.Show("Fatal Error", "Fatal Error", 
                MessageBoxButtons.AbortRetryIgnore, MessageBoxIcon.Stop);
          }
          finally {
             Application.Exit();
          }
       }

       // Exits the program when the user clicks Abort.
       if (result == DialogResult.Abort) 
          Application.Exit();
    }

    // Creates the error message and display it.
    private DialogResult ShowThreadExceptionDialog(Exception e) {
       string errorMsg = "An error occurred please contact the adminstrator " +
            "with the following information:\n\n";
       errorMsg = errorMsg + e.Message + "\n\nStack Trace:\n" + e.StackTrace;
       return MessageBox.Show(errorMsg, "Application Error", 
            MessageBoxButtons.AbortRetryIgnore, MessageBoxIcon.Stop);
    }
 }