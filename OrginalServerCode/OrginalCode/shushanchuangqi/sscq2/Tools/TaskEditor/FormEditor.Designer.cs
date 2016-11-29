namespace TaskEditor
{
    partial class FormEditor
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

        protected void InitLastDir()
        {
            System.IO.FileInfo fi = new System.IO.FileInfo("LastOpenedDir.txt");
            if (fi.Exists)
            {
                System.IO.FileStream fs = fi.OpenRead();
                byte[] path = new byte[fs.Length*3+1];
                fs.Read(path, 0, (int)fs.Length);
                this.textBoxFolderPath.Text = System.Text.Encoding.Default.GetString(path);
            }
        }
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControlConfig = new System.Windows.Forms.TabControl();
            this.tabPageBasic = new System.Windows.Forms.TabPage();
            this.groupBox63 = new System.Windows.Forms.GroupBox();
            this.rbtGuideFind = new System.Windows.Forms.RadioButton();
            this.rbtGuildJump = new System.Windows.Forms.RadioButton();
            this.groupBox44 = new System.Windows.Forms.GroupBox();
            this.comboBoxStarTask = new System.Windows.Forms.ComboBox();
            this.textBoxStarTaskGroupID = new System.Windows.Forms.TextBox();
            this.buttonSelectStarTask = new System.Windows.Forms.Button();
            this.label129 = new System.Windows.Forms.Label();
            this.label128 = new System.Windows.Forms.Label();
            this.label127 = new System.Windows.Forms.Label();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.checkBox_build = new System.Windows.Forms.CheckBox();
            this.checkBox_behave = new System.Windows.Forms.CheckBox();
            this.checkBox_grow = new System.Windows.Forms.CheckBox();
            this.checkBoxGather = new System.Windows.Forms.CheckBox();
            this.checkBoxTalk = new System.Windows.Forms.CheckBox();
            this.checkBoxProbe = new System.Windows.Forms.CheckBox();
            this.checkBoxCollect = new System.Windows.Forms.CheckBox();
            this.checkBoxKill = new System.Windows.Forms.CheckBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.buttonTaskSubmitDel = new System.Windows.Forms.Button();
            this.dataGridViewTaskSubmit = new System.Windows.Forms.DataGridView();
            this.SubmitTargetID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SubmitTargetType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SubmitTargetName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonTaskSubmitAdd = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxTaskSubmitName = new System.Windows.Forms.TextBox();
            this.textBoxTaskSubmitID = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.buttonTaskSubmit = new System.Windows.Forms.Button();
            this.comboBoxTaskSubmit = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.buttonTaskStartDel = new System.Windows.Forms.Button();
            this.buttonTaskStartAdd = new System.Windows.Forms.Button();
            this.buttonTaskStart = new System.Windows.Forms.Button();
            this.dataGridViewTaskStart = new System.Windows.Forms.DataGridView();
            this.StartTargetID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.StartTargetType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.StartTargetName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxTaskStartName = new System.Windows.Forms.TextBox();
            this.textBoxTaskStartID = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.comboBoxTaskStart = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.cbIsLevel = new System.Windows.Forms.CheckBox();
            this.checkBox_canGiveUp = new System.Windows.Forms.CheckBox();
            this.groupBox46 = new System.Windows.Forms.GroupBox();
            this.radioButton_repeat = new System.Windows.Forms.RadioButton();
            this.radioButton_noRepeat = new System.Windows.Forms.RadioButton();
            this.radioButton_dayRepeat = new System.Windows.Forms.RadioButton();
            this.label38 = new System.Windows.Forms.Label();
            this.textBoxRepeatCount = new System.Windows.Forms.TextBox();
            this.checkBoxIsShared = new System.Windows.Forms.CheckBox();
            this.checkBoxIsOpen = new System.Windows.Forms.CheckBox();
            this.groupBox33 = new System.Windows.Forms.GroupBox();
            this.radioButton_NomalTask = new System.Windows.Forms.RadioButton();
            this.radioButton_rewardTask = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBoxTaskType = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxTaskLevel = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxTaskName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxTaskID = new System.Windows.Forms.TextBox();
            this.tabPageDesc = new System.Windows.Forms.TabPage();
            this.buttonColorMode = new System.Windows.Forms.Button();
            this.buttonEditMode = new System.Windows.Forms.Button();
            this.buttonChooseColor = new System.Windows.Forms.Button();
            this.buttonInsertGather = new System.Windows.Forms.Button();
            this.buttonInsertNpcID = new System.Windows.Forms.Button();
            this.buttonInsertMonsterID = new System.Windows.Forms.Button();
            this.buttonInsertClan = new System.Windows.Forms.Button();
            this.buttonInsertName = new System.Windows.Forms.Button();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.richTextBoxAward = new System.Windows.Forms.RichTextBox();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.textBoxTaskFinish = new System.Windows.Forms.RichTextBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.textBoxTaskFail = new System.Windows.Forms.RichTextBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.textBoxTaskPurpose = new System.Windows.Forms.RichTextBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.textBoxTaskDesc = new System.Windows.Forms.RichTextBox();
            this.tabPageLimit = new System.Windows.Forms.TabPage();
            this.groupBox59 = new System.Windows.Forms.GroupBox();
            this.textBoxReputeMax = new System.Windows.Forms.TextBox();
            this.label55 = new System.Windows.Forms.Label();
            this.textBoxReputeMin = new System.Windows.Forms.TextBox();
            this.label56 = new System.Windows.Forms.Label();
            this.groupBox56 = new System.Windows.Forms.GroupBox();
            this.button_limit_propRemove = new System.Windows.Forms.Button();
            this.groupBox57 = new System.Windows.Forms.GroupBox();
            this.textBox_limit_roleProp = new System.Windows.Forms.TextBox();
            this.comboBox_limit_roleProp = new System.Windows.Forms.ComboBox();
            this.label124 = new System.Windows.Forms.Label();
            this.label125 = new System.Windows.Forms.Label();
            this.button_limit_propAdd = new System.Windows.Forms.Button();
            this.groupBox58 = new System.Windows.Forms.GroupBox();
            this.textBox_limit_campName = new System.Windows.Forms.TextBox();
            this.textBox_limit_campID = new System.Windows.Forms.TextBox();
            this.label126 = new System.Windows.Forms.Label();
            this.button_limit_selectCamp = new System.Windows.Forms.Button();
            this.label135 = new System.Windows.Forms.Label();
            this.dataGridView_limit_prop = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn32 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn33 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox31 = new System.Windows.Forms.GroupBox();
            this.button_preTaskRemove = new System.Windows.Forms.Button();
            this.groupBox55 = new System.Windows.Forms.GroupBox();
            this.radioButton_preTaskOne = new System.Windows.Forms.RadioButton();
            this.radioButton_preTaskAll = new System.Windows.Forms.RadioButton();
            this.dataGridViewPreTask = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumnTaskID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumnTaskName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button_preTaskAdd = new System.Windows.Forms.Button();
            this.textBoxPreTaskName = new System.Windows.Forms.TextBox();
            this.textBoxPreTaskID = new System.Windows.Forms.TextBox();
            this.label66 = new System.Windows.Forms.Label();
            this.label65 = new System.Windows.Forms.Label();
            this.buttonSelectPreTask = new System.Windows.Forms.Button();
            this.label64 = new System.Windows.Forms.Label();
            this.groupBox30 = new System.Windows.Forms.GroupBox();
            this.comboBox_SelectJob = new System.Windows.Forms.ComboBox();
            this.button_careerRemove = new System.Windows.Forms.Button();
            this.button_careerAdd = new System.Windows.Forms.Button();
            this.dataGridViewJobLimit = new System.Windows.Forms.DataGridView();
            this.JobID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.JobName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label63 = new System.Windows.Forms.Label();
            this.groupBox29 = new System.Windows.Forms.GroupBox();
            this.comboBox_limit_family = new System.Windows.Forms.ComboBox();
            this.groupBox28 = new System.Windows.Forms.GroupBox();
            this.comboBox_limitCamp = new System.Windows.Forms.ComboBox();
            this.groupBox27 = new System.Windows.Forms.GroupBox();
            this.comboBoxRelationLimit = new System.Windows.Forms.ComboBox();
            this.label62 = new System.Windows.Forms.Label();
            this.groupBox26 = new System.Windows.Forms.GroupBox();
            this.textBoxGradeMax = new System.Windows.Forms.TextBox();
            this.textBoxGradeMin = new System.Windows.Forms.TextBox();
            this.label60 = new System.Windows.Forms.Label();
            this.label61 = new System.Windows.Forms.Label();
            this.groupBox25 = new System.Windows.Forms.GroupBox();
            this.textBoxHourTo = new System.Windows.Forms.TextBox();
            this.checkBoxTimeLimit = new System.Windows.Forms.CheckBox();
            this.textBoxHourFrom = new System.Windows.Forms.TextBox();
            this.label59 = new System.Windows.Forms.Label();
            this.checkBoxDateLimit = new System.Windows.Forms.CheckBox();
            this.dateTimePickerDateTo = new System.Windows.Forms.DateTimePicker();
            this.dateTimePickerDateFrom = new System.Windows.Forms.DateTimePicker();
            this.label58 = new System.Windows.Forms.Label();
            this.label57 = new System.Windows.Forms.Label();
            this.groupBox23 = new System.Windows.Forms.GroupBox();
            this.comboBoxSexLimit = new System.Windows.Forms.ComboBox();
            this.label54 = new System.Windows.Forms.Label();
            this.tabPageProc = new System.Windows.Forms.TabPage();
            this.tabControlProcess = new System.Windows.Forms.TabControl();
            this.tabPageGeneral = new System.Windows.Forms.TabPage();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.dataGridViewGiveItem = new System.Windows.Forms.DataGridView();
            this.GiveItemID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GiveItemName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GiveItemCount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonGiveItemDel = new System.Windows.Forms.Button();
            this.buttonGiveItemAdd = new System.Windows.Forms.Button();
            this.textBoxGiveItemCount = new System.Windows.Forms.TextBox();
            this.textBoxGiveItemID = new System.Windows.Forms.TextBox();
            this.textBoxGiveItemName = new System.Windows.Forms.TextBox();
            this.label39 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.buttonGiveItem = new System.Windows.Forms.Button();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.textBoxLimitTime = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.tabPageKill = new System.Windows.Forms.TabPage();
            this.groupBox14 = new System.Windows.Forms.GroupBox();
            this.textBoxKillMonsterParam = new System.Windows.Forms.TextBox();
            this.label134 = new System.Windows.Forms.Label();
            this.dataGridViewKillMonster = new System.Windows.Forms.DataGridView();
            this.MonsterID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MonsterName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MonsterNum = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Fake = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.strParam = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonKillMonsterDel = new System.Windows.Forms.Button();
            this.buttonKillMonsterAdd = new System.Windows.Forms.Button();
            this.label19 = new System.Windows.Forms.Label();
            this.textBoxKillMonsterCount = new System.Windows.Forms.TextBox();
            this.textBoxKillMonsterID = new System.Windows.Forms.TextBox();
            this.textBoxKillMonsterName = new System.Windows.Forms.TextBox();
            this.label40 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.buttonKillMonster = new System.Windows.Forms.Button();
            this.label17 = new System.Windows.Forms.Label();
            this.tabPageGrow = new System.Windows.Forms.TabPage();
            this.label145 = new System.Windows.Forms.Label();
            this.groupBox64 = new System.Windows.Forms.GroupBox();
            this.txt_GrowName = new System.Windows.Forms.TextBox();
            this.label143 = new System.Windows.Forms.Label();
            this.txt_GrowID = new System.Windows.Forms.TextBox();
            this.label144 = new System.Windows.Forms.Label();
            this.button_growRemove = new System.Windows.Forms.Button();
            this.button_growAdd = new System.Windows.Forms.Button();
            this.dataGridView_grow = new System.Windows.Forms.DataGridView();
            this.roleProperty = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.roleValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.extid = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.extname = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox48 = new System.Windows.Forms.GroupBox();
            this.textBox_campName = new System.Windows.Forms.TextBox();
            this.textBox_campID = new System.Windows.Forms.TextBox();
            this.label113 = new System.Windows.Forms.Label();
            this.button_selectCamp = new System.Windows.Forms.Button();
            this.label114 = new System.Windows.Forms.Label();
            this.groupBox47 = new System.Windows.Forms.GroupBox();
            this.textBox_roleProp = new System.Windows.Forms.TextBox();
            this.comboBox_roleProp = new System.Windows.Forms.ComboBox();
            this.label112 = new System.Windows.Forms.Label();
            this.label111 = new System.Windows.Forms.Label();
            this.tabPageCollect = new System.Windows.Forms.TabPage();
            this.groupBox60 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label147 = new System.Windows.Forms.Label();
            this.txtItemParam = new System.Windows.Forms.TextBox();
            this.label146 = new System.Windows.Forms.Label();
            this.txtMonsterName = new System.Windows.Forms.TextBox();
            this.label142 = new System.Windows.Forms.Label();
            this.txtItemName = new System.Windows.Forms.TextBox();
            this.label141 = new System.Windows.Forms.Label();
            this.txtItemCount = new System.Windows.Forms.TextBox();
            this.label140 = new System.Windows.Forms.Label();
            this.dgvKillMonsterItem = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn34 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.monster = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn35 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn36 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridItemParam = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.btnCollectItemDel = new System.Windows.Forms.Button();
            this.btnCollectItemAdd = new System.Windows.Forms.Button();
            this.txtItemID = new System.Windows.Forms.TextBox();
            this.txtCollectMonsterID = new System.Windows.Forms.TextBox();
            this.label136 = new System.Windows.Forms.Label();
            this.label137 = new System.Windows.Forms.Label();
            this.label138 = new System.Windows.Forms.Label();
            this.CollectMonster = new System.Windows.Forms.Button();
            this.label139 = new System.Windows.Forms.Label();
            this.groupBox15 = new System.Windows.Forms.GroupBox();
            this.dataGridViewCollectItem = new System.Windows.Forms.DataGridView();
            this.CollectItemID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CollectItemName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CollectItemCount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonCollectItemDel = new System.Windows.Forms.Button();
            this.buttonCollectItemAdd = new System.Windows.Forms.Button();
            this.textBoxCollectItemCount = new System.Windows.Forms.TextBox();
            this.textBoxCollectItemID = new System.Windows.Forms.TextBox();
            this.textBoxCollectItemName = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.label41 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.buttonCollectItem = new System.Windows.Forms.Button();
            this.label20 = new System.Windows.Forms.Label();
            this.tabPageGather = new System.Windows.Forms.TabPage();
            this.groupBox45 = new System.Windows.Forms.GroupBox();
            this.textBoxGatherParam = new System.Windows.Forms.TextBox();
            this.label148 = new System.Windows.Forms.Label();
            this.dataGridViewGather = new System.Windows.Forms.DataGridView();
            this.GatherID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GatherCount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GatherParam = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxGatherCount = new System.Windows.Forms.TextBox();
            this.textBoxGatherID = new System.Windows.Forms.TextBox();
            this.buttonDelGather = new System.Windows.Forms.Button();
            this.label132 = new System.Windows.Forms.Label();
            this.buttonAddGather = new System.Windows.Forms.Button();
            this.label131 = new System.Windows.Forms.Label();
            this.buttonSelectGather = new System.Windows.Forms.Button();
            this.label130 = new System.Windows.Forms.Label();
            this.tabPageProbe = new System.Windows.Forms.TabPage();
            this.groupBox32 = new System.Windows.Forms.GroupBox();
            this.textBoxProbeParam = new System.Windows.Forms.TextBox();
            this.label149 = new System.Windows.Forms.Label();
            this.groupBox62 = new System.Windows.Forms.GroupBox();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.dataGridViewProbe = new System.Windows.Forms.DataGridView();
            this.MapID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MapName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CoordinateX1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CoordinateZ1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CoordinateX2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CoordinateZ2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CoordinateParam = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonDelProbe = new System.Windows.Forms.Button();
            this.buttonAddProbe = new System.Windows.Forms.Button();
            this.buttonSelectProbe = new System.Windows.Forms.Button();
            this.textBoxProbeZ2 = new System.Windows.Forms.TextBox();
            this.textBoxProbeX2 = new System.Windows.Forms.TextBox();
            this.textBoxProbeZ1 = new System.Windows.Forms.TextBox();
            this.textBoxProbeX1 = new System.Windows.Forms.TextBox();
            this.textBoxProbeMapName = new System.Windows.Forms.TextBox();
            this.textBoxProbeMapID = new System.Windows.Forms.TextBox();
            this.label73 = new System.Windows.Forms.Label();
            this.label72 = new System.Windows.Forms.Label();
            this.label71 = new System.Windows.Forms.Label();
            this.label70 = new System.Windows.Forms.Label();
            this.label69 = new System.Windows.Forms.Label();
            this.label68 = new System.Windows.Forms.Label();
            this.label67 = new System.Windows.Forms.Label();
            this.tabPageBehave = new System.Windows.Forms.TabPage();
            this.dataGridView_behave = new System.Windows.Forms.DataGridView();
            this.roleAction = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.roleActionValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.roleActionParam = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button_behaveRemove = new System.Windows.Forms.Button();
            this.button_behaveAdd = new System.Windows.Forms.Button();
            this.groupBox50 = new System.Windows.Forms.GroupBox();
            this.textBox_behave_param = new System.Windows.Forms.TextBox();
            this.label133 = new System.Windows.Forms.Label();
            this.textBox_behave_action = new System.Windows.Forms.TextBox();
            this.comboBox_behave_action = new System.Windows.Forms.ComboBox();
            this.label116 = new System.Windows.Forms.Label();
            this.label117 = new System.Windows.Forms.Label();
            this.tabPageBuild = new System.Windows.Forms.TabPage();
            this.groupBox51 = new System.Windows.Forms.GroupBox();
            this.textBox_tecValue = new System.Windows.Forms.TextBox();
            this.textBox_tecID = new System.Windows.Forms.TextBox();
            this.textBox_tecName = new System.Windows.Forms.TextBox();
            this.button_tecAdd = new System.Windows.Forms.Button();
            this.label120 = new System.Windows.Forms.Label();
            this.label121 = new System.Windows.Forms.Label();
            this.button_selectTec = new System.Windows.Forms.Button();
            this.label122 = new System.Windows.Forms.Label();
            this.dataGridView_build = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buildName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buildValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox49 = new System.Windows.Forms.GroupBox();
            this.textBox_buildLevel = new System.Windows.Forms.TextBox();
            this.textBox_buildID = new System.Windows.Forms.TextBox();
            this.textBox_buildName = new System.Windows.Forms.TextBox();
            this.button_buildAdd = new System.Windows.Forms.Button();
            this.label119 = new System.Windows.Forms.Label();
            this.label118 = new System.Windows.Forms.Label();
            this.button_selectBuild = new System.Windows.Forms.Button();
            this.label115 = new System.Windows.Forms.Label();
            this.button_tecRemove = new System.Windows.Forms.Button();
            this.tabPageTalk = new System.Windows.Forms.TabPage();
            this.groupBox24 = new System.Windows.Forms.GroupBox();
            this.dataGridViewReceiveItem = new System.Windows.Forms.DataGridView();
            this.ReveiveItem = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ReceiveName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ReceiveCount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxReceiveItemCount = new System.Windows.Forms.TextBox();
            this.textBoxReceiveItemName = new System.Windows.Forms.TextBox();
            this.textBoxReceiveItemID = new System.Windows.Forms.TextBox();
            this.label51 = new System.Windows.Forms.Label();
            this.label50 = new System.Windows.Forms.Label();
            this.label49 = new System.Windows.Forms.Label();
            this.buttonReceiveItemDel = new System.Windows.Forms.Button();
            this.buttonReceiveItemAdd = new System.Windows.Forms.Button();
            this.buttonReceiveItem = new System.Windows.Forms.Button();
            this.label48 = new System.Windows.Forms.Label();
            this.groupBoxNpcTalk = new System.Windows.Forms.GroupBox();
            this.label53 = new System.Windows.Forms.Label();
            this.label52 = new System.Windows.Forms.Label();
            this.buttonUpdateTalkWords = new System.Windows.Forms.Button();
            this.buttonAddTalkWords = new System.Windows.Forms.Button();
            this.textBoxNPCWords = new System.Windows.Forms.TextBox();
            this.textBoxPCWords = new System.Windows.Forms.TextBox();
            this.groupBox22 = new System.Windows.Forms.GroupBox();
            this.buttonDelTalkWords = new System.Windows.Forms.Button();
            this.buttonDownNpcWords = new System.Windows.Forms.Button();
            this.buttonUpNpcWords = new System.Windows.Forms.Button();
            this.dataGridViewTalkWords = new System.Windows.Forms.DataGridView();
            this.Index = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PCWords = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.NPCWords = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox21 = new System.Windows.Forms.GroupBox();
            this.buttonDelTalkNpc = new System.Windows.Forms.Button();
            this.buttonAddTalkNpc = new System.Windows.Forms.Button();
            this.dataGridViewNpcTalk = new System.Windows.Forms.DataGridView();
            this.NpcTalkID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.NpcTalkName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxNpcTalkName = new System.Windows.Forms.TextBox();
            this.label47 = new System.Windows.Forms.Label();
            this.textBoxNpcTalkID = new System.Windows.Forms.TextBox();
            this.label46 = new System.Windows.Forms.Label();
            this.buttonNpcTalk = new System.Windows.Forms.Button();
            this.label45 = new System.Windows.Forms.Label();
            this.tabPageAward = new System.Windows.Forms.TabPage();
            this.groupBox20 = new System.Windows.Forms.GroupBox();
            this.label123 = new System.Windows.Forms.Label();
            this.cmbJobLimitS = new System.Windows.Forms.ComboBox();
            this.buttonOptItemDel = new System.Windows.Forms.Button();
            this.buttonOptItemAdd = new System.Windows.Forms.Button();
            this.dataGridViewOptItem = new System.Windows.Forms.DataGridView();
            this.OptItemID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.OptItemName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.OptItemCount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn37 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxOptItemCount = new System.Windows.Forms.TextBox();
            this.label37 = new System.Windows.Forms.Label();
            this.textBoxOptItemName = new System.Windows.Forms.TextBox();
            this.label44 = new System.Windows.Forms.Label();
            this.textBoxOptItemID = new System.Windows.Forms.TextBox();
            this.label36 = new System.Windows.Forms.Label();
            this.buttonOptItem = new System.Windows.Forms.Button();
            this.label35 = new System.Windows.Forms.Label();
            this.groupBox19 = new System.Windows.Forms.GroupBox();
            this.cmbJobLimit = new System.Windows.Forms.ComboBox();
            this.label25 = new System.Windows.Forms.Label();
            this.buttonMustItemDel = new System.Windows.Forms.Button();
            this.buttonMustItemAdd = new System.Windows.Forms.Button();
            this.dataGridViewMustItem = new System.Windows.Forms.DataGridView();
            this.AwardItemID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AwradItemName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AwardItemCount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.JobLimit = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxMustItemCount = new System.Windows.Forms.TextBox();
            this.label34 = new System.Windows.Forms.Label();
            this.textBoxMustItemID = new System.Windows.Forms.TextBox();
            this.label43 = new System.Windows.Forms.Label();
            this.textBoxMustItemName = new System.Windows.Forms.TextBox();
            this.label33 = new System.Windows.Forms.Label();
            this.buttonMustItem = new System.Windows.Forms.Button();
            this.label32 = new System.Windows.Forms.Label();
            this.groupBox18 = new System.Windows.Forms.GroupBox();
            this.dataGridViewTitle = new System.Windows.Forms.DataGridView();
            this.TitleID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TitleName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonDelTitle = new System.Windows.Forms.Button();
            this.buttonAddTitle = new System.Windows.Forms.Button();
            this.textBoxTitleName = new System.Windows.Forms.TextBox();
            this.label42 = new System.Windows.Forms.Label();
            this.textBoxTitleID = new System.Windows.Forms.TextBox();
            this.label31 = new System.Windows.Forms.Label();
            this.buttonSelectTitle = new System.Windows.Forms.Button();
            this.label30 = new System.Windows.Forms.Label();
            this.groupBox16 = new System.Windows.Forms.GroupBox();
            this.dgvMercenAward = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn38 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn39 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.pos = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button_award_generalRemove = new System.Windows.Forms.Button();
            this.groupBox54 = new System.Windows.Forms.GroupBox();
            this.textBox_award_general = new System.Windows.Forms.TextBox();
            this.comboBox_award_general = new System.Windows.Forms.ComboBox();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.button_award_generalAdd = new System.Windows.Forms.Button();
            this.dataGridView_award_general = new System.Windows.Forms.DataGridView();
            this.awardGeneralName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.awardGeneralValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox53 = new System.Windows.Forms.GroupBox();
            this.button_award_propRemove = new System.Windows.Forms.Button();
            this.groupBox52 = new System.Windows.Forms.GroupBox();
            this.textBox_award_roleProp = new System.Windows.Forms.TextBox();
            this.comboBox_award_roleProp = new System.Windows.Forms.ComboBox();
            this.label28 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.button_award_propAdd = new System.Windows.Forms.Button();
            this.groupBox17 = new System.Windows.Forms.GroupBox();
            this.textBox_award_campName = new System.Windows.Forms.TextBox();
            this.textBox_award_campID = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.button_award_selectCamp = new System.Windows.Forms.Button();
            this.label27 = new System.Windows.Forms.Label();
            this.dataGridView_award_prop = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn30 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn31 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTaskList = new System.Windows.Forms.DataGridView();
            this.TaskID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TaskLevel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TaskName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TaskType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.OpenState = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ShareState = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CanGiveUp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RepeatState = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.FinishLimit = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AwardLinkLevel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.splitContainerTask = new System.Windows.Forms.SplitContainer();
            this.textBoxFolderPath = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.buttonSearchName = new System.Windows.Forms.Button();
            this.buttonSearchID = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxSearchTask = new System.Windows.Forms.TextBox();
            this.buttonSelectFile = new System.Windows.Forms.Button();
            this.buttonSelectFolder = new System.Windows.Forms.Button();
            this.buttonSaveAllTask = new System.Windows.Forms.Button();
            this.buttonOpenAllTask = new System.Windows.Forms.Button();
            this.buttonUnloadTask = new System.Windows.Forms.Button();
            this.buttonSaveTask = new System.Windows.Forms.Button();
            this.buttonOpenTask = new System.Windows.Forms.Button();
            this.buttonNewTask = new System.Windows.Forms.Button();
            this.panelTaskList = new System.Windows.Forms.Panel();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.textBox16 = new System.Windows.Forms.TextBox();
            this.textBox17 = new System.Windows.Forms.TextBox();
            this.textBox18 = new System.Windows.Forms.TextBox();
            this.textBox19 = new System.Windows.Forms.TextBox();
            this.textBox27 = new System.Windows.Forms.TextBox();
            this.textBox28 = new System.Windows.Forms.TextBox();
            this.label74 = new System.Windows.Forms.Label();
            this.label75 = new System.Windows.Forms.Label();
            this.label76 = new System.Windows.Forms.Label();
            this.label77 = new System.Windows.Forms.Label();
            this.label78 = new System.Windows.Forms.Label();
            this.label79 = new System.Windows.Forms.Label();
            this.label80 = new System.Windows.Forms.Label();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.textBox29 = new System.Windows.Forms.TextBox();
            this.textBox30 = new System.Windows.Forms.TextBox();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox34 = new System.Windows.Forms.GroupBox();
            this.dataGridView3 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn8 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn9 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.textBox31 = new System.Windows.Forms.TextBox();
            this.textBox32 = new System.Windows.Forms.TextBox();
            this.textBox33 = new System.Windows.Forms.TextBox();
            this.label81 = new System.Windows.Forms.Label();
            this.label82 = new System.Windows.Forms.Label();
            this.label83 = new System.Windows.Forms.Label();
            this.label84 = new System.Windows.Forms.Label();
            this.button14 = new System.Windows.Forms.Button();
            this.groupBox35 = new System.Windows.Forms.GroupBox();
            this.label85 = new System.Windows.Forms.Label();
            this.textBox34 = new System.Windows.Forms.TextBox();
            this.label86 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.groupBox36 = new System.Windows.Forms.GroupBox();
            this.dataGridView4 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn10 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn11 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn12 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button15 = new System.Windows.Forms.Button();
            this.button16 = new System.Windows.Forms.Button();
            this.label87 = new System.Windows.Forms.Label();
            this.textBox35 = new System.Windows.Forms.TextBox();
            this.textBox36 = new System.Windows.Forms.TextBox();
            this.textBox37 = new System.Windows.Forms.TextBox();
            this.label88 = new System.Windows.Forms.Label();
            this.label89 = new System.Windows.Forms.Label();
            this.button17 = new System.Windows.Forms.Button();
            this.label90 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.groupBox37 = new System.Windows.Forms.GroupBox();
            this.dataGridView5 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn13 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn14 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn15 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button18 = new System.Windows.Forms.Button();
            this.button22 = new System.Windows.Forms.Button();
            this.textBox38 = new System.Windows.Forms.TextBox();
            this.textBox39 = new System.Windows.Forms.TextBox();
            this.textBox40 = new System.Windows.Forms.TextBox();
            this.label91 = new System.Windows.Forms.Label();
            this.label92 = new System.Windows.Forms.Label();
            this.label93 = new System.Windows.Forms.Label();
            this.button23 = new System.Windows.Forms.Button();
            this.label94 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.groupBox38 = new System.Windows.Forms.GroupBox();
            this.dataGridView7 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn16 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn17 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn18 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn19 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn20 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn21 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBox41 = new System.Windows.Forms.TextBox();
            this.textBox42 = new System.Windows.Forms.TextBox();
            this.textBox43 = new System.Windows.Forms.TextBox();
            this.textBox44 = new System.Windows.Forms.TextBox();
            this.label95 = new System.Windows.Forms.Label();
            this.label96 = new System.Windows.Forms.Label();
            this.label97 = new System.Windows.Forms.Label();
            this.label98 = new System.Windows.Forms.Label();
            this.label99 = new System.Windows.Forms.Label();
            this.label100 = new System.Windows.Forms.Label();
            this.label101 = new System.Windows.Forms.Label();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.groupBox39 = new System.Windows.Forms.GroupBox();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.groupBox40 = new System.Windows.Forms.GroupBox();
            this.dataGridView8 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn22 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn23 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn24 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBox45 = new System.Windows.Forms.TextBox();
            this.textBox46 = new System.Windows.Forms.TextBox();
            this.textBox47 = new System.Windows.Forms.TextBox();
            this.label102 = new System.Windows.Forms.Label();
            this.label103 = new System.Windows.Forms.Label();
            this.label104 = new System.Windows.Forms.Label();
            this.button24 = new System.Windows.Forms.Button();
            this.button25 = new System.Windows.Forms.Button();
            this.button26 = new System.Windows.Forms.Button();
            this.label105 = new System.Windows.Forms.Label();
            this.groupBox41 = new System.Windows.Forms.GroupBox();
            this.label106 = new System.Windows.Forms.Label();
            this.label107 = new System.Windows.Forms.Label();
            this.button27 = new System.Windows.Forms.Button();
            this.button28 = new System.Windows.Forms.Button();
            this.textBox48 = new System.Windows.Forms.TextBox();
            this.textBox49 = new System.Windows.Forms.TextBox();
            this.groupBox42 = new System.Windows.Forms.GroupBox();
            this.button29 = new System.Windows.Forms.Button();
            this.button30 = new System.Windows.Forms.Button();
            this.button31 = new System.Windows.Forms.Button();
            this.dataGridView9 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn25 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn26 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn27 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox43 = new System.Windows.Forms.GroupBox();
            this.button32 = new System.Windows.Forms.Button();
            this.button33 = new System.Windows.Forms.Button();
            this.dataGridView10 = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn28 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn29 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBox50 = new System.Windows.Forms.TextBox();
            this.label108 = new System.Windows.Forms.Label();
            this.textBox51 = new System.Windows.Forms.TextBox();
            this.label109 = new System.Windows.Forms.Label();
            this.button34 = new System.Windows.Forms.Button();
            this.label110 = new System.Windows.Forms.Label();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.tabControlConfig.SuspendLayout();
            this.tabPageBasic.SuspendLayout();
            this.groupBox63.SuspendLayout();
            this.groupBox44.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTaskSubmit)).BeginInit();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTaskStart)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox46.SuspendLayout();
            this.groupBox33.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabPageDesc.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.tabPageLimit.SuspendLayout();
            this.groupBox59.SuspendLayout();
            this.groupBox56.SuspendLayout();
            this.groupBox57.SuspendLayout();
            this.groupBox58.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_limit_prop)).BeginInit();
            this.groupBox31.SuspendLayout();
            this.groupBox55.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewPreTask)).BeginInit();
            this.groupBox30.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewJobLimit)).BeginInit();
            this.groupBox29.SuspendLayout();
            this.groupBox28.SuspendLayout();
            this.groupBox27.SuspendLayout();
            this.groupBox26.SuspendLayout();
            this.groupBox25.SuspendLayout();
            this.groupBox23.SuspendLayout();
            this.tabPageProc.SuspendLayout();
            this.tabControlProcess.SuspendLayout();
            this.tabPageGeneral.SuspendLayout();
            this.groupBox13.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewGiveItem)).BeginInit();
            this.groupBox12.SuspendLayout();
            this.tabPageKill.SuspendLayout();
            this.groupBox14.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewKillMonster)).BeginInit();
            this.tabPageGrow.SuspendLayout();
            this.groupBox64.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_grow)).BeginInit();
            this.groupBox48.SuspendLayout();
            this.groupBox47.SuspendLayout();
            this.tabPageCollect.SuspendLayout();
            this.groupBox60.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvKillMonsterItem)).BeginInit();
            this.groupBox15.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCollectItem)).BeginInit();
            this.tabPageGather.SuspendLayout();
            this.groupBox45.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewGather)).BeginInit();
            this.tabPageProbe.SuspendLayout();
            this.groupBox32.SuspendLayout();
            this.groupBox62.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewProbe)).BeginInit();
            this.tabPageBehave.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_behave)).BeginInit();
            this.groupBox50.SuspendLayout();
            this.tabPageBuild.SuspendLayout();
            this.groupBox51.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_build)).BeginInit();
            this.groupBox49.SuspendLayout();
            this.tabPageTalk.SuspendLayout();
            this.groupBox24.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewReceiveItem)).BeginInit();
            this.groupBoxNpcTalk.SuspendLayout();
            this.groupBox22.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTalkWords)).BeginInit();
            this.groupBox21.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewNpcTalk)).BeginInit();
            this.tabPageAward.SuspendLayout();
            this.groupBox20.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewOptItem)).BeginInit();
            this.groupBox19.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMustItem)).BeginInit();
            this.groupBox18.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTitle)).BeginInit();
            this.groupBox16.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvMercenAward)).BeginInit();
            this.groupBox54.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_award_general)).BeginInit();
            this.groupBox53.SuspendLayout();
            this.groupBox52.SuspendLayout();
            this.groupBox17.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_award_prop)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTaskList)).BeginInit();
            this.splitContainerTask.Panel1.SuspendLayout();
            this.splitContainerTask.Panel2.SuspendLayout();
            this.splitContainerTask.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.panelTaskList.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.tabPage1.SuspendLayout();
            this.groupBox34.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView3)).BeginInit();
            this.groupBox35.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox36.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView4)).BeginInit();
            this.tabPage3.SuspendLayout();
            this.groupBox37.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView5)).BeginInit();
            this.tabPage4.SuspendLayout();
            this.groupBox38.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView7)).BeginInit();
            this.tabPage5.SuspendLayout();
            this.tabPage6.SuspendLayout();
            this.groupBox40.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView8)).BeginInit();
            this.groupBox41.SuspendLayout();
            this.groupBox42.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView9)).BeginInit();
            this.groupBox43.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView10)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControlConfig
            // 
            this.tabControlConfig.Controls.Add(this.tabPageBasic);
            this.tabControlConfig.Controls.Add(this.tabPageDesc);
            this.tabControlConfig.Controls.Add(this.tabPageLimit);
            this.tabControlConfig.Controls.Add(this.tabPageProc);
            this.tabControlConfig.Controls.Add(this.tabPageAward);
            this.tabControlConfig.Enabled = false;
            this.tabControlConfig.Location = new System.Drawing.Point(3, 3);
            this.tabControlConfig.Name = "tabControlConfig";
            this.tabControlConfig.SelectedIndex = 0;
            this.tabControlConfig.Size = new System.Drawing.Size(1158, 553);
            this.tabControlConfig.TabIndex = 0;
            // 
            // tabPageBasic
            // 
            this.tabPageBasic.Controls.Add(this.groupBox63);
            this.tabPageBasic.Controls.Add(this.groupBox44);
            this.tabPageBasic.Controls.Add(this.groupBox6);
            this.tabPageBasic.Controls.Add(this.groupBox5);
            this.tabPageBasic.Controls.Add(this.groupBox4);
            this.tabPageBasic.Controls.Add(this.groupBox2);
            this.tabPageBasic.Controls.Add(this.groupBox1);
            this.tabPageBasic.Location = new System.Drawing.Point(4, 22);
            this.tabPageBasic.Name = "tabPageBasic";
            this.tabPageBasic.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageBasic.Size = new System.Drawing.Size(1150, 527);
            this.tabPageBasic.TabIndex = 0;
            this.tabPageBasic.Text = "基本信息";
            this.tabPageBasic.UseVisualStyleBackColor = true;
            // 
            // groupBox63
            // 
            this.groupBox63.Controls.Add(this.rbtGuideFind);
            this.groupBox63.Controls.Add(this.rbtGuildJump);
            this.groupBox63.Location = new System.Drawing.Point(747, 25);
            this.groupBox63.Name = "groupBox63";
            this.groupBox63.Size = new System.Drawing.Size(146, 74);
            this.groupBox63.TabIndex = 19;
            this.groupBox63.TabStop = false;
            this.groupBox63.Text = "新手任务引导类型";
            // 
            // rbtGuideFind
            // 
            this.rbtGuideFind.AutoSize = true;
            this.rbtGuideFind.Enabled = false;
            this.rbtGuideFind.Location = new System.Drawing.Point(7, 18);
            this.rbtGuideFind.Name = "rbtGuideFind";
            this.rbtGuideFind.Size = new System.Drawing.Size(71, 16);
            this.rbtGuideFind.TabIndex = 12;
            this.rbtGuideFind.TabStop = true;
            this.rbtGuideFind.Text = "寻路完成";
            this.rbtGuideFind.UseVisualStyleBackColor = true;
            // 
            // rbtGuildJump
            // 
            this.rbtGuildJump.AutoSize = true;
            this.rbtGuildJump.Enabled = false;
            this.rbtGuildJump.Location = new System.Drawing.Point(7, 39);
            this.rbtGuildJump.Name = "rbtGuildJump";
            this.rbtGuildJump.Size = new System.Drawing.Size(71, 16);
            this.rbtGuildJump.TabIndex = 5;
            this.rbtGuildJump.TabStop = true;
            this.rbtGuildJump.Text = "跳转完成";
            this.rbtGuildJump.UseVisualStyleBackColor = true;
            // 
            // groupBox44
            // 
            this.groupBox44.Controls.Add(this.comboBoxStarTask);
            this.groupBox44.Controls.Add(this.textBoxStarTaskGroupID);
            this.groupBox44.Controls.Add(this.buttonSelectStarTask);
            this.groupBox44.Controls.Add(this.label129);
            this.groupBox44.Controls.Add(this.label128);
            this.groupBox44.Controls.Add(this.label127);
            this.groupBox44.Location = new System.Drawing.Point(514, 21);
            this.groupBox44.Name = "groupBox44";
            this.groupBox44.Size = new System.Drawing.Size(227, 157);
            this.groupBox44.TabIndex = 6;
            this.groupBox44.TabStop = false;
            this.groupBox44.Text = "任务星级";
            // 
            // comboBoxStarTask
            // 
            this.comboBoxStarTask.FormattingEnabled = true;
            this.comboBoxStarTask.Items.AddRange(new object[] {
            "普通任务",
            "C级任务",
            "B级任务",
            "A级任务",
            "S级任务",
            "SS级任务"});
            this.comboBoxStarTask.Location = new System.Drawing.Point(77, 106);
            this.comboBoxStarTask.Name = "comboBoxStarTask";
            this.comboBoxStarTask.Size = new System.Drawing.Size(111, 20);
            this.comboBoxStarTask.TabIndex = 4;
            this.comboBoxStarTask.SelectedIndexChanged += new System.EventHandler(this.comboBoxStarTask_SelectedIndexChanged);
            // 
            // textBoxStarTaskGroupID
            // 
            this.textBoxStarTaskGroupID.Location = new System.Drawing.Point(77, 66);
            this.textBoxStarTaskGroupID.Name = "textBoxStarTaskGroupID";
            this.textBoxStarTaskGroupID.Size = new System.Drawing.Size(100, 21);
            this.textBoxStarTaskGroupID.TabIndex = 3;
            this.textBoxStarTaskGroupID.TextChanged += new System.EventHandler(this.textBoxStarTaskGroupID_TextChanged);
            // 
            // buttonSelectStarTask
            // 
            this.buttonSelectStarTask.Location = new System.Drawing.Point(86, 26);
            this.buttonSelectStarTask.Name = "buttonSelectStarTask";
            this.buttonSelectStarTask.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectStarTask.TabIndex = 2;
            this.buttonSelectStarTask.Text = "Select";
            this.buttonSelectStarTask.UseVisualStyleBackColor = true;
            this.buttonSelectStarTask.Click += new System.EventHandler(this.buttonSelectStarTask_Click);
            // 
            // label129
            // 
            this.label129.AutoSize = true;
            this.label129.Location = new System.Drawing.Point(22, 32);
            this.label129.Name = "label129";
            this.label129.Size = new System.Drawing.Size(41, 12);
            this.label129.TabIndex = 1;
            this.label129.Text = "星级组";
            // 
            // label128
            // 
            this.label128.AutoSize = true;
            this.label128.Location = new System.Drawing.Point(25, 72);
            this.label128.Name = "label128";
            this.label128.Size = new System.Drawing.Size(29, 12);
            this.label128.TabIndex = 1;
            this.label128.Text = "组ID";
            // 
            // label127
            // 
            this.label127.AutoSize = true;
            this.label127.Location = new System.Drawing.Point(14, 110);
            this.label127.Name = "label127";
            this.label127.Size = new System.Drawing.Size(53, 12);
            this.label127.TabIndex = 0;
            this.label127.Text = "任务星级";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.checkBox_build);
            this.groupBox6.Controls.Add(this.checkBox_behave);
            this.groupBox6.Controls.Add(this.checkBox_grow);
            this.groupBox6.Controls.Add(this.checkBoxGather);
            this.groupBox6.Controls.Add(this.checkBoxTalk);
            this.groupBox6.Controls.Add(this.checkBoxProbe);
            this.groupBox6.Controls.Add(this.checkBoxCollect);
            this.groupBox6.Controls.Add(this.checkBoxKill);
            this.groupBox6.Location = new System.Drawing.Point(747, 106);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(150, 197);
            this.groupBox6.TabIndex = 5;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "任务定义";
            // 
            // checkBox_build
            // 
            this.checkBox_build.AutoSize = true;
            this.checkBox_build.Location = new System.Drawing.Point(16, 151);
            this.checkBox_build.Name = "checkBox_build";
            this.checkBox_build.Size = new System.Drawing.Size(48, 16);
            this.checkBox_build.TabIndex = 8;
            this.checkBox_build.Text = "科技";
            this.checkBox_build.UseVisualStyleBackColor = true;
            this.checkBox_build.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBox_behave
            // 
            this.checkBox_behave.AutoSize = true;
            this.checkBox_behave.Location = new System.Drawing.Point(16, 129);
            this.checkBox_behave.Name = "checkBox_behave";
            this.checkBox_behave.Size = new System.Drawing.Size(48, 16);
            this.checkBox_behave.TabIndex = 7;
            this.checkBox_behave.Text = "行为";
            this.checkBox_behave.UseVisualStyleBackColor = true;
            this.checkBox_behave.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBox_grow
            // 
            this.checkBox_grow.AutoSize = true;
            this.checkBox_grow.Location = new System.Drawing.Point(16, 41);
            this.checkBox_grow.Name = "checkBox_grow";
            this.checkBox_grow.Size = new System.Drawing.Size(48, 16);
            this.checkBox_grow.TabIndex = 6;
            this.checkBox_grow.Text = "成长";
            this.checkBox_grow.UseVisualStyleBackColor = true;
            this.checkBox_grow.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBoxGather
            // 
            this.checkBoxGather.AutoSize = true;
            this.checkBoxGather.Location = new System.Drawing.Point(16, 85);
            this.checkBoxGather.Name = "checkBoxGather";
            this.checkBoxGather.Size = new System.Drawing.Size(48, 16);
            this.checkBoxGather.TabIndex = 5;
            this.checkBoxGather.Text = "采集";
            this.checkBoxGather.UseVisualStyleBackColor = true;
            this.checkBoxGather.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBoxTalk
            // 
            this.checkBoxTalk.AutoSize = true;
            this.checkBoxTalk.Location = new System.Drawing.Point(16, 173);
            this.checkBoxTalk.Name = "checkBoxTalk";
            this.checkBoxTalk.Size = new System.Drawing.Size(48, 16);
            this.checkBoxTalk.TabIndex = 4;
            this.checkBoxTalk.Text = "对话";
            this.checkBoxTalk.UseVisualStyleBackColor = true;
            this.checkBoxTalk.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBoxProbe
            // 
            this.checkBoxProbe.AutoSize = true;
            this.checkBoxProbe.Location = new System.Drawing.Point(16, 107);
            this.checkBoxProbe.Name = "checkBoxProbe";
            this.checkBoxProbe.Size = new System.Drawing.Size(48, 16);
            this.checkBoxProbe.TabIndex = 3;
            this.checkBoxProbe.Text = "探索";
            this.checkBoxProbe.UseVisualStyleBackColor = true;
            this.checkBoxProbe.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBoxCollect
            // 
            this.checkBoxCollect.AutoSize = true;
            this.checkBoxCollect.Location = new System.Drawing.Point(16, 63);
            this.checkBoxCollect.Name = "checkBoxCollect";
            this.checkBoxCollect.Size = new System.Drawing.Size(48, 16);
            this.checkBoxCollect.TabIndex = 1;
            this.checkBoxCollect.Text = "收集";
            this.checkBoxCollect.UseVisualStyleBackColor = true;
            this.checkBoxCollect.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // checkBoxKill
            // 
            this.checkBoxKill.AutoSize = true;
            this.checkBoxKill.Location = new System.Drawing.Point(16, 19);
            this.checkBoxKill.Name = "checkBoxKill";
            this.checkBoxKill.Size = new System.Drawing.Size(48, 16);
            this.checkBoxKill.TabIndex = 0;
            this.checkBoxKill.Text = "杀怪";
            this.checkBoxKill.UseVisualStyleBackColor = true;
            this.checkBoxKill.CheckedChanged += new System.EventHandler(this.checkBox_taskContent_CheckedChanged);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.buttonTaskSubmitDel);
            this.groupBox5.Controls.Add(this.dataGridViewTaskSubmit);
            this.groupBox5.Controls.Add(this.buttonTaskSubmitAdd);
            this.groupBox5.Controls.Add(this.label11);
            this.groupBox5.Controls.Add(this.textBoxTaskSubmitName);
            this.groupBox5.Controls.Add(this.textBoxTaskSubmitID);
            this.groupBox5.Controls.Add(this.label10);
            this.groupBox5.Controls.Add(this.buttonTaskSubmit);
            this.groupBox5.Controls.Add(this.comboBoxTaskSubmit);
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Enabled = false;
            this.groupBox5.Location = new System.Drawing.Point(354, 195);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(301, 306);
            this.groupBox5.TabIndex = 4;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "任务交付";
            // 
            // buttonTaskSubmitDel
            // 
            this.buttonTaskSubmitDel.Location = new System.Drawing.Point(160, 265);
            this.buttonTaskSubmitDel.Name = "buttonTaskSubmitDel";
            this.buttonTaskSubmitDel.Size = new System.Drawing.Size(75, 23);
            this.buttonTaskSubmitDel.TabIndex = 9;
            this.buttonTaskSubmitDel.Text = "删除";
            this.buttonTaskSubmitDel.UseVisualStyleBackColor = true;
            this.buttonTaskSubmitDel.Click += new System.EventHandler(this.buttonTaskSubmitDel_Click);
            // 
            // dataGridViewTaskSubmit
            // 
            this.dataGridViewTaskSubmit.AllowUserToAddRows = false;
            this.dataGridViewTaskSubmit.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewTaskSubmit.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTaskSubmit.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.SubmitTargetID,
            this.SubmitTargetType,
            this.SubmitTargetName});
            this.dataGridViewTaskSubmit.Location = new System.Drawing.Point(22, 144);
            this.dataGridViewTaskSubmit.Name = "dataGridViewTaskSubmit";
            this.dataGridViewTaskSubmit.RowHeadersVisible = false;
            this.dataGridViewTaskSubmit.RowTemplate.Height = 23;
            this.dataGridViewTaskSubmit.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewTaskSubmit.Size = new System.Drawing.Size(260, 114);
            this.dataGridViewTaskSubmit.TabIndex = 7;
            // 
            // SubmitTargetID
            // 
            this.SubmitTargetID.HeaderText = "目标ID";
            this.SubmitTargetID.Name = "SubmitTargetID";
            this.SubmitTargetID.Width = 66;
            // 
            // SubmitTargetType
            // 
            this.SubmitTargetType.HeaderText = "目标类型";
            this.SubmitTargetType.Name = "SubmitTargetType";
            this.SubmitTargetType.Width = 78;
            // 
            // SubmitTargetName
            // 
            this.SubmitTargetName.HeaderText = "目标名称";
            this.SubmitTargetName.Name = "SubmitTargetName";
            this.SubmitTargetName.Width = 78;
            // 
            // buttonTaskSubmitAdd
            // 
            this.buttonTaskSubmitAdd.Location = new System.Drawing.Point(45, 265);
            this.buttonTaskSubmitAdd.Name = "buttonTaskSubmitAdd";
            this.buttonTaskSubmitAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonTaskSubmitAdd.TabIndex = 9;
            this.buttonTaskSubmitAdd.Text = "添加";
            this.buttonTaskSubmitAdd.UseVisualStyleBackColor = true;
            this.buttonTaskSubmitAdd.Click += new System.EventHandler(this.buttonTaskSubmitAdd_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(21, 116);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(53, 12);
            this.label11.TabIndex = 6;
            this.label11.Text = "目标名称";
            // 
            // textBoxTaskSubmitName
            // 
            this.textBoxTaskSubmitName.Location = new System.Drawing.Point(89, 113);
            this.textBoxTaskSubmitName.Name = "textBoxTaskSubmitName";
            this.textBoxTaskSubmitName.Size = new System.Drawing.Size(121, 21);
            this.textBoxTaskSubmitName.TabIndex = 5;
            // 
            // textBoxTaskSubmitID
            // 
            this.textBoxTaskSubmitID.Location = new System.Drawing.Point(89, 80);
            this.textBoxTaskSubmitID.Name = "textBoxTaskSubmitID";
            this.textBoxTaskSubmitID.Size = new System.Drawing.Size(121, 21);
            this.textBoxTaskSubmitID.TabIndex = 4;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(21, 83);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 12);
            this.label10.TabIndex = 3;
            this.label10.Text = "目标ID";
            // 
            // buttonTaskSubmit
            // 
            this.buttonTaskSubmit.Location = new System.Drawing.Point(98, 48);
            this.buttonTaskSubmit.Name = "buttonTaskSubmit";
            this.buttonTaskSubmit.Size = new System.Drawing.Size(85, 23);
            this.buttonTaskSubmit.TabIndex = 2;
            this.buttonTaskSubmit.Text = "选择目标";
            this.buttonTaskSubmit.UseVisualStyleBackColor = true;
            this.buttonTaskSubmit.Click += new System.EventHandler(this.buttonTaskSubmit_Click);
            // 
            // comboBoxTaskSubmit
            // 
            this.comboBoxTaskSubmit.FormattingEnabled = true;
            this.comboBoxTaskSubmit.Items.AddRange(new object[] {
            "NPC交付",
            "场景对象交付",
            "使用道具交付"});
            this.comboBoxTaskSubmit.Location = new System.Drawing.Point(89, 20);
            this.comboBoxTaskSubmit.Name = "comboBoxTaskSubmit";
            this.comboBoxTaskSubmit.Size = new System.Drawing.Size(121, 20);
            this.comboBoxTaskSubmit.TabIndex = 1;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(21, 23);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "交付类型";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.buttonTaskStartDel);
            this.groupBox4.Controls.Add(this.buttonTaskStartAdd);
            this.groupBox4.Controls.Add(this.buttonTaskStart);
            this.groupBox4.Controls.Add(this.dataGridViewTaskStart);
            this.groupBox4.Controls.Add(this.textBoxTaskStartName);
            this.groupBox4.Controls.Add(this.textBoxTaskStartID);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.comboBoxTaskStart);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Location = new System.Drawing.Point(20, 195);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(290, 306);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "任务起始";
            // 
            // buttonTaskStartDel
            // 
            this.buttonTaskStartDel.Location = new System.Drawing.Point(145, 264);
            this.buttonTaskStartDel.Name = "buttonTaskStartDel";
            this.buttonTaskStartDel.Size = new System.Drawing.Size(75, 23);
            this.buttonTaskStartDel.TabIndex = 9;
            this.buttonTaskStartDel.Text = "删除";
            this.buttonTaskStartDel.UseVisualStyleBackColor = true;
            this.buttonTaskStartDel.Click += new System.EventHandler(this.buttonTaskStartDel_Click);
            // 
            // buttonTaskStartAdd
            // 
            this.buttonTaskStartAdd.Location = new System.Drawing.Point(30, 264);
            this.buttonTaskStartAdd.Name = "buttonTaskStartAdd";
            this.buttonTaskStartAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonTaskStartAdd.TabIndex = 9;
            this.buttonTaskStartAdd.Text = "添加";
            this.buttonTaskStartAdd.UseVisualStyleBackColor = true;
            this.buttonTaskStartAdd.Click += new System.EventHandler(this.buttonTaskStartAdd_Click);
            // 
            // buttonTaskStart
            // 
            this.buttonTaskStart.Location = new System.Drawing.Point(103, 46);
            this.buttonTaskStart.Name = "buttonTaskStart";
            this.buttonTaskStart.Size = new System.Drawing.Size(75, 23);
            this.buttonTaskStart.TabIndex = 8;
            this.buttonTaskStart.Text = "选择目标";
            this.buttonTaskStart.UseVisualStyleBackColor = true;
            this.buttonTaskStart.Click += new System.EventHandler(this.buttonTaskStart_Click);
            // 
            // dataGridViewTaskStart
            // 
            this.dataGridViewTaskStart.AllowUserToAddRows = false;
            this.dataGridViewTaskStart.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewTaskStart.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTaskStart.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.StartTargetID,
            this.StartTargetType,
            this.StartTargetName});
            this.dataGridViewTaskStart.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.dataGridViewTaskStart.Location = new System.Drawing.Point(15, 145);
            this.dataGridViewTaskStart.Name = "dataGridViewTaskStart";
            this.dataGridViewTaskStart.RowHeadersVisible = false;
            this.dataGridViewTaskStart.RowTemplate.Height = 23;
            this.dataGridViewTaskStart.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewTaskStart.Size = new System.Drawing.Size(257, 113);
            this.dataGridViewTaskStart.TabIndex = 7;
            // 
            // StartTargetID
            // 
            this.StartTargetID.HeaderText = "目标ID";
            this.StartTargetID.Name = "StartTargetID";
            this.StartTargetID.Width = 66;
            // 
            // StartTargetType
            // 
            this.StartTargetType.HeaderText = "目标类型";
            this.StartTargetType.Name = "StartTargetType";
            this.StartTargetType.Width = 78;
            // 
            // StartTargetName
            // 
            this.StartTargetName.HeaderText = "目标名称";
            this.StartTargetName.Name = "StartTargetName";
            this.StartTargetName.Width = 78;
            // 
            // textBoxTaskStartName
            // 
            this.textBoxTaskStartName.Location = new System.Drawing.Point(80, 114);
            this.textBoxTaskStartName.Name = "textBoxTaskStartName";
            this.textBoxTaskStartName.Size = new System.Drawing.Size(130, 21);
            this.textBoxTaskStartName.TabIndex = 6;
            // 
            // textBoxTaskStartID
            // 
            this.textBoxTaskStartID.Location = new System.Drawing.Point(80, 80);
            this.textBoxTaskStartID.Name = "textBoxTaskStartID";
            this.textBoxTaskStartID.Size = new System.Drawing.Size(130, 21);
            this.textBoxTaskStartID.TabIndex = 5;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(13, 116);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 4;
            this.label8.Text = "目标名称";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 84);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 3;
            this.label7.Text = "目标ID";
            // 
            // comboBoxTaskStart
            // 
            this.comboBoxTaskStart.FormattingEnabled = true;
            this.comboBoxTaskStart.Items.AddRange(new object[] {
            "NPC委托",
            "系统给予",
            "道具触发",
            "师门衙门接取"});
            this.comboBoxTaskStart.Location = new System.Drawing.Point(80, 20);
            this.comboBoxTaskStart.Name = "comboBoxTaskStart";
            this.comboBoxTaskStart.Size = new System.Drawing.Size(130, 20);
            this.comboBoxTaskStart.TabIndex = 2;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(13, 23);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 1;
            this.label6.Text = "起始类型";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.cbIsLevel);
            this.groupBox2.Controls.Add(this.checkBox_canGiveUp);
            this.groupBox2.Controls.Add(this.groupBox46);
            this.groupBox2.Controls.Add(this.checkBoxIsShared);
            this.groupBox2.Controls.Add(this.checkBoxIsOpen);
            this.groupBox2.Controls.Add(this.groupBox33);
            this.groupBox2.Location = new System.Drawing.Point(288, 19);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(220, 158);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "任务标记";
            // 
            // cbIsLevel
            // 
            this.cbIsLevel.AutoSize = true;
            this.cbIsLevel.Location = new System.Drawing.Point(95, 44);
            this.cbIsLevel.Name = "cbIsLevel";
            this.cbIsLevel.Size = new System.Drawing.Size(96, 16);
            this.cbIsLevel.TabIndex = 18;
            this.cbIsLevel.Text = "奖励等级相关";
            this.cbIsLevel.UseVisualStyleBackColor = true;
            this.cbIsLevel.CheckedChanged += new System.EventHandler(this.cbIsLevel_CheckedChanged);
            // 
            // checkBox_canGiveUp
            // 
            this.checkBox_canGiveUp.AutoSize = true;
            this.checkBox_canGiveUp.Location = new System.Drawing.Point(95, 19);
            this.checkBox_canGiveUp.Name = "checkBox_canGiveUp";
            this.checkBox_canGiveUp.Size = new System.Drawing.Size(72, 16);
            this.checkBox_canGiveUp.TabIndex = 5;
            this.checkBox_canGiveUp.Text = "可否放弃";
            this.checkBox_canGiveUp.UseVisualStyleBackColor = true;
            this.checkBox_canGiveUp.CheckedChanged += new System.EventHandler(this.checkBox_canGiveUp_CheckedChanged);
            // 
            // groupBox46
            // 
            this.groupBox46.Controls.Add(this.radioButton_repeat);
            this.groupBox46.Controls.Add(this.radioButton_noRepeat);
            this.groupBox46.Controls.Add(this.radioButton_dayRepeat);
            this.groupBox46.Controls.Add(this.label38);
            this.groupBox46.Controls.Add(this.textBoxRepeatCount);
            this.groupBox46.Location = new System.Drawing.Point(1, 62);
            this.groupBox46.Name = "groupBox46";
            this.groupBox46.Size = new System.Drawing.Size(139, 96);
            this.groupBox46.TabIndex = 17;
            this.groupBox46.TabStop = false;
            // 
            // radioButton_repeat
            // 
            this.radioButton_repeat.AutoSize = true;
            this.radioButton_repeat.Location = new System.Drawing.Point(6, 59);
            this.radioButton_repeat.Name = "radioButton_repeat";
            this.radioButton_repeat.Size = new System.Drawing.Size(71, 16);
            this.radioButton_repeat.TabIndex = 15;
            this.radioButton_repeat.TabStop = true;
            this.radioButton_repeat.Text = "无限重复";
            this.radioButton_repeat.UseVisualStyleBackColor = true;
            this.radioButton_repeat.CheckedChanged += new System.EventHandler(this.radioButton_repeat_CheckedChanged);
            // 
            // radioButton_noRepeat
            // 
            this.radioButton_noRepeat.AutoSize = true;
            this.radioButton_noRepeat.Location = new System.Drawing.Point(6, 17);
            this.radioButton_noRepeat.Name = "radioButton_noRepeat";
            this.radioButton_noRepeat.Size = new System.Drawing.Size(71, 16);
            this.radioButton_noRepeat.TabIndex = 13;
            this.radioButton_noRepeat.TabStop = true;
            this.radioButton_noRepeat.Text = "不可重复";
            this.radioButton_noRepeat.UseVisualStyleBackColor = true;
            this.radioButton_noRepeat.CheckedChanged += new System.EventHandler(this.radioButton_noRepeat_CheckedChanged);
            // 
            // radioButton_dayRepeat
            // 
            this.radioButton_dayRepeat.AutoSize = true;
            this.radioButton_dayRepeat.Location = new System.Drawing.Point(6, 38);
            this.radioButton_dayRepeat.Name = "radioButton_dayRepeat";
            this.radioButton_dayRepeat.Size = new System.Drawing.Size(71, 16);
            this.radioButton_dayRepeat.TabIndex = 14;
            this.radioButton_dayRepeat.TabStop = true;
            this.radioButton_dayRepeat.Text = "每日重复";
            this.radioButton_dayRepeat.UseVisualStyleBackColor = true;
            this.radioButton_dayRepeat.CheckedChanged += new System.EventHandler(this.radioButton_dayRepeat_CheckedChanged);
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Location = new System.Drawing.Point(121, 40);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(17, 12);
            this.label38.TabIndex = 10;
            this.label38.Text = "次";
            // 
            // textBoxRepeatCount
            // 
            this.textBoxRepeatCount.Location = new System.Drawing.Point(84, 36);
            this.textBoxRepeatCount.Name = "textBoxRepeatCount";
            this.textBoxRepeatCount.Size = new System.Drawing.Size(27, 21);
            this.textBoxRepeatCount.TabIndex = 11;
            this.textBoxRepeatCount.Text = "1";
            this.textBoxRepeatCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxRepeatCount.TextChanged += new System.EventHandler(this.textBoxRepeatCount_TextChanged);
            // 
            // checkBoxIsShared
            // 
            this.checkBoxIsShared.AutoSize = true;
            this.checkBoxIsShared.Location = new System.Drawing.Point(6, 44);
            this.checkBoxIsShared.Name = "checkBoxIsShared";
            this.checkBoxIsShared.Size = new System.Drawing.Size(72, 16);
            this.checkBoxIsShared.TabIndex = 1;
            this.checkBoxIsShared.Text = "可否共享";
            this.checkBoxIsShared.UseVisualStyleBackColor = true;
            this.checkBoxIsShared.CheckedChanged += new System.EventHandler(this.checkBoxIsShared_CheckedChanged);
            // 
            // checkBoxIsOpen
            // 
            this.checkBoxIsOpen.AutoSize = true;
            this.checkBoxIsOpen.Location = new System.Drawing.Point(6, 19);
            this.checkBoxIsOpen.Name = "checkBoxIsOpen";
            this.checkBoxIsOpen.Size = new System.Drawing.Size(72, 16);
            this.checkBoxIsOpen.TabIndex = 0;
            this.checkBoxIsOpen.Text = "是否开放";
            this.checkBoxIsOpen.UseVisualStyleBackColor = true;
            this.checkBoxIsOpen.CheckedChanged += new System.EventHandler(this.checkBoxIsOpen_CheckedChanged);
            // 
            // groupBox33
            // 
            this.groupBox33.Controls.Add(this.radioButton_NomalTask);
            this.groupBox33.Controls.Add(this.radioButton_rewardTask);
            this.groupBox33.Location = new System.Drawing.Point(142, 61);
            this.groupBox33.Name = "groupBox33";
            this.groupBox33.Size = new System.Drawing.Size(78, 96);
            this.groupBox33.TabIndex = 16;
            this.groupBox33.TabStop = false;
            // 
            // radioButton_NomalTask
            // 
            this.radioButton_NomalTask.AutoSize = true;
            this.radioButton_NomalTask.Location = new System.Drawing.Point(7, 18);
            this.radioButton_NomalTask.Name = "radioButton_NomalTask";
            this.radioButton_NomalTask.Size = new System.Drawing.Size(71, 16);
            this.radioButton_NomalTask.TabIndex = 12;
            this.radioButton_NomalTask.TabStop = true;
            this.radioButton_NomalTask.Text = "一般任务";
            this.radioButton_NomalTask.UseVisualStyleBackColor = true;
            this.radioButton_NomalTask.CheckedChanged += new System.EventHandler(this.radioButton_NomalTask_CheckedChanged);
            // 
            // radioButton_rewardTask
            // 
            this.radioButton_rewardTask.AutoSize = true;
            this.radioButton_rewardTask.Location = new System.Drawing.Point(7, 39);
            this.radioButton_rewardTask.Name = "radioButton_rewardTask";
            this.radioButton_rewardTask.Size = new System.Drawing.Size(71, 16);
            this.radioButton_rewardTask.TabIndex = 5;
            this.radioButton_rewardTask.TabStop = true;
            this.radioButton_rewardTask.Text = "悬赏任务";
            this.radioButton_rewardTask.UseVisualStyleBackColor = true;
            this.radioButton_rewardTask.CheckedChanged += new System.EventHandler(this.radioButton_rewardTask_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxTaskType);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textBoxTaskLevel);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textBoxTaskName);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.textBoxTaskID);
            this.groupBox1.Location = new System.Drawing.Point(20, 19);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(237, 158);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "基本设定";
            // 
            // comboBoxTaskType
            // 
            this.comboBoxTaskType.FormattingEnabled = true;
            this.comboBoxTaskType.Items.AddRange(new object[] {
            "主线任务",
            "支线任务",
            "日常任务",
            "vip任务",
            "新手引导任务",
            "师门任务",
            "师门晋级任务",
            "衙门任务",
            "衙门晋级任务"});
            this.comboBoxTaskType.Location = new System.Drawing.Point(85, 122);
            this.comboBoxTaskType.Name = "comboBoxTaskType";
            this.comboBoxTaskType.Size = new System.Drawing.Size(130, 20);
            this.comboBoxTaskType.TabIndex = 7;
            this.comboBoxTaskType.SelectedIndexChanged += new System.EventHandler(this.comboBoxTaskType_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 125);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "任务类型";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 90);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "任务等级";
            // 
            // textBoxTaskLevel
            // 
            this.textBoxTaskLevel.Location = new System.Drawing.Point(85, 87);
            this.textBoxTaskLevel.Name = "textBoxTaskLevel";
            this.textBoxTaskLevel.Size = new System.Drawing.Size(130, 21);
            this.textBoxTaskLevel.TabIndex = 4;
            this.textBoxTaskLevel.TextChanged += new System.EventHandler(this.textBoxTaskLevel_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 54);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "任务名称";
            // 
            // textBoxTaskName
            // 
            this.textBoxTaskName.Location = new System.Drawing.Point(85, 51);
            this.textBoxTaskName.Name = "textBoxTaskName";
            this.textBoxTaskName.Size = new System.Drawing.Size(130, 21);
            this.textBoxTaskName.TabIndex = 2;
            this.textBoxTaskName.TextChanged += new System.EventHandler(this.textBoxTaskName_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "任务ID";
            // 
            // textBoxTaskID
            // 
            this.textBoxTaskID.Location = new System.Drawing.Point(85, 20);
            this.textBoxTaskID.Name = "textBoxTaskID";
            this.textBoxTaskID.Size = new System.Drawing.Size(130, 21);
            this.textBoxTaskID.TabIndex = 0;
            this.textBoxTaskID.TextChanged += new System.EventHandler(this.textBoxTaskID_TextChanged);
            // 
            // tabPageDesc
            // 
            this.tabPageDesc.Controls.Add(this.buttonColorMode);
            this.tabPageDesc.Controls.Add(this.buttonEditMode);
            this.tabPageDesc.Controls.Add(this.buttonChooseColor);
            this.tabPageDesc.Controls.Add(this.buttonInsertGather);
            this.tabPageDesc.Controls.Add(this.buttonInsertNpcID);
            this.tabPageDesc.Controls.Add(this.buttonInsertMonsterID);
            this.tabPageDesc.Controls.Add(this.buttonInsertClan);
            this.tabPageDesc.Controls.Add(this.buttonInsertName);
            this.tabPageDesc.Controls.Add(this.groupBox11);
            this.tabPageDesc.Controls.Add(this.groupBox10);
            this.tabPageDesc.Controls.Add(this.groupBox9);
            this.tabPageDesc.Controls.Add(this.groupBox8);
            this.tabPageDesc.Controls.Add(this.groupBox7);
            this.tabPageDesc.Location = new System.Drawing.Point(4, 22);
            this.tabPageDesc.Name = "tabPageDesc";
            this.tabPageDesc.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageDesc.Size = new System.Drawing.Size(1150, 527);
            this.tabPageDesc.TabIndex = 1;
            this.tabPageDesc.Text = "任务描述";
            this.tabPageDesc.UseVisualStyleBackColor = true;
            // 
            // buttonColorMode
            // 
            this.buttonColorMode.Location = new System.Drawing.Point(802, 57);
            this.buttonColorMode.Name = "buttonColorMode";
            this.buttonColorMode.Size = new System.Drawing.Size(75, 23);
            this.buttonColorMode.TabIndex = 12;
            this.buttonColorMode.Text = "颜色模式";
            this.buttonColorMode.UseVisualStyleBackColor = true;
            this.buttonColorMode.Click += new System.EventHandler(this.buttonColorMode_Click);
            // 
            // buttonEditMode
            // 
            this.buttonEditMode.BackColor = System.Drawing.Color.Transparent;
            this.buttonEditMode.ForeColor = System.Drawing.SystemColors.ControlText;
            this.buttonEditMode.Location = new System.Drawing.Point(802, 20);
            this.buttonEditMode.Name = "buttonEditMode";
            this.buttonEditMode.Size = new System.Drawing.Size(75, 23);
            this.buttonEditMode.TabIndex = 12;
            this.buttonEditMode.Text = "编辑模式";
            this.buttonEditMode.UseVisualStyleBackColor = false;
            this.buttonEditMode.Click += new System.EventHandler(this.buttonEditMode_Click);
            // 
            // buttonChooseColor
            // 
            this.buttonChooseColor.Enabled = false;
            this.buttonChooseColor.Location = new System.Drawing.Point(913, 20);
            this.buttonChooseColor.Name = "buttonChooseColor";
            this.buttonChooseColor.Size = new System.Drawing.Size(105, 22);
            this.buttonChooseColor.TabIndex = 11;
            this.buttonChooseColor.Text = "选择字体颜色";
            this.buttonChooseColor.UseVisualStyleBackColor = true;
            this.buttonChooseColor.Click += new System.EventHandler(this.buttonChooseColor_Click);
            // 
            // buttonInsertGather
            // 
            this.buttonInsertGather.Location = new System.Drawing.Point(913, 200);
            this.buttonInsertGather.Name = "buttonInsertGather";
            this.buttonInsertGather.Size = new System.Drawing.Size(105, 22);
            this.buttonInsertGather.TabIndex = 8;
            this.buttonInsertGather.Text = "插入采集ID";
            this.buttonInsertGather.UseVisualStyleBackColor = true;
            this.buttonInsertGather.Click += new System.EventHandler(this.buttonInsertGather_Click);
            // 
            // buttonInsertNpcID
            // 
            this.buttonInsertNpcID.Location = new System.Drawing.Point(913, 164);
            this.buttonInsertNpcID.Name = "buttonInsertNpcID";
            this.buttonInsertNpcID.Size = new System.Drawing.Size(105, 22);
            this.buttonInsertNpcID.TabIndex = 8;
            this.buttonInsertNpcID.Text = "插入NPC ID";
            this.buttonInsertNpcID.UseVisualStyleBackColor = true;
            this.buttonInsertNpcID.Click += new System.EventHandler(this.buttonInsertNpcID_Click);
            // 
            // buttonInsertMonsterID
            // 
            this.buttonInsertMonsterID.Location = new System.Drawing.Point(913, 128);
            this.buttonInsertMonsterID.Name = "buttonInsertMonsterID";
            this.buttonInsertMonsterID.Size = new System.Drawing.Size(105, 22);
            this.buttonInsertMonsterID.TabIndex = 7;
            this.buttonInsertMonsterID.Text = "插入怪物ID";
            this.buttonInsertMonsterID.UseVisualStyleBackColor = true;
            this.buttonInsertMonsterID.Click += new System.EventHandler(this.buttonInsertMonsterID_Click);
            // 
            // buttonInsertClan
            // 
            this.buttonInsertClan.Location = new System.Drawing.Point(913, 92);
            this.buttonInsertClan.Name = "buttonInsertClan";
            this.buttonInsertClan.Size = new System.Drawing.Size(105, 22);
            this.buttonInsertClan.TabIndex = 6;
            this.buttonInsertClan.Text = "插入玩家阵营";
            this.buttonInsertClan.UseVisualStyleBackColor = true;
            this.buttonInsertClan.Click += new System.EventHandler(this.buttonInsertClan_Click);
            // 
            // buttonInsertName
            // 
            this.buttonInsertName.Location = new System.Drawing.Point(913, 56);
            this.buttonInsertName.Name = "buttonInsertName";
            this.buttonInsertName.Size = new System.Drawing.Size(105, 22);
            this.buttonInsertName.TabIndex = 5;
            this.buttonInsertName.Text = "插入玩家姓名";
            this.buttonInsertName.UseVisualStyleBackColor = true;
            this.buttonInsertName.Click += new System.EventHandler(this.buttonInsertName_Click);
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.richTextBoxAward);
            this.groupBox11.Location = new System.Drawing.Point(786, 239);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(341, 230);
            this.groupBox11.TabIndex = 4;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "奖励信息预览";
            // 
            // richTextBoxAward
            // 
            this.richTextBoxAward.BackColor = System.Drawing.SystemColors.Window;
            this.richTextBoxAward.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBoxAward.Location = new System.Drawing.Point(16, 21);
            this.richTextBoxAward.Name = "richTextBoxAward";
            this.richTextBoxAward.ReadOnly = true;
            this.richTextBoxAward.Size = new System.Drawing.Size(310, 185);
            this.richTextBoxAward.TabIndex = 0;
            this.richTextBoxAward.Text = "";
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.textBoxTaskFinish);
            this.groupBox10.Location = new System.Drawing.Point(402, 239);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(363, 230);
            this.groupBox10.TabIndex = 3;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "完成对话";
            // 
            // textBoxTaskFinish
            // 
            this.textBoxTaskFinish.Location = new System.Drawing.Point(15, 21);
            this.textBoxTaskFinish.Name = "textBoxTaskFinish";
            this.textBoxTaskFinish.Size = new System.Drawing.Size(330, 185);
            this.textBoxTaskFinish.TabIndex = 0;
            this.textBoxTaskFinish.Text = "";
            this.textBoxTaskFinish.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxTaskFinish_MouseClick);
            this.textBoxTaskFinish.TextChanged += new System.EventHandler(this.textBoxTaskFinish_TextChanged);
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.textBoxTaskFail);
            this.groupBox9.Location = new System.Drawing.Point(18, 239);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(363, 230);
            this.groupBox9.TabIndex = 2;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "未完成对话";
            // 
            // textBoxTaskFail
            // 
            this.textBoxTaskFail.Location = new System.Drawing.Point(14, 21);
            this.textBoxTaskFail.Name = "textBoxTaskFail";
            this.textBoxTaskFail.Size = new System.Drawing.Size(331, 188);
            this.textBoxTaskFail.TabIndex = 0;
            this.textBoxTaskFail.Text = "";
            this.textBoxTaskFail.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxTaskFail_MouseClick);
            this.textBoxTaskFail.TextChanged += new System.EventHandler(this.textBoxTaskFail_TextChanged);
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.textBoxTaskPurpose);
            this.groupBox8.Location = new System.Drawing.Point(402, 14);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(363, 208);
            this.groupBox8.TabIndex = 1;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "任务目的";
            // 
            // textBoxTaskPurpose
            // 
            this.textBoxTaskPurpose.Location = new System.Drawing.Point(15, 22);
            this.textBoxTaskPurpose.Name = "textBoxTaskPurpose";
            this.textBoxTaskPurpose.Size = new System.Drawing.Size(330, 165);
            this.textBoxTaskPurpose.TabIndex = 0;
            this.textBoxTaskPurpose.Text = "";
            this.textBoxTaskPurpose.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxTaskPurpose_MouseClick);
            this.textBoxTaskPurpose.TextChanged += new System.EventHandler(this.textBoxTaskPurpose_TextChanged);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.textBoxTaskDesc);
            this.groupBox7.Location = new System.Drawing.Point(18, 14);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(363, 208);
            this.groupBox7.TabIndex = 0;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "任务描述";
            // 
            // textBoxTaskDesc
            // 
            this.textBoxTaskDesc.Location = new System.Drawing.Point(14, 22);
            this.textBoxTaskDesc.Name = "textBoxTaskDesc";
            this.textBoxTaskDesc.Size = new System.Drawing.Size(331, 165);
            this.textBoxTaskDesc.TabIndex = 0;
            this.textBoxTaskDesc.Text = "";
            this.textBoxTaskDesc.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxTaskDesc_MouseClick);
            this.textBoxTaskDesc.TextChanged += new System.EventHandler(this.textBoxTaskDesc_TextChanged);
            // 
            // tabPageLimit
            // 
            this.tabPageLimit.Controls.Add(this.groupBox59);
            this.tabPageLimit.Controls.Add(this.groupBox56);
            this.tabPageLimit.Controls.Add(this.groupBox31);
            this.tabPageLimit.Controls.Add(this.groupBox30);
            this.tabPageLimit.Controls.Add(this.groupBox29);
            this.tabPageLimit.Controls.Add(this.groupBox28);
            this.tabPageLimit.Controls.Add(this.groupBox27);
            this.tabPageLimit.Controls.Add(this.groupBox26);
            this.tabPageLimit.Controls.Add(this.groupBox25);
            this.tabPageLimit.Controls.Add(this.groupBox23);
            this.tabPageLimit.Location = new System.Drawing.Point(4, 22);
            this.tabPageLimit.Name = "tabPageLimit";
            this.tabPageLimit.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageLimit.Size = new System.Drawing.Size(1150, 527);
            this.tabPageLimit.TabIndex = 2;
            this.tabPageLimit.Text = "任务限制";
            this.tabPageLimit.UseVisualStyleBackColor = true;
            // 
            // groupBox59
            // 
            this.groupBox59.Controls.Add(this.textBoxReputeMax);
            this.groupBox59.Controls.Add(this.label55);
            this.groupBox59.Controls.Add(this.textBoxReputeMin);
            this.groupBox59.Controls.Add(this.label56);
            this.groupBox59.Enabled = false;
            this.groupBox59.Location = new System.Drawing.Point(31, 93);
            this.groupBox59.Name = "groupBox59";
            this.groupBox59.Size = new System.Drawing.Size(209, 57);
            this.groupBox59.TabIndex = 4;
            this.groupBox59.TabStop = false;
            this.groupBox59.Text = "声望限制";
            // 
            // textBoxReputeMax
            // 
            this.textBoxReputeMax.Location = new System.Drawing.Point(144, 21);
            this.textBoxReputeMax.Name = "textBoxReputeMax";
            this.textBoxReputeMax.Size = new System.Drawing.Size(47, 21);
            this.textBoxReputeMax.TabIndex = 3;
            this.textBoxReputeMax.TextChanged += new System.EventHandler(this.textBoxReputeMax_TextChanged);
            // 
            // label55
            // 
            this.label55.AutoSize = true;
            this.label55.Location = new System.Drawing.Point(5, 24);
            this.label55.Name = "label55";
            this.label55.Size = new System.Drawing.Size(53, 12);
            this.label55.TabIndex = 2;
            this.label55.Text = "声望限制";
            // 
            // textBoxReputeMin
            // 
            this.textBoxReputeMin.Location = new System.Drawing.Point(74, 21);
            this.textBoxReputeMin.Name = "textBoxReputeMin";
            this.textBoxReputeMin.Size = new System.Drawing.Size(47, 21);
            this.textBoxReputeMin.TabIndex = 3;
            this.textBoxReputeMin.TextChanged += new System.EventHandler(this.textBoxReputeMin_TextChanged);
            // 
            // label56
            // 
            this.label56.AutoSize = true;
            this.label56.Location = new System.Drawing.Point(127, 29);
            this.label56.Name = "label56";
            this.label56.Size = new System.Drawing.Size(11, 12);
            this.label56.TabIndex = 2;
            this.label56.Text = "~";
            // 
            // groupBox56
            // 
            this.groupBox56.Controls.Add(this.button_limit_propRemove);
            this.groupBox56.Controls.Add(this.groupBox57);
            this.groupBox56.Controls.Add(this.button_limit_propAdd);
            this.groupBox56.Controls.Add(this.groupBox58);
            this.groupBox56.Controls.Add(this.dataGridView_limit_prop);
            this.groupBox56.Location = new System.Drawing.Point(796, 22);
            this.groupBox56.Name = "groupBox56";
            this.groupBox56.Size = new System.Drawing.Size(263, 473);
            this.groupBox56.TabIndex = 15;
            this.groupBox56.TabStop = false;
            this.groupBox56.Text = "属性限制";
            // 
            // button_limit_propRemove
            // 
            this.button_limit_propRemove.Location = new System.Drawing.Point(137, 436);
            this.button_limit_propRemove.Name = "button_limit_propRemove";
            this.button_limit_propRemove.Size = new System.Drawing.Size(75, 23);
            this.button_limit_propRemove.TabIndex = 13;
            this.button_limit_propRemove.Text = "删除";
            this.button_limit_propRemove.UseVisualStyleBackColor = true;
            this.button_limit_propRemove.Click += new System.EventHandler(this.button_limit_propRemove_Click);
            // 
            // groupBox57
            // 
            this.groupBox57.Controls.Add(this.textBox_limit_roleProp);
            this.groupBox57.Controls.Add(this.comboBox_limit_roleProp);
            this.groupBox57.Controls.Add(this.label124);
            this.groupBox57.Controls.Add(this.label125);
            this.groupBox57.Location = new System.Drawing.Point(28, 33);
            this.groupBox57.Name = "groupBox57";
            this.groupBox57.Size = new System.Drawing.Size(200, 85);
            this.groupBox57.TabIndex = 9;
            this.groupBox57.TabStop = false;
            this.groupBox57.Text = "选择属性";
            // 
            // textBox_limit_roleProp
            // 
            this.textBox_limit_roleProp.Location = new System.Drawing.Point(73, 51);
            this.textBox_limit_roleProp.Name = "textBox_limit_roleProp";
            this.textBox_limit_roleProp.Size = new System.Drawing.Size(121, 21);
            this.textBox_limit_roleProp.TabIndex = 3;
            // 
            // comboBox_limit_roleProp
            // 
            this.comboBox_limit_roleProp.FormattingEnabled = true;
            this.comboBox_limit_roleProp.Location = new System.Drawing.Point(73, 22);
            this.comboBox_limit_roleProp.Name = "comboBox_limit_roleProp";
            this.comboBox_limit_roleProp.Size = new System.Drawing.Size(121, 20);
            this.comboBox_limit_roleProp.TabIndex = 2;
            // 
            // label124
            // 
            this.label124.AutoSize = true;
            this.label124.Location = new System.Drawing.Point(37, 56);
            this.label124.Name = "label124";
            this.label124.Size = new System.Drawing.Size(35, 12);
            this.label124.TabIndex = 1;
            this.label124.Text = "数值:";
            // 
            // label125
            // 
            this.label125.AutoSize = true;
            this.label125.Location = new System.Drawing.Point(13, 27);
            this.label125.Name = "label125";
            this.label125.Size = new System.Drawing.Size(59, 12);
            this.label125.TabIndex = 0;
            this.label125.Text = "角色属性:";
            // 
            // button_limit_propAdd
            // 
            this.button_limit_propAdd.Location = new System.Drawing.Point(43, 436);
            this.button_limit_propAdd.Name = "button_limit_propAdd";
            this.button_limit_propAdd.Size = new System.Drawing.Size(75, 23);
            this.button_limit_propAdd.TabIndex = 12;
            this.button_limit_propAdd.Text = "添加";
            this.button_limit_propAdd.UseVisualStyleBackColor = true;
            this.button_limit_propAdd.Click += new System.EventHandler(this.button_limit_propAdd_Click);
            // 
            // groupBox58
            // 
            this.groupBox58.Controls.Add(this.textBox_limit_campName);
            this.groupBox58.Controls.Add(this.textBox_limit_campID);
            this.groupBox58.Controls.Add(this.label126);
            this.groupBox58.Controls.Add(this.button_limit_selectCamp);
            this.groupBox58.Controls.Add(this.label135);
            this.groupBox58.Location = new System.Drawing.Point(28, 134);
            this.groupBox58.Name = "groupBox58";
            this.groupBox58.Size = new System.Drawing.Size(200, 116);
            this.groupBox58.TabIndex = 10;
            this.groupBox58.TabStop = false;
            this.groupBox58.Text = "阵营";
            // 
            // textBox_limit_campName
            // 
            this.textBox_limit_campName.Location = new System.Drawing.Point(73, 80);
            this.textBox_limit_campName.Name = "textBox_limit_campName";
            this.textBox_limit_campName.Size = new System.Drawing.Size(121, 21);
            this.textBox_limit_campName.TabIndex = 6;
            // 
            // textBox_limit_campID
            // 
            this.textBox_limit_campID.Location = new System.Drawing.Point(73, 53);
            this.textBox_limit_campID.Name = "textBox_limit_campID";
            this.textBox_limit_campID.Size = new System.Drawing.Size(121, 21);
            this.textBox_limit_campID.TabIndex = 4;
            // 
            // label126
            // 
            this.label126.AutoSize = true;
            this.label126.Location = new System.Drawing.Point(13, 85);
            this.label126.Name = "label126";
            this.label126.Size = new System.Drawing.Size(59, 12);
            this.label126.TabIndex = 5;
            this.label126.Text = "阵营名称:";
            // 
            // button_limit_selectCamp
            // 
            this.button_limit_selectCamp.Location = new System.Drawing.Point(61, 20);
            this.button_limit_selectCamp.Name = "button_limit_selectCamp";
            this.button_limit_selectCamp.Size = new System.Drawing.Size(75, 23);
            this.button_limit_selectCamp.TabIndex = 0;
            this.button_limit_selectCamp.Text = "选择阵营";
            this.button_limit_selectCamp.UseVisualStyleBackColor = true;
            this.button_limit_selectCamp.Click += new System.EventHandler(this.button_limit_selectCamp_Click);
            // 
            // label135
            // 
            this.label135.AutoSize = true;
            this.label135.Location = new System.Drawing.Point(13, 56);
            this.label135.Name = "label135";
            this.label135.Size = new System.Drawing.Size(47, 12);
            this.label135.TabIndex = 4;
            this.label135.Text = "阵营ID:";
            // 
            // dataGridView_limit_prop
            // 
            this.dataGridView_limit_prop.AllowUserToAddRows = false;
            this.dataGridView_limit_prop.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_limit_prop.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn32,
            this.dataGridViewTextBoxColumn33});
            this.dataGridView_limit_prop.Location = new System.Drawing.Point(28, 265);
            this.dataGridView_limit_prop.Name = "dataGridView_limit_prop";
            this.dataGridView_limit_prop.RowHeadersVisible = false;
            this.dataGridView_limit_prop.RowTemplate.Height = 23;
            this.dataGridView_limit_prop.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_limit_prop.Size = new System.Drawing.Size(200, 163);
            this.dataGridView_limit_prop.TabIndex = 11;
            this.dataGridView_limit_prop.SelectionChanged += new System.EventHandler(this.dataGridView_limit_prop_SelectionChanged);
            // 
            // dataGridViewTextBoxColumn32
            // 
            this.dataGridViewTextBoxColumn32.HeaderText = "角色属性";
            this.dataGridViewTextBoxColumn32.Name = "dataGridViewTextBoxColumn32";
            this.dataGridViewTextBoxColumn32.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn33
            // 
            this.dataGridViewTextBoxColumn33.HeaderText = "数值需求";
            this.dataGridViewTextBoxColumn33.Name = "dataGridViewTextBoxColumn33";
            this.dataGridViewTextBoxColumn33.ReadOnly = true;
            // 
            // groupBox31
            // 
            this.groupBox31.Controls.Add(this.button_preTaskRemove);
            this.groupBox31.Controls.Add(this.groupBox55);
            this.groupBox31.Controls.Add(this.dataGridViewPreTask);
            this.groupBox31.Controls.Add(this.button_preTaskAdd);
            this.groupBox31.Controls.Add(this.textBoxPreTaskName);
            this.groupBox31.Controls.Add(this.textBoxPreTaskID);
            this.groupBox31.Controls.Add(this.label66);
            this.groupBox31.Controls.Add(this.label65);
            this.groupBox31.Controls.Add(this.buttonSelectPreTask);
            this.groupBox31.Controls.Add(this.label64);
            this.groupBox31.Location = new System.Drawing.Point(267, 199);
            this.groupBox31.Name = "groupBox31";
            this.groupBox31.Size = new System.Drawing.Size(291, 296);
            this.groupBox31.TabIndex = 7;
            this.groupBox31.TabStop = false;
            this.groupBox31.Text = "前置任务";
            // 
            // button_preTaskRemove
            // 
            this.button_preTaskRemove.Location = new System.Drawing.Point(162, 259);
            this.button_preTaskRemove.Name = "button_preTaskRemove";
            this.button_preTaskRemove.Size = new System.Drawing.Size(75, 23);
            this.button_preTaskRemove.TabIndex = 11;
            this.button_preTaskRemove.Text = "删除";
            this.button_preTaskRemove.UseVisualStyleBackColor = true;
            this.button_preTaskRemove.Click += new System.EventHandler(this.button_preTaskRemove_Click);
            // 
            // groupBox55
            // 
            this.groupBox55.Controls.Add(this.radioButton_preTaskOne);
            this.groupBox55.Controls.Add(this.radioButton_preTaskAll);
            this.groupBox55.Location = new System.Drawing.Point(208, 0);
            this.groupBox55.Name = "groupBox55";
            this.groupBox55.Size = new System.Drawing.Size(83, 59);
            this.groupBox55.TabIndex = 4;
            this.groupBox55.TabStop = false;
            // 
            // radioButton_preTaskOne
            // 
            this.radioButton_preTaskOne.AutoSize = true;
            this.radioButton_preTaskOne.Location = new System.Drawing.Point(6, 34);
            this.radioButton_preTaskOne.Name = "radioButton_preTaskOne";
            this.radioButton_preTaskOne.Size = new System.Drawing.Size(71, 16);
            this.radioButton_preTaskOne.TabIndex = 1;
            this.radioButton_preTaskOne.TabStop = true;
            this.radioButton_preTaskOne.Text = "完成其一";
            this.radioButton_preTaskOne.UseVisualStyleBackColor = true;
            this.radioButton_preTaskOne.CheckedChanged += new System.EventHandler(this.radioButton_preTaskOne_CheckedChanged);
            // 
            // radioButton_preTaskAll
            // 
            this.radioButton_preTaskAll.AutoSize = true;
            this.radioButton_preTaskAll.Location = new System.Drawing.Point(6, 14);
            this.radioButton_preTaskAll.Name = "radioButton_preTaskAll";
            this.radioButton_preTaskAll.Size = new System.Drawing.Size(71, 16);
            this.radioButton_preTaskAll.TabIndex = 0;
            this.radioButton_preTaskAll.TabStop = true;
            this.radioButton_preTaskAll.Text = "全部完成";
            this.radioButton_preTaskAll.UseVisualStyleBackColor = true;
            this.radioButton_preTaskAll.CheckedChanged += new System.EventHandler(this.radioButton_preTaskAll_CheckedChanged);
            // 
            // dataGridViewPreTask
            // 
            this.dataGridViewPreTask.AllowUserToAddRows = false;
            this.dataGridViewPreTask.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewPreTask.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewPreTask.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumnTaskID,
            this.dataGridViewTextBoxColumnTaskName});
            this.dataGridViewPreTask.Location = new System.Drawing.Point(35, 127);
            this.dataGridViewPreTask.MultiSelect = false;
            this.dataGridViewPreTask.Name = "dataGridViewPreTask";
            this.dataGridViewPreTask.RowHeadersVisible = false;
            this.dataGridViewPreTask.RowTemplate.Height = 23;
            this.dataGridViewPreTask.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewPreTask.Size = new System.Drawing.Size(247, 124);
            this.dataGridViewPreTask.TabIndex = 2;
            // 
            // dataGridViewTextBoxColumnTaskID
            // 
            this.dataGridViewTextBoxColumnTaskID.HeaderText = "任务ID";
            this.dataGridViewTextBoxColumnTaskID.Name = "dataGridViewTextBoxColumnTaskID";
            this.dataGridViewTextBoxColumnTaskID.Width = 66;
            // 
            // dataGridViewTextBoxColumnTaskName
            // 
            this.dataGridViewTextBoxColumnTaskName.HeaderText = "任务名称";
            this.dataGridViewTextBoxColumnTaskName.Name = "dataGridViewTextBoxColumnTaskName";
            this.dataGridViewTextBoxColumnTaskName.Width = 78;
            // 
            // button_preTaskAdd
            // 
            this.button_preTaskAdd.Location = new System.Drawing.Point(62, 259);
            this.button_preTaskAdd.Name = "button_preTaskAdd";
            this.button_preTaskAdd.Size = new System.Drawing.Size(75, 23);
            this.button_preTaskAdd.TabIndex = 10;
            this.button_preTaskAdd.Text = "添加";
            this.button_preTaskAdd.UseVisualStyleBackColor = true;
            this.button_preTaskAdd.Click += new System.EventHandler(this.button_preTaskAdd_Click);
            // 
            // textBoxPreTaskName
            // 
            this.textBoxPreTaskName.Location = new System.Drawing.Point(99, 98);
            this.textBoxPreTaskName.Name = "textBoxPreTaskName";
            this.textBoxPreTaskName.Size = new System.Drawing.Size(181, 21);
            this.textBoxPreTaskName.TabIndex = 3;
            // 
            // textBoxPreTaskID
            // 
            this.textBoxPreTaskID.Location = new System.Drawing.Point(99, 64);
            this.textBoxPreTaskID.Name = "textBoxPreTaskID";
            this.textBoxPreTaskID.Size = new System.Drawing.Size(181, 21);
            this.textBoxPreTaskID.TabIndex = 3;
            // 
            // label66
            // 
            this.label66.AutoSize = true;
            this.label66.Location = new System.Drawing.Point(33, 101);
            this.label66.Name = "label66";
            this.label66.Size = new System.Drawing.Size(53, 12);
            this.label66.TabIndex = 2;
            this.label66.Text = "任务名称";
            // 
            // label65
            // 
            this.label65.AutoSize = true;
            this.label65.Location = new System.Drawing.Point(33, 69);
            this.label65.Name = "label65";
            this.label65.Size = new System.Drawing.Size(41, 12);
            this.label65.TabIndex = 2;
            this.label65.Text = "任务ID";
            // 
            // buttonSelectPreTask
            // 
            this.buttonSelectPreTask.Location = new System.Drawing.Point(111, 26);
            this.buttonSelectPreTask.Name = "buttonSelectPreTask";
            this.buttonSelectPreTask.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectPreTask.TabIndex = 1;
            this.buttonSelectPreTask.Text = "Select";
            this.buttonSelectPreTask.UseVisualStyleBackColor = true;
            this.buttonSelectPreTask.Click += new System.EventHandler(this.buttonSelectPreTask_Click);
            // 
            // label64
            // 
            this.label64.AutoSize = true;
            this.label64.Location = new System.Drawing.Point(31, 31);
            this.label64.Name = "label64";
            this.label64.Size = new System.Drawing.Size(53, 12);
            this.label64.TabIndex = 0;
            this.label64.Text = "选择任务";
            // 
            // groupBox30
            // 
            this.groupBox30.Controls.Add(this.comboBox_SelectJob);
            this.groupBox30.Controls.Add(this.button_careerRemove);
            this.groupBox30.Controls.Add(this.button_careerAdd);
            this.groupBox30.Controls.Add(this.dataGridViewJobLimit);
            this.groupBox30.Controls.Add(this.label63);
            this.groupBox30.Location = new System.Drawing.Point(576, 22);
            this.groupBox30.Name = "groupBox30";
            this.groupBox30.Size = new System.Drawing.Size(202, 279);
            this.groupBox30.TabIndex = 6;
            this.groupBox30.TabStop = false;
            this.groupBox30.Text = "职业限制";
            // 
            // comboBox_SelectJob
            // 
            this.comboBox_SelectJob.FormattingEnabled = true;
            this.comboBox_SelectJob.Location = new System.Drawing.Point(67, 39);
            this.comboBox_SelectJob.Name = "comboBox_SelectJob";
            this.comboBox_SelectJob.Size = new System.Drawing.Size(121, 20);
            this.comboBox_SelectJob.TabIndex = 10;
            // 
            // button_careerRemove
            // 
            this.button_careerRemove.Location = new System.Drawing.Point(113, 230);
            this.button_careerRemove.Name = "button_careerRemove";
            this.button_careerRemove.Size = new System.Drawing.Size(75, 23);
            this.button_careerRemove.TabIndex = 9;
            this.button_careerRemove.Text = "删除";
            this.button_careerRemove.UseVisualStyleBackColor = true;
            this.button_careerRemove.Click += new System.EventHandler(this.button_careerRemove_Click);
            // 
            // button_careerAdd
            // 
            this.button_careerAdd.Location = new System.Drawing.Point(20, 228);
            this.button_careerAdd.Name = "button_careerAdd";
            this.button_careerAdd.Size = new System.Drawing.Size(75, 23);
            this.button_careerAdd.TabIndex = 8;
            this.button_careerAdd.Text = "添加";
            this.button_careerAdd.UseVisualStyleBackColor = true;
            this.button_careerAdd.Click += new System.EventHandler(this.button_careerAdd_Click);
            // 
            // dataGridViewJobLimit
            // 
            this.dataGridViewJobLimit.AllowUserToAddRows = false;
            this.dataGridViewJobLimit.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewJobLimit.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewJobLimit.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.JobID,
            this.JobName});
            this.dataGridViewJobLimit.Location = new System.Drawing.Point(20, 96);
            this.dataGridViewJobLimit.MultiSelect = false;
            this.dataGridViewJobLimit.Name = "dataGridViewJobLimit";
            this.dataGridViewJobLimit.RowHeadersVisible = false;
            this.dataGridViewJobLimit.RowTemplate.Height = 23;
            this.dataGridViewJobLimit.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewJobLimit.Size = new System.Drawing.Size(168, 107);
            this.dataGridViewJobLimit.TabIndex = 2;
            // 
            // JobID
            // 
            this.JobID.HeaderText = "职业ID";
            this.JobID.Name = "JobID";
            this.JobID.Width = 66;
            // 
            // JobName
            // 
            this.JobName.HeaderText = "职业名称";
            this.JobName.Name = "JobName";
            this.JobName.Width = 78;
            // 
            // label63
            // 
            this.label63.AutoSize = true;
            this.label63.Location = new System.Drawing.Point(7, 42);
            this.label63.Name = "label63";
            this.label63.Size = new System.Drawing.Size(53, 12);
            this.label63.TabIndex = 0;
            this.label63.Text = "职业选择";
            // 
            // groupBox29
            // 
            this.groupBox29.Controls.Add(this.comboBox_limit_family);
            this.groupBox29.Location = new System.Drawing.Point(30, 398);
            this.groupBox29.Name = "groupBox29";
            this.groupBox29.Size = new System.Drawing.Size(207, 65);
            this.groupBox29.TabIndex = 5;
            this.groupBox29.TabStop = false;
            this.groupBox29.Text = "家族/公会限制";
            // 
            // comboBox_limit_family
            // 
            this.comboBox_limit_family.FormattingEnabled = true;
            this.comboBox_limit_family.Location = new System.Drawing.Point(75, 29);
            this.comboBox_limit_family.Name = "comboBox_limit_family";
            this.comboBox_limit_family.Size = new System.Drawing.Size(121, 20);
            this.comboBox_limit_family.TabIndex = 1;
            this.comboBox_limit_family.SelectedIndexChanged += new System.EventHandler(this.comboBox_limit_family_SelectedIndexChanged);
            // 
            // groupBox28
            // 
            this.groupBox28.Controls.Add(this.comboBox_limitCamp);
            this.groupBox28.Location = new System.Drawing.Point(30, 317);
            this.groupBox28.Name = "groupBox28";
            this.groupBox28.Size = new System.Drawing.Size(210, 60);
            this.groupBox28.TabIndex = 4;
            this.groupBox28.TabStop = false;
            this.groupBox28.Text = "阵营限制";
            // 
            // comboBox_limitCamp
            // 
            this.comboBox_limitCamp.FormattingEnabled = true;
            this.comboBox_limitCamp.Location = new System.Drawing.Point(74, 20);
            this.comboBox_limitCamp.Name = "comboBox_limitCamp";
            this.comboBox_limitCamp.Size = new System.Drawing.Size(121, 20);
            this.comboBox_limitCamp.TabIndex = 0;
            this.comboBox_limitCamp.SelectedIndexChanged += new System.EventHandler(this.comboBox_limitCamp_SelectedIndexChanged);
            // 
            // groupBox27
            // 
            this.groupBox27.Controls.Add(this.comboBoxRelationLimit);
            this.groupBox27.Controls.Add(this.label62);
            this.groupBox27.Enabled = false;
            this.groupBox27.Location = new System.Drawing.Point(29, 238);
            this.groupBox27.Name = "groupBox27";
            this.groupBox27.Size = new System.Drawing.Size(209, 64);
            this.groupBox27.TabIndex = 3;
            this.groupBox27.TabStop = false;
            this.groupBox27.Text = "特殊限制";
            // 
            // comboBoxRelationLimit
            // 
            this.comboBoxRelationLimit.Enabled = false;
            this.comboBoxRelationLimit.FormattingEnabled = true;
            this.comboBoxRelationLimit.Items.AddRange(new object[] {
            "师徒关系",
            "夫妻关系"});
            this.comboBoxRelationLimit.Location = new System.Drawing.Point(79, 25);
            this.comboBoxRelationLimit.Name = "comboBoxRelationLimit";
            this.comboBoxRelationLimit.Size = new System.Drawing.Size(116, 20);
            this.comboBoxRelationLimit.TabIndex = 1;
            // 
            // label62
            // 
            this.label62.AutoSize = true;
            this.label62.Location = new System.Drawing.Point(11, 29);
            this.label62.Name = "label62";
            this.label62.Size = new System.Drawing.Size(53, 12);
            this.label62.TabIndex = 0;
            this.label62.Text = "关系选择";
            // 
            // groupBox26
            // 
            this.groupBox26.Controls.Add(this.textBoxGradeMax);
            this.groupBox26.Controls.Add(this.textBoxGradeMin);
            this.groupBox26.Controls.Add(this.label60);
            this.groupBox26.Controls.Add(this.label61);
            this.groupBox26.Enabled = false;
            this.groupBox26.Location = new System.Drawing.Point(30, 164);
            this.groupBox26.Name = "groupBox26";
            this.groupBox26.Size = new System.Drawing.Size(209, 57);
            this.groupBox26.TabIndex = 2;
            this.groupBox26.TabStop = false;
            this.groupBox26.Text = "境界限制";
            // 
            // textBoxGradeMax
            // 
            this.textBoxGradeMax.Location = new System.Drawing.Point(144, 21);
            this.textBoxGradeMax.Name = "textBoxGradeMax";
            this.textBoxGradeMax.Size = new System.Drawing.Size(47, 21);
            this.textBoxGradeMax.TabIndex = 3;
            this.textBoxGradeMax.TextChanged += new System.EventHandler(this.textBoxGradeMax_TextChanged);
            // 
            // textBoxGradeMin
            // 
            this.textBoxGradeMin.Location = new System.Drawing.Point(74, 21);
            this.textBoxGradeMin.Name = "textBoxGradeMin";
            this.textBoxGradeMin.Size = new System.Drawing.Size(47, 21);
            this.textBoxGradeMin.TabIndex = 3;
            this.textBoxGradeMin.TextChanged += new System.EventHandler(this.textBoxGradeMin_TextChanged);
            // 
            // label60
            // 
            this.label60.AutoSize = true;
            this.label60.Location = new System.Drawing.Point(127, 29);
            this.label60.Name = "label60";
            this.label60.Size = new System.Drawing.Size(11, 12);
            this.label60.TabIndex = 2;
            this.label60.Text = "~";
            // 
            // label61
            // 
            this.label61.AutoSize = true;
            this.label61.Location = new System.Drawing.Point(6, 24);
            this.label61.Name = "label61";
            this.label61.Size = new System.Drawing.Size(53, 12);
            this.label61.TabIndex = 2;
            this.label61.Text = "境界范围";
            // 
            // groupBox25
            // 
            this.groupBox25.Controls.Add(this.textBoxHourTo);
            this.groupBox25.Controls.Add(this.checkBoxTimeLimit);
            this.groupBox25.Controls.Add(this.textBoxHourFrom);
            this.groupBox25.Controls.Add(this.label59);
            this.groupBox25.Controls.Add(this.checkBoxDateLimit);
            this.groupBox25.Controls.Add(this.dateTimePickerDateTo);
            this.groupBox25.Controls.Add(this.dateTimePickerDateFrom);
            this.groupBox25.Controls.Add(this.label58);
            this.groupBox25.Controls.Add(this.label57);
            this.groupBox25.Location = new System.Drawing.Point(266, 21);
            this.groupBox25.Name = "groupBox25";
            this.groupBox25.Size = new System.Drawing.Size(292, 167);
            this.groupBox25.TabIndex = 1;
            this.groupBox25.TabStop = false;
            this.groupBox25.Text = "时间限制";
            // 
            // textBoxHourTo
            // 
            this.textBoxHourTo.Location = new System.Drawing.Point(135, 135);
            this.textBoxHourTo.Name = "textBoxHourTo";
            this.textBoxHourTo.Size = new System.Drawing.Size(69, 21);
            this.textBoxHourTo.TabIndex = 3;
            this.textBoxHourTo.TextChanged += new System.EventHandler(this.textBoxHourTo_TextChanged);
            // 
            // checkBoxTimeLimit
            // 
            this.checkBoxTimeLimit.AutoSize = true;
            this.checkBoxTimeLimit.Location = new System.Drawing.Point(19, 113);
            this.checkBoxTimeLimit.Name = "checkBoxTimeLimit";
            this.checkBoxTimeLimit.Size = new System.Drawing.Size(72, 16);
            this.checkBoxTimeLimit.TabIndex = 3;
            this.checkBoxTimeLimit.Text = "每日时段";
            this.checkBoxTimeLimit.UseVisualStyleBackColor = true;
            this.checkBoxTimeLimit.CheckedChanged += new System.EventHandler(this.checkBoxTimeLimit_CheckedChanged);
            // 
            // textBoxHourFrom
            // 
            this.textBoxHourFrom.Location = new System.Drawing.Point(43, 135);
            this.textBoxHourFrom.Name = "textBoxHourFrom";
            this.textBoxHourFrom.Size = new System.Drawing.Size(69, 21);
            this.textBoxHourFrom.TabIndex = 3;
            this.textBoxHourFrom.TextChanged += new System.EventHandler(this.textBoxHourFrom_TextChanged);
            // 
            // label59
            // 
            this.label59.AutoSize = true;
            this.label59.Location = new System.Drawing.Point(118, 143);
            this.label59.Name = "label59";
            this.label59.Size = new System.Drawing.Size(11, 12);
            this.label59.TabIndex = 2;
            this.label59.Text = "~";
            // 
            // checkBoxDateLimit
            // 
            this.checkBoxDateLimit.AutoSize = true;
            this.checkBoxDateLimit.Location = new System.Drawing.Point(18, 24);
            this.checkBoxDateLimit.Name = "checkBoxDateLimit";
            this.checkBoxDateLimit.Size = new System.Drawing.Size(72, 16);
            this.checkBoxDateLimit.TabIndex = 2;
            this.checkBoxDateLimit.Text = "日期跨度";
            this.checkBoxDateLimit.UseVisualStyleBackColor = true;
            this.checkBoxDateLimit.CheckedChanged += new System.EventHandler(this.checkBoxDateLimit_CheckedChanged);
            // 
            // dateTimePickerDateTo
            // 
            this.dateTimePickerDateTo.Location = new System.Drawing.Point(50, 82);
            this.dateTimePickerDateTo.Name = "dateTimePickerDateTo";
            this.dateTimePickerDateTo.Size = new System.Drawing.Size(155, 21);
            this.dateTimePickerDateTo.TabIndex = 1;
            this.dateTimePickerDateTo.ValueChanged += new System.EventHandler(this.dateTimePickerDateTo_ValueChanged);
            // 
            // dateTimePickerDateFrom
            // 
            this.dateTimePickerDateFrom.Location = new System.Drawing.Point(50, 47);
            this.dateTimePickerDateFrom.Name = "dateTimePickerDateFrom";
            this.dateTimePickerDateFrom.Size = new System.Drawing.Size(155, 21);
            this.dateTimePickerDateFrom.TabIndex = 1;
            this.dateTimePickerDateFrom.ValueChanged += new System.EventHandler(this.dateTimePickerDateFrom_ValueChanged);
            // 
            // label58
            // 
            this.label58.AutoSize = true;
            this.label58.Location = new System.Drawing.Point(16, 85);
            this.label58.Name = "label58";
            this.label58.Size = new System.Drawing.Size(17, 12);
            this.label58.TabIndex = 0;
            this.label58.Text = "To";
            // 
            // label57
            // 
            this.label57.AutoSize = true;
            this.label57.Location = new System.Drawing.Point(15, 53);
            this.label57.Name = "label57";
            this.label57.Size = new System.Drawing.Size(29, 12);
            this.label57.TabIndex = 0;
            this.label57.Text = "From";
            // 
            // groupBox23
            // 
            this.groupBox23.Controls.Add(this.comboBoxSexLimit);
            this.groupBox23.Controls.Add(this.label54);
            this.groupBox23.Location = new System.Drawing.Point(30, 22);
            this.groupBox23.Name = "groupBox23";
            this.groupBox23.Size = new System.Drawing.Size(210, 61);
            this.groupBox23.TabIndex = 0;
            this.groupBox23.TabStop = false;
            this.groupBox23.Text = "性别限制";
            // 
            // comboBoxSexLimit
            // 
            this.comboBoxSexLimit.FormattingEnabled = true;
            this.comboBoxSexLimit.Location = new System.Drawing.Point(75, 24);
            this.comboBoxSexLimit.Name = "comboBoxSexLimit";
            this.comboBoxSexLimit.Size = new System.Drawing.Size(121, 20);
            this.comboBoxSexLimit.TabIndex = 1;
            this.comboBoxSexLimit.SelectedIndexChanged += new System.EventHandler(this.comboBoxSexLimit_SelectedIndexChanged);
            // 
            // label54
            // 
            this.label54.AutoSize = true;
            this.label54.Location = new System.Drawing.Point(6, 27);
            this.label54.Name = "label54";
            this.label54.Size = new System.Drawing.Size(53, 12);
            this.label54.TabIndex = 0;
            this.label54.Text = "性别选择";
            // 
            // tabPageProc
            // 
            this.tabPageProc.Controls.Add(this.tabControlProcess);
            this.tabPageProc.Location = new System.Drawing.Point(4, 22);
            this.tabPageProc.Name = "tabPageProc";
            this.tabPageProc.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageProc.Size = new System.Drawing.Size(1150, 527);
            this.tabPageProc.TabIndex = 4;
            this.tabPageProc.Text = "任务过程";
            this.tabPageProc.UseVisualStyleBackColor = true;
            // 
            // tabControlProcess
            // 
            this.tabControlProcess.Controls.Add(this.tabPageGeneral);
            this.tabControlProcess.Controls.Add(this.tabPageKill);
            this.tabControlProcess.Controls.Add(this.tabPageGrow);
            this.tabControlProcess.Controls.Add(this.tabPageCollect);
            this.tabControlProcess.Controls.Add(this.tabPageGather);
            this.tabControlProcess.Controls.Add(this.tabPageProbe);
            this.tabControlProcess.Controls.Add(this.tabPageBehave);
            this.tabControlProcess.Controls.Add(this.tabPageBuild);
            this.tabControlProcess.Controls.Add(this.tabPageTalk);
            this.tabControlProcess.Location = new System.Drawing.Point(19, 3);
            this.tabControlProcess.Name = "tabControlProcess";
            this.tabControlProcess.SelectedIndex = 0;
            this.tabControlProcess.Size = new System.Drawing.Size(1098, 570);
            this.tabControlProcess.TabIndex = 0;
            // 
            // tabPageGeneral
            // 
            this.tabPageGeneral.Controls.Add(this.groupBox13);
            this.tabPageGeneral.Controls.Add(this.groupBox12);
            this.tabPageGeneral.Location = new System.Drawing.Point(4, 22);
            this.tabPageGeneral.Name = "tabPageGeneral";
            this.tabPageGeneral.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGeneral.Size = new System.Drawing.Size(1090, 544);
            this.tabPageGeneral.TabIndex = 0;
            this.tabPageGeneral.Text = "综合设定";
            this.tabPageGeneral.UseVisualStyleBackColor = true;
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.dataGridViewGiveItem);
            this.groupBox13.Controls.Add(this.buttonGiveItemDel);
            this.groupBox13.Controls.Add(this.buttonGiveItemAdd);
            this.groupBox13.Controls.Add(this.textBoxGiveItemCount);
            this.groupBox13.Controls.Add(this.textBoxGiveItemID);
            this.groupBox13.Controls.Add(this.textBoxGiveItemName);
            this.groupBox13.Controls.Add(this.label39);
            this.groupBox13.Controls.Add(this.label16);
            this.groupBox13.Controls.Add(this.label15);
            this.groupBox13.Controls.Add(this.label14);
            this.groupBox13.Controls.Add(this.buttonGiveItem);
            this.groupBox13.Location = new System.Drawing.Point(28, 157);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(634, 239);
            this.groupBox13.TabIndex = 1;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "道具给予";
            // 
            // dataGridViewGiveItem
            // 
            this.dataGridViewGiveItem.AllowUserToAddRows = false;
            this.dataGridViewGiveItem.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewGiveItem.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewGiveItem.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.GiveItemID,
            this.GiveItemName,
            this.GiveItemCount});
            this.dataGridViewGiveItem.Location = new System.Drawing.Point(247, 64);
            this.dataGridViewGiveItem.Name = "dataGridViewGiveItem";
            this.dataGridViewGiveItem.RowHeadersVisible = false;
            this.dataGridViewGiveItem.RowTemplate.Height = 23;
            this.dataGridViewGiveItem.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewGiveItem.Size = new System.Drawing.Size(217, 142);
            this.dataGridViewGiveItem.TabIndex = 6;
            // 
            // GiveItemID
            // 
            this.GiveItemID.HeaderText = "道具ID";
            this.GiveItemID.Name = "GiveItemID";
            this.GiveItemID.Width = 66;
            // 
            // GiveItemName
            // 
            this.GiveItemName.HeaderText = "道具名称";
            this.GiveItemName.Name = "GiveItemName";
            this.GiveItemName.Width = 78;
            // 
            // GiveItemCount
            // 
            this.GiveItemCount.HeaderText = "数量";
            this.GiveItemCount.Name = "GiveItemCount";
            this.GiveItemCount.Width = 54;
            // 
            // buttonGiveItemDel
            // 
            this.buttonGiveItemDel.Location = new System.Drawing.Point(125, 184);
            this.buttonGiveItemDel.Name = "buttonGiveItemDel";
            this.buttonGiveItemDel.Size = new System.Drawing.Size(75, 23);
            this.buttonGiveItemDel.TabIndex = 5;
            this.buttonGiveItemDel.Text = "删除";
            this.buttonGiveItemDel.UseVisualStyleBackColor = true;
            this.buttonGiveItemDel.Click += new System.EventHandler(this.buttonGiveItemDel_Click);
            // 
            // buttonGiveItemAdd
            // 
            this.buttonGiveItemAdd.Location = new System.Drawing.Point(23, 184);
            this.buttonGiveItemAdd.Name = "buttonGiveItemAdd";
            this.buttonGiveItemAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonGiveItemAdd.TabIndex = 5;
            this.buttonGiveItemAdd.Text = "添加";
            this.buttonGiveItemAdd.UseVisualStyleBackColor = true;
            this.buttonGiveItemAdd.Click += new System.EventHandler(this.buttonGiveItemAdd_Click);
            // 
            // textBoxGiveItemCount
            // 
            this.textBoxGiveItemCount.Location = new System.Drawing.Point(87, 152);
            this.textBoxGiveItemCount.Name = "textBoxGiveItemCount";
            this.textBoxGiveItemCount.Size = new System.Drawing.Size(113, 21);
            this.textBoxGiveItemCount.TabIndex = 4;
            // 
            // textBoxGiveItemID
            // 
            this.textBoxGiveItemID.Location = new System.Drawing.Point(87, 77);
            this.textBoxGiveItemID.Name = "textBoxGiveItemID";
            this.textBoxGiveItemID.Size = new System.Drawing.Size(113, 21);
            this.textBoxGiveItemID.TabIndex = 3;
            // 
            // textBoxGiveItemName
            // 
            this.textBoxGiveItemName.Location = new System.Drawing.Point(87, 115);
            this.textBoxGiveItemName.Name = "textBoxGiveItemName";
            this.textBoxGiveItemName.Size = new System.Drawing.Size(113, 21);
            this.textBoxGiveItemName.TabIndex = 3;
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Location = new System.Drawing.Point(21, 82);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(41, 12);
            this.label39.TabIndex = 2;
            this.label39.Text = "道具ID";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(21, 155);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(53, 12);
            this.label16.TabIndex = 2;
            this.label16.Text = "给予数量";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(21, 119);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(53, 12);
            this.label15.TabIndex = 2;
            this.label15.Text = "道具名称";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(21, 45);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(53, 12);
            this.label14.TabIndex = 1;
            this.label14.Text = "道具选择";
            // 
            // buttonGiveItem
            // 
            this.buttonGiveItem.Location = new System.Drawing.Point(85, 40);
            this.buttonGiveItem.Name = "buttonGiveItem";
            this.buttonGiveItem.Size = new System.Drawing.Size(75, 23);
            this.buttonGiveItem.TabIndex = 0;
            this.buttonGiveItem.Text = "Select";
            this.buttonGiveItem.UseVisualStyleBackColor = true;
            this.buttonGiveItem.Click += new System.EventHandler(this.buttonGiveItem_Click);
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.label13);
            this.groupBox12.Controls.Add(this.textBoxLimitTime);
            this.groupBox12.Controls.Add(this.label12);
            this.groupBox12.Location = new System.Drawing.Point(30, 33);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(243, 81);
            this.groupBox12.TabIndex = 0;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "设定时限";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(199, 39);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(17, 12);
            this.label13.TabIndex = 2;
            this.label13.Text = "秒";
            // 
            // textBoxLimitTime
            // 
            this.textBoxLimitTime.Location = new System.Drawing.Point(94, 36);
            this.textBoxLimitTime.Name = "textBoxLimitTime";
            this.textBoxLimitTime.Size = new System.Drawing.Size(88, 21);
            this.textBoxLimitTime.TabIndex = 1;
            this.textBoxLimitTime.TextChanged += new System.EventHandler(this.textBoxLimitTime_TextChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(19, 39);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 12);
            this.label12.TabIndex = 0;
            this.label12.Text = "倒计限时";
            // 
            // tabPageKill
            // 
            this.tabPageKill.Controls.Add(this.groupBox14);
            this.tabPageKill.Location = new System.Drawing.Point(4, 22);
            this.tabPageKill.Name = "tabPageKill";
            this.tabPageKill.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageKill.Size = new System.Drawing.Size(1090, 544);
            this.tabPageKill.TabIndex = 1;
            this.tabPageKill.Text = "猎杀";
            this.tabPageKill.UseVisualStyleBackColor = true;
            // 
            // groupBox14
            // 
            this.groupBox14.Controls.Add(this.textBoxKillMonsterParam);
            this.groupBox14.Controls.Add(this.label134);
            this.groupBox14.Controls.Add(this.dataGridViewKillMonster);
            this.groupBox14.Controls.Add(this.buttonKillMonsterDel);
            this.groupBox14.Controls.Add(this.buttonKillMonsterAdd);
            this.groupBox14.Controls.Add(this.label19);
            this.groupBox14.Controls.Add(this.textBoxKillMonsterCount);
            this.groupBox14.Controls.Add(this.textBoxKillMonsterID);
            this.groupBox14.Controls.Add(this.textBoxKillMonsterName);
            this.groupBox14.Controls.Add(this.label40);
            this.groupBox14.Controls.Add(this.label18);
            this.groupBox14.Controls.Add(this.buttonKillMonster);
            this.groupBox14.Controls.Add(this.label17);
            this.groupBox14.Location = new System.Drawing.Point(36, 49);
            this.groupBox14.Name = "groupBox14";
            this.groupBox14.Size = new System.Drawing.Size(583, 244);
            this.groupBox14.TabIndex = 0;
            this.groupBox14.TabStop = false;
            this.groupBox14.Text = "猎杀";
            // 
            // textBoxKillMonsterParam
            // 
            this.textBoxKillMonsterParam.Location = new System.Drawing.Point(87, 179);
            this.textBoxKillMonsterParam.Name = "textBoxKillMonsterParam";
            this.textBoxKillMonsterParam.Size = new System.Drawing.Size(94, 21);
            this.textBoxKillMonsterParam.TabIndex = 9;
            // 
            // label134
            // 
            this.label134.AutoSize = true;
            this.label134.Location = new System.Drawing.Point(42, 184);
            this.label134.Name = "label134";
            this.label134.Size = new System.Drawing.Size(29, 12);
            this.label134.TabIndex = 8;
            this.label134.Text = "参数";
            // 
            // dataGridViewKillMonster
            // 
            this.dataGridViewKillMonster.AllowUserToAddRows = false;
            this.dataGridViewKillMonster.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewKillMonster.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewKillMonster.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.MonsterID,
            this.MonsterName,
            this.MonsterNum,
            this.Fake,
            this.strParam});
            this.dataGridViewKillMonster.Location = new System.Drawing.Point(191, 46);
            this.dataGridViewKillMonster.Name = "dataGridViewKillMonster";
            this.dataGridViewKillMonster.RowHeadersVisible = false;
            this.dataGridViewKillMonster.RowTemplate.Height = 23;
            this.dataGridViewKillMonster.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewKillMonster.Size = new System.Drawing.Size(371, 130);
            this.dataGridViewKillMonster.TabIndex = 7;
            // 
            // MonsterID
            // 
            this.MonsterID.HeaderText = "怪物ID";
            this.MonsterID.Name = "MonsterID";
            this.MonsterID.Width = 66;
            // 
            // MonsterName
            // 
            this.MonsterName.HeaderText = "怪物名称 ";
            this.MonsterName.Name = "MonsterName";
            this.MonsterName.Width = 78;
            // 
            // MonsterNum
            // 
            this.MonsterNum.HeaderText = "击杀数量";
            this.MonsterNum.Name = "MonsterNum";
            this.MonsterNum.Width = 78;
            // 
            // Fake
            // 
            this.Fake.HeaderText = "假战斗";
            this.Fake.Name = "Fake";
            this.Fake.Width = 66;
            // 
            // strParam
            // 
            this.strParam.HeaderText = "参数";
            this.strParam.Name = "strParam";
            this.strParam.Width = 54;
            // 
            // buttonKillMonsterDel
            // 
            this.buttonKillMonsterDel.Location = new System.Drawing.Point(103, 211);
            this.buttonKillMonsterDel.Name = "buttonKillMonsterDel";
            this.buttonKillMonsterDel.Size = new System.Drawing.Size(75, 23);
            this.buttonKillMonsterDel.TabIndex = 6;
            this.buttonKillMonsterDel.Text = "删除";
            this.buttonKillMonsterDel.UseVisualStyleBackColor = true;
            this.buttonKillMonsterDel.Click += new System.EventHandler(this.buttonKillMonsterDel_Click);
            // 
            // buttonKillMonsterAdd
            // 
            this.buttonKillMonsterAdd.Location = new System.Drawing.Point(20, 211);
            this.buttonKillMonsterAdd.Name = "buttonKillMonsterAdd";
            this.buttonKillMonsterAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonKillMonsterAdd.TabIndex = 6;
            this.buttonKillMonsterAdd.Text = "添加";
            this.buttonKillMonsterAdd.UseVisualStyleBackColor = true;
            this.buttonKillMonsterAdd.Click += new System.EventHandler(this.buttonKillMonsterAdd_Click);
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(17, 149);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(53, 12);
            this.label19.TabIndex = 5;
            this.label19.Text = "击杀数量";
            // 
            // textBoxKillMonsterCount
            // 
            this.textBoxKillMonsterCount.Location = new System.Drawing.Point(87, 146);
            this.textBoxKillMonsterCount.Name = "textBoxKillMonsterCount";
            this.textBoxKillMonsterCount.Size = new System.Drawing.Size(95, 21);
            this.textBoxKillMonsterCount.TabIndex = 4;
            // 
            // textBoxKillMonsterID
            // 
            this.textBoxKillMonsterID.Location = new System.Drawing.Point(88, 78);
            this.textBoxKillMonsterID.Name = "textBoxKillMonsterID";
            this.textBoxKillMonsterID.Size = new System.Drawing.Size(95, 21);
            this.textBoxKillMonsterID.TabIndex = 3;
            // 
            // textBoxKillMonsterName
            // 
            this.textBoxKillMonsterName.Location = new System.Drawing.Point(87, 112);
            this.textBoxKillMonsterName.Name = "textBoxKillMonsterName";
            this.textBoxKillMonsterName.Size = new System.Drawing.Size(95, 21);
            this.textBoxKillMonsterName.TabIndex = 3;
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Location = new System.Drawing.Point(18, 81);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(41, 12);
            this.label40.TabIndex = 2;
            this.label40.Text = "怪物ID";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(17, 115);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(53, 12);
            this.label18.TabIndex = 2;
            this.label18.Text = "怪物名称";
            // 
            // buttonKillMonster
            // 
            this.buttonKillMonster.Location = new System.Drawing.Point(87, 36);
            this.buttonKillMonster.Name = "buttonKillMonster";
            this.buttonKillMonster.Size = new System.Drawing.Size(75, 23);
            this.buttonKillMonster.TabIndex = 1;
            this.buttonKillMonster.Text = "Select";
            this.buttonKillMonster.UseVisualStyleBackColor = true;
            this.buttonKillMonster.Click += new System.EventHandler(this.buttonKillMonster_Click);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(17, 41);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(53, 12);
            this.label17.TabIndex = 0;
            this.label17.Text = "怪物选择";
            // 
            // tabPageGrow
            // 
            this.tabPageGrow.Controls.Add(this.label145);
            this.tabPageGrow.Controls.Add(this.groupBox64);
            this.tabPageGrow.Controls.Add(this.button_growRemove);
            this.tabPageGrow.Controls.Add(this.button_growAdd);
            this.tabPageGrow.Controls.Add(this.dataGridView_grow);
            this.tabPageGrow.Controls.Add(this.groupBox48);
            this.tabPageGrow.Controls.Add(this.groupBox47);
            this.tabPageGrow.Location = new System.Drawing.Point(4, 22);
            this.tabPageGrow.Name = "tabPageGrow";
            this.tabPageGrow.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGrow.Size = new System.Drawing.Size(1090, 544);
            this.tabPageGrow.TabIndex = 8;
            this.tabPageGrow.Text = "成长";
            this.tabPageGrow.UseVisualStyleBackColor = true;
            // 
            // label145
            // 
            this.label145.AutoSize = true;
            this.label145.Location = new System.Drawing.Point(237, 141);
            this.label145.Name = "label145";
            this.label145.Size = new System.Drawing.Size(203, 12);
            this.label145.TabIndex = 6;
            this.label145.Text = "注释:[附加信息]目前针对[佣兵升阶]";
            // 
            // groupBox64
            // 
            this.groupBox64.Controls.Add(this.txt_GrowName);
            this.groupBox64.Controls.Add(this.label143);
            this.groupBox64.Controls.Add(this.txt_GrowID);
            this.groupBox64.Controls.Add(this.label144);
            this.groupBox64.Location = new System.Drawing.Point(240, 13);
            this.groupBox64.Name = "groupBox64";
            this.groupBox64.Size = new System.Drawing.Size(200, 116);
            this.groupBox64.TabIndex = 5;
            this.groupBox64.TabStop = false;
            this.groupBox64.Text = "附加信息";
            // 
            // txt_GrowName
            // 
            this.txt_GrowName.Location = new System.Drawing.Point(73, 65);
            this.txt_GrowName.Name = "txt_GrowName";
            this.txt_GrowName.Size = new System.Drawing.Size(121, 21);
            this.txt_GrowName.TabIndex = 8;
            // 
            // label143
            // 
            this.label143.AutoSize = true;
            this.label143.Location = new System.Drawing.Point(10, 69);
            this.label143.Name = "label143";
            this.label143.Size = new System.Drawing.Size(59, 12);
            this.label143.TabIndex = 7;
            this.label143.Text = "附加名称:";
            // 
            // txt_GrowID
            // 
            this.txt_GrowID.Location = new System.Drawing.Point(73, 27);
            this.txt_GrowID.Name = "txt_GrowID";
            this.txt_GrowID.Size = new System.Drawing.Size(121, 21);
            this.txt_GrowID.TabIndex = 6;
            // 
            // label144
            // 
            this.label144.AutoSize = true;
            this.label144.Location = new System.Drawing.Point(22, 31);
            this.label144.Name = "label144";
            this.label144.Size = new System.Drawing.Size(47, 12);
            this.label144.TabIndex = 4;
            this.label144.Text = "附加值:";
            // 
            // button_growRemove
            // 
            this.button_growRemove.Location = new System.Drawing.Point(281, 356);
            this.button_growRemove.Name = "button_growRemove";
            this.button_growRemove.Size = new System.Drawing.Size(75, 23);
            this.button_growRemove.TabIndex = 4;
            this.button_growRemove.Text = "删除";
            this.button_growRemove.UseVisualStyleBackColor = true;
            this.button_growRemove.Click += new System.EventHandler(this.button_growRemove_Click);
            // 
            // button_growAdd
            // 
            this.button_growAdd.Location = new System.Drawing.Point(87, 356);
            this.button_growAdd.Name = "button_growAdd";
            this.button_growAdd.Size = new System.Drawing.Size(75, 23);
            this.button_growAdd.TabIndex = 3;
            this.button_growAdd.Text = "添加";
            this.button_growAdd.UseVisualStyleBackColor = true;
            this.button_growAdd.Click += new System.EventHandler(this.button_growAdd_Click);
            // 
            // dataGridView_grow
            // 
            this.dataGridView_grow.AllowUserToAddRows = false;
            this.dataGridView_grow.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_grow.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.roleProperty,
            this.roleValue,
            this.extid,
            this.extname});
            this.dataGridView_grow.Location = new System.Drawing.Point(14, 175);
            this.dataGridView_grow.Name = "dataGridView_grow";
            this.dataGridView_grow.RowHeadersVisible = false;
            this.dataGridView_grow.RowTemplate.Height = 23;
            this.dataGridView_grow.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_grow.Size = new System.Drawing.Size(407, 150);
            this.dataGridView_grow.TabIndex = 2;
            // 
            // roleProperty
            // 
            this.roleProperty.HeaderText = "角色属性";
            this.roleProperty.Name = "roleProperty";
            // 
            // roleValue
            // 
            this.roleValue.HeaderText = "数值需求";
            this.roleValue.Name = "roleValue";
            // 
            // extid
            // 
            this.extid.HeaderText = "附加值";
            this.extid.Name = "extid";
            // 
            // extname
            // 
            this.extname.HeaderText = "附加名";
            this.extname.Name = "extname";
            // 
            // groupBox48
            // 
            this.groupBox48.Controls.Add(this.textBox_campName);
            this.groupBox48.Controls.Add(this.textBox_campID);
            this.groupBox48.Controls.Add(this.label113);
            this.groupBox48.Controls.Add(this.button_selectCamp);
            this.groupBox48.Controls.Add(this.label114);
            this.groupBox48.Location = new System.Drawing.Point(466, 13);
            this.groupBox48.Name = "groupBox48";
            this.groupBox48.Size = new System.Drawing.Size(200, 116);
            this.groupBox48.TabIndex = 1;
            this.groupBox48.TabStop = false;
            this.groupBox48.Text = "阵营";
            // 
            // textBox_campName
            // 
            this.textBox_campName.Location = new System.Drawing.Point(73, 80);
            this.textBox_campName.Name = "textBox_campName";
            this.textBox_campName.ReadOnly = true;
            this.textBox_campName.Size = new System.Drawing.Size(121, 21);
            this.textBox_campName.TabIndex = 6;
            // 
            // textBox_campID
            // 
            this.textBox_campID.Location = new System.Drawing.Point(73, 53);
            this.textBox_campID.Name = "textBox_campID";
            this.textBox_campID.ReadOnly = true;
            this.textBox_campID.Size = new System.Drawing.Size(121, 21);
            this.textBox_campID.TabIndex = 4;
            // 
            // label113
            // 
            this.label113.AutoSize = true;
            this.label113.Location = new System.Drawing.Point(10, 85);
            this.label113.Name = "label113";
            this.label113.Size = new System.Drawing.Size(59, 12);
            this.label113.TabIndex = 5;
            this.label113.Text = "阵营名称:";
            // 
            // button_selectCamp
            // 
            this.button_selectCamp.Location = new System.Drawing.Point(61, 20);
            this.button_selectCamp.Name = "button_selectCamp";
            this.button_selectCamp.Size = new System.Drawing.Size(75, 23);
            this.button_selectCamp.TabIndex = 0;
            this.button_selectCamp.Text = "选择阵营";
            this.button_selectCamp.UseVisualStyleBackColor = true;
            this.button_selectCamp.Click += new System.EventHandler(this.button_selectCamp_Click);
            // 
            // label114
            // 
            this.label114.AutoSize = true;
            this.label114.Location = new System.Drawing.Point(23, 56);
            this.label114.Name = "label114";
            this.label114.Size = new System.Drawing.Size(47, 12);
            this.label114.TabIndex = 4;
            this.label114.Text = "阵营ID:";
            // 
            // groupBox47
            // 
            this.groupBox47.Controls.Add(this.textBox_roleProp);
            this.groupBox47.Controls.Add(this.comboBox_roleProp);
            this.groupBox47.Controls.Add(this.label112);
            this.groupBox47.Controls.Add(this.label111);
            this.groupBox47.Location = new System.Drawing.Point(14, 20);
            this.groupBox47.Name = "groupBox47";
            this.groupBox47.Size = new System.Drawing.Size(200, 107);
            this.groupBox47.TabIndex = 0;
            this.groupBox47.TabStop = false;
            this.groupBox47.Text = "选择属性";
            // 
            // textBox_roleProp
            // 
            this.textBox_roleProp.Location = new System.Drawing.Point(73, 51);
            this.textBox_roleProp.Name = "textBox_roleProp";
            this.textBox_roleProp.Size = new System.Drawing.Size(121, 21);
            this.textBox_roleProp.TabIndex = 3;
            // 
            // comboBox_roleProp
            // 
            this.comboBox_roleProp.FormattingEnabled = true;
            this.comboBox_roleProp.Location = new System.Drawing.Point(73, 22);
            this.comboBox_roleProp.Name = "comboBox_roleProp";
            this.comboBox_roleProp.Size = new System.Drawing.Size(121, 20);
            this.comboBox_roleProp.TabIndex = 2;
            // 
            // label112
            // 
            this.label112.AutoSize = true;
            this.label112.Location = new System.Drawing.Point(13, 56);
            this.label112.Name = "label112";
            this.label112.Size = new System.Drawing.Size(59, 12);
            this.label112.TabIndex = 1;
            this.label112.Text = "数值要求:";
            // 
            // label111
            // 
            this.label111.AutoSize = true;
            this.label111.Location = new System.Drawing.Point(13, 27);
            this.label111.Name = "label111";
            this.label111.Size = new System.Drawing.Size(59, 12);
            this.label111.TabIndex = 0;
            this.label111.Text = "角色属性:";
            // 
            // tabPageCollect
            // 
            this.tabPageCollect.Controls.Add(this.groupBox60);
            this.tabPageCollect.Controls.Add(this.groupBox15);
            this.tabPageCollect.Location = new System.Drawing.Point(4, 22);
            this.tabPageCollect.Name = "tabPageCollect";
            this.tabPageCollect.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageCollect.Size = new System.Drawing.Size(1090, 544);
            this.tabPageCollect.TabIndex = 2;
            this.tabPageCollect.Text = "收集";
            this.tabPageCollect.UseVisualStyleBackColor = true;
            // 
            // groupBox60
            // 
            this.groupBox60.Controls.Add(this.button1);
            this.groupBox60.Controls.Add(this.label147);
            this.groupBox60.Controls.Add(this.txtItemParam);
            this.groupBox60.Controls.Add(this.label146);
            this.groupBox60.Controls.Add(this.txtMonsterName);
            this.groupBox60.Controls.Add(this.label142);
            this.groupBox60.Controls.Add(this.txtItemName);
            this.groupBox60.Controls.Add(this.label141);
            this.groupBox60.Controls.Add(this.txtItemCount);
            this.groupBox60.Controls.Add(this.label140);
            this.groupBox60.Controls.Add(this.dgvKillMonsterItem);
            this.groupBox60.Controls.Add(this.btnCollectItemDel);
            this.groupBox60.Controls.Add(this.btnCollectItemAdd);
            this.groupBox60.Controls.Add(this.txtItemID);
            this.groupBox60.Controls.Add(this.txtCollectMonsterID);
            this.groupBox60.Controls.Add(this.label136);
            this.groupBox60.Controls.Add(this.label137);
            this.groupBox60.Controls.Add(this.label138);
            this.groupBox60.Controls.Add(this.CollectMonster);
            this.groupBox60.Controls.Add(this.label139);
            this.groupBox60.Location = new System.Drawing.Point(35, 194);
            this.groupBox60.Name = "groupBox60";
            this.groupBox60.Size = new System.Drawing.Size(746, 302);
            this.groupBox60.TabIndex = 1;
            this.groupBox60.TabStop = false;
            this.groupBox60.Text = "击杀取物";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(98, 110);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 16;
            this.button1.Text = "Select";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label147
            // 
            this.label147.AutoSize = true;
            this.label147.Location = new System.Drawing.Point(28, 118);
            this.label147.Name = "label147";
            this.label147.Size = new System.Drawing.Size(53, 12);
            this.label147.TabIndex = 15;
            this.label147.Text = "道具选择";
            // 
            // txtItemParam
            // 
            this.txtItemParam.Location = new System.Drawing.Point(100, 246);
            this.txtItemParam.Name = "txtItemParam";
            this.txtItemParam.Size = new System.Drawing.Size(94, 21);
            this.txtItemParam.TabIndex = 14;
            // 
            // label146
            // 
            this.label146.AutoSize = true;
            this.label146.Location = new System.Drawing.Point(45, 251);
            this.label146.Name = "label146";
            this.label146.Size = new System.Drawing.Size(29, 12);
            this.label146.TabIndex = 13;
            this.label146.Text = "参数";
            // 
            // txtMonsterName
            // 
            this.txtMonsterName.Location = new System.Drawing.Point(98, 82);
            this.txtMonsterName.Name = "txtMonsterName";
            this.txtMonsterName.Size = new System.Drawing.Size(94, 21);
            this.txtMonsterName.TabIndex = 12;
            // 
            // label142
            // 
            this.label142.AutoSize = true;
            this.label142.Location = new System.Drawing.Point(27, 85);
            this.label142.Name = "label142";
            this.label142.Size = new System.Drawing.Size(53, 12);
            this.label142.TabIndex = 11;
            this.label142.Text = "怪物名称";
            // 
            // txtItemName
            // 
            this.txtItemName.Location = new System.Drawing.Point(99, 174);
            this.txtItemName.Name = "txtItemName";
            this.txtItemName.Size = new System.Drawing.Size(94, 21);
            this.txtItemName.TabIndex = 10;
            // 
            // label141
            // 
            this.label141.AutoSize = true;
            this.label141.Location = new System.Drawing.Point(27, 179);
            this.label141.Name = "label141";
            this.label141.Size = new System.Drawing.Size(53, 12);
            this.label141.TabIndex = 9;
            this.label141.Text = "道具名称";
            // 
            // txtItemCount
            // 
            this.txtItemCount.Location = new System.Drawing.Point(100, 210);
            this.txtItemCount.Name = "txtItemCount";
            this.txtItemCount.Size = new System.Drawing.Size(94, 21);
            this.txtItemCount.TabIndex = 8;
            // 
            // label140
            // 
            this.label140.AutoSize = true;
            this.label140.Location = new System.Drawing.Point(28, 214);
            this.label140.Name = "label140";
            this.label140.Size = new System.Drawing.Size(53, 12);
            this.label140.TabIndex = 7;
            this.label140.Text = "收集数量";
            // 
            // dgvKillMonsterItem
            // 
            this.dgvKillMonsterItem.AllowUserToAddRows = false;
            this.dgvKillMonsterItem.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dgvKillMonsterItem.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvKillMonsterItem.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn34,
            this.monster,
            this.dataGridViewTextBoxColumn35,
            this.Column2,
            this.dataGridViewTextBoxColumn36,
            this.dataGridItemParam});
            this.dgvKillMonsterItem.Location = new System.Drawing.Point(217, 14);
            this.dgvKillMonsterItem.Name = "dgvKillMonsterItem";
            this.dgvKillMonsterItem.RowHeadersVisible = false;
            this.dgvKillMonsterItem.RowTemplate.Height = 23;
            this.dgvKillMonsterItem.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvKillMonsterItem.Size = new System.Drawing.Size(488, 228);
            this.dgvKillMonsterItem.TabIndex = 6;
            // 
            // dataGridViewTextBoxColumn34
            // 
            this.dataGridViewTextBoxColumn34.HeaderText = "怪物ID";
            this.dataGridViewTextBoxColumn34.Name = "dataGridViewTextBoxColumn34";
            this.dataGridViewTextBoxColumn34.Width = 66;
            // 
            // monster
            // 
            this.monster.HeaderText = "怪物名称";
            this.monster.Name = "monster";
            this.monster.Width = 78;
            // 
            // dataGridViewTextBoxColumn35
            // 
            this.dataGridViewTextBoxColumn35.HeaderText = "道具ID";
            this.dataGridViewTextBoxColumn35.Name = "dataGridViewTextBoxColumn35";
            this.dataGridViewTextBoxColumn35.Width = 66;
            // 
            // Column2
            // 
            this.Column2.HeaderText = "道具名称";
            this.Column2.Name = "Column2";
            this.Column2.Width = 78;
            // 
            // dataGridViewTextBoxColumn36
            // 
            this.dataGridViewTextBoxColumn36.HeaderText = "搜集数量";
            this.dataGridViewTextBoxColumn36.Name = "dataGridViewTextBoxColumn36";
            this.dataGridViewTextBoxColumn36.Width = 78;
            // 
            // dataGridItemParam
            // 
            this.dataGridItemParam.HeaderText = "参数";
            this.dataGridItemParam.Name = "dataGridItemParam";
            this.dataGridItemParam.Width = 54;
            // 
            // btnCollectItemDel
            // 
            this.btnCollectItemDel.Location = new System.Drawing.Point(118, 273);
            this.btnCollectItemDel.Name = "btnCollectItemDel";
            this.btnCollectItemDel.Size = new System.Drawing.Size(75, 23);
            this.btnCollectItemDel.TabIndex = 5;
            this.btnCollectItemDel.Text = "删除";
            this.btnCollectItemDel.UseVisualStyleBackColor = true;
            this.btnCollectItemDel.Click += new System.EventHandler(this.btnCollectItemDel_Click);
            // 
            // btnCollectItemAdd
            // 
            this.btnCollectItemAdd.Location = new System.Drawing.Point(23, 273);
            this.btnCollectItemAdd.Name = "btnCollectItemAdd";
            this.btnCollectItemAdd.Size = new System.Drawing.Size(75, 23);
            this.btnCollectItemAdd.TabIndex = 4;
            this.btnCollectItemAdd.Text = "添加";
            this.btnCollectItemAdd.UseVisualStyleBackColor = true;
            this.btnCollectItemAdd.Click += new System.EventHandler(this.btnCollectItemAdd_Click);
            // 
            // txtItemID
            // 
            this.txtItemID.Location = new System.Drawing.Point(99, 141);
            this.txtItemID.Name = "txtItemID";
            this.txtItemID.Size = new System.Drawing.Size(94, 21);
            this.txtItemID.TabIndex = 3;
            // 
            // txtCollectMonsterID
            // 
            this.txtCollectMonsterID.Location = new System.Drawing.Point(98, 47);
            this.txtCollectMonsterID.Name = "txtCollectMonsterID";
            this.txtCollectMonsterID.Size = new System.Drawing.Size(94, 21);
            this.txtCollectMonsterID.TabIndex = 3;
            // 
            // label136
            // 
            this.label136.AutoSize = true;
            this.label136.Location = new System.Drawing.Point(27, 146);
            this.label136.Name = "label136";
            this.label136.Size = new System.Drawing.Size(41, 12);
            this.label136.TabIndex = 2;
            this.label136.Text = "道具ID";
            // 
            // label137
            // 
            this.label137.AutoSize = true;
            this.label137.Location = new System.Drawing.Point(39, 50);
            this.label137.Name = "label137";
            this.label137.Size = new System.Drawing.Size(41, 12);
            this.label137.TabIndex = 2;
            this.label137.Text = "怪物ID";
            // 
            // label138
            // 
            this.label138.AutoSize = true;
            this.label138.Location = new System.Drawing.Point(27, 114);
            this.label138.Name = "label138";
            this.label138.Size = new System.Drawing.Size(0, 12);
            this.label138.TabIndex = 2;
            // 
            // CollectMonster
            // 
            this.CollectMonster.Location = new System.Drawing.Point(100, 11);
            this.CollectMonster.Name = "CollectMonster";
            this.CollectMonster.Size = new System.Drawing.Size(75, 23);
            this.CollectMonster.TabIndex = 1;
            this.CollectMonster.Text = "Select";
            this.CollectMonster.UseVisualStyleBackColor = true;
            this.CollectMonster.Click += new System.EventHandler(this.CollectMonster_Click);
            // 
            // label139
            // 
            this.label139.AutoSize = true;
            this.label139.Location = new System.Drawing.Point(27, 19);
            this.label139.Name = "label139";
            this.label139.Size = new System.Drawing.Size(53, 12);
            this.label139.TabIndex = 0;
            this.label139.Text = "怪物选择";
            // 
            // groupBox15
            // 
            this.groupBox15.Controls.Add(this.dataGridViewCollectItem);
            this.groupBox15.Controls.Add(this.buttonCollectItemDel);
            this.groupBox15.Controls.Add(this.buttonCollectItemAdd);
            this.groupBox15.Controls.Add(this.textBoxCollectItemCount);
            this.groupBox15.Controls.Add(this.textBoxCollectItemID);
            this.groupBox15.Controls.Add(this.textBoxCollectItemName);
            this.groupBox15.Controls.Add(this.label22);
            this.groupBox15.Controls.Add(this.label41);
            this.groupBox15.Controls.Add(this.label21);
            this.groupBox15.Controls.Add(this.buttonCollectItem);
            this.groupBox15.Controls.Add(this.label20);
            this.groupBox15.Location = new System.Drawing.Point(35, 15);
            this.groupBox15.Name = "groupBox15";
            this.groupBox15.Size = new System.Drawing.Size(504, 175);
            this.groupBox15.TabIndex = 0;
            this.groupBox15.TabStop = false;
            this.groupBox15.Text = "收集";
            // 
            // dataGridViewCollectItem
            // 
            this.dataGridViewCollectItem.AllowUserToAddRows = false;
            this.dataGridViewCollectItem.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewCollectItem.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewCollectItem.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.CollectItemID,
            this.CollectItemName,
            this.CollectItemCount});
            this.dataGridViewCollectItem.Location = new System.Drawing.Point(217, 16);
            this.dataGridViewCollectItem.Name = "dataGridViewCollectItem";
            this.dataGridViewCollectItem.RowHeadersVisible = false;
            this.dataGridViewCollectItem.RowTemplate.Height = 23;
            this.dataGridViewCollectItem.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewCollectItem.Size = new System.Drawing.Size(230, 150);
            this.dataGridViewCollectItem.TabIndex = 6;
            // 
            // CollectItemID
            // 
            this.CollectItemID.HeaderText = "道具ID";
            this.CollectItemID.Name = "CollectItemID";
            this.CollectItemID.Width = 66;
            // 
            // CollectItemName
            // 
            this.CollectItemName.HeaderText = "道具名称";
            this.CollectItemName.Name = "CollectItemName";
            this.CollectItemName.Width = 78;
            // 
            // CollectItemCount
            // 
            this.CollectItemCount.HeaderText = "搜集数量";
            this.CollectItemCount.Name = "CollectItemCount";
            this.CollectItemCount.Width = 78;
            // 
            // buttonCollectItemDel
            // 
            this.buttonCollectItemDel.Location = new System.Drawing.Point(107, 136);
            this.buttonCollectItemDel.Name = "buttonCollectItemDel";
            this.buttonCollectItemDel.Size = new System.Drawing.Size(75, 23);
            this.buttonCollectItemDel.TabIndex = 5;
            this.buttonCollectItemDel.Text = "删除";
            this.buttonCollectItemDel.UseVisualStyleBackColor = true;
            this.buttonCollectItemDel.Click += new System.EventHandler(this.buttonCollectItemDel_Click);
            // 
            // buttonCollectItemAdd
            // 
            this.buttonCollectItemAdd.Location = new System.Drawing.Point(22, 135);
            this.buttonCollectItemAdd.Name = "buttonCollectItemAdd";
            this.buttonCollectItemAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonCollectItemAdd.TabIndex = 4;
            this.buttonCollectItemAdd.Text = "添加";
            this.buttonCollectItemAdd.UseVisualStyleBackColor = true;
            this.buttonCollectItemAdd.Click += new System.EventHandler(this.buttonCollectItemAdd_Click);
            // 
            // textBoxCollectItemCount
            // 
            this.textBoxCollectItemCount.Location = new System.Drawing.Point(102, 109);
            this.textBoxCollectItemCount.Name = "textBoxCollectItemCount";
            this.textBoxCollectItemCount.Size = new System.Drawing.Size(94, 21);
            this.textBoxCollectItemCount.TabIndex = 3;
            // 
            // textBoxCollectItemID
            // 
            this.textBoxCollectItemID.Location = new System.Drawing.Point(102, 47);
            this.textBoxCollectItemID.Name = "textBoxCollectItemID";
            this.textBoxCollectItemID.Size = new System.Drawing.Size(94, 21);
            this.textBoxCollectItemID.TabIndex = 3;
            // 
            // textBoxCollectItemName
            // 
            this.textBoxCollectItemName.Location = new System.Drawing.Point(102, 78);
            this.textBoxCollectItemName.Name = "textBoxCollectItemName";
            this.textBoxCollectItemName.Size = new System.Drawing.Size(94, 21);
            this.textBoxCollectItemName.TabIndex = 3;
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(32, 113);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(53, 12);
            this.label22.TabIndex = 2;
            this.label22.Text = "收集数量";
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Location = new System.Drawing.Point(39, 53);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(41, 12);
            this.label41.TabIndex = 2;
            this.label41.Text = "道具ID";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(32, 81);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(53, 12);
            this.label21.TabIndex = 2;
            this.label21.Text = "道具名称";
            // 
            // buttonCollectItem
            // 
            this.buttonCollectItem.Location = new System.Drawing.Point(102, 16);
            this.buttonCollectItem.Name = "buttonCollectItem";
            this.buttonCollectItem.Size = new System.Drawing.Size(75, 23);
            this.buttonCollectItem.TabIndex = 1;
            this.buttonCollectItem.Text = "Select";
            this.buttonCollectItem.UseVisualStyleBackColor = true;
            this.buttonCollectItem.Click += new System.EventHandler(this.buttonCollectItem_Click);
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(28, 21);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(53, 12);
            this.label20.TabIndex = 0;
            this.label20.Text = "道具选择";
            // 
            // tabPageGather
            // 
            this.tabPageGather.Controls.Add(this.groupBox45);
            this.tabPageGather.Location = new System.Drawing.Point(4, 22);
            this.tabPageGather.Name = "tabPageGather";
            this.tabPageGather.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGather.Size = new System.Drawing.Size(1090, 544);
            this.tabPageGather.TabIndex = 7;
            this.tabPageGather.Text = "采集";
            this.tabPageGather.UseVisualStyleBackColor = true;
            // 
            // groupBox45
            // 
            this.groupBox45.Controls.Add(this.textBoxGatherParam);
            this.groupBox45.Controls.Add(this.label148);
            this.groupBox45.Controls.Add(this.dataGridViewGather);
            this.groupBox45.Controls.Add(this.textBoxGatherCount);
            this.groupBox45.Controls.Add(this.textBoxGatherID);
            this.groupBox45.Controls.Add(this.buttonDelGather);
            this.groupBox45.Controls.Add(this.label132);
            this.groupBox45.Controls.Add(this.buttonAddGather);
            this.groupBox45.Controls.Add(this.label131);
            this.groupBox45.Controls.Add(this.buttonSelectGather);
            this.groupBox45.Controls.Add(this.label130);
            this.groupBox45.Location = new System.Drawing.Point(77, 45);
            this.groupBox45.Name = "groupBox45";
            this.groupBox45.Size = new System.Drawing.Size(445, 191);
            this.groupBox45.TabIndex = 0;
            this.groupBox45.TabStop = false;
            this.groupBox45.Text = "采集";
            // 
            // textBoxGatherParam
            // 
            this.textBoxGatherParam.Location = new System.Drawing.Point(96, 135);
            this.textBoxGatherParam.Name = "textBoxGatherParam";
            this.textBoxGatherParam.Size = new System.Drawing.Size(100, 21);
            this.textBoxGatherParam.TabIndex = 7;
            // 
            // label148
            // 
            this.label148.AutoSize = true;
            this.label148.Location = new System.Drawing.Point(53, 137);
            this.label148.Name = "label148";
            this.label148.Size = new System.Drawing.Size(29, 12);
            this.label148.TabIndex = 6;
            this.label148.Text = "参数";
            // 
            // dataGridViewGather
            // 
            this.dataGridViewGather.AllowUserToAddRows = false;
            this.dataGridViewGather.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewGather.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewGather.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.GatherID,
            this.GatherCount,
            this.GatherParam});
            this.dataGridViewGather.Location = new System.Drawing.Point(230, 32);
            this.dataGridViewGather.MultiSelect = false;
            this.dataGridViewGather.Name = "dataGridViewGather";
            this.dataGridViewGather.RowHeadersVisible = false;
            this.dataGridViewGather.RowTemplate.Height = 23;
            this.dataGridViewGather.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewGather.Size = new System.Drawing.Size(203, 131);
            this.dataGridViewGather.TabIndex = 5;
            // 
            // GatherID
            // 
            this.GatherID.HeaderText = "采集ID";
            this.GatherID.Name = "GatherID";
            this.GatherID.Width = 66;
            // 
            // GatherCount
            // 
            this.GatherCount.HeaderText = "采集数量";
            this.GatherCount.Name = "GatherCount";
            this.GatherCount.Width = 78;
            // 
            // GatherParam
            // 
            this.GatherParam.HeaderText = "参数";
            this.GatherParam.Name = "GatherParam";
            this.GatherParam.Width = 54;
            // 
            // textBoxGatherCount
            // 
            this.textBoxGatherCount.Location = new System.Drawing.Point(97, 105);
            this.textBoxGatherCount.Name = "textBoxGatherCount";
            this.textBoxGatherCount.Size = new System.Drawing.Size(100, 21);
            this.textBoxGatherCount.TabIndex = 4;
            // 
            // textBoxGatherID
            // 
            this.textBoxGatherID.Location = new System.Drawing.Point(97, 70);
            this.textBoxGatherID.Name = "textBoxGatherID";
            this.textBoxGatherID.Size = new System.Drawing.Size(100, 21);
            this.textBoxGatherID.TabIndex = 4;
            // 
            // buttonDelGather
            // 
            this.buttonDelGather.Location = new System.Drawing.Point(122, 162);
            this.buttonDelGather.Name = "buttonDelGather";
            this.buttonDelGather.Size = new System.Drawing.Size(75, 23);
            this.buttonDelGather.TabIndex = 3;
            this.buttonDelGather.Text = "删除";
            this.buttonDelGather.UseVisualStyleBackColor = true;
            this.buttonDelGather.Click += new System.EventHandler(this.buttonDelGather_Click);
            // 
            // label132
            // 
            this.label132.AutoSize = true;
            this.label132.Location = new System.Drawing.Point(30, 109);
            this.label132.Name = "label132";
            this.label132.Size = new System.Drawing.Size(53, 12);
            this.label132.TabIndex = 2;
            this.label132.Text = "采集数量";
            // 
            // buttonAddGather
            // 
            this.buttonAddGather.Location = new System.Drawing.Point(29, 162);
            this.buttonAddGather.Name = "buttonAddGather";
            this.buttonAddGather.Size = new System.Drawing.Size(75, 23);
            this.buttonAddGather.TabIndex = 3;
            this.buttonAddGather.Text = "添加";
            this.buttonAddGather.UseVisualStyleBackColor = true;
            this.buttonAddGather.Click += new System.EventHandler(this.buttonAddGather_Click);
            // 
            // label131
            // 
            this.label131.AutoSize = true;
            this.label131.Location = new System.Drawing.Point(30, 74);
            this.label131.Name = "label131";
            this.label131.Size = new System.Drawing.Size(41, 12);
            this.label131.TabIndex = 2;
            this.label131.Text = "采集ID";
            // 
            // buttonSelectGather
            // 
            this.buttonSelectGather.Location = new System.Drawing.Point(96, 33);
            this.buttonSelectGather.Name = "buttonSelectGather";
            this.buttonSelectGather.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectGather.TabIndex = 1;
            this.buttonSelectGather.Text = "Select";
            this.buttonSelectGather.UseVisualStyleBackColor = true;
            this.buttonSelectGather.Click += new System.EventHandler(this.buttonSelectGather_Click);
            // 
            // label130
            // 
            this.label130.AutoSize = true;
            this.label130.Location = new System.Drawing.Point(27, 40);
            this.label130.Name = "label130";
            this.label130.Size = new System.Drawing.Size(53, 12);
            this.label130.TabIndex = 0;
            this.label130.Text = "采集选择";
            // 
            // tabPageProbe
            // 
            this.tabPageProbe.Controls.Add(this.groupBox32);
            this.tabPageProbe.Location = new System.Drawing.Point(4, 22);
            this.tabPageProbe.Name = "tabPageProbe";
            this.tabPageProbe.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageProbe.Size = new System.Drawing.Size(1090, 544);
            this.tabPageProbe.TabIndex = 3;
            this.tabPageProbe.Text = "探索";
            this.tabPageProbe.UseVisualStyleBackColor = true;
            // 
            // groupBox32
            // 
            this.groupBox32.Controls.Add(this.textBoxProbeParam);
            this.groupBox32.Controls.Add(this.label149);
            this.groupBox32.Controls.Add(this.groupBox62);
            this.groupBox32.Controls.Add(this.dataGridViewProbe);
            this.groupBox32.Controls.Add(this.buttonDelProbe);
            this.groupBox32.Controls.Add(this.buttonAddProbe);
            this.groupBox32.Controls.Add(this.buttonSelectProbe);
            this.groupBox32.Controls.Add(this.textBoxProbeZ2);
            this.groupBox32.Controls.Add(this.textBoxProbeX2);
            this.groupBox32.Controls.Add(this.textBoxProbeZ1);
            this.groupBox32.Controls.Add(this.textBoxProbeX1);
            this.groupBox32.Controls.Add(this.textBoxProbeMapName);
            this.groupBox32.Controls.Add(this.textBoxProbeMapID);
            this.groupBox32.Controls.Add(this.label73);
            this.groupBox32.Controls.Add(this.label72);
            this.groupBox32.Controls.Add(this.label71);
            this.groupBox32.Controls.Add(this.label70);
            this.groupBox32.Controls.Add(this.label69);
            this.groupBox32.Controls.Add(this.label68);
            this.groupBox32.Controls.Add(this.label67);
            this.groupBox32.Location = new System.Drawing.Point(34, 34);
            this.groupBox32.Name = "groupBox32";
            this.groupBox32.Size = new System.Drawing.Size(691, 341);
            this.groupBox32.TabIndex = 0;
            this.groupBox32.TabStop = false;
            this.groupBox32.Text = "探索";
            // 
            // textBoxProbeParam
            // 
            this.textBoxProbeParam.Location = new System.Drawing.Point(100, 275);
            this.textBoxProbeParam.Name = "textBoxProbeParam";
            this.textBoxProbeParam.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeParam.TabIndex = 8;
            // 
            // label149
            // 
            this.label149.AutoSize = true;
            this.label149.Location = new System.Drawing.Point(39, 278);
            this.label149.Name = "label149";
            this.label149.Size = new System.Drawing.Size(29, 12);
            this.label149.TabIndex = 7;
            this.label149.Text = "参数";
            // 
            // groupBox62
            // 
            this.groupBox62.Controls.Add(this.radioButton2);
            this.groupBox62.Controls.Add(this.radioButton1);
            this.groupBox62.Location = new System.Drawing.Point(255, 23);
            this.groupBox62.Name = "groupBox62";
            this.groupBox62.Size = new System.Drawing.Size(187, 39);
            this.groupBox62.TabIndex = 6;
            this.groupBox62.TabStop = false;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(100, 14);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(71, 16);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.Text = "探索其一";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(6, 14);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(71, 16);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "探索全部";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // dataGridViewProbe
            // 
            this.dataGridViewProbe.AllowUserToAddRows = false;
            this.dataGridViewProbe.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewProbe.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewProbe.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.MapID,
            this.MapName,
            this.CoordinateX1,
            this.CoordinateZ1,
            this.CoordinateX2,
            this.CoordinateZ2,
            this.CoordinateParam});
            this.dataGridViewProbe.Location = new System.Drawing.Point(217, 80);
            this.dataGridViewProbe.MultiSelect = false;
            this.dataGridViewProbe.Name = "dataGridViewProbe";
            this.dataGridViewProbe.RowHeadersVisible = false;
            this.dataGridViewProbe.RowTemplate.Height = 23;
            this.dataGridViewProbe.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewProbe.Size = new System.Drawing.Size(468, 189);
            this.dataGridViewProbe.TabIndex = 5;
            // 
            // MapID
            // 
            this.MapID.HeaderText = "地图ID";
            this.MapID.Name = "MapID";
            this.MapID.Width = 66;
            // 
            // MapName
            // 
            this.MapName.HeaderText = "地图名称";
            this.MapName.Name = "MapName";
            this.MapName.Width = 78;
            // 
            // CoordinateX1
            // 
            this.CoordinateX1.HeaderText = "X1坐标";
            this.CoordinateX1.Name = "CoordinateX1";
            this.CoordinateX1.Width = 66;
            // 
            // CoordinateZ1
            // 
            this.CoordinateZ1.HeaderText = "Z1坐标";
            this.CoordinateZ1.Name = "CoordinateZ1";
            this.CoordinateZ1.Width = 66;
            // 
            // CoordinateX2
            // 
            this.CoordinateX2.HeaderText = "X2坐标";
            this.CoordinateX2.Name = "CoordinateX2";
            this.CoordinateX2.Width = 66;
            // 
            // CoordinateZ2
            // 
            this.CoordinateZ2.HeaderText = "Z2坐标";
            this.CoordinateZ2.Name = "CoordinateZ2";
            this.CoordinateZ2.Width = 66;
            // 
            // CoordinateParam
            // 
            this.CoordinateParam.HeaderText = "参数";
            this.CoordinateParam.Name = "CoordinateParam";
            this.CoordinateParam.Width = 54;
            // 
            // buttonDelProbe
            // 
            this.buttonDelProbe.Location = new System.Drawing.Point(129, 305);
            this.buttonDelProbe.Name = "buttonDelProbe";
            this.buttonDelProbe.Size = new System.Drawing.Size(75, 23);
            this.buttonDelProbe.TabIndex = 4;
            this.buttonDelProbe.Text = "删除";
            this.buttonDelProbe.UseVisualStyleBackColor = true;
            this.buttonDelProbe.Click += new System.EventHandler(this.buttonDelProbe_Click);
            // 
            // buttonAddProbe
            // 
            this.buttonAddProbe.Location = new System.Drawing.Point(33, 305);
            this.buttonAddProbe.Name = "buttonAddProbe";
            this.buttonAddProbe.Size = new System.Drawing.Size(75, 23);
            this.buttonAddProbe.TabIndex = 3;
            this.buttonAddProbe.Text = "添加";
            this.buttonAddProbe.UseVisualStyleBackColor = true;
            this.buttonAddProbe.Click += new System.EventHandler(this.buttonAddProbe_Click);
            // 
            // buttonSelectProbe
            // 
            this.buttonSelectProbe.Location = new System.Drawing.Point(103, 36);
            this.buttonSelectProbe.Name = "buttonSelectProbe";
            this.buttonSelectProbe.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectProbe.TabIndex = 2;
            this.buttonSelectProbe.Text = "Select";
            this.buttonSelectProbe.UseVisualStyleBackColor = true;
            this.buttonSelectProbe.Click += new System.EventHandler(this.buttonSelectProbe_Click);
            // 
            // textBoxProbeZ2
            // 
            this.textBoxProbeZ2.Location = new System.Drawing.Point(100, 246);
            this.textBoxProbeZ2.Name = "textBoxProbeZ2";
            this.textBoxProbeZ2.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeZ2.TabIndex = 1;
            // 
            // textBoxProbeX2
            // 
            this.textBoxProbeX2.Location = new System.Drawing.Point(100, 212);
            this.textBoxProbeX2.Name = "textBoxProbeX2";
            this.textBoxProbeX2.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeX2.TabIndex = 1;
            // 
            // textBoxProbeZ1
            // 
            this.textBoxProbeZ1.Location = new System.Drawing.Point(100, 178);
            this.textBoxProbeZ1.Name = "textBoxProbeZ1";
            this.textBoxProbeZ1.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeZ1.TabIndex = 1;
            // 
            // textBoxProbeX1
            // 
            this.textBoxProbeX1.Location = new System.Drawing.Point(100, 144);
            this.textBoxProbeX1.Name = "textBoxProbeX1";
            this.textBoxProbeX1.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeX1.TabIndex = 1;
            // 
            // textBoxProbeMapName
            // 
            this.textBoxProbeMapName.Location = new System.Drawing.Point(100, 110);
            this.textBoxProbeMapName.Name = "textBoxProbeMapName";
            this.textBoxProbeMapName.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeMapName.TabIndex = 1;
            // 
            // textBoxProbeMapID
            // 
            this.textBoxProbeMapID.Location = new System.Drawing.Point(100, 76);
            this.textBoxProbeMapID.Name = "textBoxProbeMapID";
            this.textBoxProbeMapID.Size = new System.Drawing.Size(87, 21);
            this.textBoxProbeMapID.TabIndex = 1;
            // 
            // label73
            // 
            this.label73.AutoSize = true;
            this.label73.Location = new System.Drawing.Point(31, 250);
            this.label73.Name = "label73";
            this.label73.Size = new System.Drawing.Size(41, 12);
            this.label73.TabIndex = 0;
            this.label73.Text = "Z2坐标";
            // 
            // label72
            // 
            this.label72.AutoSize = true;
            this.label72.Location = new System.Drawing.Point(31, 216);
            this.label72.Name = "label72";
            this.label72.Size = new System.Drawing.Size(41, 12);
            this.label72.TabIndex = 0;
            this.label72.Text = "X2坐标";
            // 
            // label71
            // 
            this.label71.AutoSize = true;
            this.label71.Location = new System.Drawing.Point(31, 182);
            this.label71.Name = "label71";
            this.label71.Size = new System.Drawing.Size(41, 12);
            this.label71.TabIndex = 0;
            this.label71.Text = "Z1坐标";
            // 
            // label70
            // 
            this.label70.AutoSize = true;
            this.label70.Location = new System.Drawing.Point(31, 148);
            this.label70.Name = "label70";
            this.label70.Size = new System.Drawing.Size(41, 12);
            this.label70.TabIndex = 0;
            this.label70.Text = "X1坐标";
            // 
            // label69
            // 
            this.label69.AutoSize = true;
            this.label69.Location = new System.Drawing.Point(31, 114);
            this.label69.Name = "label69";
            this.label69.Size = new System.Drawing.Size(53, 12);
            this.label69.TabIndex = 0;
            this.label69.Text = "地图名称";
            // 
            // label68
            // 
            this.label68.AutoSize = true;
            this.label68.Location = new System.Drawing.Point(31, 80);
            this.label68.Name = "label68";
            this.label68.Size = new System.Drawing.Size(41, 12);
            this.label68.TabIndex = 0;
            this.label68.Text = "地图ID";
            // 
            // label67
            // 
            this.label67.AutoSize = true;
            this.label67.Location = new System.Drawing.Point(31, 41);
            this.label67.Name = "label67";
            this.label67.Size = new System.Drawing.Size(53, 12);
            this.label67.TabIndex = 0;
            this.label67.Text = "区域选择";
            // 
            // tabPageBehave
            // 
            this.tabPageBehave.Controls.Add(this.dataGridView_behave);
            this.tabPageBehave.Controls.Add(this.button_behaveRemove);
            this.tabPageBehave.Controls.Add(this.button_behaveAdd);
            this.tabPageBehave.Controls.Add(this.groupBox50);
            this.tabPageBehave.Location = new System.Drawing.Point(4, 22);
            this.tabPageBehave.Name = "tabPageBehave";
            this.tabPageBehave.Size = new System.Drawing.Size(1090, 544);
            this.tabPageBehave.TabIndex = 9;
            this.tabPageBehave.Text = "行为";
            this.tabPageBehave.UseVisualStyleBackColor = true;
            // 
            // dataGridView_behave
            // 
            this.dataGridView_behave.AllowUserToAddRows = false;
            this.dataGridView_behave.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_behave.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.roleAction,
            this.roleActionValue,
            this.roleActionParam});
            this.dataGridView_behave.Location = new System.Drawing.Point(232, 35);
            this.dataGridView_behave.Name = "dataGridView_behave";
            this.dataGridView_behave.RowHeadersVisible = false;
            this.dataGridView_behave.RowTemplate.Height = 23;
            this.dataGridView_behave.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_behave.Size = new System.Drawing.Size(381, 148);
            this.dataGridView_behave.TabIndex = 5;
            // 
            // roleAction
            // 
            this.roleAction.HeaderText = "角色行为";
            this.roleAction.Name = "roleAction";
            // 
            // roleActionValue
            // 
            this.roleActionValue.HeaderText = "次数需求";
            this.roleActionValue.Name = "roleActionValue";
            // 
            // roleActionParam
            // 
            this.roleActionParam.HeaderText = "参数";
            this.roleActionParam.Name = "roleActionParam";
            // 
            // button_behaveRemove
            // 
            this.button_behaveRemove.Location = new System.Drawing.Point(114, 152);
            this.button_behaveRemove.Name = "button_behaveRemove";
            this.button_behaveRemove.Size = new System.Drawing.Size(75, 23);
            this.button_behaveRemove.TabIndex = 7;
            this.button_behaveRemove.Text = "删除";
            this.button_behaveRemove.UseVisualStyleBackColor = true;
            this.button_behaveRemove.Click += new System.EventHandler(this.button_behaveRemove_Click);
            // 
            // button_behaveAdd
            // 
            this.button_behaveAdd.Location = new System.Drawing.Point(22, 152);
            this.button_behaveAdd.Name = "button_behaveAdd";
            this.button_behaveAdd.Size = new System.Drawing.Size(75, 23);
            this.button_behaveAdd.TabIndex = 6;
            this.button_behaveAdd.Text = "添加";
            this.button_behaveAdd.UseVisualStyleBackColor = true;
            this.button_behaveAdd.Click += new System.EventHandler(this.button_behaveAdd_Click);
            // 
            // groupBox50
            // 
            this.groupBox50.Controls.Add(this.textBox_behave_param);
            this.groupBox50.Controls.Add(this.label133);
            this.groupBox50.Controls.Add(this.textBox_behave_action);
            this.groupBox50.Controls.Add(this.comboBox_behave_action);
            this.groupBox50.Controls.Add(this.label116);
            this.groupBox50.Controls.Add(this.label117);
            this.groupBox50.Location = new System.Drawing.Point(14, 28);
            this.groupBox50.Name = "groupBox50";
            this.groupBox50.Size = new System.Drawing.Size(212, 114);
            this.groupBox50.TabIndex = 1;
            this.groupBox50.TabStop = false;
            this.groupBox50.Text = "功能选择";
            // 
            // textBox_behave_param
            // 
            this.textBox_behave_param.Location = new System.Drawing.Point(47, 82);
            this.textBox_behave_param.Name = "textBox_behave_param";
            this.textBox_behave_param.Size = new System.Drawing.Size(147, 21);
            this.textBox_behave_param.TabIndex = 5;
            // 
            // label133
            // 
            this.label133.AutoSize = true;
            this.label133.Location = new System.Drawing.Point(13, 85);
            this.label133.Name = "label133";
            this.label133.Size = new System.Drawing.Size(35, 12);
            this.label133.TabIndex = 4;
            this.label133.Text = "参数:";
            // 
            // textBox_behave_action
            // 
            this.textBox_behave_action.Location = new System.Drawing.Point(73, 51);
            this.textBox_behave_action.Name = "textBox_behave_action";
            this.textBox_behave_action.Size = new System.Drawing.Size(121, 21);
            this.textBox_behave_action.TabIndex = 3;
            // 
            // comboBox_behave_action
            // 
            this.comboBox_behave_action.FormattingEnabled = true;
            this.comboBox_behave_action.Location = new System.Drawing.Point(73, 22);
            this.comboBox_behave_action.Name = "comboBox_behave_action";
            this.comboBox_behave_action.Size = new System.Drawing.Size(121, 20);
            this.comboBox_behave_action.TabIndex = 2;
            // 
            // label116
            // 
            this.label116.AutoSize = true;
            this.label116.Location = new System.Drawing.Point(13, 56);
            this.label116.Name = "label116";
            this.label116.Size = new System.Drawing.Size(59, 12);
            this.label116.TabIndex = 1;
            this.label116.Text = "次数需求:";
            // 
            // label117
            // 
            this.label117.AutoSize = true;
            this.label117.Location = new System.Drawing.Point(13, 27);
            this.label117.Name = "label117";
            this.label117.Size = new System.Drawing.Size(59, 12);
            this.label117.TabIndex = 0;
            this.label117.Text = "执行功能:";
            // 
            // tabPageBuild
            // 
            this.tabPageBuild.Controls.Add(this.groupBox51);
            this.tabPageBuild.Controls.Add(this.dataGridView_build);
            this.tabPageBuild.Controls.Add(this.groupBox49);
            this.tabPageBuild.Controls.Add(this.button_tecRemove);
            this.tabPageBuild.Location = new System.Drawing.Point(4, 22);
            this.tabPageBuild.Name = "tabPageBuild";
            this.tabPageBuild.Size = new System.Drawing.Size(1090, 544);
            this.tabPageBuild.TabIndex = 10;
            this.tabPageBuild.Text = "建设";
            this.tabPageBuild.UseVisualStyleBackColor = true;
            // 
            // groupBox51
            // 
            this.groupBox51.Controls.Add(this.textBox_tecValue);
            this.groupBox51.Controls.Add(this.textBox_tecID);
            this.groupBox51.Controls.Add(this.textBox_tecName);
            this.groupBox51.Controls.Add(this.button_tecAdd);
            this.groupBox51.Controls.Add(this.label120);
            this.groupBox51.Controls.Add(this.label121);
            this.groupBox51.Controls.Add(this.button_selectTec);
            this.groupBox51.Controls.Add(this.label122);
            this.groupBox51.Location = new System.Drawing.Point(20, 232);
            this.groupBox51.Name = "groupBox51";
            this.groupBox51.Size = new System.Drawing.Size(200, 193);
            this.groupBox51.TabIndex = 7;
            this.groupBox51.TabStop = false;
            this.groupBox51.Text = "科技提升";
            // 
            // textBox_tecValue
            // 
            this.textBox_tecValue.Location = new System.Drawing.Point(90, 121);
            this.textBox_tecValue.Name = "textBox_tecValue";
            this.textBox_tecValue.Size = new System.Drawing.Size(100, 21);
            this.textBox_tecValue.TabIndex = 8;
            // 
            // textBox_tecID
            // 
            this.textBox_tecID.Location = new System.Drawing.Point(91, 92);
            this.textBox_tecID.Name = "textBox_tecID";
            this.textBox_tecID.Size = new System.Drawing.Size(100, 21);
            this.textBox_tecID.TabIndex = 7;
            // 
            // textBox_tecName
            // 
            this.textBox_tecName.Location = new System.Drawing.Point(91, 63);
            this.textBox_tecName.Name = "textBox_tecName";
            this.textBox_tecName.Size = new System.Drawing.Size(100, 21);
            this.textBox_tecName.TabIndex = 6;
            // 
            // button_tecAdd
            // 
            this.button_tecAdd.Location = new System.Drawing.Point(58, 164);
            this.button_tecAdd.Name = "button_tecAdd";
            this.button_tecAdd.Size = new System.Drawing.Size(75, 23);
            this.button_tecAdd.TabIndex = 4;
            this.button_tecAdd.Text = "添加";
            this.button_tecAdd.UseVisualStyleBackColor = true;
            this.button_tecAdd.Click += new System.EventHandler(this.button_buildAdd_Click);
            // 
            // label120
            // 
            this.label120.AutoSize = true;
            this.label120.Location = new System.Drawing.Point(19, 126);
            this.label120.Name = "label120";
            this.label120.Size = new System.Drawing.Size(65, 12);
            this.label120.TabIndex = 3;
            this.label120.Text = "等级需求：";
            // 
            // label121
            // 
            this.label121.AutoSize = true;
            this.label121.Location = new System.Drawing.Point(19, 96);
            this.label121.Name = "label121";
            this.label121.Size = new System.Drawing.Size(53, 12);
            this.label121.TabIndex = 2;
            this.label121.Text = "科技ID：";
            // 
            // button_selectTec
            // 
            this.button_selectTec.Location = new System.Drawing.Point(78, 20);
            this.button_selectTec.Name = "button_selectTec";
            this.button_selectTec.Size = new System.Drawing.Size(75, 23);
            this.button_selectTec.TabIndex = 1;
            this.button_selectTec.Text = "选择科技";
            this.button_selectTec.UseVisualStyleBackColor = true;
            this.button_selectTec.Click += new System.EventHandler(this.button_selectTec_Click);
            // 
            // label122
            // 
            this.label122.AutoSize = true;
            this.label122.Location = new System.Drawing.Point(19, 66);
            this.label122.Name = "label122";
            this.label122.Size = new System.Drawing.Size(65, 12);
            this.label122.TabIndex = 0;
            this.label122.Text = "科技名称：";
            // 
            // dataGridView_build
            // 
            this.dataGridView_build.AllowUserToAddRows = false;
            this.dataGridView_build.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_build.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.buildName,
            this.buildValue});
            this.dataGridView_build.Location = new System.Drawing.Point(245, 33);
            this.dataGridView_build.Name = "dataGridView_build";
            this.dataGridView_build.RowHeadersVisible = false;
            this.dataGridView_build.RowTemplate.Height = 23;
            this.dataGridView_build.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_build.Size = new System.Drawing.Size(307, 204);
            this.dataGridView_build.TabIndex = 6;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "ID";
            this.Column1.Name = "Column1";
            // 
            // buildName
            // 
            this.buildName.HeaderText = "建筑/科技";
            this.buildName.Name = "buildName";
            // 
            // buildValue
            // 
            this.buildValue.HeaderText = "等级需求";
            this.buildValue.Name = "buildValue";
            // 
            // groupBox49
            // 
            this.groupBox49.Controls.Add(this.textBox_buildLevel);
            this.groupBox49.Controls.Add(this.textBox_buildID);
            this.groupBox49.Controls.Add(this.textBox_buildName);
            this.groupBox49.Controls.Add(this.button_buildAdd);
            this.groupBox49.Controls.Add(this.label119);
            this.groupBox49.Controls.Add(this.label118);
            this.groupBox49.Controls.Add(this.button_selectBuild);
            this.groupBox49.Controls.Add(this.label115);
            this.groupBox49.Location = new System.Drawing.Point(20, 28);
            this.groupBox49.Name = "groupBox49";
            this.groupBox49.Size = new System.Drawing.Size(200, 193);
            this.groupBox49.TabIndex = 0;
            this.groupBox49.TabStop = false;
            this.groupBox49.Text = "主城建设";
            // 
            // textBox_buildLevel
            // 
            this.textBox_buildLevel.Location = new System.Drawing.Point(90, 121);
            this.textBox_buildLevel.Name = "textBox_buildLevel";
            this.textBox_buildLevel.Size = new System.Drawing.Size(100, 21);
            this.textBox_buildLevel.TabIndex = 8;
            // 
            // textBox_buildID
            // 
            this.textBox_buildID.Location = new System.Drawing.Point(91, 92);
            this.textBox_buildID.Name = "textBox_buildID";
            this.textBox_buildID.Size = new System.Drawing.Size(100, 21);
            this.textBox_buildID.TabIndex = 7;
            // 
            // textBox_buildName
            // 
            this.textBox_buildName.Location = new System.Drawing.Point(91, 63);
            this.textBox_buildName.Name = "textBox_buildName";
            this.textBox_buildName.Size = new System.Drawing.Size(100, 21);
            this.textBox_buildName.TabIndex = 6;
            // 
            // button_buildAdd
            // 
            this.button_buildAdd.Location = new System.Drawing.Point(58, 164);
            this.button_buildAdd.Name = "button_buildAdd";
            this.button_buildAdd.Size = new System.Drawing.Size(75, 23);
            this.button_buildAdd.TabIndex = 4;
            this.button_buildAdd.Text = "添加";
            this.button_buildAdd.UseVisualStyleBackColor = true;
            this.button_buildAdd.Click += new System.EventHandler(this.button_buildAdd_Click);
            // 
            // label119
            // 
            this.label119.AutoSize = true;
            this.label119.Location = new System.Drawing.Point(19, 126);
            this.label119.Name = "label119";
            this.label119.Size = new System.Drawing.Size(65, 12);
            this.label119.TabIndex = 3;
            this.label119.Text = "等级需求：";
            // 
            // label118
            // 
            this.label118.AutoSize = true;
            this.label118.Location = new System.Drawing.Point(19, 96);
            this.label118.Name = "label118";
            this.label118.Size = new System.Drawing.Size(53, 12);
            this.label118.TabIndex = 2;
            this.label118.Text = "建筑ID：";
            // 
            // button_selectBuild
            // 
            this.button_selectBuild.Enabled = false;
            this.button_selectBuild.Location = new System.Drawing.Point(78, 20);
            this.button_selectBuild.Name = "button_selectBuild";
            this.button_selectBuild.Size = new System.Drawing.Size(75, 23);
            this.button_selectBuild.TabIndex = 1;
            this.button_selectBuild.Text = "选择建筑";
            this.button_selectBuild.UseVisualStyleBackColor = true;
            this.button_selectBuild.Click += new System.EventHandler(this.button_selectBuild_Click);
            // 
            // label115
            // 
            this.label115.AutoSize = true;
            this.label115.Location = new System.Drawing.Point(19, 66);
            this.label115.Name = "label115";
            this.label115.Size = new System.Drawing.Size(65, 12);
            this.label115.TabIndex = 0;
            this.label115.Text = "建筑名称：";
            // 
            // button_tecRemove
            // 
            this.button_tecRemove.Location = new System.Drawing.Point(354, 254);
            this.button_tecRemove.Name = "button_tecRemove";
            this.button_tecRemove.Size = new System.Drawing.Size(75, 23);
            this.button_tecRemove.TabIndex = 5;
            this.button_tecRemove.Text = "删除";
            this.button_tecRemove.UseVisualStyleBackColor = true;
            this.button_tecRemove.Click += new System.EventHandler(this.button_tecRemove_Click);
            // 
            // tabPageTalk
            // 
            this.tabPageTalk.Controls.Add(this.groupBox24);
            this.tabPageTalk.Controls.Add(this.groupBoxNpcTalk);
            this.tabPageTalk.Controls.Add(this.groupBox22);
            this.tabPageTalk.Controls.Add(this.groupBox21);
            this.tabPageTalk.Location = new System.Drawing.Point(4, 22);
            this.tabPageTalk.Name = "tabPageTalk";
            this.tabPageTalk.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageTalk.Size = new System.Drawing.Size(1090, 544);
            this.tabPageTalk.TabIndex = 5;
            this.tabPageTalk.Text = "互动对话/递送";
            this.tabPageTalk.UseVisualStyleBackColor = true;
            // 
            // groupBox24
            // 
            this.groupBox24.Controls.Add(this.dataGridViewReceiveItem);
            this.groupBox24.Controls.Add(this.textBoxReceiveItemCount);
            this.groupBox24.Controls.Add(this.textBoxReceiveItemName);
            this.groupBox24.Controls.Add(this.textBoxReceiveItemID);
            this.groupBox24.Controls.Add(this.label51);
            this.groupBox24.Controls.Add(this.label50);
            this.groupBox24.Controls.Add(this.label49);
            this.groupBox24.Controls.Add(this.buttonReceiveItemDel);
            this.groupBox24.Controls.Add(this.buttonReceiveItemAdd);
            this.groupBox24.Controls.Add(this.buttonReceiveItem);
            this.groupBox24.Controls.Add(this.label48);
            this.groupBox24.Location = new System.Drawing.Point(20, 320);
            this.groupBox24.Name = "groupBox24";
            this.groupBox24.Size = new System.Drawing.Size(381, 160);
            this.groupBox24.TabIndex = 3;
            this.groupBox24.TabStop = false;
            this.groupBox24.Text = "收取道具";
            // 
            // dataGridViewReceiveItem
            // 
            this.dataGridViewReceiveItem.AllowUserToAddRows = false;
            this.dataGridViewReceiveItem.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewReceiveItem.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewReceiveItem.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ReveiveItem,
            this.ReceiveName,
            this.ReceiveCount});
            this.dataGridViewReceiveItem.Location = new System.Drawing.Point(149, 19);
            this.dataGridViewReceiveItem.MultiSelect = false;
            this.dataGridViewReceiveItem.Name = "dataGridViewReceiveItem";
            this.dataGridViewReceiveItem.RowHeadersVisible = false;
            this.dataGridViewReceiveItem.RowTemplate.Height = 23;
            this.dataGridViewReceiveItem.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewReceiveItem.Size = new System.Drawing.Size(226, 134);
            this.dataGridViewReceiveItem.TabIndex = 4;
            this.dataGridViewReceiveItem.SelectionChanged += new System.EventHandler(this.dataGridViewReceiveItem_SelectionChanged);
            // 
            // ReveiveItem
            // 
            this.ReveiveItem.HeaderText = "道具ID";
            this.ReveiveItem.Name = "ReveiveItem";
            this.ReveiveItem.Width = 66;
            // 
            // ReceiveName
            // 
            this.ReceiveName.HeaderText = "道具名称";
            this.ReceiveName.Name = "ReceiveName";
            this.ReceiveName.Width = 78;
            // 
            // ReceiveCount
            // 
            this.ReceiveCount.HeaderText = "收集数量";
            this.ReceiveCount.Name = "ReceiveCount";
            this.ReceiveCount.Width = 78;
            // 
            // textBoxReceiveItemCount
            // 
            this.textBoxReceiveItemCount.Location = new System.Drawing.Point(62, 103);
            this.textBoxReceiveItemCount.Name = "textBoxReceiveItemCount";
            this.textBoxReceiveItemCount.Size = new System.Drawing.Size(84, 21);
            this.textBoxReceiveItemCount.TabIndex = 3;
            // 
            // textBoxReceiveItemName
            // 
            this.textBoxReceiveItemName.Location = new System.Drawing.Point(62, 74);
            this.textBoxReceiveItemName.Name = "textBoxReceiveItemName";
            this.textBoxReceiveItemName.Size = new System.Drawing.Size(85, 21);
            this.textBoxReceiveItemName.TabIndex = 3;
            // 
            // textBoxReceiveItemID
            // 
            this.textBoxReceiveItemID.Location = new System.Drawing.Point(62, 45);
            this.textBoxReceiveItemID.Name = "textBoxReceiveItemID";
            this.textBoxReceiveItemID.Size = new System.Drawing.Size(84, 21);
            this.textBoxReceiveItemID.TabIndex = 3;
            // 
            // label51
            // 
            this.label51.AutoSize = true;
            this.label51.Location = new System.Drawing.Point(9, 108);
            this.label51.Name = "label51";
            this.label51.Size = new System.Drawing.Size(53, 12);
            this.label51.TabIndex = 2;
            this.label51.Text = "收集数量";
            // 
            // label50
            // 
            this.label50.AutoSize = true;
            this.label50.Location = new System.Drawing.Point(9, 79);
            this.label50.Name = "label50";
            this.label50.Size = new System.Drawing.Size(53, 12);
            this.label50.TabIndex = 2;
            this.label50.Text = "道具名称";
            // 
            // label49
            // 
            this.label49.AutoSize = true;
            this.label49.Location = new System.Drawing.Point(9, 50);
            this.label49.Name = "label49";
            this.label49.Size = new System.Drawing.Size(41, 12);
            this.label49.TabIndex = 2;
            this.label49.Text = "道具ID";
            // 
            // buttonReceiveItemDel
            // 
            this.buttonReceiveItemDel.Location = new System.Drawing.Point(76, 130);
            this.buttonReceiveItemDel.Name = "buttonReceiveItemDel";
            this.buttonReceiveItemDel.Size = new System.Drawing.Size(67, 23);
            this.buttonReceiveItemDel.TabIndex = 1;
            this.buttonReceiveItemDel.Text = "删除";
            this.buttonReceiveItemDel.UseVisualStyleBackColor = true;
            this.buttonReceiveItemDel.Click += new System.EventHandler(this.buttonReceiveItemDel_Click);
            // 
            // buttonReceiveItemAdd
            // 
            this.buttonReceiveItemAdd.Location = new System.Drawing.Point(10, 130);
            this.buttonReceiveItemAdd.Name = "buttonReceiveItemAdd";
            this.buttonReceiveItemAdd.Size = new System.Drawing.Size(60, 23);
            this.buttonReceiveItemAdd.TabIndex = 1;
            this.buttonReceiveItemAdd.Text = "添加";
            this.buttonReceiveItemAdd.UseVisualStyleBackColor = true;
            this.buttonReceiveItemAdd.Click += new System.EventHandler(this.buttonReceiveItemAdd_Click);
            // 
            // buttonReceiveItem
            // 
            this.buttonReceiveItem.Location = new System.Drawing.Point(62, 19);
            this.buttonReceiveItem.Name = "buttonReceiveItem";
            this.buttonReceiveItem.Size = new System.Drawing.Size(75, 23);
            this.buttonReceiveItem.TabIndex = 1;
            this.buttonReceiveItem.Text = "Select";
            this.buttonReceiveItem.UseVisualStyleBackColor = true;
            this.buttonReceiveItem.Click += new System.EventHandler(this.buttonReceiveItem_Click);
            // 
            // label48
            // 
            this.label48.AutoSize = true;
            this.label48.Location = new System.Drawing.Point(9, 21);
            this.label48.Name = "label48";
            this.label48.Size = new System.Drawing.Size(53, 12);
            this.label48.TabIndex = 0;
            this.label48.Text = "道具选择";
            // 
            // groupBoxNpcTalk
            // 
            this.groupBoxNpcTalk.Controls.Add(this.label53);
            this.groupBoxNpcTalk.Controls.Add(this.label52);
            this.groupBoxNpcTalk.Controls.Add(this.buttonUpdateTalkWords);
            this.groupBoxNpcTalk.Controls.Add(this.buttonAddTalkWords);
            this.groupBoxNpcTalk.Controls.Add(this.textBoxNPCWords);
            this.groupBoxNpcTalk.Controls.Add(this.textBoxPCWords);
            this.groupBoxNpcTalk.Location = new System.Drawing.Point(407, 3);
            this.groupBoxNpcTalk.Name = "groupBoxNpcTalk";
            this.groupBoxNpcTalk.Size = new System.Drawing.Size(347, 477);
            this.groupBoxNpcTalk.TabIndex = 2;
            this.groupBoxNpcTalk.TabStop = false;
            this.groupBoxNpcTalk.Text = "台词";
            // 
            // label53
            // 
            this.label53.AutoSize = true;
            this.label53.Location = new System.Drawing.Point(16, 238);
            this.label53.Name = "label53";
            this.label53.Size = new System.Drawing.Size(47, 12);
            this.label53.TabIndex = 4;
            this.label53.Text = "NPC台词";
            // 
            // label52
            // 
            this.label52.AutoSize = true;
            this.label52.Location = new System.Drawing.Point(21, 20);
            this.label52.Name = "label52";
            this.label52.Size = new System.Drawing.Size(41, 12);
            this.label52.TabIndex = 4;
            this.label52.Text = "PC台词";
            // 
            // buttonUpdateTalkWords
            // 
            this.buttonUpdateTalkWords.Location = new System.Drawing.Point(187, 447);
            this.buttonUpdateTalkWords.Name = "buttonUpdateTalkWords";
            this.buttonUpdateTalkWords.Size = new System.Drawing.Size(75, 23);
            this.buttonUpdateTalkWords.TabIndex = 3;
            this.buttonUpdateTalkWords.Text = "更新";
            this.buttonUpdateTalkWords.UseVisualStyleBackColor = true;
            this.buttonUpdateTalkWords.Click += new System.EventHandler(this.buttonUpdateTalkWords_Click);
            // 
            // buttonAddTalkWords
            // 
            this.buttonAddTalkWords.Location = new System.Drawing.Point(50, 447);
            this.buttonAddTalkWords.Name = "buttonAddTalkWords";
            this.buttonAddTalkWords.Size = new System.Drawing.Size(75, 23);
            this.buttonAddTalkWords.TabIndex = 3;
            this.buttonAddTalkWords.Text = "添加";
            this.buttonAddTalkWords.UseVisualStyleBackColor = true;
            this.buttonAddTalkWords.Click += new System.EventHandler(this.buttonAddTalkWords_Click);
            // 
            // textBoxNPCWords
            // 
            this.textBoxNPCWords.Location = new System.Drawing.Point(18, 258);
            this.textBoxNPCWords.Multiline = true;
            this.textBoxNPCWords.Name = "textBoxNPCWords";
            this.textBoxNPCWords.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxNPCWords.Size = new System.Drawing.Size(313, 181);
            this.textBoxNPCWords.TabIndex = 1;
            // 
            // textBoxPCWords
            // 
            this.textBoxPCWords.Location = new System.Drawing.Point(18, 35);
            this.textBoxPCWords.Multiline = true;
            this.textBoxPCWords.Name = "textBoxPCWords";
            this.textBoxPCWords.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxPCWords.Size = new System.Drawing.Size(313, 196);
            this.textBoxPCWords.TabIndex = 0;
            // 
            // groupBox22
            // 
            this.groupBox22.Controls.Add(this.buttonDelTalkWords);
            this.groupBox22.Controls.Add(this.buttonDownNpcWords);
            this.groupBox22.Controls.Add(this.buttonUpNpcWords);
            this.groupBox22.Controls.Add(this.dataGridViewTalkWords);
            this.groupBox22.Location = new System.Drawing.Point(20, 156);
            this.groupBox22.Name = "groupBox22";
            this.groupBox22.Size = new System.Drawing.Size(381, 158);
            this.groupBox22.TabIndex = 1;
            this.groupBox22.TabStop = false;
            this.groupBox22.Text = "台词预览";
            // 
            // buttonDelTalkWords
            // 
            this.buttonDelTalkWords.Location = new System.Drawing.Point(321, 105);
            this.buttonDelTalkWords.Name = "buttonDelTalkWords";
            this.buttonDelTalkWords.Size = new System.Drawing.Size(49, 23);
            this.buttonDelTalkWords.TabIndex = 3;
            this.buttonDelTalkWords.Text = "删除";
            this.buttonDelTalkWords.UseVisualStyleBackColor = true;
            this.buttonDelTalkWords.Click += new System.EventHandler(this.buttonDelTalkWords_Click);
            // 
            // buttonDownNpcWords
            // 
            this.buttonDownNpcWords.Location = new System.Drawing.Point(321, 75);
            this.buttonDownNpcWords.Name = "buttonDownNpcWords";
            this.buttonDownNpcWords.Size = new System.Drawing.Size(49, 24);
            this.buttonDownNpcWords.TabIndex = 1;
            this.buttonDownNpcWords.Text = "下移";
            this.buttonDownNpcWords.UseVisualStyleBackColor = true;
            this.buttonDownNpcWords.Click += new System.EventHandler(this.buttonDownNpcWords_Click);
            // 
            // buttonUpNpcWords
            // 
            this.buttonUpNpcWords.Location = new System.Drawing.Point(321, 45);
            this.buttonUpNpcWords.Name = "buttonUpNpcWords";
            this.buttonUpNpcWords.Size = new System.Drawing.Size(49, 24);
            this.buttonUpNpcWords.TabIndex = 1;
            this.buttonUpNpcWords.Text = "上移";
            this.buttonUpNpcWords.UseVisualStyleBackColor = true;
            this.buttonUpNpcWords.Click += new System.EventHandler(this.buttonUpNpcWords_Click);
            // 
            // dataGridViewTalkWords
            // 
            this.dataGridViewTalkWords.AllowUserToAddRows = false;
            this.dataGridViewTalkWords.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewTalkWords.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTalkWords.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Index,
            this.PCWords,
            this.NPCWords});
            this.dataGridViewTalkWords.Location = new System.Drawing.Point(10, 22);
            this.dataGridViewTalkWords.MultiSelect = false;
            this.dataGridViewTalkWords.Name = "dataGridViewTalkWords";
            this.dataGridViewTalkWords.RowHeadersVisible = false;
            this.dataGridViewTalkWords.RowTemplate.Height = 23;
            this.dataGridViewTalkWords.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewTalkWords.Size = new System.Drawing.Size(305, 125);
            this.dataGridViewTalkWords.TabIndex = 0;
            this.dataGridViewTalkWords.SelectionChanged += new System.EventHandler(this.dataGridViewTalkWords_SelectionChanged);
            // 
            // Index
            // 
            this.Index.HeaderText = "编号";
            this.Index.Name = "Index";
            this.Index.Width = 54;
            // 
            // PCWords
            // 
            this.PCWords.HeaderText = "PC台词";
            this.PCWords.Name = "PCWords";
            this.PCWords.Width = 66;
            // 
            // NPCWords
            // 
            this.NPCWords.HeaderText = "NPC台词";
            this.NPCWords.Name = "NPCWords";
            this.NPCWords.Width = 72;
            // 
            // groupBox21
            // 
            this.groupBox21.Controls.Add(this.buttonDelTalkNpc);
            this.groupBox21.Controls.Add(this.buttonAddTalkNpc);
            this.groupBox21.Controls.Add(this.dataGridViewNpcTalk);
            this.groupBox21.Controls.Add(this.textBoxNpcTalkName);
            this.groupBox21.Controls.Add(this.label47);
            this.groupBox21.Controls.Add(this.textBoxNpcTalkID);
            this.groupBox21.Controls.Add(this.label46);
            this.groupBox21.Controls.Add(this.buttonNpcTalk);
            this.groupBox21.Controls.Add(this.label45);
            this.groupBox21.Location = new System.Drawing.Point(20, 3);
            this.groupBox21.Name = "groupBox21";
            this.groupBox21.Size = new System.Drawing.Size(381, 153);
            this.groupBox21.TabIndex = 0;
            this.groupBox21.TabStop = false;
            this.groupBox21.Text = "目标选择";
            // 
            // buttonDelTalkNpc
            // 
            this.buttonDelTalkNpc.Location = new System.Drawing.Point(87, 116);
            this.buttonDelTalkNpc.Name = "buttonDelTalkNpc";
            this.buttonDelTalkNpc.Size = new System.Drawing.Size(60, 23);
            this.buttonDelTalkNpc.TabIndex = 5;
            this.buttonDelTalkNpc.Text = "删除";
            this.buttonDelTalkNpc.UseVisualStyleBackColor = true;
            this.buttonDelTalkNpc.Click += new System.EventHandler(this.buttonDelTalkNpc_Click);
            // 
            // buttonAddTalkNpc
            // 
            this.buttonAddTalkNpc.Location = new System.Drawing.Point(11, 116);
            this.buttonAddTalkNpc.Name = "buttonAddTalkNpc";
            this.buttonAddTalkNpc.Size = new System.Drawing.Size(60, 23);
            this.buttonAddTalkNpc.TabIndex = 5;
            this.buttonAddTalkNpc.Text = "添加";
            this.buttonAddTalkNpc.UseVisualStyleBackColor = true;
            this.buttonAddTalkNpc.Click += new System.EventHandler(this.buttonAddTalkNpc_Click);
            // 
            // dataGridViewNpcTalk
            // 
            this.dataGridViewNpcTalk.AllowUserToAddRows = false;
            this.dataGridViewNpcTalk.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewNpcTalk.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewNpcTalk.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NpcTalkID,
            this.NpcTalkName});
            this.dataGridViewNpcTalk.Location = new System.Drawing.Point(165, 18);
            this.dataGridViewNpcTalk.MultiSelect = false;
            this.dataGridViewNpcTalk.Name = "dataGridViewNpcTalk";
            this.dataGridViewNpcTalk.RowHeadersVisible = false;
            this.dataGridViewNpcTalk.RowTemplate.Height = 23;
            this.dataGridViewNpcTalk.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewNpcTalk.Size = new System.Drawing.Size(210, 129);
            this.dataGridViewNpcTalk.TabIndex = 4;
            this.dataGridViewNpcTalk.SelectionChanged += new System.EventHandler(this.dataGridViewNpcTalk_SelectionChanged);
            // 
            // NpcTalkID
            // 
            this.NpcTalkID.HeaderText = "目标ID";
            this.NpcTalkID.Name = "NpcTalkID";
            this.NpcTalkID.Width = 66;
            // 
            // NpcTalkName
            // 
            this.NpcTalkName.HeaderText = "目标名称";
            this.NpcTalkName.Name = "NpcTalkName";
            this.NpcTalkName.Width = 78;
            // 
            // textBoxNpcTalkName
            // 
            this.textBoxNpcTalkName.Location = new System.Drawing.Point(59, 85);
            this.textBoxNpcTalkName.Name = "textBoxNpcTalkName";
            this.textBoxNpcTalkName.Size = new System.Drawing.Size(100, 21);
            this.textBoxNpcTalkName.TabIndex = 3;
            // 
            // label47
            // 
            this.label47.AutoSize = true;
            this.label47.Location = new System.Drawing.Point(6, 88);
            this.label47.Name = "label47";
            this.label47.Size = new System.Drawing.Size(47, 12);
            this.label47.TabIndex = 2;
            this.label47.Text = "NPC名称";
            // 
            // textBoxNpcTalkID
            // 
            this.textBoxNpcTalkID.Location = new System.Drawing.Point(59, 56);
            this.textBoxNpcTalkID.Name = "textBoxNpcTalkID";
            this.textBoxNpcTalkID.Size = new System.Drawing.Size(100, 21);
            this.textBoxNpcTalkID.TabIndex = 3;
            // 
            // label46
            // 
            this.label46.AutoSize = true;
            this.label46.Location = new System.Drawing.Point(6, 59);
            this.label46.Name = "label46";
            this.label46.Size = new System.Drawing.Size(41, 12);
            this.label46.TabIndex = 2;
            this.label46.Text = "NPC ID";
            // 
            // buttonNpcTalk
            // 
            this.buttonNpcTalk.Location = new System.Drawing.Point(59, 26);
            this.buttonNpcTalk.Name = "buttonNpcTalk";
            this.buttonNpcTalk.Size = new System.Drawing.Size(75, 23);
            this.buttonNpcTalk.TabIndex = 1;
            this.buttonNpcTalk.Text = "Select";
            this.buttonNpcTalk.UseVisualStyleBackColor = true;
            this.buttonNpcTalk.Click += new System.EventHandler(this.buttonNpcTalk_Click);
            // 
            // label45
            // 
            this.label45.AutoSize = true;
            this.label45.Location = new System.Drawing.Point(6, 31);
            this.label45.Name = "label45";
            this.label45.Size = new System.Drawing.Size(47, 12);
            this.label45.TabIndex = 0;
            this.label45.Text = "NPC选择";
            // 
            // tabPageAward
            // 
            this.tabPageAward.Controls.Add(this.groupBox20);
            this.tabPageAward.Controls.Add(this.groupBox19);
            this.tabPageAward.Controls.Add(this.groupBox18);
            this.tabPageAward.Controls.Add(this.groupBox16);
            this.tabPageAward.Controls.Add(this.groupBox53);
            this.tabPageAward.Location = new System.Drawing.Point(4, 22);
            this.tabPageAward.Name = "tabPageAward";
            this.tabPageAward.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageAward.Size = new System.Drawing.Size(1150, 527);
            this.tabPageAward.TabIndex = 3;
            this.tabPageAward.Text = "任务奖励";
            this.tabPageAward.UseVisualStyleBackColor = true;
            // 
            // groupBox20
            // 
            this.groupBox20.Controls.Add(this.label123);
            this.groupBox20.Controls.Add(this.cmbJobLimitS);
            this.groupBox20.Controls.Add(this.buttonOptItemDel);
            this.groupBox20.Controls.Add(this.buttonOptItemAdd);
            this.groupBox20.Controls.Add(this.dataGridViewOptItem);
            this.groupBox20.Controls.Add(this.textBoxOptItemCount);
            this.groupBox20.Controls.Add(this.label37);
            this.groupBox20.Controls.Add(this.textBoxOptItemName);
            this.groupBox20.Controls.Add(this.label44);
            this.groupBox20.Controls.Add(this.textBoxOptItemID);
            this.groupBox20.Controls.Add(this.label36);
            this.groupBox20.Controls.Add(this.buttonOptItem);
            this.groupBox20.Controls.Add(this.label35);
            this.groupBox20.Enabled = false;
            this.groupBox20.Location = new System.Drawing.Point(573, 164);
            this.groupBox20.Name = "groupBox20";
            this.groupBox20.Size = new System.Drawing.Size(243, 315);
            this.groupBox20.TabIndex = 4;
            this.groupBox20.TabStop = false;
            this.groupBox20.Text = "选择道具";
            // 
            // label123
            // 
            this.label123.AutoSize = true;
            this.label123.Location = new System.Drawing.Point(21, 155);
            this.label123.Name = "label123";
            this.label123.Size = new System.Drawing.Size(53, 12);
            this.label123.TabIndex = 11;
            this.label123.Text = "职业限制";
            // 
            // cmbJobLimitS
            // 
            this.cmbJobLimitS.FormattingEnabled = true;
            this.cmbJobLimitS.Location = new System.Drawing.Point(100, 149);
            this.cmbJobLimitS.Name = "cmbJobLimitS";
            this.cmbJobLimitS.Size = new System.Drawing.Size(100, 20);
            this.cmbJobLimitS.TabIndex = 10;
            // 
            // buttonOptItemDel
            // 
            this.buttonOptItemDel.Location = new System.Drawing.Point(124, 285);
            this.buttonOptItemDel.Name = "buttonOptItemDel";
            this.buttonOptItemDel.Size = new System.Drawing.Size(75, 23);
            this.buttonOptItemDel.TabIndex = 8;
            this.buttonOptItemDel.Text = "删除";
            this.buttonOptItemDel.UseVisualStyleBackColor = true;
            this.buttonOptItemDel.Click += new System.EventHandler(this.buttonOptItemDel_Click);
            // 
            // buttonOptItemAdd
            // 
            this.buttonOptItemAdd.Location = new System.Drawing.Point(35, 286);
            this.buttonOptItemAdd.Name = "buttonOptItemAdd";
            this.buttonOptItemAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonOptItemAdd.TabIndex = 7;
            this.buttonOptItemAdd.Text = "添加";
            this.buttonOptItemAdd.UseVisualStyleBackColor = true;
            this.buttonOptItemAdd.Click += new System.EventHandler(this.buttonOptItemAdd_Click);
            // 
            // dataGridViewOptItem
            // 
            this.dataGridViewOptItem.AllowUserToAddRows = false;
            this.dataGridViewOptItem.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.OptItemID,
            this.OptItemName,
            this.OptItemCount,
            this.dataGridViewTextBoxColumn37});
            this.dataGridViewOptItem.Location = new System.Drawing.Point(18, 181);
            this.dataGridViewOptItem.Name = "dataGridViewOptItem";
            this.dataGridViewOptItem.RowHeadersVisible = false;
            this.dataGridViewOptItem.RowTemplate.Height = 23;
            this.dataGridViewOptItem.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewOptItem.Size = new System.Drawing.Size(209, 97);
            this.dataGridViewOptItem.TabIndex = 6;
            // 
            // OptItemID
            // 
            this.OptItemID.FillWeight = 50F;
            this.OptItemID.HeaderText = "道具ID";
            this.OptItemID.Name = "OptItemID";
            this.OptItemID.Width = 40;
            // 
            // OptItemName
            // 
            this.OptItemName.FillWeight = 70F;
            this.OptItemName.HeaderText = "道具名称";
            this.OptItemName.Name = "OptItemName";
            this.OptItemName.Width = 62;
            // 
            // OptItemCount
            // 
            this.OptItemCount.FillWeight = 50F;
            this.OptItemCount.HeaderText = "数量";
            this.OptItemCount.Name = "OptItemCount";
            this.OptItemCount.Width = 40;
            // 
            // dataGridViewTextBoxColumn37
            // 
            this.dataGridViewTextBoxColumn37.FillWeight = 70F;
            this.dataGridViewTextBoxColumn37.HeaderText = "职业限制";
            this.dataGridViewTextBoxColumn37.Name = "dataGridViewTextBoxColumn37";
            this.dataGridViewTextBoxColumn37.Width = 62;
            // 
            // textBoxOptItemCount
            // 
            this.textBoxOptItemCount.Location = new System.Drawing.Point(100, 114);
            this.textBoxOptItemCount.Name = "textBoxOptItemCount";
            this.textBoxOptItemCount.Size = new System.Drawing.Size(100, 21);
            this.textBoxOptItemCount.TabIndex = 5;
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Location = new System.Drawing.Point(20, 119);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(53, 12);
            this.label37.TabIndex = 4;
            this.label37.Text = "道具数量";
            // 
            // textBoxOptItemName
            // 
            this.textBoxOptItemName.Location = new System.Drawing.Point(100, 82);
            this.textBoxOptItemName.Name = "textBoxOptItemName";
            this.textBoxOptItemName.Size = new System.Drawing.Size(100, 21);
            this.textBoxOptItemName.TabIndex = 3;
            // 
            // label44
            // 
            this.label44.AutoSize = true;
            this.label44.Location = new System.Drawing.Point(20, 87);
            this.label44.Name = "label44";
            this.label44.Size = new System.Drawing.Size(53, 12);
            this.label44.TabIndex = 2;
            this.label44.Text = "道具名称";
            // 
            // textBoxOptItemID
            // 
            this.textBoxOptItemID.Location = new System.Drawing.Point(101, 49);
            this.textBoxOptItemID.Name = "textBoxOptItemID";
            this.textBoxOptItemID.Size = new System.Drawing.Size(98, 21);
            this.textBoxOptItemID.TabIndex = 3;
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Location = new System.Drawing.Point(21, 54);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(41, 12);
            this.label36.TabIndex = 2;
            this.label36.Text = "道具ID";
            // 
            // buttonOptItem
            // 
            this.buttonOptItem.Location = new System.Drawing.Point(101, 19);
            this.buttonOptItem.Name = "buttonOptItem";
            this.buttonOptItem.Size = new System.Drawing.Size(75, 23);
            this.buttonOptItem.TabIndex = 1;
            this.buttonOptItem.Text = "Select";
            this.buttonOptItem.UseVisualStyleBackColor = true;
            this.buttonOptItem.Click += new System.EventHandler(this.buttonOptItem_Click);
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(18, 23);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(53, 12);
            this.label35.TabIndex = 0;
            this.label35.Text = "道具选择";
            // 
            // groupBox19
            // 
            this.groupBox19.Controls.Add(this.cmbJobLimit);
            this.groupBox19.Controls.Add(this.label25);
            this.groupBox19.Controls.Add(this.buttonMustItemDel);
            this.groupBox19.Controls.Add(this.buttonMustItemAdd);
            this.groupBox19.Controls.Add(this.dataGridViewMustItem);
            this.groupBox19.Controls.Add(this.textBoxMustItemCount);
            this.groupBox19.Controls.Add(this.label34);
            this.groupBox19.Controls.Add(this.textBoxMustItemID);
            this.groupBox19.Controls.Add(this.label43);
            this.groupBox19.Controls.Add(this.textBoxMustItemName);
            this.groupBox19.Controls.Add(this.label33);
            this.groupBox19.Controls.Add(this.buttonMustItem);
            this.groupBox19.Controls.Add(this.label32);
            this.groupBox19.Location = new System.Drawing.Point(308, 163);
            this.groupBox19.Name = "groupBox19";
            this.groupBox19.Size = new System.Drawing.Size(238, 316);
            this.groupBox19.TabIndex = 3;
            this.groupBox19.TabStop = false;
            this.groupBox19.Text = "必给道具";
            // 
            // cmbJobLimit
            // 
            this.cmbJobLimit.FormattingEnabled = true;
            this.cmbJobLimit.Location = new System.Drawing.Point(106, 150);
            this.cmbJobLimit.Name = "cmbJobLimit";
            this.cmbJobLimit.Size = new System.Drawing.Size(105, 20);
            this.cmbJobLimit.TabIndex = 9;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(18, 156);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(53, 12);
            this.label25.TabIndex = 8;
            this.label25.Text = "职业限制";
            // 
            // buttonMustItemDel
            // 
            this.buttonMustItemDel.Location = new System.Drawing.Point(129, 286);
            this.buttonMustItemDel.Name = "buttonMustItemDel";
            this.buttonMustItemDel.Size = new System.Drawing.Size(75, 23);
            this.buttonMustItemDel.TabIndex = 7;
            this.buttonMustItemDel.Text = "删除";
            this.buttonMustItemDel.UseVisualStyleBackColor = true;
            this.buttonMustItemDel.Click += new System.EventHandler(this.buttonMustItemDel_Click);
            // 
            // buttonMustItemAdd
            // 
            this.buttonMustItemAdd.Location = new System.Drawing.Point(30, 287);
            this.buttonMustItemAdd.Name = "buttonMustItemAdd";
            this.buttonMustItemAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonMustItemAdd.TabIndex = 7;
            this.buttonMustItemAdd.Text = "添加";
            this.buttonMustItemAdd.UseVisualStyleBackColor = true;
            this.buttonMustItemAdd.Click += new System.EventHandler(this.buttonMustItemAdd_Click);
            // 
            // dataGridViewMustItem
            // 
            this.dataGridViewMustItem.AllowUserToAddRows = false;
            this.dataGridViewMustItem.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.AwardItemID,
            this.AwradItemName,
            this.AwardItemCount,
            this.JobLimit});
            this.dataGridViewMustItem.Location = new System.Drawing.Point(16, 183);
            this.dataGridViewMustItem.Name = "dataGridViewMustItem";
            this.dataGridViewMustItem.RowHeadersVisible = false;
            this.dataGridViewMustItem.RowTemplate.Height = 23;
            this.dataGridViewMustItem.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewMustItem.Size = new System.Drawing.Size(207, 96);
            this.dataGridViewMustItem.TabIndex = 6;
            // 
            // AwardItemID
            // 
            this.AwardItemID.FillWeight = 50F;
            this.AwardItemID.HeaderText = "道具";
            this.AwardItemID.Name = "AwardItemID";
            this.AwardItemID.Width = 40;
            // 
            // AwradItemName
            // 
            this.AwradItemName.FillWeight = 70F;
            this.AwradItemName.HeaderText = "道具名称";
            this.AwradItemName.Name = "AwradItemName";
            this.AwradItemName.Width = 62;
            // 
            // AwardItemCount
            // 
            this.AwardItemCount.FillWeight = 50F;
            this.AwardItemCount.HeaderText = "数量";
            this.AwardItemCount.Name = "AwardItemCount";
            this.AwardItemCount.Width = 40;
            // 
            // JobLimit
            // 
            this.JobLimit.FillWeight = 70F;
            this.JobLimit.HeaderText = "职业限制";
            this.JobLimit.Name = "JobLimit";
            this.JobLimit.Width = 62;
            // 
            // textBoxMustItemCount
            // 
            this.textBoxMustItemCount.Location = new System.Drawing.Point(106, 116);
            this.textBoxMustItemCount.Name = "textBoxMustItemCount";
            this.textBoxMustItemCount.Size = new System.Drawing.Size(105, 21);
            this.textBoxMustItemCount.TabIndex = 5;
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(18, 119);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(53, 12);
            this.label34.TabIndex = 4;
            this.label34.Text = "道具数量";
            // 
            // textBoxMustItemID
            // 
            this.textBoxMustItemID.Location = new System.Drawing.Point(106, 52);
            this.textBoxMustItemID.Name = "textBoxMustItemID";
            this.textBoxMustItemID.Size = new System.Drawing.Size(105, 21);
            this.textBoxMustItemID.TabIndex = 3;
            // 
            // label43
            // 
            this.label43.AutoSize = true;
            this.label43.Location = new System.Drawing.Point(18, 57);
            this.label43.Name = "label43";
            this.label43.Size = new System.Drawing.Size(41, 12);
            this.label43.TabIndex = 2;
            this.label43.Text = "道具ID";
            // 
            // textBoxMustItemName
            // 
            this.textBoxMustItemName.Location = new System.Drawing.Point(106, 83);
            this.textBoxMustItemName.Name = "textBoxMustItemName";
            this.textBoxMustItemName.Size = new System.Drawing.Size(105, 21);
            this.textBoxMustItemName.TabIndex = 3;
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(18, 89);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(53, 12);
            this.label33.TabIndex = 2;
            this.label33.Text = "道具名称";
            // 
            // buttonMustItem
            // 
            this.buttonMustItem.Location = new System.Drawing.Point(106, 21);
            this.buttonMustItem.Name = "buttonMustItem";
            this.buttonMustItem.Size = new System.Drawing.Size(91, 23);
            this.buttonMustItem.TabIndex = 1;
            this.buttonMustItem.Text = "Select";
            this.buttonMustItem.UseVisualStyleBackColor = true;
            this.buttonMustItem.Click += new System.EventHandler(this.buttonMustItem_Click);
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(18, 26);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(53, 12);
            this.label32.TabIndex = 0;
            this.label32.Text = "道具选择";
            // 
            // groupBox18
            // 
            this.groupBox18.Controls.Add(this.dataGridViewTitle);
            this.groupBox18.Controls.Add(this.buttonDelTitle);
            this.groupBox18.Controls.Add(this.buttonAddTitle);
            this.groupBox18.Controls.Add(this.textBoxTitleName);
            this.groupBox18.Controls.Add(this.label42);
            this.groupBox18.Controls.Add(this.textBoxTitleID);
            this.groupBox18.Controls.Add(this.label31);
            this.groupBox18.Controls.Add(this.buttonSelectTitle);
            this.groupBox18.Controls.Add(this.label30);
            this.groupBox18.Location = new System.Drawing.Point(308, 6);
            this.groupBox18.Name = "groupBox18";
            this.groupBox18.Size = new System.Drawing.Size(388, 142);
            this.groupBox18.TabIndex = 2;
            this.groupBox18.TabStop = false;
            this.groupBox18.Text = "称号奖励";
            // 
            // dataGridViewTitle
            // 
            this.dataGridViewTitle.AllowUserToAddRows = false;
            this.dataGridViewTitle.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridViewTitle.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTitle.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.TitleID,
            this.TitleName});
            this.dataGridViewTitle.Location = new System.Drawing.Point(185, 18);
            this.dataGridViewTitle.Name = "dataGridViewTitle";
            this.dataGridViewTitle.RowHeadersVisible = false;
            this.dataGridViewTitle.RowTemplate.Height = 23;
            this.dataGridViewTitle.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewTitle.Size = new System.Drawing.Size(172, 112);
            this.dataGridViewTitle.TabIndex = 5;
            // 
            // TitleID
            // 
            this.TitleID.HeaderText = "称号ID";
            this.TitleID.Name = "TitleID";
            this.TitleID.Width = 66;
            // 
            // TitleName
            // 
            this.TitleName.HeaderText = "称号名称";
            this.TitleName.Name = "TitleName";
            this.TitleName.Width = 78;
            // 
            // buttonDelTitle
            // 
            this.buttonDelTitle.Location = new System.Drawing.Point(95, 109);
            this.buttonDelTitle.Name = "buttonDelTitle";
            this.buttonDelTitle.Size = new System.Drawing.Size(71, 23);
            this.buttonDelTitle.TabIndex = 4;
            this.buttonDelTitle.Text = "删除";
            this.buttonDelTitle.UseVisualStyleBackColor = true;
            this.buttonDelTitle.Click += new System.EventHandler(this.buttonDelTitle_Click);
            // 
            // buttonAddTitle
            // 
            this.buttonAddTitle.Location = new System.Drawing.Point(8, 110);
            this.buttonAddTitle.Name = "buttonAddTitle";
            this.buttonAddTitle.Size = new System.Drawing.Size(71, 23);
            this.buttonAddTitle.TabIndex = 4;
            this.buttonAddTitle.Text = "添加";
            this.buttonAddTitle.UseVisualStyleBackColor = true;
            this.buttonAddTitle.Click += new System.EventHandler(this.buttonAddTitle_Click);
            // 
            // textBoxTitleName
            // 
            this.textBoxTitleName.Location = new System.Drawing.Point(75, 82);
            this.textBoxTitleName.Name = "textBoxTitleName";
            this.textBoxTitleName.Size = new System.Drawing.Size(91, 21);
            this.textBoxTitleName.TabIndex = 3;
            // 
            // label42
            // 
            this.label42.AutoSize = true;
            this.label42.Location = new System.Drawing.Point(12, 85);
            this.label42.Name = "label42";
            this.label42.Size = new System.Drawing.Size(53, 12);
            this.label42.TabIndex = 2;
            this.label42.Text = "称号名称";
            // 
            // textBoxTitleID
            // 
            this.textBoxTitleID.Location = new System.Drawing.Point(75, 52);
            this.textBoxTitleID.Name = "textBoxTitleID";
            this.textBoxTitleID.Size = new System.Drawing.Size(91, 21);
            this.textBoxTitleID.TabIndex = 3;
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(12, 55);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(41, 12);
            this.label31.TabIndex = 2;
            this.label31.Text = "称号ID";
            // 
            // buttonSelectTitle
            // 
            this.buttonSelectTitle.Location = new System.Drawing.Point(75, 22);
            this.buttonSelectTitle.Name = "buttonSelectTitle";
            this.buttonSelectTitle.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectTitle.TabIndex = 1;
            this.buttonSelectTitle.Text = "Select";
            this.buttonSelectTitle.UseVisualStyleBackColor = true;
            this.buttonSelectTitle.Click += new System.EventHandler(this.buttonSelectTitle_Click);
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(6, 28);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(53, 12);
            this.label30.TabIndex = 0;
            this.label30.Text = "选择称号";
            // 
            // groupBox16
            // 
            this.groupBox16.Controls.Add(this.dgvMercenAward);
            this.groupBox16.Controls.Add(this.button_award_generalRemove);
            this.groupBox16.Controls.Add(this.groupBox54);
            this.groupBox16.Controls.Add(this.button_award_generalAdd);
            this.groupBox16.Controls.Add(this.dataGridView_award_general);
            this.groupBox16.Location = new System.Drawing.Point(12, 6);
            this.groupBox16.Name = "groupBox16";
            this.groupBox16.Size = new System.Drawing.Size(259, 473);
            this.groupBox16.TabIndex = 0;
            this.groupBox16.TabStop = false;
            this.groupBox16.Text = "一般奖励";
            // 
            // dgvMercenAward
            // 
            this.dgvMercenAward.AllowUserToAddRows = false;
            this.dgvMercenAward.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvMercenAward.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn38,
            this.dataGridViewTextBoxColumn39,
            this.pos});
            this.dgvMercenAward.Enabled = false;
            this.dgvMercenAward.Location = new System.Drawing.Point(6, 351);
            this.dgvMercenAward.Name = "dgvMercenAward";
            this.dgvMercenAward.RowHeadersVisible = false;
            this.dgvMercenAward.RowHeadersWidth = 35;
            this.dgvMercenAward.RowTemplate.Height = 23;
            this.dgvMercenAward.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvMercenAward.Size = new System.Drawing.Size(247, 108);
            this.dgvMercenAward.TabIndex = 17;
            // 
            // dataGridViewTextBoxColumn38
            // 
            this.dataGridViewTextBoxColumn38.HeaderText = "奖励佣兵";
            this.dataGridViewTextBoxColumn38.Name = "dataGridViewTextBoxColumn38";
            this.dataGridViewTextBoxColumn38.Width = 82;
            // 
            // dataGridViewTextBoxColumn39
            // 
            this.dataGridViewTextBoxColumn39.HeaderText = "佣兵名称";
            this.dataGridViewTextBoxColumn39.Name = "dataGridViewTextBoxColumn39";
            this.dataGridViewTextBoxColumn39.Width = 81;
            // 
            // pos
            // 
            this.pos.HeaderText = "阵型位置";
            this.pos.Name = "pos";
            this.pos.Width = 80;
            // 
            // button_award_generalRemove
            // 
            this.button_award_generalRemove.Location = new System.Drawing.Point(121, 306);
            this.button_award_generalRemove.Name = "button_award_generalRemove";
            this.button_award_generalRemove.Size = new System.Drawing.Size(75, 23);
            this.button_award_generalRemove.TabIndex = 16;
            this.button_award_generalRemove.Text = "删除";
            this.button_award_generalRemove.UseVisualStyleBackColor = true;
            this.button_award_generalRemove.Click += new System.EventHandler(this.button_award_generalRemove_Click);
            // 
            // groupBox54
            // 
            this.groupBox54.Controls.Add(this.textBox_award_general);
            this.groupBox54.Controls.Add(this.comboBox_award_general);
            this.groupBox54.Controls.Add(this.label23);
            this.groupBox54.Controls.Add(this.label24);
            this.groupBox54.Location = new System.Drawing.Point(18, 37);
            this.groupBox54.Name = "groupBox54";
            this.groupBox54.Size = new System.Drawing.Size(200, 85);
            this.groupBox54.TabIndex = 10;
            this.groupBox54.TabStop = false;
            this.groupBox54.Text = "选择项目";
            // 
            // textBox_award_general
            // 
            this.textBox_award_general.Location = new System.Drawing.Point(73, 51);
            this.textBox_award_general.Name = "textBox_award_general";
            this.textBox_award_general.Size = new System.Drawing.Size(121, 21);
            this.textBox_award_general.TabIndex = 3;
            // 
            // comboBox_award_general
            // 
            this.comboBox_award_general.FormattingEnabled = true;
            this.comboBox_award_general.Location = new System.Drawing.Point(73, 22);
            this.comboBox_award_general.Name = "comboBox_award_general";
            this.comboBox_award_general.Size = new System.Drawing.Size(121, 20);
            this.comboBox_award_general.TabIndex = 2;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(13, 56);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(35, 12);
            this.label23.TabIndex = 1;
            this.label23.Text = "数额:";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(13, 27);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(35, 12);
            this.label24.TabIndex = 0;
            this.label24.Text = "项目:";
            // 
            // button_award_generalAdd
            // 
            this.button_award_generalAdd.Location = new System.Drawing.Point(33, 303);
            this.button_award_generalAdd.Name = "button_award_generalAdd";
            this.button_award_generalAdd.Size = new System.Drawing.Size(75, 23);
            this.button_award_generalAdd.TabIndex = 15;
            this.button_award_generalAdd.Text = "添加";
            this.button_award_generalAdd.UseVisualStyleBackColor = true;
            this.button_award_generalAdd.Click += new System.EventHandler(this.button_award_generalAdd_Click);
            // 
            // dataGridView_award_general
            // 
            this.dataGridView_award_general.AllowUserToAddRows = false;
            this.dataGridView_award_general.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_award_general.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.awardGeneralName,
            this.awardGeneralValue});
            this.dataGridView_award_general.Location = new System.Drawing.Point(18, 146);
            this.dataGridView_award_general.Name = "dataGridView_award_general";
            this.dataGridView_award_general.RowHeadersVisible = false;
            this.dataGridView_award_general.RowTemplate.Height = 23;
            this.dataGridView_award_general.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_award_general.Size = new System.Drawing.Size(200, 141);
            this.dataGridView_award_general.TabIndex = 14;
            // 
            // awardGeneralName
            // 
            this.awardGeneralName.HeaderText = "项目名称";
            this.awardGeneralName.Name = "awardGeneralName";
            this.awardGeneralName.Width = 98;
            // 
            // awardGeneralValue
            // 
            this.awardGeneralValue.HeaderText = "奖励数额";
            this.awardGeneralValue.Name = "awardGeneralValue";
            this.awardGeneralValue.Width = 98;
            // 
            // groupBox53
            // 
            this.groupBox53.Controls.Add(this.button_award_propRemove);
            this.groupBox53.Controls.Add(this.groupBox52);
            this.groupBox53.Controls.Add(this.button_award_propAdd);
            this.groupBox53.Controls.Add(this.groupBox17);
            this.groupBox53.Controls.Add(this.dataGridView_award_prop);
            this.groupBox53.Location = new System.Drawing.Point(822, 13);
            this.groupBox53.Name = "groupBox53";
            this.groupBox53.Size = new System.Drawing.Size(263, 466);
            this.groupBox53.TabIndex = 14;
            this.groupBox53.TabStop = false;
            this.groupBox53.Text = "属性奖励";
            // 
            // button_award_propRemove
            // 
            this.button_award_propRemove.Location = new System.Drawing.Point(137, 436);
            this.button_award_propRemove.Name = "button_award_propRemove";
            this.button_award_propRemove.Size = new System.Drawing.Size(75, 23);
            this.button_award_propRemove.TabIndex = 13;
            this.button_award_propRemove.Text = "删除";
            this.button_award_propRemove.UseVisualStyleBackColor = true;
            this.button_award_propRemove.Click += new System.EventHandler(this.button_award_propRemove_Click);
            // 
            // groupBox52
            // 
            this.groupBox52.Controls.Add(this.textBox_award_roleProp);
            this.groupBox52.Controls.Add(this.comboBox_award_roleProp);
            this.groupBox52.Controls.Add(this.label28);
            this.groupBox52.Controls.Add(this.label29);
            this.groupBox52.Location = new System.Drawing.Point(28, 33);
            this.groupBox52.Name = "groupBox52";
            this.groupBox52.Size = new System.Drawing.Size(200, 85);
            this.groupBox52.TabIndex = 9;
            this.groupBox52.TabStop = false;
            this.groupBox52.Text = "选择属性";
            // 
            // textBox_award_roleProp
            // 
            this.textBox_award_roleProp.Location = new System.Drawing.Point(73, 51);
            this.textBox_award_roleProp.Name = "textBox_award_roleProp";
            this.textBox_award_roleProp.Size = new System.Drawing.Size(121, 21);
            this.textBox_award_roleProp.TabIndex = 3;
            // 
            // comboBox_award_roleProp
            // 
            this.comboBox_award_roleProp.FormattingEnabled = true;
            this.comboBox_award_roleProp.Location = new System.Drawing.Point(73, 22);
            this.comboBox_award_roleProp.Name = "comboBox_award_roleProp";
            this.comboBox_award_roleProp.Size = new System.Drawing.Size(121, 20);
            this.comboBox_award_roleProp.TabIndex = 2;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(13, 56);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(59, 12);
            this.label28.TabIndex = 1;
            this.label28.Text = "奖励数额:";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(13, 27);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(59, 12);
            this.label29.TabIndex = 0;
            this.label29.Text = "角色属性:";
            // 
            // button_award_propAdd
            // 
            this.button_award_propAdd.Location = new System.Drawing.Point(43, 436);
            this.button_award_propAdd.Name = "button_award_propAdd";
            this.button_award_propAdd.Size = new System.Drawing.Size(75, 23);
            this.button_award_propAdd.TabIndex = 12;
            this.button_award_propAdd.Text = "添加";
            this.button_award_propAdd.UseVisualStyleBackColor = true;
            this.button_award_propAdd.Click += new System.EventHandler(this.button_award_propAdd_Click);
            // 
            // groupBox17
            // 
            this.groupBox17.Controls.Add(this.textBox_award_campName);
            this.groupBox17.Controls.Add(this.textBox_award_campID);
            this.groupBox17.Controls.Add(this.label26);
            this.groupBox17.Controls.Add(this.button_award_selectCamp);
            this.groupBox17.Controls.Add(this.label27);
            this.groupBox17.Location = new System.Drawing.Point(28, 134);
            this.groupBox17.Name = "groupBox17";
            this.groupBox17.Size = new System.Drawing.Size(200, 116);
            this.groupBox17.TabIndex = 10;
            this.groupBox17.TabStop = false;
            this.groupBox17.Text = "阵营";
            // 
            // textBox_award_campName
            // 
            this.textBox_award_campName.Location = new System.Drawing.Point(73, 80);
            this.textBox_award_campName.Name = "textBox_award_campName";
            this.textBox_award_campName.Size = new System.Drawing.Size(121, 21);
            this.textBox_award_campName.TabIndex = 6;
            // 
            // textBox_award_campID
            // 
            this.textBox_award_campID.Location = new System.Drawing.Point(73, 53);
            this.textBox_award_campID.Name = "textBox_award_campID";
            this.textBox_award_campID.Size = new System.Drawing.Size(121, 21);
            this.textBox_award_campID.TabIndex = 4;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(13, 85);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(59, 12);
            this.label26.TabIndex = 5;
            this.label26.Text = "阵营名称:";
            // 
            // button_award_selectCamp
            // 
            this.button_award_selectCamp.Location = new System.Drawing.Point(61, 20);
            this.button_award_selectCamp.Name = "button_award_selectCamp";
            this.button_award_selectCamp.Size = new System.Drawing.Size(75, 23);
            this.button_award_selectCamp.TabIndex = 0;
            this.button_award_selectCamp.Text = "选择阵营";
            this.button_award_selectCamp.UseVisualStyleBackColor = true;
            this.button_award_selectCamp.Click += new System.EventHandler(this.button_award_selectCamp_Click);
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(13, 56);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(47, 12);
            this.label27.TabIndex = 4;
            this.label27.Text = "阵营ID:";
            // 
            // dataGridView_award_prop
            // 
            this.dataGridView_award_prop.AllowUserToAddRows = false;
            this.dataGridView_award_prop.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_award_prop.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn30,
            this.dataGridViewTextBoxColumn31});
            this.dataGridView_award_prop.Location = new System.Drawing.Point(28, 265);
            this.dataGridView_award_prop.Name = "dataGridView_award_prop";
            this.dataGridView_award_prop.RowHeadersVisible = false;
            this.dataGridView_award_prop.RowTemplate.Height = 23;
            this.dataGridView_award_prop.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView_award_prop.Size = new System.Drawing.Size(200, 163);
            this.dataGridView_award_prop.TabIndex = 11;
            this.dataGridView_award_prop.SelectionChanged += new System.EventHandler(this.dataGridView_award_prop_SelectionChanged);
            // 
            // dataGridViewTextBoxColumn30
            // 
            this.dataGridViewTextBoxColumn30.HeaderText = "角色属性";
            this.dataGridViewTextBoxColumn30.Name = "dataGridViewTextBoxColumn30";
            this.dataGridViewTextBoxColumn30.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn31
            // 
            this.dataGridViewTextBoxColumn31.HeaderText = "数值需求";
            this.dataGridViewTextBoxColumn31.Name = "dataGridViewTextBoxColumn31";
            this.dataGridViewTextBoxColumn31.ReadOnly = true;
            // 
            // dataGridViewTaskList
            // 
            this.dataGridViewTaskList.AllowUserToAddRows = false;
            this.dataGridViewTaskList.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.dataGridViewTaskList.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTaskList.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.TaskID,
            this.TaskLevel,
            this.TaskName,
            this.TaskType,
            this.OpenState,
            this.ShareState,
            this.CanGiveUp,
            this.RepeatState,
            this.FinishLimit,
            this.AwardLinkLevel});
            this.dataGridViewTaskList.Dock = System.Windows.Forms.DockStyle.Top;
            this.dataGridViewTaskList.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.dataGridViewTaskList.Location = new System.Drawing.Point(0, 0);
            this.dataGridViewTaskList.MultiSelect = false;
            this.dataGridViewTaskList.Name = "dataGridViewTaskList";
            this.dataGridViewTaskList.RowHeadersWidth = 20;
            this.dataGridViewTaskList.RowTemplate.Height = 23;
            this.dataGridViewTaskList.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewTaskList.Size = new System.Drawing.Size(917, 148);
            this.dataGridViewTaskList.TabIndex = 4;
            this.dataGridViewTaskList.ColumnHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridViewTaskList_ColumnHeaderMouseClick);
            this.dataGridViewTaskList.SelectionChanged += new System.EventHandler(this.dataGridViewTaskList_SelectionChanged);
            // 
            // TaskID
            // 
            this.TaskID.HeaderText = "任务ID";
            this.TaskID.Name = "TaskID";
            this.TaskID.Width = 66;
            // 
            // TaskLevel
            // 
            this.TaskLevel.HeaderText = "任务等级";
            this.TaskLevel.Name = "TaskLevel";
            this.TaskLevel.Width = 78;
            // 
            // TaskName
            // 
            this.TaskName.HeaderText = "任务名称";
            this.TaskName.Name = "TaskName";
            this.TaskName.Width = 78;
            // 
            // TaskType
            // 
            this.TaskType.HeaderText = "任务类型";
            this.TaskType.Name = "TaskType";
            this.TaskType.Width = 78;
            // 
            // OpenState
            // 
            this.OpenState.HeaderText = "开放状态";
            this.OpenState.Name = "OpenState";
            this.OpenState.Width = 78;
            // 
            // ShareState
            // 
            this.ShareState.HeaderText = "共享状态";
            this.ShareState.Name = "ShareState";
            this.ShareState.Width = 78;
            // 
            // CanGiveUp
            // 
            this.CanGiveUp.HeaderText = "放弃状态";
            this.CanGiveUp.Name = "CanGiveUp";
            this.CanGiveUp.Width = 78;
            // 
            // RepeatState
            // 
            this.RepeatState.HeaderText = "重复状态";
            this.RepeatState.Name = "RepeatState";
            this.RepeatState.Width = 78;
            // 
            // FinishLimit
            // 
            this.FinishLimit.HeaderText = "完成限制";
            this.FinishLimit.Name = "FinishLimit";
            this.FinishLimit.Width = 78;
            // 
            // AwardLinkLevel
            // 
            this.AwardLinkLevel.HeaderText = "奖励等级相关";
            this.AwardLinkLevel.Name = "AwardLinkLevel";
            // 
            // splitContainerTask
            // 
            this.splitContainerTask.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainerTask.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainerTask.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerTask.Location = new System.Drawing.Point(0, 0);
            this.splitContainerTask.Name = "splitContainerTask";
            this.splitContainerTask.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerTask.Panel1
            // 
            this.splitContainerTask.Panel1.Controls.Add(this.textBoxFolderPath);
            this.splitContainerTask.Panel1.Controls.Add(this.groupBox3);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonSelectFile);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonSelectFolder);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonSaveAllTask);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonOpenAllTask);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonUnloadTask);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonSaveTask);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonOpenTask);
            this.splitContainerTask.Panel1.Controls.Add(this.buttonNewTask);
            this.splitContainerTask.Panel1.Controls.Add(this.panelTaskList);
            // 
            // splitContainerTask.Panel2
            // 
            this.splitContainerTask.Panel2.AutoScroll = true;
            this.splitContainerTask.Panel2.Controls.Add(this.tabControlConfig);
            this.splitContainerTask.Size = new System.Drawing.Size(1230, 746);
            this.splitContainerTask.SplitterDistance = 181;
            this.splitContainerTask.TabIndex = 4;
            // 
            // textBoxFolderPath
            // 
            this.textBoxFolderPath.AllowDrop = true;
            this.textBoxFolderPath.Location = new System.Drawing.Point(10, 5);
            this.textBoxFolderPath.Name = "textBoxFolderPath";
            this.textBoxFolderPath.Size = new System.Drawing.Size(471, 21);
            this.textBoxFolderPath.TabIndex = 0;
            this.textBoxFolderPath.DragEnter += new System.Windows.Forms.DragEventHandler(this.textBoxFolderPath_DragEnter);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.buttonSearchName);
            this.groupBox3.Controls.Add(this.buttonSearchID);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.textBoxSearchTask);
            this.groupBox3.Location = new System.Drawing.Point(988, 8);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(227, 140);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "任务搜索";
            // 
            // buttonSearchName
            // 
            this.buttonSearchName.Location = new System.Drawing.Point(71, 96);
            this.buttonSearchName.Name = "buttonSearchName";
            this.buttonSearchName.Size = new System.Drawing.Size(75, 23);
            this.buttonSearchName.TabIndex = 3;
            this.buttonSearchName.Text = "搜索名称";
            this.buttonSearchName.UseVisualStyleBackColor = true;
            this.buttonSearchName.Click += new System.EventHandler(this.buttonSearchName_Click);
            // 
            // buttonSearchID
            // 
            this.buttonSearchID.Location = new System.Drawing.Point(71, 58);
            this.buttonSearchID.Name = "buttonSearchID";
            this.buttonSearchID.Size = new System.Drawing.Size(75, 23);
            this.buttonSearchID.TabIndex = 2;
            this.buttonSearchID.Text = "搜索ID";
            this.buttonSearchID.UseVisualStyleBackColor = true;
            this.buttonSearchID.Click += new System.EventHandler(this.buttonSearchID_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(14, 25);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "搜索";
            // 
            // textBoxSearchTask
            // 
            this.textBoxSearchTask.Location = new System.Drawing.Point(55, 22);
            this.textBoxSearchTask.Name = "textBoxSearchTask";
            this.textBoxSearchTask.Size = new System.Drawing.Size(149, 21);
            this.textBoxSearchTask.TabIndex = 0;
            // 
            // buttonSelectFile
            // 
            this.buttonSelectFile.Location = new System.Drawing.Point(487, 5);
            this.buttonSelectFile.Name = "buttonSelectFile";
            this.buttonSelectFile.Size = new System.Drawing.Size(75, 21);
            this.buttonSelectFile.TabIndex = 2;
            this.buttonSelectFile.Text = "选择文件";
            this.buttonSelectFile.UseVisualStyleBackColor = true;
            this.buttonSelectFile.Click += new System.EventHandler(this.SelectFile);
            // 
            // buttonSelectFolder
            // 
            this.buttonSelectFolder.Location = new System.Drawing.Point(568, 5);
            this.buttonSelectFolder.Name = "buttonSelectFolder";
            this.buttonSelectFolder.Size = new System.Drawing.Size(75, 21);
            this.buttonSelectFolder.TabIndex = 2;
            this.buttonSelectFolder.Text = "选择文件夹";
            this.buttonSelectFolder.UseVisualStyleBackColor = true;
            this.buttonSelectFolder.Click += new System.EventHandler(this.SelectFolder);
            // 
            // buttonSaveAllTask
            // 
            this.buttonSaveAllTask.Location = new System.Drawing.Point(468, 33);
            this.buttonSaveAllTask.Name = "buttonSaveAllTask";
            this.buttonSaveAllTask.Size = new System.Drawing.Size(86, 21);
            this.buttonSaveAllTask.TabIndex = 2;
            this.buttonSaveAllTask.Text = "保存所有任务";
            this.buttonSaveAllTask.UseVisualStyleBackColor = true;
            this.buttonSaveAllTask.Click += new System.EventHandler(this.SaveAllFile);
            // 
            // buttonOpenAllTask
            // 
            this.buttonOpenAllTask.Location = new System.Drawing.Point(377, 32);
            this.buttonOpenAllTask.Name = "buttonOpenAllTask";
            this.buttonOpenAllTask.Size = new System.Drawing.Size(85, 21);
            this.buttonOpenAllTask.TabIndex = 2;
            this.buttonOpenAllTask.Text = "打开所有任务";
            this.buttonOpenAllTask.UseVisualStyleBackColor = true;
            this.buttonOpenAllTask.Click += new System.EventHandler(this.OpenAllFile);
            // 
            // buttonUnloadTask
            // 
            this.buttonUnloadTask.Location = new System.Drawing.Point(255, 32);
            this.buttonUnloadTask.Name = "buttonUnloadTask";
            this.buttonUnloadTask.Size = new System.Drawing.Size(75, 21);
            this.buttonUnloadTask.TabIndex = 2;
            this.buttonUnloadTask.Text = "移除任务";
            this.buttonUnloadTask.UseVisualStyleBackColor = true;
            this.buttonUnloadTask.Click += new System.EventHandler(this.RemoveTask);
            // 
            // buttonSaveTask
            // 
            this.buttonSaveTask.Location = new System.Drawing.Point(172, 32);
            this.buttonSaveTask.Name = "buttonSaveTask";
            this.buttonSaveTask.Size = new System.Drawing.Size(75, 21);
            this.buttonSaveTask.TabIndex = 2;
            this.buttonSaveTask.Text = "保存任务";
            this.buttonSaveTask.UseVisualStyleBackColor = true;
            this.buttonSaveTask.Click += new System.EventHandler(this.SaveFile);
            // 
            // buttonOpenTask
            // 
            this.buttonOpenTask.Location = new System.Drawing.Point(90, 32);
            this.buttonOpenTask.Name = "buttonOpenTask";
            this.buttonOpenTask.Size = new System.Drawing.Size(75, 21);
            this.buttonOpenTask.TabIndex = 2;
            this.buttonOpenTask.Text = "打开任务";
            this.buttonOpenTask.UseVisualStyleBackColor = true;
            this.buttonOpenTask.Click += new System.EventHandler(this.OpenFile);
            // 
            // buttonNewTask
            // 
            this.buttonNewTask.Location = new System.Drawing.Point(9, 32);
            this.buttonNewTask.Name = "buttonNewTask";
            this.buttonNewTask.Size = new System.Drawing.Size(75, 21);
            this.buttonNewTask.TabIndex = 2;
            this.buttonNewTask.Text = "新增任务";
            this.buttonNewTask.UseVisualStyleBackColor = true;
            this.buttonNewTask.Click += new System.EventHandler(this.buttonNewTask_Click);
            // 
            // panelTaskList
            // 
            this.panelTaskList.Controls.Add(this.dataGridViewTaskList);
            this.panelTaskList.Location = new System.Drawing.Point(7, 59);
            this.panelTaskList.Name = "panelTaskList";
            this.panelTaskList.Size = new System.Drawing.Size(917, 148);
            this.panelTaskList.TabIndex = 1;
            // 
            // dataGridView2
            // 
            this.dataGridView2.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn1,
            this.dataGridViewTextBoxColumn2,
            this.dataGridViewTextBoxColumn3,
            this.dataGridViewTextBoxColumn4,
            this.dataGridViewTextBoxColumn5,
            this.dataGridViewTextBoxColumn6});
            this.dataGridView2.Location = new System.Drawing.Point(240, 41);
            this.dataGridView2.MultiSelect = false;
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersVisible = false;
            this.dataGridView2.RowTemplate.Height = 23;
            this.dataGridView2.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView2.Size = new System.Drawing.Size(418, 210);
            this.dataGridView2.TabIndex = 5;
            // 
            // dataGridViewTextBoxColumn1
            // 
            this.dataGridViewTextBoxColumn1.HeaderText = "地图ID";
            this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
            this.dataGridViewTextBoxColumn1.Width = 66;
            // 
            // dataGridViewTextBoxColumn2
            // 
            this.dataGridViewTextBoxColumn2.HeaderText = "地图名称";
            this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
            this.dataGridViewTextBoxColumn2.Width = 78;
            // 
            // dataGridViewTextBoxColumn3
            // 
            this.dataGridViewTextBoxColumn3.HeaderText = "X1坐标";
            this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
            this.dataGridViewTextBoxColumn3.Width = 66;
            // 
            // dataGridViewTextBoxColumn4
            // 
            this.dataGridViewTextBoxColumn4.HeaderText = "Z1坐标";
            this.dataGridViewTextBoxColumn4.Name = "dataGridViewTextBoxColumn4";
            this.dataGridViewTextBoxColumn4.Width = 66;
            // 
            // dataGridViewTextBoxColumn5
            // 
            this.dataGridViewTextBoxColumn5.HeaderText = "X2坐标";
            this.dataGridViewTextBoxColumn5.Name = "dataGridViewTextBoxColumn5";
            this.dataGridViewTextBoxColumn5.Width = 66;
            // 
            // dataGridViewTextBoxColumn6
            // 
            this.dataGridViewTextBoxColumn6.HeaderText = "Z2坐标";
            this.dataGridViewTextBoxColumn6.Name = "dataGridViewTextBoxColumn6";
            this.dataGridViewTextBoxColumn6.Width = 66;
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(129, 284);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(75, 23);
            this.button6.TabIndex = 4;
            this.button6.Text = "删除";
            this.button6.UseVisualStyleBackColor = true;
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(33, 284);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(75, 23);
            this.button7.TabIndex = 3;
            this.button7.Text = "添加";
            this.button7.UseVisualStyleBackColor = true;
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(103, 36);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(75, 23);
            this.button8.TabIndex = 2;
            this.button8.Text = "Select";
            this.button8.UseVisualStyleBackColor = true;
            // 
            // textBox16
            // 
            this.textBox16.Location = new System.Drawing.Point(100, 246);
            this.textBox16.Name = "textBox16";
            this.textBox16.Size = new System.Drawing.Size(87, 21);
            this.textBox16.TabIndex = 1;
            // 
            // textBox17
            // 
            this.textBox17.Location = new System.Drawing.Point(100, 212);
            this.textBox17.Name = "textBox17";
            this.textBox17.Size = new System.Drawing.Size(87, 21);
            this.textBox17.TabIndex = 1;
            // 
            // textBox18
            // 
            this.textBox18.Location = new System.Drawing.Point(100, 178);
            this.textBox18.Name = "textBox18";
            this.textBox18.Size = new System.Drawing.Size(87, 21);
            this.textBox18.TabIndex = 1;
            // 
            // textBox19
            // 
            this.textBox19.Location = new System.Drawing.Point(100, 144);
            this.textBox19.Name = "textBox19";
            this.textBox19.Size = new System.Drawing.Size(87, 21);
            this.textBox19.TabIndex = 1;
            // 
            // textBox27
            // 
            this.textBox27.Location = new System.Drawing.Point(100, 110);
            this.textBox27.Name = "textBox27";
            this.textBox27.Size = new System.Drawing.Size(87, 21);
            this.textBox27.TabIndex = 1;
            // 
            // textBox28
            // 
            this.textBox28.Location = new System.Drawing.Point(100, 76);
            this.textBox28.Name = "textBox28";
            this.textBox28.Size = new System.Drawing.Size(87, 21);
            this.textBox28.TabIndex = 1;
            // 
            // label74
            // 
            this.label74.AutoSize = true;
            this.label74.Location = new System.Drawing.Point(31, 250);
            this.label74.Name = "label74";
            this.label74.Size = new System.Drawing.Size(41, 12);
            this.label74.TabIndex = 0;
            this.label74.Text = "Z2坐标";
            // 
            // label75
            // 
            this.label75.AutoSize = true;
            this.label75.Location = new System.Drawing.Point(31, 216);
            this.label75.Name = "label75";
            this.label75.Size = new System.Drawing.Size(41, 12);
            this.label75.TabIndex = 0;
            this.label75.Text = "X2坐标";
            // 
            // label76
            // 
            this.label76.AutoSize = true;
            this.label76.Location = new System.Drawing.Point(31, 182);
            this.label76.Name = "label76";
            this.label76.Size = new System.Drawing.Size(41, 12);
            this.label76.TabIndex = 0;
            this.label76.Text = "Z1坐标";
            // 
            // label77
            // 
            this.label77.AutoSize = true;
            this.label77.Location = new System.Drawing.Point(31, 148);
            this.label77.Name = "label77";
            this.label77.Size = new System.Drawing.Size(41, 12);
            this.label77.TabIndex = 0;
            this.label77.Text = "X1坐标";
            // 
            // label78
            // 
            this.label78.AutoSize = true;
            this.label78.Location = new System.Drawing.Point(31, 114);
            this.label78.Name = "label78";
            this.label78.Size = new System.Drawing.Size(53, 12);
            this.label78.TabIndex = 0;
            this.label78.Text = "地图名称";
            // 
            // label79
            // 
            this.label79.AutoSize = true;
            this.label79.Location = new System.Drawing.Point(31, 80);
            this.label79.Name = "label79";
            this.label79.Size = new System.Drawing.Size(41, 12);
            this.label79.TabIndex = 0;
            this.label79.Text = "地图ID";
            // 
            // label80
            // 
            this.label80.AutoSize = true;
            this.label80.Location = new System.Drawing.Point(31, 41);
            this.label80.Name = "label80";
            this.label80.Size = new System.Drawing.Size(53, 12);
            this.label80.TabIndex = 0;
            this.label80.Text = "区域选择";
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(129, 284);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(75, 23);
            this.button9.TabIndex = 4;
            this.button9.Text = "删除";
            this.button9.UseVisualStyleBackColor = true;
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(33, 284);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(75, 23);
            this.button10.TabIndex = 3;
            this.button10.Text = "添加";
            this.button10.UseVisualStyleBackColor = true;
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(103, 36);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(75, 23);
            this.button11.TabIndex = 2;
            this.button11.Text = "Select";
            this.button11.UseVisualStyleBackColor = true;
            // 
            // textBox29
            // 
            this.textBox29.Location = new System.Drawing.Point(100, 246);
            this.textBox29.Name = "textBox29";
            this.textBox29.Size = new System.Drawing.Size(87, 21);
            this.textBox29.TabIndex = 1;
            // 
            // textBox30
            // 
            this.textBox30.Location = new System.Drawing.Point(100, 212);
            this.textBox30.Name = "textBox30";
            this.textBox30.Size = new System.Drawing.Size(87, 21);
            this.textBox30.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox34);
            this.tabPage1.Controls.Add(this.groupBox35);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(873, 548);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "综合设定";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox34
            // 
            this.groupBox34.Controls.Add(this.dataGridView3);
            this.groupBox34.Controls.Add(this.button12);
            this.groupBox34.Controls.Add(this.button13);
            this.groupBox34.Controls.Add(this.textBox31);
            this.groupBox34.Controls.Add(this.textBox32);
            this.groupBox34.Controls.Add(this.textBox33);
            this.groupBox34.Controls.Add(this.label81);
            this.groupBox34.Controls.Add(this.label82);
            this.groupBox34.Controls.Add(this.label83);
            this.groupBox34.Controls.Add(this.label84);
            this.groupBox34.Controls.Add(this.button14);
            this.groupBox34.Location = new System.Drawing.Point(28, 157);
            this.groupBox34.Name = "groupBox34";
            this.groupBox34.Size = new System.Drawing.Size(634, 239);
            this.groupBox34.TabIndex = 1;
            this.groupBox34.TabStop = false;
            this.groupBox34.Text = "道具给予";
            // 
            // dataGridView3
            // 
            this.dataGridView3.AllowUserToAddRows = false;
            this.dataGridView3.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView3.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView3.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn7,
            this.dataGridViewTextBoxColumn8,
            this.dataGridViewTextBoxColumn9});
            this.dataGridView3.Location = new System.Drawing.Point(247, 64);
            this.dataGridView3.Name = "dataGridView3";
            this.dataGridView3.RowHeadersVisible = false;
            this.dataGridView3.RowTemplate.Height = 23;
            this.dataGridView3.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView3.Size = new System.Drawing.Size(217, 142);
            this.dataGridView3.TabIndex = 6;
            // 
            // dataGridViewTextBoxColumn7
            // 
            this.dataGridViewTextBoxColumn7.HeaderText = "道具ID";
            this.dataGridViewTextBoxColumn7.Name = "dataGridViewTextBoxColumn7";
            this.dataGridViewTextBoxColumn7.Width = 66;
            // 
            // dataGridViewTextBoxColumn8
            // 
            this.dataGridViewTextBoxColumn8.HeaderText = "道具名称";
            this.dataGridViewTextBoxColumn8.Name = "dataGridViewTextBoxColumn8";
            this.dataGridViewTextBoxColumn8.Width = 78;
            // 
            // dataGridViewTextBoxColumn9
            // 
            this.dataGridViewTextBoxColumn9.HeaderText = "数量";
            this.dataGridViewTextBoxColumn9.Name = "dataGridViewTextBoxColumn9";
            this.dataGridViewTextBoxColumn9.Width = 54;
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(125, 184);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(75, 23);
            this.button12.TabIndex = 5;
            this.button12.Text = "删除";
            this.button12.UseVisualStyleBackColor = true;
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(23, 184);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(75, 23);
            this.button13.TabIndex = 5;
            this.button13.Text = "添加";
            this.button13.UseVisualStyleBackColor = true;
            // 
            // textBox31
            // 
            this.textBox31.Location = new System.Drawing.Point(87, 152);
            this.textBox31.Name = "textBox31";
            this.textBox31.Size = new System.Drawing.Size(113, 21);
            this.textBox31.TabIndex = 4;
            // 
            // textBox32
            // 
            this.textBox32.Location = new System.Drawing.Point(87, 77);
            this.textBox32.Name = "textBox32";
            this.textBox32.Size = new System.Drawing.Size(113, 21);
            this.textBox32.TabIndex = 3;
            // 
            // textBox33
            // 
            this.textBox33.Location = new System.Drawing.Point(87, 115);
            this.textBox33.Name = "textBox33";
            this.textBox33.Size = new System.Drawing.Size(113, 21);
            this.textBox33.TabIndex = 3;
            // 
            // label81
            // 
            this.label81.AutoSize = true;
            this.label81.Location = new System.Drawing.Point(21, 82);
            this.label81.Name = "label81";
            this.label81.Size = new System.Drawing.Size(41, 12);
            this.label81.TabIndex = 2;
            this.label81.Text = "道具ID";
            // 
            // label82
            // 
            this.label82.AutoSize = true;
            this.label82.Location = new System.Drawing.Point(21, 155);
            this.label82.Name = "label82";
            this.label82.Size = new System.Drawing.Size(53, 12);
            this.label82.TabIndex = 2;
            this.label82.Text = "给予数量";
            // 
            // label83
            // 
            this.label83.AutoSize = true;
            this.label83.Location = new System.Drawing.Point(21, 119);
            this.label83.Name = "label83";
            this.label83.Size = new System.Drawing.Size(53, 12);
            this.label83.TabIndex = 2;
            this.label83.Text = "道具名称";
            // 
            // label84
            // 
            this.label84.AutoSize = true;
            this.label84.Location = new System.Drawing.Point(21, 45);
            this.label84.Name = "label84";
            this.label84.Size = new System.Drawing.Size(53, 12);
            this.label84.TabIndex = 1;
            this.label84.Text = "道具选择";
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(85, 40);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(75, 23);
            this.button14.TabIndex = 0;
            this.button14.Text = "Select";
            this.button14.UseVisualStyleBackColor = true;
            // 
            // groupBox35
            // 
            this.groupBox35.Controls.Add(this.label85);
            this.groupBox35.Controls.Add(this.textBox34);
            this.groupBox35.Controls.Add(this.label86);
            this.groupBox35.Location = new System.Drawing.Point(30, 33);
            this.groupBox35.Name = "groupBox35";
            this.groupBox35.Size = new System.Drawing.Size(243, 81);
            this.groupBox35.TabIndex = 0;
            this.groupBox35.TabStop = false;
            this.groupBox35.Text = "设定时限";
            // 
            // label85
            // 
            this.label85.AutoSize = true;
            this.label85.Location = new System.Drawing.Point(199, 39);
            this.label85.Name = "label85";
            this.label85.Size = new System.Drawing.Size(17, 12);
            this.label85.TabIndex = 2;
            this.label85.Text = "秒";
            // 
            // textBox34
            // 
            this.textBox34.Location = new System.Drawing.Point(94, 36);
            this.textBox34.Name = "textBox34";
            this.textBox34.Size = new System.Drawing.Size(88, 21);
            this.textBox34.TabIndex = 1;
            // 
            // label86
            // 
            this.label86.AutoSize = true;
            this.label86.Location = new System.Drawing.Point(19, 39);
            this.label86.Name = "label86";
            this.label86.Size = new System.Drawing.Size(53, 12);
            this.label86.TabIndex = 0;
            this.label86.Text = "倒计限时";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.groupBox36);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(873, 548);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "猎杀";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // groupBox36
            // 
            this.groupBox36.Controls.Add(this.dataGridView4);
            this.groupBox36.Controls.Add(this.button15);
            this.groupBox36.Controls.Add(this.button16);
            this.groupBox36.Controls.Add(this.label87);
            this.groupBox36.Controls.Add(this.textBox35);
            this.groupBox36.Controls.Add(this.textBox36);
            this.groupBox36.Controls.Add(this.textBox37);
            this.groupBox36.Controls.Add(this.label88);
            this.groupBox36.Controls.Add(this.label89);
            this.groupBox36.Controls.Add(this.button17);
            this.groupBox36.Controls.Add(this.label90);
            this.groupBox36.Location = new System.Drawing.Point(36, 49);
            this.groupBox36.Name = "groupBox36";
            this.groupBox36.Size = new System.Drawing.Size(490, 244);
            this.groupBox36.TabIndex = 0;
            this.groupBox36.TabStop = false;
            this.groupBox36.Text = "猎杀";
            // 
            // dataGridView4
            // 
            this.dataGridView4.AllowUserToAddRows = false;
            this.dataGridView4.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView4.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView4.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn10,
            this.dataGridViewTextBoxColumn11,
            this.dataGridViewTextBoxColumn12});
            this.dataGridView4.Location = new System.Drawing.Point(219, 71);
            this.dataGridView4.Name = "dataGridView4";
            this.dataGridView4.RowHeadersVisible = false;
            this.dataGridView4.RowTemplate.Height = 23;
            this.dataGridView4.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView4.Size = new System.Drawing.Size(227, 130);
            this.dataGridView4.TabIndex = 7;
            // 
            // dataGridViewTextBoxColumn10
            // 
            this.dataGridViewTextBoxColumn10.HeaderText = "怪物ID";
            this.dataGridViewTextBoxColumn10.Name = "dataGridViewTextBoxColumn10";
            this.dataGridViewTextBoxColumn10.Width = 66;
            // 
            // dataGridViewTextBoxColumn11
            // 
            this.dataGridViewTextBoxColumn11.HeaderText = "怪物名称 ";
            this.dataGridViewTextBoxColumn11.Name = "dataGridViewTextBoxColumn11";
            this.dataGridViewTextBoxColumn11.Width = 78;
            // 
            // dataGridViewTextBoxColumn12
            // 
            this.dataGridViewTextBoxColumn12.HeaderText = "击杀数量";
            this.dataGridViewTextBoxColumn12.Name = "dataGridViewTextBoxColumn12";
            this.dataGridViewTextBoxColumn12.Width = 78;
            // 
            // button15
            // 
            this.button15.Location = new System.Drawing.Point(107, 179);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(75, 23);
            this.button15.TabIndex = 6;
            this.button15.Text = "删除";
            this.button15.UseVisualStyleBackColor = true;
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(25, 179);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(75, 23);
            this.button16.TabIndex = 6;
            this.button16.Text = "添加";
            this.button16.UseVisualStyleBackColor = true;
            // 
            // label87
            // 
            this.label87.AutoSize = true;
            this.label87.Location = new System.Drawing.Point(17, 149);
            this.label87.Name = "label87";
            this.label87.Size = new System.Drawing.Size(53, 12);
            this.label87.TabIndex = 5;
            this.label87.Text = "击杀数量";
            // 
            // textBox35
            // 
            this.textBox35.Location = new System.Drawing.Point(87, 146);
            this.textBox35.Name = "textBox35";
            this.textBox35.Size = new System.Drawing.Size(95, 21);
            this.textBox35.TabIndex = 4;
            // 
            // textBox36
            // 
            this.textBox36.Location = new System.Drawing.Point(88, 78);
            this.textBox36.Name = "textBox36";
            this.textBox36.Size = new System.Drawing.Size(95, 21);
            this.textBox36.TabIndex = 3;
            // 
            // textBox37
            // 
            this.textBox37.Location = new System.Drawing.Point(87, 112);
            this.textBox37.Name = "textBox37";
            this.textBox37.Size = new System.Drawing.Size(95, 21);
            this.textBox37.TabIndex = 3;
            // 
            // label88
            // 
            this.label88.AutoSize = true;
            this.label88.Location = new System.Drawing.Point(18, 81);
            this.label88.Name = "label88";
            this.label88.Size = new System.Drawing.Size(41, 12);
            this.label88.TabIndex = 2;
            this.label88.Text = "怪物ID";
            // 
            // label89
            // 
            this.label89.AutoSize = true;
            this.label89.Location = new System.Drawing.Point(17, 115);
            this.label89.Name = "label89";
            this.label89.Size = new System.Drawing.Size(53, 12);
            this.label89.TabIndex = 2;
            this.label89.Text = "怪物名称";
            // 
            // button17
            // 
            this.button17.Location = new System.Drawing.Point(87, 36);
            this.button17.Name = "button17";
            this.button17.Size = new System.Drawing.Size(75, 23);
            this.button17.TabIndex = 1;
            this.button17.Text = "Select";
            this.button17.UseVisualStyleBackColor = true;
            // 
            // label90
            // 
            this.label90.AutoSize = true;
            this.label90.Location = new System.Drawing.Point(17, 41);
            this.label90.Name = "label90";
            this.label90.Size = new System.Drawing.Size(53, 12);
            this.label90.TabIndex = 0;
            this.label90.Text = "怪物选择";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.groupBox37);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(873, 548);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "收集";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // groupBox37
            // 
            this.groupBox37.Controls.Add(this.dataGridView5);
            this.groupBox37.Controls.Add(this.button18);
            this.groupBox37.Controls.Add(this.button22);
            this.groupBox37.Controls.Add(this.textBox38);
            this.groupBox37.Controls.Add(this.textBox39);
            this.groupBox37.Controls.Add(this.textBox40);
            this.groupBox37.Controls.Add(this.label91);
            this.groupBox37.Controls.Add(this.label92);
            this.groupBox37.Controls.Add(this.label93);
            this.groupBox37.Controls.Add(this.button23);
            this.groupBox37.Controls.Add(this.label94);
            this.groupBox37.Location = new System.Drawing.Point(34, 47);
            this.groupBox37.Name = "groupBox37";
            this.groupBox37.Size = new System.Drawing.Size(504, 229);
            this.groupBox37.TabIndex = 0;
            this.groupBox37.TabStop = false;
            this.groupBox37.Text = "收集";
            // 
            // dataGridView5
            // 
            this.dataGridView5.AllowUserToAddRows = false;
            this.dataGridView5.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView5.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView5.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn13,
            this.dataGridViewTextBoxColumn14,
            this.dataGridViewTextBoxColumn15});
            this.dataGridView5.Location = new System.Drawing.Point(237, 46);
            this.dataGridView5.Name = "dataGridView5";
            this.dataGridView5.RowHeadersVisible = false;
            this.dataGridView5.RowTemplate.Height = 23;
            this.dataGridView5.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView5.Size = new System.Drawing.Size(230, 150);
            this.dataGridView5.TabIndex = 6;
            // 
            // dataGridViewTextBoxColumn13
            // 
            this.dataGridViewTextBoxColumn13.HeaderText = "道具ID";
            this.dataGridViewTextBoxColumn13.Name = "dataGridViewTextBoxColumn13";
            this.dataGridViewTextBoxColumn13.Width = 66;
            // 
            // dataGridViewTextBoxColumn14
            // 
            this.dataGridViewTextBoxColumn14.HeaderText = "道具名称";
            this.dataGridViewTextBoxColumn14.Name = "dataGridViewTextBoxColumn14";
            this.dataGridViewTextBoxColumn14.Width = 78;
            // 
            // dataGridViewTextBoxColumn15
            // 
            this.dataGridViewTextBoxColumn15.HeaderText = "搜集数量";
            this.dataGridViewTextBoxColumn15.Name = "dataGridViewTextBoxColumn15";
            this.dataGridViewTextBoxColumn15.Width = 78;
            // 
            // button18
            // 
            this.button18.Location = new System.Drawing.Point(119, 183);
            this.button18.Name = "button18";
            this.button18.Size = new System.Drawing.Size(75, 23);
            this.button18.TabIndex = 5;
            this.button18.Text = "删除";
            this.button18.UseVisualStyleBackColor = true;
            // 
            // button22
            // 
            this.button22.Location = new System.Drawing.Point(19, 183);
            this.button22.Name = "button22";
            this.button22.Size = new System.Drawing.Size(75, 23);
            this.button22.TabIndex = 4;
            this.button22.Text = "添加";
            this.button22.UseVisualStyleBackColor = true;
            // 
            // textBox38
            // 
            this.textBox38.Location = new System.Drawing.Point(100, 144);
            this.textBox38.Name = "textBox38";
            this.textBox38.Size = new System.Drawing.Size(94, 21);
            this.textBox38.TabIndex = 3;
            // 
            // textBox39
            // 
            this.textBox39.Location = new System.Drawing.Point(102, 74);
            this.textBox39.Name = "textBox39";
            this.textBox39.Size = new System.Drawing.Size(94, 21);
            this.textBox39.TabIndex = 3;
            // 
            // textBox40
            // 
            this.textBox40.Location = new System.Drawing.Point(101, 110);
            this.textBox40.Name = "textBox40";
            this.textBox40.Size = new System.Drawing.Size(94, 21);
            this.textBox40.TabIndex = 3;
            // 
            // label91
            // 
            this.label91.AutoSize = true;
            this.label91.Location = new System.Drawing.Point(29, 147);
            this.label91.Name = "label91";
            this.label91.Size = new System.Drawing.Size(53, 12);
            this.label91.TabIndex = 2;
            this.label91.Text = "搜集数量";
            // 
            // label92
            // 
            this.label92.AutoSize = true;
            this.label92.Location = new System.Drawing.Point(28, 78);
            this.label92.Name = "label92";
            this.label92.Size = new System.Drawing.Size(41, 12);
            this.label92.TabIndex = 2;
            this.label92.Text = "道具ID";
            // 
            // label93
            // 
            this.label93.AutoSize = true;
            this.label93.Location = new System.Drawing.Point(27, 114);
            this.label93.Name = "label93";
            this.label93.Size = new System.Drawing.Size(53, 12);
            this.label93.TabIndex = 2;
            this.label93.Text = "道具名称";
            // 
            // button23
            // 
            this.button23.Location = new System.Drawing.Point(100, 38);
            this.button23.Name = "button23";
            this.button23.Size = new System.Drawing.Size(75, 23);
            this.button23.TabIndex = 1;
            this.button23.Text = "Select";
            this.button23.UseVisualStyleBackColor = true;
            // 
            // label94
            // 
            this.label94.AutoSize = true;
            this.label94.Location = new System.Drawing.Point(29, 43);
            this.label94.Name = "label94";
            this.label94.Size = new System.Drawing.Size(53, 12);
            this.label94.TabIndex = 0;
            this.label94.Text = "道具选择";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.groupBox38);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(873, 548);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "探索";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // groupBox38
            // 
            this.groupBox38.Controls.Add(this.dataGridView7);
            this.groupBox38.Controls.Add(this.button9);
            this.groupBox38.Controls.Add(this.button10);
            this.groupBox38.Controls.Add(this.button11);
            this.groupBox38.Controls.Add(this.textBox29);
            this.groupBox38.Controls.Add(this.textBox30);
            this.groupBox38.Controls.Add(this.textBox41);
            this.groupBox38.Controls.Add(this.textBox42);
            this.groupBox38.Controls.Add(this.textBox43);
            this.groupBox38.Controls.Add(this.textBox44);
            this.groupBox38.Controls.Add(this.label95);
            this.groupBox38.Controls.Add(this.label96);
            this.groupBox38.Controls.Add(this.label97);
            this.groupBox38.Controls.Add(this.label98);
            this.groupBox38.Controls.Add(this.label99);
            this.groupBox38.Controls.Add(this.label100);
            this.groupBox38.Controls.Add(this.label101);
            this.groupBox38.Location = new System.Drawing.Point(34, 34);
            this.groupBox38.Name = "groupBox38";
            this.groupBox38.Size = new System.Drawing.Size(691, 323);
            this.groupBox38.TabIndex = 0;
            this.groupBox38.TabStop = false;
            this.groupBox38.Text = "探索";
            // 
            // dataGridView7
            // 
            this.dataGridView7.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView7.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView7.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn16,
            this.dataGridViewTextBoxColumn17,
            this.dataGridViewTextBoxColumn18,
            this.dataGridViewTextBoxColumn19,
            this.dataGridViewTextBoxColumn20,
            this.dataGridViewTextBoxColumn21});
            this.dataGridView7.Location = new System.Drawing.Point(240, 41);
            this.dataGridView7.MultiSelect = false;
            this.dataGridView7.Name = "dataGridView7";
            this.dataGridView7.RowHeadersVisible = false;
            this.dataGridView7.RowTemplate.Height = 23;
            this.dataGridView7.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView7.Size = new System.Drawing.Size(418, 210);
            this.dataGridView7.TabIndex = 5;
            // 
            // dataGridViewTextBoxColumn16
            // 
            this.dataGridViewTextBoxColumn16.HeaderText = "地图ID";
            this.dataGridViewTextBoxColumn16.Name = "dataGridViewTextBoxColumn16";
            this.dataGridViewTextBoxColumn16.Width = 66;
            // 
            // dataGridViewTextBoxColumn17
            // 
            this.dataGridViewTextBoxColumn17.HeaderText = "地图名称";
            this.dataGridViewTextBoxColumn17.Name = "dataGridViewTextBoxColumn17";
            this.dataGridViewTextBoxColumn17.Width = 78;
            // 
            // dataGridViewTextBoxColumn18
            // 
            this.dataGridViewTextBoxColumn18.HeaderText = "X1坐标";
            this.dataGridViewTextBoxColumn18.Name = "dataGridViewTextBoxColumn18";
            this.dataGridViewTextBoxColumn18.Width = 66;
            // 
            // dataGridViewTextBoxColumn19
            // 
            this.dataGridViewTextBoxColumn19.HeaderText = "Z1坐标";
            this.dataGridViewTextBoxColumn19.Name = "dataGridViewTextBoxColumn19";
            this.dataGridViewTextBoxColumn19.Width = 66;
            // 
            // dataGridViewTextBoxColumn20
            // 
            this.dataGridViewTextBoxColumn20.HeaderText = "X2坐标";
            this.dataGridViewTextBoxColumn20.Name = "dataGridViewTextBoxColumn20";
            this.dataGridViewTextBoxColumn20.Width = 66;
            // 
            // dataGridViewTextBoxColumn21
            // 
            this.dataGridViewTextBoxColumn21.HeaderText = "Z2坐标";
            this.dataGridViewTextBoxColumn21.Name = "dataGridViewTextBoxColumn21";
            this.dataGridViewTextBoxColumn21.Width = 66;
            // 
            // textBox41
            // 
            this.textBox41.Location = new System.Drawing.Point(100, 178);
            this.textBox41.Name = "textBox41";
            this.textBox41.Size = new System.Drawing.Size(87, 21);
            this.textBox41.TabIndex = 1;
            // 
            // textBox42
            // 
            this.textBox42.Location = new System.Drawing.Point(100, 144);
            this.textBox42.Name = "textBox42";
            this.textBox42.Size = new System.Drawing.Size(87, 21);
            this.textBox42.TabIndex = 1;
            // 
            // textBox43
            // 
            this.textBox43.Location = new System.Drawing.Point(100, 110);
            this.textBox43.Name = "textBox43";
            this.textBox43.Size = new System.Drawing.Size(87, 21);
            this.textBox43.TabIndex = 1;
            // 
            // textBox44
            // 
            this.textBox44.Location = new System.Drawing.Point(100, 76);
            this.textBox44.Name = "textBox44";
            this.textBox44.Size = new System.Drawing.Size(87, 21);
            this.textBox44.TabIndex = 1;
            // 
            // label95
            // 
            this.label95.AutoSize = true;
            this.label95.Location = new System.Drawing.Point(31, 250);
            this.label95.Name = "label95";
            this.label95.Size = new System.Drawing.Size(41, 12);
            this.label95.TabIndex = 0;
            this.label95.Text = "Z2坐标";
            // 
            // label96
            // 
            this.label96.AutoSize = true;
            this.label96.Location = new System.Drawing.Point(31, 216);
            this.label96.Name = "label96";
            this.label96.Size = new System.Drawing.Size(41, 12);
            this.label96.TabIndex = 0;
            this.label96.Text = "X2坐标";
            // 
            // label97
            // 
            this.label97.AutoSize = true;
            this.label97.Location = new System.Drawing.Point(31, 182);
            this.label97.Name = "label97";
            this.label97.Size = new System.Drawing.Size(41, 12);
            this.label97.TabIndex = 0;
            this.label97.Text = "Z1坐标";
            // 
            // label98
            // 
            this.label98.AutoSize = true;
            this.label98.Location = new System.Drawing.Point(31, 148);
            this.label98.Name = "label98";
            this.label98.Size = new System.Drawing.Size(41, 12);
            this.label98.TabIndex = 0;
            this.label98.Text = "X1坐标";
            // 
            // label99
            // 
            this.label99.AutoSize = true;
            this.label99.Location = new System.Drawing.Point(31, 114);
            this.label99.Name = "label99";
            this.label99.Size = new System.Drawing.Size(53, 12);
            this.label99.TabIndex = 0;
            this.label99.Text = "地图名称";
            // 
            // label100
            // 
            this.label100.AutoSize = true;
            this.label100.Location = new System.Drawing.Point(31, 80);
            this.label100.Name = "label100";
            this.label100.Size = new System.Drawing.Size(41, 12);
            this.label100.TabIndex = 0;
            this.label100.Text = "地图ID";
            // 
            // label101
            // 
            this.label101.AutoSize = true;
            this.label101.Location = new System.Drawing.Point(31, 41);
            this.label101.Name = "label101";
            this.label101.Size = new System.Drawing.Size(53, 12);
            this.label101.TabIndex = 0;
            this.label101.Text = "区域选择";
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.groupBox39);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage5.Size = new System.Drawing.Size(873, 548);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "使用道具/技能";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // groupBox39
            // 
            this.groupBox39.Location = new System.Drawing.Point(40, 42);
            this.groupBox39.Name = "groupBox39";
            this.groupBox39.Size = new System.Drawing.Size(617, 348);
            this.groupBox39.TabIndex = 0;
            this.groupBox39.TabStop = false;
            this.groupBox39.Text = "使用道具/技能";
            // 
            // tabPage6
            // 
            this.tabPage6.Controls.Add(this.groupBox40);
            this.tabPage6.Controls.Add(this.groupBox41);
            this.tabPage6.Controls.Add(this.groupBox42);
            this.tabPage6.Controls.Add(this.groupBox43);
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(873, 548);
            this.tabPage6.TabIndex = 5;
            this.tabPage6.Text = "互动对话/递送";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // groupBox40
            // 
            this.groupBox40.Controls.Add(this.dataGridView8);
            this.groupBox40.Controls.Add(this.textBox45);
            this.groupBox40.Controls.Add(this.textBox46);
            this.groupBox40.Controls.Add(this.textBox47);
            this.groupBox40.Controls.Add(this.label102);
            this.groupBox40.Controls.Add(this.label103);
            this.groupBox40.Controls.Add(this.label104);
            this.groupBox40.Controls.Add(this.button24);
            this.groupBox40.Controls.Add(this.button25);
            this.groupBox40.Controls.Add(this.button26);
            this.groupBox40.Controls.Add(this.label105);
            this.groupBox40.Location = new System.Drawing.Point(20, 352);
            this.groupBox40.Name = "groupBox40";
            this.groupBox40.Size = new System.Drawing.Size(406, 175);
            this.groupBox40.TabIndex = 3;
            this.groupBox40.TabStop = false;
            this.groupBox40.Text = "收取道具";
            // 
            // dataGridView8
            // 
            this.dataGridView8.AllowUserToAddRows = false;
            this.dataGridView8.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView8.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView8.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn22,
            this.dataGridViewTextBoxColumn23,
            this.dataGridViewTextBoxColumn24});
            this.dataGridView8.Location = new System.Drawing.Point(170, 23);
            this.dataGridView8.MultiSelect = false;
            this.dataGridView8.Name = "dataGridView8";
            this.dataGridView8.RowHeadersVisible = false;
            this.dataGridView8.RowTemplate.Height = 23;
            this.dataGridView8.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView8.Size = new System.Drawing.Size(226, 145);
            this.dataGridView8.TabIndex = 4;
            // 
            // dataGridViewTextBoxColumn22
            // 
            this.dataGridViewTextBoxColumn22.HeaderText = "道具ID";
            this.dataGridViewTextBoxColumn22.Name = "dataGridViewTextBoxColumn22";
            this.dataGridViewTextBoxColumn22.Width = 66;
            // 
            // dataGridViewTextBoxColumn23
            // 
            this.dataGridViewTextBoxColumn23.HeaderText = "道具名称";
            this.dataGridViewTextBoxColumn23.Name = "dataGridViewTextBoxColumn23";
            this.dataGridViewTextBoxColumn23.Width = 78;
            // 
            // dataGridViewTextBoxColumn24
            // 
            this.dataGridViewTextBoxColumn24.HeaderText = "收集数量";
            this.dataGridViewTextBoxColumn24.Name = "dataGridViewTextBoxColumn24";
            this.dataGridViewTextBoxColumn24.Width = 78;
            // 
            // textBox45
            // 
            this.textBox45.Location = new System.Drawing.Point(62, 111);
            this.textBox45.Name = "textBox45";
            this.textBox45.Size = new System.Drawing.Size(97, 21);
            this.textBox45.TabIndex = 3;
            // 
            // textBox46
            // 
            this.textBox46.Location = new System.Drawing.Point(62, 82);
            this.textBox46.Name = "textBox46";
            this.textBox46.Size = new System.Drawing.Size(97, 21);
            this.textBox46.TabIndex = 3;
            // 
            // textBox47
            // 
            this.textBox47.Location = new System.Drawing.Point(62, 53);
            this.textBox47.Name = "textBox47";
            this.textBox47.Size = new System.Drawing.Size(97, 21);
            this.textBox47.TabIndex = 3;
            // 
            // label102
            // 
            this.label102.AutoSize = true;
            this.label102.Location = new System.Drawing.Point(9, 116);
            this.label102.Name = "label102";
            this.label102.Size = new System.Drawing.Size(53, 12);
            this.label102.TabIndex = 2;
            this.label102.Text = "收集数量";
            // 
            // label103
            // 
            this.label103.AutoSize = true;
            this.label103.Location = new System.Drawing.Point(9, 87);
            this.label103.Name = "label103";
            this.label103.Size = new System.Drawing.Size(53, 12);
            this.label103.TabIndex = 2;
            this.label103.Text = "道具名称";
            // 
            // label104
            // 
            this.label104.AutoSize = true;
            this.label104.Location = new System.Drawing.Point(9, 58);
            this.label104.Name = "label104";
            this.label104.Size = new System.Drawing.Size(41, 12);
            this.label104.TabIndex = 2;
            this.label104.Text = "道具ID";
            // 
            // button24
            // 
            this.button24.Location = new System.Drawing.Point(87, 143);
            this.button24.Name = "button24";
            this.button24.Size = new System.Drawing.Size(67, 23);
            this.button24.TabIndex = 1;
            this.button24.Text = "删除";
            this.button24.UseVisualStyleBackColor = true;
            // 
            // button25
            // 
            this.button25.Location = new System.Drawing.Point(10, 143);
            this.button25.Name = "button25";
            this.button25.Size = new System.Drawing.Size(60, 23);
            this.button25.TabIndex = 1;
            this.button25.Text = "添加";
            this.button25.UseVisualStyleBackColor = true;
            // 
            // button26
            // 
            this.button26.Location = new System.Drawing.Point(71, 21);
            this.button26.Name = "button26";
            this.button26.Size = new System.Drawing.Size(75, 23);
            this.button26.TabIndex = 1;
            this.button26.Text = "Select";
            this.button26.UseVisualStyleBackColor = true;
            // 
            // label105
            // 
            this.label105.AutoSize = true;
            this.label105.Location = new System.Drawing.Point(9, 26);
            this.label105.Name = "label105";
            this.label105.Size = new System.Drawing.Size(53, 12);
            this.label105.TabIndex = 0;
            this.label105.Text = "道具选择";
            // 
            // groupBox41
            // 
            this.groupBox41.Controls.Add(this.label106);
            this.groupBox41.Controls.Add(this.label107);
            this.groupBox41.Controls.Add(this.button27);
            this.groupBox41.Controls.Add(this.button28);
            this.groupBox41.Controls.Add(this.textBox48);
            this.groupBox41.Controls.Add(this.textBox49);
            this.groupBox41.Location = new System.Drawing.Point(462, 20);
            this.groupBox41.Name = "groupBox41";
            this.groupBox41.Size = new System.Drawing.Size(347, 507);
            this.groupBox41.TabIndex = 2;
            this.groupBox41.TabStop = false;
            this.groupBox41.Text = "台词";
            // 
            // label106
            // 
            this.label106.AutoSize = true;
            this.label106.Location = new System.Drawing.Point(21, 245);
            this.label106.Name = "label106";
            this.label106.Size = new System.Drawing.Size(47, 12);
            this.label106.TabIndex = 4;
            this.label106.Text = "NPC台词";
            // 
            // label107
            // 
            this.label107.AutoSize = true;
            this.label107.Location = new System.Drawing.Point(21, 20);
            this.label107.Name = "label107";
            this.label107.Size = new System.Drawing.Size(41, 12);
            this.label107.TabIndex = 4;
            this.label107.Text = "PC台词";
            // 
            // button27
            // 
            this.button27.Location = new System.Drawing.Point(186, 473);
            this.button27.Name = "button27";
            this.button27.Size = new System.Drawing.Size(75, 23);
            this.button27.TabIndex = 3;
            this.button27.Text = "更新";
            this.button27.UseVisualStyleBackColor = true;
            // 
            // button28
            // 
            this.button28.Location = new System.Drawing.Point(65, 473);
            this.button28.Name = "button28";
            this.button28.Size = new System.Drawing.Size(75, 23);
            this.button28.TabIndex = 3;
            this.button28.Text = "添加";
            this.button28.UseVisualStyleBackColor = true;
            // 
            // textBox48
            // 
            this.textBox48.Location = new System.Drawing.Point(18, 264);
            this.textBox48.Multiline = true;
            this.textBox48.Name = "textBox48";
            this.textBox48.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox48.Size = new System.Drawing.Size(313, 198);
            this.textBox48.TabIndex = 1;
            // 
            // textBox49
            // 
            this.textBox49.Location = new System.Drawing.Point(18, 40);
            this.textBox49.Multiline = true;
            this.textBox49.Name = "textBox49";
            this.textBox49.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox49.Size = new System.Drawing.Size(313, 198);
            this.textBox49.TabIndex = 0;
            // 
            // groupBox42
            // 
            this.groupBox42.Controls.Add(this.button29);
            this.groupBox42.Controls.Add(this.button30);
            this.groupBox42.Controls.Add(this.button31);
            this.groupBox42.Controls.Add(this.dataGridView9);
            this.groupBox42.Location = new System.Drawing.Point(20, 184);
            this.groupBox42.Name = "groupBox42";
            this.groupBox42.Size = new System.Drawing.Size(381, 158);
            this.groupBox42.TabIndex = 1;
            this.groupBox42.TabStop = false;
            this.groupBox42.Text = "台词预览";
            // 
            // button29
            // 
            this.button29.Location = new System.Drawing.Point(321, 105);
            this.button29.Name = "button29";
            this.button29.Size = new System.Drawing.Size(49, 23);
            this.button29.TabIndex = 3;
            this.button29.Text = "删除";
            this.button29.UseVisualStyleBackColor = true;
            // 
            // button30
            // 
            this.button30.Location = new System.Drawing.Point(321, 75);
            this.button30.Name = "button30";
            this.button30.Size = new System.Drawing.Size(49, 24);
            this.button30.TabIndex = 1;
            this.button30.Text = "下移";
            this.button30.UseVisualStyleBackColor = true;
            // 
            // button31
            // 
            this.button31.Location = new System.Drawing.Point(321, 45);
            this.button31.Name = "button31";
            this.button31.Size = new System.Drawing.Size(49, 24);
            this.button31.TabIndex = 1;
            this.button31.Text = "上移";
            this.button31.UseVisualStyleBackColor = true;
            // 
            // dataGridView9
            // 
            this.dataGridView9.AllowUserToAddRows = false;
            this.dataGridView9.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView9.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView9.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn25,
            this.dataGridViewTextBoxColumn26,
            this.dataGridViewTextBoxColumn27});
            this.dataGridView9.Location = new System.Drawing.Point(10, 22);
            this.dataGridView9.MultiSelect = false;
            this.dataGridView9.Name = "dataGridView9";
            this.dataGridView9.RowHeadersVisible = false;
            this.dataGridView9.RowTemplate.Height = 23;
            this.dataGridView9.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView9.Size = new System.Drawing.Size(305, 125);
            this.dataGridView9.TabIndex = 0;
            // 
            // dataGridViewTextBoxColumn25
            // 
            this.dataGridViewTextBoxColumn25.HeaderText = "编号";
            this.dataGridViewTextBoxColumn25.Name = "dataGridViewTextBoxColumn25";
            this.dataGridViewTextBoxColumn25.Width = 54;
            // 
            // dataGridViewTextBoxColumn26
            // 
            this.dataGridViewTextBoxColumn26.HeaderText = "PC台词";
            this.dataGridViewTextBoxColumn26.Name = "dataGridViewTextBoxColumn26";
            this.dataGridViewTextBoxColumn26.Width = 66;
            // 
            // dataGridViewTextBoxColumn27
            // 
            this.dataGridViewTextBoxColumn27.HeaderText = "NPC台词";
            this.dataGridViewTextBoxColumn27.Name = "dataGridViewTextBoxColumn27";
            this.dataGridViewTextBoxColumn27.Width = 72;
            // 
            // groupBox43
            // 
            this.groupBox43.Controls.Add(this.button32);
            this.groupBox43.Controls.Add(this.button33);
            this.groupBox43.Controls.Add(this.dataGridView10);
            this.groupBox43.Controls.Add(this.textBox50);
            this.groupBox43.Controls.Add(this.label108);
            this.groupBox43.Controls.Add(this.textBox51);
            this.groupBox43.Controls.Add(this.label109);
            this.groupBox43.Controls.Add(this.button34);
            this.groupBox43.Controls.Add(this.label110);
            this.groupBox43.Location = new System.Drawing.Point(20, 20);
            this.groupBox43.Name = "groupBox43";
            this.groupBox43.Size = new System.Drawing.Size(381, 153);
            this.groupBox43.TabIndex = 0;
            this.groupBox43.TabStop = false;
            this.groupBox43.Text = "目标选择";
            // 
            // button32
            // 
            this.button32.Location = new System.Drawing.Point(87, 116);
            this.button32.Name = "button32";
            this.button32.Size = new System.Drawing.Size(60, 23);
            this.button32.TabIndex = 5;
            this.button32.Text = "删除";
            this.button32.UseVisualStyleBackColor = true;
            // 
            // button33
            // 
            this.button33.Location = new System.Drawing.Point(11, 116);
            this.button33.Name = "button33";
            this.button33.Size = new System.Drawing.Size(60, 23);
            this.button33.TabIndex = 5;
            this.button33.Text = "添加";
            this.button33.UseVisualStyleBackColor = true;
            // 
            // dataGridView10
            // 
            this.dataGridView10.AllowUserToAddRows = false;
            this.dataGridView10.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView10.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView10.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn28,
            this.dataGridViewTextBoxColumn29});
            this.dataGridView10.Location = new System.Drawing.Point(165, 18);
            this.dataGridView10.MultiSelect = false;
            this.dataGridView10.Name = "dataGridView10";
            this.dataGridView10.RowHeadersVisible = false;
            this.dataGridView10.RowTemplate.Height = 23;
            this.dataGridView10.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView10.Size = new System.Drawing.Size(210, 129);
            this.dataGridView10.TabIndex = 4;
            // 
            // dataGridViewTextBoxColumn28
            // 
            this.dataGridViewTextBoxColumn28.HeaderText = "目标ID";
            this.dataGridViewTextBoxColumn28.Name = "dataGridViewTextBoxColumn28";
            this.dataGridViewTextBoxColumn28.Width = 66;
            // 
            // dataGridViewTextBoxColumn29
            // 
            this.dataGridViewTextBoxColumn29.HeaderText = "目标名称";
            this.dataGridViewTextBoxColumn29.Name = "dataGridViewTextBoxColumn29";
            this.dataGridViewTextBoxColumn29.Width = 78;
            // 
            // textBox50
            // 
            this.textBox50.Location = new System.Drawing.Point(59, 85);
            this.textBox50.Name = "textBox50";
            this.textBox50.Size = new System.Drawing.Size(100, 21);
            this.textBox50.TabIndex = 3;
            // 
            // label108
            // 
            this.label108.AutoSize = true;
            this.label108.Location = new System.Drawing.Point(6, 88);
            this.label108.Name = "label108";
            this.label108.Size = new System.Drawing.Size(47, 12);
            this.label108.TabIndex = 2;
            this.label108.Text = "NPC名称";
            // 
            // textBox51
            // 
            this.textBox51.Location = new System.Drawing.Point(59, 56);
            this.textBox51.Name = "textBox51";
            this.textBox51.Size = new System.Drawing.Size(100, 21);
            this.textBox51.TabIndex = 3;
            // 
            // label109
            // 
            this.label109.AutoSize = true;
            this.label109.Location = new System.Drawing.Point(6, 59);
            this.label109.Name = "label109";
            this.label109.Size = new System.Drawing.Size(41, 12);
            this.label109.TabIndex = 2;
            this.label109.Text = "NPC ID";
            // 
            // button34
            // 
            this.button34.Location = new System.Drawing.Point(59, 26);
            this.button34.Name = "button34";
            this.button34.Size = new System.Drawing.Size(75, 23);
            this.button34.TabIndex = 1;
            this.button34.Text = "Select";
            this.button34.UseVisualStyleBackColor = true;
            // 
            // label110
            // 
            this.label110.AutoSize = true;
            this.label110.Location = new System.Drawing.Point(6, 31);
            this.label110.Name = "label110";
            this.label110.Size = new System.Drawing.Size(47, 12);
            this.label110.TabIndex = 0;
            this.label110.Text = "NPC选择";
            // 
            // tabPage7
            // 
            this.tabPage7.Location = new System.Drawing.Point(4, 22);
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage7.Size = new System.Drawing.Size(873, 548);
            this.tabPage7.TabIndex = 6;
            this.tabPage7.Text = "护送";
            this.tabPage7.UseVisualStyleBackColor = true;
            // 
            // FormEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1230, 746);
            this.Controls.Add(this.splitContainerTask);
            this.Name = "FormEditor";
            this.Text = "任务编辑器";
            this.tabControlConfig.ResumeLayout(false);
            this.tabPageBasic.ResumeLayout(false);
            this.groupBox63.ResumeLayout(false);
            this.groupBox63.PerformLayout();
            this.groupBox44.ResumeLayout(false);
            this.groupBox44.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTaskSubmit)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTaskStart)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox46.ResumeLayout(false);
            this.groupBox46.PerformLayout();
            this.groupBox33.ResumeLayout(false);
            this.groupBox33.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabPageDesc.ResumeLayout(false);
            this.groupBox11.ResumeLayout(false);
            this.groupBox10.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.tabPageLimit.ResumeLayout(false);
            this.groupBox59.ResumeLayout(false);
            this.groupBox59.PerformLayout();
            this.groupBox56.ResumeLayout(false);
            this.groupBox57.ResumeLayout(false);
            this.groupBox57.PerformLayout();
            this.groupBox58.ResumeLayout(false);
            this.groupBox58.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_limit_prop)).EndInit();
            this.groupBox31.ResumeLayout(false);
            this.groupBox31.PerformLayout();
            this.groupBox55.ResumeLayout(false);
            this.groupBox55.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewPreTask)).EndInit();
            this.groupBox30.ResumeLayout(false);
            this.groupBox30.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewJobLimit)).EndInit();
            this.groupBox29.ResumeLayout(false);
            this.groupBox28.ResumeLayout(false);
            this.groupBox27.ResumeLayout(false);
            this.groupBox27.PerformLayout();
            this.groupBox26.ResumeLayout(false);
            this.groupBox26.PerformLayout();
            this.groupBox25.ResumeLayout(false);
            this.groupBox25.PerformLayout();
            this.groupBox23.ResumeLayout(false);
            this.groupBox23.PerformLayout();
            this.tabPageProc.ResumeLayout(false);
            this.tabControlProcess.ResumeLayout(false);
            this.tabPageGeneral.ResumeLayout(false);
            this.groupBox13.ResumeLayout(false);
            this.groupBox13.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewGiveItem)).EndInit();
            this.groupBox12.ResumeLayout(false);
            this.groupBox12.PerformLayout();
            this.tabPageKill.ResumeLayout(false);
            this.groupBox14.ResumeLayout(false);
            this.groupBox14.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewKillMonster)).EndInit();
            this.tabPageGrow.ResumeLayout(false);
            this.tabPageGrow.PerformLayout();
            this.groupBox64.ResumeLayout(false);
            this.groupBox64.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_grow)).EndInit();
            this.groupBox48.ResumeLayout(false);
            this.groupBox48.PerformLayout();
            this.groupBox47.ResumeLayout(false);
            this.groupBox47.PerformLayout();
            this.tabPageCollect.ResumeLayout(false);
            this.groupBox60.ResumeLayout(false);
            this.groupBox60.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvKillMonsterItem)).EndInit();
            this.groupBox15.ResumeLayout(false);
            this.groupBox15.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCollectItem)).EndInit();
            this.tabPageGather.ResumeLayout(false);
            this.groupBox45.ResumeLayout(false);
            this.groupBox45.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewGather)).EndInit();
            this.tabPageProbe.ResumeLayout(false);
            this.groupBox32.ResumeLayout(false);
            this.groupBox32.PerformLayout();
            this.groupBox62.ResumeLayout(false);
            this.groupBox62.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewProbe)).EndInit();
            this.tabPageBehave.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_behave)).EndInit();
            this.groupBox50.ResumeLayout(false);
            this.groupBox50.PerformLayout();
            this.tabPageBuild.ResumeLayout(false);
            this.groupBox51.ResumeLayout(false);
            this.groupBox51.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_build)).EndInit();
            this.groupBox49.ResumeLayout(false);
            this.groupBox49.PerformLayout();
            this.tabPageTalk.ResumeLayout(false);
            this.groupBox24.ResumeLayout(false);
            this.groupBox24.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewReceiveItem)).EndInit();
            this.groupBoxNpcTalk.ResumeLayout(false);
            this.groupBoxNpcTalk.PerformLayout();
            this.groupBox22.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTalkWords)).EndInit();
            this.groupBox21.ResumeLayout(false);
            this.groupBox21.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewNpcTalk)).EndInit();
            this.tabPageAward.ResumeLayout(false);
            this.groupBox20.ResumeLayout(false);
            this.groupBox20.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewOptItem)).EndInit();
            this.groupBox19.ResumeLayout(false);
            this.groupBox19.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMustItem)).EndInit();
            this.groupBox18.ResumeLayout(false);
            this.groupBox18.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTitle)).EndInit();
            this.groupBox16.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvMercenAward)).EndInit();
            this.groupBox54.ResumeLayout(false);
            this.groupBox54.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_award_general)).EndInit();
            this.groupBox53.ResumeLayout(false);
            this.groupBox52.ResumeLayout(false);
            this.groupBox52.PerformLayout();
            this.groupBox17.ResumeLayout(false);
            this.groupBox17.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_award_prop)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTaskList)).EndInit();
            this.splitContainerTask.Panel1.ResumeLayout(false);
            this.splitContainerTask.Panel1.PerformLayout();
            this.splitContainerTask.Panel2.ResumeLayout(false);
            this.splitContainerTask.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.panelTaskList.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.tabPage1.ResumeLayout(false);
            this.groupBox34.ResumeLayout(false);
            this.groupBox34.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView3)).EndInit();
            this.groupBox35.ResumeLayout(false);
            this.groupBox35.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.groupBox36.ResumeLayout(false);
            this.groupBox36.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView4)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.groupBox37.ResumeLayout(false);
            this.groupBox37.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView5)).EndInit();
            this.tabPage4.ResumeLayout(false);
            this.groupBox38.ResumeLayout(false);
            this.groupBox38.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView7)).EndInit();
            this.tabPage5.ResumeLayout(false);
            this.tabPage6.ResumeLayout(false);
            this.groupBox40.ResumeLayout(false);
            this.groupBox40.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView8)).EndInit();
            this.groupBox41.ResumeLayout(false);
            this.groupBox41.PerformLayout();
            this.groupBox42.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView9)).EndInit();
            this.groupBox43.ResumeLayout(false);
            this.groupBox43.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView10)).EndInit();
            this.ResumeLayout(false);

        }

        public System.Windows.Forms.DataGridView GetTaskListGridView()
        {
            return dataGridViewTaskList;
        }

        #endregion

        private System.Windows.Forms.TabControl tabControlConfig;
        private System.Windows.Forms.TabPage tabPageBasic;
        private System.Windows.Forms.TabPage tabPageDesc;
        private System.Windows.Forms.DataGridView dataGridViewTaskList;
        private System.Windows.Forms.TabPage tabPageLimit;
        private System.Windows.Forms.TabPage tabPageAward;
        private System.Windows.Forms.TabPage tabPageProc;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxTaskID;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxTaskName;
        private System.Windows.Forms.TextBox textBoxTaskLevel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxTaskType;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkBoxIsOpen;
        private System.Windows.Forms.CheckBox checkBoxIsShared;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBoxTaskStart;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxTaskStartID;
        private System.Windows.Forms.TextBox textBoxTaskStartName;
        private System.Windows.Forms.DataGridView dataGridViewTaskStart;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox comboBoxTaskSubmit;
        private System.Windows.Forms.Button buttonTaskSubmit;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxTaskSubmitID;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxTaskSubmitName;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.CheckBox checkBoxKill;
        private System.Windows.Forms.CheckBox checkBoxCollect;
        private System.Windows.Forms.CheckBox checkBoxProbe;
        private System.Windows.Forms.CheckBox checkBoxTalk;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Button buttonInsertName;
        private System.Windows.Forms.Button buttonInsertClan;
        private System.Windows.Forms.Button buttonInsertMonsterID;
        private System.Windows.Forms.Button buttonInsertNpcID;
        private System.Windows.Forms.TabControl tabControlProcess;
        private System.Windows.Forms.TabPage tabPageGeneral;
        private System.Windows.Forms.TabPage tabPageKill;
        private System.Windows.Forms.TabPage tabPageCollect;
        private System.Windows.Forms.TabPage tabPageProbe;
        private System.Windows.Forms.TabPage tabPageTalk;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textBoxLimitTime;
        private System.Windows.Forms.GroupBox groupBox13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button buttonGiveItem;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox textBoxGiveItemName;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox textBoxGiveItemCount;
        private System.Windows.Forms.Button buttonGiveItemAdd;
        private System.Windows.Forms.Button buttonGiveItemDel;
        private System.Windows.Forms.DataGridView dataGridViewGiveItem;
        private System.Windows.Forms.GroupBox groupBox14;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button buttonKillMonster;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox textBoxKillMonsterName;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox textBoxKillMonsterCount;
        private System.Windows.Forms.Button buttonKillMonsterAdd;
        private System.Windows.Forms.Button buttonKillMonsterDel;
        private System.Windows.Forms.DataGridView dataGridViewKillMonster;
        private System.Windows.Forms.GroupBox groupBox15;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Button buttonCollectItem;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.TextBox textBoxCollectItemName;
        private System.Windows.Forms.TextBox textBoxCollectItemCount;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Button buttonCollectItemAdd;
        private System.Windows.Forms.Button buttonCollectItemDel;
        private System.Windows.Forms.DataGridView dataGridViewCollectItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn CollectItemID;
        private System.Windows.Forms.DataGridViewTextBoxColumn CollectItemName;
        private System.Windows.Forms.DataGridViewTextBoxColumn CollectItemCount;
        private System.Windows.Forms.DataGridViewTextBoxColumn GiveItemID;
        private System.Windows.Forms.DataGridViewTextBoxColumn GiveItemName;
        private System.Windows.Forms.DataGridViewTextBoxColumn GiveItemCount;
        private System.Windows.Forms.GroupBox groupBox16;
        private System.Windows.Forms.GroupBox groupBox18;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Button buttonAddTitle;
        private System.Windows.Forms.TextBox textBoxTitleID;
        private System.Windows.Forms.Button buttonDelTitle;
        private System.Windows.Forms.DataGridView dataGridViewTitle;
        private System.Windows.Forms.DataGridViewTextBoxColumn TitleID;
        private System.Windows.Forms.DataGridViewTextBoxColumn TitleName;
        private System.Windows.Forms.GroupBox groupBox19;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Button buttonMustItem;
        private System.Windows.Forms.TextBox textBoxMustItemName;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.TextBox textBoxMustItemCount;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.DataGridView dataGridViewMustItem;
        private System.Windows.Forms.GroupBox groupBox20;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Button buttonOptItem;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.TextBox textBoxOptItemID;
        private System.Windows.Forms.TextBox textBoxOptItemCount;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.DataGridView dataGridViewOptItem;
        private System.Windows.Forms.Button buttonMustItemDel;
        private System.Windows.Forms.Button buttonMustItemAdd;
        private System.Windows.Forms.Button buttonOptItemAdd;
        private System.Windows.Forms.Button buttonOptItemDel;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.TextBox textBoxRepeatCount;
        private System.Windows.Forms.Button buttonTaskStart;
        private System.Windows.Forms.Button buttonTaskStartDel;
        private System.Windows.Forms.Button buttonTaskStartAdd;
        private System.Windows.Forms.DataGridView dataGridViewTaskSubmit;
        private System.Windows.Forms.Button buttonTaskSubmitDel;
        private System.Windows.Forms.Button buttonTaskSubmitAdd;
        private System.Windows.Forms.TextBox textBoxGiveItemID;
        private System.Windows.Forms.Label label39;
        private System.Windows.Forms.TextBox textBoxKillMonsterID;
        private System.Windows.Forms.Label label40;
        private System.Windows.Forms.TextBox textBoxCollectItemID;
        private System.Windows.Forms.Label label41;
        private System.Windows.Forms.DataGridViewTextBoxColumn SubmitTargetID;
        private System.Windows.Forms.DataGridViewTextBoxColumn SubmitTargetType;
        private System.Windows.Forms.DataGridViewTextBoxColumn SubmitTargetName;
        private System.Windows.Forms.DataGridViewTextBoxColumn StartTargetID;
        private System.Windows.Forms.DataGridViewTextBoxColumn StartTargetType;
        private System.Windows.Forms.DataGridViewTextBoxColumn StartTargetName;
        private System.Windows.Forms.TextBox textBoxTitleName;
        private System.Windows.Forms.Label label42;
        private System.Windows.Forms.TextBox textBoxMustItemID;
        private System.Windows.Forms.Label label43;
        private System.Windows.Forms.TextBox textBoxOptItemName;
        private System.Windows.Forms.Label label44;
        private System.Windows.Forms.SplitContainer splitContainerTask;
        private System.Windows.Forms.Panel panelTaskList;
        private System.Windows.Forms.Button buttonNewTask;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxSearchTask;
        private System.Windows.Forms.Button buttonSearchName;
        private System.Windows.Forms.Button buttonSearchID;
        private System.Windows.Forms.GroupBox groupBox21;
        private System.Windows.Forms.Button buttonNpcTalk;
        private System.Windows.Forms.Label label45;
        private System.Windows.Forms.Label label46;
        private System.Windows.Forms.TextBox textBoxNpcTalkName;
        private System.Windows.Forms.Label label47;
        private System.Windows.Forms.TextBox textBoxNpcTalkID;
        private System.Windows.Forms.DataGridView dataGridViewNpcTalk;
        private System.Windows.Forms.DataGridViewTextBoxColumn NpcTalkID;
        private System.Windows.Forms.DataGridViewTextBoxColumn NpcTalkName;
        private System.Windows.Forms.GroupBox groupBox22;
        private System.Windows.Forms.DataGridView dataGridViewTalkWords;
        private System.Windows.Forms.DataGridViewTextBoxColumn Index;
        private System.Windows.Forms.DataGridViewTextBoxColumn PCWords;
        private System.Windows.Forms.DataGridViewTextBoxColumn NPCWords;
        private System.Windows.Forms.GroupBox groupBoxNpcTalk;
        private System.Windows.Forms.TextBox textBoxNPCWords;
        private System.Windows.Forms.TextBox textBoxPCWords;
        private System.Windows.Forms.Button buttonDelTalkWords;
        private System.Windows.Forms.Button buttonAddTalkWords;
        private System.Windows.Forms.Button buttonAddTalkNpc;
        private System.Windows.Forms.Button buttonDelTalkNpc;
        private System.Windows.Forms.GroupBox groupBox24;
        private System.Windows.Forms.TextBox textBoxReceiveItemID;
        private System.Windows.Forms.Label label49;
        private System.Windows.Forms.Button buttonReceiveItem;
        private System.Windows.Forms.Label label48;
        private System.Windows.Forms.TextBox textBoxReceiveItemCount;
        private System.Windows.Forms.TextBox textBoxReceiveItemName;
        private System.Windows.Forms.Label label51;
        private System.Windows.Forms.Label label50;
        private System.Windows.Forms.Button buttonReceiveItemAdd;
        private System.Windows.Forms.Button buttonReceiveItemDel;
        private System.Windows.Forms.DataGridView dataGridViewReceiveItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn ReveiveItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn ReceiveName;
        private System.Windows.Forms.DataGridViewTextBoxColumn ReceiveCount;
        private System.Windows.Forms.Button buttonUpNpcWords;
        private System.Windows.Forms.Button buttonDownNpcWords;
        private System.Windows.Forms.Button buttonOpenTask;
        private System.Windows.Forms.Button buttonOpenAllTask;
        private System.Windows.Forms.TextBox textBoxFolderPath;
        private System.Windows.Forms.Button buttonSelectFolder;
        private System.Windows.Forms.Button buttonSaveAllTask;
        private System.Windows.Forms.Button buttonSaveTask;
        private System.Windows.Forms.Label label52;
        private System.Windows.Forms.Label label53;
        private System.Windows.Forms.Button buttonUpdateTalkWords;
        private System.Windows.Forms.Button buttonChooseColor;
        private System.Windows.Forms.RichTextBox textBoxTaskDesc;
        private System.Windows.Forms.RichTextBox textBoxTaskPurpose;
        private System.Windows.Forms.RichTextBox textBoxTaskFail;
        private System.Windows.Forms.RichTextBox textBoxTaskFinish;
        private System.Windows.Forms.Button buttonSelectFile;
        private System.Windows.Forms.RichTextBox richTextBoxAward;
        private System.Windows.Forms.GroupBox groupBox23;
        private System.Windows.Forms.Label label54;
        private System.Windows.Forms.ComboBox comboBoxSexLimit;
        private System.Windows.Forms.Label label55;
        private System.Windows.Forms.TextBox textBoxReputeMax;
        private System.Windows.Forms.TextBox textBoxReputeMin;
        private System.Windows.Forms.Label label56;
        private System.Windows.Forms.GroupBox groupBox25;
        private System.Windows.Forms.Label label57;
        private System.Windows.Forms.Label label58;
        private System.Windows.Forms.DateTimePicker dateTimePickerDateFrom;
        private System.Windows.Forms.DateTimePicker dateTimePickerDateTo;
        private System.Windows.Forms.CheckBox checkBoxDateLimit;
        private System.Windows.Forms.CheckBox checkBoxTimeLimit;
        private System.Windows.Forms.TextBox textBoxHourTo;
        private System.Windows.Forms.TextBox textBoxHourFrom;
        private System.Windows.Forms.Label label59;
        private System.Windows.Forms.GroupBox groupBox26;
        private System.Windows.Forms.TextBox textBoxGradeMax;
        private System.Windows.Forms.TextBox textBoxGradeMin;
        private System.Windows.Forms.Label label60;
        private System.Windows.Forms.Label label61;
        private System.Windows.Forms.GroupBox groupBox27;
        private System.Windows.Forms.Label label62;
        private System.Windows.Forms.ComboBox comboBoxRelationLimit;
        private System.Windows.Forms.GroupBox groupBox28;
        private System.Windows.Forms.GroupBox groupBox29;
        private System.Windows.Forms.GroupBox groupBox30;
        private System.Windows.Forms.Label label63;
        private System.Windows.Forms.DataGridView dataGridViewJobLimit;
        private System.Windows.Forms.DataGridViewTextBoxColumn JobID;
        private System.Windows.Forms.DataGridViewTextBoxColumn JobName;
        private System.Windows.Forms.GroupBox groupBox31;
        private System.Windows.Forms.Label label64;
        private System.Windows.Forms.Button buttonSelectPreTask;
        private System.Windows.Forms.Label label65;
        private System.Windows.Forms.TextBox textBoxPreTaskID;
        private System.Windows.Forms.Label label66;
        private System.Windows.Forms.TextBox textBoxPreTaskName;
        private System.Windows.Forms.DataGridView dataGridViewPreTask;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumnTaskID;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumnTaskName;
        private System.Windows.Forms.GroupBox groupBox32;
        private System.Windows.Forms.Label label67;
        private System.Windows.Forms.TextBox textBoxProbeMapID;
        private System.Windows.Forms.Label label68;
        private System.Windows.Forms.Button buttonSelectProbe;
        private System.Windows.Forms.TextBox textBoxProbeZ2;
        private System.Windows.Forms.TextBox textBoxProbeX2;
        private System.Windows.Forms.TextBox textBoxProbeZ1;
        private System.Windows.Forms.TextBox textBoxProbeX1;
        private System.Windows.Forms.TextBox textBoxProbeMapName;
        private System.Windows.Forms.Label label73;
        private System.Windows.Forms.Label label72;
        private System.Windows.Forms.Label label71;
        private System.Windows.Forms.Label label70;
        private System.Windows.Forms.Label label69;
        private System.Windows.Forms.Button buttonAddProbe;
        private System.Windows.Forms.Button buttonDelProbe;
        private System.Windows.Forms.DataGridView dataGridViewProbe;
        private System.Windows.Forms.DataGridViewTextBoxColumn MapID;
        private System.Windows.Forms.DataGridViewTextBoxColumn MapName;
        private System.Windows.Forms.DataGridViewTextBoxColumn CoordinateX1;
        private System.Windows.Forms.DataGridViewTextBoxColumn CoordinateZ1;
        private System.Windows.Forms.DataGridViewTextBoxColumn CoordinateX2;
        private System.Windows.Forms.DataGridViewTextBoxColumn CoordinateZ2;
        private System.Windows.Forms.DataGridViewTextBoxColumn CoordinateParam;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn4;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn5;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn6;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.TextBox textBox16;
        private System.Windows.Forms.TextBox textBox17;
        private System.Windows.Forms.TextBox textBox18;
        private System.Windows.Forms.TextBox textBox19;
        private System.Windows.Forms.TextBox textBox27;
        private System.Windows.Forms.TextBox textBox28;
        private System.Windows.Forms.Label label74;
        private System.Windows.Forms.Label label75;
        private System.Windows.Forms.Label label76;
        private System.Windows.Forms.Label label77;
        private System.Windows.Forms.Label label78;
        private System.Windows.Forms.Label label79;
        private System.Windows.Forms.Label label80;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.TextBox textBox29;
        private System.Windows.Forms.TextBox textBox30;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox groupBox34;
        private System.Windows.Forms.DataGridView dataGridView3;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn7;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn8;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn9;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.TextBox textBox31;
        private System.Windows.Forms.TextBox textBox32;
        private System.Windows.Forms.TextBox textBox33;
        private System.Windows.Forms.Label label81;
        private System.Windows.Forms.Label label82;
        private System.Windows.Forms.Label label83;
        private System.Windows.Forms.Label label84;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.GroupBox groupBox35;
        private System.Windows.Forms.Label label85;
        private System.Windows.Forms.TextBox textBox34;
        private System.Windows.Forms.Label label86;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox groupBox36;
        private System.Windows.Forms.DataGridView dataGridView4;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn10;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn11;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn12;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.Label label87;
        private System.Windows.Forms.TextBox textBox35;
        private System.Windows.Forms.TextBox textBox36;
        private System.Windows.Forms.TextBox textBox37;
        private System.Windows.Forms.Label label88;
        private System.Windows.Forms.Label label89;
        private System.Windows.Forms.Button button17;
        private System.Windows.Forms.Label label90;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.GroupBox groupBox37;
        private System.Windows.Forms.DataGridView dataGridView5;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn13;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn14;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn15;
        private System.Windows.Forms.Button button18;
        private System.Windows.Forms.Button button22;
        private System.Windows.Forms.TextBox textBox38;
        private System.Windows.Forms.TextBox textBox39;
        private System.Windows.Forms.TextBox textBox40;
        private System.Windows.Forms.Label label91;
        private System.Windows.Forms.Label label92;
        private System.Windows.Forms.Label label93;
        private System.Windows.Forms.Button button23;
        private System.Windows.Forms.Label label94;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.GroupBox groupBox38;
        private System.Windows.Forms.DataGridView dataGridView7;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn16;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn17;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn18;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn19;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn20;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn21;
        private System.Windows.Forms.TextBox textBox41;
        private System.Windows.Forms.TextBox textBox42;
        private System.Windows.Forms.TextBox textBox43;
        private System.Windows.Forms.TextBox textBox44;
        private System.Windows.Forms.Label label95;
        private System.Windows.Forms.Label label96;
        private System.Windows.Forms.Label label97;
        private System.Windows.Forms.Label label98;
        private System.Windows.Forms.Label label99;
        private System.Windows.Forms.Label label100;
        private System.Windows.Forms.Label label101;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.GroupBox groupBox39;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.GroupBox groupBox40;
        private System.Windows.Forms.DataGridView dataGridView8;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn22;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn23;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn24;
        private System.Windows.Forms.TextBox textBox45;
        private System.Windows.Forms.TextBox textBox46;
        private System.Windows.Forms.TextBox textBox47;
        private System.Windows.Forms.Label label102;
        private System.Windows.Forms.Label label103;
        private System.Windows.Forms.Label label104;
        private System.Windows.Forms.Button button24;
        private System.Windows.Forms.Button button25;
        private System.Windows.Forms.Button button26;
        private System.Windows.Forms.Label label105;
        private System.Windows.Forms.GroupBox groupBox41;
        private System.Windows.Forms.Label label106;
        private System.Windows.Forms.Label label107;
        private System.Windows.Forms.Button button27;
        private System.Windows.Forms.Button button28;
        private System.Windows.Forms.TextBox textBox48;
        private System.Windows.Forms.TextBox textBox49;
        private System.Windows.Forms.GroupBox groupBox42;
        private System.Windows.Forms.Button button29;
        private System.Windows.Forms.Button button30;
        private System.Windows.Forms.Button button31;
        private System.Windows.Forms.DataGridView dataGridView9;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn25;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn26;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn27;
        private System.Windows.Forms.GroupBox groupBox43;
        private System.Windows.Forms.Button button32;
        private System.Windows.Forms.Button button33;
        private System.Windows.Forms.DataGridView dataGridView10;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn28;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn29;
        private System.Windows.Forms.TextBox textBox50;
        private System.Windows.Forms.Label label108;
        private System.Windows.Forms.TextBox textBox51;
        private System.Windows.Forms.Label label109;
        private System.Windows.Forms.Button button34;
        private System.Windows.Forms.Label label110;
        private System.Windows.Forms.TabPage tabPage7;
        private System.Windows.Forms.GroupBox groupBox44;
        private System.Windows.Forms.Label label127;
        private System.Windows.Forms.Label label128;
        private System.Windows.Forms.Button buttonSelectStarTask;
        private System.Windows.Forms.Label label129;
        private System.Windows.Forms.TextBox textBoxStarTaskGroupID;
        private System.Windows.Forms.ComboBox comboBoxStarTask;
        private System.Windows.Forms.Button buttonColorMode;
        private System.Windows.Forms.Button buttonEditMode;
        private System.Windows.Forms.TabPage tabPageGather;
        private System.Windows.Forms.GroupBox groupBox45;
        private System.Windows.Forms.Label label130;
        private System.Windows.Forms.Button buttonSelectGather;
        private System.Windows.Forms.Label label131;
        private System.Windows.Forms.Button buttonDelGather;
        private System.Windows.Forms.Button buttonAddGather;
        private System.Windows.Forms.TextBox textBoxGatherID;
        private System.Windows.Forms.DataGridView dataGridViewGather;
        private System.Windows.Forms.CheckBox checkBoxGather;
        private System.Windows.Forms.TextBox textBoxGatherCount;
        private System.Windows.Forms.Label label132;
        private System.Windows.Forms.DataGridViewTextBoxColumn GatherID;
        private System.Windows.Forms.DataGridViewTextBoxColumn GatherCount;
        private System.Windows.Forms.DataGridViewTextBoxColumn GatherParam;
        //private System.Windows.Forms.Label label133;
        //private System.Windows.Forms.Label label134;
        //private System.Windows.Forms.TextBox textBoxStarCoef;
        //private System.Windows.Forms.TextBox textBoxRingCoef;
        private System.Windows.Forms.Button buttonInsertGather;
        private System.Windows.Forms.Button buttonUnloadTask;
        private System.Windows.Forms.RadioButton radioButton_noRepeat;
        private System.Windows.Forms.CheckBox checkBox_canGiveUp;
        private System.Windows.Forms.RadioButton radioButton_rewardTask;
        private System.Windows.Forms.RadioButton radioButton_NomalTask;
        private System.Windows.Forms.RadioButton radioButton_repeat;
        private System.Windows.Forms.RadioButton radioButton_dayRepeat;
        private System.Windows.Forms.CheckBox checkBox_build;
        private System.Windows.Forms.CheckBox checkBox_behave;
        private System.Windows.Forms.CheckBox checkBox_grow;
        private System.Windows.Forms.TabPage tabPageGrow;
        private System.Windows.Forms.TabPage tabPageBehave;
        private System.Windows.Forms.TabPage tabPageBuild;
        private System.Windows.Forms.GroupBox groupBox46;
        private System.Windows.Forms.GroupBox groupBox33;
        private System.Windows.Forms.ComboBox comboBox_limit_family;
        private System.Windows.Forms.ComboBox comboBox_limitCamp;
        private System.Windows.Forms.GroupBox groupBox48;
        private System.Windows.Forms.GroupBox groupBox47;
        private System.Windows.Forms.TextBox textBox_roleProp;
        private System.Windows.Forms.ComboBox comboBox_roleProp;
        private System.Windows.Forms.Label label112;
        private System.Windows.Forms.Label label111;
        private System.Windows.Forms.Button button_growRemove;
        private System.Windows.Forms.Button button_growAdd;
        private System.Windows.Forms.DataGridView dataGridView_grow;
        private System.Windows.Forms.TextBox textBox_campName;
        private System.Windows.Forms.TextBox textBox_campID;
        private System.Windows.Forms.Label label113;
        private System.Windows.Forms.Button button_selectCamp;
        private System.Windows.Forms.Label label114;
        private System.Windows.Forms.GroupBox groupBox50;
        private System.Windows.Forms.TextBox textBox_behave_action;
        private System.Windows.Forms.ComboBox comboBox_behave_action;
        private System.Windows.Forms.Label label116;
        private System.Windows.Forms.Label label117;
        private System.Windows.Forms.Button button_behaveRemove;
        private System.Windows.Forms.Button button_behaveAdd;
        private System.Windows.Forms.DataGridView dataGridView_behave;
        private System.Windows.Forms.DataGridViewTextBoxColumn roleAction;
        private System.Windows.Forms.DataGridViewTextBoxColumn roleActionValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn roleActionParam;
        private System.Windows.Forms.GroupBox groupBox51;
        private System.Windows.Forms.TextBox textBox_tecValue;
        private System.Windows.Forms.TextBox textBox_tecID;
        private System.Windows.Forms.TextBox textBox_tecName;
        private System.Windows.Forms.Button button_tecRemove;
        private System.Windows.Forms.Button button_tecAdd;
        private System.Windows.Forms.Label label120;
        private System.Windows.Forms.Label label121;
        private System.Windows.Forms.Button button_selectTec;
        private System.Windows.Forms.Label label122;
        private System.Windows.Forms.DataGridView dataGridView_build;
        private System.Windows.Forms.GroupBox groupBox49;
        private System.Windows.Forms.TextBox textBox_buildLevel;
        private System.Windows.Forms.TextBox textBox_buildID;
        private System.Windows.Forms.TextBox textBox_buildName;
        private System.Windows.Forms.Button button_buildAdd;
        private System.Windows.Forms.Label label119;
        private System.Windows.Forms.Label label118;
        private System.Windows.Forms.Button button_selectBuild;
        private System.Windows.Forms.Label label115;
        private System.Windows.Forms.Button button_award_propRemove;
        private System.Windows.Forms.Button button_award_propAdd;
        private System.Windows.Forms.DataGridView dataGridView_award_prop;
        private System.Windows.Forms.GroupBox groupBox17;
        private System.Windows.Forms.TextBox textBox_award_campName;
        private System.Windows.Forms.TextBox textBox_award_campID;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Button button_award_selectCamp;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.GroupBox groupBox52;
        private System.Windows.Forms.TextBox textBox_award_roleProp;
        private System.Windows.Forms.ComboBox comboBox_award_roleProp;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.GroupBox groupBox53;
        private System.Windows.Forms.Button button_award_generalRemove;
        private System.Windows.Forms.GroupBox groupBox54;
        private System.Windows.Forms.TextBox textBox_award_general;
        private System.Windows.Forms.ComboBox comboBox_award_general;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Button button_award_generalAdd;
        private System.Windows.Forms.DataGridView dataGridView_award_general;
        private System.Windows.Forms.GroupBox groupBox55;
        private System.Windows.Forms.RadioButton radioButton_preTaskOne;
        private System.Windows.Forms.RadioButton radioButton_preTaskAll;
        private System.Windows.Forms.Button button_preTaskRemove;
        private System.Windows.Forms.Button button_preTaskAdd;
        private System.Windows.Forms.Button button_careerRemove;
        private System.Windows.Forms.Button button_careerAdd;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn buildName;
        private System.Windows.Forms.DataGridViewTextBoxColumn buildValue;
        private System.Windows.Forms.GroupBox groupBox56;
        private System.Windows.Forms.Button button_limit_propRemove;
        private System.Windows.Forms.GroupBox groupBox57;
        private System.Windows.Forms.TextBox textBox_limit_roleProp;
        private System.Windows.Forms.ComboBox comboBox_limit_roleProp;
        private System.Windows.Forms.Label label124;
        private System.Windows.Forms.Label label125;
        private System.Windows.Forms.Button button_limit_propAdd;
        private System.Windows.Forms.GroupBox groupBox58;
        private System.Windows.Forms.TextBox textBox_limit_campName;
        private System.Windows.Forms.TextBox textBox_limit_campID;
        private System.Windows.Forms.Label label126;
        private System.Windows.Forms.Button button_limit_selectCamp;
        private System.Windows.Forms.Label label135;
        private System.Windows.Forms.DataGridView dataGridView_limit_prop;
        private System.Windows.Forms.GroupBox groupBox59;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn32;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn33;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn30;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn31;
        private System.Windows.Forms.GroupBox groupBox60;
        private System.Windows.Forms.DataGridView dgvKillMonsterItem;
        private System.Windows.Forms.Button btnCollectItemDel;
        private System.Windows.Forms.Button btnCollectItemAdd;
        private System.Windows.Forms.TextBox txtItemID;
        private System.Windows.Forms.TextBox txtCollectMonsterID;
        private System.Windows.Forms.Label label136;
        private System.Windows.Forms.Label label137;
        private System.Windows.Forms.Label label138;
        private System.Windows.Forms.Button CollectMonster;
        private System.Windows.Forms.Label label139;
        private System.Windows.Forms.TextBox txtItemCount;
        private System.Windows.Forms.Label label140;
        private System.Windows.Forms.TextBox txtMonsterName;
        private System.Windows.Forms.Label label142;
        private System.Windows.Forms.TextBox txtItemName;
        private System.Windows.Forms.Label label141;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn34;
        private System.Windows.Forms.DataGridViewTextBoxColumn monster;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn35;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn36;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridItemParam;
        private System.Windows.Forms.CheckBox cbIsLevel;
        private System.Windows.Forms.Button buttonSelectTitle;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.ComboBox comboBox_SelectJob;
        private System.Windows.Forms.Label label123;
        private System.Windows.Forms.ComboBox cmbJobLimitS;
        private System.Windows.Forms.ComboBox cmbJobLimit;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.DataGridViewTextBoxColumn TaskID;
        private System.Windows.Forms.DataGridViewTextBoxColumn TaskLevel;
        private System.Windows.Forms.DataGridViewTextBoxColumn TaskName;
        private System.Windows.Forms.DataGridViewTextBoxColumn TaskType;
        private System.Windows.Forms.DataGridViewTextBoxColumn OpenState;
        private System.Windows.Forms.DataGridViewTextBoxColumn ShareState;
        private System.Windows.Forms.DataGridViewTextBoxColumn CanGiveUp;
        private System.Windows.Forms.DataGridViewTextBoxColumn RepeatState;
        private System.Windows.Forms.DataGridViewTextBoxColumn FinishLimit;
        private System.Windows.Forms.DataGridViewTextBoxColumn AwardLinkLevel;
        private System.Windows.Forms.DataGridViewTextBoxColumn OptItemID;
        private System.Windows.Forms.DataGridViewTextBoxColumn OptItemName;
        private System.Windows.Forms.DataGridViewTextBoxColumn OptItemCount;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn37;
        private System.Windows.Forms.DataGridViewTextBoxColumn AwardItemID;
        private System.Windows.Forms.DataGridViewTextBoxColumn AwradItemName;
        private System.Windows.Forms.DataGridViewTextBoxColumn AwardItemCount;
        private System.Windows.Forms.DataGridViewTextBoxColumn JobLimit;
        //private System.Windows.Forms.GroupBox groupBox61;
        //private System.Windows.Forms.ComboBox cmbRaceLimit;
        private System.Windows.Forms.GroupBox groupBox62;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.GroupBox groupBox63;
        private System.Windows.Forms.RadioButton rbtGuideFind;
        private System.Windows.Forms.RadioButton rbtGuildJump;
        private System.Windows.Forms.DataGridViewTextBoxColumn MonsterID;
        private System.Windows.Forms.DataGridViewTextBoxColumn MonsterName;
        private System.Windows.Forms.DataGridViewTextBoxColumn MonsterNum;
        private System.Windows.Forms.DataGridViewTextBoxColumn Fake;
        private System.Windows.Forms.DataGridViewTextBoxColumn strParam;
        private System.Windows.Forms.DataGridView dgvMercenAward;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn38;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn39;
        private System.Windows.Forms.DataGridViewTextBoxColumn pos;
        private System.Windows.Forms.DataGridViewTextBoxColumn awardGeneralName;
        private System.Windows.Forms.DataGridViewTextBoxColumn awardGeneralValue;
        private System.Windows.Forms.GroupBox groupBox64;
        private System.Windows.Forms.TextBox txt_GrowID;
        private System.Windows.Forms.Label label144;
        private System.Windows.Forms.TextBox txt_GrowName;
        private System.Windows.Forms.Label label143;
        private System.Windows.Forms.Label label145;
        private System.Windows.Forms.DataGridViewTextBoxColumn roleProperty;
        private System.Windows.Forms.DataGridViewTextBoxColumn roleValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn extid;
        private System.Windows.Forms.DataGridViewTextBoxColumn extname;
        private System.Windows.Forms.TextBox textBox_behave_param;
        private System.Windows.Forms.Label label133;
        private System.Windows.Forms.Label label134;
        private System.Windows.Forms.TextBox textBoxKillMonsterParam;
        private System.Windows.Forms.Label label146;
        private System.Windows.Forms.TextBox txtItemParam;
        private System.Windows.Forms.Label label147;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label148;
        private System.Windows.Forms.TextBox textBoxGatherParam;
        private System.Windows.Forms.Label label149;
        private System.Windows.Forms.TextBox textBoxProbeParam;
    }
}

