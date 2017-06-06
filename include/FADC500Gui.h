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
#include "FADC500Analysis.h"
#include <stdio.h>
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>

class FADC500Gui
{
	private :
		FADC500Decoder decoder;
		FADC500Analysis ana;

		TString openFile;
		TString directory;

		TGComboBox *fDFMODE[6][4];
		TGComboBox *fADCMODE[6][4];
		TGComboBox *fTDCMODE[6][4];
		TGNumberEntryField *fPRETHR[6][4];
		TGNumberEntryField *fDFTHR[6][4];
		TGNumberEntryField *fDELAY[6][4];
		TGNumberEntryField *fRATIO[6][4];
		TGNumberEntryField *fLENGTH[6][4];
		TGNumberEntryField *fGAP[6][4];
		TGNumberEntryField *fFLENGTH[6][4];


	public :
		FADC500Gui();
		void OpenDatFile();
		void OpenROOTFile();
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
		void SetADCMode(int value);
		void SetDFMode(int value);
		void SetTDCMode(int value);
		void SetDelay(char *value);
		void SetRatio(char *value);
		void SetLength(char *value);
		void SetfLength(char *value);
		void SetGap(char *value);
		void SetDFTHR(char *value);
		void SetPRETHR(char *value);
		void SetSame();
		void StartAnalyzer();
		void StopAnalyzer();
		void FilterOn();
		void FilterOff();
};
#endif

