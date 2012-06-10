// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

namespace NullUnit.Runner.Test
{
    partial class TestView
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TestView));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBoxTestCases = new System.Windows.Forms.GroupBox();
            this.treeView = new System.Windows.Forms.TreeView();
            this.caseStateImageList = new System.Windows.Forms.ImageList(this.components);
            this.groupBoxFailureTrace = new System.Windows.Forms.GroupBox();
            this.listViewFailures = new System.Windows.Forms.ListView();
            this.columnHeaderReason = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeaderFilename = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeaderLineNumber = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBoxTestCases.SuspendLayout();
            this.groupBoxFailureTrace.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBoxTestCases);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.groupBoxFailureTrace);
            this.splitContainer1.Size = new System.Drawing.Size(533, 348);
            this.splitContainer1.SplitterDistance = 187;
            this.splitContainer1.TabIndex = 0;
            // 
            // groupBoxTestCases
            // 
            this.groupBoxTestCases.Controls.Add(this.treeView);
            this.groupBoxTestCases.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBoxTestCases.Location = new System.Drawing.Point(0, 0);
            this.groupBoxTestCases.Name = "groupBoxTestCases";
            this.groupBoxTestCases.Size = new System.Drawing.Size(187, 348);
            this.groupBoxTestCases.TabIndex = 1;
            this.groupBoxTestCases.TabStop = false;
            this.groupBoxTestCases.Text = "Test Cases";
            // 
            // treeView
            // 
            this.treeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView.Location = new System.Drawing.Point(3, 16);
            this.treeView.Name = "treeView";
            this.treeView.Size = new System.Drawing.Size(181, 329);
            this.treeView.StateImageList = this.caseStateImageList;
            this.treeView.TabIndex = 0;
            this.treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView_AfterSelect);
            // 
            // caseStateImageList
            // 
            this.caseStateImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("caseStateImageList.ImageStream")));
            this.caseStateImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.caseStateImageList.Images.SetKeyName(0, "test_unknown.png");
            this.caseStateImageList.Images.SetKeyName(1, "test_fail.png");
            this.caseStateImageList.Images.SetKeyName(2, "test_pass.png");
            // 
            // groupBoxFailureTrace
            // 
            this.groupBoxFailureTrace.Controls.Add(this.listViewFailures);
            this.groupBoxFailureTrace.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBoxFailureTrace.Location = new System.Drawing.Point(0, 0);
            this.groupBoxFailureTrace.Name = "groupBoxFailureTrace";
            this.groupBoxFailureTrace.Size = new System.Drawing.Size(342, 348);
            this.groupBoxFailureTrace.TabIndex = 0;
            this.groupBoxFailureTrace.TabStop = false;
            this.groupBoxFailureTrace.Text = "Failure Trace";
            // 
            // listViewFailures
            // 
            this.listViewFailures.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderReason,
            this.columnHeaderFilename,
            this.columnHeaderLineNumber});
            this.listViewFailures.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listViewFailures.Location = new System.Drawing.Point(3, 16);
            this.listViewFailures.MultiSelect = false;
            this.listViewFailures.Name = "listViewFailures";
            this.listViewFailures.ShowGroups = false;
            this.listViewFailures.Size = new System.Drawing.Size(336, 329);
            this.listViewFailures.SmallImageList = this.caseStateImageList;
            this.listViewFailures.TabIndex = 0;
            this.listViewFailures.UseCompatibleStateImageBehavior = false;
            this.listViewFailures.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderReason
            // 
            this.columnHeaderReason.Text = "Reason";
            this.columnHeaderReason.Width = 187;
            // 
            // columnHeaderFilename
            // 
            this.columnHeaderFilename.Text = "File";
            this.columnHeaderFilename.Width = 94;
            // 
            // columnHeaderLineNumber
            // 
            this.columnHeaderLineNumber.Text = "Line";
            this.columnHeaderLineNumber.Width = 38;
            // 
            // TestView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "TestView";
            this.Size = new System.Drawing.Size(533, 348);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBoxTestCases.ResumeLayout(false);
            this.groupBoxFailureTrace.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBoxFailureTrace;
        private System.Windows.Forms.TreeView treeView;
        private System.Windows.Forms.ImageList caseStateImageList;
        private System.Windows.Forms.ListView listViewFailures;
        private System.Windows.Forms.ColumnHeader columnHeaderReason;
        private System.Windows.Forms.ColumnHeader columnHeaderFilename;
        private System.Windows.Forms.ColumnHeader columnHeaderLineNumber;
        private System.Windows.Forms.GroupBox groupBoxTestCases;
    }
}
