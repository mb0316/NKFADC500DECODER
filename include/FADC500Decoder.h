//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 19 19:11:58 2016 by ROOT version 5.34/21
// from TTree wftree/waveform tree FADC500
// found on file: hpge161118_1.root
//////////////////////////////////////////////////////////

#ifndef FADC500DECODER_h
#define FADC500DECODER_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1D.h"
#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h"


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class FADC500Decoder {
	public :
		TTree          *fChain;   //!pointer to the analyzed TTree or TChain
		Int_t           fCurrent; //!current Tree number in a TChain

		// Declaration of leaf types
		ULong64_t       event_number;
		Int_t           Channel;
		Int_t           mid;
		Int_t           cid;
		Int_t           data_length;
		Int_t           run_number;
		Int_t           trig_type;
		Int_t           trig_dest;
		ULong64_t       trig_num;
		ULong64_t       trig_ftime;
		ULong64_t       trig_ctime;
		ULong64_t       local_trig_num;
		ULong64_t       local_trig_pattern;
		ULong64_t       local_trig_ftime;
		ULong64_t       local_trig_ctime;
		Int_t           waveform_length;
		Int_t           waveform[16368];   //[waveform_length]
		Int_t           waveformtime[16368];   //[waveform_length]
		Int_t           twaveform_length;
		Int_t           twaveform[4092];   //[twaveform_length]
		Double_t        waveform_ftime;

		Int_t			adcvalue;
		Double_t		tdiff[6][4];

		// List of branches
		TBranch			*b_event_number;   //!
		TBranch        	*b_Channel;   //!
		TBranch        	*b_mid;   //!
		TBranch        	*b_cid;   //!
		TBranch        	*b_data_length;   //!
		TBranch        	*b_run_number;   //!
		TBranch        	*b_trig_type;   //!
		TBranch        	*b_trig_dest;   //!
		TBranch        	*b_trig_num;   //!
		TBranch        	*b_trig_ftime;   //!
		TBranch        	*b_trig_ctime;   //!
		TBranch        	*b_local_trig_num;   //!
		TBranch        	*b_local_trig_pattern;   //!
		TBranch        	*b_local_str_ftime;   //!
		TBranch        	*b_local_str_ctime;   //!
		TBranch        	*b_waveform_length;   //!
		TBranch        	*b_waveform;   //!
		TBranch        	*b_waveformtime;   //!
		TBranch        	*b_twaveform_length;   //!
		TBranch        	*b_twaveform;   //!
		TBranch        	*b_twaveformValue;   //!
		TBranch        	*b_waveform_height;   //!
		TBranch        	*b_waveform_NEGint;   //!
		TBranch        	*b_waveform_POSint;   //!
		TBranch        	*b_waveform_ped;   //!
		TBranch        	*b_waveform_ftime;   //!

		Int_t			flag = 1;
		Int_t			on_flag = 1;
		Int_t			monitorflag = 1;
		TH1D			*fadc[6][4];
		TH1D			*adc[6][4];
		TH1D			*tdc[6][4];
		TGraph			*rate[6][4];
		TCanvas			*c1[6][4];
		TCanvas			*c2[6][4];
		TCanvas			*c3[6][4];
		TCanvas			*c4[6][4];
		UInt_t			eventflag[6][4];

		void     		GetTree(const char* filename, TTree *tree=0);
		Int_t    		GetEntry(Long64_t entry);
		Long64_t	 	LoadTree(Long64_t entry);
		void    	 	Init(TTree *tree);
		void     		Build(TTree *tree);
		void    		Show(Long64_t entry = -1);
		Bool_t			Notify();
		void			Online(TString datafile);
		void			Decoder(TString datafile);
		void			Monitor(Int_t &monitorflag);
};
#endif

