namespace WindowsFormsApp1
{
    partial class Load_Mid_Form
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置受控資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_load = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.btn_sixteen = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.richTextBox2 = new System.Windows.Forms.RichTextBox();
            this.btn_Binary = new System.Windows.Forms.Button();
            this.btn_Binary_save = new System.Windows.Forms.Button();
            this.btn_trim = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.openFileDialog2 = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // btn_load
            // 
            this.btn_load.Location = new System.Drawing.Point(21, 12);
            this.btn_load.Name = "btn_load";
            this.btn_load.Size = new System.Drawing.Size(121, 61);
            this.btn_load.TabIndex = 0;
            this.btn_load.Text = "讀檔 mid";
            this.btn_load.UseVisualStyleBackColor = true;
            this.btn_load.Click += new System.EventHandler(this.btn_load_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // btn_sixteen
            // 
            this.btn_sixteen.Location = new System.Drawing.Point(21, 318);
            this.btn_sixteen.Name = "btn_sixteen";
            this.btn_sixteen.Size = new System.Drawing.Size(121, 58);
            this.btn_sixteen.TabIndex = 2;
            this.btn_sixteen.Text = "解析成16進位";
            this.btn_sixteen.UseVisualStyleBackColor = true;
            this.btn_sixteen.Click += new System.EventHandler(this.btn_sixteen_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBox1.Location = new System.Drawing.Point(184, 318);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(1007, 212);
            this.richTextBox1.TabIndex = 3;
            this.richTextBox1.Text = "";
            // 
            // richTextBox2
            // 
            this.richTextBox2.Location = new System.Drawing.Point(184, 108);
            this.richTextBox2.Name = "richTextBox2";
            this.richTextBox2.Size = new System.Drawing.Size(1007, 204);
            this.richTextBox2.TabIndex = 4;
            this.richTextBox2.Text = "";
            // 
            // btn_Binary
            // 
            this.btn_Binary.Location = new System.Drawing.Point(21, 108);
            this.btn_Binary.Name = "btn_Binary";
            this.btn_Binary.Size = new System.Drawing.Size(121, 68);
            this.btn_Binary.TabIndex = 5;
            this.btn_Binary.Text = "解析成2進位";
            this.btn_Binary.UseVisualStyleBackColor = true;
            this.btn_Binary.Click += new System.EventHandler(this.btn_binary_Click);
            // 
            // btn_Binary_save
            // 
            this.btn_Binary_save.Location = new System.Drawing.Point(21, 205);
            this.btn_Binary_save.Name = "btn_Binary_save";
            this.btn_Binary_save.Size = new System.Drawing.Size(121, 38);
            this.btn_Binary_save.TabIndex = 6;
            this.btn_Binary_save.Text = "2進位存檔";
            this.btn_Binary_save.UseVisualStyleBackColor = true;
            this.btn_Binary_save.Click += new System.EventHandler(this.btn_Binary_save_Click);
            // 
            // btn_trim
            // 
            this.btn_trim.Location = new System.Drawing.Point(407, 12);
            this.btn_trim.Name = "btn_trim";
            this.btn_trim.Size = new System.Drawing.Size(129, 61);
            this.btn_trim.TabIndex = 7;
            this.btn_trim.Text = "Save txt to mid";
            this.btn_trim.UseVisualStyleBackColor = true;
            this.btn_trim.Click += new System.EventHandler(this.btn_save_txtTomid_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(193, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(133, 61);
            this.button1.TabIndex = 8;
            this.button1.Text = "讀檔 txt";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btn_load_txt_Click);
            // 
            // openFileDialog2
            // 
            this.openFileDialog2.FileName = "openFileDialog2";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1203, 542);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btn_trim);
            this.Controls.Add(this.btn_Binary_save);
            this.Controls.Add(this.btn_Binary);
            this.Controls.Add(this.richTextBox2);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.btn_sixteen);
            this.Controls.Add(this.btn_load);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_load;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button btn_sixteen;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.RichTextBox richTextBox2;
        private System.Windows.Forms.Button btn_Binary;
        private System.Windows.Forms.Button btn_Binary_save;
        private System.Windows.Forms.Button btn_trim;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.OpenFileDialog openFileDialog2;
    }
}

