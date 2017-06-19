/************************************************************
NKFADC500 GUI system
Made by Byul Moon.
FADC500Gui.cc source file
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
	M_FILE_OPEN_DAT_FILE,
	M_FILE_OPEN_ROOT_FILE,
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
	fMenuFile->AddEntry(" &Open DAT File", M_FILE_OPEN_DAT_FILE, 0, gClient->GetPicture("bld_open.png")); 
	fMenuFile->AddEntry(" &Open ROOT File", M_FILE_OPEN_ROOT_FILE, 0, gClient->GetPicture("bld_open.png")); 
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

	// Decoder
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



	// Online Monitor
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

	// Analyzer
	TGLabel *lTitle3 = new TGLabel(fCompositeFrame1, "Analyzer");
	lTitle3 -> SetTextJustify(kTextLeft);
	lTitle3 -> SetMargins(0, 0, 0, 0);
	lTitle3 -> SetWrapLength(-1);
	fCompositeFrame1 -> AddFrame(lTitle3, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
	lTitle3 -> MoveResize(500,10,170,20);

	TGCompositeFrame *fModuleFrame1[6];
    TGCompositeFrame *fChannelFrame1[6][4];

	TGTab *fSubTab1 = new TGTab(fCompositeFrame1, 600, 350);
    TGTab *fSSubTab1[6];

	for (int i = 0; i < 6; i++)
    {
        fModuleFrame1[i] = fSubTab1 -> AddTab(Form("Module#%d",i+1));
        fModuleFrame1[i] -> SetLayoutManager(new TGVerticalLayout(fModuleFrame1[i]));
        fModuleFrame1[i] ->SetLayoutBroken(kTRUE);

		fSSubTab1[i] = new TGTab(fModuleFrame1[i], 580, 320);
		for (int j = 0; j < 4; j++)
        {
            int widgetID = i*100 + j*10;
            fChannelFrame1[i][j] = fSSubTab1[i] -> AddTab(Form("Channel#%d",j+1));
            fChannelFrame1[i][j] -> SetLayoutManager(new TGVerticalLayout(fChannelFrame1[i][j]));
            fChannelFrame1[i][j] ->SetLayoutBroken(kTRUE);

            TGLabel *lDFMODE = new TGLabel(fChannelFrame1[i][j], "Digital Filter");
            lDFMODE -> SetTextJustify(kTextLeft);
            lDFMODE -> SetMargins(0, 0, 0, 0);
            lDFMODE -> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lDFMODE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lDFMODE -> MoveResize(20,10,170,20);

			fDFMODE[i][j] = new TGComboBox(fChannelFrame1[i][j],widgetID);
	        fDFMODE[i][j]->SetName("Digital Filter");
	        fDFMODE[i][j]->AddEntry("Enable",0);
	        fDFMODE[i][j]->AddEntry("Unable",1);
	        fDFMODE[i][j]->Resize(100,20);
			fDFMODE[i][j]->Select(-1);
			fChannelFrame1[i][j]->AddFrame(fDFMODE[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	        fDFMODE[i][j]->MoveResize(200,10,100,20);
	        fDFMODE[i][j]->Connect("Selected(Int_t)", "FADC500Gui", this, "SetDFMode(Int_t)");

            TGLabel *lADCMODE = new TGLabel(fChannelFrame1[i][j], "ADC Mode");
            lADCMODE -> SetTextJustify(kTextLeft);
            lADCMODE -> SetMargins(0, 0, 0, 0);
            lADCMODE -> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lADCMODE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lADCMODE -> MoveResize(20,40,170,20);

			fADCMODE[i][j] = new TGComboBox(fChannelFrame1[i][j],widgetID);
	        fADCMODE[i][j]->SetName("ADC MODE");
	        fADCMODE[i][j]->AddEntry("ADC",0);
	        fADCMODE[i][j]->AddEntry("QDC",1);
	        fADCMODE[i][j]->Resize(100,20);
			fADCMODE[i][j]->Select(-1);
			fChannelFrame1[i][j]->AddFrame(fADCMODE[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	        fADCMODE[i][j]->MoveResize(200,40,100,20);
	        fADCMODE[i][j]->Connect("Selected(Int_t)", "FADC500Gui", this, "SetADCMode(Int_t)");

            TGLabel *lTDCMODE = new TGLabel(fChannelFrame1[i][j], "TDC Mode");
            lTDCMODE -> SetTextJustify(kTextLeft);
            lTDCMODE -> SetMargins(0, 0, 0, 0);
            lTDCMODE -> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lTDCMODE, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lTDCMODE -> MoveResize(20,70,170,20);

			fTDCMODE[i][j] = new TGComboBox(fChannelFrame1[i][j],widgetID);
	        fTDCMODE[i][j]->SetName("TDC MODE");
	        fTDCMODE[i][j]->AddEntry("Leading Edge",0);
	        fTDCMODE[i][j]->AddEntry("CFD",1);
	        fTDCMODE[i][j]->Resize(100,20);
			fTDCMODE[i][j]->Select(-1);
			fChannelFrame1[i][j]->AddFrame(fTDCMODE[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	        fTDCMODE[i][j]->MoveResize(200,70,100,20);
	        fTDCMODE[i][j]->Connect("Selected(Int_t)", "FADC500Gui", this, "SetTDCMode(Int_t)");

            TGLabel *lPRETHR = new TGLabel(fChannelFrame1[i][j], "Thereshold for Pulse");
            lPRETHR -> SetTextJustify(kTextLeft);
            lPRETHR -> SetMargins(0, 0, 0, 0);
            lPRETHR -> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lPRETHR, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lPRETHR -> MoveResize(20,100,170,20);

			fPRETHR[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
            fPRETHR[i][j]->MoveResize(200,100,100,20);
            fChannelFrame1[i][j]->AddFrame(fPRETHR[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fPRETHR[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetPRETHR(const Char_t *)");
			fPRETHR[i][j] -> SetText("0", kFALSE);
			ana.pre_thr[i][j] = 0;

            TGLabel *lDFTHR = new TGLabel(fChannelFrame1[i][j], "Thereshold for Digital Filter");
            lDFTHR -> SetTextJustify(kTextLeft);
            lDFTHR -> SetMargins(0, 0, 0, 0);
            lDFTHR -> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lDFTHR, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lDFTHR -> MoveResize(20,130,170,20);

			fDFTHR[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 4096);
            fDFTHR[i][j]->MoveResize(200,130,100,20);
            fChannelFrame1[i][j]->AddFrame(fDFTHR[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fDFTHR[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetDFTHR(const Char_t *)");
			fDFTHR[i][j] -> SetText("0", kFALSE);
			ana.thr[i][j] = 0;

            TGLabel *lDELAY= new TGLabel(fChannelFrame1[i][j], "Delay for CFD");
            lDELAY-> SetTextJustify(kTextLeft);
            lDELAY-> SetMargins(0, 0, 0, 0);
            lDELAY-> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lDELAY, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lDELAY-> MoveResize(20,160,170,20);

			fDELAY[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 32000);
            fDELAY[i][j]->MoveResize(200,160,100,20);
            fChannelFrame1[i][j]->AddFrame(fDELAY[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fDELAY[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetDelay(const Char_t *)");
			fDELAY[i][j] -> SetText("0", kFALSE);
			ana.delay[i][j] = 0;

            TGLabel *lRATIO= new TGLabel(fChannelFrame1[i][j], "Ratio for CFD");
            lRATIO-> SetTextJustify(kTextLeft);
            lRATIO-> SetMargins(0, 0, 0, 0);
            lRATIO-> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lRATIO, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lRATIO-> MoveResize(20,190,170,20);

			fRATIO[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 1);
            fRATIO[i][j]->MoveResize(200,190,100,20);
            fChannelFrame1[i][j]->AddFrame(fRATIO[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fRATIO[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetRatio(const Char_t *)");
			fRATIO[i][j] -> SetText("0", kFALSE);
			ana.ratio[i][j] = 0;

            TGLabel *lLENGTH= new TGLabel(fChannelFrame1[i][j], "Length for Digital Filter");
            lLENGTH-> SetTextJustify(kTextLeft);
            lLENGTH-> SetMargins(0, 0, 0, 0);
            lLENGTH-> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lLENGTH, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lLENGTH-> MoveResize(20,220,170,20);

			fLENGTH[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 32000);
            fLENGTH[i][j]->MoveResize(200,220,100,20);
            fChannelFrame1[i][j]->AddFrame(fLENGTH[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fLENGTH[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetLength(const Char_t *)");
			fLENGTH[i][j] -> SetText("0", kFALSE);
			ana.length[i][j] = 0;

            TGLabel *lGAP= new TGLabel(fChannelFrame1[i][j], "Gap for Digital Filter");
            lGAP-> SetTextJustify(kTextLeft);
            lGAP-> SetMargins(0, 0, 0, 0);
            lGAP-> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lGAP, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lGAP-> MoveResize(20,250,170,20);

			fGAP[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 32000);
            fGAP[i][j]->MoveResize(200,250,100,20);
            fChannelFrame1[i][j]->AddFrame(fGAP[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fGAP[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetGap(const Char_t *)");
			fGAP[i][j] -> SetText("0", kFALSE);
			ana.gap[i][j] = 0;

            TGLabel *lFLENGTH= new TGLabel(fChannelFrame1[i][j], "Length for TFA");
            lFLENGTH-> SetTextJustify(kTextLeft);
            lFLENGTH-> SetMargins(0, 0, 0, 0);
            lFLENGTH-> SetWrapLength(-1);
            fChannelFrame1[i][j] -> AddFrame(lFLENGTH, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
            lFLENGTH-> MoveResize(20,280,170,20);

			fFLENGTH[i][j] = new TGNumberEntryField(fChannelFrame1[i][j], widgetID, 0, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0, 32000);
            fFLENGTH[i][j]->MoveResize(200,280,100,20);
            fChannelFrame1[i][j]->AddFrame(fFLENGTH[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
            fFLENGTH[i][j] -> Connect("TextChanged(const Char_t *)", "FADC500Gui", this, "SetfLength(const Char_t *)");
			fFLENGTH[i][j] -> SetText("0", kFALSE);
			ana.flength[i][j] = 0;
		}
	}

	TGTextButton *SETSAME = new TGTextButton(fCompositeFrame1,"SET SAME",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    SETSAME-> Connect("Clicked()", "FADC500Gui", this, "SetSame()");
    SETSAME->SetTextJustify(36);
    SETSAME->SetMargins(0,0,0,0);
    SETSAME->SetWrapLength(-1);
    SETSAME->Resize(100,35);
    fCompositeFrame1->AddFrame(SETSAME, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    SETSAME->MoveResize(500,420,100,35);

	TGTextButton *STARTANA = new TGTextButton(fCompositeFrame1,"START ANA",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    STARTANA-> Connect("Clicked()", "FADC500Gui", this, "StartAnalyzer()");
    STARTANA->SetTextJustify(36);
    STARTANA->SetMargins(0,0,0,0);
    STARTANA->SetWrapLength(-1);
    STARTANA->Resize(100,35);
    fCompositeFrame1->AddFrame(STARTANA, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    STARTANA->MoveResize(620,420,100,35);

	TGTextButton *STOPANA = new TGTextButton(fCompositeFrame1,"STOP ANA",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    STOPANA-> Connect("Clicked()", "FADC500Gui", this, "StopAnalyzer()");
    STOPANA->SetTextJustify(36);
    STOPANA->SetMargins(0,0,0,0);
    STOPANA->SetWrapLength(-1);
    STOPANA->Resize(100,35);
    fCompositeFrame1->AddFrame(STOPANA, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    STOPANA->MoveResize(740,420,100,35);


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
	TRootEmbeddedCanvas *monitorRATE[6][4];

	Int_t wmonitorFADC[6][4];
	Int_t wmonitorADC[6][4];
	Int_t wmonitorTDC[6][4];
	Int_t wmonitorRATE[6][4];

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

			monitorRATE[i][j] = new TRootEmbeddedCanvas(0,fChannelFrame[i][j],500,230,kSunkenFrame);
			monitorRATE[i][j]->SetName(Form("monitorRATE_%d_%d", i, j));
			wmonitorRATE[i][j] = monitorRATE[i][j]->GetCanvasWindowId();
			decoder.c4[i][j] = new TCanvas(Form("cvs4_%d_%d", i, j), 10, 10, wmonitorRATE[i][j]);
			monitorRATE[i][j]->AdoptCanvas(decoder.c4[i][j]);
			fChannelFrame[i][j]->AddFrame(monitorRATE[i][j], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
			monitorRATE[i][j]->MoveResize(520,240,500,220);


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


	// container for tab3
	TGCompositeFrame *fCompositeFrame3;
	fCompositeFrame3 = fTab1 -> AddTab("Analysis Monitor");
	fCompositeFrame3 -> SetLayoutManager(new TGVerticalLayout(fCompositeFrame3));
	fCompositeFrame3 ->SetLayoutBroken(kTRUE);

	TRootEmbeddedCanvas *monitorPULSE = new TRootEmbeddedCanvas(0,fCompositeFrame3,500,230,kSunkenFrame);
	monitorPULSE->SetName("Monitor Pulse");
	Int_t wmonitorPULSE = monitorPULSE->GetCanvasWindowId();
	ana.cPulse = new TCanvas("cvs1", 10, 10, wmonitorPULSE);
	monitorPULSE->AdoptCanvas(ana.cPulse);
	fCompositeFrame3->AddFrame(monitorPULSE, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorPULSE->MoveResize(10,10,500,250);

	TRootEmbeddedCanvas *monitorDFA = new TRootEmbeddedCanvas(0,fCompositeFrame3,500,230,kSunkenFrame);
	monitorDFA->SetName("Monitor DFA");
	Int_t wmonitorDFA = monitorDFA->GetCanvasWindowId();
	ana.cDFA = new TCanvas("cvs2", 10, 10, wmonitorDFA);
	monitorDFA->AdoptCanvas(ana.cDFA);
	fCompositeFrame3->AddFrame(monitorDFA, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorDFA->MoveResize(520,10,500,250);

	TRootEmbeddedCanvas *monitorTFA = new TRootEmbeddedCanvas(0,fCompositeFrame3,500,230,kSunkenFrame);
	monitorTFA->SetName("Monitor TDC");
	Int_t wmonitorTFA = monitorTFA->GetCanvasWindowId();
	ana.cTFA= new TCanvas("cvs2", 10, 10, wmonitorTFA);
	monitorTFA->AdoptCanvas(ana.cTFA);
	fCompositeFrame3->AddFrame(monitorTFA, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorTFA->MoveResize(10,280,500,250);

	TRootEmbeddedCanvas *monitorCFD = new TRootEmbeddedCanvas(0,fCompositeFrame3,500,230,kSunkenFrame);
	monitorCFD->SetName("Monitor TDC");
	Int_t wmonitorCFD = monitorCFD->GetCanvasWindowId();
	ana.cCFD= new TCanvas("cvs2", 10, 10, wmonitorCFD);
	monitorCFD->AdoptCanvas(ana.cCFD);
	fCompositeFrame3->AddFrame(monitorCFD, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorCFD->MoveResize(520,280,500,250);

	TGTextButton *DRAWON = new TGTextButton(fCompositeFrame3,"MONITOR ON",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    DRAWON -> Connect("Clicked()", "FADC500Gui", this, "FilterOn()");
    DRAWON->SetTextJustify(36);
    DRAWON->SetMargins(0,0,0,0);
    DRAWON->SetWrapLength(-1);
    DRAWON->Resize(100,35);
    fCompositeFrame3->AddFrame(DRAWON, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    DRAWON->MoveResize(1030,100,100,35);

	TGTextButton *DRAWOFF = new TGTextButton(fCompositeFrame3,"MONITOR OFF",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
    DRAWOFF-> Connect("Clicked()", "FADC500Gui", this, "FilterOff()");
    DRAWOFF->SetTextJustify(36);
    DRAWOFF->SetMargins(0,0,0,0);
    DRAWOFF->SetWrapLength(-1);
    DRAWOFF->Resize(100,35);
    fCompositeFrame3->AddFrame(DRAWOFF, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    DRAWOFF->MoveResize(1030,150,100,35);








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

	fSubTab1 -> SetTab(0);
	fSubTab1->Resize(fSubTab1->GetDefaultSize());
	fCompositeFrame1->AddFrame(fSubTab1, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fSubTab1->MoveResize(500,10,650,400);

	for (int i = 0; i < 6; i++)
	{
		fSSubTab1[i] -> SetTab(0);
		fSSubTab1[i]->Resize(fSSubTab1[i]->GetDefaultSize());
		fModuleFrame1[i]->AddFrame(fSSubTab1[i], new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
		fSSubTab1[i]->MoveResize(10,10,600,350);
	}


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

void FADC500Gui::OpenDatFile()
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

void FADC500Gui::OpenROOTFile()
{
	TGFileInfo fileInfo;
    const Char_t *fileType[4] = {"ROOT File", "*.root", 0, 0};
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
		case M_FILE_OPEN_DAT_FILE:
			OpenDatFile();
			break;
		case M_FILE_OPEN_ROOT_FILE:
			OpenROOTFile();
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

void FADC500Gui::SetADCMode(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;

    if (value == 0)
    {
        ana.adcmode[module][channel] = 0;
        cout << "***** ADC Mode : " << "ADC" << " *****" << endl;
    }
    if (value == 1)
    {
        ana.adcmode[module][channel] = 1;
        cout << "***** ADC Mode : " << "QDC" << " *****" << endl;
    }
}

void FADC500Gui::SetTDCMode(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;

    if (value == 0)
    {
        ana.tdcmode[module][channel] = 0;
        cout << "***** TDC Mode : " << "Leading edge" << " *****" << endl;
    }
    if (value == 1)
    {
        ana.tdcmode[module][channel] = 1;
        cout << "***** TDC Mode : " << "CFD" << " *****" << endl;
    }
}

void FADC500Gui::SetDFMode(int value)
{
	TGComboBox *object = (TGComboBox *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;

    if (value == 0)
    {
        ana.dfmode[module][channel] = 1;
        cout << "***** Digital Filter: " << "Able" << " *****" << endl;
    }
    if (value == 1)
    {
        ana.dfmode[module][channel] = 0;
        cout << "***** Digital Filter: " << "Unable" << " *****" << endl;
    }
}

void FADC500Gui::SetDFTHR(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.thr[module][channel] = atoi(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** DF Threshold : " << ana.thr[module][channel] << endl;
}

void FADC500Gui::SetPRETHR(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.pre_thr[module][channel] = atoi(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** Pulse Threshold : " << ana.pre_thr[module][channel] << endl;
}

void FADC500Gui::SetDelay(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.delay[module][channel] = atoi(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** CFD Delay : " << ana.delay[module][channel] << endl;
}

void FADC500Gui::SetRatio(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.ratio[module][channel] = atof(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** CFD Ratio : " << ana.ratio[module][channel] << endl;
}

void FADC500Gui::SetLength(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.length[module][channel] = atoi(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** DF Length : " << ana.length[module][channel] << endl;
}

void FADC500Gui::SetGap(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.gap[module][channel] = atoi(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** DF Gap : " << ana.gap[module][channel] << endl;
}

void FADC500Gui::SetfLength(char *value)
{
	TGNumberEntryField *object = (TGNumberEntryField *) gTQSender;
    Int_t widgetID = object -> WidgetId();
    Int_t module = widgetID/100;
    Int_t channel = (widgetID%100)/10;
    ana.flength[module][channel] = atoi(value);
    cout << "***** Module ID : " << module+1 << " *****" << endl;
    cout << "***** Channel ID : " << channel+1 << " *****" << endl;
    cout << "***** TFA Length : " << ana.flength[module][channel] << endl;
}

void FADC500Gui::SetSame()
{
	for (Int_t i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			for (Int_t j = 1; j < 4; j++)
			{
				ana.dfmode[i][j] = ana.dfmode[0][0];
				ana.adcmode[i][j] = ana.adcmode[0][0];
				ana.tdcmode[i][j] = ana.tdcmode[0][0];
				ana.pre_thr[i][j] = ana.pre_thr[0][0];
				ana.thr[i][j] = ana.thr[0][0];
				ana.delay[i][j] = ana.delay[0][0];
				ana.ratio[i][j] = ana.ratio[0][0];
				ana.length[i][j] = ana.length[0][0];
				ana.flength[i][j] = ana.flength[0][0];
				ana.gap[i][j] = ana.gap[0][0];

				fDFTHR[i][j] -> SetText(Form("%d", ana.thr[i][j]), kFALSE);
				fPRETHR[i][j] -> SetText(Form("%d", ana.pre_thr[i][j]), kFALSE);
				fDELAY[i][j] -> SetText(Form("%d", ana.delay[i][j]), kFALSE);
				fRATIO[i][j] -> SetText(Form("%f", ana.ratio[i][j]), kFALSE);
				fLENGTH[i][j] -> SetText(Form("%d", ana.length[i][j]), kFALSE);
				fFLENGTH[i][j] -> SetText(Form("%d", ana.flength[i][j]), kFALSE);
				fGAP[i][j] -> SetText(Form("%d", ana.gap[i][j]), kFALSE);

				if (ana.dfmode[i][j] == 1)	fDFMODE[i][j] -> Select(0);
				if (ana.dfmode[i][j] == 0)	fDFMODE[i][j] -> Select(1);

				if (ana.adcmode[i][j] == 1)	fADCMODE[i][j] -> Select(1);
				if (ana.adcmode[i][j] == 0)	fADCMODE[i][j] -> Select(0);

				if (ana.tdcmode[i][j] == 1)	fTDCMODE[i][j] -> Select(1);
				if (ana.tdcmode[i][j] == 0)	fTDCMODE[i][j] -> Select(0);
			}
		}
		else
		{
			for (Int_t j = 0; j < 4; j++)
			{
				ana.dfmode[i][j] = ana.dfmode[0][0];
				ana.adcmode[i][j] = ana.adcmode[0][0];
				ana.tdcmode[i][j] = ana.tdcmode[0][0];
				ana.pre_thr[i][j] = ana.pre_thr[0][0];
				ana.thr[i][j] = ana.thr[0][0];
				ana.delay[i][j] = ana.delay[0][0];
				ana.ratio[i][j] = ana.ratio[0][0];
				ana.length[i][j] = ana.length[0][0];
				ana.flength[i][j] = ana.flength[0][0];
				ana.gap[i][j] = ana.gap[0][0];

				fDFTHR[i][j] -> SetText(Form("%d", ana.thr[i][j]), kFALSE);
				fPRETHR[i][j] -> SetText(Form("%d", ana.pre_thr[i][j]), kFALSE);
				fDELAY[i][j] -> SetText(Form("%d", ana.delay[i][j]), kFALSE);
				fRATIO[i][j] -> SetText(Form("%f", ana.ratio[i][j]), kFALSE);
				fLENGTH[i][j] -> SetText(Form("%d", ana.length[i][j]), kFALSE);
				fFLENGTH[i][j] -> SetText(Form("%d", ana.flength[i][j]), kFALSE);
				fGAP[i][j] -> SetText(Form("%d", ana.gap[i][j]), kFALSE);

				if (ana.dfmode[i][j] == 1)	fDFMODE[i][j] -> Select(0);
				if (ana.dfmode[i][j] == 0)	fDFMODE[i][j] -> Select(1);

				if (ana.adcmode[i][j] == 1)	fADCMODE[i][j] -> Select(1);
				if (ana.adcmode[i][j] == 0)	fADCMODE[i][j] -> Select(0);

				if (ana.tdcmode[i][j] == 1)	fTDCMODE[i][j] -> Select(1);
				if (ana.tdcmode[i][j] == 0)	fTDCMODE[i][j] -> Select(0);
			}
		}
	}
}

void FADC500Gui::StartAnalyzer()
{
	TString datafile = directory + openFile;

	if (datafile.Length() >= 1)
	{
		ana.main(datafile);
	}
	if (datafile.Length() == 0)
	{
		cout << "Please open data file." << endl;
	}
}

void FADC500Gui::StopAnalyzer()
{
	ana.flag = 0;
	gSystem -> ProcessEvents();
}

void FADC500Gui::FilterOn()
{
	ana.draw_flag = 1;
	gSystem -> ProcessEvents();
}

void FADC500Gui::FilterOff()
{
	ana.draw_flag = 0;
	gSystem -> ProcessEvents();
}
