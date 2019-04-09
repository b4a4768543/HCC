using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Load_Mid_Form : Form
    {
        public Load_Mid_Form()
        {
            InitializeComponent();
        }


        byte[] tmp;
        List<string> r_mid_2 = new List<string>();
        List<byte> r_txt_2 = new List<byte>();
        string[] r_16;
        StreamReader r_mid;
        StreamReader r_txt;

        // MIDI
        private void btn_load_Click(object sender, EventArgs e)
        {
            openFileDialog1.DefaultExt = ".mid";
            openFileDialog1.FileName = "";
            openFileDialog1.InitialDirectory = "C:\\Users\\b4a47\\Documents\\MuseScore3\\樂譜";
            //openFileDialog1.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory) + "\\";
            openFileDialog1.Filter = "MIDI(*.mid)|*.mid|所有檔案(*.*)|*.*";

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                tmp = File.ReadAllBytes(openFileDialog1.FileName);
                r_mid = new StreamReader(openFileDialog1.OpenFile());
                r_txt = null;

                for (string s = "0"; s != null;)
                {
                    s = r_mid.ReadLine();
                    if (s == null)
                        break;
                    r_mid_2.Add(s.ToString());
                }
                r_16 = new string[tmp.Length];
                for (int i = 0; i < tmp.Length; i++)
                    r_16[i] = Convert.ToInt32(tmp[i]).ToString("X2");
            }
        }
        // TXT
        private void btn_load_txt_Click(object sender, EventArgs e)
        {
            openFileDialog2.DefaultExt = ".txt";
            openFileDialog2.FileName = "";
            openFileDialog2.InitialDirectory = "C:\\Users\\b4a47\\Documents\\MuseScore3\\樂譜";
            //openFileDialog2.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory) + "\\";
            openFileDialog2.Filter = "txt(*.txt)|*.txt|所有檔案(*.*)|*.*";

            if (openFileDialog2.ShowDialog() == DialogResult.OK)
            {
                r_txt = new StreamReader(openFileDialog2.OpenFile());
                r_mid = null;

                for (string s = "0"; s != null;)
                {
                    s = r_txt.ReadLine();
                    if (s == null)
                        break;
                    // sixteen
                    if (!s.Contains("-"))
                        r_mid_2.Add(s.ToString());

                    // binary
                    string[] s_tmp = s.Split(' ');
                    for (int i = 0; i < s_tmp.Length; i++)
                    {
                        if (s_tmp[i] == "" || s_tmp[i].Contains('-'))
                            break;
                        Int32 sb_tmp = Convert.ToInt32(s_tmp[i], 16);
                        r_txt_2.Add(Convert.ToByte(sb_tmp));
                    }
                }
            }
        }

        private void btn_sixteen_Click(object sender, EventArgs e)
        {
            if (r_mid!=null)
            {
                richTextBox1.Text = "";
                for (int i = 0; i < tmp.Length; i++)
                    richTextBox1.Text += r_16[i] + " ";
            }
            else if (r_txt != null)
            {
                richTextBox1.Text = "";
                for (int i = 0; i < r_mid_2.Count; i++)
                    richTextBox1.Text += r_mid_2[i];
            }
        }

        private void btn_binary_Click(object sender, EventArgs e)
        {
            if (r_mid != null)
            {
                richTextBox2.Text = "";
                for (int i = 0; i < tmp.Length; i++)
                    richTextBox2.Text += tmp[i] + " ";
            }
            else if(r_txt != null)
            {
                richTextBox2.Text = "";
                for (int i = 0; i < r_txt_2.Count; i++)
                    richTextBox2.Text += r_txt_2[i] + " ";
            }
        }

        //Save
        private void btn_Binary_save_Click(object sender, EventArgs e)
        {
           if(saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs;
                fs = new FileStream(saveFileDialog1.FileName, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                BinaryWriter bw = new BinaryWriter(fs);

                for (int i = 0; i < tmp.Length; i++)
                    bw.Write(tmp[i]);

                int length = Convert.ToInt32(bw.BaseStream.Length);
                fs.Close();
                bw.Close();

            }
        }

        private void btn_save_txtTomid_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs;
                fs = new FileStream(saveFileDialog1.FileName, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                BinaryWriter bw = new BinaryWriter(fs);

                for (int i = 0; i < r_txt_2.Count; i++)
                    bw.Write(r_txt_2[i]);

                int length = Convert.ToInt32(bw.BaseStream.Length);
                fs.Close();
                bw.Close();

            }
        }

        
    }
}
