/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500gui.h header file
GUI builder for NKFADC500 DAQ.
May. 1. 2017.
***********************************************************/

#ifndef FADC500GUI_H
#define FADC500GUI_H

#include "TGDockableFrame.h"
#include "TGMenu.h"
#include "TGMdiDecorFrame.h"
#include "TG3DLine.h"
#include "TGMdiFrame.h"
#include "TGMdiMainFrame.h"
#include "TGMdiMenu.h"
#include "TGListBox.h"
#include "TGNumberEntry.h"
#include "TGHtml.h"
#include "TGScrollBar.h"
#include "TGComboBox.h"
#include "TGuiBldHintsEditor.h"
#include "TGuiBldNameFrame.h"
#include "TGFrame.h"
#include "TGFileDialog.h"
#include "TGShutter.h"
#include "TGButtonGroup.h"
#include "TGCanvas.h"
#include "TGFSContainer.h"
#include "TGuiBldEditor.h"
#include "TGColorSelect.h"
#include "TGButton.h"
#include "TGFSComboBox.h"
#include "TGLabel.h"
#include "TGView.h"
#include "TRootGuiBuilder.h"
#include "TGTab.h"
#include "TGListView.h"
#include "TGSplitter.h"
#include "TGTextView.h"
#include "TGStatusBar.h"
#include "TGListTree.h"
#include "TGuiBldGeometryFrame.h"
#include "TGToolTip.h"
#include "TGToolBar.h"
#include "TGuiBldDragManager.h"
#include "TRootEmbeddedCanvas.h"
#include "TGLabel.h"
#include "TGFileDialog.h"
#include "TRootHelpDialog.h"

#include "Riostream.h"
#include "FADC500Decoder.h"
#include <stdio.h>
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>

class FADC500Gui
{
	private :
		FADC500Decoder decoder;
//		FADC500Analysis ana;

		TString openFile;
		TString directory;


	public :
		FADC500Gui();
		void OpenFile();
		void HandleMenu(Int_t menu_id);
		void TerminatePro();
		void StartDecoder();
		void StopDecoder();
		void StartOnline();
		void ResumeOnline();
		void PauseOnline();
		void StopOnline();
		void MonitorOn();
		void MonitorOff();

};
#endif

