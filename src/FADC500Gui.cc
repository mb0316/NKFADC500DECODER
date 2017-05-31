/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500gui.cc source file
GUI builder for NKFADC500 DAQ.
May. 1. 2017.
***********************************************************/

#include "TROOT.h"
#include "TApplication.h"
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
#include "FADC500Gui.h"
#include "FADC500Decoder.h"
#include <stdio.h>
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"

using namespace std;


const char gAboutNKFADC500[] = "\
				NKFADC500 GUI DECODER Program\n\
Notice Korea Flash ADC 500MHz(NKFADC500).\n\
GUI DECODER Program is built by Byul Moon from Korea Univerity.\n\
";

const char gMANUAL[] ="\
				NKFADC500 GUI DECODER Program MANUAL\n\
";

const char gCONTACT[] ="\
				NKFADC500 GUI DECODER Program CONTACT INFORMATION\n\
Please contact via the following e-mail address.\n\
mb0316@nuclear.korea.ac.kr\n\
";

enum EMyMessageTypes
{
	M_FILE_OPEN_FILE,
	M_FILE_EXIT,
	M_HELP_ABOUT,
	M_HELP_MANUAL,
	M_HELP_CONTACT
};

FADC500Gui::FADC500Gui()
{

	// main frame
	TGMainFrame *fMainFrame1073 = new TGMainFrame(gClient->GetRoot(),1200,650,kMainFrame | kVerticalFrame);
	fMainFrame1073->SetName("NKFADC500");
	fMainFrame1073->SetLayoutBroken(kTRUE);

	TGMenuBar* fMenuBar = new TGMenuBar(fMainFrame1073, 1200, 25, kHorizontalFrame);
	TGPopupMenu* fMenuFile = new TGPopupMenu(gClient->GetRoot());
	fMenuFile->AddEntry(" &Open File", M_FILE_OPEN_FILE, 0, gClient->GetPicture("bld_open.png")); 
	fMenuFile->AddSeparator();
	fMenuFile->AddEntry(" E&xit", M_FILE_EXIT, 0, gClient->GetPicture("bld_exit.png"));
	fMenuFile->Connect("Activated(Int_t)", "FADC500Gui", this, "HandleMenu(Int_t)");
	fMenuBar->AddPopup("&File", fMenuFile, new TGLayoutHints(kLHintsTop|kLHintsLeft, 0, 4, 0, 0));

	TGPopupMenu* fMenuHelp = new TGPopupMenu(gClient->GetRoot());
	fMenuHelp->AddEntry(" &About NKFADC500 DECODER", M_HELP_ABOUT, 0, gClient->GetPicture("about.xpm"));
	fMenuHelp->AddEntry(" NKFADC500 DECODER &Manual", M_HELP_MANUAL);
	fMenuHelp->AddEntry(" NKFADC500 DECODER &Contact Info.", M_HELP_CONTACT);
	fMenuHelp->Connect("Activated(Int_t)", "FADC500Gui", this, "HandleMenu(Int_t)");
	fMenuBar->AddPopup("&Help", fMenuHelp, new TGLayoutHints(kLHintsTop|kLHintsLeft));

	fMainFrame1073 -> AddFrame(fMenuBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 5));
	fMenuBar->MoveResize(0,0,1200,25);

	// tab widget
	TGTab *fTab1 = new TGTab(fMainFrame1073, 1180, 550);

	// container of "Tab1"
	TGCompositeFrame *fCompositeFrame1;
	fCompositeFrame1 = fTab1 -> AddTab("Setting");
	fCompositeFrame1 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame1));
	fCompositeFrame1 ->SetLayoutBroken(kTRUE);

	// global parameters
	TGLabel *lTitle1 = new TGLabel(fCompositeFrame1, "Decoder");
	lTitle1 -> SetTextJustify(kTextLeft);
	lTitle1 -> SetMargins(0, 0, 0, 0);
	lTitle1 -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTitle1, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTitle1 -> MoveResize(20,10,170,20);

	TGTextButton *DECODER = new TGTextButton(fCompositeFrame1,"DECODER",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    DECODER-> Connect("Clicked()", "FADC500Gui", this, "StartDecoder()");
    DECODER->SetTextJustify(36);
    DECODER->SetMargins(0,0,0,0);
    DECODER->SetWrapLength(-1);
    DECODER->Resize(100,35);
    fCompositeFrame1->AddFrame(DECODER, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    DECODER->MoveResize(20,50,100,35);

	TGTextButton *STOPDECODER = new TGTextButton(fCompositeFrame1,"STOP",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    STOPDECODER-> Connect("Clicked()", "FADC500Gui", this, "StopDecoder()");
    STOPDECODER->SetTextJustify(36);
    STOPDECODER->SetMargins(0,0,0,0);
    STOPDECODER->SetWrapLength(-1);
    STOPDECODER->Resize(100,35);
    fCompositeFrame1->AddFrame(STOPDECODER, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    STOPDECODER->MoveResize(130,50,100,35);



	// function buttons
	TGLabel *lTitle2 = new TGLabel(fCompositeFrame1, "Online Monitor");
	lTitle2 -> SetTextJustify(kTextLeft);
	lTitle2 -> SetMargins(0, 0, 0, 0);
	lTitle2 -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTitle2, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTitle2 -> MoveResize(20,110,170,20);

	TGTextButton *ONLINE = new TGTextButton(fCompositeFrame1,"ONLINE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    ONLINE->Connect("Clicked()", "FADC500Gui", this, "StartOnline()");
    ONLINE->SetTextJustify(36);
    ONLINE->SetMargins(0,0,0,0);
    ONLINE->SetWrapLength(-1);
    ONLINE->Resize(100,35);
    fCompositeFrame1->AddFrame(ONLINE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    ONLINE->MoveResize(20,150,100,35);

	TGTextButton *PAUSEONLINE = new TGTextButton(fCompositeFrame1,"PAUSE",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    PAUSEONLINE-> Connect("Clicked()", "FADC500Gui", this, "PauseOnline()");
    PAUSEONLINE->SetTextJustify(36);
    PAUSEONLINE->SetMargins(0,0,0,0);
    PAUSEONLINE->SetWrapLength(-1);
    PAUSEONLINE->Resize(100,35);
    fCompositeFrame1->AddFrame(PAUSEONLINE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    PAUSEONLINE->MoveResize(130,150,100,35);

	TGTextButton *RESUMEONLINE = new TGTextButton(fCompositeFrame1,"RESUME",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    RESUMEONLINE-> Connect("Clicked()", "FADC500Gui", this, "ResumeOnline()");
    RESUMEONLINE->SetTextJustify(36);
    RESUMEONLINE->SetMargins(0,0,0,0);
    RESUMEONLINE->SetWrapLength(-1);
    RESUMEONLINE->Resize(100,35);
    fCompositeFrame1->AddFrame(RESUMEONLINE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    RESUMEONLINE->MoveResize(240,150,100,35);

	TGTextButton *STOPONLINE = new TGTextButton(fCompositeFrame1,"STOP",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    STOPONLINE-> Connect("Clicked()", "FADC500Gui", this, "StopOnline()");
    STOPONLINE->SetTextJustify(36);
    STOPONLINE->SetMargins(0,0,0,0);
    STOPONLINE->SetWrapLength(-1);
    STOPONLINE->Resize(100,35);
    fCompositeFrame1->AddFrame(STOPONLINE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    STOPONLINE->MoveResize(350,150,100,35);



	// container for tab2
	TGCompositeFrame *fCompositeFrame2;
	fCompositeFrame2 = fTab1 -> AddTab("Online Monitoring");
	fCompositeFrame2 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame2));
	fCompositeFrame2 ->SetLayoutBroken(kTRUE);

	TGTab *fSubTab = new TGTab(fCompositeFrame2, 1050, 530);
	TGTab *fSSubTab[6];

	// container of "SubTab"
	TGCompositeFrame *fModuleFrame[6];
	TGCompositeFrame *fChannelFrame[6][4];

	TRootEmbeddedCanvas *monitorFADC[6][4];
	TRootEmbeddedCanvas *monitorADC[6][4];
	TRootEmbeddedCanvas *monitorTDC[6][4];

	Int_t wmonitorFADC[6][4];
	Int_t wmonitorADC[6][4];
	Int_t wmonitorTDC[6][4];

	for (int i = 0; i < 6; i++)
	{
		fModuleFrame[i] = fSubTab -> AddTab(Form("Module#%d",i+1));
		fModuleFrame[i] -> SetLayoutManager(new TGVerticalLayout(fModuleFrame[i]));
		fModuleFrame[i] ->SetLayoutBroken(kTRUE);

		fSSubTab[i] = new TGTab(fModuleFrame[i], 1040, 490);


		// local parameters : channels
		for (int j = 0; j < 4; j++)
		{
//          int widgetID = i*100 + j*10;
			fChannelFrame[i][j] = fSSubTab[i] -> AddTab(Form("Channel#%d",j+1));
			fChannelFrame[i][j] -> SetLayoutManager(new TGVerticalLayout(fChannelFrame[i][j]));
			fChannelFrame[i][j] ->SetLayoutBroken(kTRUE);

			monitorFADC[i][j] = new TRootEmbeddedCanvas(0,fChannelFrame[i][j],500,230,kSunkenFrame);
			monitorFADC[i][j]->SetName(Form("monitorFADC_%d_%d", i, j));
			wmonitorFADC[i][j] = monitorFADC[i][j]->GetCanvasWindowId();
			decoder.c1[i][j] = new TCanvas(Form("cvs1_%d_%d", i, j), 10, 10, wmonitorFADC[i][j]);
			monitorFADC[i][j]->AdoptCanvas(decoder.c1[i][j]);
			fChannelFrame[i][j]->AddFrame(monitorFADC[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			monitorFADC[i][j]->MoveResize(10,10,500,220);

			monitorADC[i][j] = new TRootEmbeddedCanvas(0,fChannelFrame[i][j],500,230,kSunkenFrame);
			monitorADC[i][j]->SetName(Form("monitorADC_%d_%d", i, j));
			wmonitorADC[i][j] = monitorADC[i][j]->GetCanvasWindowId();
			decoder.c2[i][j] = new TCanvas(Form("cvs2_%d_%d", i, j), 10, 10, wmonitorADC[i][j]);
			monitorADC[i][j]->AdoptCanvas(decoder.c2[i][j]);
			fChannelFrame[i][j]->AddFrame(monitorADC[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			monitorADC[i][j]->MoveResize(520,10,500,220);

			monitorTDC[i][j] = new TRootEmbeddedCanvas(0,fChannelFrame[i][j],500,230,kSunkenFrame);
			monitorTDC[i][j]->SetName(Form("monitorTDC_%d_%d", i, j));
			wmonitorTDC[i][j] = monitorTDC[i][j]->GetCanvasWindowId();
			decoder.c3[i][j] = new TCanvas(Form("cvs3_%d_%d", i, j), 10, 10, wmonitorTDC[i][j]);
			monitorTDC[i][j]->AdoptCanvas(decoder.c3[i][j]);
			fChannelFrame[i][j]->AddFrame(monitorTDC[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			monitorTDC[i][j]->MoveResize(10,240,500,220);
		}

	}

	TGTextButton *MONITORON = new TGTextButton(fCompositeFrame2,"MONITOR ON",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    MONITORON -> Connect("Clicked()", "FADC500Gui", this, "MonitorOn()");
    MONITORON->SetTextJustify(36);
    MONITORON->SetMargins(0,0,0,0);
    MONITORON->SetWrapLength(-1);
    MONITORON->Resize(100,35);
    fCompositeFrame2->AddFrame(MONITORON, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    MONITORON->MoveResize(1070,100,100,35);

	TGTextButton *MONITOROFF = new TGTextButton(fCompositeFrame2,"MONITOR OFF",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    MONITOROFF -> Connect("Clicked()", "FADC500Gui", this, "MonitorOff()");
    MONITOROFF->SetTextJustify(36);
    MONITOROFF->SetMargins(0,0,0,0);
    MONITOROFF->SetWrapLength(-1);
    MONITOROFF->Resize(100,35);
    fCompositeFrame2->AddFrame(MONITOROFF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    MONITOROFF->MoveResize(1070,150,100,35);


	TGLabel *lCOPYRIGHT = new TGLabel(fMainFrame1073, "Copyright 2017. B. Moon");
    lCOPYRIGHT -> SetTextJustify(kTextLeft);
    lCOPYRIGHT -> SetMargins(0, 0, 0, 0);
    lCOPYRIGHT -> SetWrapLength(-1);
    fMainFrame1073 -> AddFrame(lCOPYRIGHT, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
    lCOPYRIGHT -> MoveResize(1050, 590, 200, 20);




	fTab1 -> SetTab(0);
	fTab1->Resize(fTab1->GetDefaultSize());
	fMainFrame1073->AddFrame(fTab1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fTab1->MoveResize(10,25,1180,560);

	fSubTab -> SetTab(0);
	fSubTab->Resize(fSubTab->GetDefaultSize());
	fCompositeFrame2->AddFrame(fSubTab, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fSubTab->MoveResize(10,10,1050,530);

	for (int i = 0; i < 6; i++)
	{
		fSSubTab[i] -> SetTab(0);
		fSSubTab[i]->Resize(fSSubTab[i]->GetDefaultSize());
		fModuleFrame[i]->AddFrame(fSSubTab[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fSSubTab[i]->MoveResize(10,10,1040,490);
	}

	fMainFrame1073->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
	fMainFrame1073->MapSubwindows();

	fMainFrame1073->Resize(fMainFrame1073->GetDefaultSize());
	fMainFrame1073->MapWindow();
	fMainFrame1073->Resize(1200,620);

	fMainFrame1073->SetWindowName("NKFADC500 DECODER");
	fMainFrame1073->MapSubwindows();
	fMainFrame1073->Connect("CloseWindow()", "FADC500Gui", this, "TerminatePro()");

}

void FADC500Gui::OpenFile()
{
	TGFileInfo fileInfo;
    const Char_t *fileType[4] = {"Data File", "*.dat", 0, 0};
    fileInfo.fFileTypes = fileType;
    new TGFileDialog(gClient -> GetRoot(), 0, kFDOpen, &fileInfo);

    // If user clicks cancel, do nothing.
    if (fileInfo.fFilename == NULL)
        return;

    // Get the file name with path
    TString filenameWithPath = fileInfo.fFilename;
    TObjArray *decomposedFileNameWithPath = filenameWithPath.Tokenize("/");
    openFile = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    directory = filenameWithPath.ReplaceAll(openFile, "");

    cout << "Directory : " << directory << endl;
    cout << "Filename : " << openFile << endl;
   
    delete decomposedFileNameWithPath;
}

void FADC500Gui::HandleMenu(Int_t menu_id)
{
	// Handle menu events.
	TRootHelpDialog *hd;
	switch (menu_id) {
		case M_FILE_EXIT:
			// close the window and quit application
			gApplication->Terminate(0);
			break;
		case M_FILE_OPEN_FILE:
			OpenFile();
			break;
		case M_HELP_ABOUT:
			hd = new TRootHelpDialog(0, "About NKFADC500", 750, 250);
			hd->SetText(gAboutNKFADC500);
			hd->Popup();
			break;
		case M_HELP_MANUAL:
			hd = new TRootHelpDialog(0, "NKFADC500 Manual", 1000, 500);
			hd->SetText(gMANUAL);
			hd->Popup();
			break;
		case M_HELP_CONTACT:
			hd = new TRootHelpDialog(0, "NKFADC500 Contact Information", 750, 250);
			hd->SetText(gCONTACT);
			hd->Popup();
			break;
	}
}

void FADC500Gui::TerminatePro()
{
	gApplication->Terminate(0);
}

void FADC500Gui::StartDecoder()
{
	TString datafile = directory + openFile;

	if (datafile.Length() >= 1)
	{
		decoder.Decoder(datafile);
	}	
	if (datafile.Length() == 0)
	{
		cout << "Please open data file." << endl;
	}
}

void FADC500Gui::StopDecoder()
{
	decoder.flag = 0;
	gSystem -> ProcessEvents();
}

void FADC500Gui::StartOnline()
{
	TString datafile = directory + openFile;

	if (datafile.Length() >= 1)
	{
		decoder.Online(datafile);
	}	
	if (datafile.Length() == 0)
	{
		cout << "Please open data file." << endl;
	}
}

void FADC500Gui::PauseOnline()
{
	decoder.on_flag = 2;
	gSystem -> ProcessEvents();
}

void FADC500Gui::ResumeOnline()
{
	decoder.on_flag = 1;
	gSystem -> ProcessEvents();
}

void FADC500Gui::StopOnline()
{
	decoder.on_flag = 0;
	gSystem -> ProcessEvents();
}

void FADC500Gui::MonitorOn()
{
	decoder.monitorflag = 1;
	gSystem -> ProcessEvents();
}

void FADC500Gui::MonitorOff()
{
	decoder.monitorflag = 0;
	gSystem -> ProcessEvents();
}

