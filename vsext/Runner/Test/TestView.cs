// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace NullUnit.Runner.Test
{
    partial class TestView : UserControl, ITestView
    {
        public ITestPresenter Presenter { set; private get; }

        public Control ProvidedControl
        {
            get
            {
                return this;
            }
        }

        public IEnumerable<string> SelectedTests
        {
            get
            {
                TreeNode tn = treeView.SelectedNode;

                List<string> selection = new List<string>();

                if (tn != null)
                {
                    if (tn.Parent != null)
                    {
                        selection.Add(tn.Parent.Name + "." + tn.Name);
                    }
                    else
                    {
                        selection.Add(tn.Name);
                    }
                }

                return selection;
            }
        }

        public TestView()
        {
            InitializeComponent();
        }

        public void Clear()
        {
            treeView.Nodes.Clear();
            groupBoxFailureTrace.Visible = false;
        }

        int imageIndexFromTestState(TestState state)
        {
            switch (state)
            {
                default:
                case TestState.Unknown:
                    return 0;

                case TestState.Fail:
                    return 1;

                case TestState.Pass:
                    return 2;
            }
        }

        public void AddCaseResult(string suiteName, string caseName, string result,
            string filename, int lineNumber, TestState state)
        {
            List<ListViewItem> nodes = GetCaseNode(suiteName, caseName).Tag as List<ListViewItem>;

            if (nodes != null)
            {
                ListViewItem item = new ListViewItem();
                item.ImageIndex = imageIndexFromTestState(state);
                item.Text = result;
                item.SubItems.Add(Path.GetFileName(filename));
                item.SubItems.Add(lineNumber.ToString());

                nodes.Add(item);
            }
        }

        TreeNode GetSuiteNode(string suiteName)
        {
            TreeNode suiteNode = treeView.Nodes[suiteName];
            if (suiteNode == null)
            {
                treeView.Nodes.Add(suiteName, suiteName);
                suiteNode = treeView.Nodes[suiteName];
                suiteNode.StateImageIndex = 2;
            }

            return suiteNode;
        }

        TreeNode GetCaseNode(string suiteName, string caseName)
        {
            TreeNode suiteNode = GetSuiteNode(suiteName);

            TreeNode caseNode = suiteNode.Nodes[caseName];
            if (caseNode == null)
            {
                suiteNode.Nodes.Add(caseName, caseName);
                caseNode = suiteNode.Nodes[caseName];
                caseNode.StateImageIndex = 0;
                caseNode.Tag = new List<ListViewItem>();
            }

            return caseNode;
        }

        public void AddSuite(string suiteName)
        {
            GetSuiteNode(suiteName);
        }

        public void SetCaseState(string suiteName, string caseName, TestState state)
        {
            TreeNode suiteNode = GetSuiteNode(suiteName);
            TreeNode caseNode = GetCaseNode(suiteName, caseName);

            int imageIndex = imageIndexFromTestState(state);

            int currentIndex = caseNode.StateImageIndex;
            if (currentIndex != 1)
            {
                caseNode.StateImageIndex = imageIndex;
            }

            // Update suite index:
            int suiteImageIndex = 2;
            foreach (TreeNode childNode in suiteNode.Nodes)
            {
                if (childNode.StateImageIndex == 0)
                {
                    suiteImageIndex = 0;
                }
                else if (childNode.StateImageIndex == 1)
                {
                    suiteImageIndex = 1;
                    break;
                }
            }

            suiteNode.StateImageIndex = suiteImageIndex;

            treeView.Update();
        }

        private void treeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            List<ListViewItem> resultList = e.Node.Tag as List<ListViewItem>;

            if (resultList != null)
            {
                groupBoxFailureTrace.Visible = true;
                listViewFailures.Items.Clear();

                foreach(ListViewItem n in resultList)
                {
                    listViewFailures.Items.Add(n);
                }
            }
            else
            {
                groupBoxFailureTrace.Visible = false;
            }

            Presenter.SelectionChanged();
        }
    }
}
