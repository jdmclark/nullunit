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
using NullUnit.Framework.Place;
using System.ComponentModel;
using NullUnit.Runner.Properties;
using System.Diagnostics;
using NullUnit.Runner.Events.State;
using System.IO;
using NullUnit.Runner.Events;
using NullUnit.Framework;
using NullUnit.Framework.Event;
using NullUnit.Framework.Utility;

namespace NullUnit.Runner.Test
{
    class TestPresenter : Presenter, ITestPresenter
    {
        TestPlace place;
        Services services;

        BackgroundRunner backgroundRunner;

        public TestPresenter(TestPlace place, Services services)
        {
            this.place = place;
            this.services = services;

            backgroundRunner = new BackgroundRunner(services.TestView.ProvidedControl);

            backgroundRunner.ListBegin += new EventHandler(backgroundRunner_ListBegin);
            backgroundRunner.ListEntrySuite += new EventHandler<ListEntrySuiteEventArgs>(backgroundRunner_ListEntrySuite);
            backgroundRunner.ListEntryCase += new EventHandler<ListEntryCaseEventArgs>(backgroundRunner_ListEntryCase);
            backgroundRunner.ListEnd += new EventHandler(backgroundRunner_ListEnd);

            backgroundRunner.ReportBegin += new EventHandler(backgroundRunner_ReportBegin);
            backgroundRunner.CasePass += new EventHandler<CaseEventArgs>(backgroundRunner_CasePass);
            backgroundRunner.CaseFail += new EventHandler<CaseFailEventArgs>(backgroundRunner_CaseFail);
            backgroundRunner.ReportEnd += new EventHandler(backgroundRunner_ReportEnd);

            backgroundRunner.Finished += new EventHandler(backgroundRunner_Finished);
            backgroundRunner.InvalidTestCase += new EventHandler(backgroundRunner_InvalidTestCase);
        }

        void backgroundRunner_InvalidTestCase(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusInvalidTestCase, false, 1.0));
        }

        void backgroundRunner_Finished(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new CommandEnableEventArgs(true, services.TestView.SelectedTests.Count() > 0));
        }

        int caseCount = 0;
        int passCount = 0;
        bool failed = false;
        double progress = 0.0;
        double delta = 0.0;

        #region List update

        void backgroundRunner_ListBegin(object sender, EventArgs e)
        {
            caseCount = 0;
            services.TestView.Clear();

            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusLoading, true, 1.0));
            services.EventBus.FireEvent(this, new TestStateEventArgs(TestState.Unknown));
        }

        void backgroundRunner_ListEnd(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusIdle, false, 1.0));
        }

        void backgroundRunner_ListEntrySuite(object sender, ListEntrySuiteEventArgs e)
        {
            services.TestView.AddSuite(e.Suite);
        }

        void backgroundRunner_ListEntryCase(object sender, ListEntryCaseEventArgs e)
        {
            ++caseCount;
            services.TestView.SetCaseState(e.Suite, e.Case, TestState.Unknown);
        }
        
        #endregion

        #region Report update

        void backgroundRunner_ReportBegin(object sender, EventArgs e)
        {
            if (caseCount > 0)
            {
                progress = 0.0;
                delta = 1.0 / (double)caseCount;
            }
            else
            {
                progress = 1.0;
                delta = 0.0;
            }

            caseCount = 0;
            passCount = 0;
            failed = false;

            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusRunning, true, progress));
            services.EventBus.FireEvent(this, new TestStateEventArgs(TestState.Unknown));
        }

        void backgroundRunner_ReportEnd(object sender, EventArgs e)
        {
            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusIdle, false, 1.0));

            if (!failed && caseCount == passCount)
            {
                services.EventBus.FireEvent(this, new TestStateEventArgs(TestState.Pass));
            }
        }

        void backgroundRunner_CasePass(object sender, CaseEventArgs e)
        {
            ++caseCount;
            ++passCount;
            progress += delta;
            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusRunning, true, progress));
            services.TestView.SetCaseState(e.Suite, e.Case, TestState.Pass);
        }

        void backgroundRunner_CaseFail(object sender, CaseFailEventArgs e)
        {
            ++caseCount;
            progress += delta;
            failed = true;
            services.EventBus.FireEvent(this, new StatusEventArgs(Resources.StatusRunning, true, progress));
            services.EventBus.FireEvent(this, new TestStateEventArgs(TestState.Fail));

            services.TestView.SetCaseState(e.Suite, e.Case, TestState.Fail);
            services.TestView.AddCaseResult(e.Suite, e.Case, e.Reason, e.Filename, e.LineNumber, TestState.Fail);
        }

        #endregion

        public override void Start(IAcceptsOneControl viewFrame, IEventBus eventBus)
        {
            services.TestView.Presenter = this;
            viewFrame.Control = services.TestView.ProvidedControl;

            eventBus.FireEvent(this, new PageTitleEventArgs(String.Format(Resources.MainWindowFileTitle,
                Path.GetFileNameWithoutExtension(place.Filename))));

            eventBus.AddHandler<RunAllEventArgs>(onRunAll);
            eventBus.AddHandler<RunSelectedEventArgs>(onRunSelected);

            eventBus.FireEvent(this, new CommandEnableEventArgs(false, false));
            backgroundRunner.Run(place.Filename, true, null);
        }

        public void SelectionChanged()
        {
            services.EventBus.FireEvent(this, new CommandEnableEventArgs(null, services.TestView.SelectedTests.Count() > 0));
        }

        private void onRunAll(object sender, RunAllEventArgs e)
        {
            services.EventBus.FireEvent(this, new CommandEnableEventArgs(false, false));
            backgroundRunner.Run(place.Filename, false, null);
        }

        private void onRunSelected(object sender, RunSelectedEventArgs e)
        {
            services.EventBus.FireEvent(this, new CommandEnableEventArgs(false, false));
            backgroundRunner.Run(place.Filename, false, services.TestView.SelectedTests);
        }
    }
}
