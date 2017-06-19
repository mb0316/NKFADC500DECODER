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
#include "FADC500Decoder.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class FADC500Analysis {
	private :
		FADC500Decoder	data;
		TH1D			*pulse_hist = 0;
		TH1D			*tfa_hist = 0;
		TH1D			*cfd_hist = 0;
		TH1D			*dfa_hist = 0;
	
		std::vector<double>	tfa;
		std::vector<double>	cfd;
		std::vector<double>	trape;

		Double_t		data_L;
		Double_t		data_fL;
		Double_t		data_G;
		Double_t		data_fG;
		Double_t		data_cfd;
		Double_t		data_tdc;
		Double_t		data_delay;
		Double_t		ped = 0;
		Double_t		tped = 0;
		Double_t		pre_ped = 0;
		Double_t		temp_point = 0;
		Double_t		max_tdc = 0;
		Int_t			trape_flag = 0;
		Int_t			tflag = 0;
		Int_t			pre_flag = 0;

        Double_t		slope = 0;
        Double_t		yax = 0;


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
		TBranch        	*b_ADC;   //!
		TBranch        	*b_QDC;   //!
		TBranch        	*b_TDC_CFD;   //!
		TBranch        	*b_TDC_LEAD;   //!

		TCanvas			*cPulse;
		TCanvas			*cDFA;
		TCanvas			*cTFA;
		TCanvas			*cCFD;

		Int_t			delay[6][4];
		Double_t		ratio[6][4];
		Int_t			length[6][4];
		Int_t			flength[6][4];
		Int_t			gap[6][4];
		Int_t			thr[6][4];
		Int_t			pre_thr[6][4];

		Int_t			draw_flag = 1;
		Int_t			result_flag = 1;
		Int_t			flag = 1;
		Int_t			adcmode[6][4]; //0 : ADC, 1 : QDC
		Int_t			tdcmode[6][4]; //0 : LEAD, 2 : CFD
		Int_t			dfmode[6][4]; //0 : unable, 1 : enable

		void     		GetTree(const char* filename, TTree *tree=0);
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
		void			DigitalFilter();
		void			clearall();
};
#endif

