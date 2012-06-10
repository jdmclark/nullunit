// Copyright (c) 2011, Jonathan Clark
// All rights reserved.
//
// This software is licensed under the two-clause Simplified BSD License.
// The text of this license is available from:
// http://www.opensource.org/licenses/bsd-license.php

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.ComponentModel;
using System.Diagnostics;

namespace NullUnit.Framework.Utility
{
    public class BackgroundRunner
    {
        Control control;
        BackgroundWorker worker;
        Dictionary<string, Action<string[]>> protocolActions = new Dictionary<string, Action<string[]>>();

        public BackgroundRunner(Control form)
        {
            worker = new BackgroundWorker();
            this.control = form;

            worker.DoWork += new DoWorkEventHandler(worker_DoWork);
            worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(worker_RunWorkerCompleted);

            #region Build action table
            protocolActions.Add("LIST_BEGIN", l =>
                {
                    onListBegin(this, new EventArgs());
                }
            );

            protocolActions.Add("LIST_END", l =>
                {
                    onListEnd(this, new EventArgs());
                }
            );

            protocolActions.Add("LIST_SUITE", l =>
                {
                    onListEntrySuite(this, new ListEntrySuiteEventArgs(
                        l[1], l[2], int.Parse(l[3])));
                }
            );

            protocolActions.Add("LIST_CASE", l =>
                {
                    onListEntryCase(this, new ListEntryCaseEventArgs(
                        l[1], l[2], l[3], int.Parse(l[4])));
                }
            );

            protocolActions.Add("REPORT_BEGIN", l =>
                {
                    onReportBegin(this, new EventArgs());
                }
            );

            protocolActions.Add("REPORT_END", l =>
                {
                    onReportEnd(this, new EventArgs());
                }
            );

            protocolActions.Add("SUITE_BEGIN", l =>
                {
                    onSuiteBegin(this, new SuiteEventArgs(l[1]));
                }
            );

            protocolActions.Add("SUITE_END", l =>
                {
                    onSuiteEnd(this, new SuiteEventArgs(l[1]));
                }
            );

            protocolActions.Add("CASE_BEGIN", l =>
                {
                    onCaseBegin(this, new CaseEventArgs(l[1], l[2]));
                }
            );

            protocolActions.Add("CASE_END", l =>
                {
                    onCaseEnd(this, new CaseEventArgs(l[1], l[2]));
                }
            );

            protocolActions.Add("CASE_PASS", l =>
                {
                    onCasePass(this, new CaseEventArgs(l[1], l[2]));
                }
            );

            protocolActions.Add("CASE_FAIL", l =>
                {
                    onCaseFail(this, new CaseFailEventArgs(
                        l[1], l[2], l[3], l[4], int.Parse(l[5])));
                }
            );
            #endregion
        }

        public void Run(string exePath, bool listOnly, IEnumerable<String> cases)
        {
            BackgroundRunnerParameters p =
                new BackgroundRunnerParameters(exePath, listOnly, cases);
            worker.RunWorkerAsync(p);
        }

        #region Runner
        void doProtocol(Process p)
        {
            string magic = p.StandardOutput.ReadLine();
            if (magic != "NULLUNIT")
            {
                control.Invoke(new EventHandler(onInvalidTestCase));
                return;
            }

            while (!p.StandardOutput.EndOfStream)
            {
                string line = p.StandardOutput.ReadLine();
                string[] l = line.Split(new char[] { '\x1E' });
                Action<string[]> action = protocolActions[l[0]];
                control.Invoke(action, new object[] { l });
            }

            p.WaitForExit();

            control.Invoke(new EventHandler(onFinished));
        }

        void doListWork(string path, IEnumerable<string> cases)
        {
            Process p = new Process();
            p.StartInfo.CreateNoWindow = true;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.FileName = path;

            StringBuilder argumentBuilder = new StringBuilder();
            argumentBuilder.Append("--gui --list");

            if (cases != null)
            {
                argumentBuilder.Append(" --run");

                foreach (string s in cases)
                {
                    argumentBuilder.Append(" ");
                    argumentBuilder.Append(s);
                }
            }

            p.StartInfo.Arguments = argumentBuilder.ToString();

            p.Start();

            doProtocol(p);
        }

        void doReportWork(string path, IEnumerable<string> cases)
        {
            Process p = new Process();
            p.StartInfo.CreateNoWindow = true;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.FileName = path;

            StringBuilder argumentBuilder = new StringBuilder();
            argumentBuilder.Append("--gui");

            if (cases != null)
            {
                argumentBuilder.Append(" --run");

                foreach (string s in cases)
                {
                    argumentBuilder.Append(" ");
                    argumentBuilder.Append(s);
                }
            }

            p.StartInfo.Arguments = argumentBuilder.ToString();

            p.Start();

            doProtocol(p);
        }

        void worker_DoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                BackgroundRunnerParameters p = e.Argument as BackgroundRunnerParameters;
                if (p.ListOnly)
                {
                    doListWork(p.ExePath, p.Cases);
                }
                else
                {
                    doReportWork(p.ExePath, p.Cases);
                }
            }
            catch (Exception)
            {
                control.Invoke(new EventHandler(onInvalidTestCase));
            }
        }

        void worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            control.Invoke(new EventHandler(onFinished));
        }
        #endregion

        #region Asynchronous reporting
        void onInvalidTestCase(object sender, EventArgs e)
        {
            if (InvalidTestCase != null)
            {
                InvalidTestCase.Invoke(sender, e);
            }
        }

        void onFinished(object sender, EventArgs e)
        {
            if (Finished != null)
            {
                Finished.Invoke(sender, e);
            }
        }

        void onReportBegin(object sender, EventArgs e)
        {
            if (ReportBegin != null)
            {
                ReportBegin.Invoke(sender, e);
            }
        }

        void onReportEnd(object sender, EventArgs e)
        {
            if (ReportEnd != null)
            {
                ReportEnd.Invoke(sender, e);
            }
        }

        void onSuiteBegin(object sender, SuiteEventArgs e)
        {
            if (SuiteBegin != null)
            {
                SuiteBegin.Invoke(sender, e);
            }
        }

        void onSuiteEnd(object sender, SuiteEventArgs e)
        {
            if (SuiteEnd != null)
            {
                SuiteEnd.Invoke(sender, e);
            }
        }

        void onCaseBegin(object sender, CaseEventArgs e)
        {
            if (CaseBegin != null)
            {
                CaseBegin.Invoke(sender, e);
            }
        }

        void onCaseEnd(object sender, CaseEventArgs e)
        {
            if(CaseEnd != null)
            {
                CaseEnd.Invoke(sender, e);
            }
        }

        void onCasePass(object sender, CaseEventArgs e)
        {
            if(CasePass != null)
            {
                CasePass.Invoke(sender, e);
            }
        }

        void onCaseFail(object sender, CaseFailEventArgs e)
        {
            if (CaseFail != null)
            {
                CaseFail.Invoke(sender, e);
            }
        }

        void onListBegin(object sender, EventArgs e)
        {
            if (ListBegin != null)
            {
                ListBegin.Invoke(sender, e);
            }
        }

        void onListEnd(object sender, EventArgs e)
        {
            if (ListEnd != null)
            {
                ListEnd.Invoke(sender, e);
            }
        }

        void onListEntrySuite(object sender, ListEntrySuiteEventArgs e)
        {
            if (ListEntrySuite != null)
            {
                ListEntrySuite.Invoke(sender, e);
            }
        }

        void onListEntryCase(object sender, ListEntryCaseEventArgs e)
        {
            if (ListEntryCase != null)
            {
                ListEntryCase.Invoke(sender, e);
            }
        }
        #endregion

        #region Public events
        public event EventHandler InvalidTestCase;
        public event EventHandler Finished;

        public event EventHandler ReportBegin;
        public event EventHandler ReportEnd;

        public event EventHandler<SuiteEventArgs> SuiteBegin;
        public event EventHandler<SuiteEventArgs> SuiteEnd;

        public event EventHandler<CaseEventArgs> CaseBegin;
        public event EventHandler<CaseEventArgs> CaseEnd;

        public event EventHandler<CaseEventArgs> CasePass;
        public event EventHandler<CaseFailEventArgs> CaseFail;

        public event EventHandler ListBegin;
        public event EventHandler ListEnd;
        public event EventHandler<ListEntrySuiteEventArgs> ListEntrySuite;
        public event EventHandler<ListEntryCaseEventArgs> ListEntryCase;
        #endregion
    }
}
