﻿
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Abstractspoon.Tdl.PluginHelpers;

namespace HTMLReportExporter
{
	[System.ComponentModel.DesignerCategory("")]
    public class HTMLReportExporterCore
    {
        public HTMLReportExporterCore(Translator trans)
        {
            m_trans = trans;
        }

        public bool Export(TaskList srcTasks, string sDestFilePath, bool bSilent, Preferences prefs, string sKey)
        {
			if (!bSilent)
			{
				// Display a dialog to get the report parameters
				// TODO

			}

            // Process the tasks
            Task task = srcTasks.GetFirstTask();

            while (task.IsValid())
            {
                if (!ExportTask(task /*, probably with some additional parameters*/ ))
                {
                    // Decide whether to stop or not
                    // TODO
                }

                task = task.GetNextTask();
            }

            return true;
        }

        protected bool ExportTask(Task task /*, probably with some additional parameters*/)
        {
            // Process task's own attributes
            // TODO

            // Export task's children
            Task subtask = task.GetFirstSubtask();

            while (subtask.IsValid())
            {
                if (!ExportTask(subtask /*, probably with some additional parameters*/ ))
                {
                    // Decide whether to stop or not
                    // TODO
                }

                subtask = subtask.GetNextTask();
            }

            return true;
        }
	
        // --------------------------------------------------------------------------------------
	    private Translator m_trans;
    }
}
