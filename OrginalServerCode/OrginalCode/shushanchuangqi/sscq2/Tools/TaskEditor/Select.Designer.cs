namespace TaskEditor
{
    partial class FormSelect
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewXML = new System.Windows.Forms.DataGridView();
            this.splitContainerSelect = new System.Windows.Forms.SplitContainer();
            this.buttonInsert = new System.Windows.Forms.Button();
            this.textBoxUrl = new System.Windows.Forms.TextBox();
            this.buttonSearchID = new System.Windows.Forms.Button();
            this.textBoxSearchID = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewXML)).BeginInit();
            this.splitContainerSelect.Panel1.SuspendLayout();
            this.splitContainerSelect.Panel2.SuspendLayout();
            this.splitContainerSelect.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataGridViewXML
            // 
            this.dataGridViewXML.AllowUserToAddRows = false;
            this.dataGridViewXML.AllowUserToResizeRows = false;
            this.dataGridViewXML.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewXML.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewXML.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewXML.Location = new System.Drawing.Point(0, 0);
            this.dataGridViewXML.MultiSelect = false;
            this.dataGridViewXML.Name = "dataGridViewXML";
            this.dataGridViewXML.RowHeadersVisible = false;
            this.dataGridViewXML.RowTemplate.Height = 23;
            this.dataGridViewXML.Size = new System.Drawing.Size(795, 429);
            this.dataGridViewXML.TabIndex = 0;
            this.dataGridViewXML.SelectionChanged += new System.EventHandler(this.dataGridViewXML_SelectionChanged);
            // 
            // splitContainerSelect
            // 
            this.splitContainerSelect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerSelect.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainerSelect.Location = new System.Drawing.Point(0, 0);
            this.splitContainerSelect.Name = "splitContainerSelect";
            this.splitContainerSelect.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerSelect.Panel1
            // 
            this.splitContainerSelect.Panel1.Controls.Add(this.dataGridViewXML);
            // 
            // splitContainerSelect.Panel2
            // 
            this.splitContainerSelect.Panel2.Controls.Add(this.buttonInsert);
            this.splitContainerSelect.Panel2.Controls.Add(this.textBoxUrl);
            this.splitContainerSelect.Panel2.Controls.Add(this.buttonSearchID);
            this.splitContainerSelect.Panel2.Controls.Add(this.textBoxSearchID);
            this.splitContainerSelect.Size = new System.Drawing.Size(795, 491);
            this.splitContainerSelect.SplitterDistance = 429;
            this.splitContainerSelect.TabIndex = 1;
            // 
            // buttonInsert
            // 
            this.buttonInsert.Location = new System.Drawing.Point(445, 14);
            this.buttonInsert.Name = "buttonInsert";
            this.buttonInsert.Size = new System.Drawing.Size(75, 23);
            this.buttonInsert.TabIndex = 3;
            this.buttonInsert.Text = "插入";
            this.buttonInsert.UseVisualStyleBackColor = true;
            this.buttonInsert.Visible = false;
            this.buttonInsert.Click += new System.EventHandler(this.buttonInsert_Click);
            // 
            // textBoxUrl
            // 
            this.textBoxUrl.Location = new System.Drawing.Point(264, 16);
            this.textBoxUrl.Name = "textBoxUrl";
            this.textBoxUrl.Size = new System.Drawing.Size(160, 21);
            this.textBoxUrl.TabIndex = 2;
            this.textBoxUrl.Visible = false;
            // 
            // buttonSearchID
            // 
            this.buttonSearchID.Location = new System.Drawing.Point(154, 14);
            this.buttonSearchID.Name = "buttonSearchID";
            this.buttonSearchID.Size = new System.Drawing.Size(75, 23);
            this.buttonSearchID.TabIndex = 1;
            this.buttonSearchID.Text = "搜索ID";
            this.buttonSearchID.UseVisualStyleBackColor = true;
            this.buttonSearchID.Click += new System.EventHandler(this.buttonSearchID_Click);
            // 
            // textBoxSearchID
            // 
            this.textBoxSearchID.Location = new System.Drawing.Point(21, 15);
            this.textBoxSearchID.Name = "textBoxSearchID";
            this.textBoxSearchID.Size = new System.Drawing.Size(115, 21);
            this.textBoxSearchID.TabIndex = 0;
            // 
            // FormSelect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(795, 491);
            this.Controls.Add(this.splitContainerSelect);
            this.Name = "FormSelect";
            this.Text = "选择";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewXML)).EndInit();
            this.splitContainerSelect.Panel1.ResumeLayout(false);
            this.splitContainerSelect.Panel2.ResumeLayout(false);
            this.splitContainerSelect.Panel2.PerformLayout();
            this.splitContainerSelect.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewXML;
        private System.Windows.Forms.SplitContainer splitContainerSelect;
        private System.Windows.Forms.TextBox textBoxSearchID;
        private System.Windows.Forms.Button buttonSearchID;
        private System.Windows.Forms.TextBox textBoxUrl;
        private System.Windows.Forms.Button buttonInsert;
    }
}