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

using namespace std;


void FADC500Analysis::GetTree(const char* filename, TTree *tree)
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

void FADC500Analysis::main(TString datafile)
{
	TString inputfile = datafile;
    TObjArray *decomposedFileNameWithPath = datafile.Tokenize("/");
    TString filename = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    datafile.ReplaceAll(filename, Form("ana_%s", filename.Data()));
    std::cout << "Data input file name : " << inputfile << std::endl;
    std::cout << "Data output file name : " << datafile << std::endl;

	gSystem -> ProcessEvents();

	data.GetTree(inputfile.Data());
	gSystem -> ProcessEvents();

	TFile* out = new TFile(datafile.Data(), "RECREATE");
	TTree* t1 = new TTree("data", "data");
	Build(t1);
	gSystem -> ProcessEvents();

	Long64_t nEnt = data.fChain -> GetEntries();
	std::cout << "Entries : " << nEnt << std::endl;

	flag = 1;
	draw_flag = 1;
	result_flag = 1;
	gSystem -> ProcessEvents();

	std::cout << "Start analysis." << std::endl;

	for (Int_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		gSystem -> ProcessEvents();
		data.fChain -> GetEntry(iEnt);

		event_number = data.event_number;
		Channel = data.Channel;
		mid = data.mid;
		cid = data.cid;
		trig_num = data.trig_num;
		trig_ftime = data.trig_ftime;
		trig_ctime = data.trig_ctime;
		local_trig_num = data.local_trig_num;
		local_trig_ftime = data.local_trig_ftime;
		local_trig_ctime = data.local_trig_ctime;
		waveform_ftime = data.waveform_ftime;
		gSystem -> ProcessEvents();

		std::cout << "-----------------------------------------------------" << std::endl;
		std::cout << "Entry : " << iEnt << std::endl;
		std::cout << "Process : " << 100*iEnt/nEnt << " %" << std::endl;
		std::cout << "Module ID : " << mid << std::endl;
		std::cout << "Channel ID : " << cid << std::endl;
		
		if (dfmode[mid-1][cid-1] == 1)	DigitalFilter();
		gSystem -> ProcessEvents();
		if (adcmode[mid-1][cid-1] == 0)
		{
			AnaADC();
			std::cout << "ADC : " << ADC << std::endl;
		}
		gSystem -> ProcessEvents();
		if (adcmode[mid-1][cid-1] == 1)
		{
			AnaQDC();
			std::cout << "QDC : " << QDC << std::endl;
		}
		gSystem -> ProcessEvents();
		if (tdcmode[mid-1][cid-1] == 0)
		{
			AnaTDC_LEAD();
			std::cout << "TDC : " << TDC_LEAD << std::endl;
		}
		gSystem -> ProcessEvents();
		if (tdcmode[mid-1][cid-1] == 1)
		{
			AnaTDC_CFD();
			std::cout << "TDC : " << TDC_CFD << std::endl;
		}
		std::cout << "-----------------------------------------------------" << std::endl;
		gSystem -> ProcessEvents();

		if (draw_flag == 1)	DrawProcess();
		gSystem -> ProcessEvents();

		if (flag == 0)	break;
		gSystem -> ProcessEvents();

		t1 -> Fill();
		gSystem -> ProcessEvents();

		clearall();
	}
	out -> cd();
	t1 -> Write();
	out -> Close();

	pulse_hist = 0;
	tfa_hist = 0;
	cfd_hist = 0;
	dfa_hist = 0;

	std::cout << "All work has been finished." << std::endl;
}

void FADC500Analysis::DigitalFilter()
{
	for (Int_t ipoint = 0; ipoint < data.waveform_length; ipoint++)
	{
		gSystem -> ProcessEvents();
		// Trapezoidal Digital Filter for ADC
		if (ipoint < (data.waveform_length-2*length[mid-1][cid-1]-gap[mid-1][cid-1]))
		{
			for (Int_t j = 0; j < length[mid-1][cid-1]; j++)
			{
				data_L += data.waveform[ipoint+j];
				data_G += data.waveform[length[mid-1][cid-1]+gap[mid-1][cid-1]+ipoint+j];
			}
		}
		gSystem -> ProcessEvents();

		// Triangular Digital Filter for CFD-TDC
		if (ipoint < (data.waveform_length-2*flength[mid-1][cid-1]))
		{
			for (Int_t j = 0; j < flength[mid-1][cid-1]; j++)
			{
				data_fL += data.waveform[ipoint+j];
				data_fG += data.waveform[flength[mid-1][cid-1]+ipoint+j];
			}
		}
		gSystem -> ProcessEvents();

		data_L = data_L/length[mid-1][cid-1];
		data_fL = data_fL/flength[mid-1][cid-1];
		data_G = data_G/length[mid-1][cid-1];
		data_fG = data_fG/flength[mid-1][cid-1];
		trape.push_back(data_G - data_L);
		tfa.push_back(data_fG - data_fL);
		data_L = 0;
		data_fL = 0;
		data_G = 0;
		data_fG = 0;
	}	
}

Double_t FADC500Analysis::AnaADC()
{
	if (dfmode[mid-1][cid-1] == 0)	//No digital filter function
	{
		gSystem -> ProcessEvents();
		for (Int_t i = 0; i < 10; i++)	pre_ped += data.waveform[i];
		pre_ped = pre_ped/10;
		cout << "Pulse Pedestal : " << pre_ped << endl;
		gSystem -> ProcessEvents();

		for (Int_t ipoint = 1; ipoint < data.waveform_length; ipoint++)
		{
			temp_point = abs(data.waveform[ipoint]-pre_ped);
			if (ipoint == 1)	ADC = abs(data.waveform[ipoint]-pre_ped);
			if (temp_point > ADC)	ADC = temp_point;
			else continue;
		}
		gSystem -> ProcessEvents();
		temp_point = 0;
		pre_flag = 0;
		pre_ped = 0;
	}
	if (dfmode[mid-1][cid-1] == 1)
	{
		gSystem -> ProcessEvents();
		for (Int_t i = 0; i < data.waveform_length; i++)
		{
			temp_point = trape[i];
			if (abs(temp_point) > thr[mid-1][cid-1])
			{
				trape_flag = i;
				break;
			}
			else continue;
		}
		temp_point = 0;
		gSystem -> ProcessEvents();

		for (Int_t i = 0; i < int(trape_flag/2); i++)	ped += trape[i];
		ped = ped/int(trape_flag/2);
		cout << "Pulse Pestal : " << ped << endl;
		gSystem -> ProcessEvents();

//		for (Int_t ipoint = trape_flag; ipoint < flag+length[mid-1][cid-1]+int(gap[mid-1][cid-1])/3; ipoint++)
		for (Int_t ipoint = 0; ipoint < data.waveform_length; ipoint++)
		{
			temp_point = abs(trape[ipoint]-ped);
			if (ipoint == trape_flag)	ADC = abs(trape[ipoint]-ped);
			if (temp_point > ADC)	ADC = temp_point;
			else continue;
		}
		gSystem -> ProcessEvents();
		temp_point = 0;
		trape_flag = 0;
		ped = 0;
		ADC = 20*ADC;
	}
	return ADC;
}

Double_t FADC500Analysis::AnaQDC()
{
	gSystem -> ProcessEvents();
	for (Int_t i = 0; i < 10; i++)	pre_ped += data.waveform[i];
	pre_ped = pre_ped/10;
	cout << "Pulse Pedestal : " << pre_ped << endl;
	gSystem -> ProcessEvents();

	for (Int_t ipoint = 0; ipoint < data.waveform_length; ipoint++)	QDC += abs(data.waveform[ipoint] - pre_ped);
	pre_flag = 0;
	pre_ped = 0;
	gSystem -> ProcessEvents();

	return QDC;
}

Double_t FADC500Analysis::AnaTDC_CFD()
{
	gSystem -> ProcessEvents();
	for (Int_t i = 0; i < data.waveform_length; i++)
	{
		temp_point = abs(tfa[i]);
		if (temp_point > thr[mid-1][cid-1])
		{
			tflag = i;
			break;
		}
		else continue;
	}
	temp_point = 0;
	gSystem -> ProcessEvents();

	for (Int_t i = 0; i < int(tflag/2); i++)	tped += tfa[i];
	tped = tped/int(tflag/2);
	gSystem -> ProcessEvents();

	for (Int_t ipoint = 0; ipoint < data.waveform_length; ipoint++)
	{
		if (ipoint <= delay[mid-1][cid-1])	cfd.push_back(0);
		else
		{
			data_delay = tfa[ipoint-delay[mid-1][cid-1]] - tped;
			data_cfd = ratio[mid-1][cid-1]*tfa[ipoint] - tped;
			cfd.push_back(-data_cfd+data_delay);
		}
	}
	gSystem -> ProcessEvents();

//	for (Int_t i = tflag; i < tflag+(delay[mid-1][cid-1]+2*flength[mid-1][cid-1])/2; i++)
	for (Int_t i = tflag; i < data.waveform_length; i++)
	{
		if ((cfd[tflag] > 0 && cfd[i] < 0) || (cfd[tflag] < 0 && cfd[i] > 0))
		{
			slope = (cfd[i]-cfd[i-1])/2;
			yax = cfd[i] - (cfd[i]-cfd[i-1])*data.waveformtime[i]/2;
			TDC_CFD = -yax/slope;
			break;
		}
	}
	gSystem -> ProcessEvents();
	tped = 0;
	slope = 0;
	yax = 0;
	data_delay = 0;
	data_cfd = 0;

	return TDC_CFD;
}

Double_t FADC500Analysis::AnaTDC_LEAD()
{
	gSystem -> ProcessEvents();
	for (Int_t i = 0; i < 10; i++)	tflag += data.waveform[i];
	tflag = tflag/10;
	gSystem -> ProcessEvents();

	for (Int_t i = 0; i < data.waveform_length; i++)
	{
		temp_point = data.waveform[i];
		if (abs(temp_point-tflag) > pre_thr[mid-1][cid-1])
		{
			slope = (data.waveform[i]-data.waveform[i-1])/2;
			yax = data.waveform[i] - (data.waveform[i]-data.waveform[i-1])*data.waveformtime[i]/2;
			TDC_LEAD = -yax/slope;
			break;
		}
	}
	gSystem -> ProcessEvents();
	tflag = 0;
	temp_point = 0;
	slope = 0;
	yax = 0;

	return TDC_LEAD;
}

void FADC500Analysis::clearall()
{
	gSystem -> ProcessEvents();
	ADC = 0;
	QDC = 0;
	TDC_CFD = 0;
	TDC_LEAD = 0;
	if (dfmode[mid-1][cid-1] == 1)
	{
		trape.clear();
		tfa.clear();
		cfd.clear();
	}
}

void FADC500Analysis::DrawProcess()
{
	gSystem -> ProcessEvents();
	if (event_number == 0)
	{
		pulse_hist = new TH1D("PULSE", "Pulse; Time (ns); ADC;", data.waveform_length, 0, 2*data.waveform_length);
		tfa_hist = new TH1D("TFA", "Timing Filter Amplifier; Time (ns); ADC;", data.waveform_length, 0, 2*data.waveform_length);
		cfd_hist = new TH1D("CFD", "Constant Fraction Discriminator; Time (ns); ADC;", data.waveform_length, 0, 2*data.waveform_length);
		dfa_hist = new TH1D("DFA", "Digital Filter Amplifier; Time (ns); ADC;", data.waveform_length, 0, 2*data.waveform_length);
	}
	gSystem -> ProcessEvents();
	if (event_number > 0)
	{
		pulse_hist -> Reset();
		tfa_hist -> Reset();
		cfd_hist -> Reset();
		dfa_hist -> Reset();
	}
	gSystem -> ProcessEvents();

	for (Int_t i = 0; i < data.waveform_length; i++)
	{
		pulse_hist -> Fill(data.waveformtime[i], data.waveform[i]);
		if (dfmode[mid-1][cid-1] == 1)
		{
			tfa_hist -> Fill(data.waveformtime[i], tfa[i]);
			cfd_hist -> Fill(data.waveformtime[i], cfd[i]);
			dfa_hist -> Fill(data.waveformtime[i], trape[i]);
		}
	}
	gSystem -> ProcessEvents();

	pulse_hist -> Sumw2(kFALSE);
	tfa_hist -> Sumw2(kFALSE);
	cfd_hist -> Sumw2(kFALSE);
	dfa_hist -> Sumw2(kFALSE);
	gSystem -> ProcessEvents();

	cPulse -> cd();
	cPulse -> Modified();
	cPulse -> Update();
	pulse_hist -> Draw();
	gSystem -> ProcessEvents();

	cDFA -> cd();
	cDFA -> Modified();
	cDFA -> Update();
	dfa_hist -> Draw();
	gSystem -> ProcessEvents();

	cTFA -> cd();
	cTFA -> Modified();
	cTFA -> Update();
	tfa_hist -> Draw();
	gSystem -> ProcessEvents();
	
	cCFD -> cd();
	cCFD -> Modified();
	cCFD -> Update();
	cfd_hist -> Draw();
	gSystem -> ProcessEvents();

}

