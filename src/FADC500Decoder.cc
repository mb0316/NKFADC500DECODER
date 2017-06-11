//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 19 19:11:58 2016 by ROOT version 5.34/21
// from TTree wftree/waveform tree FADC500
// found on file: hpge161118_1.root
//////////////////////////////////////////////////////////

// Data structure
// 0-3   : data length
// 4-5   : run_number
// 6 low : trigger type
// 6 up  : trigger destination
// 7-10  : trigger number
// 11    : trigger fine time
// 12-14 : trigger coarse time
// 15    : module id
// 16    : channel id
// 17-20 : local trigger number
// 21-24 : local trigger pattern
// 25    : local starting fine time
// 26-28 : local starting coarse time
// 29-31 : not assigned
// 32-data_length : waveform data
// ADC data( 12bit )
// 32+Offset+point_id*2       (0xFF): waveform adc data[0-1]
// 32+Offset+point_id*2+1 low (0x0F): waveform adc data[2]
// TDC data( 10bit,1000 = 8ns)
// 32+Offset+point_id*2+1 up(0xF0) : waveform tdc data[0]
// 32+Offset+point_id*2+3 up(0xF0) : waveform tdc data[1]
// 32+OFfset+point_id*2+5 up(0x30) : waveform tdc data[2]


#include <TROOT.h>
#include <TChain.h>
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "FADC500Decoder.h"
#include "TSystem.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include <stdio.h>
#include <iostream>
#include <fstream>


void FADC500Decoder::GetTree(const char* filename, TTree *tree)
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

Int_t FADC500Decoder::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}

Long64_t FADC500Decoder::LoadTree(Long64_t entry)
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

void FADC500Decoder::Init(TTree *tree)
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
	fChain->SetBranchAddress("data_length", &data_length, &b_data_length);
	fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
	fChain->SetBranchAddress("trig_type", &trig_type, &b_trig_type);
	fChain->SetBranchAddress("trig_dest", &trig_dest, &b_trig_dest);
	fChain->SetBranchAddress("trig_num", &trig_num, &b_trig_num);
	fChain->SetBranchAddress("trig_ftime", &trig_ftime, &b_trig_ftime);
	fChain->SetBranchAddress("trig_ctime", &trig_ctime, &b_trig_ctime);
	fChain->SetBranchAddress("local_trig_num", &local_trig_num, &b_local_trig_num);
	fChain->SetBranchAddress("local_trig_pattern", &local_trig_pattern, &b_local_trig_pattern);
	fChain->SetBranchAddress("local_trig_ftime", &local_trig_ftime, &b_local_str_ftime);
	fChain->SetBranchAddress("local_trig_ctime", &local_trig_ctime, &b_local_str_ctime);
	fChain->SetBranchAddress("waveform_length", &waveform_length, &b_waveform_length);
	fChain->SetBranchAddress("waveform", waveform, &b_waveform);
	fChain->SetBranchAddress("waveformtime", waveformtime, &b_waveformtime);
	fChain->SetBranchAddress("twaveform_length", &twaveform_length, &b_twaveform_length);
	fChain->SetBranchAddress("twaveform", twaveform, &b_twaveform);
	fChain->SetBranchAddress("waveform_ftime", &waveform_ftime, &b_waveform_ftime);
	Notify();
}

void FADC500Decoder::Build(TTree *tree)
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
	fChain->Branch("data_length", &data_length, "data_length/I");
	fChain->Branch("run_number", &run_number, "run_number/I");
	fChain->Branch("trig_type", &trig_type, "trig_type/I");
	fChain->Branch("trig_dest", &trig_dest, "trig_dest/I");
	fChain->Branch("trig_num", &trig_num, "trig_num/l");
	fChain->Branch("trig_ftime", &trig_ftime, "trig_ftime/l");
	fChain->Branch("trig_ctime", &trig_ctime, "trig_ctime/l");
	fChain->Branch("local_trig_num", &local_trig_num, "local_trig_num/l");
	fChain->Branch("local_trig_pattern", &local_trig_pattern, "local_trig_pattern/l");
	fChain->Branch("local_trig_ftime", &local_trig_ftime, "local_trig_ftime/l");
	fChain->Branch("local_trig_ctime", &local_trig_ctime, "local_trig_ctime/l");
	fChain->Branch("waveform_length", &waveform_length, "waveform_length/I");
	fChain->Branch("waveform", waveform, "waveform[waveform_length]/I");
	fChain->Branch("waveformtime", waveformtime, "waveformtime[waveform_length]/I");
	fChain->Branch("twaveform_length", &twaveform_length, "twaveform_length/I");
	fChain->Branch("twaveform", twaveform, "twaveform[twaveform_length]/I");
	fChain->Branch("waveform_ftime", &waveform_ftime, "waveform_ftime/D");
	Notify();
}

Bool_t FADC500Decoder::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FADC500Decoder::Show(Long64_t entry)
{
	// Print contents of entry.
	// If entry is not specified, print current entry
	if (!fChain) return;
	fChain->Show(entry);
}

void FADC500Decoder::Decoder(TString datafile)
{
	TString inputfile = datafile;
    TObjArray *decomposedFileNameWithPath = datafile.Tokenize(".");
    TString filetype = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    datafile.ReplaceAll(filetype, "root");
	std::cout << "Data input file name : " << inputfile << std::endl;
	std::cout << "Data output file name : " << datafile << std::endl;

	FILE *fcheck;
	fcheck = fopen(inputfile, "rb");
	char checklength[4];

	fread(checklength, 1, 4, fcheck);
	const int length
		= (checklength[0] & 0xFF)
		+ ((checklength[1] & 0xFF) << 8)
		+ ((checklength[2] & 0xFF) << 16)
		+ ((checklength[3] & 0xFF) << 24);
	fclose(fcheck);

	std::cout << "Data Length : " << length << std::endl;

	char data[length];

	TFile* out = new TFile(datafile, "recreate");
	TTree* tree = new TTree("tree", "data");
	Build(tree);

	FILE *file;
	file = fopen(inputfile, "rb");

	UInt_t  itmp;
	ULong_t ltmp;
	int read_size = 0;
	event_number = 0;
	int firsttdc = 0;
	flag = 1;


	std::cout << "Start decoding the data." << std::endl;
	while(1)
	{
		gSystem -> ProcessEvents();
		if (flag == 1)
		{
			read_size = fread ( data , 1, length, file );
			if(read_size == 0 || read_size != length)
			{
				std::cout<< "End the data readout." << std::endl;
				break;
			}
			if (event_number % 100 == 0)	std::cout << "Event number : " << event_number << std::endl;
			gSystem -> ProcessEvents();


			data_length
				= (data[0] & 0xFF)
				+ ((data[1] & 0xFF) << 8)
				+ ((data[2] & 0xFF) << 16)
				+ ((data[3] & 0xFF) << 24);
			run_number
				= (data[4] & 0xFF)
				+ ((data[5] & 0xFF) << 8);
			trig_type
				= (data[6] & 0x0F);
			trig_dest
				= (data[6] & 0xF0) >> 4;
			trig_num
				= (data[7] & 0xFF)
				+ ((data[8] & 0xFF ) << 8)
				+ ((data[9] & 0xFF ) << 16)
				+ ((data[10] & 0xFF ) << 24);
			trig_ftime
				= (data[11] & 0xFF);
			trig_ctime
				= (data[12] & 0xFF)
				+ ((data[13] & 0xFF ) << 8 )
				+ ((data[14] & 0xFF ) << 16 );
			mid = (data[15] & 0xFF);
			cid = (data[16] & 0xFF);
			local_trig_num
				= (data[17] & 0xFF)
				+ ((data[18] & 0xFF) << 8 )
				+ ((data[19] & 0xFF) << 16 )
				+ ((data[20] & 0xFF) << 24 );
			local_trig_pattern
				= (data[21] & 0xFF)
				+ ((data[22] & 0xFF) << 8 )
				+ ((data[23] & 0xFF) << 16 )
				+ ((data[24] & 0xFF) << 24 );
			local_trig_ftime
				= (data[25] & 0xFF);
			local_trig_ctime
				= (data[26] & 0xFF)
				+ ((data[27] & 0xFF) << 8 )
				+ ((data[28] & 0xFF) << 16 );
			gSystem -> ProcessEvents();

			if( data_length != length)
			{
				std::cout<< "Wrong data_length, Abort event" << std::endl;
				std::cout<< data_length << "\t" << length<< std::endl;
				continue;
			}
			gSystem -> ProcessEvents();
			Channel = (mid-1)*4 + cid-1;
			if( Channel >= 24 || Channel <  0  )
			{
				std::cout<< "Wrong Channel, Abort event" << std::endl;
				std::cout<< Channel << std::endl;
				continue;
			}
			gSystem -> ProcessEvents();
			waveform_length = (int)((data_length - 32)/2);
			twaveform_length = waveform_length/4;
			firsttdc = 0;
			gSystem -> ProcessEvents();
			for( int ip = 0; ip < waveform_length; ip++)
			{
				gSystem -> ProcessEvents();
				waveform[ip] = (UInt_t) (data[32+ip*2] & 0xFF) + ((data[32+ip*2+1] & 0x0F) << 8 );
				waveformtime[ip] = 2*ip;
				if( (ip % 4) == 0 )
				{
					gSystem -> ProcessEvents();
					twaveform[ip/4] = (UInt_t)(((data[32+ip*2+1] >> 4 ) & 0xF ) + (((data[32+ip*2+3] >> 4 ) & 0xF ) << 4 ) + (((data[32+ip*2+5] >> 4 ) & 0x3 ) << 8 ));
					if( twaveform[ip/4]  != 0 && firsttdc == 0 )
					{
						gSystem -> ProcessEvents();
						waveform_ftime = (double)(ip/4)*8000+twaveform[ip/4]*8;// ps order
						firsttdc = 1;
					}
				}

				gSystem -> ProcessEvents();
			}
			gSystem -> ProcessEvents();
			gSystem -> ProcessEvents();
			if (flag == 0)	break;
			gSystem -> ProcessEvents();
			tree->Fill();
			event_number++;
			gSystem -> ProcessEvents();
		}
		if (flag == 0)	break;
	}

	tree->Write();
	fclose( file );
	out->Close();
	std::cout << "The data has been successfully decoded." << std::endl;

}


void FADC500Decoder::Online(TString datafile)
{
	TString inputfile = datafile;
    TObjArray *decomposedFileNameWithPath = datafile.Tokenize(".");
    TString filetype = ((TObjString *) decomposedFileNameWithPath -> Last()) -> GetString();
    datafile.ReplaceAll(filetype, "root");
	std::cout << "Data input file name : " << inputfile << std::endl;
	std::cout << "Data output file name : " << datafile << std::endl;

	FILE *fcheck;
	fcheck = fopen(inputfile, "rb");
	char checklength[4];

	fread(checklength, 1, 4, fcheck);
	const int length
		= (checklength[0] & 0xFF)
		+ ((checklength[1] & 0xFF) << 8)
		+ ((checklength[2] & 0xFF) << 16)
		+ ((checklength[3] & 0xFF) << 24);
	fclose(fcheck);

	std::cout << "Data Length : " << length << std::endl;

	char data[length];

	TFile* out = new TFile(datafile, "recreate");
	TTree* tree = new TTree("tree", "data");
	Build(tree);

	FILE *file;
	file = fopen(inputfile, "rb");

	UInt_t  itmp;
	ULong_t ltmp;
	int read_size = 0;
	event_number = 0;
	int firsttdc = 0;
	on_flag = 1;
	monitorflag = 1;


	std::cout << "Start decoding the data." << std::endl;
	while(1)
	{
		gSystem -> ProcessEvents();
		if (on_flag == 1)
		{
			read_size = fread ( data , 1, length, file );
			if(read_size == 0 || read_size != length)
			{
				std::cout<< "End the data readout." << std::endl;
				break;
			}
			gSystem -> ProcessEvents();


			data_length
				= (data[0] & 0xFF)
				+ ((data[1] & 0xFF) << 8)
				+ ((data[2] & 0xFF) << 16)
				+ ((data[3] & 0xFF) << 24);
			run_number
				= (data[4] & 0xFF)
				+ ((data[5] & 0xFF) << 8);
			trig_type
				= (data[6] & 0x0F);
			trig_dest
				= (data[6] & 0xF0) >> 4;
			trig_num
				= (data[7] & 0xFF)
				+ ((data[8] & 0xFF ) << 8)
				+ ((data[9] & 0xFF ) << 16)
				+ ((data[10] & 0xFF ) << 24);
			trig_ftime
				= (data[11] & 0xFF);
			trig_ctime
				= (data[12] & 0xFF)
				+ ((data[13] & 0xFF ) << 8 )
				+ ((data[14] & 0xFF ) << 16 );
			mid = (data[15] & 0xFF);
			cid = (data[16] & 0xFF);
			local_trig_num
				= (data[17] & 0xFF)
				+ ((data[18] & 0xFF) << 8 )
				+ ((data[19] & 0xFF) << 16 )
				+ ((data[20] & 0xFF) << 24 );
			local_trig_pattern
				= (data[21] & 0xFF)
				+ ((data[22] & 0xFF) << 8 )
				+ ((data[23] & 0xFF) << 16 )
				+ ((data[24] & 0xFF) << 24 );
			local_trig_ftime
				= (data[25] & 0xFF);
			local_trig_ctime
				= (data[26] & 0xFF)
				+ ((data[27] & 0xFF) << 8 )
				+ ((data[28] & 0xFF) << 16 );
			gSystem -> ProcessEvents();

			if( data_length != length)
			{
				std::cout<< "Wrong data_length, Abort event" << std::endl;
				std::cout<< data_length << "\t" << length<< std::endl;
				continue;
			}
			gSystem -> ProcessEvents();
			Channel = (mid-1)*4 + cid-1;
			if( Channel >= 24 || Channel <  0  )
			{
				std::cout<< "Wrong Channel, Abort event" << std::endl;
				std::cout<< Channel << std::endl;
				continue;
			}
			gSystem -> ProcessEvents();
			waveform_length = (int)((data_length - 32)/2);
			twaveform_length = waveform_length/4;
			firsttdc = 0;
			gSystem -> ProcessEvents();
			for( int ip = 0; ip < waveform_length; ip++)
			{
				gSystem -> ProcessEvents();
				waveform[ip] = (UInt_t) (data[32+ip*2] & 0xFF) + ((data[32+ip*2+1] & 0x0F) << 8 );
				waveformtime[ip] = 2*ip;
				if( (ip % 4) == 0 )
				{
					gSystem -> ProcessEvents();
					twaveform[ip/4] = (UInt_t)(((data[32+ip*2+1] >> 4 ) & 0xF ) + (((data[32+ip*2+3] >> 4 ) & 0xF ) << 4 ) + (((data[32+ip*2+5] >> 4 ) & 0x3 ) << 8 ));
					if( twaveform[ip/4]  != 0 && firsttdc == 0 )
					{
						gSystem -> ProcessEvents();
						waveform_ftime = (double)(ip/4)*8000+twaveform[ip/4]*8;// ps order
						firsttdc = 1;
					}
				}

				gSystem -> ProcessEvents();
			}
			gSystem -> ProcessEvents();
			Monitor(monitorflag);
			gSystem -> ProcessEvents();
			if (on_flag == 0)	break;
			gSystem -> ProcessEvents();
			if (event_number%1 == 0)
			{
				std::cout << "Event number : " << event_number << std::endl;
				std::cout << "Trigger number : " << trig_num << std::endl;
				std::cout << "Local trigger number : " << local_trig_num << std::endl;
				std::cout << "Module ID : " << mid << std::endl;
				std::cout << "Channel ID : " << cid << std::endl;
				std::cout << "///////////////////////////////////////////////////" << std::endl;
			}

			tree->Fill();
			event_number++;
			gSystem -> ProcessEvents();
		}
		if (on_flag == 2)
		{
			std::cout << "PAUSED" << std::endl;
		}
		if (on_flag == 0)	break;
	}

	tree->Write();
	fclose( file );
	out->Close();
	std::cout << "The data has been successfully decoded." << std::endl;

}

void FADC500Decoder::Monitor(Int_t &monitorflag)
{
	gSystem -> ProcessEvents();
	if (event_number == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				fadc[i][j] = new TH1D(Form("Flash_ADC%d%d", i, j), "FADC; Time (ns); ADC;", waveform_length, 0, 2*waveform_length);
				adc[i][j] = new TH1D(Form("ADC%d%d", i, j), "ADC; ADC; Counts;", 4096, 0, 4096);
				tdc[i][j] = new TH1D(Form("TDC%d%d", i, j), "TDC; Time (ps); Counts;", 1000, 0, 10000E3); 
				rate[i][j] = new TGraph();
			}
		}
	}
	gSystem -> ProcessEvents();
	if (monitorflag == 1)
	{

		if (event_number > 0)
		{
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					fadc[i][j] -> Reset();
				}
			}
		}
		gSystem -> ProcessEvents();


		Int_t ped = 0;

		for (int i = 0; i < 10; i++)
		{
			ped += waveform[i];
		}
		gSystem -> ProcessEvents();
		ped = int(ped/10);

		for (int i = 0; i < waveform_length; i++)
		{
			fadc[mid-1][cid-1] -> Fill(waveformtime[i], waveform[i]);
		}	
		fadc[mid-1][cid-1] -> Sumw2(kFALSE);
		gSystem -> ProcessEvents();

		Int_t tempadc1 = 0;
		Int_t tempadc2 = 0;

		tempadc1 = fadc[mid-1][cid-1] -> GetMaximum();
		tempadc2 = fadc[mid-1][cid-1] -> GetMinimum();
		if (abs(tempadc1-ped) > abs(tempadc2-ped))	adcvalue = tempadc1 - ped;
		if (abs(tempadc1-ped) < abs(tempadc2-ped))	adcvalue = ped - tempadc2;
		gSystem -> ProcessEvents();

		adc[mid-1][cid-1] -> Fill(adcvalue);
		tdc[mid-1][cid-1] -> Fill(waveform_ftime);
		gSystem -> ProcessEvents();

		if (local_trig_num == 0)	tdiff[mid-1][cid-1] = 0;
		if (local_trig_num != 0)	tdiff[mid-1][cid-1] = local_trig_ctime - tdiff[mid-1][cid-1];
		rate[mid-1][cid-1] -> SetPoint(local_trig_num, local_trig_num, tdiff[mid-1][cid-1]);
		if (local_trig_num > 500)   rate[mid-1][cid-1] -> GetXaxis() -> SetLimits(local_trig_num-500, local_trig_num+100);

		c1[mid-1][cid-1] -> cd();
		c1[mid-1][cid-1] -> Modified();
		c1[mid-1][cid-1] -> Update();
		fadc[mid-1][cid-1] -> Draw();
		gSystem -> ProcessEvents();

		c2[mid-1][cid-1] -> cd();
		c2[mid-1][cid-1] -> Modified();
		c2[mid-1][cid-1] -> Update();
		adc[mid-1][cid-1] -> Draw();
		gSystem -> ProcessEvents();

		c3[mid-1][cid-1] -> cd();
		c3[mid-1][cid-1] -> Modified();
		c3[mid-1][cid-1] -> Update();
		tdc[mid-1][cid-1] -> Draw();
		gSystem -> ProcessEvents();

		c4[mid-1][cid-1] -> cd();
		c4[mid-1][cid-1] -> Modified();
		c4[mid-1][cid-1] -> Update();
		rate[mid-1][cid-1] -> Draw();
		gSystem -> ProcessEvents();


		
		tdiff[mid-1][cid-1] = local_trig_ctime;
	}
	
}
