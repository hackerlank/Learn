using System;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace TaskEditor
{
    public partial class FormEditor : Form
    {
        private CTaskInfoMgr _taskInfoMgr = new CTaskInfoMgr();
        private Dictionary<DataGridViewRow, CTaskInfo> _mapRow2TaskInfo = new Dictionary<DataGridViewRow, CTaskInfo>();
        private CTaskInfo _curTaskInfo;
        private FormSelect _formSelect;
        private RichTextBox _curTextBox;
        private bool _bEditMode;

        //任务定义辅助
        private Hashtable _taskContentUIHelper = new Hashtable();

        //用于UI的字符串常量定义
        public static readonly string[] title_limitGender = new string[] {"所有", "男性", "女性" };
        public static readonly string[] title_limitCamp = new string[] { "无限制", "峨眉", "昆仑", "中立" };
        public static readonly string[] title_limitJob = new String[] { "无限制", "儒", "释", "道", "墨" };
        public static readonly string[] title_limitFamily = new string[] { "无限制", "家族", "帮派" };
        public static readonly string[] limit_prop = new string[] { "等级", "声望" };
        //public static readonly string[] limit_race = new string[] { "无限制", "人类", "兽人", "亡灵" };

        public static readonly string[] title_roleProps = new string[] { "等级", "声望"};
        public static readonly string[] title_actions = new string[] {
            "单人副本", "多人副本", "装备强化", "装备铸造", "世界BOSS伤害",
            "加入帮派", "招募散仙", "扫荡副本", "散仙培养", "帮派贡献",
            "帮派技能", "(新手引导)升级技能", "收藏游戏", "解封装备",
            "获得技能", "获得法宝",  "邀请好友", "激活阵型", "激活坐骑",
            "坐骑升级", "激活阵灵", "阵灵升级", "散仙出战", "散仙淬体",
            "散仙法宝", "散仙技能", "法宝祭炼", "当日活跃度","完成师门任务",
            "完成衙门任务","散仙渡劫到N","仙府祈火","兽魂升级",
            "散仙技能升级"
             };
        //public static readonly string[] award_general = new string[] { "仙石", "礼券", "银币", "魂魄", "声望", "荣誉", "修为", "符印", "仙元", "体力", "阅历", "道术", "潜能", "灵力", "仙券", "经验" };
        public static readonly string[] award_general = new string[] { "仙石", "银币", "礼券", "金券", "经验", "声望", "魂魄", "荣誉", "修为", "符印", "仙元", "体力", "阅历", "道术", "渡劫点数", "副本星级", "寻仙积分", "封印点", "攻击之魂", "生命之魂", "暴击之魂", "反击之魂", "身法之魂", "防御之魂", "命中之魂", "闪避之魂", "成就点", "收藏点", "帮派贡献" };
        public static readonly string[] award_prop = new string[] { "声望", "威望" };

        public FormEditor()
        {
            InitializeComponent();
            this.InitLastDir();

            this.GenerateDynamicComs();

            //初始化UI coms
            this.InitComs();
        }

        //添加由代码生成的控件
        private void GenerateDynamicComs()
        {

        }

        //初始化控件属性，由代码控制
        private void InitComs()
        {
            //任务定义相关
            this._taskContentUIHelper.Add(EContentType.eContentKill,
                new TaskContentUIElement(EContentType.eContentKill, this.checkBoxKill, this.tabPageKill));
            this._taskContentUIHelper.Add(EContentType.eContentGrow,
                new TaskContentUIElement(EContentType.eContentGrow, this.checkBox_grow, this.tabPageGrow));
            this._taskContentUIHelper.Add(EContentType.eContentCollect,
                new TaskContentUIElement(EContentType.eContentCollect, this.checkBoxCollect, this.tabPageCollect));
            this._taskContentUIHelper.Add(EContentType.eContentGather,
                new TaskContentUIElement(EContentType.eContentGather, this.checkBoxGather, this.tabPageGather));
            this._taskContentUIHelper.Add(EContentType.eContentProbe,
                new TaskContentUIElement(EContentType.eContentProbe, this.checkBoxProbe, this.tabPageProbe));
            this._taskContentUIHelper.Add(EContentType.eContentBehave,
                new TaskContentUIElement(EContentType.eContentBehave, this.checkBox_behave, this.tabPageBehave));
            this._taskContentUIHelper.Add(EContentType.eContentBuild,
                new TaskContentUIElement(EContentType.eContentBuild, this.checkBox_build, this.tabPageBuild));
            this._taskContentUIHelper.Add(EContentType.eContentTalk,
                new TaskContentUIElement(EContentType.eContentTalk, this.checkBoxTalk, this.tabPageTalk));
            foreach (DictionaryEntry item in this._taskContentUIHelper)
            {
                TaskContentUIElement obj = item.Value as TaskContentUIElement;
                obj.page.Enabled = false;
            }

            _bEditMode = true;
            buttonEditMode.BackColor = Color.Aqua;
            buttonColorMode.BackColor = Color.Transparent;

            //任务限制
            this.comboBoxSexLimit.Items.AddRange(title_limitGender);
            this.comboBox_limitCamp.Items.AddRange(title_limitCamp);
            this.comboBox_SelectJob.Items.AddRange(title_limitJob);
            this.comboBox_limit_family.Items.AddRange(title_limitFamily);
            this.comboBox_limit_roleProp.Items.AddRange(limit_prop);
            //this.cmbRaceLimit.Items.AddRange(limit_race);

            //任务过程
            this.comboBox_roleProp.Items.AddRange(title_roleProps);
            this.comboBox_behave_action.Items.AddRange(title_actions);

            //任务奖励
            this.comboBox_award_general.Items.AddRange(award_general);
            this.comboBox_award_roleProp.Items.AddRange(award_prop);
            this.cmbJobLimit.Items.AddRange(title_limitJob);
            this.cmbJobLimitS.Items.AddRange(title_limitJob);
        }

        private void dataGridViewTaskList_ColumnHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            DataGridViewColumn newColumn = dataGridViewTaskList.Columns[e.ColumnIndex];
            if (e.ColumnIndex == 0)
                dataGridViewTaskList.Sort(new CIDComparer());
            else if (e.ColumnIndex == 1)
                dataGridViewTaskList.Sort(new CLevelComparer());
            else
                dataGridViewTaskList.Sort(newColumn, ListSortDirection.Ascending);
            newColumn.HeaderCell.SortGlyphDirection = SortOrder.Ascending;
        }

        private void textBoxFolderPath_DragEnter(object sender, DragEventArgs e)
        {
            string[] arFileList = (string[])e.Data.GetData(DataFormats.FileDrop, false);
            if (arFileList.Length > 0)
                textBoxFolderPath.Text = arFileList[0];
        }

        private void SelectFile(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = ".";
            openFileDialog1.Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.Multiselect = true;
            openFileDialog1.RestoreDirectory = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (openFileDialog1.FileNames.Length > 0)
                    textBoxFolderPath.Text = openFileDialog1.FileNames[0];
            }
        }

        private void SelectFolder(object sender, EventArgs e)
        {
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            DialogResult result = folderBrowserDialog.ShowDialog();
            if (result == DialogResult.OK)
                textBoxFolderPath.Text = folderBrowserDialog.SelectedPath;

            FileInfo fi = new FileInfo("LastOpenedDir.txt");
            FileStream fs = null;
            if (!fi.Exists)
                fs = fi.Create();
            else
                fs = fi.OpenWrite();

            byte[] path = System.Text.Encoding.Default.GetBytes(textBoxFolderPath.Text.ToCharArray());
            fs.Write(path, 0, path.Length);
            fs.Close();
            fi.Refresh();
        }

        private void OpenFile(object sender, EventArgs e)
        {
            try
            {
                FileInfo fi = new FileInfo(textBoxFolderPath.Text);
                if (!fi.Exists)
                {
                    MessageBox.Show("文件\"" + fi.FullName + "\"不存在", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
                CTaskInfo taskInfo = _taskInfoMgr.LoadXMLFile(textBoxFolderPath.Text);
                _curTaskInfo = taskInfo;
                DataGridViewRow row = InsertNewTask(_curTaskInfo);
                row.Selected = true;
                RefreshData(taskInfo);
                MessageBox.Show("打开成功", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "打开失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void SaveFile(object sender, EventArgs e)
        {
            if (_curTaskInfo == null || _curTaskInfo.wID == 0)
                return;
            if (_curTaskInfo.ArTriggerTarget.Count == 0)
            {
                MessageBox.Show("触发条件缺失", "保存失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            try
            {
                string strPath = "";
                FileInfo fi = new FileInfo(textBoxFolderPath.Text);
                if (fi.Exists)
                {
                    strPath = textBoxFolderPath.Text;
                }
                else
                {
                    DirectoryInfo di = new DirectoryInfo(textBoxFolderPath.Text);
                    if (!di.Exists)
                    {
                        MessageBox.Show("目录不存在", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                        return;
                    }
                    strPath = textBoxFolderPath.Text + "\\Task" + _curTaskInfo.wID.ToString() + ".xml";
                }
                _taskInfoMgr.SaveXMLFile(_curTaskInfo, strPath);
                MessageBox.Show("保存成功", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "保存失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void RemoveTask(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            dataGridViewTaskList.Rows.Remove(row);
            _mapRow2TaskInfo.Remove(row);
            if (dataGridViewTaskList.Rows.Count == 0)
                RefreshData(new CTaskInfo());
        }

        private void OpenAllFile(object sender, EventArgs e)
        {
            string strFile = "";
            try
            {
                DirectoryInfo di = new DirectoryInfo(textBoxFolderPath.Text);
                if (di.Exists)
                {
                    FileInfo[] arFile = di.GetFiles("Task*.xml");
                    dataGridViewTaskList.Rows.Clear();
                    _mapRow2TaskInfo.Clear();
                    foreach(FileInfo fi in arFile)
                    {
                        strFile = fi.FullName;
                        CTaskInfo taskInfo = _taskInfoMgr.LoadXMLFile(fi.FullName);
                        _curTaskInfo = taskInfo;
                        DataGridViewRow row = InsertNewTask(_curTaskInfo);
                        row.Selected = true;
                        RefreshData(taskInfo);
                    }
                    dataGridViewTaskList.Sort(new CIDComparer());
                    MessageBox.Show("打开成功", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(strFile + ": " + ex.Message, "加载失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void SaveAllFile(object sender, EventArgs e)
        {
            try
            {
                DirectoryInfo di = new DirectoryInfo(textBoxFolderPath.Text);
                if (di.Exists)
                {
                    foreach (KeyValuePair<DataGridViewRow, CTaskInfo> kvp in _mapRow2TaskInfo)
                    {
                        CTaskInfo taskInfo = kvp.Value;
                        if (taskInfo.wID != 0)
                        {
                            string strPath = textBoxFolderPath.Text + "\\Task" + taskInfo.wID.ToString() + ".xml";
                            _taskInfoMgr.SaveXMLFile(taskInfo, strPath);
                        }
                    }
                    MessageBox.Show("保存成功", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("目录不存在", "操作结果", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "保存失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private DataGridViewRow InsertNewTask(CTaskInfo info)
        {
            string[] strRow = {};
            int index = dataGridViewTaskList.Rows.Count;
            dataGridViewTaskList.Rows.Add(strRow);
            DataGridViewRow row = dataGridViewTaskList.Rows[index];

            this._mapRow2TaskInfo.Add(row, info);
            RefreshTaskRow(row);

            return row; 
        }

        /**
         * 刷新当前任务栏的数据
         */ 
        private void RefreshTaskRow(DataGridViewRow row)
        {
            if (null == row)
            {
                return;
            }

            for (int i = 0; i < dataGridViewTaskList.Columns.Count; ++i)
            {
                RefreshTaskColumn(row, dataGridViewTaskList.Columns[i].Name);
            }
        }

        private void RefreshTaskColumn(DataGridViewRow row, string columnName)
        { // TaskID TaskLevel TaskName TaskType OpenState ShareState CanGiveUp RepeatState FinishLimit
            if (null == row || null == columnName)
            {
                return;
            }

            DataGridViewCell cell = row.Cells[columnName];
            if (null == cell)
            {
                return;
            }

            if (!this._mapRow2TaskInfo.ContainsKey(row))
            {
                return;
            }

            CTaskInfo info = this._mapRow2TaskInfo[row];
            if (null == info)
            {
                return;
            }

            if("TaskID" == columnName)
            {
                cell.Value = info.wID.ToString();
            }
            else if ("TaskLevel" == columnName)
            {
                cell.Value = info.byLevel.ToString();
            }
            else if ("TaskName" == columnName)
            {
                cell.Value = info.strName;
            }
            else if ("TaskType" == columnName)
            {
                int index = (int)info.dwTaskType - 1;
                if (index != -1)
                {
                    cell.Value = comboBoxTaskType.Items[index];
                }
                else
                {
                    cell.Value = "";
                }
            }
            else if ("OpenState" == columnName)
            {
                cell.Value = (0 == info.byOpen ? "不开放" : "开放");
            }
            else if ("ShareState" == columnName)
            {
                cell.Value = (0 == info.byShare ? "不共享" : "共享");
            }
            else if ("CanGiveUp" == columnName)
            {
                cell.Value = (0 == info.byCanGiveUp ? "不可放弃" : "可放弃");
            }
            else if ("AwardLinkLevel" == columnName)
            {
                cell.Value = (0 == info.byAwardLinkLevel ? "普通奖励" : "等级相关奖励");
            }
            else if ("RepeatState" == columnName)
            {
                if(0 == info.dwRepeat)
                {
                    cell.Value = "不可重复";
                }
                else if(UInt32.MaxValue == info.dwRepeat)
                {
                    cell.Value = "无限重复";
                }
                else
                {
                    cell.Value = "每日重复";
                }
            }
            else if ("FinishLimit" == columnName)
            {
                switch (info.byTaskTypeExtent)
                {
                    case (Byte)ETaskTypeExtent.eTaskTypeExtent_normal:
                        cell.Value = "一般任务";
                        break;
                    case (Byte)ETaskTypeExtent.eTaskTypeExtent_reward:
                        cell.Value = "悬赏任务";
                        break;
                    default:
                        cell.Value = "";
                        break;
                }
            }
        }

        private void ShowAward(CTaskInfo taskInfo)
        {
            string strAward = "你将获得：";
            foreach (SAwardGeneral obj in taskInfo.AwardGeneral)
            {
                strAward += "\n\n" + award_general[(int)(obj.type)] + "：" + obj.value.ToString();
            }

            //属性奖励
            strAward += "\n\n属性：";
            foreach (CEnumValue obj in taskInfo.AwardProps)
            {
                strAward += "\n\n[" + award_prop[obj.type] + "：" + obj.value.ToString();
                if (obj.type == (Byte)EAwardProperty.repute)
                {
                    strAward += ", 阵营(" + taskInfo.awardProp_campID.ToString() + ", " + taskInfo.awardProp_campName + ")";
                }

                strAward += "]";
            }

            //称号奖励
            strAward += "\n\n称号：";
            foreach (CIdxName obj in taskInfo.AwardTitles)
            {
                strAward += "[" + obj.name + "] ";
            }

            if (taskInfo.ArMustAwardItem.Count > 0)
            {
                strAward += "\n\n道具：\n";
                foreach (Object obj in taskInfo.ArMustAwardItem)
                {
                    CIdxNameCountJob idxNameCount = (CIdxNameCountJob)obj;
                    strAward += "  [" + idxNameCount.strName + "]";
                    if (idxNameCount.wCount > 1)
                        strAward += " * " + idxNameCount.wCount;
                }
            }
            if (taskInfo.ArOptAwardItem.Count > 0)
            {
                strAward += "\n\n你可以从这些奖励品中挑选一件：\n";
                foreach (Object obj in taskInfo.ArOptAwardItem)
                {
                    CIdxNameCountJob idxNameCount = (CIdxNameCountJob)obj;
                    strAward += "  [" + idxNameCount.strName + "]";
                    if (idxNameCount.wCount > 1)
                        strAward += " * " + idxNameCount.wCount;
                }
            }

            richTextBoxAward.Text = strAward;
        }

        private void ShowColor(CTaskInfo taskInfo)
        {
            textBoxTaskDesc.Text = taskInfo.taskTextDesc.strText;
            taskInfo.taskTextDesc.ShowColor(textBoxTaskDesc);
            textBoxTaskPurpose.Text = taskInfo.taskTextPurpose.strText;
            taskInfo.taskTextPurpose.ShowColor(textBoxTaskPurpose);
            textBoxTaskFail.Text = taskInfo.taskTextFail.strText;
            taskInfo.taskTextFail.ShowColor(textBoxTaskFail);
            textBoxTaskFinish.Text = taskInfo.taskTextFinish.strText;
            taskInfo.taskTextFinish.ShowColor(textBoxTaskFinish);
        }

        private void ShowColorText(CTaskInfo taskInfo)
        {
            textBoxTaskDesc.Text = taskInfo.taskTextDesc.ColorText;
            textBoxTaskPurpose.Text = taskInfo.taskTextPurpose.ColorText;
            textBoxTaskFail.Text = taskInfo.taskTextFail.ColorText;
            textBoxTaskFinish.Text = taskInfo.taskTextFinish.ColorText;
        }

        /**
         * 刷新基本信息区域
         */
        private void RefreshTaskBase(CTaskInfo taskInfo)
        {
            textBoxTaskID.Text = taskInfo.wID.ToString();
            textBoxTaskName.Text = taskInfo.strName;
            textBoxTaskLevel.Text = taskInfo.byLevel.ToString();
            comboBoxTaskType.SelectedIndex = (int)(taskInfo.dwTaskType - 1);

            //任务标记
            checkBoxIsOpen.Checked = taskInfo.byOpen == 1;
            checkBoxIsShared.Checked = taskInfo.byShare == 1;
            checkBox_canGiveUp.Checked = taskInfo.byCanGiveUp == 1;
            cbIsLevel.Checked = taskInfo.byAwardLinkLevel == 1;
            this.radioButton_noRepeat.Checked = taskInfo.dwRepeat == 0;
            if (taskInfo.dwRepeat > 0 && taskInfo.dwRepeat < UInt32.MaxValue)
            {
                this.textBoxRepeatCount.Text = taskInfo.dwRepeat.ToString();
                this.radioButton_dayRepeat.Checked = true;
            }
            this.radioButton_repeat.Checked = taskInfo.dwRepeat == UInt32.MaxValue;
            this.radioButton_NomalTask.Checked = (taskInfo.byTaskTypeExtent == (Byte)ETaskTypeExtent.eTaskTypeExtent_normal);
            this.radioButton_rewardTask.Checked = (taskInfo.byTaskTypeExtent == (Byte)ETaskTypeExtent.eTaskTypeExtent_reward);
            if (1 == taskInfo.byGuideType)
            {
                this.rbtGuideFind.Checked = true;
            }
            else if (2 == taskInfo.byGuideType)
            {
                this.rbtGuildJump.Checked = true;
            }
            else
            {
                this.rbtGuideFind.Checked = false;
                this.rbtGuildJump.Checked = false;
            }

            //任务定义
            RefreshTaskContent(taskInfo);

            if (taskInfo.dwStarGroupID > 0)
                textBoxStarTaskGroupID.Text = taskInfo.dwStarGroupID.ToString();
            else
                textBoxStarTaskGroupID.Text = "";
            comboBoxStarTask.SelectedIndex = (int)taskInfo.dwTaskStar;

            dataGridViewTaskStart.Rows.Clear();
            textBoxTaskStartID.Clear();
            textBoxTaskStartName.Clear();
            if (taskInfo.ArTriggerTarget.Count > 0)
            {
                CIdxNameType[] arIdxNameType = (CIdxNameType[])taskInfo.ArTriggerTarget.ToArray(typeof(CIdxNameType));
                foreach (CIdxNameType idxNameType in arIdxNameType)
                {
                    comboBoxTaskStart.SelectedIndex = idxNameType.byType - 1;
                    string[] row = { idxNameType.dwIdx.ToString(), comboBoxTaskStart.SelectedItem.ToString(), idxNameType.strName };
                    dataGridViewTaskStart.Rows.Add(row);
                }
            }
            comboBoxTaskStart.SelectedIndex = -1;

            dataGridViewTaskSubmit.Rows.Clear();
            textBoxTaskSubmitID.Clear();
            textBoxTaskSubmitName.Clear();
            if (taskInfo.ArSubmitTarget.Count > 0)
            {
                CIdxNameType[] arIdxNameType = (CIdxNameType[])taskInfo.ArSubmitTarget.ToArray(typeof(CIdxNameType));
                foreach (CIdxNameType idxNameType in arIdxNameType)
                {
                    comboBoxTaskSubmit.SelectedIndex = idxNameType.byType - 1;
                    string[] row = { idxNameType.dwIdx.ToString(), comboBoxTaskSubmit.SelectedItem.ToString(), idxNameType.strName };
                    dataGridViewTaskSubmit.Rows.Add(row);
                }
            }
            comboBoxTaskSubmit.SelectedIndex = -1;
        }
        
        /**
         * 刷新任务定义区域
         */ 
        private void RefreshTaskContent(CTaskInfo taskInfo)
        {
            TaskContentUIElement obj = null;
            foreach (DictionaryEntry item in this._taskContentUIHelper)
            {
                obj = item.Value as TaskContentUIElement;
                if (obj != null)
                {
                    obj.box.Checked = (taskInfo.dwContentType & (UInt32)obj.type) != 0;
                }
            }
        }

        /**
         * 刷新任务描述区域
         */
        private void RefreshTaskDesc(CTaskInfo taskInfo)
        {
            buttonChooseColor.Enabled = false;
            textBoxTaskDesc.ReadOnly = false;
            buttonEditMode.BackColor = Color.Aqua;
            buttonColorMode.BackColor = Color.Transparent;

            ShowColorText(taskInfo);
        }

        //插入一条前置任务记录
        private void InsertLimitPreTask(CIdxName item)
        {
            this.InsertIdxName2GridView(this.dataGridViewPreTask, item);
        }

        private void InsertLimitCareer(CIdxName item)
        {
            this.InsertIdxName2GridView(this.dataGridViewJobLimit, item);
        }

        //插入一条称号奖励记录
        private void InsertAwardTitle(CIdxName item)
        {
            this.InsertIdxName2GridView(this.dataGridViewTitle, item);
        }

        //往DataGridView中插入一条CIdxName记录。
        private void InsertIdxName2GridView(DataGridView view, CIdxName item)
        {
            if (null == view || null == item)
            {
                return;
            }

            string[] strRow = { };
            int index = view.Rows.Count;
            view.Rows.Add(strRow);
            DataGridViewRow row = view.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = item.id.ToString();
            cell = row.Cells[1];
            cell.Value = item.name;
        }

        //插入一条建筑\科技记录
        private void InsertBuilding(CIdxNameCount item)
        {
            this.InsertIdxNameCount2GridView(this.dataGridView_build, item);
        }

        //往DataGridView中插入一条CIdxNameCount记录。
        private void InsertIdxNameCount2GridView(DataGridView view, CIdxNameCount item)
        {
            if (null == view || null == item)
            {
                return;
            }

            string[] strRow = { };
            int index = view.Rows.Count;
            view.Rows.Add(strRow);
            DataGridViewRow row = view.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = item.dwIdx.ToString();
            cell = row.Cells[1];
            cell.Value = item.strName;
            cell = row.Cells[2];
            cell.Value = item.wCount.ToString();
        }

        private void InsertRoleProp(CEnumValueExt item)
        {
            this.InsertEnumValueExt2GridView(this.dataGridView_grow, item, title_roleProps);
        }

        private void InsertAction(CEnumValueStr item)
        {
            this.InsertEnumValue2GridView_1(this.dataGridView_behave, item, title_actions);
        }

        private void InsertAwardProp(CEnumValue item)
        {
            this.InsertEnumValue2GridView_0(this.dataGridView_award_prop, item, award_prop);
        }

        private void InsertLimitProp(CEnumValue item)
        {
            this.InsertEnumValue2GridView(this.dataGridView_limit_prop, item, limit_prop);
        }

        //往DataGridView中插入一条CEnumValueExt记录。
        private void InsertEnumValueExt2GridView(DataGridView view, CEnumValueExt item, string[] titles)
        {
            if (null == view || null == item || null == titles)
            {
                return;
            }

            string[] strRow = { };
            int index = view.Rows.Count;
            view.Rows.Add(strRow);
            DataGridViewRow row = view.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = titles[item.type - 1];
            cell = row.Cells[1];
            cell.Value = item.value.ToString();
            if (item.dwIdx > 0)
            {
                cell = row.Cells[2];
                cell.Value = item.dwIdx.ToString();
                cell = row.Cells[3];
                cell.Value = item.name;
            }
        }

        //往DataGridView中插入一条CEnumValue记录。
        private void InsertEnumValue2GridView(DataGridView view, CEnumValue item, string[] titles)
        {
            if (null == view || null == item || null == titles)
            {
                return;
            }

            string[] strRow = { };
            int index = view.Rows.Count;
            view.Rows.Add(strRow);
            DataGridViewRow row = view.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = titles[item.type - 1];
            cell = row.Cells[1];
            cell.Value = item.value.ToString();
            //cell = row.Cells[2];
            //cell.Value = item.param.ToString();
        }

        //往DataGridView中插入一条CEnumValue记录, 序号从0开始
        private void InsertEnumValue2GridView_0(DataGridView view, CEnumValue item, string[] titles)
        {
            if (null == view || null == item || null == titles)
            {
                return;
            }

            string[] strRow = { };
            int index = view.Rows.Count;
            view.Rows.Add(strRow);
            DataGridViewRow row = view.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = titles[item.type];
            cell = row.Cells[1];
            cell.Value = item.value.ToString();
        }

        //往DataGridView中插入一条CEnumValue记录。
        private void InsertEnumValue2GridView_1(DataGridView view, CEnumValueStr item, string[] titles)
        {
            if (null == view || null == item || null == titles)
            {
                return;
            }

            string[] strRow = { };
            int index = view.Rows.Count;
            view.Rows.Add(strRow);
            DataGridViewRow row = view.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = titles[item.type - 1];
            cell = row.Cells[1];
            cell.Value = item.value.ToString();
            cell = row.Cells[2];
            cell.Value = item.param.ToString();
        }
        /**
         * 刷新任务限制区域
         */
        private void RefreshTaskLimit(CTaskInfo taskInfo)
        {
            int index = (int)taskInfo.limitGender;
            //if (index >= 0)
            {
                this.comboBoxSexLimit.SelectedIndex = index;
            }


            if (taskInfo.limitReputeMin > 0 || taskInfo.limitReputeMax > 0)
            {
                this.textBoxReputeMin.Text = taskInfo.limitReputeMin.ToString();
                this.textBoxReputeMax.Text = taskInfo.limitReputeMax.ToString();
            }
            else
            {
                this.textBoxReputeMin.Clear();
                this.textBoxReputeMax.Clear();
            }

            if (taskInfo.limitJingJieMin > 0 || taskInfo.limitJingJieMax > 0)
            {
                this.textBoxGradeMin.Text = taskInfo.limitJingJieMin.ToString();
                this.textBoxGradeMax.Text = taskInfo.limitJingJieMax.ToString();
            }
            else
            {
                this.textBoxGradeMin.Clear();
                this.textBoxGradeMax.Clear();
            }

            index = (int)taskInfo.limitCamp;
            //if(index >= 0)
            {
                this.comboBox_limitCamp.SelectedIndex = index;
            }

            index = (int)taskInfo.limitFamily;
            //if(index >= 0)
            {
                this.comboBox_limit_family.SelectedIndex = index;
            }

            //this.cmbRaceLimit.SelectedIndex = (int)taskInfo.limitRace;

            //时间限制
            if (taskInfo.limitDateFrom > 0 && taskInfo.limitDateTo > 0)
            {
                this.dateTimePickerDateFrom.Value = new DateTime(taskInfo.limitDateFrom);
                this.dateTimePickerDateTo.Value = new DateTime(taskInfo.limitDateTo);

                this.checkBoxDateLimit.Checked = true;
            }
            else
            {
                this.checkBoxDateLimit.Checked = false;
            }

            //每日时间段限制
            if (taskInfo.limitDayTimeFrom > 0 && taskInfo.limitDayTimeTo > 0)
            {
                this.textBoxHourFrom.Text = taskInfo.limitDayTimeFrom.ToString();
                this.textBoxHourTo.Text = taskInfo.limitDayTimeTo.ToString();

                this.checkBoxTimeLimit.Checked = true;
            }
            else
            {
                this.checkBoxTimeLimit.Checked = false;
            }

            //前置任务限制
            this.radioButton_preTaskAll.Checked = false;
            this.radioButton_preTaskOne.Checked = false;
            this.dataGridViewPreTask.Rows.Clear();
            if (taskInfo.PreTasks.Count > 0)
            {
                this.radioButton_preTaskAll.Checked = 0 == taskInfo.limitPreTaskFlag;
                this.radioButton_preTaskOne.Checked = 1 == taskInfo.limitPreTaskFlag;

                foreach (CIdxName obj in taskInfo.PreTasks)
                {
                    this.InsertLimitPreTask(obj);
                }
            }

            //职业限制
            this.dataGridViewJobLimit.Rows.Clear();
            if (taskInfo.LimitCareers.Count > 0)
            {
                foreach (CIdxName obj in taskInfo.LimitCareers)
                {
                    this.InsertLimitCareer(obj);
                }
            }

            //属性奖励
            this.dataGridView_limit_prop.Rows.Clear();
            foreach (CEnumValue obj in taskInfo.LimitProps)
            {
                this.InsertLimitProp(obj);
            }
        }

        /**
         * 刷新任务过程区域
         */
        private void RefreshTaskProcess(CTaskInfo taskInfo)
        {
            if (taskInfo.dwLimitTime > 0)
            {
                this.textBoxLimitTime.Text = taskInfo.dwLimitTime.ToString();
            }
            else
            {
                this.textBoxLimitTime.Clear(); 
            }

            dataGridViewGiveItem.Rows.Clear();
            textBoxGiveItemID.Clear();
            textBoxGiveItemName.Clear();
            textBoxGiveItemCount.Clear();
            if (taskInfo.ArGiveItem.Count > 0)
            {
                CIdxNameCount[] arIdxNameCount = (CIdxNameCount[])taskInfo.ArGiveItem.ToArray(typeof(CIdxNameCount));
                foreach (CIdxNameCount idxNameType in arIdxNameCount)
                {
                    string[] row = { idxNameType.dwIdx.ToString(), idxNameType.strName, idxNameType.wCount.ToString() };
                    dataGridViewGiveItem.Rows.Add(row);
                }
            }

            dataGridViewKillMonster.Rows.Clear();
            textBoxKillMonsterID.Clear();
            textBoxKillMonsterName.Clear();
            textBoxKillMonsterCount.Clear();
            textBoxKillMonsterParam.Clear();
            if (taskInfo.ArKillMonster.Count > 0)
            {
                CIdxNameCountEx[] arIdxNameCount = (CIdxNameCountEx[])taskInfo.ArKillMonster.ToArray(typeof(CIdxNameCountEx));
                foreach (CIdxNameCountEx idxNameType in arIdxNameCount)
                {
                    string[] row = { idxNameType.dwIdx.ToString(), idxNameType.strName, idxNameType.wCount.ToString(), idxNameType.dwFakeIdx.ToString(), idxNameType.strParam.ToString()};
                    dataGridViewKillMonster.Rows.Add(row);
                }
            }

            dataGridViewCollectItem.Rows.Clear();
            textBoxCollectItemID.Clear();
            textBoxCollectItemName.Clear();
            textBoxCollectItemCount.Clear();
            if (taskInfo.ArCollectItem.Count > 0)
            {
                CIdxNameCount[] arIdxNameCount = (CIdxNameCount[])taskInfo.ArCollectItem.ToArray(typeof(CIdxNameCount));
                foreach (CIdxNameCount idxNameType in arIdxNameCount)
                {
                    string[] row = { idxNameType.dwIdx.ToString(), idxNameType.strName, idxNameType.wCount.ToString() };
                    dataGridViewCollectItem.Rows.Add(row);
                }
            }

            dgvKillMonsterItem.Rows.Clear();
            txtCollectMonsterID.Clear();
            txtItemID.Clear();
            txtItemCount.Clear();
            txtItemParam.Clear();
            if (taskInfo.ArKillCollectItem.Count > 0)
            {
                CIdxKillItemCount[] arIdxKillCount = (CIdxKillItemCount[])taskInfo.ArKillCollectItem.ToArray(typeof(CIdxKillItemCount));
                foreach (CIdxKillItemCount idxKillType in arIdxKillCount)
                {
                    string[] row = { idxKillType.dwIdx1.ToString(), idxKillType.strName1, idxKillType.dwIdx2.ToString(), idxKillType.strName2, idxKillType.wCount.ToString(), idxKillType.strParam.ToString() };
                    dgvKillMonsterItem.Rows.Add(row);
                }
            }

            dataGridViewProbe.Rows.Clear();
            textBoxProbeMapID.Clear();
            textBoxProbeMapName.Clear();
            textBoxProbeX1.Clear();
            textBoxProbeZ1.Clear();
            textBoxProbeX2.Clear();
            textBoxProbeZ2.Clear();
            if (taskInfo.ArProbe.Count > 0)
            {
                this.radioButton1.Checked = 0 == taskInfo.ProbeFlag;
                this.radioButton2.Checked = 1 == taskInfo.ProbeFlag;
                CMapArea[] arMapArea = (CMapArea[])taskInfo.ArProbe.ToArray(typeof(CMapArea));
                foreach (CMapArea mapArea in arMapArea)
                {
                    string[] row = { mapArea.dwMapID.ToString(), mapArea.strName, mapArea.x.ToString(), mapArea.z.ToString(), mapArea.x2.ToString(), mapArea.z2.ToString(), mapArea.strParam };
                    dataGridViewProbe.Rows.Add(row);
                }
            }

            //             textBoxUseItemSkillMapID.Clear();
            //             textBoxUseItemSkillMapName.Clear();
            //             textBoxUseItemSkillX1.Clear();
            //             textBoxUseItemSkillZ1.Clear();
            //             textBoxUseItemSkillX2.Clear();
            //             textBoxUseItemSkillZ2.Clear();
            // 
            //             dataGridViewUseItem.Rows.Clear();
            //             textBoxUseItemID.Clear();
            //             textBoxUseItemName.Clear();
            //             if (taskInfo.ArUseItem.Count > 0)
            //             {
            //                 CUseItem[] arUseItem = (CUseItem[])taskInfo.ArUseItem.ToArray(typeof(CUseItem));
            //                 foreach (CUseItem useItem in arUseItem)
            //                 {
            //                     if (useItem.mapArea != null)
            //                     {
            //                         string[] row = { useItem.dwItemID.ToString(), useItem.strName, useItem.mapArea.dwMapID.ToString(), useItem.mapArea.strName,
            //                                            useItem.mapArea.fX1.ToString("f2"), useItem.mapArea.fZ1.ToString("f2"), useItem.mapArea.fX2.ToString("f2"), useItem.mapArea.fZ2.ToString("f2") };
            //                         dataGridViewUseItem.Rows.Add(row);
            //                     }
            //                     else
            //                     {
            //                         string[] row = { useItem.dwItemID.ToString(), useItem.strName };
            //                         dataGridViewUseItem.Rows.Add(row);
            //                     }
            //                 }
            //             }

            //             dataGridViewUseSkill.Rows.Clear();
            //             textBoxUseSkillID.Clear();
            //             textBoxUseSkillName.Clear();
            //             if (taskInfo.ArUseSkill.Count > 0)
            //             {
            //                 CUseSkill[] arUseSkill = (CUseSkill[])taskInfo.ArUseSkill.ToArray(typeof(CUseSkill));
            //                 foreach (CUseSkill useSkill in arUseSkill)
            //                 {
            //                     if (useSkill.mapArea != null)
            //                     {
            //                         string[] row = { useSkill.dwSkillID.ToString(), useSkill.strName, useSkill.mapArea.dwMapID.ToString(), useSkill.mapArea.strName,
            //                                            useSkill.mapArea.fX1.ToString("f2"), useSkill.mapArea.fZ1.ToString("f2"), useSkill.mapArea.fX2.ToString("f2"), useSkill.mapArea.fZ2.ToString("f2") };
            //                         dataGridViewUseSkill.Rows.Add(row);
            //                     }
            //                     else
            //                     {
            //                         string[] row = { useSkill.dwSkillID.ToString(), useSkill.strName };
            //                         dataGridViewUseSkill.Rows.Add(row);
            //                     }
            //                 }
            //             }

            dataGridViewGather.Rows.Clear();
            textBoxGatherID.Clear();
            if (taskInfo.ArGather.Count > 0)
            {
                CGatherIdxCount[] arIdxCount = (CGatherIdxCount[])taskInfo.ArGather.ToArray(typeof(CGatherIdxCount));
                foreach (CGatherIdxCount idxCount in arIdxCount)
                {
                    string[] row = { idxCount.dwIdx.ToString(), idxCount.wCount.ToString(), idxCount.strParam };
                    dataGridViewGather.Rows.Add(row);
                }
            }

            dataGridViewNpcTalk.Rows.Clear();
            dataGridViewTalkWords.Rows.Clear();
            dataGridViewReceiveItem.Rows.Clear();

            if (taskInfo.MapNpc2Talk.Count > 0)
            {
                foreach (KeyValuePair<UInt32, CNpcTalk> kvp in taskInfo.MapNpc2Talk)
                {
                    UInt32 dwNpcIdx = kvp.Key;
                    CNpcTalk npcTalk = kvp.Value;
                    string[] row = { dwNpcIdx.ToString(), npcTalk.strName };
                    dataGridViewNpcTalk.Rows.Add(row);
                }
                dataGridViewNpcTalk.ClearSelection();

            }


            //成长
            this.dataGridView_grow.Rows.Clear();
            if (taskInfo.RoleProps.Count > 0)
            {
                foreach (CEnumValueExt obj in taskInfo.RoleProps)
                {
                    this.InsertRoleProp(obj);
                }
            }

            //行为
            this.dataGridView_behave.Rows.Clear();
            if (taskInfo.RoleActions.Count > 0)
            {
                foreach (CEnumValueStr obj in taskInfo.RoleActions)
                {
                    this.InsertAction(obj);
                }
            }

            //建筑
            this.dataGridView_build.Rows.Clear();
            if (taskInfo.Buildings.Count > 0 || taskInfo.Technics.Count > 0)
            {
                foreach (CIdxNameCount obj in taskInfo.Buildings)
                {
                    this.InsertBuilding(obj);
                }

                foreach (CIdxNameCount obj in taskInfo.Technics)
                {
                    this.InsertBuilding(obj);
                }
            }
        }

        private void InsertGeneralAward(EAwardGeneral type, UInt32 value)
        {
            if (type >= EAwardGeneral.end)
            {
                return;
            }

            string[] strRow = { };
            int index = this.dataGridView_award_general.Rows.Count;
            this.dataGridView_award_general.Rows.Add(strRow);
            DataGridViewRow row = this.dataGridView_award_general.Rows[index];

            DataGridViewCell cell = row.Cells[0];
            cell.Value = award_general[(int)type];

            cell = row.Cells[1];
            cell.Value = value;
        }

        /**
         * 刷新任务奖励区域
         */
        private void RefreshTaskAward(CTaskInfo taskInfo)
        {
            //一般属性
            this.dataGridView_award_general.Rows.Clear();
            foreach (SAwardGeneral obj in taskInfo.AwardGeneral)
            {
                this.InsertGeneralAward(obj.type, obj.value);
            }

            //属性奖励
            this.dataGridView_award_prop.Rows.Clear();
            foreach (CEnumValue obj in taskInfo.AwardProps)
            {
                this.InsertAwardProp(obj);
            }

            //佣兵奖励
            if (taskInfo.AwardMercen.Count > 0)
            {
                CIdxMercenPos[] arIdxMercen = (CIdxMercenPos[])taskInfo.AwardMercen.ToArray(typeof(CIdxMercenPos));
                foreach (CIdxMercenPos idxNameType in arIdxMercen)
                {
                    string[] row = { idxNameType.wIdx.ToString(), idxNameType.wNameIDx.ToString(), idxNameType.wPos.ToString()};
                    dgvMercenAward.Rows.Add(row);
                }
            }

            //称号奖励
            this.dataGridViewTitle.Rows.Clear();
            foreach (CIdxName obj in taskInfo.AwardTitles)
            {
                this.InsertAwardTitle(obj);
            }
            /*
            if (_curTaskInfo.fStarCoef > float.Epsilon)
                textBoxStarCoef.Text = _curTaskInfo.fStarCoef.ToString();
            else
                textBoxStarCoef.Text = "";
             
            if (_curTaskInfo.fRingCoef > float.Epsilon)
                textBoxRingCoef.Text = _curTaskInfo.fRingCoef.ToString();
            else
                textBoxRingCoef.Text = "";
            */
            dataGridViewMustItem.Rows.Clear();
            textBoxMustItemID.Clear();
            textBoxMustItemName.Clear();
            textBoxMustItemCount.Clear();
            cmbJobLimit.SelectedIndex = 0;
            if (taskInfo.ArMustAwardItem.Count > 0)
            {
                CIdxNameCountJob[] arIdxNameCount = (CIdxNameCountJob[])taskInfo.ArMustAwardItem.ToArray(typeof(CIdxNameCountJob));
                foreach (CIdxNameCountJob idxNameType in arIdxNameCount)
                {
                    string[] row = { idxNameType.dwIdx.ToString(), idxNameType.strName, idxNameType.wCount.ToString(), idxNameType.strJobName };
                    dataGridViewMustItem.Rows.Add(row);
                }
            }

            dataGridViewOptItem.Rows.Clear();
            textBoxOptItemID.Clear();
            textBoxOptItemName.Clear();
            textBoxOptItemCount.Clear();
            cmbJobLimitS.SelectedIndex = 0;
            if (taskInfo.ArOptAwardItem.Count > 0)
            {
                CIdxNameCountJob[] arIdxNameCount = (CIdxNameCountJob[])taskInfo.ArOptAwardItem.ToArray(typeof(CIdxNameCountJob));
                foreach (CIdxNameCountJob idxNameType in arIdxNameCount)
                {
                    string[] row = { idxNameType.dwIdx.ToString(), idxNameType.strName, idxNameType.wCount.ToString() };
                    dataGridViewOptItem.Rows.Add(row);
                }
            }

            ShowAward(taskInfo);
        }

        private void RefreshData(CTaskInfo taskInfo)
        {
            _bEditMode = true;

            //基本信息
            RefreshTaskBase(taskInfo);

            //任务描述
            RefreshTaskDesc(taskInfo);

            //任务限制
            RefreshTaskLimit(taskInfo);

            //任务过程
            RefreshTaskProcess(taskInfo);

            //任务奖励
            RefreshTaskAward(taskInfo);
        }

        private void dataGridViewTaskList_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count == 1)
            {
                tabControlConfig.Enabled = true;
                DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
                if (_mapRow2TaskInfo.ContainsKey(row))
                {
                    _curTaskInfo = _mapRow2TaskInfo[row];
                    RefreshData(_curTaskInfo);
                }
            }
            else
            {
                tabControlConfig.Enabled = false;
            }
        }

        private void buttonNewTask_Click(object sender, EventArgs e)
        {
            _curTaskInfo = new CTaskInfo();
            DataGridViewRow row = InsertNewTask(_curTaskInfo);
            row.Selected = true;
            RefreshData(_curTaskInfo);
        }

        private void textBoxTaskID_TextChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            UInt16.TryParse(textBoxTaskID.Text, out _curTaskInfo.wID);

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "TaskID");
        }

        private void textBoxTaskName_TextChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            _curTaskInfo.strName = textBoxTaskName.Text;
            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "TaskName");

            
        }

        private void textBoxTaskLevel_TextChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            Byte byLevel = 0;
            if (!Byte.TryParse(textBoxTaskLevel.Text, out byLevel))
                return;

            _curTaskInfo.byLevel = byLevel;

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "TaskLevel");
        }

        private void comboBoxTaskType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            _curTaskInfo.dwTaskType = (UInt32)(comboBoxTaskType.SelectedIndex + 1);
            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "TaskType");
        }

        private void checkBoxIsOpen_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (checkBoxIsOpen.Checked)
            {
                _curTaskInfo.byOpen = 1;
            }
            else
            {
                _curTaskInfo.byOpen = 0;
            }

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "OpenState");
        }

        private void checkBoxIsShared_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (checkBoxIsShared.Checked)
            {
                _curTaskInfo.byShare = 1;
            }
            else
            {
                _curTaskInfo.byShare = 0;
            }

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "ShareState");
        }

        private void checkBox_canGiveUp_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (checkBox_canGiveUp.Checked)
            {
                _curTaskInfo.byCanGiveUp = 1;
            }
            else
            {
                _curTaskInfo.byCanGiveUp = 0;
            }

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "CanGiveUp");
        }

        private void radioButton_noRepeat_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (radioButton_noRepeat.Checked)
            {
                _curTaskInfo.dwRepeat = 0;
                DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
                RefreshTaskColumn(row, "RepeatState");
            }
        }

        private void radioButton_dayRepeat_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (radioButton_dayRepeat.Checked)
            {
                UInt32 dwRepeat = UInt32.Parse(textBoxRepeatCount.Text);
                if (dwRepeat != _curTaskInfo.dwRepeat)
                {
                    _curTaskInfo.dwRepeat = dwRepeat;
                    DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
                    RefreshTaskColumn(row, "RepeatState");
                }
            }
        }

        private void textBoxRepeatCount_TextChanged(object sender, EventArgs e)
        {
            if (radioButton_dayRepeat.Checked)
            {
                _curTaskInfo.dwRepeat = UInt32.Parse(textBoxRepeatCount.Text);
            }
        }

        private void radioButton_repeat_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (radioButton_repeat.Checked)
            {
                _curTaskInfo.dwRepeat = UInt32.MaxValue;
                DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
                RefreshTaskColumn(row, "RepeatState");
            }
        }

        private void radioButton_NomalTask_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (radioButton_NomalTask.Checked)
            {
                _curTaskInfo.byTaskTypeExtent = (Byte)ETaskTypeExtent.eTaskTypeExtent_normal;
                DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
                RefreshTaskColumn(row, "FinishLimit");
            }
        }

        private void radioButton_rewardTask_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (radioButton_rewardTask.Checked)
            {
                _curTaskInfo.byTaskTypeExtent = (Byte)ETaskTypeExtent.eTaskTypeExtent_reward;
                DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
                RefreshTaskColumn(row, "FinishLimit");
            }
        }

/*
        private void checkBoxElite_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            DataGridViewCell cell = dataGridViewTaskList.SelectedRows[0].Cells["FinishLimit"];
            if (checkBoxElite.Checked)
            {
                checkBoxCommon.Checked = false;
                checkBoxGroup.Checked = false;
                cell.Value = "精英任务";
                _curTaskInfo.byLimit = 1;
            }
        }
 * 
        private void checkBoxGroup_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            DataGridViewCell cell = dataGridViewTaskList.SelectedRows[0].Cells["FinishLimit"];
            if (checkBoxGroup.Checked)
            {
                checkBoxCommon.Checked = false;
                checkBoxElite.Checked = false;
                cell.Value = "团队任务";
                _curTaskInfo.byLimit = 2;
            }
        }
 */

        private void checkBox_taskContent_CheckedChanged(object sender, EventArgs e)
        {
            TaskContentUIElement obj = null;
            foreach(DictionaryEntry item in this._taskContentUIHelper)
            {
                obj = item.Value as TaskContentUIElement;
                if(obj != null && obj.box == sender)
                {
                    if(obj.box.Checked)
                    {
                        obj.page.Enabled = true;
                        _curTaskInfo.dwContentType |= (UInt32)obj.type;
                    }
                    else
                    {
                        obj.page.Enabled = false;
                        _curTaskInfo.dwContentType &= ~(UInt32)obj.type;
                    }

                    break;
                }
            }  
        }









        private void textBoxStarTaskGroupID_TextChanged(object sender, EventArgs e)
        {
            if (!UInt32.TryParse(textBoxStarTaskGroupID.Text, out _curTaskInfo.dwStarGroupID))
                textBoxStarTaskGroupID.Text = "";
        }

        private void comboBoxStarTask_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxStarTask.SelectedIndex >= 0)
                _curTaskInfo.dwTaskStar = (UInt32)(comboBoxStarTask.SelectedIndex);
        }

        private void buttonSelectStarTask_Click(object sender, EventArgs e)
        {
            /*if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectTask, textBoxStarTaskGroupID, null);
            _formSelect.Show();*/
        }

        private void buttonTaskStart_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            ESelectType eSelectType = ESelectType.eSelectNone;
            switch (comboBoxTaskStart.SelectedIndex)
            {
                case 0:
                    eSelectType = ESelectType.eSelectNpc;
                    break;
                case 2:
                    eSelectType = ESelectType.eSelectItem;
                    break;
                default:
                    return;
            }
            _formSelect.LoadContent(eSelectType, textBoxTaskStartID, textBoxTaskStartName);
            _formSelect.Show();
        }

        private void buttonTaskSubmit_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            ESelectType eSelectType = ESelectType.eSelectNone;
            switch (comboBoxTaskSubmit.SelectedIndex)
            {
                case 0:
                    eSelectType = ESelectType.eSelectNpc;
                    break;
                case 2:
                    eSelectType = ESelectType.eSelectItem;
                    break;
                default:
                    return;
            }
            _formSelect.LoadContent(eSelectType, textBoxTaskSubmitID, textBoxTaskSubmitName);
            _formSelect.Show();
        }

        private void buttonGiveItem_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectItem, textBoxGiveItemID, textBoxGiveItemName);
            _formSelect.Show();
        }

        private void buttonKillMonster_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectMonster, textBoxKillMonsterID, textBoxKillMonsterName);
            _formSelect.Show();
        }

        private void buttonCollectItem_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectItem, textBoxCollectItemID, textBoxCollectItemName);
            _formSelect.Show();
        }

        private void buttonMustItem_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectItem, textBoxMustItemID, textBoxMustItemName);
            _formSelect.Show();
        }

        private void buttonOptItem_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectItem, textBoxOptItemID, textBoxOptItemName);
            _formSelect.Show();
        }

        private void buttonNpcTalk_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectNpc, textBoxNpcTalkID, textBoxNpcTalkName);
            _formSelect.Show();
        }

        private void buttonReceiveItem_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectItem, textBoxReceiveItemID, textBoxReceiveItemName);
            _formSelect.Show();
        }

        private void buttonSelectProbe_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectMap, textBoxProbeMapID, textBoxProbeMapName);
            _formSelect.Show();
        }

        private void buttonSelectGather_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectGather, textBoxGatherID, null);
            _formSelect.Show();
        }

        private void buttonTaskStartAdd_Click(object sender, EventArgs e)
        {
            if (comboBoxTaskStart.SelectedItem == null)
                return;
            CIdxNameType idxNameType = new CIdxNameType();
            idxNameType.byType = (Byte)(comboBoxTaskStart.SelectedIndex + 1);
            if ((Byte)ETargetType.eTargetScene == idxNameType.byType || (Byte)ETargetType.eTargetItem == idxNameType.byType)
            {
                textBoxTaskStartID.Text = "0";
                textBoxTaskStartName.Text = "";
            }
            if (!UInt32.TryParse(textBoxTaskStartID.Text, out idxNameType.dwIdx))
                return;

            idxNameType.strName = textBoxTaskStartName.Text;
            
            string[] row = { textBoxTaskStartID.Text, comboBoxTaskStart.SelectedItem.ToString(), textBoxTaskStartName.Text };
            dataGridViewTaskStart.Rows.Add(row);

            _curTaskInfo.ArTriggerTarget.Add(idxNameType);
        }

        private void buttonTaskStartDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewTaskStart.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewTaskStart.SelectedRows[0];
            dataGridViewTaskStart.Rows.Remove(row);
            UInt32 dwRowIdx = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
            foreach (Object obj in _curTaskInfo.ArTriggerTarget)
            {
                CIdxNameType idxNameType = (CIdxNameType)obj;
                if (idxNameType.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArTriggerTarget.Remove(obj);
                    break;
                }
            }
        }

        private void buttonTaskSubmitAdd_Click(object sender, EventArgs e)
        {
            if (comboBoxTaskSubmit.SelectedItem == null)
                return;
            CIdxNameType idxNameType = new CIdxNameType();
            if (!UInt32.TryParse(textBoxTaskSubmitID.Text, out idxNameType.dwIdx))
                return;

            idxNameType.strName = textBoxTaskSubmitName.Text;
            idxNameType.byType = (Byte)(comboBoxTaskSubmit.SelectedIndex + 1);

            string[] row = { textBoxTaskSubmitID.Text, comboBoxTaskSubmit.SelectedItem.ToString(), textBoxTaskSubmitName.Text };
            dataGridViewTaskSubmit.Rows.Add(row);

            _curTaskInfo.ArSubmitTarget.Add(idxNameType);
        }

        private void buttonTaskSubmitDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewTaskSubmit.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewTaskSubmit.SelectedRows[0];
            dataGridViewTaskSubmit.Rows.Remove(row);
            UInt32 dwRowIdx = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
            foreach (Object obj in _curTaskInfo.ArSubmitTarget)
            {
                CIdxNameType idxNameType = (CIdxNameType)obj;
                if (idxNameType.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArSubmitTarget.Remove(obj);
                    break;
                }
            }
        }

        private void buttonGiveItemAdd_Click(object sender, EventArgs e)
        {
            CIdxNameCount idxNameCount = new CIdxNameCount();
            if (!UInt32.TryParse(textBoxGiveItemID.Text, out idxNameCount.dwIdx))
                return;
            if (!UInt16.TryParse(textBoxGiveItemCount.Text, out idxNameCount.wCount))
                return;
            idxNameCount.strName = textBoxGiveItemName.Text;
            string[] row = { textBoxGiveItemID.Text, textBoxGiveItemName.Text, textBoxGiveItemCount.Text };
            dataGridViewGiveItem.Rows.Add(row);

            _curTaskInfo.ArGiveItem.Add(idxNameCount);
        }

        private void buttonGiveItemDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewGiveItem.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewGiveItem.SelectedRows[0];
            dataGridViewGiveItem.Rows.Remove(row);
            UInt32 dwRowIdx = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
            foreach (Object obj in _curTaskInfo.ArGiveItem)
            {
                CIdxNameCount idxNameCount = (CIdxNameCount)obj;
                if (idxNameCount.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArGiveItem.Remove(obj);
                    break;
                }
            }
        }

        private void buttonKillMonsterAdd_Click(object sender, EventArgs e)
        {
            CIdxNameCountEx idxNameCount = new CIdxNameCountEx();
            if (!UInt32.TryParse(textBoxKillMonsterID.Text, out idxNameCount.dwIdx))
                return;
            if (!UInt16.TryParse(textBoxKillMonsterCount.Text, out idxNameCount.wCount))
                return;
            idxNameCount.strName = textBoxKillMonsterName.Text;
            idxNameCount.strParam = textBoxKillMonsterParam.Text;
            string[] row = { textBoxKillMonsterID.Text, textBoxKillMonsterName.Text, textBoxKillMonsterCount.Text, "0", textBoxKillMonsterParam.Text };
            dataGridViewKillMonster.Rows.Add(row);

            _curTaskInfo.ArKillMonster.Add(idxNameCount);
        }

        private void buttonKillMonsterDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewKillMonster.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewKillMonster.SelectedRows[0];
            dataGridViewKillMonster.Rows.Remove(row);
            UInt32 dwRowIdx = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
            foreach (Object obj in _curTaskInfo.ArKillMonster)
            {
                CIdxNameCountEx idxNameCount = (CIdxNameCountEx)obj;
                if (idxNameCount.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArKillMonster.Remove(obj);
                    break;
                }
            }
        }

        private void buttonCollectItemAdd_Click(object sender, EventArgs e)
        {
            CIdxNameCount idxNameCount = new CIdxNameCount();
            if (!UInt32.TryParse(textBoxCollectItemID.Text, out idxNameCount.dwIdx))
                return;
            if (!UInt16.TryParse(textBoxCollectItemCount.Text, out idxNameCount.wCount))
                return;
            idxNameCount.strName = textBoxCollectItemName.Text;
            string[] row = { textBoxCollectItemID.Text, textBoxCollectItemName.Text, textBoxCollectItemCount.Text };
            dataGridViewCollectItem.Rows.Add(row);

            _curTaskInfo.ArCollectItem.Add(idxNameCount);
        }

        private void buttonCollectItemDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewCollectItem.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewCollectItem.SelectedRows[0];
            dataGridViewCollectItem.Rows.Remove(row);
            UInt32 dwRowIdx = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
            foreach (Object obj in _curTaskInfo.ArCollectItem)
            {
                CIdxNameCount idxNameCount = (CIdxNameCount)obj;
                if (idxNameCount.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArCollectItem.Remove(obj);
                    break;
                }
            }
        }

        private void buttonAddProbe_Click(object sender, EventArgs e)
        {
            CMapArea mapArea = new CMapArea();
            if (!UInt32.TryParse(textBoxProbeMapID.Text, out mapArea.dwMapID))
                return;
            mapArea.strName = textBoxProbeMapName.Text;
            if (!Int32.TryParse(textBoxProbeX1.Text, out mapArea.x))
                return;
            if (!Int32.TryParse(textBoxProbeZ1.Text, out mapArea.z))
                return;
            if (!Int32.TryParse(textBoxProbeX2.Text, out mapArea.x2))
                return;
            if (!Int32.TryParse(textBoxProbeZ2.Text, out mapArea.z2))
                return;
            mapArea.strParam = textBoxProbeParam.Text;
            string[] row = { textBoxProbeMapID.Text, textBoxProbeMapName.Text, textBoxProbeX1.Text, textBoxProbeZ1.Text, textBoxProbeX2.Text, textBoxProbeZ2.Text, textBoxProbeParam.Text };
            dataGridViewProbe.Rows.Add(row);

            _curTaskInfo.ArProbe.Add(mapArea);
        }

        private void buttonDelProbe_Click(object sender, EventArgs e)
        {
            if (dataGridViewProbe.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewProbe.SelectedRows[0];
            dataGridViewProbe.Rows.Remove(row);
            UInt32 dwMapID = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwMapID);
            foreach (Object obj in _curTaskInfo.ArProbe)
            {
                CMapArea mapArea = (CMapArea)obj;
                if (mapArea.dwMapID == dwMapID)
                {
                    _curTaskInfo.ArProbe.Remove(obj);
                    break;
                }
            }
        }

        private void buttonAddGather_Click(object sender, EventArgs e)
        {
            CGatherIdxCount idxCount = new CGatherIdxCount();
            if (!UInt32.TryParse(textBoxGatherID.Text, out idxCount.dwIdx))
                return;
            if (!UInt16.TryParse(textBoxGatherCount.Text, out idxCount.wCount))
                return;
            idxCount.strParam = textBoxGatherParam.Text;
            string[] row = { textBoxGatherID.Text, textBoxGatherCount.Text, textBoxGatherParam.Text };
            dataGridViewGather.Rows.Add(row);

            _curTaskInfo.ArGather.Add(idxCount);
        }

        private void buttonDelGather_Click(object sender, EventArgs e)
        {
            if (dataGridViewGather.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewGather.SelectedRows[0];
            dataGridViewGather.Rows.Remove(row);
            UInt32 dwDelGatherID = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwDelGatherID);
            foreach (Object obj in _curTaskInfo.ArGather)
            {
                CGatherIdxCount idxCount = (CGatherIdxCount)obj;
                if (dwDelGatherID == idxCount.dwIdx)
                {
                    _curTaskInfo.ArGather.Remove(obj);
                    break;
                }
            }
        }

        private void buttonAddTalkNpc_Click(object sender, EventArgs e)
        {
            UInt32 dwNpcIdx = 0;
            if (!UInt32.TryParse(textBoxNpcTalkID.Text, out dwNpcIdx))
                return;
            if (_curTaskInfo.MapNpc2Talk.ContainsKey(dwNpcIdx))
                 return;
            string[] row = { textBoxNpcTalkID.Text, textBoxNpcTalkName.Text };
            dataGridViewNpcTalk.Rows.Add(row);

            CNpcTalk npcTalk = new CNpcTalk();
            npcTalk.strName = textBoxNpcTalkName.Text;
            _curTaskInfo.MapNpc2Talk.Add(dwNpcIdx, npcTalk);
        }

        private void buttonDelTalkNpc_Click(object sender, EventArgs e)
        {
            if (dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = dataGridViewNpcTalk.SelectedRows[0];
            dataGridViewNpcTalk.Rows.Remove(row);
            UInt32 dwNpcIdx = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwNpcIdx);
            if (_curTaskInfo.MapNpc2Talk.ContainsKey(dwNpcIdx))
                _curTaskInfo.MapNpc2Talk.Remove(dwNpcIdx);
        }

        private void UpdateTalkWords(bool bDel, int delIndex)
        {
            UInt32 dwNpcIdx = 0;
            UInt32.TryParse(dataGridViewNpcTalk.SelectedRows[0].Cells[0].Value.ToString(), out dwNpcIdx);
            if (!_curTaskInfo.MapNpc2Talk.ContainsKey(dwNpcIdx))
                return;
            CNpcTalk npcTalk = _curTaskInfo.MapNpc2Talk[dwNpcIdx];
            npcTalk.ArChat = ArrayList.Repeat(null, dataGridViewTalkWords.Rows.Count);
            foreach (DataGridViewRow row in dataGridViewTalkWords.Rows)
            {
                int index = int.Parse(row.Cells[0].Value.ToString()) - 1;
                if (bDel && index > delIndex)
                {
                    --index;
                    row.Cells[0].Value = (index + 1).ToString();
                }
                CChat chat = new CChat();
                chat.strPC = row.Cells[1].Value.ToString();
                chat.strNPC = row.Cells[2].Value.ToString();
                npcTalk.ArChat[index] = chat;
            }
        }

        private void buttonAddTalkWords_Click(object sender, EventArgs e)
        {
            if (dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;
            
            int index = 0;
            if (dataGridViewTalkWords.SelectedRows.Count != 1)
            {
                string[] newRow = { (dataGridViewTalkWords.Rows.Count + 1).ToString(), textBoxPCWords.Text.Trim(), textBoxNPCWords.Text.Trim() };
                index = dataGridViewTalkWords.Rows.Add(newRow);
            }
            else
            {
                index = dataGridViewTalkWords.SelectedRows[0].Index + 1;
                string[] newRow = { (index + 1).ToString(), textBoxPCWords.Text.Trim(), textBoxNPCWords.Text.Trim() };
                dataGridViewTalkWords.Rows.Insert(index, newRow);
                for (int i = index + 1; i < dataGridViewTalkWords.Rows.Count; ++i)
                {
                    dataGridViewTalkWords.Rows[i].Cells[0].Value = (i + 1).ToString();
                }
            }
            DataGridViewRow row = dataGridViewTalkWords.Rows[index];
            dataGridViewTalkWords.CurrentCell = row.Cells[0];
            row.Selected = true;

            UpdateTalkWords(false, 0);
        }

        private void buttonUpdateTalkWords_Click(object sender, EventArgs e)
        {
            if (dataGridViewTalkWords.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = dataGridViewTalkWords.SelectedRows[0];
            row.Cells[1].Value = textBoxPCWords.Text.Trim();
            row.Cells[2].Value = textBoxNPCWords.Text.Trim();

            UpdateTalkWords(false, 0);
        }

        private void buttonDelTalkWords_Click(object sender, EventArgs e)
        {
            if (dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;
            if (dataGridViewTalkWords.SelectedRows.Count != 1)
                return;
            int delIndex = int.Parse(dataGridViewTalkWords.SelectedRows[0].Cells[0].Value.ToString()) - 1;
            dataGridViewTalkWords.Rows.Remove(dataGridViewTalkWords.SelectedRows[0]);

            UpdateTalkWords(true, delIndex);
        }

        private void buttonUpNpcWords_Click(object sender, EventArgs e)
        {
            if (dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;
            if (dataGridViewTalkWords.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewTalkWords.SelectedRows[0];
            if (row.Index == 0)
                return;
            int index = int.Parse(row.Cells[0].Value.ToString()) - 1;
            DataGridViewRow prevRow = dataGridViewTalkWords.Rows[row.Index - 1];
            dataGridViewTalkWords.Rows.Remove(row);
            dataGridViewTalkWords.Rows.Remove(prevRow);
            dataGridViewTalkWords.Rows.Insert(index - 1, row);
            dataGridViewTalkWords.Rows.Insert(index, prevRow);
            prevRow.Cells[0].Value = (index + 1).ToString();
            row.Cells[0].Value = index.ToString();
            dataGridViewTalkWords.CurrentCell = row.Cells[0];
            row.Selected = true;

            UpdateTalkWords(false, 0);
        }

        private void buttonDownNpcWords_Click(object sender, EventArgs e)
        {
            if (dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;
            if (dataGridViewTalkWords.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dataGridViewTalkWords.SelectedRows[0];
            if (row.Index == dataGridViewTalkWords.Rows.Count - 1)
                return;
            int index = int.Parse(row.Cells[0].Value.ToString()) - 1;
            DataGridViewRow nextRow = dataGridViewTalkWords.Rows[row.Index + 1];
            dataGridViewTalkWords.Rows.Remove(row);
            dataGridViewTalkWords.Rows.Remove(nextRow);
            dataGridViewTalkWords.Rows.Insert(index, nextRow);
            dataGridViewTalkWords.Rows.Insert(index + 1, row);
            nextRow.Cells[0].Value = (index + 1).ToString();
            row.Cells[0].Value = (index + 2).ToString();
            dataGridViewTalkWords.CurrentCell = row.Cells[0];
            row.Selected = true;

            UpdateTalkWords(false, 0);
        }

        private void buttonReceiveItemAdd_Click(object sender, EventArgs e)
        {
            if(dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;

            UInt32 npcID;
            UInt32.TryParse(dataGridViewNpcTalk.SelectedRows[0].Cells[0].Value.ToString(), out npcID);
            if(!this._curTaskInfo.MapNpc2Talk.ContainsKey(npcID))
                return;

            CNpcTalk npcTalk= this._curTaskInfo.MapNpc2Talk[npcID];

            UInt32 id;
            string name;
            UInt16 value;

            UInt32.TryParse(this.textBoxReceiveItemID.Text, out id);
            name = this.textBoxReceiveItemName.Text;
            UInt16.TryParse(this.textBoxReceiveItemCount.Text, out value);
            if (id <= 0 || name.Length <= 0 || value <= 0)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }


            CIdxNameCount item = new CIdxNameCount();
            item.dwIdx = id;
            item.strName = name;
            item.wCount = value;
            npcTalk.ArReceiveItem.Add(item);

            string[] row = { item.dwIdx.ToString(), item.strName, item.wCount.ToString() };
            dataGridViewReceiveItem.Rows.Add(row);
        }

        private void buttonReceiveItemDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewNpcTalk.SelectedRows.Count != 1 || dataGridViewReceiveItem.SelectedRows.Count != 1)
            {
                return;
            }

            UInt32 npcID;
            UInt32.TryParse(dataGridViewNpcTalk.SelectedRows[0].Cells[0].Value.ToString(), out npcID);
            if (!this._curTaskInfo.MapNpc2Talk.ContainsKey(npcID))
                return;

            CNpcTalk npcTalk = this._curTaskInfo.MapNpc2Talk[npcID];

            UInt32 itemID;
            UInt32.TryParse(dataGridViewReceiveItem.SelectedRows[0].Cells[0].Value.ToString(), out itemID);

            foreach (CIdxNameCount obj in npcTalk.ArReceiveItem)
            {
                if (obj.dwIdx == itemID)
                {
                    npcTalk.ArReceiveItem.Remove(obj);
                    break;
                }
            }

            dataGridViewReceiveItem.Rows.Remove(dataGridViewReceiveItem.SelectedRows[0]);
        }

        private void textBoxTaskDesc_TextChanged(object sender, EventArgs e)
        {
            if(_bEditMode)
                _curTaskInfo.taskTextDesc.ColorText = textBoxTaskDesc.Text;
        }

        private void textBoxTaskPurpose_TextChanged(object sender, EventArgs e)
        {
            if (_bEditMode)
                _curTaskInfo.taskTextPurpose.ColorText = textBoxTaskPurpose.Text;
        }

        private void textBoxTaskFail_TextChanged(object sender, EventArgs e)
        {
            if (_bEditMode)
                _curTaskInfo.taskTextFail.ColorText = textBoxTaskFail.Text;
        }

        private void textBoxTaskFinish_TextChanged(object sender, EventArgs e)
        {
            if (_bEditMode)
                _curTaskInfo.taskTextFinish.ColorText = textBoxTaskFinish.Text;
        }

        private void textBoxLimitTime_TextChanged(object sender, EventArgs e)
        {
            UInt32.TryParse(textBoxLimitTime.Text, out _curTaskInfo.dwLimitTime);
        }

        private void dataGridViewNpcTalk_SelectionChanged(object sender, EventArgs e)
        {
            dataGridViewTalkWords.Rows.Clear();
            dataGridViewReceiveItem.Rows.Clear();

            if (dataGridViewNpcTalk.SelectedRows.Count != 1)
                return;
            UInt32 dwNpcIdx = 0;
            UInt32.TryParse(dataGridViewNpcTalk.SelectedRows[0].Cells[0].Value.ToString(), out dwNpcIdx);
            if (!_curTaskInfo.MapNpc2Talk.ContainsKey(dwNpcIdx))
                return;
            CNpcTalk npcTalk = _curTaskInfo.MapNpc2Talk[dwNpcIdx];
            UInt32 dwIndex = 1;
            foreach (CChat chat in npcTalk.ArChat)
            {
                string[] row = { dwIndex.ToString(), chat.strPC.ToString(), chat.strNPC.ToString() };
                dataGridViewTalkWords.Rows.Add(row);
                ++dwIndex;
            }

            foreach (CIdxNameCount obj in npcTalk.ArReceiveItem)
            {
                string[] row = { obj.dwIdx.ToString(), obj.strName, obj.wCount.ToString()};
                dataGridViewReceiveItem.Rows.Add(row);
            }
        }

        private void dataGridViewTalkWords_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewTalkWords.SelectedRows.Count != 1)
                return;
            textBoxPCWords.Text = dataGridViewTalkWords.SelectedRows[0].Cells[1].Value.ToString();
            textBoxNPCWords.Text = dataGridViewTalkWords.SelectedRows[0].Cells[2].Value.ToString();
        }

        private void dataGridViewReceiveItem_SelectionChanged(object sender, EventArgs e)
        {

        }

        private void buttonChooseColor_Click(object sender, EventArgs e)
        {
            ColorDialog MyDialog = new ColorDialog();
            MyDialog.AllowFullOpen = false;
            MyDialog.ShowHelp = true;
            MyDialog.Color = textBoxTitleName.ForeColor;
            if (MyDialog.ShowDialog() == DialogResult.OK)
            {
                if (textBoxTaskDesc.SelectedText.Length > 0)
                {
                    textBoxTaskDesc.SelectionColor = MyDialog.Color;
                    _curTaskInfo.taskTextDesc.AddSelection(textBoxTaskDesc.SelectionStart, textBoxTaskDesc.SelectionStart + textBoxTaskDesc.SelectionLength - 1, MyDialog.Color.ToArgb());
                }
                else if (textBoxTaskPurpose.SelectedText.Length > 0)
                {
                    textBoxTaskPurpose.SelectionColor = MyDialog.Color;
                    _curTaskInfo.taskTextPurpose.AddSelection(textBoxTaskPurpose.SelectionStart, textBoxTaskPurpose.SelectionStart + textBoxTaskPurpose.SelectionLength - 1, MyDialog.Color.ToArgb());
                }
                else if (textBoxTaskFail.SelectedText.Length > 0)
                {
                    textBoxTaskFail.SelectionColor = MyDialog.Color;
                    _curTaskInfo.taskTextFail.AddSelection(textBoxTaskFail.SelectionStart, textBoxTaskFail.SelectionStart + textBoxTaskFail.SelectionLength - 1, MyDialog.Color.ToArgb());
                }
                else if (textBoxTaskFinish.SelectedText.Length > 0)
                {
                    textBoxTaskFinish.SelectionColor = MyDialog.Color;
                    _curTaskInfo.taskTextFinish.AddSelection(textBoxTaskFinish.SelectionStart, textBoxTaskFinish.SelectionStart + textBoxTaskFinish.SelectionLength - 1, MyDialog.Color.ToArgb());
                }
            }
        }

        private void buttonInsertName_Click(object sender, EventArgs e)
        {
            if (_curTextBox != null)
            {
                string strText = _curTextBox.Text;
                _curTextBox.Text = strText.Substring(0, _curTextBox.SelectionStart) + "$角色姓名$" + strText.Substring(_curTextBox.SelectionStart);
            }
        }

        private void buttonInsertClan_Click(object sender, EventArgs e)
        {
            if (_curTextBox != null)
            {
                string strText = _curTextBox.Text;
                _curTextBox.Text = strText.Substring(0, _curTextBox.SelectionStart) + "$角色阵营$" + strText.Substring(_curTextBox.SelectionStart);
            }
        }

        private void buttonInsertMonsterID_Click(object sender, EventArgs e)
        {
            if (_curTextBox == null)
                return;
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectMonster, _curTextBox);
            _formSelect.Show();
        }

        private void buttonInsertNpcID_Click(object sender, EventArgs e)
        {
            if (_curTextBox == null)
                return;
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectNpc, _curTextBox);
            _formSelect.Show();
        }

        private void buttonInsertGather_Click(object sender, EventArgs e)
        {
            if (_curTextBox == null)
                return;
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectGather, _curTextBox);
            _formSelect.Show();
        }

        private void textBoxTaskDesc_MouseClick(object sender, MouseEventArgs e)
        {
            textBoxTaskPurpose.SelectionLength = 0;
            textBoxTaskFail.SelectionLength = 0;
            textBoxTaskFinish.SelectionLength = 0;
            _curTextBox = textBoxTaskDesc;
        }

        private void textBoxTaskPurpose_MouseClick(object sender, MouseEventArgs e)
        {
            textBoxTaskDesc.SelectionLength = 0;
            textBoxTaskFail.SelectionLength = 0;
            textBoxTaskFinish.SelectionLength = 0;
            _curTextBox = textBoxTaskPurpose;
        }

        private void textBoxTaskFail_MouseClick(object sender, MouseEventArgs e)
        {
            textBoxTaskDesc.SelectionLength = 0;
            textBoxTaskPurpose.SelectionLength = 0;
            textBoxTaskFinish.SelectionLength = 0;
            _curTextBox = textBoxTaskFail;
        }

        private void textBoxTaskFinish_MouseClick(object sender, MouseEventArgs e)
        {
            textBoxTaskDesc.SelectionLength = 0;
            textBoxTaskPurpose.SelectionLength = 0;
            textBoxTaskFail.SelectionLength = 0;
            _curTextBox = textBoxTaskFinish;
        }

        private void buttonSearchID_Click(object sender, EventArgs e)
        {
            UInt32 dwSearchID = 0;
            if (!UInt32.TryParse(textBoxSearchTask.Text, out dwSearchID))
            {
                MessageBox.Show("数字格式非法", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            foreach (DataGridViewRow row in dataGridViewTaskList.Rows)
            {
                DataGridViewCell cellID = row.Cells[0];
                UInt32 dwID = 0;
                if (cellID.Value != null && UInt32.TryParse(cellID.Value.ToString(), out dwID) && dwSearchID == dwID)
                {
                    dataGridViewTaskList.ClearSelection();
                    dataGridViewTaskList.CurrentCell = row.Cells[0];
                    row.Selected = true;
                    return;
                }
            }
            MessageBox.Show("找不到该任务", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void buttonSearchName_Click(object sender, EventArgs e)
        {
            string strTaskName = textBoxSearchTask.Text.Trim();
            if (strTaskName.Length == 0)
                return;
            int startIndex = 0;
            if(dataGridViewTaskList.SelectedRows.Count > 0)
                startIndex = dataGridViewTaskList.SelectedRows[0].Index;
            foreach (DataGridViewRow row in dataGridViewTaskList.Rows)
            {
                if(row.Index <= startIndex)
                    continue;
                DataGridViewCell cellName = row.Cells[2];
                if (cellName.Value != null && cellName.Value.ToString().Contains(strTaskName))
                {
                    dataGridViewTaskList.ClearSelection();
                    dataGridViewTaskList.CurrentCell = row.Cells[0];
                    row.Selected = true;
                    return;
                }
            }
            MessageBox.Show("找不到该任务", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void buttonEditMode_Click(object sender, EventArgs e)
        {
            _bEditMode = true;
            buttonChooseColor.Enabled = false;
            textBoxTaskDesc.ReadOnly = false;
            textBoxTaskPurpose.ReadOnly = false;
            textBoxTaskFail.ReadOnly = false;
            textBoxTaskFinish.ReadOnly = false;
            buttonInsertName.Enabled = true;
            buttonInsertClan.Enabled = true;
            buttonInsertMonsterID.Enabled = true;
            buttonInsertNpcID.Enabled = true;
            buttonInsertGather.Enabled = true;
            buttonEditMode.BackColor = Color.Aqua;
            buttonColorMode.BackColor = Color.Transparent;
            textBoxTaskDesc.Text = _curTaskInfo.taskTextDesc.ColorText;
            textBoxTaskPurpose.Text = _curTaskInfo.taskTextPurpose.ColorText;
            textBoxTaskFail.Text = _curTaskInfo.taskTextFail.ColorText;
            textBoxTaskFinish.Text = _curTaskInfo.taskTextFinish.ColorText;
        }

        private void buttonColorMode_Click(object sender, EventArgs e)
        {
            _bEditMode = false;
            buttonChooseColor.Enabled = true;
            textBoxTaskDesc.ReadOnly = true;
            textBoxTaskPurpose.ReadOnly = true;
            textBoxTaskFail.ReadOnly = true;
            textBoxTaskFinish.ReadOnly = true;
            buttonInsertName.Enabled = false;
            buttonInsertClan.Enabled = false;
            buttonInsertMonsterID.Enabled = false;
            buttonInsertNpcID.Enabled = false;
            buttonInsertGather.Enabled = false;
            buttonEditMode.BackColor = Color.Transparent;
            buttonColorMode.BackColor = Color.Aqua;
            _curTaskInfo.taskTextDesc.ColorText = textBoxTaskDesc.Text;
            _curTaskInfo.taskTextPurpose.ColorText = textBoxTaskPurpose.Text;
            _curTaskInfo.taskTextFail.ColorText = textBoxTaskFail.Text;
            _curTaskInfo.taskTextFinish.ColorText = textBoxTaskFinish.Text;
            ShowColor(_curTaskInfo);
        }

        private void buttonMustItemAdd_Click(object sender, EventArgs e)
        {
            CIdxNameCountJob idxNameCount = new CIdxNameCountJob();
            if (!UInt32.TryParse(textBoxMustItemID.Text, out idxNameCount.dwIdx))
                return;
            if (!UInt16.TryParse(textBoxMustItemCount.Text, out idxNameCount.wCount))
                return;
            idxNameCount.strName = textBoxMustItemName.Text;
            int index = this.cmbJobLimit.SelectedIndex;
            if (index < 0)
            {
                index = 0;//无职业限制
                idxNameCount.strJobName = "无限制";
            }
            else
            {
                idxNameCount.strJobName = this.cmbJobLimit.Text;
            }
            idxNameCount.wJob = (UInt16)index;
            string[] row = { textBoxMustItemID.Text, textBoxMustItemName.Text, textBoxMustItemCount.Text, idxNameCount.strJobName};
            dataGridViewMustItem.Rows.Add(row);

            if (_curTaskInfo.ArMustAwardItem == null)
                _curTaskInfo.ArMustAwardItem = new ArrayList();
            _curTaskInfo.ArMustAwardItem.Add(idxNameCount);
            ShowAward(_curTaskInfo);
        }

        private void buttonMustItemDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewMustItem.SelectedRows.Count != 1 || dataGridViewMustItem.SelectedRows[0].IsNewRow)
                return;
            DataGridViewRow row = dataGridViewMustItem.SelectedRows[0];
            dataGridViewMustItem.Rows.Remove(row);
            foreach (Object obj in _curTaskInfo.ArMustAwardItem)
            {
                CIdxNameCountJob idxNameCount = (CIdxNameCountJob)obj;
                UInt32 dwRowIdx = 0;
                UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
                if (idxNameCount.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArMustAwardItem.Remove(obj);
                    break;
                }
            }
            ShowAward(_curTaskInfo);
        }

        private void buttonOptItemAdd_Click(object sender, EventArgs e)
        {
            CIdxNameCountJob idxNameCount = new CIdxNameCountJob();
            if (!UInt32.TryParse(textBoxOptItemID.Text, out idxNameCount.dwIdx))
                return;
            if (!UInt16.TryParse(textBoxOptItemCount.Text, out idxNameCount.wCount))
                return;
            idxNameCount.strName = textBoxOptItemName.Text;
            int index = this.cmbJobLimitS.SelectedIndex;
            if (index < 0)
            {
                index = 0;//无职业限制
                idxNameCount.strJobName = "无限制";
            }
            else
            {
                idxNameCount.strJobName = this.cmbJobLimitS.Text;
            }
            idxNameCount.wJob = (UInt16)index;
            string[] row = { textBoxOptItemID.Text, textBoxOptItemName.Text, textBoxOptItemCount.Text, idxNameCount.strJobName };
            dataGridViewOptItem.Rows.Add(row);

            _curTaskInfo.ArOptAwardItem.Add(idxNameCount);
            ShowAward(_curTaskInfo);
        }

        private void buttonOptItemDel_Click(object sender, EventArgs e)
        {
            if (dataGridViewOptItem.SelectedRows.Count != 1 || dataGridViewOptItem.SelectedRows[0].IsNewRow)
                return;
            DataGridViewRow row = dataGridViewOptItem.SelectedRows[0];
            dataGridViewOptItem.Rows.Remove(row);
            foreach (Object obj in _curTaskInfo.ArOptAwardItem)
            {
                CIdxNameCount idxNameCount = (CIdxNameCount)obj;
                UInt32 dwRowIdx = 0;
                UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx);
                if (idxNameCount.dwIdx == dwRowIdx)
                {
                    _curTaskInfo.ArOptAwardItem.Remove(obj);
                    break;
                }
            }
            ShowAward(_curTaskInfo);
        }
        /*
        private void textBoxStarCoef_TextChanged(object sender, EventArgs e)
        {
            if (!float.TryParse(textBoxStarCoef.Text, out _curTaskInfo.fStarCoef))
                textBoxStarCoef.Text = "";
        }

        private void textBoxRingCoef_TextChanged(object sender, EventArgs e)
        {
            if (!float.TryParse(textBoxRingCoef.Text, out _curTaskInfo.fRingCoef))
                textBoxStarCoef.Text = "";
        }
        */
        private void comboBox_limitCamp_SelectedIndexChanged(object sender, EventArgs e)
        {
            this._curTaskInfo.limitCamp = (Byte)(this.comboBox_limitCamp.SelectedIndex);
        }

        private void comboBox_limit_family_SelectedIndexChanged(object sender, EventArgs e)
        {
            this._curTaskInfo.limitFamily = (Byte)(this.comboBox_limit_family.SelectedIndex);
        }

        private void comboBoxSexLimit_SelectedIndexChanged(object sender, EventArgs e)
        {
            this._curTaskInfo.limitGender = (Byte)(this.comboBoxSexLimit.SelectedIndex);
        }

        private void textBoxReputeMin_TextChanged(object sender, EventArgs e)
        {
            if (null == this._curTaskInfo)
                return;

            UInt16.TryParse(this.textBoxReputeMin.Text, out this._curTaskInfo.limitReputeMin);
        }

        private void textBoxReputeMax_TextChanged(object sender, EventArgs e)
        {
            if (null == this._curTaskInfo)
                return;

            UInt16.TryParse(this.textBoxReputeMax.Text, out this._curTaskInfo.limitReputeMax);
        }

        private void textBoxGradeMin_TextChanged(object sender, EventArgs e)
        {
            if (null == this._curTaskInfo)
                return;

            UInt16.TryParse(this.textBoxGradeMin.Text, out this._curTaskInfo.limitJingJieMin);
        }

        private void textBoxGradeMax_TextChanged(object sender, EventArgs e)
        {
            if (null == this._curTaskInfo)
                return;

            UInt16.TryParse(this.textBoxGradeMax.Text, out this._curTaskInfo.limitJingJieMax);
        }

        private void checkBoxDateLimit_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxDateLimit.Checked)
            {
                this._curTaskInfo.limitDateFrom = this.dateTimePickerDateFrom.Value.Ticks;
                this._curTaskInfo.limitDateTo = this.dateTimePickerDateTo.Value.Ticks;
            }
            else
            {
                this._curTaskInfo.limitDateFrom = 0;
                this._curTaskInfo.limitDateTo = 0;
            }
        }

        private void dateTimePickerDateFrom_ValueChanged(object sender, EventArgs e)
        {
            if (this.checkBoxDateLimit.Checked)
            {
                this._curTaskInfo.limitDateFrom = this.dateTimePickerDateFrom.Value.Ticks;
            }
        }

        private void dateTimePickerDateTo_ValueChanged(object sender, EventArgs e)
        {
            if (this.checkBoxDateLimit.Checked)
            {
                this._curTaskInfo.limitDateTo = this.dateTimePickerDateTo.Value.Ticks;
            }
        }

        private void checkBoxTimeLimit_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxTimeLimit.Checked)
            {
                UInt16.TryParse(this.textBoxHourFrom.Text, out this._curTaskInfo.limitDayTimeFrom);
                UInt16.TryParse(this.textBoxHourTo.Text, out this._curTaskInfo.limitDayTimeTo);
            }
            else
            {
                this._curTaskInfo.limitDayTimeFrom = 0;
                this._curTaskInfo.limitDayTimeTo = 0;
            }
        }

        private void textBoxHourFrom_TextChanged(object sender, EventArgs e)
        {
            if (this.checkBoxTimeLimit.Checked)
            {
                UInt16.TryParse(this.textBoxHourFrom.Text, out this._curTaskInfo.limitDayTimeFrom);
            }
        }

        private void textBoxHourTo_TextChanged(object sender, EventArgs e)
        {
            if (this.checkBoxTimeLimit.Checked)
            {
                UInt16.TryParse(this.textBoxHourTo.Text, out this._curTaskInfo.limitDayTimeTo);
            }
        }

        private void buttonSelectPreTask_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadTaskContent(this, textBoxPreTaskID, textBoxPreTaskName);
            _formSelect.Show();
        }

        private void buttonSelectTitle_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectTitle, textBoxTitleID, textBoxTitleName);
            _formSelect.Show();
        }

        private void buttonAddTitle_Click(object sender, EventArgs e)
        {
            UInt32 id;
            UInt32.TryParse(this.textBoxTitleID.Text, out id);
            string name = this.textBoxTitleName.Text;
            if (id <= 0 || name.Length <= 0)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            foreach (CIdxName obj in this._curTaskInfo.AwardTitles)
            {
                if (obj.id == id)
                {
                    MessageBox.Show("奖励项目已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            CIdxName item = new CIdxName();
            item.id = id;
            item.name = name;
            this._curTaskInfo.AwardTitles.Add(item);
            this.InsertAwardTitle(item);
            this.ShowAward(this._curTaskInfo);
        }

        private void buttonDelTitle_Click(object sender, EventArgs e)
        {
            if (this.dataGridViewTitle.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridViewTitle.SelectedRows[0];
            UInt32 id;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out id);
            foreach (CIdxName obj in this._curTaskInfo.AwardTitles)
            {
                if (id == obj.id)
                {
                    this._curTaskInfo.AwardTitles.Remove(obj);
                    break;
                }
            }

            this.dataGridViewTitle.Rows.Remove(row);
        }

        private void button_award_generalAdd_Click(object sender, EventArgs e)
        {
            int index = this.comboBox_award_general.SelectedIndex;
            if (index < 0 || index >= (int)EAwardGeneral.end)
            {
                return;
            }

            UInt32 value;
            UInt32.TryParse(this.textBox_award_general.Text, out value);
            if(0 == value)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

//             if (this._curTaskInfo.awardGenerals[index] > 0)
//             {
//                 MessageBox.Show("奖励项目已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
//                 return;
//             }

            SAwardGeneral award = new SAwardGeneral();
            award.type = (EAwardGeneral)index;
            award.value = value;

            this._curTaskInfo.AwardGeneral.Add(award);
            this.InsertGeneralAward((EAwardGeneral)index, value);

            this.ShowAward(this._curTaskInfo);
        }

        private void button_award_generalRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridView_award_general.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridView_award_general.SelectedRows[0];
//             int index = (int)EAwardGeneral.eAwardGeneral_end;
//             string headTxt = (string)row.Cells[0].Value;
//             for (int i = 0; i < (int)EAwardGeneral.eAwardGeneral_end; ++i)
//             {
//                 if (award_general[i] == headTxt)
//                 {
//                     index = i;
//                     break;
//                 }
//             }
// 
//             if ((int)EAwardGeneral.eAwardGeneral_end == index)
//                 return;

            this._curTaskInfo.AwardGeneral.RemoveAt(row.Index);
            this.dataGridView_award_general.Rows.Remove(row); 
        }

        private void radioButton_preTaskAll_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton_preTaskAll.Checked)
            {
                this._curTaskInfo.limitPreTaskFlag = 0;
            }
        }

        private void radioButton_preTaskOne_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton_preTaskOne.Checked)
            {
                this._curTaskInfo.limitPreTaskFlag = 1;
            }
        }

        private void button_careerAdd_Click(object sender, EventArgs e)
        {
            int id = this.comboBox_SelectJob.SelectedIndex;
            
            if (id <= 0)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            foreach (CIdxName obj in this._curTaskInfo.LimitCareers)
            {
                if (obj.id == id)
                {
                    MessageBox.Show("奖励项目已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            CIdxName item = new CIdxName();
            item.id = (UInt32)id;
            item.name = this.comboBox_SelectJob.Text;
            this._curTaskInfo.LimitCareers.Add(item);
            this.InsertLimitCareer(item);
        }

        private void button_careerRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridViewJobLimit.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridViewJobLimit.SelectedRows[0];
            UInt32 id;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out id);
            foreach (CIdxName obj in this._curTaskInfo.LimitCareers)
            {
                if (id == obj.id)
                {
                    this._curTaskInfo.LimitCareers.Remove(obj);
                    break;
                }
            }

            this.dataGridViewJobLimit.Rows.Remove(row);
        }

        private void button_growAdd_Click(object sender, EventArgs e)
        {
            Byte type = (Byte)(this.comboBox_roleProp.SelectedIndex + 1);
            if (type <= (Byte)EProcessRoleProperty.eProcessRoleProperty_none)
                return;

            UInt32 value;
            UInt32.TryParse(this.textBox_roleProp.Text, out value);
            if (0 == value)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            //检查该type是否已经存在
            foreach (CEnumValueExt obj in this._curTaskInfo.RoleProps)
            {
                if (obj.type == type)
                {
                    MessageBox.Show("该角色行为已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            UInt32 dwid = 0;
            if (type == (Byte)EProcessRoleProperty.eProcessRoleProperty_repute)
            {
                UInt32.TryParse(this.textBox_campID.Text, out dwid);

                if (dwid <= 0 || this.textBox_campName.Text.Length <= 0)
                {
                    MessageBox.Show("阵营属性不合法，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            CEnumValueExt item = new CEnumValueExt();
            item.type = type;
            item.value = value;
            item.dwIdx = dwid;
            if (type == (Byte)EProcessRoleProperty.eProcessRoleProperty_repute)
            {
                item.name = this.textBox_campName.Text;
            }

            this._curTaskInfo.RoleProps.Add(item);
            this.InsertRoleProp(item);
        }

        private void button_growRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridView_grow.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridView_grow.SelectedRows[0];
            Byte type = (Byte)EProcessRoleProperty.eProcessRoleProperty_none;
            string headTxt = (string)row.Cells[0].Value;
            for (int i = 0; i < title_roleProps.Length; ++i)
            {
                if (title_roleProps[i] == headTxt)
                {
                    type = (Byte)(i + 1);
                    break;
                }
            }

            if (type <= (Byte)EProcessRoleProperty.eProcessRoleProperty_none)
                return;

            foreach (CEnumValueExt obj in this._curTaskInfo.RoleProps)
            {
                if (obj.type == type)
                {
                    this._curTaskInfo.RoleProps.Remove(obj);
                    break;
                }
            }
            this.dataGridView_grow.Rows.Remove(row);
        }

        private void button_behaveAdd_Click(object sender, EventArgs e)
        {
            Byte type = (Byte)(this.comboBox_behave_action.SelectedIndex + 1);
            if (type <= (Byte)EProcessAction.eProcessAction_none)
                return;

            UInt32 value;
            UInt32.TryParse(this.textBox_behave_action.Text, out value);
            if (0 == value)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            /*UInt32 param;
            UInt32.TryParse(this.textBox_behave_param.Text, out param);*/
           
            //检查该type是否已经存在
            foreach (CEnumValueStr obj in this._curTaskInfo.RoleActions)
            {
                if (obj.type == type)
                {
                    MessageBox.Show("该角色行为已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            CEnumValueStr item = new CEnumValueStr();
            item.type = type;
            item.value = value;
            item.param = this.textBox_behave_param.Text;
            //item.param = param;
            this._curTaskInfo.RoleActions.Add(item);
            this.InsertAction(item);
        }

        private void button_behaveRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridView_behave.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridView_behave.SelectedRows[0];
            Byte type = (Byte)EProcessAction.eProcessAction_none;
            string headTxt = (string)row.Cells[0].Value;
            for (int i = 0; i < title_actions.Length; ++i)
            {
                if (title_actions[i] == headTxt)
                {
                    type = (Byte)(i + 1);
                    break;
                }
            }

            if (type <= (Byte)EProcessAction.eProcessAction_none)
                return;

            foreach (CEnumValueStr obj in this._curTaskInfo.RoleActions)
            {
                if (obj.type == type)
                {
                    this._curTaskInfo.RoleActions.Remove(obj);
                    break;
                }
            }

            this.dataGridView_behave.Rows.Remove(row);
        }

        private void button_tecRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridView_build.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridView_build.SelectedRows[0];
            UInt32 id = UInt32.Parse((string)row.Cells[0].Value);
            string headTxt = (string)row.Cells[1].Value;
            this.dataGridView_build.Rows.Remove(row);

            foreach (CIdxNameCount obj in this._curTaskInfo.Buildings)
            {
                if (obj.dwIdx == id && obj.strName == headTxt)
                {
                    this._curTaskInfo.Buildings.Remove(obj);
                    return;
                }
            }

            foreach (CIdxNameCount obj in this._curTaskInfo.Technics)
            {
                if (obj.dwIdx == id && obj.strName == headTxt)
                {
                    this._curTaskInfo.Technics.Remove(obj);
                    return;
                }
            }
        }

        private void button_buildAdd_Click(object sender, EventArgs e)
        {
            UInt32 id = 0;
            string name = "";
            UInt16 value = 0;
            ArrayList list = null;
            if (sender == this.button_buildAdd)
            {
                UInt32.TryParse(this.textBox_buildID.Text, out id);
                name = this.textBox_buildName.Text;
                UInt16.TryParse(this.textBox_buildLevel.Text, out value);

                list = this._curTaskInfo.Buildings;
            }
            else if(sender == this.button_tecAdd)
            {
                UInt32.TryParse(this.textBox_tecID.Text, out id);
                name = this.textBox_tecName.Text;
                UInt16.TryParse(this.textBox_tecValue.Text, out value);

                list = this._curTaskInfo.Technics;
            }

            if(null == list)
                return;

            if (id <= 0 || name.Length <= 0 || value <= 0)
            {
                MessageBox.Show("数值不正确，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }


            foreach (CIdxNameCount obj in list)
            {
                if (id == obj.dwIdx)
                {
                    MessageBox.Show("该项目已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            CIdxNameCount item = new CIdxNameCount();
            item.dwIdx = id;
            item.strName = name;
            item.wCount = value;
            list.Add(item);
            this.InsertBuilding(item);
        }

        private void button_award_propAdd_Click(object sender, EventArgs e)
        {
            Byte type = (Byte)(this.comboBox_award_roleProp.SelectedIndex);
            if (type >= (Byte)EAwardProperty.end)
                return;

            UInt32 value;
            UInt32.TryParse(this.textBox_award_roleProp.Text, out value);
            if (0 == value)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            //检查该type是否已经存在
            foreach (CEnumValue obj in this._curTaskInfo.AwardProps)
            {
                if (obj.type == type)
                {
                    MessageBox.Show("该角色行为已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            if (type == (Byte)EAwardProperty.repute)
            {
                UInt32 id;
                UInt32.TryParse(this.textBox_award_campID.Text, out id);

                if (id <= 0 || this.textBox_award_campName.Text.Length <= 0)
                {
                    MessageBox.Show("阵营属性不合法，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }

                this._curTaskInfo.awardProp_campID = id;
                this._curTaskInfo.awardProp_campName = this.textBox_award_campName.Text;
            }

            CEnumValue item = new CEnumValue();
            item.type = type;
            item.value = value;
            this._curTaskInfo.AwardProps.Add(item);
            this.InsertAwardProp(item);
        }

        private void button_award_propRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridView_award_prop.SelectedRows.Count != 1)
                return;


            DataGridViewRow row = this.dataGridView_award_prop.SelectedRows[0];
            Byte type = (Byte)EAwardProperty.end;
            string headTxt = (string)row.Cells[0].Value;
            for (int i = 0; i < award_prop.Length; ++i)
            {
                if (award_prop[i] == headTxt)
                {
                    type = (Byte)(i + 1);
                    break;
                }
            }

            if (type >= (Byte)EAwardProperty.end)
                return;

            foreach (CEnumValue obj in this._curTaskInfo.AwardProps)
            {
                if (obj.type == type)
                {
                    this._curTaskInfo.AwardProps.Remove(obj);

                    if (type == (Byte)EAwardProperty.repute)
                    {
                        this._curTaskInfo.awardProp_campID = 0;
                        this._curTaskInfo.awardProp_campName = "";
                    }
                    break;
                }
            }

            this.dataGridView_award_prop.Rows.Remove(row);
        }

        private void button_award_selectCamp_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectCamp, textBox_campID, textBox_campName);
            _formSelect.Show();
        }

        private void dataGridView_award_prop_SelectionChanged(object sender, EventArgs e)
        {
            if (this.dataGridView_award_prop.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridView_award_prop.SelectedRows[0];
            Byte type = (Byte)EAwardProperty.end;
            string headTxt = (string)row.Cells[0].Value;
            for (int i = 0; i < award_prop.Length; ++i)
            {
                if (award_prop[i] == headTxt)
                {
                    type = (Byte)(i + 1);
                    break;
                }
            }

            if (type != (Byte)EAwardProperty.repute)
            {
                return;
            }

            foreach (CEnumValue obj in this._curTaskInfo.AwardProps)
            {
                if (obj.type == type)
                {
                    this.textBox_award_campID.Text = this._curTaskInfo.awardProp_campID.ToString();
                    this.textBox_award_campName.Text = this._curTaskInfo.awardProp_campName;
                    return;
                }
            }
        }

        private void button_preTaskAdd_Click(object sender, EventArgs e)
        {
            UInt32 id;
            UInt32.TryParse(this.textBoxPreTaskID.Text, out id);
            string name = this.textBoxPreTaskName.Text;
            if (id <= 0 || name.Length <= 0)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            foreach (CIdxName obj in this._curTaskInfo.PreTasks)
            {
                if (obj.id == id)
                {
                    MessageBox.Show("奖励项目已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            CIdxName item = new CIdxName();
            item.id = id;
            item.name = name;
            this._curTaskInfo.PreTasks.Add(item);
            this.InsertLimitPreTask(item);
        }

        private void button_preTaskRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridViewPreTask.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridViewPreTask.SelectedRows[0];
            UInt32 id;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out id);
            foreach (CIdxName obj in this._curTaskInfo.PreTasks)
            {
                if (id == obj.id)
                {
                    this._curTaskInfo.PreTasks.Remove(obj);
                    break;
                }
            }

            this.dataGridViewPreTask.Rows.Remove(row);
        }

        private void button_limit_selectCamp_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectCamp, textBox_limit_campID, textBox_limit_campName);
            _formSelect.Show();
        }

        private void button_limit_propAdd_Click(object sender, EventArgs e)
        {
            Byte type = (Byte)(this.comboBox_limit_roleProp.SelectedIndex + 1);
            if (type >= (Byte)ETaskLimitPropType.end)
                return;

            UInt32 value;
            UInt32.TryParse(this.textBox_limit_roleProp.Text, out value);
            if (0 == value)
            {
                MessageBox.Show("数值不正确，请重新填写！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            //检查该type是否已经存在
            foreach (CEnumValue obj in this._curTaskInfo.LimitProps)
            {
                if (obj.type == type)
                {
                    MessageBox.Show("该角色属性已存在，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
            }

            if (type == (Byte)ETaskLimitPropType.eRepute)
            {
                UInt32 id;
                UInt32.TryParse(this.textBox_limit_campID.Text, out id);

                if (id <= 0/* || this.textBox_limit_campName.Text.Length <= 0*/)
                {
                    MessageBox.Show("阵营属性不合法，请重新选择！", "添加失败", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }

                this._curTaskInfo.limitProp_campID = id;
                //this._curTaskInfo.limitProp_campName = this.textBox_limit_campName.Text;
            }

            CEnumValue item = new CEnumValue();
            item.type = type;
            item.value = value;
            this._curTaskInfo.LimitProps.Add(item);
            this.InsertLimitProp(item);
        }

        private void button_limit_propRemove_Click(object sender, EventArgs e)
        {
            if (this.dataGridView_limit_prop.SelectedRows.Count != 1)
                return;


            DataGridViewRow row = this.dataGridView_limit_prop.SelectedRows[0];
            Byte type = (Byte)ETaskLimitPropType.end;
            string headTxt = (string)row.Cells[0].Value;
            for (int i = 0; i < limit_prop.Length; ++i)
            {
                if (limit_prop[i] == headTxt)
                {
                    type = (Byte)(i + 1);
                    break;
                }
            }

            if (type >= (Byte)ETaskLimitPropType.end)
                return;

            foreach (CEnumValue obj in this._curTaskInfo.LimitProps)
            {
                if (obj.type == type)
                {
                    this._curTaskInfo.LimitProps.Remove(obj);

                    if (type == (Byte)ETaskLimitPropType.eRepute)
                    {
                        this._curTaskInfo.limitProp_campID = 0;
                        //this._curTaskInfo.limitProp_campName = "";
                    }
                    break;
                }
            }

            this.dataGridView_limit_prop.Rows.Remove(row);
        }

        private void dataGridView_limit_prop_SelectionChanged(object sender, EventArgs e)
        {
            if (this.dataGridView_limit_prop.SelectedRows.Count != 1)
                return;

            DataGridViewRow row = this.dataGridView_limit_prop.SelectedRows[0];
            Byte type = (Byte)ETaskLimitPropType.end;
            string headTxt = (string)row.Cells[0].Value;
            for (int i = 0; i < limit_prop.Length; ++i)
            {
                if (limit_prop[i] == headTxt)
                {
                    type = (Byte)(i);
                    break;
                }
            }

            if (type != (Byte)ETaskLimitPropType.eRepute)
            {
                return;
            }

            UInt32 campID = 0;
            foreach (CEnumValue obj in this._curTaskInfo.LimitProps)
            {
                if (obj.type == type)
                {
                    campID = this._curTaskInfo.limitProp_campID;
                    break;
                }
            }

            if (campID != 0)
            {
                this.textBox_limit_campID.Text = campID.ToString();
                //this.textBox_limit_campName.Text = this._curTaskInfo.limitProp_campName;

                //查表得到
            }
        }

        private void CollectMonster_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectMonster, txtCollectMonsterID, txtMonsterName);
            _formSelect.Show();
/*
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectTaskDrop, txtCollectMonsterID, txtMonsterName, txtItemID, txtItemName);
            _formSelect.Show();
*/
        }

        private void btnCollectItemAdd_Click(object sender, EventArgs e)
        { 
            CIdxKillItemCount idxNameCount = new CIdxKillItemCount();
            if (!UInt32.TryParse(txtCollectMonsterID.Text, out idxNameCount.dwIdx1))
                return;
            if (!UInt32.TryParse(txtItemID.Text, out idxNameCount.dwIdx2))
                return;
            if (!UInt16.TryParse(txtItemCount.Text, out idxNameCount.wCount))
                return;
            idxNameCount.strName1 = txtMonsterName.Text;
            idxNameCount.strName2 = txtItemName.Text;
            idxNameCount.strParam = txtItemParam.Text;

            string[] row = { txtCollectMonsterID.Text, txtMonsterName.Text, txtItemID.Text, txtItemName.Text, txtItemCount.Text, txtItemParam.Text };
            dgvKillMonsterItem.Rows.Add(row);

            _curTaskInfo.ArKillCollectItem.Add(idxNameCount);
        }

        private void btnCollectItemDel_Click(object sender, EventArgs e)
        {
            if (dgvKillMonsterItem.SelectedRows.Count != 1)
                return;
            DataGridViewRow row = dgvKillMonsterItem.SelectedRows[0];
            dgvKillMonsterItem.Rows.Remove(row);
            UInt32 dwRowIdx1 = 0;
            UInt32.TryParse(row.Cells[0].Value.ToString(), out dwRowIdx1);
            UInt32 dwRowIdx2 = 0;
            UInt32.TryParse(row.Cells[2].Value.ToString(), out dwRowIdx2);
            foreach (Object obj in _curTaskInfo.ArKillCollectItem)
            {
                CIdxKillItemCount idxNameCount = (CIdxKillItemCount)obj;
                if (idxNameCount.dwIdx1 == dwRowIdx1 && idxNameCount.dwIdx2 == dwRowIdx2)
                {
                    _curTaskInfo.ArKillCollectItem.Remove(obj);
                    break;
                }
            }
        }

        private void cbIsLevel_CheckedChanged(object sender, EventArgs e)
        {
            if (dataGridViewTaskList.SelectedRows.Count != 1)
                return;

            if (cbIsLevel.Checked)
            {
                _curTaskInfo.byAwardLinkLevel = 1;
            }
            else
            {
                _curTaskInfo.byAwardLinkLevel = 0;
            }

            DataGridViewRow row = dataGridViewTaskList.SelectedRows[0];
            RefreshTaskColumn(row, "AwardLinkLevel");
        }

        private void button_selectBuild_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectBuild, textBox_buildID, textBox_buildName);
            _formSelect.Show();
        }

        private void button_selectTec_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectScience, textBox_tecID, textBox_tecName);
            _formSelect.Show();
        }

        private void button_selectCamp_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectCamp, textBox_campID, textBox_campName);
            _formSelect.Show();
        }
        /*
        private void cmbRaceLimit_SelectedIndexChanged(object sender, EventArgs e)
        {
            this._curTaskInfo.limitRace = (Byte)(this.cmbRaceLimit.SelectedIndex);
        }
        */

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton1.Checked)
            {
                this._curTaskInfo.ProbeFlag = 0;
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton2.Checked)
            {
                this._curTaskInfo.ProbeFlag = 1;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (_formSelect != null)
                _formSelect.Dispose();
            _formSelect = new FormSelect();
            _formSelect.LoadContent(ESelectType.eSelectItem, txtItemID, txtItemName);
            _formSelect.Show();
        }
    }

    public class CIDComparer : IComparer
    {
        public int Compare(object x, object y)
        {
            DataGridViewRow DataGridViewRow1 = (DataGridViewRow)x;
            DataGridViewRow DataGridViewRow2 = (DataGridViewRow)y;

            UInt16 wTaskID1 = 0;
            UInt16.TryParse(DataGridViewRow1.Cells[0].Value.ToString(), out wTaskID1);

            UInt16 wTaskID2 = 0;
            UInt16.TryParse(DataGridViewRow2.Cells[0].Value.ToString(), out wTaskID2);
            return wTaskID1 - wTaskID2;
        }
    }

    public class CLevelComparer : IComparer
    {
        public int Compare(object x, object y)
        {
            DataGridViewRow DataGridViewRow1 = (DataGridViewRow)x;
            DataGridViewRow DataGridViewRow2 = (DataGridViewRow)y;

            UInt16 wLevel1 = 0;
            UInt16.TryParse(DataGridViewRow1.Cells[1].Value.ToString(), out wLevel1);

            UInt16 wLevel2 = 0;
            UInt16.TryParse(DataGridViewRow2.Cells[1].Value.ToString(), out wLevel2);
            return wLevel1 - wLevel2;
        }
    }

    /**
     * 任务定义相关
     */ 
    public class TaskContentUIElement
    {
        public EContentType type;
        public CheckBox box;
        public TabPage page;

        public TaskContentUIElement(EContentType type, 
            System.Windows.Forms.CheckBox box, 
            System.Windows.Forms.TabPage page)
        {
            this.type = type;
            this.box = box;
            this.page = page;
        }
    }
}
