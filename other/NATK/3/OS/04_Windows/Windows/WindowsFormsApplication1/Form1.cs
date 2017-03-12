using System;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1(string[] s)
        {
            InitializeComponent();
            if (s.Length == 0)
                listBox1.Items.Add("Не заданы параметры");
            else
            {
                listBox1.Items.Add("Заданы следующие параметры:");
                for (int i=0; i<s.LongLength; i++)
                    listBox1.Items.Add("Параметр "+(i+1)+" - "+s[i]);
                Print(listBox1, s[0]);
            }
        }

        private static int Check(string s)
        {
            for (int i = 0; i < s.Length; i++)
            {
                char ch=s[i];
                if (ch<'0' || ch>'9')
                    return -1;
            }
            return Convert.ToInt32(s);
        }

        private static void Print(ListBox lstb, string s)
        {
            int val = Check(s);
            if (val != -1)
            {
                if (val > 9) val = 9;
                for (int i = 0; i < val; i++)
                    lstb.Items.Add("Значение : " + Convert.ToString(i));
            }
            else
                lstb.Items.Add("Ошибочное значение : " + s);
        }

        private void button1_Click(object sender, EventArgs e)
        {

            if (textBox1.Text != "")
                Print(listBox1, textBox1.Text);
            else
                MessageBox.Show("Введите число(>0, но <9)");
            textBox1.Focus();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            MessageBox.Show("Вы выбрали "+listBox1.SelectedItem.ToString());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int k=listBox1.Items.Count;
            //MessageBox.Show("Кол-во элементов в списке "+ Convert.ToString(k));
            for (int i = 0; i < listBox1.Items.Count; i++)
                listBox1.Items.Remove(i);
            listBox1.Items.Clear();
        }

    }
}
