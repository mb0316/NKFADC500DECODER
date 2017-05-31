//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 19 19:11:58 2016 by ROOT version 5.34/21
// from TTree wftree/waveform tree FADC500
// found on file: hpge161118_1.root
//////////////////////////////////////////////////////////

#ifndef FADC500ANALYSIS_h
#define FADC500ANALYSIS_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1D.h"
#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"
#include <vector>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class FADC500Analysis {
	public :
		TTree          *fChain;   //!pointer to the analyzed TTree or TChain
		Int_t           fCurrent; //!current Tree number in a TChain

		// Declaration of leaf types
		ULong64_t       event_number;
		Int_t           Channel;
		Int_t           mid;
		Int_t           cid;
		ULong64_t       trig_num;
		ULong64_t       trig_ftime;
		ULong64_t       trig_ctime;
		ULong64_t       local_trig_num;
		ULong64_t       local_trig_ftime;
		ULong64_t       local_trig_ctime;
		Double_t        waveform_ftime;
		Double_t		ADC;
		Double_t		QDC;
		Double_t		TDC_CFD;
		Double_t		TDC_LEAD;

		// List of branches
		TBranch			*b_event_number;   //!
		TBranch        	*b_Channel;   //!
		TBranch        	*b_mid;   //!
		TBranch        	*b_cid;   //!
		TBranch        	*b_trig_num;   //!
		TBranch        	*b_trig_ftime;   //!
		TBranch        	*b_trig_ctime;   //!
		TBranch        	*b_local_trig_num;   //!
		TBranch        	*b_local_str_ftime;   //!
		TBranch        	*b_local_str_ctime;   //!
		TBranch        	*b_waveform_ftime;   //!
		TBranch        	*ADC;   //!
		TBranch        	*QDC;   //!
		TBranch        	*TDC_CFD;   //!
		TBranch        	*TDC_LEAD;   //!

		Int_t			flag = 1;
		TH1D			*tfa;
		TH1D			*tfa_inv;
		TH1D			*cfd;
		TH1D			*dfa;
		TH1D			*adc[6][4];
		TH1D			*qdc[6][4];
		TH1D			*tdc_cfd[6][4];
		TH1D			*tdc_lead[6][4];
		TCanvas			*cPulse;
		TCanvas			*cDFA;
		TCanvas			*cCFD;
		TCanvas			*cADC[6][4];
		TCanvas			*cQDC[6][4];
		TCanvas			*cTDC_CFD[6][4];
		TCanvas			*cTDC_LEAD[6][4];

		void     		GetTree(char* filename, TTree *tree=0);
		Int_t    		GetEntry(Long64_t entry);
		Long64_t	 	LoadTree(Long64_t entry);
		void    	 	Init(TTree *tree);
		void     		Build(TTree *tree);
		void    		Show(Long64_t entry = -1);
		Bool_t			Notify();
		void			main(TString datafile);
		Double_t		AnaADC();
		Double_t		AnaQDC();
		Double_t		AnaTDC_CFD();
		Double_t		AnaTDC_LEAD();
		void			DrawProcess();
		void			DrawResults();
};
#endif

