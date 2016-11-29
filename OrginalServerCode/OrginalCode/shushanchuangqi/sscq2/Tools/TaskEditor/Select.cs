using System;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Windows.Forms;

namespace TaskEditor
{
    public enum ESelectType
    {
        eSelectNone,
        eSelectNpc,
        eSelectItem,
        eSelectMonster,
        eSelectSkill,
        eSelectMap,
        eSelectGather,
        eSelectTask,
        eSelectTaskDrop,
        eSelectBuild,
        eSelectScience,
        eSelectCamp,
        eSelectTitle
    };

    public partial class FormSelect : Form
    {
        Dictionary<ESelectType, string> _mapType2FileName = new Dictionary<ESelectType, string>();

        ESelectType _eSelectType = ESelectType.eSelectNone;
        TextBox _textID;
        TextBox _textName;
        TextBox _textID1;
        TextBox _textName1;
        RichTextBox _richTextBox;

        bool bInit = true;

        public FormSelect()
        {
            _mapType2FileName.Add(ESelectType.eSelectNpc, "Config/NpcProp.xml");
            _mapType2FileName.Add(ESelectType.eSelectItem, "Config/Item.xml");
            _mapType2FileName.Add(ESelectType.eSelectMonster, "Config/MonsterGroup.xml");
            _mapType2FileName.Add(ESelectType.eSelectSkill, "Config/SkillBase.xml");
            _mapType2FileName.Add(ESelectType.eSelectMap, "Config/Map.xml");
            _mapType2FileName.Add(ESelectType.eSelectGather, "Config/Gather.xml");
            //_mapType2FileName.Add(ESelectType.eSelectTask, "Config/TaskList.xml");
            _mapType2FileName.Add(ESelectType.eSelectTaskDrop, "Config/TaskDrop.xml");
            _mapType2FileName.Add(ESelectType.eSelectBuild, "Config/BuildingOpen.xml");
            _mapType2FileName.Add(ESelectType.eSelectScience, "Config/Library.xml");
            _mapType2FileName.Add(ESelectType.eSelectCamp, "Config/Camp.xml");
            _mapType2FileName.Add(ESelectType.eSelectTitle, "Config/Title.xml");
            InitializeComponent();
        }

        private XmlDocument LoadDocument(string fileName)
        {
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.ConformanceLevel = ConformanceLevel.Fragment;
            settings.IgnoreWhitespace = true;
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(fileName, settings);
            XmlDocument doc = new XmlDocument();
            doc.Load(reader);
            return doc;
        }

        public void LoadContent(ESelectType eSelectType, TextBox textID, TextBox textName)
        {
            _textID = textID;
            _textName = textName;
            textBoxUrl.Visible = false;
            buttonInsert.Visible = false;
            LoadContent(eSelectType);
        }

        public void LoadContent(ESelectType eSelectType, TextBox textID, TextBox textName, TextBox textID1, TextBox textName1)
        {
            _textID = textID;
            _textID1 = textID1;
            _textName = textName;
            _textName1 = textName1;
            textBoxUrl.Visible = false;
            buttonInsert.Visible = false;
            LoadContent(eSelectType);
        }

        public void LoadContent(ESelectType eSelectType, RichTextBox richTextBox)
        {
            _richTextBox = richTextBox;
            textBoxUrl.Visible = true;
            buttonInsert.Visible = true;
            LoadContent(eSelectType);
        }

        public void LoadContent(ESelectType eSelectType)
        {
            _eSelectType = eSelectType;
            if (!_mapType2FileName.ContainsKey(eSelectType))
            {
                MessageBox.Show("找不到该配置文件", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            string fileName = _mapType2FileName[eSelectType];
            FileInfo fi = new FileInfo(fileName);
            if (!fi.Exists)
            {
                MessageBox.Show("找不该配置文件" + fileName, "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            XmlDocument doc = null;
            
            try
            {
                doc = LoadDocument(fileName);
            }
            catch (System.Xml.XmlException ex)
            {
                using (StreamReader sr = File.OpenText(fileName))
                {
                    string s = sr.ReadLine();
                    if (!s.Contains("<?xml"))
                    {
                        string text = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" + sr.ReadToEnd();
                        sr.Close();
                        StreamWriter sw = new StreamWriter(fileName);
                        sw.Write(text);
                    }
                }
                doc = LoadDocument(fileName);
            }
            
            ArrayList arColumn = new ArrayList();
            XmlElement elem = CTaskInfoMgr.GetDescendElement(doc, "Table");
            if (null == elem)
            {
                return;
            }

            bool bCreateColumn = true;
            foreach (XmlNode node in elem.ChildNodes)
            {
                if (node.GetType() == typeof(XmlElement))
                {
                    XmlElement elemData = (XmlElement)node;
                    ArrayList arData = new ArrayList();
                    foreach (XmlAttribute attr in elemData.Attributes)
                    {
                        if (bCreateColumn)
                        {
                            DataGridViewColumn column = new DataGridViewTextBoxColumn();
                            column.HeaderText = attr.Name;
                            column.Name = attr.Name;
                            arColumn.Add(column);
                        }
                        arData.Add(attr.Value);
                    }
                    if (bCreateColumn)
                    {
                        DataGridViewColumn[] arDataGridViewColumn = (DataGridViewColumn[])arColumn.ToArray(typeof(DataGridViewColumn));
                        dataGridViewXML.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
                        dataGridViewXML.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                        dataGridViewXML.EditMode = DataGridViewEditMode.EditProgrammatically;
                        dataGridViewXML.Columns.AddRange(arDataGridViewColumn);
                    }
                    bCreateColumn = false;
                    string[] arDataText = (string[])arData.ToArray(typeof(string));
                    dataGridViewXML.Rows.Add(arDataText);
                }
            }
        }

        public void LoadTaskContent(FormEditor fe, TextBox textID, TextBox textName)
        {
            _eSelectType = ESelectType.eSelectTask;
            _textID = textID;
            _textName = textName;
            textBoxUrl.Visible = false;
            buttonInsert.Visible = false;
            this.dataGridViewXML.RowHeadersWidth = 20;
            this.dataGridViewXML.RowTemplate.Height = 23;
            this.dataGridViewXML.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            System.Windows.Forms.DataGridView dgv = fe.GetTaskListGridView();
            for (int i = 0; i < dgv.Columns.Count; ++i)
            {
                dataGridViewXML.Columns.Add(dgv.Columns[i].Clone() as DataGridViewColumn);
            }
            for (int j = 0; j < dgv.Rows.Count; ++j)
            {
                int idx = dataGridViewXML.Rows.Add();
                for (int i = 0; i < dgv.Columns.Count; ++i)
                {
                    dataGridViewXML.Rows[idx].Cells[i].Value = dgv.Rows[j].Cells[i].Value.ToString();
                }
            }
        }

        private void dataGridViewXML_SelectionChanged(object sender, EventArgs e)
        {
            if (bInit)
            {
                dataGridViewXML.ClearSelection();
                bInit = false;
            }
            if (dataGridViewXML.SelectedRows.Count != 1)
                return;
            try
            {
                DataGridViewCell cellID = dataGridViewXML.SelectedRows[0].Cells[0];
                string strID = cellID.Value.ToString();
                if (_textID != null)
                    _textID.Text = strID;
                if (_textName != null)
                {
                    if (_eSelectType == ESelectType.eSelectTaskDrop)
                    {
                        DataGridViewCell cellName = dataGridViewXML.SelectedRows[0].Cells["Name"];
                        _textName.Text = cellName.Value.ToString();
                        cellName = dataGridViewXML.SelectedRows[0].Cells["ItemID"];
                        _textID1.Text = cellName.Value.ToString();
                        cellName = dataGridViewXML.SelectedRows[0].Cells["ItemName"];
                        _textName1.Text = cellName.Value.ToString();
                    }
                    else if (_eSelectType == ESelectType.eSelectTask)
                    {
                        DataGridViewCell cellName = dataGridViewXML.SelectedRows[0].Cells[2];
                        _textName.Text = cellName.Value.ToString();
                    }
                    else
                    {
                        DataGridViewCell cellName = dataGridViewXML.SelectedRows[0].Cells["Name"];
                        _textName.Text = cellName.Value.ToString();
                    }
                }
                if (textBoxUrl.Visible)
                {
                    switch (_eSelectType)
                    {
                        case ESelectType.eSelectMonster:
                            textBoxUrl.Text = "<url value='0," + strID + "'>";
                            break;
                        case ESelectType.eSelectNpc:
                            textBoxUrl.Text = "<url value='1," + strID + "'>";
                            break;
                        case ESelectType.eSelectGather:
                            textBoxUrl.Text = "<url value='2," + strID + "'>";
                            break;
                    }
                }
            }
            catch (System.Exception ex)
            {
            }
        }

        private void buttonSearchID_Click(object sender, EventArgs e)
        {
            UInt32 dwSearchIdx = 0;
            if (!UInt32.TryParse(textBoxSearchID.Text, out dwSearchIdx))
                return;
            foreach (DataGridViewRow row in dataGridViewXML.Rows)
            {
                DataGridViewCell cellID = row.Cells[0];
                UInt32 dwIdx = 0;
                if (cellID.Value != null && UInt32.TryParse(cellID.Value.ToString(), out dwIdx) && dwSearchIdx == dwIdx)
                {
                    dataGridViewXML.ClearSelection();
                    dataGridViewXML.CurrentCell = row.Cells[0];
                    row.Selected = true;
                    return;
                }
            }
            MessageBox.Show("找不到该ID", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void buttonInsert_Click(object sender, EventArgs e)
        {
            if (textBoxUrl.Text.Length == 0 || _richTextBox == null)
                return;
            string strText = _richTextBox.Text;
            _richTextBox.Text = strText.Substring(0, _richTextBox.SelectionStart) + textBoxUrl.Text.Trim() + strText.Substring(_richTextBox.SelectionStart);
            Dispose();
        }
    }
}
