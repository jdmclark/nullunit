// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NullUnit.Framework;
using NullUnit.Runner.Events;
using NullUnit.Runner.Events.State;

namespace NullUnit.Runner
{
    public partial class MainFrame : Form, IAcceptsOneControl
    {
        Services services;

        public Control Control
        {
            set
            {
                contentPanel.Controls.Clear();

                if (value != null)
                {
                    value.Dock = DockStyle.Fill;
                    contentPanel.Controls.Add(value);
                }
            }
        }

        public MainFrame()
        {
            services = new Services(this);

            services.EventBus.AddHandler<PageTitleEventArgs>(onTitleChanged);
            services.EventBus.AddHandler<StatusEventArgs>(onStatusChanged);
            services.EventBus.AddHandler<CommandEnableEventArgs>(onCommandEnableChanged);
            services.EventBus.AddHandler<ExitEventArgs>(onExitEvent);
            services.EventBus.AddHandler<OpenEventArgs>(onOpenEvent);
            services.EventBus.AddHandler<TestStateEventArgs>(onTestStateChanged);

            InitializeComponent();

            // Go to initial place
            services.PlaceController.GoTo(new Empty.EmptyPlace());
        }

        #region Application-wide events
        private void onTitleChanged(object sender, PageTitleEventArgs e)
        {
            Text = e.Title;
        }

        private void onStatusChanged(object sender, StatusEventArgs e)
        {
            toolStripStatusLabel.Text = e.Message;

            if (e.Progress < 0.0)
            {
                toolStripProgressBar.Value = 0;
            }
            else if (e.Progress > 1.0)
            {
                toolStripProgressBar.Value = 100;
            }
            else
            {
                toolStripProgressBar.Value = (int)(e.Progress * 100);
            }

            toolStripProgressBar.Visible = e.ShowProgress;
            toolStripStatusLabel.Invalidate();
        }

        private void onCommandEnableChanged(object sender, CommandEnableEventArgs e)
        {
            if (e.RunAllEnabled.HasValue)
            {
                runAllToolStripMenuItem.Enabled = e.RunAllEnabled.Value;
            }

            if (e.RunSelectedEnabled.HasValue)
            {
                runSelectedToolStripMenuItem.Enabled = e.RunSelectedEnabled.Value;
            }
        }

        private void onExitEvent(object sender, ExitEventArgs args)
        {
            // Fire exiting event, allowing presenters to cancel.
            ExitingEventArgs e = new ExitingEventArgs();
            services.EventBus.FireEvent(this, e);

            if (!e.Cancel)
            {
                // Exiting event not canceled.
                // Exit application.
                Application.Exit();
            }
        }

        private void onOpenEvent(object sender, OpenEventArgs e)
        {
            DialogResult dr = openTestDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                services.PlaceController.GoTo(new Test.TestPlace(openTestDialog.FileName));
            }
        }

        private void onTestStateChanged(object sender, TestStateEventArgs e)
        {
            switch (e.State)
            {
                default:
                case TestState.Nothing:
                    testStatePanel.BackColor = Color.Transparent;
                    break;

                case TestState.Unknown:
                    testStatePanel.BackColor = Color.RoyalBlue;
                    break;

                case TestState.Fail:
                    testStatePanel.BackColor = Color.Red;
                    break;

                case TestState.Pass:
                    testStatePanel.BackColor = Color.LightGreen;
                    break;
            }
        }
        #endregion

        #region Main window input events
        private void MainFrame_FormClosing(object sender, FormClosingEventArgs e)
        {
            services.EventBus.FireEvent(this, new ExitEventArgs());
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new ExitEventArgs());
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new OpenEventArgs());
        }

        private void runAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new RunAllEventArgs());
        }

        private void runSelectedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new RunSelectedEventArgs());
        }
        #endregion
    }
}
