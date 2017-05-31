//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 19 19:11:58 2016 by ROOT version 5.34/21
// from TTree wftree/waveform tree FADC500
// found on file: hpge161118_1.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "FADC500Decoder.h"
#include "FADC500Analysis.h"
#include "TSystem.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TCanvas.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TF1.h"
#include <vector>


void FADC500Analysis::GetTree(char* filename, TTree *tree)
{
	if (tree == 0) {
		TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
		if (!f || !f->IsOpen()) {
			f = new TFile(filename);
		}
		f->GetObject("tree",tree);

	}
	Init(tree);
}

Int_t FADC500Analysis::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}

Long64_t FADC500Analysis::LoadTree(Long64_t entry)
{
	// Set the environment to read one entry
	if (!fChain) return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0) return centry;
	if (fChain->GetTreeNumber() != fCurrent) {
		fCurrent = fChain->GetTreeNumber();
		Notify();
	}
	return centry;
}

void FADC500Analysis::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	// Set branch addresses and branch pointers
	if (!tree) return;
	fChain = tree;
	fCurrent = -1;
	fChain->SetMakeClass(1);

	fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
	fChain->SetBranchAddress("Channel", &Channel, &b_Channel);
	fChain->SetBranchAddress("mid", &mid, &b_mid);
	fChain->SetBranchAddress("cid", &cid, &b_cid);
	fChain->SetBranchAddress("trig_num", &trig_num, &b_trig_num);
	fChain->SetBranchAddress("trig_ftime", &trig_ftime, &b_trig_ftime);
	fChain->SetBranchAddress("trig_ctime", &trig_ctime, &b_trig_ctime);
	fChain->SetBranchAddress("local_trig_num", &local_trig_num, &b_local_trig_num);
	fChain->SetBranchAddress("local_trig_ftime", &local_trig_ftime, &b_local_str_ftime);
	fChain->SetBranchAddress("local_trig_ctime", &local_trig_ctime, &b_local_str_ctime);
	fChain->SetBranchAddress("waveform_ftime", &waveform_ftime, &b_waveform_ftime);
	fChain->SetBranchAddress("ADC", &ADC, &b_ADC);
	fChain->SetBranchAddress("QDC", &QDC, &b_QDC);
	fChain->SetBranchAddress("TDC_CFD", &TDC_CFD, &b_TDC_CFD);
	fChain->SetBranchAddress("TDC_LEAD", &TDC_LEAD, &b_TDC_LEAD);
	Notify();
}

void FADC500Analysis::Build(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	// Set branch addresses and branch pointers
	if (!tree) return;
	fChain = tree;

	fChain->Branch("event_number", &event_number, "event_number/l");
	fChain->Branch("Channel", &Channel, "Channel/I");
	fChain->Branch("mid", &mid, "mid/I");
	fChain->Branch("cid", &cid, "cid/I");
	fChain->Branch("trig_num", &trig_num, "trig_num/l");
	fChain->Branch("trig_ftime", &trig_ftime, "trig_ftime/l");
	fChain->Branch("trig_ctime", &trig_ctime, "trig_ctime/l");
	fChain->Branch("local_trig_num", &local_trig_num, "local_trig_num/l");
	fChain->Branch("local_trig_ftime", &local_trig_ftime, "local_trig_ftime/l");
	fChain->Branch("local_trig_ctime", &local_trig_ctime, "local_trig_ctime/l");
	fChain->Branch("waveform_ftime", &waveform_ftime, "waveform_ftime/D");
	fChain->Branch("ADC", &ADC, "ADC/D");
	fChain->Branch("QDC", &QDC, "QDC/D");
	fChain->Branch("TDC_CFD", &TDC_CFD, "TDC_CFD/D");
	fChain->Branch("TDC_LEAD", &TDC_LEAD, "TDC_LEAD/D");
	Notify();
}

Bool_t FADC500Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FADC500Analysis::Show(Long64_t entry)
{
	// Print contents of entry.
	// If entry is not specified, print current entry
	if (!fChain) return;
	fChain->Show(entry);
}

