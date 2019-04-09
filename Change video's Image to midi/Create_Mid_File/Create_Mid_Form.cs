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

using System.Windows.Forms.DataVisualization.Charting;


namespace Create_Mid_File
{
    public partial class Create_Mid_Form : Form
    {
        Graphics g1;
        public Create_Mid_Form()
        {
            InitializeComponent();

            tableLayoutPanel_ALL.Enabled = false;
        }


        /// <summary>
        /// Read Video File
        /// </summary>
       List<string> File = new List<string>();
        FolderBrowserDialog path = new FolderBrowserDialog();
        Bitmap bit;
        int page = 0;

        private void btn_Open_Click(object sender, EventArgs e)
        {
            string p = @"C:\Users\b4a47\Documents\MuseScore3\capture\Hontou No Oto (3-30-2019 2-06-18 AM)";
            //string p = @"C:\Users\b4a47\Documents\MuseScore3\capture\How to train your dragon1";

            //if (path.ShowDialog() == DialogResult.OK)
            //{
            File.Clear();
            foreach (string fname in System.IO.Directory.GetFiles(p))//path.SelectedPath))
            {
                File.Add(fname);
            }

            numericUpDown2.Maximum = File.Count;
            bit = null;
            bit = new Bitmap(Image.FromFile(File[page]));
            tableLayoutPanel3.BackgroundImage = bit;
            tableLayoutPanel3.BackgroundImageLayout = ImageLayout.Stretch;

            //}

            tableLayoutPanel_ALL.Enabled = true;
        }


        /// <summary>
        /// Data Field
        /// </summary>
        List<byte> title;
        List<byte> time;

        List<byte> track1_title;
        List<byte> track1_content;
        List<byte> track1_end;

        List<byte> track2_title;
        List<byte> track2_content;
        List<byte> track2_end;


        /// <summary>
        /// Draw Line
        /// </summary>
        #region Draw
        private void numericUpDown_detect_white_ValueChanged(object sender, EventArgs e)
        {
            if (File.Count != 0)
            {
                bit = null;
                bit = new Bitmap(Image.FromFile(File[page]));
                pictureBox1_Paint(this, null);
            }
        }
        private void numericUpDown_detect_black_ValueChanged(object sender, EventArgs e)
        {
            if (File.Count != 0)
            {
                bit = null;
                bit = new Bitmap(Image.FromFile(File[page]));
                pictureBox1_Paint(this, null);
            }
        }

        float[] move = new float[12];
        float[] first = new float[12];
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if (File.Count != 0)
            {
                // Initialize
                numericUpDown_detect_white.Maximum = pictureBox1.Height ;
                numericUpDown_detect_black.Maximum = pictureBox1.Height;
                bit = null;
                bit = new Bitmap(Image.FromFile(File[page]));
                g1 = Graphics.FromImage(bit);

                // Draw
                int y_white = (int)(Convert.ToSingle(numericUpDown_detect_white.Value) * bit.Height / pictureBox1.Height);
                int y_black = (int)(Convert.ToSingle(numericUpDown_detect_black.Value) * bit.Height / pictureBox1.Height);
                for (int j = 0; j < 88; j++)
                {
                    //
                    int x = (int)(first[j % 12] + (j / 12) * move[j % 12]);
                    int y = 0;
                    
                    //
                    if (j % 12 == 0 || j % 12 == 2 || j % 12 == 3 || j % 12 == 5 || j % 12 == 7 || j % 12 == 8 || j % 12 == 10)
                        y = y_white;
                    else
                        y = y_black;

                    //
                    Color c;
                    if (x > 0 && x < bit.Width - 1)
                    {
                        c = bit.GetPixel(x, y);
                        // 畫點點
                        g1.DrawRectangle(Pens.Red, x, y, 1, 1);
                        // 顯示滑鼠點的顏色
                        if (checkBox_Draw_RGB.Checked)
                        {
                            string s = $"({c.R},{c.G},{c.B})";
                            g1.DrawString(s, DefaultFont, SystemBrushes.ActiveBorder, new Point(x, y));
                        }
                    }

                    
                }

                // Refresh
                tableLayoutPanel3.BackgroundImage = bit;
            }
        }
        #endregion
        


        /// <summary>
        /// Analysis
        /// </summary>
        float intPercent = 1.25f;
        int type = 0;

        int[][] Left_content = new int[88][];
        int[][] Right_content = new int[88][];

        List<int[]> Left_chord = new List<int[]>();
        List<int[]> Right_chord = new List<int[]>();

        List<int> time_thread = new List<int>();
        List<int> play_time_Original_L = new List<int>();
        List<int> play_time_Original_R = new List<int>();

        List<int> play_time_Optimize_L = new List<int>();
        List<int> play_time_Optimize_R = new List<int>();
        List<int> play_time_Optimize_ALL = new List<int>();

        int y_white = 0;
        int y_black = 0;
        private void btn_Check_setting_Click(object sender, EventArgs e)
        {
            // Initialize
            Analysis_Initialize();
        }

        int start = 0;
        int end = 2000;
        private void btn_Find_Click(object sender, EventArgs e)
        {
            if (start < File.Count)
            {
                if (end > File.Count)
                    end = File.Count;
                // 判斷 何時有聲音
                Analysis_Sound_detect(start, end);

                start += 2000;
                end += 2000;
            }
            else
                MessageBox.Show(this,"全部搜尋完畢。","cc",MessageBoxButtons.OK);
        }
        private void btn_analysis_Click(object sender, EventArgs e)
        {
            // 判斷 音的長度
            Analysis_Sound_length();

            // 平移
            Offset();

            // 改旋律
            Analysis_Reshape_tempo();

            // 分離連音
            //Compare(Left_chord, play_time_Optimize_L);
            //Compare(Right_chord, play_time_Optimize_R);
            play_time_Optimize_L.Sort();
            play_time_Optimize_R.Sort();

            // Display
            for (int i = 0; i < play_time_Optimize_R.Count; i++)
                checkedListBox1.Items.Add(play_time_Optimize_R[i]);
            for (int i = 0; i < play_time_Optimize_L.Count; i++)
                checkedListBox1.Items.Add(play_time_Optimize_L[i]);


            // 畫圖顯示
            chart1.ChartAreas[0].AxisX.Minimum = 0;
            chart1.ChartAreas[0].AxisX.Maximum = File.Count * 2;
            chart1.ChartAreas[0].AxisY.Minimum = 0;
            chart1.ChartAreas[0].AxisY.Maximum = 88;

            for (int i = 0; i < Left_chord.Count; i++)
                Draw_chart(Left_chord[i], chart1, Color.Blue);
            for (int i = 0; i < Right_chord.Count; i++)
                Draw_chart(Right_chord[i], chart1, Color.Red);
        }
        // 1.
        void Analysis_Initialize()
        {
            // Initialize
            toolStripProgressBar1.Maximum = File.Count;
            Left_chord.Clear();
            Right_chord.Clear();
            time_thread.Clear();
            play_time_Original_L.Clear();
            play_time_Original_R.Clear();
            play_time_Optimize_L.Clear();
            play_time_Optimize_R.Clear();
            play_time_Optimize_ALL.Clear();
            Left_content = null;
            Right_content = null;
            chart1.Series.Clear();
            checkedListBox1.Items.Clear();

            // Set Space
            Left_content = new int[88][];
            Right_content = new int[88][];
            for (int i = 0; i < 88; i++)
            {
                Left_content[i] = new int[File.Count];
                Right_content[i] = new int[File.Count];
            }

            y_white = (int)(Convert.ToSingle(numericUpDown_detect_white.Value) * bit.Height / pictureBox1.Height);
            y_black = (int)(Convert.ToSingle(numericUpDown_detect_black.Value) * bit.Height / pictureBox1.Height);

            start = 0;
            end = 2000;
        }
        // 2
        void Analysis_Sound_detect(int start , int end)
        {
            for (int i = start; i < end; i++)
            {
                toolStripProgressBar1.Value = i + 1;

                Find(i, y_white, y_black);

                System.Runtime.GCSettings.LargeObjectHeapCompactionMode = System.Runtime.GCLargeObjectHeapCompactionMode.CompactOnce;
                GC.Collect();
            }
        }

        List<Bitmap> bitma = new List<Bitmap>();
        void Find(int i, int y_white, int y_black)
        {
            Bitmap bitt = new Bitmap(File[i]);

            for (int j = 0; j < 88; j++)
            {
                int x = (int)(first[j % 12] + (j / 12) * move[j % 12]);

                int y = 0;
                if (j % 12 == 0 || j % 12 == 2 || j % 12 == 3 || j % 12 == 5 || j % 12 == 7 || j % 12 == 8 || j % 12 == 10)
                    y = y_white;
                else
                    y = y_black;

                if (x > 0 && x < bit.Width - 1)
                {
                    Color c = bitt.GetPixel(x, y);

                    switch (type)
                    {
                        case 11:
                            if (c.R < numericUpDown_L_Up_Color.Value && c.R > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.R < numericUpDown_R_Up_Color.Value && c.R > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        case 12:
                            if (c.R < numericUpDown_L_Up_Color.Value && c.R > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.G < numericUpDown_R_Up_Color.Value && c.G > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        case 13:
                            if (c.R < numericUpDown_L_Up_Color.Value && c.R > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.B < numericUpDown_R_Up_Color.Value && c.B > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;

                        case 21:
                            if (c.G < numericUpDown_L_Up_Color.Value && c.G > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.R < numericUpDown_R_Up_Color.Value && c.R > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        case 22:
                            if (c.G < numericUpDown_L_Up_Color.Value && c.G > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.G < numericUpDown_R_Up_Color.Value && c.G > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        case 23:
                            if (c.G < numericUpDown_L_Up_Color.Value && c.G > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.B < numericUpDown_R_Up_Color.Value && c.B > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;

                        case 31:
                            if (c.B < numericUpDown_L_Up_Color.Value && c.B > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.R < numericUpDown_R_Up_Color.Value && c.R > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        case 32:
                            if (c.B < numericUpDown_L_Up_Color.Value && c.B > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.G < numericUpDown_R_Up_Color.Value && c.G > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        case 33:
                            if (c.B < numericUpDown_L_Up_Color.Value && c.B > numericUpDown_L_Down_Color.Value)
                                Left_content[j][i] = 1;
                            else if (c.B < numericUpDown_R_Up_Color.Value && c.B > numericUpDown_R_Down_Color.Value)
                                Right_content[j][i] = 1;
                            break;
                        default:
                            break;
                    }
                }
            }

        }
        // 3
        void Analysis_Sound_length()
        {
            for (int i = 0; i < 88; i++)
            {
                int[] tmp_L = null;
                int[] tmp_R = null;

                for (int j = 0; j < File.Count; j++)
                {
                    if (Left_content[i][j] == 1)
                    {
                        if (tmp_L == null)
                        {
                            tmp_L = new int[3];
                            tmp_L[0] = i; // 哪個音
                            tmp_L[1] = j; // 什麼時候
                        }
                        tmp_L[2]++; // 多久
                    }
                    else
                    {
                        if (tmp_L != null)
                        {
                            //time_thread.Add(tmp_L[2]);
                            play_time_Original_L.Add(tmp_L[1]);

                            int[] c = new int[3];
                            tmp_L.CopyTo(c, 0);
                            Left_chord.Add(c);
                            tmp_L = null;
                        }
                    }

                    //
                    if (Right_content[i][j] == 1)
                    {
                        if (tmp_R == null)
                        {
                            tmp_R = new int[3];
                            tmp_R[0] = i; // 哪個音
                            tmp_R[1] = j; // 什麼時候
                        }
                        tmp_R[2]++; // 多久
                    }
                    else
                    {
                        if (tmp_R != null)
                        {
                            //time_thread.Add(tmp_R[2]);
                            play_time_Original_R.Add(tmp_R[1]);

                            int[] c = new int[3];
                            tmp_R.CopyTo(c, 0);
                            Right_chord.Add(c);
                            tmp_R = null;
                        }
                    }
                }
            }
            play_time_Original_L.Sort();
            play_time_Original_R.Sort();

        }
        // 4
        void Offset()
        {
            // offset
            if (play_time_Original_L.Count > 0)
            {
                int offset_L = play_time_Original_L[0];
                for (int i = 0; i < Left_chord.Count; i++)
                {
                    Left_chord[i][1] -= offset_L;
                    play_time_Original_L[i] -= offset_L;
                }
            }

            if (play_time_Original_R.Count > 0)
            {
                int offset_R = play_time_Original_R[0];
                for (int i = 0; i < Right_chord.Count; i++)
                {
                    Right_chord[i][1] -= offset_R;
                    play_time_Original_R[i] -= offset_R;
                }
            }
        }
        // 5
        void Analysis_Reshape_tempo()
        {
            ///Reshape
            // 優化 Left_chord & Right_chord
            for (int i = 0; i < Left_chord.Count; i++)
            {
                Left_chord[i][2] = Reshape(Left_chord[i][2]);
                time_thread.Add(Left_chord[i][2]);
            }
            for (int i = 0; i < Right_chord.Count; i++)
            {
                Right_chord[i][2] = Reshape(Right_chord[i][2]);
                time_thread.Add(Right_chord[i][2]);
            }
            time_thread.Sort();

            List<int> play_time_Original_All = new List<int>();
            for (int j = 0; j < play_time_Original_R.Count; j++)
                play_time_Original_All.Add(play_time_Original_R[j]);
            for (int j = 0; j < play_time_Original_L.Count; j++)
                play_time_Original_All.Add(play_time_Original_L[j]);

            play_time_Original_All.Sort();
            Reshape(play_time_Original_All, play_time_Optimize_ALL);


            // 紀錄 play_time_Optimize_R & L
            for (int j = 0; j < play_time_Original_R.Count; j++)
            {
                if (play_time_Original_All.Contains(play_time_Original_R[j]))
                    play_time_Optimize_R.Add(play_time_Optimize_ALL[play_time_Original_All.IndexOf(play_time_Original_R[j])]);
            }

            for (int j = 0; j < play_time_Original_L.Count; j++)
            {
                if (play_time_Original_All.Contains(play_time_Original_L[j]))
                    play_time_Optimize_L.Add(play_time_Optimize_ALL[play_time_Original_All.IndexOf(play_time_Original_L[j])]);
            }


            /// 將優化值更改回 Left_chord & Right_chord
            bool[] test_L = new bool[Left_chord.Count];
            bool[] test_R = new bool[Right_chord.Count];

            int count = 0;
            for (int j = 0; j < play_time_Optimize_ALL.Count; j++)
            {
                for (int i = 0; i < Left_chord.Count; i++)
                    if (Left_chord[i][1] == play_time_Original_All[j] && !test_L[i])
                    {
                        count++;
                        test_L[i] = true;
                        Left_chord[i][1] = play_time_Optimize_ALL[j];
                    }
                for (int i = 0; i < Right_chord.Count; i++)
                    if (Right_chord[i][1] == play_time_Original_All[j] && !test_R[i])
                    {
                        test_R[i] = true;
                        Right_chord[i][1] = play_time_Optimize_ALL[j];
                    }
            }
            count = 0;
        }
        void Reshape(List<int> Input, List<int> output) // 優化 撥放位置
        {
            output.Add(Input[0]);
            for (int i = 1; i < Input.Count ;)
            {
                List<int> delta = new List<int>();
                for (int j = 0; delta.Count == 0 || delta[j - 1] == 0; j++)
                {
                    if (i + j < Input.Count)
                        delta.Add(Input[i + j] - Input[i - 1]);
                    else
                        break;
                }

                for (int j = 0; j < delta.Count; j++)
                {
                    if (delta[j] == 0)
                        delta[j] = output[i - 1];

                    else if (delta[j] <= ((double)numericUpDown_forth.Value / 2) + 2)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value);
                    else if (delta[j] <= (int)numericUpDown_forth.Value + 2)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 2);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 1.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 3);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 2 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 4);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 2.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 5);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 3 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 6);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 3.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 7);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 4 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 8);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 4.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 9);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 10);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 5.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 11);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 6 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 12);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 6.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 13);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 7 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 14);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 7.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 15);

                    else if (delta[j] <= (int)numericUpDown_forth.Value * 8 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 16);
                    else if (delta[j] <= (int)numericUpDown_forth.Value * 8.5 + 1)
                        delta[j] = (output[i - 1] + (int)numericUpDown_forth.Value * 17);

                    output.Add(delta[j]);
                    i++;
                }
            }
        }
        int Reshape(int Input) // 優化 撥放時間
        {
            int output = 0;
            int input_tmp = Input;

            if (input_tmp <= ((double)numericUpDown_forth.Value / 4) )
                output = 0;

            else if(input_tmp <= ((double)numericUpDown_forth.Value / 2) + 2)
                output = (int)numericUpDown_forth.Value;

            else if (input_tmp <= (int)numericUpDown_forth.Value + 2)
                output = (int)numericUpDown_forth.Value *2;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 1.5 + 1)
                output = (int)((int)numericUpDown_forth.Value * 3);

            else if (input_tmp <= (int)numericUpDown_forth.Value * 2 + 2)
                output = (int)numericUpDown_forth.Value * 4;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 2.5 + 2)
                output = (int)numericUpDown_forth.Value * 5;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 3 + 3)
                output = (int)numericUpDown_forth.Value * 6;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 3.5 + 3)
                output = (int)numericUpDown_forth.Value * 7;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 4 + 4)
                output = (int)numericUpDown_forth.Value * 8;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 4.5 + 4)
                output = (int)numericUpDown_forth.Value * 9;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 5 + 5)
                output = (int)numericUpDown_forth.Value * 10;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 5.5 + 5)
                output = (int)numericUpDown_forth.Value * 11;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 6 + 6)
                output = (int)numericUpDown_forth.Value * 12;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 6.5 + 6)
                output = (int)numericUpDown_forth.Value * 13;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 7 + 7)
                output = (int)numericUpDown_forth.Value * 14;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 7.5 + 7)
                output = (int)numericUpDown_forth.Value * 15;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 8 + 8)
                output = (int)numericUpDown_forth.Value * 16;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 8.5 + 8)
                output = (int)numericUpDown_forth.Value * 17;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 9 + 9)
                output = (int)numericUpDown_forth.Value * 18;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 9.5 + 9)
                output = (int)numericUpDown_forth.Value * 19;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 10 + 10)
                output = (int)numericUpDown_forth.Value * 20;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 10.5 + 10)
                output = (int)numericUpDown_forth.Value * 21;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 11 + 11)
                output = (int)numericUpDown_forth.Value * 22;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 11.5 + 11)
                output = (int)numericUpDown_forth.Value * 23;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 12 + 12)
                output = (int)numericUpDown_forth.Value * 24;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 12.5 + 12)
                output = (int)numericUpDown_forth.Value * 25;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 13 + 1)
                output = (int)numericUpDown_forth.Value * 26;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 13.5 + 1)
                output = (int)numericUpDown_forth.Value * 27;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 14 + 1)
                output = (int)numericUpDown_forth.Value * 28;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 14.5 + 1)
                output = (int)numericUpDown_forth.Value * 29;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 15 + 1)
                output = (int)numericUpDown_forth.Value * 30;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 15.5 + 1)
                output = (int)numericUpDown_forth.Value * 31;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 16)
                output = (int)numericUpDown_forth.Value * 32;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 16.5)
                output = (int)numericUpDown_forth.Value * 33;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 17)
                output = (int)numericUpDown_forth.Value * 34;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 17.5)
                output = (int)numericUpDown_forth.Value * 35;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 18)
                output = (int)numericUpDown_forth.Value * 36;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 18.5)
                output = (int)numericUpDown_forth.Value * 37;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 19)
                output = (int)numericUpDown_forth.Value * 38;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 19.5)
                output = (int)numericUpDown_forth.Value * 39;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 20)
                output = (int)numericUpDown_forth.Value * 40;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 20.5)
                output = (int)numericUpDown_forth.Value * 41;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 21)
                output = (int)numericUpDown_forth.Value * 42;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 21.5)
                output = (int)numericUpDown_forth.Value * 43;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 22)
                output = (int)numericUpDown_forth.Value * 44;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 22.5)
                output = (int)numericUpDown_forth.Value * 45;

            else if (input_tmp <= (int)numericUpDown_forth.Value * 23)
                output = (int)numericUpDown_forth.Value * 46;
            else if (input_tmp <= (int)numericUpDown_forth.Value * 23.5)
                output = (int)numericUpDown_forth.Value * 47;

            return output;
        }
        // 5 分離連音
        void Compare(List<int[]> Compared_chord, List<int> play_list)
        {
            for (int i = 0; i < Compared_chord.Count - 1; i++)
            {
                for (int j = i + 1; j < Compared_chord.Count; j++)
                {
                    if (Compared_chord[i][1] == Compared_chord[j][1])
                    {
                        if (Compared_chord[i][2] > Compared_chord[j][2])
                        {
                            // 音 時 長度
                            int[] tmp = new int[3];
                            tmp[0] = Compared_chord[i][0];
                            tmp[1] = Compared_chord[i][1] + Compared_chord[j][2];
                            tmp[2] = Compared_chord[i][2] - Compared_chord[j][2];

                            Compared_chord.Add(tmp);
                            play_list.Add(tmp[1]);

                            Compared_chord[i][2] = Compared_chord[j][2];

                            i = -1;
                            break;
                        }
                        else if (Compared_chord[i][2] < Compared_chord[j][2])
                        {
                            // 音 時 長度
                            int[] tmp = new int[3];
                            tmp[0] = Compared_chord[j][0];
                            tmp[1] = Compared_chord[j][1] + Compared_chord[i][2];
                            tmp[2] = Compared_chord[j][2] - Compared_chord[i][2];

                            Compared_chord.Add(tmp);
                            play_list.Add(tmp[1]);

                            Compared_chord[j][2] = Compared_chord[i][2];

                            i = -1;
                            break;
                        }
                    }
                }
            }
        }
        // 6 畫圖
        void Draw_chart(int[] line, Chart C1, Color c)
        {
            Series se = new Series();
            se.Points.AddXY(line[1], line[0]);
            se.Points.AddXY(line[1] + line[2], line[0]);

            se.ChartArea = C1.ChartAreas[0].Name;
            se.ChartType = SeriesChartType.Line;
            se.Color = c;
            C1.Series.Add(se);
        }





        /// <summary>
        /// Save File
        /// </summary>
        #region Save
        private void btn_Save_Click(object sender, EventArgs e)
        {
            Save_Initialize();
        }
        void Save_Initialize()
        {
            saveFileDialog1.DefaultExt = ".mid";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string s;
                if (title != null)
                {
                    title = null;
                    track1_title = null;
                    track1_content = null;
                    track1_end = null;
                    track2_title = null;
                    track2_content = null;
                    track2_end = null;
                }

                ///
                // track1_content
                //List<int> play_time_R_tmp = new List<int>();
                //List<int> play_time_L_tmp = new List<int>();

                //for (int j = 0; j < play_time_R.Count; j++)
                //    play_time_R_tmp.Add(play_time_R[j]);
                //for (int j = 0; j < play_time_L.Count; j++)
                //    play_time_L_tmp.Add(play_time_L[j]);

                s = get_chord(Right_chord, play_time_Optimize_R, play_time_Original_R);
                track1_content = Construct_Space(s);

                // track2_content
                //play_time_R_tmp.Clear();
                //play_time_L_tmp.Clear();

                //for (int j = 0; j < play_time_R.Count; j++)
                //    play_time_R_tmp.Add(play_time_R[j]);
                //for (int j = 0; j < play_time_L.Count; j++)
                //    play_time_L_tmp.Add(play_time_L[j]);

                s = get_chord(Left_chord, play_time_Optimize_L, play_time_Original_L);
                track2_content = Construct_Space(s);

                /// 
                // Title
                s = "4D 54 68 64 00 00 00 06 00 01 00 02";
                title = Construct_Space(s);

                // track1_title
                //int ss = 52 + track1_content.Count;
                //Int32 sb_tmp = Convert.ToInt32(ss.ToString(), 16);
                s = $"4D 54 72 6B 00 00 00 00 00 FF 58 04 04 02 18 08 00 FF 59 02 00 00 00 FF 51 03 07 A1 20 00 B0 79 00 00 C0 00 00 B0 07 64 00 0A 40 00 5B 00 00 5D 00 00 FF 21 01 00";
                track1_title = Construct_Space(s);

                // time
                s = "00 78";
                time = Construct_Space(s);

                // track1_end
                s = "01 FF 2F 00";
                track1_end = Construct_Space(s);

                // track2_title
                s = $"4D 54 72 6B 00 00 00 00 00 FF 59 02 00 00 00 FF 21 01 00";
                track2_title = Construct_Space(s);

                // track2_end
                s = "01 FF 2F 00";
                track2_end = Construct_Space(s);

                /// output
                FileStream fs;
                fs = new FileStream(saveFileDialog1.FileName, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                BinaryWriter bw = new BinaryWriter(fs);

                for (int i = 0; i < title.Count; i++)
                    bw.Write(title[i]);
                for (int i = 0; i < time.Count; i++)
                    bw.Write(time[i]);
                for (int i = 0; i < track1_title.Count; i++)
                    bw.Write(track1_title[i]);
                for (int i = 0; i < track1_content.Count; i++)
                    bw.Write(track1_content[i]);
                for (int i = 0; i < track1_end.Count; i++)
                    bw.Write(track1_end[i]);
                for (int i = 0; i < track2_title.Count; i++)
                    bw.Write(track2_title[i]);
                for (int i = 0; i < track2_content.Count; i++)
                    bw.Write(track2_content[i]);
                for (int i = 0; i < track2_end.Count; i++)
                    bw.Write(track2_end[i]);

                fs.Close();
                bw.Close();
            }
        }

        int delay = 0;
        string get_chord(List<int[]> content , List<int> play_time, List<int> play_time_others)
        {
            string s = "00 90 ";
            int intial_count = 0;

            for(int i = 0; i < play_time.Count; intial_count++)
            {
                List<int> index = new List<int>();

                /// get chord index
                // play_time 抓重複
                int play_now = Convert.ToInt32(play_time[0].ToString());
                int count = 0;
                for (int j = 0; j < play_time.Count;)
                {
                    if (play_time[j] == play_now)
                    {
                        count++;
                        play_time.RemoveAt(0);
                    }
                    else
                        break;
                }

                // find index 找content裡 重複的 index
                for (int j = 0 ; j < content.Count; j++)
                {
                    if (index.Count < count)
                    {
                        // 音 何時 長度
                        if (content[j][1] == play_now)
                        {
                            index.Add(Convert.ToInt32(j.ToString()));
                        }
                    }
                    else
                        break;
                }

                /// 調整旋律
                List<int> chord_length = new List<int>(); // 多個音的撥放長度
                int play_next = 0;

                for (int j = 0; j< index.Count; j ++)
                    chord_length.Add(Chord_len(content[index[j]][2]));

                int min_idx = chord_length.IndexOf(chord_length.Min()); // length裡最小值的inx

                if (play_time.Count > 0)
                    play_next = Chord_len(play_time[0] - play_now);

                // 其他判斷方式
                for (int j = 0; j < chord_length.Count; j++)
                {
                    if (play_time.Count > 0 && content[index[j]][1] + content[index[j]][2] > play_time[0])
                    {
                        int[] tmp = new int[3];
                        tmp[0] = content[index[j]][0];
                        tmp[1] = play_time[0];
                        tmp[2] = content[index[j]][1] + content[index[j]][2] - play_time[0];

                        play_time.Insert(0, play_time[0]);
                        content.Add(tmp);

                        chord_length[j] = Chord_len(play_time[0] - content[index[j]][1]);
                    }
                }


                /// 制譜
                // 1. Note on
                for (int j = 0; j < chord_length.Count;j++)
                {
                    //step 1. delay
                    if (intial_count == 0 && j ==0)
                    { }
                    else if(delay!=0)
                    {
                        s += $"{delay_time(delay)} ";
                        delay = 0;
                    }
                    else
                        s += "00 ";

                    //step 2. chord
                    byte x = Convert.ToByte(content[index[j]][0] + 21);
                    string s_tmp = Convert.ToInt32(x).ToString("X2");
                    s += s_tmp + " ";

                    // step3. strengh
                    s += "50 ";

                }

                // 2. Note off
                for (int j = 0; j < chord_length.Count; j++)
                {
                    //step 1. delay
                    if (j == 0)
                    {
                        s += delay_time(chord_length[min_idx]);
                    }
                    else
                    {
                        s += "00 ";
                    }

                    //step 2. chord
                    byte x = Convert.ToByte(content[index[j]][0] + 21);
                    string s_tmp = Convert.ToInt32(x).ToString("X2");
                    s += s_tmp + " ";

                    // step3. strengh
                    s += "00 ";

                }

                if (chord_length[min_idx] < play_next)
                    delay = play_next - chord_length.Min();
                if (delay != 0)
                {
                    int t = 0;
                }
            }
            return s;
        }
        string delay_time(int i)
        {
            string s = "";
            if (i > 128)
            {
                byte x = Convert.ToByte(i % 128);
                string s_tmp = Convert.ToInt32(x).ToString("X2");

                if((int)(i / 128)<10)
                    s = $"8{(int)(i / 128)} {s_tmp} ";
                else
                    s = $"8{(int)(i / 128)} {s_tmp} ";
            }
            else if (i == 60)
            {
                s = "3C ";
            }
            else if (i==30)
            {
                s = "1E ";
            }
            else
                s = "78 ";
            return s;
        }

        int Chord_len(int i)
        {
            int type = 0;

            if (i <= numericUpDown_forth.Value) //8
                type = 30;
            else if (i <= numericUpDown_forth.Value * 2)  //4
                type = 60;
            else if (i <= numericUpDown_forth.Value * 3)  //2
                type = 90;
            else if (i <= numericUpDown_forth.Value * 4)  //1
                type = 120;
            else if (i <= numericUpDown_forth.Value * 5)  //1
                type = 150;
            else if (i <= numericUpDown_forth.Value * 6)  //4
                type = 180;
            else if (i <= numericUpDown_forth.Value * 7)  //1
                type = 210;
            else if (i <= numericUpDown_forth.Value * 8)  //4
                type = 240;
            else if (i <= numericUpDown_forth.Value * 9)  //1
                type = 270;
            else if (i <= numericUpDown_forth.Value * 10)  //4
                type = 300;
            else if (i <= numericUpDown_forth.Value * 11)  //1
                type = 330;
            else if (i <= numericUpDown_forth.Value * 12)  //4
                type = 360;
            else if (i <= numericUpDown_forth.Value * 13)  //1
                type = 390;
            else if (i <= numericUpDown_forth.Value * 14)  //4
                type = 420;
            else if (i <= numericUpDown_forth.Value * 15)  //1
                type = 450;
            else if (i <= numericUpDown_forth.Value * 16)  //4
                type = 480;
            else if (i <= numericUpDown_forth.Value * 17)  //1
                type = 510;
            else if (i <= numericUpDown_forth.Value * 18)  //4
                type = 540;
            else if (i <= numericUpDown_forth.Value * 19)  //4
                type = 570;
            else if (i <= numericUpDown_forth.Value * 20)  //4
                type = 600;
            else if (i <= numericUpDown_forth.Value * 21)  //4
                type = 630;
            else if (i <= numericUpDown_forth.Value * 22)  //4
                type = 660;
            else if (i <= numericUpDown_forth.Value * 23)  //4
                type = 690;
            else if (i <= numericUpDown_forth.Value * 24)  //4
                type = 720;
            else
                type = 750;
            return type;
        }

        List<byte> Construct_Space(string s)
        {
            string[] S_get_split = s.Split(' ');
            List<byte> space = new List<byte>();
            for (int i = 0; i < S_get_split.Length; i++)
            {
                if (S_get_split[i] != "")
                {
                    Int32 sb_tmp = Convert.ToInt32(S_get_split[i], 16);
                    space.Add(Convert.ToByte(sb_tmp));
                }
            }
            return space;
        }
        #endregion


        /// <summary>
        /// Change Image
        /// </summary>
        #region Change Image
        private void btn_next_Click(object sender, EventArgs e)
        {
            if (File.Count != 0 && page < File.Count)
            {
                page++;
                numericUpDown2.Value = page;

                bit = null;
                bit = new Bitmap(Image.FromFile(File[page]));
                pictureBox1_Paint(this, null);
            }
        }
        private void btn_last_Click(object sender, EventArgs e)
        {
            if (File.Count != 0 && page > 0)
            {
                page--;
                numericUpDown2.Value = page;

                bit = null;
                bit = new Bitmap(Image.FromFile(File[page]));
                pictureBox1_Paint(this, null);
            }
        }
        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            if (File.Count != 0 && (int)numericUpDown2.Value< File.Count)
            {
                page = (int)numericUpDown2.Value;

                bit = null;
                bit = new Bitmap(Image.FromFile(File[page]));
                pictureBox1_Paint(this, null);
            }
            else
                numericUpDown2.Value = page;
        }
        #endregion




        /// <summary>
        /// Check Point
        /// </summary>
        #region Check_Point
        private void numericUpDown_first_0_ValueChanged(object sender, EventArgs e)
        {
            first[0] = (float)numericUpDown_first_0.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_1_ValueChanged(object sender, EventArgs e)
        {
            first[1] = (float)numericUpDown_first_1.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_2_ValueChanged(object sender, EventArgs e)
        {
            first[2] = (float)numericUpDown_first_2.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_3_ValueChanged(object sender, EventArgs e)
        {
            first[3] = (float)numericUpDown_first_3.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_4_ValueChanged(object sender, EventArgs e)
        {
            first[4] = (float)numericUpDown_first_4.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_5_ValueChanged(object sender, EventArgs e)
        {
            first[5] = (float)numericUpDown_first_5.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_6_ValueChanged(object sender, EventArgs e)
        {
            first[6] = (float)numericUpDown_first_6.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_7_ValueChanged(object sender, EventArgs e)
        {
            first[7] = (float)numericUpDown_first_7.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_8_ValueChanged(object sender, EventArgs e)
        {
            first[8] = (float)numericUpDown_first_8.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_9_ValueChanged(object sender, EventArgs e)
        {
            first[9] = (float)numericUpDown_first_9.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_10_ValueChanged(object sender, EventArgs e)
        {
            first[10] = (float)numericUpDown_first_10.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_first_11_ValueChanged(object sender, EventArgs e)
        {
            first[11] = (float)numericUpDown_first_11.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_0_ValueChanged(object sender, EventArgs e)
        {
            move[0] = (float)numericUpDown_move_0.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_1_ValueChanged(object sender, EventArgs e)
        {
            move[1] = (float)numericUpDown_move_1.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_2_ValueChanged(object sender, EventArgs e)
        {
            move[2] = (float)numericUpDown_move_2.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_3_ValueChanged(object sender, EventArgs e)
        {
            move[3] = (float)numericUpDown_move_3.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_4_ValueChanged(object sender, EventArgs e)
        {
            move[4] = (float)numericUpDown_move_4.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_5_ValueChanged(object sender, EventArgs e)
        {
            move[5] = (float)numericUpDown_move_5.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_6_ValueChanged(object sender, EventArgs e)
        {
            move[6] = (float)numericUpDown_move_6.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_7_ValueChanged(object sender, EventArgs e)
        {
            move[7] = (float)numericUpDown_move_7.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_8_ValueChanged(object sender, EventArgs e)
        {
            move[8] = (float)numericUpDown_move_8.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_9_ValueChanged(object sender, EventArgs e)
        {
            move[9] = (float)numericUpDown_move_9.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_10_ValueChanged(object sender, EventArgs e)
        {
            move[10] = (float)numericUpDown_move_10.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void numericUpDown_move_11_ValueChanged(object sender, EventArgs e)
        {
            move[11] = (float)numericUpDown_move_11.Value;
            numericUpDown_detect_white_ValueChanged(this, null);
        }

        private void btn_first_minus_Click(object sender, EventArgs e)
        {
            NumericUpDown tmp = new NumericUpDown();
            for (int i = 0; i < 12; i++)
            {
                tmp = this.Controls.Find("numericUpDown_first_" + i.ToString(), true).FirstOrDefault() as NumericUpDown;
                tmp.Value -= 1;
            }
        }

        private void btn_first_plus_Click(object sender, EventArgs e)
        {
            NumericUpDown tmp = new NumericUpDown();
            for (int i = 0; i < 12; i++)
            {
                tmp = this.Controls.Find("numericUpDown_first_" + i.ToString(), true).FirstOrDefault() as NumericUpDown;
                tmp.Value += 1;
            }
        }

        private void btn_move_minus_Click(object sender, EventArgs e)
        {
            NumericUpDown tmp = new NumericUpDown();
            for (int i = 0; i < 12; i++)
            {
                tmp = this.Controls.Find("numericUpDown_move_" + i.ToString(), true).FirstOrDefault() as NumericUpDown;
                tmp.Value -= 1;
            }
        }

        private void btn_move_plus_Click(object sender, EventArgs e)
        {
            NumericUpDown tmp = new NumericUpDown();
            for (int i = 0; i < 12; i++)
            {
                tmp = this.Controls.Find("numericUpDown_move_" + i.ToString(), true).FirstOrDefault() as NumericUpDown;
                tmp.Value += 1;
            }
        }

        private void btn_auto_Click(object sender, EventArgs e)
        {
            //
            numericUpDown_first_0.Value = 2;
            numericUpDown_first_1.Value = 10;
            numericUpDown_first_2.Value = 14;
            numericUpDown_first_3.Value = 27;
            numericUpDown_first_4.Value = 31;
            numericUpDown_first_5.Value = 39;
            numericUpDown_first_6.Value = 46;
            numericUpDown_first_7.Value = 51;
            numericUpDown_first_8.Value = 64;
            numericUpDown_first_9.Value = 68;
            numericUpDown_first_10.Value = 75;
            numericUpDown_first_11.Value = 82;

            numericUpDown_move_0.Value = 87;
            numericUpDown_move_1.Value = 87;
            numericUpDown_move_2.Value = 87;
            numericUpDown_move_3.Value = 87;
            numericUpDown_move_4.Value = 87;
            numericUpDown_move_5.Value = 87;
            numericUpDown_move_6.Value = 87;
            numericUpDown_move_7.Value = 87;
            numericUpDown_move_8.Value = 87;
            numericUpDown_move_9.Value = 87;
            numericUpDown_move_10.Value = 87;
            numericUpDown_move_11.Value = 87;

            //
            numericUpDown_detect_white.Value = 775;
            numericUpDown_detect_black.Value = 700;
            radioButton_L_B.Checked = true;
            radioButton_R_R.Checked = true;
            numericUpDown_L_Up_Color.Value = 220;
            numericUpDown_R_Up_Color.Value = 250;
            numericUpDown_L_Down_Color.Value = 100;
            numericUpDown_R_Down_Color.Value = 100;
        }
        #endregion



        /// <summary>
        /// Color Type
        /// </summary>
        #region Color type
        private void radiobutton_check(object sender, EventArgs e)
        {
            if (radioButton_L_R.Checked)
            {
                if (radioButton_R_R.Checked)
                    type = 11;
                else if (radioButton_R_G.Checked)
                    type = 12;
                else
                    type = 13;
            }
            else if (radioButton_L_G.Checked)
            {
                if (radioButton_R_R.Checked)
                    type = 21;
                else if (radioButton_R_G.Checked)
                    type = 22;
                else
                    type = 23;
            }
            else
            {
                if (radioButton_R_R.Checked)
                    type = 31;
                else if (radioButton_R_G.Checked)
                    type = 32;
                else
                    type = 33;
            }
        }
        #endregion

        /// <summary>
        /// Get Pixel Color
        /// </summary>
        #region Get Pixel Color
        Color GetPixelColor(Point position)
        {
            Point P = new Point((int)(position.X * intPercent), (int)(position.Y * intPercent));

            using (Bitmap bitmap = new Bitmap(1, 1))
            {
                using (Graphics graphics = Graphics.FromImage(bitmap))
                {
                    graphics.CopyFromScreen(P, new Point(0, 0), new Size(1, 1));
                }
                return bitmap.GetPixel(0, 0);
            }
        }
        private void pictureBox1_Click(object sender, EventArgs e)
        {
            if (radioButton_L.Checked)
            {
                Color c = GetPixelColor(System.Windows.Forms.Cursor.Position);
                pictureBox_L.BackColor = c;
                label_L.Text = $"({c.R},{c.G},{c.B})";
            }
            else
            {
                Color c = GetPixelColor(System.Windows.Forms.Cursor.Position);
                pictureBox_R.BackColor = c;
                label_R.Text = $"({c.R},{c.G},{c.B})";
            }
        }

        
        #endregion

        ///
        //Graphics myGraphics = this.CreateGraphics();

        //Size s = axWindowsMediaPlayer1.Size;
        //s.Width = (int)(s.Width * intPercent);
        //s.Height = 10;

        //Bitmap memoryImage = new Bitmap(s.Width, s.Height, myGraphics);
        //Graphics memoryGraphics = Graphics.FromImage(memoryImage);
        //Point sta = this.axWindowsMediaPlayer1.PointToScreen(Point.Empty);
        //sta.X = (int)(sta.X * intPercent);
        //sta.Y = (int)((sta.Y + (int)numericUpDown_panel2_height.Value)* intPercent);

        //memoryGraphics.CopyFromScreen(sta, new Point(0, 0), s);

        //memoryImage.Save(@"newImg.png");
        ///Original
        //Graphics myGraphics = this.CreateGraphics();

        //Size s = axWindowsMediaPlayer1.Size;
        //s.Width = (int)(s.Width * intPercent);
        //s.Height = (int)(s.Height * intPercent);

        //Bitmap memoryImage = new Bitmap(s.Width, s.Height, myGraphics);
        //Graphics memoryGraphics = Graphics.FromImage(memoryImage);
        //Point sta = this.axWindowsMediaPlayer1.PointToScreen(Point.Empty);
        //sta.X = (int)(sta.X * intPercent);
        //sta.Y = (int)(sta.Y * intPercent);

        //memoryGraphics.CopyFromScreen(sta, new Point(0,0), s);

        //memoryImage.Save(@"newImg.png");
    }
}
