//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 15 22:47:51 2017 by ROOT version 6.07/03
// from TTree tree/tree
// found on file: TOTME13HV3.root
//////////////////////////////////////////////////////////

#ifndef pressure_dependence_removal_h
#define pressure_dependence_removal_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH3.h>
#include <TF1.h>
#include <TGraphErrors.h>
// Header file for the classes stored in the TTree if any.

class pressure_dependence_removal {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   ULong64_t       _eventNb;
   ULong64_t       _runNb;
   ULong64_t       _lumiBlock;
   Int_t           _rhid;
   Int_t           _stationring;
   Double_t        _rhsumQ;
   Double_t        _rhsumQ_RAW;

   Double_t        _pressure;
   Double_t        _temperature;
   Double_t        _instlumi;
   Double_t        _integratelumi;
   UInt_t          _timesecond;
   Int_t           _n_PV;
   Int_t           _bunchcrossing;

	 // Declaration of leaf types for new tree
   ULong64_t        new_eventNb;
   ULong64_t        new_runNb;
   ULong64_t        new_lumiBlock;
   Int_t            new_rhid;
   Int_t            new_stationring;
   Double_t         new_rhsumQ;
   Double_t         new_rhsumQ_RAW;

   Double_t         new_pressure;
   Double_t         new_temperature;
   Double_t         new_instlumi;
   Double_t         new_integratelumi;
   UInt_t           new_timesecond;
   Int_t            new_n_PV;
   Int_t            new_bunchcrossing;


   // List of branches
   TBranch        *b__eventNb;   //!
   TBranch        *b__runNb;   //!
   TBranch        *b__lumiBlock;   //!
   TBranch        *b__rhid;   //!
   TBranch        *b__stationring;   //!
   TBranch        *b__rhsumQ;   //!
   TBranch        *b__rhsumQ_RAW;   //!
   TBranch        *b__pressure;   //!
   TBranch        *b__temperature;   //!
   TBranch        *b__instlumi;   //!
   TBranch        *b__integratelumi;   //!
   TBranch        *b__timesecond;   //!
   TBranch        *b__n_PV;   //!
   TBranch        *b__bunchcrossing;   //!


	 TDirectory *dir_var_name;
   pressure_dependence_removal(TTree *tree=0);
   virtual ~pressure_dependence_removal();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);



	 std::vector<float > trimmed_mean(TH2D *myh);
   virtual vector <std::pair<double,double > >  GetSlope( TH3D * myh , TString thevar , TString filename, TString title, TFile * outf);

   double ApplyCorrection( double pressure ,TString correctiontype, double p0, double p1 );
   virtual void  Loop(TString , TString, TString, TString, TString);
   
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

	  TTree *tree_new;
	  TString chamber_string_name; 
    TString output_path ;
    TString output_plots_folder ; 
		TString detregionstr;

/*		std::vector<UInt_t> *time_vector=nullptr;
		std::vector<double> *gas_gain_vector=nullptr;
		std::vector<double> *gas_gain_error_vector=nullptr;
*/
		std::vector<UInt_t> time_vector;
		std::vector<double> gas_gain_vector;
		std::vector<double> gas_gain_error_vector;
		double time_value;
		double old_time;
    std::string new_time;
    const char* new_time_Char;

	  std::string time_conv(double timeSeconds);
		void plot_gain_time();
    void Setup_new_tree();
};

#endif

#ifdef pressure_dependence_removal_cxx
pressure_dependence_removal::pressure_dependence_removal(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
 
}

pressure_dependence_removal::~pressure_dependence_removal()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pressure_dependence_removal::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pressure_dependence_removal::LoadTree(Long64_t entry)
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


void pressure_dependence_removal::Setup_new_tree(){

 tree_new->Branch("new_eventNb",&new_eventNb, "new_eventNb/l");
 tree_new->Branch("new_runNb",&new_runNb, "new_runNb/l");
 tree_new->Branch("new_lumiBlock",&new_lumiBlock, "new_lumiBlock/l");
 tree_new->Branch("new_rhid",&new_rhid, "new_rhid/I");
 tree_new->Branch("new_stationring",&new_stationring, "new_stationring/I");
 tree_new->Branch("new_rhsumQ",&new_rhsumQ , "new_rhsumQ/D");
 tree_new->Branch("new_rhsumQ_RAW", &new_rhsumQ_RAW, "new_rhsumQ_RAW/D");
 tree_new->Branch("new_pressure", &new_pressure, "new_pressure/D");
 tree_new->Branch("new_temperature", &new_temperature, "new_temperature/D");
 tree_new->Branch("new_instlumi", &new_instlumi, "new_instlumi/D");
 tree_new->Branch("new_integratelumi", &new_integratelumi, "new_integratelumi/D");
 tree_new->Branch("new_timesecond",&new_timesecond, "new_timesecond/i");
 tree_new->Branch("new_n_PV", &new_n_PV, "new_n_PV/I");
 tree_new->Branch("new_bunchcrossing", &new_bunchcrossing, "new_bunchcrossing/I");

}

void pressure_dependence_removal::Init(TTree *tree)
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

   fChain->SetBranchAddress("_eventNb", &_eventNb, &b__eventNb);
   fChain->SetBranchAddress("_runNb", &_runNb, &b__runNb);
   fChain->SetBranchAddress("_lumiBlock", &_lumiBlock, &b__lumiBlock);
   fChain->SetBranchAddress("_rhid", &_rhid, &b__rhid);
   fChain->SetBranchAddress("_stationring", &_stationring, &b__stationring);
   fChain->SetBranchAddress("_rhsumQ", &_rhsumQ, &b__rhsumQ);
   fChain->SetBranchAddress("_rhsumQ_RAW", &_rhsumQ_RAW, &b__rhsumQ_RAW);
   fChain->SetBranchAddress("_pressure", &_pressure, &b__pressure);
   fChain->SetBranchAddress("_temperature", &_temperature, &b__temperature);
   fChain->SetBranchAddress("_instlumi", &_instlumi, &b__instlumi);
   fChain->SetBranchAddress("_integratelumi", &_integratelumi, &b__integratelumi);
   fChain->SetBranchAddress("_timesecond", &_timesecond, &b__timesecond);
//   fChain->SetBranchAddress("_n_PV", &_n_PV, &b__n_PV);
   fChain->SetBranchAddress("_bunchcrossing", &_bunchcrossing, &b__bunchcrossing);

   fChain->SetBranchStatus("_temperature",0);
   fChain->SetBranchStatus("_lumiBlock",0);
   fChain->SetBranchStatus("_eventNb",0);
//   fChain->SetBranchStatus("_n_PV",0);
   fChain->SetBranchStatus("_bunchcrossing",0);
//   fChain->SetBranchStatus("_timesecond",0);

   Notify();
   
}
std::string time_conv(double timeSeconds) {
    // Set the time in seconds                                                                                                       
                                                                                                                                     
    // Convert to time_t (seconds since epoch)                                                                                       
    time_t timeEpoch = timeSeconds;
                                                                                                                                     
    // Convert to tm structure                                                                                                       
    struct tm* timeInfo = gmtime(&timeEpoch);
                                                                                                                                     
    // Format the date and time                                                                                                      
    std::string strBuffer(80, '\0'); 
    strftime(&strBuffer[0], 80, "%d/%m", timeInfo);
                                                                                                                                     
    // Print the date and time                                                                                                       
    std::cout << "Time in seconds: " << timeSeconds << std::endl; 
    std::cout << "Date and time: " << strBuffer << std::endl;
                                                                                                                                     
    return strBuffer;
}

Bool_t pressure_dependence_removal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pressure_dependence_removal::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pressure_dependence_removal::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pressure_dependence_removal_cxx
