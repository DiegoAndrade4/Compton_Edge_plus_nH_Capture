//////////////////////////////////////////////////////////////////
// 
//  SBND Analysis ROOT Macro
//
////////////////////////////////////////////////////////////////// 



#include "TBranch.h"
#include "TTree.h"
#include "varsint.h"
//#include "varsdata.h"
#include "statunc.h"
#include <iomanip>
#include <algorithm>
#include "TGraph.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"
#include "TVector.h"
#include <string>
#include "TStyle.h"
#include "TColor.h"
#include <vector>

//#include <math.h>
//#include <cmath>


using namespace std;











// Input files 
//std::string   inputFileName   = "hist_BlipAna.root";
//std::string   outputFileName  = "output_hist_BlipAna.root";


// ROOT TTree and output file 
TTree* fTree;
TFile* fOutFile;

const Int_t nx = 8; 
const char* particle[nx] = {"p+","e-","e+","bkg","mu-","mu+","gamma","other"};


float LX1, UX1, LY1, UY1, LZ1, UZ1;
float LX2, UX2, LY2, UY2, LZ2, UZ2;
float LX3, UX3, LY3, UY3, LZ3, UZ3;
float LX4, UX4, LY4, UY4, LZ4, UZ4;
float LX5, UX5, LY5, UY5, LZ5, UZ5;

int blips2to3mev = 0 ; 

//int Process[2]={0, 0}; 

//Truth particle within a subrange
TH1F* hpdg_sr0; 

//Truth particles within a band for a given subrange
TH1F* hpdg_band_sr0; 

TH1F* hpdg_sr0_band;

//TH1F* hpdg = new TH1F("hpdg","truth particles",7,0,7);



// Histograms
TH2D* h_blipcharge_blipsize_pk_0;

TH2D* h_blipchargeblipsize_blipenergy_pk_0;

TH1D* h_blip_proxtrkdist_0;

TH1D* h_dx_0 ; 
TH1D* h_dyz_0 ;



TH1D* h_dEdx_15;
TH1D* h_dEdx_box_15;

TH1D* h_sr9_edep_pdg;  

TH1D* h_anatreeE;

TH1D* h_myE;

TH1D* H ; 
TH1D* L; 

TH1D* H_blip_Energy;
TH1D* H_blip_Energy_overlay;
TH1D* H_blip_Energy_mc;
TH1D* H_blip_Energy_mc_gammas;
TH1D* H_blip_Energy_mc_protons;
TH1D* H_blip_Energy_mc_eminus;
TH1D* H_blip_Energy_mc_eplus;
TH1D* H_blip_Energy_mc_otherpdg;

//Process Type
TH1D* H_blip_Energy_mc_primary;
TH1D* H_blip_Energy_mc_compton;
TH1D* H_blip_Energy_mc_photoe;
TH1D* H_blip_Energy_mc_pairprod;
TH1D* H_blip_Energy_mc_otherproc;
TH1D* H_blip_Energy_mc_nonproc;


TH2D* h_recoVsTrueE_p; //proton
TH2D* h_recoVsTrueE_blips;// blips
TH2D* h_pE_true_reco;
TH1D* h_ratio;

TH2D* h_blip_zy_pk_0;
TH2D* h_blip_zy_pk_0_mc;

TH2D* h_blip_zx_pk_0;
TH2D* h_blip_zx_pk_0_mc;

TH1D* hsr0; 

int blip0Proc = 0 ;
int blip1Proc = 0 ;


// Counters
int numEvents = 0;

int allblips = 0; 
int pickyblips = 0; 
int allblipsE = 0;
int pickyblipsE = 0;

int fractionAbove90ke = 0; 
int blipEntriesTotal = 0;
int passedBlips = 0;


int sr0_blipswithinbox = 0 ;
int sr1_blipswithinbox = 0 ;
int sr2_blipswithinbox = 0 ;
int sr3_blipswithinbox = 0 ;
int sr4_blipswithinbox = 0 ;
int sr5_blipswithinbox = 0 ;
int sr6_blipswithinbox = 0 ;
int sr7_blipswithinbox = 0 ;
int sr8_blipswithinbox = 0 ;
int sr9_blipswithinbox = 0 ;
int sr10_blipswithinbox = 0 ;
int sr11_blipswithinbox = 0 ;
int sr12_blipswithinbox = 0 ;
int sr13_blipswithinbox = 0 ;
int sr14_blipswithinbox = 0 ;
int sr15_blipswithinbox = 0 ;

int Sum90kecm = 0; 

int sr0_blips = 0 ;
int sr1_blips = 0 ;
int sr2_blips = 0 ;
int sr3_blips = 0 ;
int sr4_blips = 0 ;
int sr5_blips = 0 ;
int sr6_blips = 0 ;
int sr7_blips = 0 ;
int sr8_blips = 0 ;
int sr9_blips = 0 ;
int sr10_blips = 0 ;
int sr11_blips = 0 ;
int sr12_blips = 0 ;
int sr13_blips = 0 ;
int sr14_blips = 0 ;
int sr15_blips = 0 ;
int Sum = 0;


int auxsr0Event = -1;
int auxsr1Event = -1;
int auxsr2Event = -1;
int auxsr3Event = -1;
int auxsr4Event = -1;
int auxsr5Event = -1;
int auxsr6Event = -1;
int auxsr7Event = -1;
int auxsr8Event = -1;
int auxsr9Event = -1;
int auxsr10Event = -1;
int auxsr11Event = -1;
int auxsr12Event = -1;
int auxsr13Event = -1;
int auxsr14Event = -1;
int auxsr15Event = -1;

int EVDsr0 = 0;
int EVDsr1 = 0;
int EVDsr2 = 0;
int EVDsr3 = 0;
int EVDsr4 = 0;
int EVDsr5 = 0;
int EVDsr6 = 0;
int EVDsr7 = 0;
int EVDsr8 = 0;
int EVDsr9 = 0;
int EVDsr10 = 0;
int EVDsr11 = 0;
int EVDsr12 = 0;
int EVDsr13 = 0;
int EVDsr14 = 0;
int EVDsr15 = 0;

int sr1_fractionabove = 0; 
int sr2_fractionabove = 0;
int sr3_fractionabove = 0;
int sr4_fractionabove = 0;
int sr5_fractionabove = 0;
int sr6_fractionabove = 0;
int sr7_fractionabove = 0;
int sr8_fractionabove = 0;
int sr9_fractionabove = 0;
int sr10_fractionabove = 0;
int sr12_fractionabove = 0;

int sr0_inband_pdg2212 = 0; int sr0_inband_pdg13 = 0; int sr0_inband_pdgneg13 = 0;  int sr0_inband_pdg11 = 0; int sr0_inband_pdgneg11 = 0; int sr0_inband_pdg0 = 0; int sr0_inband_pdgother = 0; int sr0_inband_pdg22 = 0;
int sr1_inband_pdg2212 = 0; int sr1_inband_pdg13 = 0; int sr1_inband_pdgneg13 = 0;  int sr1_inband_pdg11 = 0; int sr1_inband_pdgneg11 = 0; int sr1_inband_pdg0 = 0; int sr1_inband_pdgother = 0; int sr1_inband_pdg22 = 0;
int sr2_inband_pdg2212 = 0; int sr2_inband_pdg13 = 0; int sr2_inband_pdgneg13 = 0;  int sr2_inband_pdg11 = 0; int sr2_inband_pdgneg11 = 0; int sr2_inband_pdg0 = 0; int sr2_inband_pdgother = 0; int sr2_inband_pdg22 = 0;
int sr3_inband_pdg2212 = 0; int sr3_inband_pdg13 = 0; int sr3_inband_pdgneg13 = 0;  int sr3_inband_pdg11 = 0; int sr3_inband_pdgneg11 = 0; int sr3_inband_pdg0 = 0; int sr3_inband_pdgother = 0; int sr3_inband_pdg22 = 0;
int sr4_inband_pdg2212 = 0; int sr4_inband_pdg13 = 0; int sr4_inband_pdgneg13 = 0;  int sr4_inband_pdg11 = 0; int sr4_inband_pdgneg11 = 0; int sr4_inband_pdg0 = 0; int sr4_inband_pdgother = 0; int sr4_inband_pdg22 = 0;
int sr5_inband_pdg2212 = 0; int sr5_inband_pdg13 = 0; int sr5_inband_pdgneg13 = 0;  int sr5_inband_pdg11 = 0; int sr5_inband_pdgneg11 = 0; int sr5_inband_pdg0 = 0; int sr5_inband_pdgother = 0; int sr5_inband_pdg22 = 0;
int sr6_inband_pdg2212 = 0; int sr6_inband_pdg13 = 0; int sr6_inband_pdgneg13 = 0;  int sr6_inband_pdg11 = 0; int sr6_inband_pdgneg11 = 0; int sr6_inband_pdg0 = 0; int sr6_inband_pdgother = 0; int sr6_inband_pdg22 = 0;
int sr7_inband_pdg2212 = 0; int sr7_inband_pdg13 = 0; int sr7_inband_pdgneg13 = 0;  int sr7_inband_pdg11 = 0; int sr7_inband_pdgneg11 = 0; int sr7_inband_pdg0 = 0; int sr7_inband_pdgother = 0; int sr7_inband_pdg22 = 0;
int sr8_inband_pdg2212 = 0; int sr8_inband_pdg13 = 0; int sr8_inband_pdgneg13 = 0;  int sr8_inband_pdg11 = 0; int sr8_inband_pdgneg11 = 0; int sr8_inband_pdg0 = 0; int sr8_inband_pdgother = 0; int sr8_inband_pdg22 = 0;
int sr9_inband_pdg2212 = 0; int sr9_inband_pdg13 = 0; int sr9_inband_pdgneg13 = 0;  int sr9_inband_pdg11 = 0; int sr9_inband_pdgneg11 = 0; int sr9_inband_pdg0 = 0; int sr9_inband_pdgother = 0; int sr9_inband_pdg22 = 0;
int sr10_inband_pdg2212 = 0; int sr10_inband_pdg13 = 0; int sr10_inband_pdgneg13 = 0;  int sr10_inband_pdg11 = 0; int sr10_inband_pdgneg11 = 0; int sr10_inband_pdg0 = 0; int sr10_inband_pdgother = 0; int sr10_inband_pdg22 = 0;
int sr11_inband_pdg2212 = 0; int sr11_inband_pdg13 = 0; int sr11_inband_pdgneg13 = 0;  int sr11_inband_pdg11 = 0; int sr11_inband_pdgneg11 = 0; int sr11_inband_pdg0 = 0; int sr11_inband_pdgother = 0; int sr11_inband_pdg22 = 0;
int sr12_inband_pdg2212 = 0; int sr12_inband_pdg13 = 0; int sr12_inband_pdgneg13 = 0;  int sr12_inband_pdg11 = 0; int sr12_inband_pdgneg11 = 0; int sr12_inband_pdg0 = 0; int sr12_inband_pdgother = 0; int sr12_inband_pdg22 = 0;
int sr13_inband_pdg2212 = 0; int sr13_inband_pdg13 = 0; int sr13_inband_pdgneg13 = 0;  int sr13_inband_pdg11 = 0; int sr13_inband_pdgneg11 = 0; int sr13_inband_pdg0 = 0; int sr13_inband_pdgother = 0; int sr13_inband_pdg22 = 0;
int sr14_inband_pdg2212 = 0; int sr14_inband_pdg13 = 0; int sr14_inband_pdgneg13 = 0;  int sr14_inband_pdg11 = 0; int sr14_inband_pdgneg11 = 0; int sr14_inband_pdg0 = 0; int sr14_inband_pdgother = 0; int sr14_inband_pdg22 = 0;
int sr15_inband_pdg2212 = 0; int sr15_inband_pdg13 = 0; int sr15_inband_pdgneg13 = 0;  int sr15_inband_pdg11 = 0; int sr15_inband_pdgneg11 = 0; int sr15_inband_pdg0 = 0; int sr15_inband_pdgother = 0; int sr15_inband_pdg22 = 0;




int sr0_pdg2212 = 0; int sr0_pdg13 = 0; int sr0_pdgneg13 = 0;  int sr0_pdg11 = 0; int sr0_pdgneg11 = 0; int sr0_pdg0 = 0; int sr0_pdgother = 0; int sr0_pdg22 = 0;
int sr1_pdg2212 = 0; int sr1_pdg13 = 0; int sr1_pdgneg13 = 0;  int sr1_pdg11 = 0; int sr1_pdgneg11 = 0; int sr1_pdg0 = 0; int sr1_pdgother = 0; int sr1_pdg22 = 0;
int sr2_pdg2212 = 0; int sr2_pdg13 = 0; int sr2_pdgneg13 = 0;  int sr2_pdg11 = 0; int sr2_pdgneg11 = 0; int sr2_pdg0 = 0; int sr2_pdgother = 0; int sr2_pdg22 = 0;
int sr3_pdg2212 = 0; int sr3_pdg13 = 0; int sr3_pdgneg13 = 0;  int sr3_pdg11 = 0; int sr3_pdgneg11 = 0; int sr3_pdg0 = 0; int sr3_pdgother = 0; int sr3_pdg22 = 0;
int sr4_pdg2212 = 0; int sr4_pdg13 = 0; int sr4_pdgneg13 = 0;  int sr4_pdg11 = 0; int sr4_pdgneg11 = 0; int sr4_pdg0 = 0; int sr4_pdgother = 0; int sr4_pdg22 = 0;
int sr5_pdg2212 = 0; int sr5_pdg13 = 0; int sr5_pdgneg13 = 0;  int sr5_pdg11 = 0; int sr5_pdgneg11 = 0; int sr5_pdg0 = 0; int sr5_pdgother = 0; int sr5_pdg22 = 0;
int sr6_pdg2212 = 0; int sr6_pdg13 = 0; int sr6_pdgneg13 = 0;  int sr6_pdg11 = 0; int sr6_pdgneg11 = 0; int sr6_pdg0 = 0; int sr6_pdgother = 0; int sr6_pdg22 = 0;
int sr7_pdg2212 = 0; int sr7_pdg13 = 0; int sr7_pdgneg13 = 0;  int sr7_pdg11 = 0; int sr7_pdgneg11 = 0; int sr7_pdg0 = 0; int sr7_pdgother = 0; int sr7_pdg22 = 0;
int sr8_pdg2212 = 0; int sr8_pdg13 = 0; int sr8_pdgneg13 = 0;  int sr8_pdg11 = 0; int sr8_pdgneg11 = 0; int sr8_pdg0 = 0; int sr8_pdgother = 0; int sr8_pdg22 = 0;
int sr9_pdg2212 = 0; int sr9_pdg13 = 0; int sr9_pdgneg13 = 0;  int sr9_pdg11 = 0; int sr9_pdgneg11 = 0; int sr9_pdg0 = 0; int sr9_pdgother = 0; int sr9_pdg22 = 0;
int sr10_pdg2212 = 0; int sr10_pdg13 = 0; int sr10_pdgneg13 = 0;  int sr10_pdg11 = 0; int sr10_pdgneg11 = 0; int sr10_pdg0 = 0; int sr10_pdgother = 0; int sr10_pdg22 = 0;
int sr11_pdg2212 = 0; int sr11_pdg13 = 0; int sr11_pdgneg13 = 0;  int sr11_pdg11 = 0; int sr11_pdgneg11 = 0; int sr11_pdg0 = 0; int sr11_pdgother = 0; int sr11_pdg22 = 0;
int sr12_pdg2212 = 0; int sr12_pdg13 = 0; int sr12_pdgneg13 = 0;  int sr12_pdg11 = 0; int sr12_pdgneg11 = 0; int sr12_pdg0 = 0; int sr12_pdgother = 0; int sr12_pdg22 = 0;
int sr13_pdg2212 = 0; int sr13_pdg13 = 0; int sr13_pdgneg13 = 0;  int sr13_pdg11 = 0; int sr13_pdgneg11 = 0; int sr13_pdg0 = 0; int sr13_pdgother = 0; int sr13_pdg22 = 0;
int sr14_pdg2212 = 0; int sr14_pdg13 = 0; int sr14_pdgneg13 = 0;  int sr14_pdg11 = 0; int sr14_pdgneg11 = 0; int sr14_pdg0 = 0; int sr14_pdgother = 0; int sr14_pdg22 = 0;
int sr15_pdg2212 = 0; int sr15_pdg13 = 0; int sr15_pdgneg13 = 0;  int sr15_pdg11 = 0; int sr15_pdgneg11 = 0; int sr15_pdg0 = 0; int sr15_pdgother = 0; int sr15_pdg22 = 0;











//Variables
//#################################################################################



void fillHistograms(string  inputFileName, string outputFileName, string outdir, int pdg, string label,  float shift, string DataType, string DetRegion )
{

//string folder = "txt";	
//char *dir = Form("mkdir  %s", folder.c_str() );


char *dir = Form("mkdir -p %s/%s/", outdir.c_str(), label.c_str());
system(dir);

std::string mcoverlay;

//ofstream metrics;
//ofstream metrics_clust;
ofstream metrics_blips;
ofstream graph_blips;
ofstream per_graph_blips;
ofstream graph_rr;
ofstream graph_rrsk1;
ofstream graph_rrsk2;


ofstream evd_blips;

ofstream abs_rates;
ofstream rel_rates;

ofstream eff_type1;
ofstream eff_type2;
ofstream eff_type3;

ofstream purity_type1;
ofstream purity_type2;
ofstream purity_type3;


const char *inputFileNameMetricBlips  = Form("%s/%s/summary_blip_ratios-%s.txt",outdir.c_str() ,label.c_str() , label.c_str()) ;
const char *inputFileNameGraphBlips  = Form("%s/%s/graph_blip_ratios-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameGraphBlipsPer  = Form("%s/%s/absolute_rates-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameGraphBlipsState  = Form("%s/%s/relative_rates-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameGraphBlipsStateSkip1bins  =  Form("%s/%s/relative_rates_skip1bins-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameGraphBlipsStateSkip2bins  =  Form("%s/%s/relative_rates_skip2bins-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;

const char *inputFileNameEVD  = Form("%s/%s/evd_blips_-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;

const char *inputFileNameMetricAbs  = Form("%s/%s/abs_ratios-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameMetricRel  = Form("%s/%s/rel_ratios-%s.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;

const char *inputFileNameEffType1  = Form("%s/%s/eff_vs_blipenergy-%s_protons.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameEffType2  = Form("%s/%s/eff_vs_blipenergy-%s_emineplus.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNameEffType3  = Form("%s/%s/eff_vs_blipenergy-%s_else.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;

const char *inputFileNamePurityType1  = Form("%s/%s/purity_vs_blipenergy-%s_protons.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNamePurityType2  = Form("%s/%s/purity_vs_blipenergy-%s_emineplus.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;
const char *inputFileNamePurityType3  = Form("%s/%s/purity_vs_blipenergy-%s_else.txt",outdir.c_str() ,label.c_str(), label.c_str()) ;


metrics_blips.open (inputFileNameMetricBlips,std::ofstream::in |std::ofstream::app);
graph_blips.open (inputFileNameGraphBlips,std::ofstream::in |std::ofstream::app);
per_graph_blips.open (inputFileNameGraphBlipsPer,std::ofstream::in |std::ofstream::app);
graph_rr.open (inputFileNameGraphBlipsState,std::ofstream::in |std::ofstream::app);
graph_rrsk1.open (inputFileNameGraphBlipsStateSkip1bins,std::ofstream::in |std::ofstream::app);
graph_rrsk2.open (inputFileNameGraphBlipsStateSkip2bins,std::ofstream::in |std::ofstream::app);

evd_blips.open (inputFileNameEVD,std::ofstream::in |std::ofstream::app);

abs_rates.open (inputFileNameMetricAbs,std::ofstream::in |std::ofstream::app);
rel_rates.open (inputFileNameMetricRel,std::ofstream::in |std::ofstream::app);

eff_type1.open (inputFileNameEffType1,std::ofstream::in |std::ofstream::app);
eff_type2.open (inputFileNameEffType2,std::ofstream::in |std::ofstream::app);
eff_type3.open (inputFileNameEffType3,std::ofstream::in |std::ofstream::app);

purity_type1.open (inputFileNamePurityType1,std::ofstream::in |std::ofstream::app);
purity_type2.open (inputFileNamePurityType2,std::ofstream::in |std::ofstream::app);
purity_type3.open (inputFileNamePurityType3,std::ofstream::in |std::ofstream::app);


  //*******************************************
  // Open the file and set up the TTree
  //*******************************************
  TFile* file = new TFile(inputFileName.c_str(),"READ");

  cout<<"Passed arg: "<<DataType<<endl; 
  if(DataType == "mcoverlay" )  fTree = (TTree*)file->Get("blipana/anatree");  //Overlay
  else                          fTree = (TTree*)file->Get("blipanaTrkMask/anatree");  //Full MC,  Data




  //*******************************************
  // Set the branches you plan on using; this 
  // function is in the "vars.h" file sourced 
  // at the top, along with all the variables.
  //*******************************************
  setBranches(fTree);
 
  

  //*******************************************
  // make output file to store plots
  //*******************************************
  fOutFile = new TFile(outputFileName.c_str(),"recreate");
 
  //*******************************************
  // Make histograms
  //*******************************************
  
  // hits per plane
  // 3D blip charge

  hpdg_sr0 = new TH1F("hpdg_sr0","truth matched particles in subrange",7,0,7);
 
  hpdg_band_sr0 = new TH1F("hpdg_band_sr0","band truth matched particles",7,0,7);
 

  h_blip_proxtrkdist_0 = new TH1D("proxtrkdist_sr0","sr0 blip_proxtrkdist; blip_proxtrkdist; Events", 400,0,120);

  
  // h_sr9_edep_pdg = new TH1D("edep_pdg_sr9","sr9 edep_pdg; edep_pdg; Events", 2100000000,100000,2000000);
   h_sr9_edep_pdg = new TH1D();
   h_dx_0 = new TH1D("dx_sr0","sr0 blip_dx; blip_dx; Events", 500,0,5);
   h_dyz_0 = new TH1D("dyz_sr0","sr0 blip_dyz; blip_dyz; Events", 500,0,5);

h_anatreeE = new TH1D("h_anatreeE","Eblip; E_{blip}; Events", 80, 0, 20);
h_myE = new TH1D("h_myE","myEblip; E_{blip}; Events", 200, 0, 10);


h_myE->SetBinContent(1, 102); 

h_myE->SetBinContent(45, 100);
h_myE->SetBinContent(10, 100);
h_myE->SetBinContent(20, 100);
h_myE->SetBinContent(30, 100);
h_myE->SetBinContent(40, 100);
h_myE->SetBinContent(50, 100);
h_myE->SetBinContent(60, 100);
h_myE->SetBinContent(70, 100);
h_myE->SetBinContent(80, 100);
h_myE->SetBinContent(90, 100);
h_myE->SetBinContent(100, 100);
h_myE->SetBinContent(21, 100);
h_myE->SetBinContent(56, 100);
h_myE->SetBinContent(58, 100);

H_blip_Energy = new TH1D("H_blip_Energy","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_overlay = new TH1D("H_blip_Energy_overlay","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc = new TH1D("H_blip_Energy_mc","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_gammas = new TH1D("H_blip_Energy_mc_gammas","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_protons = new TH1D("H_blip_Energy_mc_protons","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_eminus = new TH1D("H_blip_Energy_mc_eminus","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_eplus = new TH1D("H_blip_Energy_mc_eplus","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_otherpdg = new TH1D("H_blip_Energy_mc_otherpdg","E blip; E_{blip}; Events", 200, 0, 10);

H_blip_Energy_mc_primary = new TH1D("H_blip_Energy_mc_primary","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_compton = new TH1D("H_blip_Energy_mc_compton","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_photoe = new TH1D("H_blip_Energy_mc_photoe","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_pairprod = new TH1D("H_blip_Energy_mc_pairprod","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_otherproc = new TH1D("H_blip_Energy_mc_otherproc","E blip; E_{blip}; Events", 200, 0, 10);
H_blip_Energy_mc_nonproc = new TH1D("H_blip_Energy_mc_nonproc","E blip; E_{blip}; Events", 200, 0, 10);

H = new TH1D("h_HBlip","HBlip; E_{blip}; Events", 150, 0, 3);
L = new TH1D("h_LBlip","Lblip; E_{blip}; Events", 150, 0, 3);

h_ratio = new TH1D("h_ratio","ratio  ;  blip_energy[iBlip]  /  clust_charge[blip_pl2_clustid[iBlip]]    ; Ratio", 200, -10, 10);
  h_dEdx_15 = new TH1D("blip_dEdx_sr15","sr15 blip dE/dx; (dE/dx)_{blip}; Events", 60, 0, 30);
  h_dEdx_box_15 = new TH1D("blip_dEdx_box_sr15","boxsr15 blip dE/dx; (dE/dx)_{blip}; Events", 60, 0, 30);
  // YZ coordinates of 3D blips ("side view")
  float Zmin = -100;  float Zmax = 1100;  int Zbins = 240;
  float Ymin = -150;  float Ymax = 150;   int Ybins = 60;
  float Xmin = -100 ;  float Xmax = 350;   int Xbins = 90 ;


  h_blip_zy_pk_0 = new TH2D("blip_ZY_pk_sr0","3-matched-planes 3D blips;Z [cm]; Y [cm]",Zbins,Zmin,Zmax,Ybins,Ymin,Ymax);
  h_blip_zx_pk_0 = new TH2D("blip_ZX_pk_sr0","3-matched-planes 3D blips;Z [cm]; X [cm]",Zbins,Zmin,Zmax,Xbins,Xmin,Xmax);

  h_blip_zy_pk_0_mc = new TH2D("blip_ZY_pk_sr0_mc","MC 3-matched-planes 3D blips;Z [cm]; Y [cm]",Zbins,Zmin,Zmax,Ybins,Ymin,Ymax);
  h_blip_zx_pk_0_mc = new TH2D("blip_ZX_pk_sr0_mc","MC 3-matched-planes 3D blips;Z [cm]; X [cm]",Zbins,Zmin,Zmax,Xbins,Xmin,Xmax);


  h_recoVsTrueE_blips = new TH2D("h_recoVsTrueE_blips","Reco vs True E_{Blip}; True Blip Energy; Reco Blip Energy",100,0,10,100,0,10);
  h_recoVsTrueE_p = new TH2D("h_recoVsTrueE_p","Proton  Reco vs True Energy;  True Proton Energy; Reco Proton Energy",180,0,45,180,0,45);


h_blip_zy_pk_0->SetOption("colz");
h_blip_zx_pk_0->SetOption("colz");

h_blip_zy_pk_0_mc->SetOption("colz");
h_blip_zx_pk_0_mc->SetOption("colz");

// 2D Number of hits in a cluster vs charge in a cluster
float nmin = 0;  float nmax = 15;  int nbins = 15;
float chmin = 0;  float chmax = 3e5;   int chbins = 600;
float Emin = 0;  float Emax = 12;   int Ebins = 120;

h_blipcharge_blipsize_pk_0 = new TH2D("h_blipcharge_blipsize_pk_sr0","sr0 3-matched-planes Blip Size vs Blip Charge/Blip Size ; Blip Size ; Blip Charge/Blip Size", 20,0,6,chbins,chmin,chmax);


h_blipchargeblipsize_blipenergy_pk_0 = new TH2D("h_blipchargeblipsize_blipenergy_pk_sr0","sr0 3-matched-planes Blip Energy vs Blip Charge/Blip Size ; Blip Energy ; Blip Charge/Blip Size",Ebins,Emin,Emax, chbins,chmin,chmax);


 hsr0 = new TH1D("hsr0","sr0 blipsinbox; blipsinbox; Events", chbins,chmin,chmax);



//floateY1per[11] = { 81500, 87000, 88000, 90500, 92000, 93000, 96000, 98900, 98500, 100000, 72700}; 
// float  eY1per[11] = { 80800, 86800, 87500, 89800, 91800, 92000,  94000, 94000, 95000, 91200, 73500};// scm-26ms-tmfmc
//float  eY1per[11] = { 82000, 87500, 91200, 90200, 94100, 94000, 95500, 99000, 101000, 94700, 74500};// new v08_00_00_63
float  eY1per[11] = { 78300, 83500, 84000, 87200, 89900, 90700,	 92500, 94500,	95100, 95400, 69000};// new v08_00_00_63 low threshold






//float  gY1per[11] = { 86000,  94000, 100000, 103000, 104500, 109000, 113000, 117000, 120000, 121500, 71300};
//float  gY1per[11] = { 86000,   91700,   98900, 103000, 105500, 107100, 110500, 117000,  118100, 120000, 71200}; // scm-26ms-tmfmc
//float  gY1per[11] = { 85400,   91700,  99500, 107500, 108500, 108400, 114000, 118100, 118100, 119700, 71600}; // new v08_00_00_63


float  gY1per[11] = { 80800,  	88100,	96300,	98000,	99900, 	104400,	108000,	109000,	112500,	113700, 66000}; // new v08_00_00_63 low threshold





//float pY1per[11] = {124000, 137500,  149000, 153000, 158000, 162000, 168000, 171500, 173000, 174000, 102000};
//float pY1per[11] = {118500, 133200,  146200, 153900,  155500, 159800, 164500, 170500, 175000, 176500, 99000};//  scm-26ms-tmfmc
//float pY1per[11] = {118700, 133800, 146900, 154000, 156000, 161500, 166600, 171300,176000, 175200, 99100};//  new v08_00_00_63


float pY1per[11] = {113400, 125000,130500, 135000, 138600,148500, 158000, 164100, 160500, 161200, 94200};//  new v08_00_00_63 lowthreshold






// 0.1 % limits													     
float eY01per[11] =  { 100000, 98000, 105000, 108000, 111000, 112000, 117000, 115800, 116000, 108000, 87000 };										
float gY01per[11] = {106000, 114000, 109800, 121000, 126000, 131000, 131900, 141500, 138000, 144000, 86000 };
float pY01per[11] = {128300, 146500, 162700, 170000,  173000, 171000, 177000, 184000, 188000, 200000, 108300};

float Yzero[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

//pdg electrons: 11
//pdg gammas: 22
//pdg protons: 2212 

float Ybot[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
float Ytop[11] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

if(pdg == 11){//electron band 

        	for(int j=0; j<= 11 ; j++){ Ybot[j] = Yzero[j]; Ytop[j] = eY1per[j];  /*Ybot[j] = Yzero[j]; Ytop[j] = eY01per[j];*/ }

}else if(pdg ==22){//gamma band
               for(int j=0; j<= 11 ; j++){Ybot[j] = eY1per[j]; Ytop[j] = gY1per[j]; /*Ybot[j] = eY01per[j]; Ytop[j] = gY01per[j];*/}
}else{//proton band

	       for(int j=0; j<= 11 ; j++){Ybot[j] = gY1per[j]; Ytop[j] = pY1per[j]; /*Ybot[j] = gY01per[j]; Ytop[j] = pY01per[j];*/ }

}


  //*******************************************
  // Loop over events
  //*******************************************
  int totalEvents = fTree->GetEntries();     float factor =1 ; //   1/ (totalEvents) ; 
  for(int iEvent=0; iEvent < totalEvents ; iEvent++){
    
   // std::cout<<"========== EVENT "<<iEvent<<" / "<<totalEvents<<" ========================\n";
    
    // loads all variables for event 'iEvent' into memory
    fTree->GetEntry(iEvent);
    
    // keep count
    numEvents++;
 float truePEnergy = 0; 




//if(nblips > 2) {
//
 float Aux = 0 ;  float High = 0;  float Low = 0  ; 
 

     //------------------------------------------
    // Loop over the 3D reconstructed blips in 
    // this event (made by BlipAna_module).
    //------------------------------------------
   // std::cout<<"This event has "<<nblips<<" blips\n";
    for(int iBlip=0; iBlip<nblips; iBlip++){
     //cout<<"nblip"<<nblips<<endl;
    blipEntriesTotal++;

  //RecoVsTrue E  for protons
    int iedep = blip_edepid[iBlip];
     if( iedep >= 0 ) {
         if( edep_pdg[iedep] == 2212 && edep_isPrimary[iedep] ) {
             h_recoVsTrueE_p->Fill(edep_energy[iedep], blip_energy[iBlip]);
         }
     }
    float energy = blip_charge[iBlip]/0.584 * 23.6e-6 * (1+ (shift/100)); 

    //h_myE->Fill(energy);
    h_anatreeE->Fill(blip_energy[iBlip]); 

    
      // plot charge
     if (blip_pl2_clustid[iBlip] >= 0) h_ratio->Fill(blip_energy[iBlip] / clust_charge[blip_pl2_clustid[iBlip]]);  /*cout<<"Ratio: "<<blip_energy[iBlip] / clust_charge[blip_pl2_clustid[iBlip]]<<endl;  */
     float blipsize = sqrt( blip_dx[iBlip]*blip_dx[iBlip]  +  blip_dyz[iBlip]*blip_dyz[iBlip] ); 
      // plot ZY position
 

//Picky blips and additional requirements
//G10
//if( blip_nplanes[iBlip] == 3 &&  (blip_x[iBlip] > 0 ) && (blip_x[iBlip] < 270 )   &&  (blip_y[iBlip] > -115 ) && (blip_y[iBlip] < -90 )  &&  (blip_z[iBlip] > 310 ) && (blip_z[iBlip] < 370 )   && blip_proxtrkdist[iBlip] > 25  )
//All
//if( blip_nplanes[iBlip] == 3  && blip_proxtrkdist[iBlip] > 25 )
//NonG10
//if( blip_nplanes[iBlip] == 3 &&  (blip_x[iBlip] > 0 ) && (blip_x[iBlip] < 270 )   &&  (blip_y[iBlip] > -25 ) && (blip_y[iBlip] < 0 )  &&  (blip_z[iBlip] > 500 ) && (blip_z[iBlip] < 560 )  /* && blip_proxtrkdist[iBlip] > 25*/ )

     
     
if( DetRegion == "fulldet" ){    LX1 = -100 ; UX1 = 350 ;   LY1 = -150 ; UY1 = 150 ;  LZ1 = -100 ;   UZ1 = 1100;  
                                 LX2 = LX1  ; UX2 = UX1 ;   LY2 = LY1  ; UY2 = UY1 ;  LZ2 = LZ1  ;   UZ2 = UZ1 ;      LX3 = LX1  ; UX3 = UX1 ;   LY3 = LY1  ; UY3 = UY1 ;  LZ3 = LZ1  ;   UZ3 = UZ1 ;  
                                 LX4 = LX1  ; UX4 = UX1 ;   LY4 = LY1  ; UY4 = UY1 ;  LZ4 = LZ1  ;   UZ4 = UZ1 ;      LX5 = LX1  ; UX5 = UX1 ;   LY5 = LY1  ; UY5 = UY1 ;  LZ5 = LZ1  ;   UZ5 = UZ1 ; }

else if( DetRegion == "G10" ){   LX1 = 0    ; UX1 = 250;   LY1 = -116 ; UY1 = -90 ;   LZ1 =  90  ; UZ1 = 130; 
                                 LX2 = 0    ; UX2 = 250;   LY2 = -116 ; UY2 = -90 ;   LZ2 = 210  ; UZ2 = 250;         LX3 = 0   ; UX3 = 250;   LY3 = -116 ; UY3 = -90 ;   LZ3 = 320  ; UZ3 =  360;
                                 LX4 = 0    ; UX4 = 250;   LY4 = -116 ; UY4 = -90 ;   LZ4 = 440  ; UZ4 = 470;         LX5 = 0   ; UX5 = 250;   LY5 = -116 ; UY5 = -90 ;   LZ5 = 560  ; UZ5 =  600; }


else if( DetRegion == "NonG10"){ LX1 = 0    ; UX1 = 250;   LY1 = -25 ; UY1 = 0 ;   LZ1 =  90  ; UZ1 = 130;    
                                 LX2 = 0    ; UX2 = 250;   LY2 = -25 ; UY2 = 0 ;   LZ2 = 210  ; UZ2 = 250;         LX3 = 0   ; UX3 = 250;   LY3 = -25 ; UY3 = 0 ;   LZ3 = 320  ; UZ3 =  360;    
                                 LX4 = 0    ; UX4 = 250;   LY4 = -25 ; UY4 = 0 ;   LZ4 = 440  ; UZ4 = 470;         LX5 = 0   ; UX5 = 250;   LY5 = -25 ; UY5 = 0 ;   LZ5 = 560  ; UZ5 =  600;  }
else {cout<<"Specify the detector region: 'fulldet' , 'G10' , 'NonG10' "<<endl; }

if( blip_nplanes[iBlip] == 3 && 
		        (   (blip_x[iBlip] > LX1   && blip_x[iBlip] < UX1  )   &&  (blip_y[iBlip] > LY1  &&  blip_y[iBlip] < UY1 )  &&  (blip_z[iBlip] > LZ1  && blip_z[iBlip] < UZ1 ) 
		      	||  (blip_x[iBlip] > LX2   && blip_x[iBlip] < UX2  )   &&  (blip_y[iBlip] > LY2  &&  blip_y[iBlip] < UY2 )  &&  (blip_z[iBlip] > LZ2  && blip_z[iBlip] < UZ2 )  
		       	||  (blip_x[iBlip] > LX3   && blip_x[iBlip] < UX3  )   &&  (blip_y[iBlip] > LY3  &&  blip_y[iBlip] < UY3 )  &&  (blip_z[iBlip] > LZ3  && blip_z[iBlip] < UZ3 ) 
		       	||  (blip_x[iBlip] > LX4   && blip_x[iBlip] < UX4  )   &&  (blip_y[iBlip] > LY4  &&  blip_y[iBlip] < UY4 )  &&  (blip_z[iBlip] > LZ4  && blip_z[iBlip] < UZ4 )  
		       	||  (blip_x[iBlip] > LX5   && blip_x[iBlip] < UX5  )   &&  (blip_y[iBlip] > LY5  &&  blip_y[iBlip] < UY5 )  &&  (blip_z[iBlip] > LZ5  && blip_z[iBlip] < UZ5 ) ) 
	 
    	&& blip_proxtrkdist[iBlip] > 25     ) 
 {
	    passedBlips++;
	    
	   
	     //cout<<"blip_energy["<<iBlip<<"]: "<<blip_energy[iBlip]<<endl; 
	     //cout<<"blip_pl0_clustid[iBlip]: "<<blip_pl0_clustid[iBlip]<<endl;
	     //cout<<"blip_pl1_clustid[iBlip]: "<<blip_pl1_clustid[iBlip]<<endl;
	     //cout<<"blip_pl2_clustid[iBlip]: "<<blip_pl2_clustid[iBlip]<<endl;

	// plot ZY position
	     pickyblips++;
	     sr0_blips++; 

	     //Reco Vs True Eblip
	     int edep_id = blip_edepid[iBlip];
             if( edep_id >= 0 /*&& edep_pdg[edep_id] ==   11*/) {
             float trueEnergy = edep_energy[edep_id];
              
	     h_recoVsTrueE_blips->Fill(trueEnergy, blip_energy[iBlip] );
	     }

              

	       
      

             float Bcharge = clust_charge[blip_pl2_clustid[iBlip]] * (1+ (shift/100)) ; //Blip Charge Shifted 
	     float Bsize   = blip_size[iBlip];             //Blip Size
             float Benergy = blip_energy[iBlip] * (1+ (shift/100)) ; //Blip energy Shifted 
             //float Benergy = blip_charge[iBlip] * (1+ (shift/100)) ; //Blip Charge Shifted
//cout<<"In For Before iEvent: "<<iEvent<<"   nBlipis:  "<<nblips<<"   iBlip: "<<iBlip<<"    Eblip: "<<Benergy <<"         H: "<<High<<" Low: "<<Low<<"   Aux: "<<Aux<<endl;


//e+e- feature studies	     
/*	   
if(iBlip == 0 )  blip0Proc = edep_proc[blip_edepid[iBlip]] ;	     
if(iBlip == 1 )  blip1Proc = edep_proc[blip_edepid[iBlip]] ;

  if(iBlip ==1 && edep_proc[blip_edepid[iBlip]] == 4 ){
	   if(Benergy > Aux){ High = Benergy; Low = Aux;  
           if( Low > 0.0 && Low < 0.6 && blip0Proc == 4 && blip1Proc == 4 ) { H->Fill(High);L->Fill(Low);} } else { High = Aux; Low = Benergy; if(Low > 0.0 && Low < 0.6){   H->Fill(High);L->Fill(Low);}     }
    }  
   
      Aux = Benergy; 
*/
      
      //cout<<"Filling Hists  H: "<<High<<" Low: "<<Low<<"   Aux: "<<Aux<<endl;
      //H->Fill(High);
      //L->Fill(Low);
      //Aux = 0; High = 0; Low = 0;
      //cout<<"In For After iEvent: "<<iEvent<<"   nBlipis:  "<<nblips<<"   iBlip: "<<iBlip<<"    edep_proc: "<<edep_proc[blip_edepid[iBlip]]<<"    Eblip: "<<Benergy <<"         H: "<<High<<" Low: "<<Low<<"   Aux: "<<Aux<<endl;

             H_blip_Energy->Fill(energy);
	     
	     if(edep_id >= 0 ) {H_blip_Energy_mc->Fill(energy);
		     	       
		               if(      edep_pdg[blip_edepid[iBlip]] ==   22 ) H_blip_Energy_mc_gammas->Fill(energy);
			       else if( edep_pdg[blip_edepid[iBlip]] == 2212 ) H_blip_Energy_mc_protons->Fill(energy);
			       else if( edep_pdg[blip_edepid[iBlip]] == 11 ) H_blip_Energy_mc_eminus->Fill(energy);
			       else if( edep_pdg[blip_edepid[iBlip]] == -11 ) H_blip_Energy_mc_eplus->Fill(energy);
			       else  H_blip_Energy_mc_otherpdg->Fill(energy);

                               
	     }else H_blip_Energy_overlay->Fill(energy);




           if(edep_id >= 0 ) {    if(      edep_proc[blip_edepid[iBlip]] ==   0 ) H_blip_Energy_mc_primary->Fill(energy); 
                             else if(      edep_proc[blip_edepid[iBlip]] ==   1 ) H_blip_Energy_mc_compton->Fill(energy);
	                     else if(      edep_proc[blip_edepid[iBlip]] ==   2 ) H_blip_Energy_mc_photoe->Fill(energy);
			     else if(      edep_proc[blip_edepid[iBlip]] ==   3 ) H_blip_Energy_mc_pairprod->Fill(energy);
			     else if(      edep_proc[blip_edepid[iBlip]] ==   4 ) H_blip_Energy_mc_otherproc->Fill(energy);
	                       else  H_blip_Energy_mc_nonproc->Fill(energy);
	   
	   }

           if(edep_id >= 0 ){	   
           h_blip_zy_pk_0_mc->Fill( blip_z[iBlip], blip_y[iBlip] );
	   h_blip_zx_pk_0_mc->Fill( blip_z[iBlip], blip_x[iBlip] ); 	   
	   }


             h_blip_zy_pk_0->Fill( blip_z[iBlip], blip_y[iBlip] );
             h_blip_zx_pk_0->Fill( blip_z[iBlip], blip_x[iBlip] );
	     h_blipcharge_blipsize_pk_0 ->Fill( Bsize  , Bcharge / Bsize  );
             h_blipchargeblipsize_blipenergy_pk_0 ->Fill( Benergy  , Bcharge / Bsize  ); 
	     h_blip_proxtrkdist_0->Fill(blip_proxtrkdist[iBlip]);
	     h_dx_0->Fill(blip_dx[iBlip]);
	     h_dyz_0->Fill(blip_dyz[iBlip]);
	     sr0_blipswithinbox++; hsr0->Fill(Bcharge / Bsize);

	     if(energy > 2 && energy < 3 ) blips2to3mev++;




             if(auxsr0Event != iEvent) EVDsr0++; 
	     auxsr0Event = iEvent;


            //edep_pdg's in the subrange (All)
                                            if( edep_pdg[blip_edepid[iBlip]] == 2212 ) {sr0_pdg2212++;  hpdg_sr0->Fill(particle[0],1);}
                                       else if( edep_pdg[blip_edepid[iBlip]] ==   11 ) {sr0_pdg11++;    hpdg_sr0->Fill(particle[1],1);}
                                       else if( edep_pdg[blip_edepid[iBlip]] ==  -11 ) {sr0_pdgneg11++; hpdg_sr0->Fill(particle[2],1);}
                                       else if( edep_pdg[blip_edepid[iBlip]] ==    0 ) {sr0_pdg0++;     hpdg_sr0->Fill(particle[3],1);}
                                       else if( edep_pdg[blip_edepid[iBlip]] ==   13 ) {sr0_pdg13++;    hpdg_sr0->Fill(particle[4],1);}
                                       else if( edep_pdg[blip_edepid[iBlip]] ==  -13 ) {sr0_pdgneg13++; hpdg_sr0->Fill(particle[5],1);}
                                       else if( edep_pdg[blip_edepid[iBlip]] ==   22 ) {sr0_pdg22++;    hpdg_sr0->Fill(particle[6],1);}
                                                                                 else  {sr0_pdgother++; hpdg_sr0->Fill(particle[7],1);}



            









        }// <-- end loop over picky blips



    }// <-- end loop over 3D blips      
/*
cout<<"Filling Hists  H: "<<High<<" Low: "<<Low<<"   Aux: "<<Aux<<endl; 
H->Fill(High);
L->Fill(Low);
Aux = 0; High = 0; Low = 0;  
cout<<"Resetting H: "<<High<<" Low: "<<Low<<"   Aux: "<<Aux<<endl;
*/
//cout<<" %n"<<endl;
//}// <-- end if nblips==2 

}// <-- end loop over events


//TH_11* hx = h_blipchargeblipsize_blipenergy_pk->ProjectionX();
//TH_11* hy = h_blipchargeblipsize_blipenergy_pk->ProjectionY();


TH1* h_blip_Z = h_blip_zx_pk_0->ProjectionX();
TH1* h_blip_Y = h_blip_zy_pk_0->ProjectionY();
TH1* h_blip_X = h_blip_zx_pk_0->ProjectionY();

TH1* h_blip_E0 = h_blipchargeblipsize_blipenergy_pk_0->ProjectionX();

TH1* h_blip_chargebysize0 = h_blipchargeblipsize_blipenergy_pk_0->ProjectionY();


//*******************************************
  // All done!
  //*******************************************
  std::cout<<"Done processing file. Looped through "<<numEvents<<" events total.\n";
 
// TVectorD v(3); v_0 = fractionAbove90ke; v_11 = passedBlips ; v_2 = (float) fractionAbove90ke / passedBlips ;
// v.Write("Ratios");
 
 
  fOutFile->Write();
  fOutFile->Close();
 
  cout<<"input file: "<<inputFileName<<endl;
  cout<<"output file: "<<outputFileName<<endl;

 
 
  


 cout<<"===================================================================================================================================================================================================="<<endl;
cout<<"FullRange: "  << Ratio(sr0_blipswithinbox,sr0_blips)<<" ± " << RatioStatUnc(sr0_blipswithinbox,sr0_blips)<<"\t Percentage: "  << Ratio(sr0_blipswithinbox,sr0_blips) * 100<<" ± " << RatioStatUnc(sr0_blipswithinbox,sr0_blips) * 100<<" %"<<endl;
cout<<" - "<<", "<< Ratio(sr1_blipswithinbox,sr1_blips)<<" ± " << RatioStatUnc(sr1_blipswithinbox,sr1_blips)<<"\t Percentage: "  << Ratio(sr1_blipswithinbox,sr1_blips) * 100<<" ± " << RatioStatUnc(sr1_blipswithinbox,sr1_blips) * 100<<" %"<<endl;
/*
cout<<"3.0 - 3.5, Fraction Above: "<<Ratio(sr1_fractionabove,sr1_blips)<<endl; 
cout<<"3.5 - 4.0, Fraction Above: "<<Ratio(sr2_fractionabove,sr2_blips)<<endl;
cout<<"4.0 - 4.5, Fraction Above: "<<Ratio(sr3_fractionabove,sr3_blips)<<endl;
cout<<"4.5 - 5.0, Fraction Above: "<<Ratio(sr4_fractionabove,sr4_blips)<<endl;
cout<<"5.0 - 5.5, Fraction Above: "<<Ratio(sr5_fractionabove,sr5_blips)<<endl;
cout<<"5.5 - 6.0, Fraction Above: "<<Ratio(sr6_fractionabove,sr6_blips)<<endl;
cout<<"6.0 - 6.5, Fraction Above: "<<Ratio(sr7_fractionabove,sr7_blips)<<endl;
cout<<"6.5 - 7.0, Fraction Above: "<<Ratio(sr8_fractionabove,sr8_blips)<<endl;
cout<<"7.0 - 7.5, Fraction Above: "<<Ratio(sr9_fractionabove,sr9_blips)<<endl;
cout<<"7.5 - 8.0, Fraction Above: "<<Ratio(sr10_fractionabove,sr10_blips)<<endl;
*/
cout<<"===================================================================================================================================================================================================="<<endl;


cout<<setprecision(2);
cout<<"UPDATED VALUES"<<endl;
cout<<"passedBlips: "<< passedBlips<<endl; 
cout<<"totalEvents= EVD: "<<totalEvents<<endl;
cout<<"Subrange "<<"\t"<<"srn"<<"\t"<<"BlipsInBox"<<"\t\t"<<"BlipsInRange"<<"\t"<< "BlipsInBox/BlipsInRange±Er(%)" <<"\t\t"<<  "BlipsInBox/EVD±Er(%)"   <<endl;

cout<<"AllEnergies"<<"\t"<<0<<"\t"<<sr0_blipswithinbox<<"\t \t"<<sr0_blips<<"\t\t"<<setprecision(2)<< factor*Ratio(sr0_blipswithinbox,sr0_blips) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(sr0_blipswithinbox,sr0_blips)<<"\t\t"<<setprecision(2)<< factor*Ratio(sr0_blipswithinbox,totalEvents) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(sr0_blipswithinbox,totalEvents)<<endl;

cout<<"2 to 3 MeV"<<"\t"<<0<<"\t"<<blips2to3mev<<"\t"<<sr0_blips<<"\t\t"<<setprecision(2)<< factor*Ratio(blips2to3mev,sr0_blips) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(blips2to3mev,sr0_blips)<<"\t\t"<<setprecision(2)<< factor*Ratio(blips2to3mev,totalEvents) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(blips2to3mev,totalEvents)<<endl;




    const char sep     = ' ';
    const int letWidth = 6;
    const int numWidth = 8;

    
    
//============================================================================= 

metrics_blips<<"Output info of: " <<Form("summary_blip_ratios-%s.txt", label.c_str())<<endl;
metrics_blips<<"Energy shift: "<<shift <<" %"<<endl; 
metrics_blips<<"\n"<<endl;
metrics_blips<<"passedBlips: "<< passedBlips<<endl;
metrics_blips<<"totalEvents= EVD: "<<totalEvents<<endl;
metrics_blips<<"Relative Rate = [ BlipsWithinBox/BlipsInRange] ± Er"<<endl; 
metrics_blips<<"Absolute Rate = [ BlipsWithinBox/EVD]   ± Er "<<endl;

metrics_blips<<"\n"<<endl;

metrics_blips<<"Subrange "<<"\t"<<"BlipsInBox"<<"\t"<<"BlipsInRange"<<"\t"<< "Relative Rate" <<"\t\t"<<  "Absolute Rate"   <<endl;

metrics_blips<<"AllEnergies"<<"\t"<<sr0_blipswithinbox<<"\t\t"<<sr0_blips<<"\t\t"<<setprecision(2)<< factor*Ratio(sr0_blipswithinbox,sr0_blips) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(sr0_blipswithinbox,sr0_blips)<<"\t\t"<<setprecision(2)<< factor*Ratio(sr0_blipswithinbox,totalEvents) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(sr0_blipswithinbox,totalEvents)<<endl;

metrics_blips<<"2 to 3 MeV"<<"\t"<<blips2to3mev<<"\t\t"<<sr0_blips<<"\t\t"<<setprecision(2)<< factor*Ratio(blips2to3mev,sr0_blips) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(blips2to3mev,sr0_blips)<<"\t\t"<<setprecision(2)<< factor*Ratio(blips2to3mev,totalEvents) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(blips2to3mev,totalEvents)<<endl;

metrics_blips<<"\n"<<endl; 



metrics_blips<<"Subrange "<<"\t"<<"Relative Rate" <<"\t\t"<<  "Absolute Rate"   <<endl;
metrics_blips<<"AllEnergies"<<"\t"<<setprecision(2)<< factor*Ratio(sr0_blipswithinbox,sr0_blips) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(sr0_blipswithinbox,sr0_blips)<<" \t"<<setprecision(2)<< factor*Ratio(sr0_blipswithinbox,totalEvents) <<" ± "<<setprecision(2)<< factor*RatioStatUnc(sr0_blipswithinbox,totalEvents)<<endl;







//=============================================================================
//                               PDG rates
//=============================================================================

metrics_blips<<"\n"<<endl;
metrics_blips<<"Truth Info- Only MC"<<endl; 
/*
metrics_blips<<"srn"<<endl;
metrics_blips<<"sr12 - 0-3 MeV  "<<endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV   "<<endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<endl;
metrics_blips<<" "<<endl;


metrics_blips<<"Proton pdg 2212 - relative rates:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr12_inband_pdg2212,sr12_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg2212,sr12_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr1_inband_pdg2212,sr1_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg2212,sr1_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr2_inband_pdg2212,sr2_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg2212,sr2_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr3_inband_pdg2212,sr3_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg2212,sr3_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr4_inband_pdg2212,sr4_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg2212,sr4_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr5_inband_pdg2212,sr5_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg2212,sr5_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr6_inband_pdg2212,sr6_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg2212,sr6_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr7_inband_pdg2212,sr7_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg2212,sr7_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr8_inband_pdg2212,sr8_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg2212,sr8_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr9_inband_pdg2212,sr9_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg2212,sr9_pdg2212)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr10_inband_pdg2212,sr10_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg2212,sr10_pdg2212)<<endl;
metrics_blips<<" "<<endl;

metrics_blips<<"Electron pdg 11 - relative rates:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr12_inband_pdg11,sr12_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg11,sr12_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr1_inband_pdg11,sr1_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg11,sr1_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr2_inband_pdg11,sr2_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg11,sr2_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr3_inband_pdg11,sr3_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg11,sr3_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr4_inband_pdg11,sr4_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg11,sr4_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr5_inband_pdg11,sr5_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg11,sr5_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr6_inband_pdg11,sr6_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg11,sr6_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr7_inband_pdg11,sr7_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg11,sr7_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr8_inband_pdg11,sr8_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg11,sr8_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr9_inband_pdg11,sr9_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg11,sr9_pdg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr10_inband_pdg11,sr10_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg11,sr10_pdg11)<<endl;
metrics_blips<<" "<<endl;


metrics_blips<<"Positron pdg -11 - relative rates:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr12_inband_pdgneg11,sr12_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdgneg11,sr12_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr1_inband_pdgneg11,sr1_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdgneg11,sr1_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr2_inband_pdgneg11,sr2_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdgneg11,sr2_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr3_inband_pdgneg11,sr3_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdgneg11,sr3_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr4_inband_pdgneg11,sr4_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdgneg11,sr4_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr5_inband_pdgneg11,sr5_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdgneg11,sr5_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr6_inband_pdgneg11,sr6_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdgneg11,sr6_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr7_inband_pdgneg11,sr7_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdgneg11,sr7_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr8_inband_pdgneg11,sr8_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdgneg11,sr8_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr9_inband_pdgneg11,sr9_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdgneg11,sr9_pdgneg11)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr10_inband_pdgneg11,sr10_pdgneg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdgneg11,sr10_pdgneg11)<<endl;
metrics_blips<<" "<<endl;


int gamm_inband_sr12 = sr12_inband_pdg11+sr12_inband_pdgneg11; int gam_sr12 = sr12_pdg11+sr12_pdgneg11;
int gamm_inband_sr1 = sr1_inband_pdg11+sr1_inband_pdgneg11; int gam_sr1 = sr1_pdg11+sr1_pdgneg11;
int gamm_inband_sr2 = sr2_inband_pdg11+sr2_inband_pdgneg11; int gam_sr2 = sr2_pdg11+sr2_pdgneg11;
int gamm_inband_sr3 = sr3_inband_pdg11+sr3_inband_pdgneg11; int gam_sr3 = sr3_pdg11+sr3_pdgneg11;
int gamm_inband_sr4 = sr4_inband_pdg11+sr4_inband_pdgneg11; int gam_sr4 = sr4_pdg11+sr4_pdgneg11;
int gamm_inband_sr5 = sr5_inband_pdg11+sr5_inband_pdgneg11; int gam_sr5 = sr5_pdg11+sr5_pdgneg11;
int gamm_inband_sr6 = sr6_inband_pdg11+sr6_inband_pdgneg11; int gam_sr6 = sr6_pdg11+sr6_pdgneg11;
int gamm_inband_sr7 = sr7_inband_pdg11+sr7_inband_pdgneg11; int gam_sr7 = sr7_pdg11+sr7_pdgneg11;
int gamm_inband_sr8 = sr8_inband_pdg11+sr8_inband_pdgneg11; int gam_sr8 = sr8_pdg11+sr8_pdgneg11;
int gamm_inband_sr9 = sr9_inband_pdg11+sr9_inband_pdgneg11; int gam_sr9 = sr9_pdg11+sr9_pdgneg11;
int gamm_inband_sr10 = sr10_inband_pdg11+sr10_inband_pdgneg11; int gam_sr10 = sr10_pdg11+sr10_pdgneg11;

metrics_blips<<"Gammas  pdg -11 & pdg 11  - relative rates:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr12,gam_sr12)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr12,gam_sr12)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr1,gam_sr1)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr1,gam_sr1)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr2,gam_sr2)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr2,gam_sr2)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr3,gam_sr3)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr3,gam_sr3)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr4,gam_sr4)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr4,gam_sr4)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr5,gam_sr5)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr5,gam_sr5)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr6,gam_sr6)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr6,gam_sr6)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr7,gam_sr7)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr7,gam_sr7)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr8,gam_sr8)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr8,gam_sr8)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr9,gam_sr9)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr9,gam_sr9)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr10,gam_sr10)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr10,gam_sr10)<<endl;
metrics_blips<<" "<<endl;





metrics_blips<<"7-7.5 MeV    pdgs in band:"<<endl;
metrics_blips<<"sr9_inband_pdg2212: "<< sr9_inband_pdg2212 <<endl;
metrics_blips<<"sr9_inband_pdg13: "<< sr9_inband_pdg13 <<endl;
metrics_blips<<"sr9_inband_pdgneg13: "<< sr9_inband_pdgneg13 <<endl;
metrics_blips<<"sr9_inband_pdg11: "<< sr9_inband_pdg11 <<endl;
metrics_blips<<"sr9_inband_pdgneg11: "<< sr9_inband_pdgneg11 <<endl;
metrics_blips<<"sr9_inband_pdg0: "<< sr9_inband_pdg0 <<endl;
metrics_blips<<"sr9_inband_pdgother: "<< sr9_inband_pdgother <<endl;
metrics_blips<<" "<<endl;

metrics_blips<<"7 -7.5 MeV    pdgs in subrange:"<<endl;
metrics_blips<<"sr9_pdg2212 "<< sr9_pdg2212 <<endl;
metrics_blips<<"sr9_pdg13 "<< sr9_pdg13 <<endl;
metrics_blips<<"sr9_pdgneg13 "<< sr9_pdgneg13 <<endl;
metrics_blips<<"sr9_pdg11 "<< sr9_pdg11 <<endl;
metrics_blips<<"sr9_pdgneg11 "<< sr9_pdgneg11 <<endl;
metrics_blips<<"sr9_pdg0 "<< sr9_pdg0 <<endl;
metrics_blips<<"sr9_pdgother "<< sr9_pdgother <<endl;
metrics_blips<<" "<<endl;







metrics_blips<<"=============================================="<<endl;
metrics_blips<<"Proton pdg 2212 - pdg / totalBlipsinsubrange:"<<endl;
metrics_blips<<"=============================================="<<endl;

metrics_blips<<"srn"<<endl;
metrics_blips<<"sr12 - 0-3 MeV  "<<endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV   "<<endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<endl;
metrics_blips<<" "<<endl;


metrics_blips<<"Proton pdg 2212 - pdgtypeBytotalBlipsinsubrange:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr12_inband_pdg2212,sr12_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg2212,sr12_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr1_inband_pdg2212,sr1_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg2212,sr1_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr2_inband_pdg2212,sr2_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg2212,sr2_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr3_inband_pdg2212,sr3_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg2212,sr3_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr4_inband_pdg2212,sr4_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg2212,sr4_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr5_inband_pdg2212,sr5_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg2212,sr5_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr6_inband_pdg2212,sr6_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg2212,sr6_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr7_inband_pdg2212,sr7_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg2212,sr7_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr8_inband_pdg2212,sr8_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg2212,sr8_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr9_inband_pdg2212,sr9_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg2212,sr9_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr10_inband_pdg2212,sr10_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg2212,sr10_blips)<<endl;
metrics_blips<<" "<<endl;

metrics_blips<<"Electron pdg 11 - pdgtypeBytotalBlipsinsubrange:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr12_inband_pdg11,sr12_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg11,sr12_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr1_inband_pdg11,sr1_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg11,sr1_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr2_inband_pdg11,sr2_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg11,sr2_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr3_inband_pdg11,sr3_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg11,sr3_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr4_inband_pdg11,sr4_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg11,sr4_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr5_inband_pdg11,sr5_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg11,sr5_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr6_inband_pdg11,sr6_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg11,sr6_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr7_inband_pdg11,sr7_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg11,sr7_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr8_inband_pdg11,sr8_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg11,sr8_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr9_inband_pdg11,sr9_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg11,sr9_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr10_inband_pdg11,sr10_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg11,sr10_blips)<<endl;
metrics_blips<<" "<<endl;


metrics_blips<<"Positron pdg -11 - pdgtypeBytotalBlipsinsubrange:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr12_inband_pdgneg11,sr12_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdgneg11,sr12_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr1_inband_pdgneg11,sr1_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdgneg11,sr1_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr2_inband_pdgneg11,sr2_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdgneg11,sr2_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr3_inband_pdgneg11,sr3_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdgneg11,sr3_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr4_inband_pdgneg11,sr4_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdgneg11,sr4_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr5_inband_pdgneg11,sr5_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdgneg11,sr5_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr6_inband_pdgneg11,sr6_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdgneg11,sr6_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr7_inband_pdgneg11,sr7_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdgneg11,sr7_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr8_inband_pdgneg11,sr8_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdgneg11,sr8_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr9_inband_pdgneg11,sr9_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdgneg11,sr9_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(sr10_inband_pdgneg11,sr10_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdgneg11,sr10_blips)<<endl;
metrics_blips<<" "<<endl;

metrics_blips<<"Gammas  pdg -11 & pdg 11  - pdgtypeBytotalBlipsinsubrange:"<<endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr12,sr12_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr12,sr12_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr1,sr1_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr1,sr1_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr2,sr2_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr2,sr2_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr3,sr3_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr3,sr3_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr4,sr4_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr4,sr4_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr5,sr5_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr5,sr5_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr6,sr6_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr6,sr6_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr7,sr7_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr7,sr7_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr8,sr8_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr8,sr8_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr9,sr9_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr9,sr9_blips)<< endl;
metrics_blips<<setprecision(2)<< factor*Ratio(gamm_inband_sr10,sr10_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(gamm_inband_sr10,sr10_blips)<<endl;
metrics_blips<<" "<<endl;

*/


//Purity Denominators
int sr12_pdg_band_entries = sr12_inband_pdg2212 + sr12_inband_pdg13 + sr12_inband_pdgneg13 + sr12_inband_pdg11 + sr12_inband_pdgneg11 + sr12_inband_pdg0 + sr12_inband_pdgother + sr12_inband_pdg22 ;
int sr1_pdg_band_entries = sr1_inband_pdg2212 + sr1_inband_pdg13 + sr1_inband_pdgneg13 + sr1_inband_pdg11 + sr1_inband_pdgneg11 + sr1_inband_pdg0 + sr1_inband_pdgother + sr1_inband_pdg22 ;
int sr2_pdg_band_entries = sr2_inband_pdg2212 + sr2_inband_pdg13 + sr2_inband_pdgneg13 + sr2_inband_pdg11 + sr2_inband_pdgneg11 + sr2_inband_pdg0 + sr2_inband_pdgother + sr2_inband_pdg22 ;
int sr3_pdg_band_entries = sr3_inband_pdg2212 + sr3_inband_pdg13 + sr3_inband_pdgneg13 + sr3_inband_pdg11 + sr3_inband_pdgneg11 + sr3_inband_pdg0 + sr3_inband_pdgother + sr3_inband_pdg22 ;
int sr4_pdg_band_entries = sr4_inband_pdg2212 + sr4_inband_pdg13 + sr4_inband_pdgneg13 + sr4_inband_pdg11 + sr4_inband_pdgneg11 + sr4_inband_pdg0 + sr4_inband_pdgother + sr4_inband_pdg22 ;
int sr5_pdg_band_entries = sr5_inband_pdg2212 + sr5_inband_pdg13 + sr5_inband_pdgneg13 + sr5_inband_pdg11 + sr5_inband_pdgneg11 + sr5_inband_pdg0 + sr5_inband_pdgother + sr5_inband_pdg22 ;
int sr6_pdg_band_entries = sr6_inband_pdg2212 + sr6_inband_pdg13 + sr6_inband_pdgneg13 + sr6_inband_pdg11 + sr6_inband_pdgneg11 + sr6_inband_pdg0 + sr6_inband_pdgother + sr6_inband_pdg22 ;
int sr7_pdg_band_entries = sr7_inband_pdg2212 + sr7_inband_pdg13 + sr7_inband_pdgneg13 + sr7_inband_pdg11 + sr7_inband_pdgneg11 + sr7_inband_pdg0 + sr7_inband_pdgother + sr7_inband_pdg22 ;
int sr8_pdg_band_entries = sr8_inband_pdg2212 + sr8_inband_pdg13 + sr8_inband_pdgneg13 + sr8_inband_pdg11 + sr8_inband_pdgneg11 + sr8_inband_pdg0 + sr8_inband_pdgother + sr8_inband_pdg22 ;
int sr9_pdg_band_entries = sr9_inband_pdg2212 + sr9_inband_pdg13 + sr9_inband_pdgneg13 + sr9_inband_pdg11 + sr9_inband_pdgneg11 + sr9_inband_pdg0 + sr9_inband_pdgother + sr9_inband_pdg22 ;
int sr10_pdg_band_entries = sr10_inband_pdg2212 + sr10_inband_pdg13 + sr10_inband_pdgneg13 + sr10_inband_pdg11 + sr10_inband_pdgneg11 + sr10_inband_pdg0 + sr10_inband_pdgother + sr10_inband_pdg22 ;



//Other pdg Prutity Bcharge
int sr12_inband_pdgelse =sr12_inband_pdg13 + sr12_inband_pdgneg13+ sr12_inband_pdg0 + sr12_inband_pdgother + sr12_inband_pdg22 ;
int sr1_inband_pdgelse = sr1_inband_pdg13 + sr1_inband_pdgneg13 + sr1_inband_pdg0 + sr1_inband_pdgother + sr1_inband_pdg22 ;
int sr2_inband_pdgelse = sr2_inband_pdg13 + sr2_inband_pdgneg13 + sr2_inband_pdg0 + sr2_inband_pdgother + sr2_inband_pdg22 ;
int sr3_inband_pdgelse = sr3_inband_pdg13 + sr3_inband_pdgneg13 + sr3_inband_pdg0 + sr3_inband_pdgother + sr3_inband_pdg22 ;
int sr4_inband_pdgelse = sr4_inband_pdg13 + sr4_inband_pdgneg13 + sr4_inband_pdg0 + sr4_inband_pdgother + sr4_inband_pdg22 ;
int sr5_inband_pdgelse = sr5_inband_pdg13 + sr5_inband_pdgneg13 + sr5_inband_pdg0 + sr5_inband_pdgother + sr5_inband_pdg22 ;
int sr6_inband_pdgelse = sr6_inband_pdg13 + sr6_inband_pdgneg13 + sr6_inband_pdg0 + sr6_inband_pdgother + sr6_inband_pdg22 ;
int sr7_inband_pdgelse = sr7_inband_pdg13 + sr7_inband_pdgneg13 + sr7_inband_pdg0 + sr7_inband_pdgother + sr7_inband_pdg22 ;
int sr8_inband_pdgelse = sr8_inband_pdg13 + sr8_inband_pdgneg13 + sr8_inband_pdg0 + sr8_inband_pdgother + sr8_inband_pdg22 ;
int sr9_inband_pdgelse = sr9_inband_pdg13 + sr9_inband_pdgneg13 + sr9_inband_pdg0 + sr9_inband_pdgother + sr9_inband_pdg22 ;
int sr10_inband_pdgelse =sr10_inband_pdg13 + sr10_inband_pdgneg13+ sr10_inband_pdg0 + sr10_inband_pdgother + sr10_inband_pdg22 ;

//Eff elsepdg Bsize 
int sr12_pdgelse =sr12_pdg13 + sr12_pdgneg13+ sr12_pdg0 + sr12_pdgother + sr12_pdg22 ;
int sr1_pdgelse = sr1_pdg13 + sr1_pdgneg13 + sr1_pdg0 + sr1_pdgother + sr1_pdg22 ;
int sr2_pdgelse = sr2_pdg13 + sr2_pdgneg13 + sr2_pdg0 + sr2_pdgother + sr2_pdg22 ;
int sr3_pdgelse = sr3_pdg13 + sr3_pdgneg13 + sr3_pdg0 + sr3_pdgother + sr3_pdg22 ;
int sr4_pdgelse = sr4_pdg13 + sr4_pdgneg13 + sr4_pdg0 + sr4_pdgother + sr4_pdg22 ;
int sr5_pdgelse = sr5_pdg13 + sr5_pdgneg13 + sr5_pdg0 + sr5_pdgother + sr5_pdg22 ;
int sr6_pdgelse = sr6_pdg13 + sr6_pdgneg13 + sr6_pdg0 + sr6_pdgother + sr6_pdg22 ;
int sr7_pdgelse = sr7_pdg13 + sr7_pdgneg13 + sr7_pdg0 + sr7_pdgother + sr7_pdg22 ;
int sr8_pdgelse = sr8_pdg13 + sr8_pdgneg13 + sr8_pdg0 + sr8_pdgother + sr8_pdg22 ;
int sr9_pdgelse = sr9_pdg13 + sr9_pdgneg13 + sr9_pdg0 + sr9_pdgother + sr9_pdg22 ;
int sr10_pdgelse =sr10_pdg13 + sr10_pdgneg13+ sr10_pdg0 + sr10_pdgother + sr10_pdg22 ;



//Eff and Purity Bcharge for emin and eplus together
int sr12_inband_pdg_emineplus = sr12_inband_pdg11 + sr12_inband_pdgneg11 ;  
int sr1_inband_pdg_emineplus = sr1_inband_pdg11 + sr1_inband_pdgneg11 ;
int sr2_inband_pdg_emineplus = sr2_inband_pdg11 + sr2_inband_pdgneg11 ;
int sr3_inband_pdg_emineplus = sr3_inband_pdg11 + sr3_inband_pdgneg11 ;
int sr4_inband_pdg_emineplus = sr4_inband_pdg11 + sr4_inband_pdgneg11 ;
int sr5_inband_pdg_emineplus = sr5_inband_pdg11 + sr5_inband_pdgneg11 ;
int sr6_inband_pdg_emineplus = sr6_inband_pdg11 + sr6_inband_pdgneg11 ;
int sr7_inband_pdg_emineplus = sr7_inband_pdg11 + sr7_inband_pdgneg11 ;
int sr8_inband_pdg_emineplus = sr8_inband_pdg11 + sr8_inband_pdgneg11 ;
int sr9_inband_pdg_emineplus = sr9_inband_pdg11 + sr9_inband_pdgneg11 ;
int sr10_inband_pdg_emineplus = sr10_inband_pdg11 + sr10_inband_pdgneg11 ;


//Eff Bsize for emin and eplus together
int sr12_pdg_emineplus = sr12_pdg11 + sr12_pdgneg11 ;
int sr1_pdg_emineplus = sr1_pdg11 + sr1_pdgneg11 ;
int sr2_pdg_emineplus = sr2_pdg11 + sr2_pdgneg11 ;
int sr3_pdg_emineplus = sr3_pdg11 + sr3_pdgneg11 ;
int sr4_pdg_emineplus = sr4_pdg11 + sr4_pdgneg11 ;
int sr5_pdg_emineplus = sr5_pdg11 + sr5_pdgneg11 ;
int sr6_pdg_emineplus = sr6_pdg11 + sr6_pdgneg11 ;
int sr7_pdg_emineplus = sr7_pdg11 + sr7_pdgneg11 ;
int sr8_pdg_emineplus = sr8_pdg11 + sr8_pdgneg11 ;
int sr9_pdg_emineplus = sr9_pdg11 + sr9_pdgneg11 ;
int sr10_pdg_emineplus = sr10_pdg11 + sr10_pdgneg11 ;





metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"              # pdg-blips in band    "<<endl;
metrics_blips<<"pdg Eff = -------------------------- "<<endl;
metrics_blips<<"           # all_pdg-blips_in_range  "<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;
metrics_blips<<"                 # pdg(2212)-blips in band  "<<endl;
metrics_blips<<"pdg:2212 Eff = -------------------------------"<<endl;
metrics_blips<<"               # all_pdg(2212)-blips_in_range "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2)<< factor*Ratio(sr12_inband_pdg2212,sr12_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg2212,sr12_pdg2212)<< endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2)<< factor*Ratio(sr1_inband_pdg2212,sr1_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg2212,sr1_pdg2212)<< endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2)<< factor*Ratio(sr2_inband_pdg2212,sr2_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg2212,sr2_pdg2212)<< endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2)<< factor*Ratio(sr3_inband_pdg2212,sr3_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg2212,sr3_pdg2212)<< endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2)<< factor*Ratio(sr4_inband_pdg2212,sr4_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg2212,sr4_pdg2212)<< endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2)<< factor*Ratio(sr5_inband_pdg2212,sr5_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg2212,sr5_pdg2212)<< endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2)<< factor*Ratio(sr6_inband_pdg2212,sr6_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg2212,sr6_pdg2212)<< endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2)<< factor*Ratio(sr7_inband_pdg2212,sr7_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg2212,sr7_pdg2212)<< endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2)<< factor*Ratio(sr8_inband_pdg2212,sr8_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg2212,sr8_pdg2212)<< endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2)<< factor*Ratio(sr9_inband_pdg2212,sr9_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg2212,sr9_pdg2212)<< endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2)<< factor*Ratio(sr10_inband_pdg2212,sr10_pdg2212)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg2212,sr10_pdg2212)<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

eff_type1<</*"sr12- 0.0 - 3.0 MeV  "*/"1\t0\t"<<setprecision(2)<< factor*Ratio(sr12_inband_pdg2212,sr12_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg2212,sr12_pdg2212)<< endl;
eff_type1<</*"sr1 - 3.0 - 3.5 MeV  "*/"2\t0\t"<<setprecision(2)<< factor*Ratio(sr1_inband_pdg2212,sr1_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg2212,sr1_pdg2212)<< endl;
eff_type1<</*"sr2 - 3.5 - 4.0 MeV  "*/"3\t0\t"<<setprecision(2)<< factor*Ratio(sr2_inband_pdg2212,sr2_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg2212,sr2_pdg2212)<< endl;
eff_type1<</*"sr3 - 4.0 - 4.5 MeV  "*/"4\t0\t"<<setprecision(2)<< factor*Ratio(sr3_inband_pdg2212,sr3_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg2212,sr3_pdg2212)<< endl;
eff_type1<</*"sr4 - 4.5 - 5.0 MeV  "*/"5\t0\t"<<setprecision(2)<< factor*Ratio(sr4_inband_pdg2212,sr4_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg2212,sr4_pdg2212)<< endl;
eff_type1<</*"sr5 - 5.0 - 5.5 MeV  "*/"6\t0\t"<<setprecision(2)<< factor*Ratio(sr5_inband_pdg2212,sr5_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg2212,sr5_pdg2212)<< endl;
eff_type1<</*"sr6 - 5.5 - 6.0 MeV  "*/"7\t0\t"<<setprecision(2)<< factor*Ratio(sr6_inband_pdg2212,sr6_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg2212,sr6_pdg2212)<< endl;
eff_type1<</*"sr7 - 6.0 - 6.5 MeV  "*/"8\t0\t"<<setprecision(2)<< factor*Ratio(sr7_inband_pdg2212,sr7_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg2212,sr7_pdg2212)<< endl;
eff_type1<</*"sr8 - 6.5 - 7.0 MeV  "*/"9\t0\t"<<setprecision(2)<< factor*Ratio(sr8_inband_pdg2212,sr8_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg2212,sr8_pdg2212)<< endl;
eff_type1<</*"sr9 - 7.0 - 7.5 MeV  "*/"10\t0\t"<<setprecision(2)<< factor*Ratio(sr9_inband_pdg2212,sr9_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg2212,sr9_pdg2212)<< endl;
eff_type1<</*"sr10 -7.5 - 8.0 MeV  "*/"11\t0\t"<<setprecision(2)<< factor*Ratio(sr10_inband_pdg2212,sr10_pdg2212)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg2212,sr10_pdg2212)<<endl;





metrics_blips<<"                         # pdg(-11&11)-blips in band    "<<endl;
metrics_blips<<"pdg:(11 &-11) Eff = ------------------------------------"<<endl;
metrics_blips<<"                      # all_pdg(-11&11)-blips_in_range  "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;
metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2)<< factor*Ratio(sr12_inband_pdg_emineplus , sr12_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg_emineplus, sr12_pdg_emineplus)<< endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2)<< factor*Ratio(sr1_inband_pdg_emineplus , sr1_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg_emineplus , sr1_pdg_emineplus )<< endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2)<< factor*Ratio(sr2_inband_pdg_emineplus , sr2_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg_emineplus , sr2_pdg_emineplus )<< endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2)<< factor*Ratio(sr3_inband_pdg_emineplus , sr3_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg_emineplus , sr3_pdg_emineplus)<< endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2)<< factor*Ratio(sr4_inband_pdg_emineplus , sr4_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg_emineplus , sr4_pdg_emineplus)<< endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2)<< factor*Ratio(sr5_inband_pdg_emineplus , sr5_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg_emineplus , sr5_pdg_emineplus)<< endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2)<< factor*Ratio(sr6_inband_pdg_emineplus , sr6_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg_emineplus , sr6_pdg_emineplus)<< endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2)<< factor*Ratio(sr7_inband_pdg_emineplus , sr7_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg_emineplus , sr7_pdg_emineplus)<< endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2)<< factor*Ratio(sr8_inband_pdg_emineplus , sr8_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg_emineplus , sr8_pdg_emineplus)<< endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2)<< factor*Ratio(sr9_inband_pdg_emineplus , sr9_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg_emineplus , sr9_pdg_emineplus)<< endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2)<< factor*Ratio(sr10_inband_pdg_emineplus ,sr10_pdg_emineplus)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg_emineplus,sr10_pdg_emineplus)<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

eff_type2<</*"sr12- 0.0 - 3.0 MeV  "*/"1\t0\t"<<setprecision(2)<< factor*Ratio(sr12_inband_pdg_emineplus , sr12_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg_emineplus, sr12_pdg_emineplus)<< endl;
eff_type2<</*"sr1 - 3.0 - 3.5 MeV  "*/"2\t0\t"<<setprecision(2)<< factor*Ratio(sr1_inband_pdg_emineplus , sr1_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg_emineplus , sr1_pdg_emineplus )<< endl;
eff_type2<</*"sr2 - 3.5 - 4.0 MeV  "*/"3\t0\t"<<setprecision(2)<< factor*Ratio(sr2_inband_pdg_emineplus , sr2_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg_emineplus , sr2_pdg_emineplus )<< endl;
eff_type2<</*"sr3 - 4.0 - 4.5 MeV  "*/"4\t0\t"<<setprecision(2)<< factor*Ratio(sr3_inband_pdg_emineplus , sr3_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg_emineplus , sr3_pdg_emineplus)<< endl;
eff_type2<</*"sr4 - 4.5 - 5.0 MeV  "*/"5\t0\t"<<setprecision(2)<< factor*Ratio(sr4_inband_pdg_emineplus , sr4_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg_emineplus , sr4_pdg_emineplus)<< endl;
eff_type2<</*"sr5 - 5.0 - 5.5 MeV  "*/"6\t0\t"<<setprecision(2)<< factor*Ratio(sr5_inband_pdg_emineplus , sr5_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg_emineplus , sr5_pdg_emineplus)<< endl;
eff_type2<</*"sr6 - 5.5 - 6.0 MeV  "*/"7\t0\t"<<setprecision(2)<< factor*Ratio(sr6_inband_pdg_emineplus , sr6_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg_emineplus , sr6_pdg_emineplus)<< endl;
eff_type2<</*"sr7 - 6.0 - 6.5 MeV  "*/"8\t0\t"<<setprecision(2)<< factor*Ratio(sr7_inband_pdg_emineplus , sr7_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg_emineplus , sr7_pdg_emineplus)<< endl;
eff_type2<</*"sr8 - 6.5 - 7.0 MeV  "*/"9\t0\t"<<setprecision(2)<< factor*Ratio(sr8_inband_pdg_emineplus , sr8_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg_emineplus , sr8_pdg_emineplus)<< endl;
eff_type2<</*"sr9 - 7.0 - 7.5 MeV  "*/"10\t0\t"<<setprecision(2)<< factor*Ratio(sr9_inband_pdg_emineplus , sr9_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg_emineplus , sr9_pdg_emineplus)<< endl;
eff_type2<</*"sr10 -7.5 - 8.0 MeV  "*/"11\t0\t"<<setprecision(2)<< factor*Ratio(sr10_inband_pdg_emineplus ,sr10_pdg_emineplus)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg_emineplus,sr10_pdg_emineplus)<<endl;




metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;
metrics_blips<<"                    # pdg(else)-blips in band    "<<endl;
metrics_blips<<"pdg:else Eff = ----------------------------------"<<endl;
metrics_blips<<"                 # all_pdg(else)-blips_in_range  "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2)<< factor*Ratio(sr12_inband_pdgelse,sr12_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdgelse,sr12_pdgelse)<< endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2)<< factor*Ratio(sr1_inband_pdgelse,sr1_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdgelse,sr1_pdgelse)<< endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2)<< factor*Ratio(sr2_inband_pdgelse,sr2_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdgelse,sr2_pdgelse)<< endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2)<< factor*Ratio(sr3_inband_pdgelse,sr3_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdgelse,sr3_pdgelse)<< endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2)<< factor*Ratio(sr4_inband_pdgelse,sr4_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdgelse,sr4_pdgelse)<< endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2)<< factor*Ratio(sr5_inband_pdgelse,sr5_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdgelse,sr5_pdgelse)<< endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2)<< factor*Ratio(sr6_inband_pdgelse,sr6_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdgelse,sr6_pdgelse)<< endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2)<< factor*Ratio(sr7_inband_pdgelse,sr7_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdgelse,sr7_pdgelse)<< endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2)<< factor*Ratio(sr8_inband_pdgelse,sr8_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdgelse,sr8_pdgelse)<< endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2)<< factor*Ratio(sr9_inband_pdgelse,sr9_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdgelse,sr9_pdgelse)<< endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2)<< factor*Ratio(sr10_inband_pdgelse,sr10_pdgelse)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdgelse,sr10_pdgelse)<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

eff_type3<</*"sr12- 0.0 - 3.0 MeV  "*/"1\t0\t"<<setprecision(2)<< factor*Ratio(sr12_inband_pdgelse,sr12_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdgelse,sr12_pdgelse)<< endl;
eff_type3<</*"sr1 - 3.0 - 3.5 MeV  "*/"2\t0\t"<<setprecision(2)<< factor*Ratio(sr1_inband_pdgelse,sr1_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdgelse,sr1_pdgelse)<< endl;
eff_type3<</*"sr2 - 3.5 - 4.0 MeV  "*/"3\t0\t"<<setprecision(2)<< factor*Ratio(sr2_inband_pdgelse,sr2_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdgelse,sr2_pdgelse)<< endl;
eff_type3<</*"sr3 - 4.0 - 4.5 MeV  "*/"4\t0\t"<<setprecision(2)<< factor*Ratio(sr3_inband_pdgelse,sr3_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdgelse,sr3_pdgelse)<< endl;
eff_type3<</*"sr4 - 4.5 - 5.0 MeV  "*/"5\t0\t"<<setprecision(2)<< factor*Ratio(sr4_inband_pdgelse,sr4_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdgelse,sr4_pdgelse)<< endl;
eff_type3<</*"sr5 - 5.0 - 5.5 MeV  "*/"6\t0\t"<<setprecision(2)<< factor*Ratio(sr5_inband_pdgelse,sr5_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdgelse,sr5_pdgelse)<< endl;
eff_type3<</*"sr6 - 5.5 - 6.0 MeV  "*/"7\t0\t"<<setprecision(2)<< factor*Ratio(sr6_inband_pdgelse,sr6_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdgelse,sr6_pdgelse)<< endl;
eff_type3<</*"sr7 - 6.0 - 6.5 MeV  "*/"8\t0\t"<<setprecision(2)<< factor*Ratio(sr7_inband_pdgelse,sr7_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdgelse,sr7_pdgelse)<< endl;
eff_type3<</*"sr8 - 6.5 - 7.0 MeV  "*/"9\t0\t"<<setprecision(2)<< factor*Ratio(sr8_inband_pdgelse,sr8_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdgelse,sr8_pdgelse)<< endl;
eff_type3<</*"sr9 - 7.0 - 7.5 MeV  "*/"10\t0\t"<<setprecision(2)<< factor*Ratio(sr9_inband_pdgelse,sr9_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdgelse,sr9_pdgelse)<< endl;
eff_type3<</*"sr10 -7.5 - 8.0 MeV  "*/"11\t0\t"<<setprecision(2)<< factor*Ratio(sr10_inband_pdgelse,sr10_pdgelse)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdgelse,sr10_pdgelse)<<endl;





/* //Only electrons
metrics_blips<<"                  # pdg(11) in band      "<<endl;
metrics_blips<<"pdg:11 Eff =-----------------------------"<<endl;
metrics_blips<<"               # all_pdg(11)_in_range "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;
metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2)<< factor*Ratio(sr12_inband_pdg11,sr12_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_inband_pdg11,sr12_pdg11)<< endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2)<< factor*Ratio(sr1_inband_pdg11,sr1_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_inband_pdg11,sr1_pdg11)<< endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2)<< factor*Ratio(sr2_inband_pdg11,sr2_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_inband_pdg11,sr2_pdg11)<< endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2)<< factor*Ratio(sr3_inband_pdg11,sr3_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_inband_pdg11,sr3_pdg11)<< endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2)<< factor*Ratio(sr4_inband_pdg11,sr4_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_inband_pdg11,sr4_pdg11)<< endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2)<< factor*Ratio(sr5_inband_pdg11,sr5_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_inband_pdg11,sr5_pdg11)<< endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2)<< factor*Ratio(sr6_inband_pdg11,sr6_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_inband_pdg11,sr6_pdg11)<< endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2)<< factor*Ratio(sr7_inband_pdg11,sr7_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_inband_pdg11,sr7_pdg11)<< endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2)<< factor*Ratio(sr8_inband_pdg11,sr8_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_inband_pdg11,sr8_pdg11)<< endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2)<< factor*Ratio(sr9_inband_pdg11,sr9_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_inband_pdg11,sr9_pdg11)<< endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2)<< factor*Ratio(sr10_inband_pdg11,sr10_pdg11)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_inband_pdg11,sr10_pdg11)<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;
*/





metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"               # pdg-blips in band          "<<endl;
metrics_blips<<"pdg Purity = ------------------------------"<<endl; 
metrics_blips<<"             # all_blips_in_band "<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;
/*
int sr12_pdg_band_entries = hpdg_band_sr12->GetEntries();
int sr1_pdg_band_entries = hpdg_band_sr1->GetEntries();
int sr2_pdg_band_entries = hpdg_band_sr2->GetEntries();
int sr3_pdg_band_entries = hpdg_band_sr3->GetEntries();
int sr4_pdg_band_entries = hpdg_band_sr4->GetEntries();
int sr5_pdg_band_entries = hpdg_band_sr5->GetEntries();
int sr6_pdg_band_entries = hpdg_band_sr6->GetEntries();
int sr7_pdg_band_entries = hpdg_band_sr7->GetEntries();
int sr8_pdg_band_entries = hpdg_band_sr8->GetEntries();
int sr9_pdg_band_entries = hpdg_band_sr9->GetEntries();
int sr10_pdg_band_entries = hpdg_band_sr10->GetEntries();
*/
metrics_blips<<"                   # pdg(2212)-blips in band "<<endl;
metrics_blips<<"pdg:2212 Purity = ---------------------------"<<endl;
metrics_blips<<"                     # all_blips_in_band     "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

metrics_blips<<"srn"<<endl;
metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2) <<Ratio(sr12_inband_pdg2212, sr12_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr12_inband_pdg2212, sr12_pdg_band_entries) <<endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2) <<Ratio(sr1_inband_pdg2212, sr1_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr1_inband_pdg2212, sr1_pdg_band_entries) <<endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2) <<Ratio(sr2_inband_pdg2212, sr2_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr2_inband_pdg2212, sr2_pdg_band_entries)<<endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2) <<Ratio(sr3_inband_pdg2212, sr3_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr3_inband_pdg2212, sr3_pdg_band_entries)<<endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2) <<Ratio(sr4_inband_pdg2212, sr4_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr4_inband_pdg2212, sr4_pdg_band_entries)<<endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2) <<Ratio(sr5_inband_pdg2212, sr5_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr5_inband_pdg2212, sr5_pdg_band_entries)<<endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2) <<Ratio(sr6_inband_pdg2212, sr6_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr6_inband_pdg2212, sr6_pdg_band_entries)<<endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2) <<Ratio(sr7_inband_pdg2212, sr7_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr7_inband_pdg2212, sr7_pdg_band_entries)<<endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2) <<Ratio(sr8_inband_pdg2212, sr8_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr8_inband_pdg2212, sr8_pdg_band_entries)<<endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2) <<Ratio(sr9_inband_pdg2212, sr9_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr9_inband_pdg2212, sr9_pdg_band_entries)<<endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2) <<Ratio(sr10_inband_pdg2212, sr10_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr10_inband_pdg2212, sr10_pdg_band_entries)<<endl;
metrics_blips<<" "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

purity_type1<</*"sr12- 0.0 - 3.0 MeV  "*/"1\t0\t"<<setprecision(2) <<Ratio(sr12_inband_pdg2212, sr12_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr12_inband_pdg2212, sr12_pdg_band_entries) <<endl;
purity_type1<</*"sr1 - 3.0 - 3.5 MeV  "*/"2\t0\t"<<setprecision(2) <<Ratio(sr1_inband_pdg2212, sr1_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr1_inband_pdg2212, sr1_pdg_band_entries) <<endl;
purity_type1<</*"sr2 - 3.5 - 4.0 MeV  "*/"3\t0\t"<<setprecision(2) <<Ratio(sr2_inband_pdg2212, sr2_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr2_inband_pdg2212, sr2_pdg_band_entries)<<endl;
purity_type1<</*"sr3 - 4.0 - 4.5 MeV  "*/"4\t0\t"<<setprecision(2) <<Ratio(sr3_inband_pdg2212, sr3_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr3_inband_pdg2212, sr3_pdg_band_entries)<<endl;
purity_type1<</*"sr4 - 4.5 - 5.0 MeV  "*/"5\t0\t"<<setprecision(2) <<Ratio(sr4_inband_pdg2212, sr4_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr4_inband_pdg2212, sr4_pdg_band_entries)<<endl;
purity_type1<</*"sr5 - 5.0 - 5.5 MeV  "*/"6\t0\t"<<setprecision(2) <<Ratio(sr5_inband_pdg2212, sr5_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr5_inband_pdg2212, sr5_pdg_band_entries)<<endl;
purity_type1<</*"sr6 - 5.5 - 6.0 MeV  "*/"7\t0\t"<<setprecision(2) <<Ratio(sr6_inband_pdg2212, sr6_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr6_inband_pdg2212, sr6_pdg_band_entries)<<endl;
purity_type1<</*"sr7 - 6.0 - 6.5 MeV  "*/"8\t0\t"<<setprecision(2) <<Ratio(sr7_inband_pdg2212, sr7_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr7_inband_pdg2212, sr7_pdg_band_entries)<<endl;
purity_type1<</*"sr8 - 6.5 - 7.0 MeV  "*/"9\t0\t"<<setprecision(2) <<Ratio(sr8_inband_pdg2212, sr8_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr8_inband_pdg2212, sr8_pdg_band_entries)<<endl;
purity_type1<</*"sr9 - 7.0 - 7.5 MeV  "*/"10\t0\t"<<setprecision(2) <<Ratio(sr9_inband_pdg2212, sr9_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr9_inband_pdg2212, sr9_pdg_band_entries)<<endl;
purity_type1<</*"sr10 -7.5 - 8.0 MeV  "*/"11\t0\t"<<setprecision(2) <<Ratio(sr10_inband_pdg2212, sr10_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr10_inband_pdg2212, sr10_pdg_band_entries)<<endl;


metrics_blips<<"                        # pdg(-11&11)-blips in band  "<<endl;
metrics_blips<<"pdg:(-11&11) Purity = -------------------------------"<<endl;
metrics_blips<<"                             # all_blips_in_band     "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

metrics_blips<<"srn"<<endl;
metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2) <<Ratio(sr12_inband_pdg_emineplus, sr12_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr12_inband_pdg_emineplus, sr12_pdg_band_entries) <<endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2) <<Ratio(sr1_inband_pdg_emineplus, sr1_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr1_inband_pdg_emineplus, sr1_pdg_band_entries) <<endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2) <<Ratio(sr2_inband_pdg_emineplus, sr2_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr2_inband_pdg_emineplus, sr2_pdg_band_entries)<<endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2) <<Ratio(sr3_inband_pdg_emineplus, sr3_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr3_inband_pdg_emineplus, sr3_pdg_band_entries)<<endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2) <<Ratio(sr4_inband_pdg_emineplus, sr4_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr4_inband_pdg_emineplus, sr4_pdg_band_entries)<<endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2) <<Ratio(sr5_inband_pdg_emineplus, sr5_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr5_inband_pdg_emineplus, sr5_pdg_band_entries)<<endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2) <<Ratio(sr6_inband_pdg_emineplus, sr6_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr6_inband_pdg_emineplus, sr6_pdg_band_entries)<<endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2) <<Ratio(sr7_inband_pdg_emineplus, sr7_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr7_inband_pdg_emineplus, sr7_pdg_band_entries)<<endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2) <<Ratio(sr8_inband_pdg_emineplus, sr8_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr8_inband_pdg_emineplus, sr8_pdg_band_entries)<<endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2) <<Ratio(sr9_inband_pdg_emineplus, sr9_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr9_inband_pdg_emineplus, sr9_pdg_band_entries)<<endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2) <<Ratio(sr10_inband_pdg_emineplus, sr10_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr10_inband_pdg_emineplus, sr10_pdg_band_entries)<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

purity_type2<</*"sr12- 0.0 - 3.0 MeV  "*/"1\t0\t"<<setprecision(2) <<Ratio(sr12_inband_pdg_emineplus, sr12_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr12_inband_pdg_emineplus, sr12_pdg_band_entries) <<endl;
purity_type2<</*"sr1 - 3.0 - 3.5 MeV  "*/"2\t0\t"<<setprecision(2) <<Ratio(sr1_inband_pdg_emineplus, sr1_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr1_inband_pdg_emineplus, sr1_pdg_band_entries) <<endl;
purity_type2<</*"sr2 - 3.5 - 4.0 MeV  "*/"3\t0\t"<<setprecision(2) <<Ratio(sr2_inband_pdg_emineplus, sr2_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr2_inband_pdg_emineplus, sr2_pdg_band_entries)<<endl;
purity_type2<</*"sr3 - 4.0 - 4.5 MeV  "*/"4\t0\t"<<setprecision(2) <<Ratio(sr3_inband_pdg_emineplus, sr3_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr3_inband_pdg_emineplus, sr3_pdg_band_entries)<<endl;
purity_type2<</*"sr4 - 4.5 - 5.0 MeV  "*/"5\t0\t"<<setprecision(2) <<Ratio(sr4_inband_pdg_emineplus, sr4_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr4_inband_pdg_emineplus, sr4_pdg_band_entries)<<endl;
purity_type2<</*"sr5 - 5.0 - 5.5 MeV  "*/"6\t0\t"<<setprecision(2) <<Ratio(sr5_inband_pdg_emineplus, sr5_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr5_inband_pdg_emineplus, sr5_pdg_band_entries)<<endl;
purity_type2<</*"sr6 - 5.5 - 6.0 MeV  "*/"7\t0\t"<<setprecision(2) <<Ratio(sr6_inband_pdg_emineplus, sr6_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr6_inband_pdg_emineplus, sr6_pdg_band_entries)<<endl;
purity_type2<</*"sr7 - 6.0 - 6.5 MeV  "*/"8\t0\t"<<setprecision(2) <<Ratio(sr7_inband_pdg_emineplus, sr7_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr7_inband_pdg_emineplus, sr7_pdg_band_entries)<<endl;
purity_type2<</*"sr8 - 6.5 - 7.0 MeV  "*/"9\t0\t"<<setprecision(2) <<Ratio(sr8_inband_pdg_emineplus, sr8_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr8_inband_pdg_emineplus, sr8_pdg_band_entries)<<endl;
purity_type2<</*"sr9 - 7.0 - 7.5 MeV  "*/"10\t0\t"<<setprecision(2) <<Ratio(sr9_inband_pdg_emineplus, sr9_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr9_inband_pdg_emineplus, sr9_pdg_band_entries)<<endl;
purity_type2<</*"sr10 -7.5 - 8.0 MeV  "*/"11\t0\t"<<setprecision(2) <<Ratio(sr10_inband_pdg_emineplus, sr10_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr10_inband_pdg_emineplus, sr10_pdg_band_entries)<<endl;





metrics_blips<<"                       # pdg(else)-blips in band   "<<endl;
metrics_blips<<"pdg:(else) Purity = --------------------------------"<<endl;
metrics_blips<<"                         # all_blips_in_band        "<<endl;
metrics_blips<<" "<<endl;

metrics_blips<<"srn"<<endl;
metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2) <<Ratio(sr12_inband_pdgelse, sr12_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr12_inband_pdgelse , sr12_pdg_band_entries) <<endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2) <<Ratio(sr1_inband_pdgelse, sr1_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr1_inband_pdgelse, sr1_pdg_band_entries) <<endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2) <<Ratio(sr2_inband_pdgelse, sr2_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr2_inband_pdgelse, sr2_pdg_band_entries)<<endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2) <<Ratio(sr3_inband_pdgelse, sr3_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr3_inband_pdgelse, sr3_pdg_band_entries)<<endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2) <<Ratio(sr4_inband_pdgelse, sr4_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr4_inband_pdgelse, sr4_pdg_band_entries)<<endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2) <<Ratio(sr5_inband_pdgelse, sr5_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr5_inband_pdgelse, sr5_pdg_band_entries)<<endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2) <<Ratio(sr6_inband_pdgelse, sr6_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr6_inband_pdgelse, sr6_pdg_band_entries)<<endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2) <<Ratio(sr7_inband_pdgelse, sr7_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr7_inband_pdgelse, sr7_pdg_band_entries)<<endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2) <<Ratio(sr8_inband_pdgelse, sr8_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr8_inband_pdgelse, sr8_pdg_band_entries)<<endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2) <<Ratio(sr9_inband_pdgelse, sr9_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr9_inband_pdgelse, sr9_pdg_band_entries)<<endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2) <<Ratio(sr10_inband_pdgelse, sr10_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr10_inband_pdgelse, sr10_pdg_band_entries)<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

purity_type3<</*"sr12- 0.0 - 3.0 MeV  "*/"1\t0\t"<<setprecision(2) <<Ratio(sr12_inband_pdgelse, sr12_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr12_inband_pdgelse , sr12_pdg_band_entries) <<endl;
purity_type3<</*"sr1 - 3.0 - 3.5 MeV  "*/"2\t0\t"<<setprecision(2) <<Ratio(sr1_inband_pdgelse, sr1_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr1_inband_pdgelse, sr1_pdg_band_entries) <<endl;
purity_type3<</*"sr2 - 3.5 - 4.0 MeV  "*/"3\t0\t"<<setprecision(2) <<Ratio(sr2_inband_pdgelse, sr2_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr2_inband_pdgelse, sr2_pdg_band_entries)<<endl;
purity_type3<</*"sr3 - 4.0 - 4.5 MeV  "*/"4\t0\t"<<setprecision(2) <<Ratio(sr3_inband_pdgelse, sr3_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr3_inband_pdgelse, sr3_pdg_band_entries)<<endl;
purity_type3<</*"sr4 - 4.5 - 5.0 MeV  "*/"5\t0\t"<<setprecision(2) <<Ratio(sr4_inband_pdgelse, sr4_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr4_inband_pdgelse, sr4_pdg_band_entries)<<endl;
purity_type3<</*"sr5 - 5.0 - 5.5 MeV  "*/"6\t0\t"<<setprecision(2) <<Ratio(sr5_inband_pdgelse, sr5_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr5_inband_pdgelse, sr5_pdg_band_entries)<<endl;
purity_type3<</*"sr6 - 5.5 - 6.0 MeV  "*/"7\t0\t"<<setprecision(2) <<Ratio(sr6_inband_pdgelse, sr6_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr6_inband_pdgelse, sr6_pdg_band_entries)<<endl;
purity_type3<</*"sr7 - 6.0 - 6.5 MeV  "*/"8\t0\t"<<setprecision(2) <<Ratio(sr7_inband_pdgelse, sr7_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr7_inband_pdgelse, sr7_pdg_band_entries)<<endl;
purity_type3<</*"sr8 - 6.5 - 7.0 MeV  "*/"9\t0\t"<<setprecision(2) <<Ratio(sr8_inband_pdgelse, sr8_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr8_inband_pdgelse, sr8_pdg_band_entries)<<endl;
purity_type3<</*"sr9 - 7.0 - 7.5 MeV  "*/"10\t0\t"<<setprecision(2) <<Ratio(sr9_inband_pdgelse, sr9_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr9_inband_pdgelse, sr9_pdg_band_entries)<<endl;
purity_type3<</*"sr10 -7.5 - 8.0 MeV  "*/"11\t0\t"<<setprecision(2) <<Ratio(sr10_inband_pdgelse, sr10_pdg_band_entries)<<"\t" << setprecision(2)<<RatioStatUnc(sr10_inband_pdgelse, sr10_pdg_band_entries)<<endl;




/* //Only electrons
metrics_blips<<"                      # pdg(11) in band          "<<endl;
metrics_blips<<"pdg:11 Purity = ------------------------"<<endl;
metrics_blips<<"             # all_blips_in_band "<<endl;
metrics_blips<<" "<<endl;metrics_blips<<" "<<endl;

metrics_blips<<"srn"<<endl;
metrics_blips<<"sr12- 0.0 - 3.0 MeV  "<<setprecision(2) <<Ratio(sr12_inband_pdg11, sr12_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr12_inband_pdg11, sr12_pdg_band_entries) <<endl;
metrics_blips<<"sr1 - 3.0 - 3.5 MeV  "<<setprecision(2) <<Ratio(sr1_inband_pdg11, sr1_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr1_inband_pdg11, sr1_pdg_band_entries) <<endl;
metrics_blips<<"sr2 - 3.5 - 4.0 MeV  "<<setprecision(2) <<Ratio(sr2_inband_pdg11, sr2_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr2_inband_pdg11, sr2_pdg_band_entries)<<endl;
metrics_blips<<"sr3 - 4.0 - 4.5 MeV  "<<setprecision(2) <<Ratio(sr3_inband_pdg11, sr3_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr3_inband_pdg11, sr3_pdg_band_entries)<<endl;
metrics_blips<<"sr4 - 4.5 - 5.0 MeV  "<<setprecision(2) <<Ratio(sr4_inband_pdg11, sr4_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr4_inband_pdg11, sr4_pdg_band_entries)<<endl;
metrics_blips<<"sr5 - 5.0 - 5.5 MeV  "<<setprecision(2) <<Ratio(sr5_inband_pdg11, sr5_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr5_inband_pdg11, sr5_pdg_band_entries)<<endl;
metrics_blips<<"sr6 - 5.5 - 6.0 MeV  "<<setprecision(2) <<Ratio(sr6_inband_pdg11, sr6_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr6_inband_pdg11, sr6_pdg_band_entries)<<endl;
metrics_blips<<"sr7 - 6.0 - 6.5 MeV  "<<setprecision(2) <<Ratio(sr7_inband_pdg11, sr7_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr7_inband_pdg11, sr7_pdg_band_entries)<<endl;
metrics_blips<<"sr8 - 6.5 - 7.0 MeV  "<<setprecision(2) <<Ratio(sr8_inband_pdg11, sr8_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr8_inband_pdg11, sr8_pdg_band_entries)<<endl;
metrics_blips<<"sr9 - 7.0 - 7.5 MeV  "<<setprecision(2) <<Ratio(sr9_inband_pdg11, sr9_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr9_inband_pdg11, sr9_pdg_band_entries)<<endl;
metrics_blips<<"sr10 -7.5 - 8.0 MeV  "<<setprecision(2) <<Ratio(sr10_inband_pdg11, sr10_pdg_band_entries)<<" ± " << setprecision(2)<<RatioStatUnc(sr10_inband_pdg11, sr10_pdg_band_entries)<<endl;
metrics_blips<<" "<<endl;
*/ 


metrics_blips<<"==================================================================================="<<endl;
metrics_blips<<"==================================================================================="<<endl;







//==============================================================================
//==           Printing into files for plotting                               ==
//==============================================================================

rel_rates<<"relative rates:"<<endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr12_blipswithinbox,sr12_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_blipswithinbox,sr12_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr1_blipswithinbox,sr1_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_blipswithinbox,sr1_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr2_blipswithinbox,sr2_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,sr2_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr3_blipswithinbox,sr3_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,sr3_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr4_blipswithinbox,sr4_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,sr4_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr5_blipswithinbox,sr5_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,sr5_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr6_blipswithinbox,sr6_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,sr6_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr7_blipswithinbox,sr7_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,sr7_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr8_blipswithinbox,sr8_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,sr8_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr9_blipswithinbox,sr9_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,sr9_blips)<< endl;
rel_rates<<setprecision(2)<< factor*Ratio(sr10_blipswithinbox,sr10_blips)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,sr10_blips)<<endl;

rel_rates<<" "<<endl; rel_rates<<" "<<endl; rel_rates<<" "<<endl; 
rel_rates<<"Set histograms"<<endl;
rel_rates<<"h->SetBinContent(1,"<<setprecision(2)<< factor*Ratio(sr12_blipswithinbox,sr12_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(2,"<<setprecision(2)<< factor*Ratio(sr1_blipswithinbox,sr1_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(3,"<<setprecision(2)<< factor*Ratio(sr2_blipswithinbox,sr2_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(4,"<<setprecision(2)<< factor*Ratio(sr3_blipswithinbox,sr3_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(5,"<<setprecision(2)<< factor*Ratio(sr4_blipswithinbox,sr4_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(6,"<<setprecision(2)<< factor*Ratio(sr5_blipswithinbox,sr5_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(7,"<<setprecision(2)<< factor*Ratio(sr6_blipswithinbox,sr6_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(8,"<<setprecision(2)<< factor*Ratio(sr7_blipswithinbox,sr7_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(9,"<<setprecision(2)<< factor*Ratio(sr8_blipswithinbox,sr8_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(10,"<<setprecision(2)<< factor*Ratio(sr9_blipswithinbox,sr9_blips)<<");"<<endl;
rel_rates<<"h->SetBinContent(11,"<<setprecision(2)<< factor*Ratio(sr10_blipswithinbox,sr10_blips)<<");"<<endl;
rel_rates<<""<<endl; 

rel_rates<<"h->SetBinError(1,"<<setprecision(2)<< factor*RatioStatUnc(sr12_blipswithinbox,sr12_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(2,"<<setprecision(2)<< factor*RatioStatUnc(sr1_blipswithinbox,sr1_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(3,"<<setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,sr2_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(4,"<<setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,sr3_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(5,"<<setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,sr4_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(6,"<<setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,sr5_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(7,"<<setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,sr6_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(8,"<<setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,sr7_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(9,"<<setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,sr8_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(10,"<<setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,sr9_blips)<<");"<<endl;
rel_rates<<"h->SetBinError(11,"<<setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,sr10_blips)<<");"<<endl;

float  eS = shift  ; 
rel_rates<<" "<<endl; rel_rates<<" "<<endl; rel_rates<<" "<<endl;
rel_rates<<"Relative Rates Array"<<endl;

rel_rates<<" float Obs_"<<eS<<"[11] = {"<<setprecision(2)<<factor*Ratio(sr12_blipswithinbox,sr12_blips)<<", "<<setprecision(2)<< factor*Ratio(sr1_blipswithinbox,sr1_blips)<<", "<<setprecision(2)<< factor*Ratio(sr2_blipswithinbox,sr2_blips)<<", "<<setprecision(2)<< factor*Ratio(sr3_blipswithinbox,sr3_blips)<<", "<<setprecision(2)<< factor*Ratio(sr4_blipswithinbox,sr4_blips)<<", "<<setprecision(2)<< factor*Ratio(sr5_blipswithinbox,sr5_blips)<<", "<<setprecision(2)<< factor*Ratio(sr6_blipswithinbox,sr6_blips)<<", "<<setprecision(2)<< factor*Ratio(sr7_blipswithinbox,sr7_blips)<<", "<<setprecision(2)<< factor*Ratio(sr8_blipswithinbox,sr8_blips)<<", "<<setprecision(2)<< factor*Ratio(sr9_blipswithinbox,sr9_blips)<<", "<<setprecision(2)<< factor*Ratio(sr10_blipswithinbox,sr10_blips)<<"};"<<endl; 




abs_rates<<"absolute rates"<<endl;
abs_rates<<setprecision(2)<< factor*Ratio(sr12_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr12_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr1_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr1_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr2_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr3_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr4_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr5_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr6_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr7_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr8_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr9_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,totalEvents)<< endl; 
abs_rates<<setprecision(2)<< factor*Ratio(sr10_blipswithinbox,totalEvents)<<" ± " << setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,totalEvents)<<endl;


metrics_blips<<"Band limits: "<<endl; 
for (int m = 0 ; m < 11 ; m++){

metrics_blips<<"Ybot["<<m <<" ]: "<< Ybot[m]<<"\tYtop["<<m <<" ]: "<< Ytop[m]<<endl;

}
/*
for (int m = 0 ; m < 11 ; m++){

metrics_blips<<"Ybot["<<m <<" ]: "<< Ybot[m]<<endl;

}
*/






graph_rr<</*"0.0 - 3.0: "<<"\t"<<*/1<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr12_blipswithinbox,sr12_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr12_blipswithinbox,sr12_blips)<< endl;
graph_rr<</*"3.0 - 3.5: "<<"\t"<<*/2<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr1_blipswithinbox,sr1_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr1_blipswithinbox,sr1_blips)<< endl;
graph_rr<</*"3.5 - 4.0: "<<"\t"<<*/3<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr2_blipswithinbox,sr2_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,sr2_blips)<< endl;
graph_rr<</*"4.0 - 4.5: "<<"\t"<<*/4<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr3_blipswithinbox,sr3_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,sr3_blips)<< endl;
graph_rr<</*"4.5 - 5.0: "<<"\t"<<*/5<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr4_blipswithinbox,sr4_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,sr4_blips)<< endl;
graph_rr<</*"5.0 - 5.5: "<<"\t"<<*/6<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr5_blipswithinbox,sr5_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,sr5_blips)<< endl;
graph_rr<</*"5.5 - 6.0: "<<"\t"<<*/7<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr6_blipswithinbox,sr6_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,sr6_blips)<< endl;
graph_rr<</*"6.0 - 6.5: "<<"\t"<<*/8<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr7_blipswithinbox,sr7_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,sr7_blips)<< endl;
graph_rr<</*"6.5 - 7.0: "<<"\t"<<*/9<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr8_blipswithinbox,sr8_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,sr8_blips)<< endl;
graph_rr<</*"7.0 - 7.5: "<<"\t"<<*/10<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr9_blipswithinbox,sr9_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,sr9_blips)<< endl;
graph_rr<</*"7.5 - 8.0: "<<"\t"<<*/11<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr10_blipswithinbox,sr10_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,sr10_blips)<<endl;



graph_rrsk1<</*"3.0 - 3.5: "<<"\t"<<*/2<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr1_blipswithinbox,sr1_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr1_blipswithinbox,sr1_blips)<< endl;
graph_rrsk1<</*"3.5 - 4.0: "<<"\t"<<*/3<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr2_blipswithinbox,sr2_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,sr2_blips)<< endl;
graph_rrsk1<</*"4.0 - 4.5: "<<"\t"<<*/4<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr3_blipswithinbox,sr3_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,sr3_blips)<< endl;
graph_rrsk1<</*"4.5 - 5.0: "<<"\t"<<*/5<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr4_blipswithinbox,sr4_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,sr4_blips)<< endl;
graph_rrsk1<</*"5.0 - 5.5: "<<"\t"<<*/6<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr5_blipswithinbox,sr5_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,sr5_blips)<< endl;
graph_rrsk1<</*"5.5 - 6.0: "<<"\t"<<*/7<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr6_blipswithinbox,sr6_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,sr6_blips)<< endl;
graph_rrsk1<</*"6.0 - 6.5: "<<"\t"<<*/8<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr7_blipswithinbox,sr7_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,sr7_blips)<< endl;
graph_rrsk1<</*"6.5 - 7.0: "<<"\t"<<*/9<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr8_blipswithinbox,sr8_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,sr8_blips)<< endl;
graph_rrsk1<</*"7.0 - 7.5: "<<"\t"<<*/10<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr9_blipswithinbox,sr9_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,sr9_blips)<< endl;
graph_rrsk1<</*"7.5 - 8.0: "<<"\t"<<*/11<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr10_blipswithinbox,sr10_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,sr10_blips)<<endl;


graph_rrsk2<</*"3.5 - 4.0: "<<"\t"<<*/3<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr2_blipswithinbox,sr2_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,sr2_blips)<< endl;
graph_rrsk2<</*"4.0 - 4.5: "<<"\t"<<*/4<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr3_blipswithinbox,sr3_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,sr3_blips)<< endl;
graph_rrsk2<</*"4.5 - 5.0: "<<"\t"<<*/5<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr4_blipswithinbox,sr4_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,sr4_blips)<< endl;
graph_rrsk2<</*"5.0 - 5.5: "<<"\t"<<*/6<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr5_blipswithinbox,sr5_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,sr5_blips)<< endl;
graph_rrsk2<</*"5.5 - 6.0: "<<"\t"<<*/7<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr6_blipswithinbox,sr6_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,sr6_blips)<< endl;
graph_rrsk2<</*"6.0 - 6.5: "<<"\t"<<*/8<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr7_blipswithinbox,sr7_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,sr7_blips)<< endl;
graph_rrsk2<</*"6.5 - 7.0: "<<"\t"<<*/9<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr8_blipswithinbox,sr8_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,sr8_blips)<< endl;
graph_rrsk2<</*"7.0 - 7.5: "<<"\t"<<*/10<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr9_blipswithinbox,sr9_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,sr9_blips)<< endl;
graph_rrsk2<</*"7.5 - 8.0: "<<"\t"<<*/11<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr10_blipswithinbox,sr10_blips)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,sr10_blips)<<endl;





per_graph_blips<</*"0.0 - 3.0: "<<"\t"<<*/1<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr12_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr12_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"3.0 - 3.5: "<<"\t"<<*/2<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr1_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr1_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"3.5 - 4.0: "<<"\t"<<*/3<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr2_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr2_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"4.0 - 4.5: "<<"\t"<<*/4<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr3_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr3_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"4.5 - 5.0: "<<"\t"<<*/5<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr4_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr4_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"5.0 - 5.5: "<<"\t"<<*/6<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr5_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr5_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"5.5 - 6.0: "<<"\t"<<*/7<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr6_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr6_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"6.0 - 6.5: "<<"\t"<<*/8<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr7_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr7_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"6.5 - 7.0: "<<"\t"<<*/9<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr8_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr8_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"7.0 - 7.5: "<<"\t"<<*/10<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr9_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr9_blipswithinbox,totalEvents)<< endl;
per_graph_blips<</*"7.5 - 8.0: "<<"\t"<<*/11<<"\t0\t"<< setprecision(2)<< factor*Ratio(sr10_blipswithinbox,totalEvents)<<"\t" << setprecision(2)<< factor*RatioStatUnc(sr10_blipswithinbox,totalEvents)<<endl;









//cout<<"BSP h_blip_proxtrkdist_0-StdDeV: "<<hsr0->GetStdDev()<<endl;


/*

*/


float fac = totalEvents*0.5 ; 



cout<<"Limits: "<<endl; 
cout<<"0.0 - 3.0, Fraction Above: "<<Ratio(sr12_fractionabove,sr12_blips)*100<<" %"<<endl;
cout<<"3.0 - 3.5, Fraction Above: "<<Ratio(sr1_fractionabove,sr1_blips)*100<<" %"<<endl;
cout<<"3.5 - 4.0, Fraction Above: "<<Ratio(sr2_fractionabove,sr2_blips)*100<<" %"<<endl;
cout<<"4.0 - 4.5, Fraction Above: "<<Ratio(sr3_fractionabove,sr3_blips)*100<<" %"<<endl;
cout<<"4.5 - 5.0, Fraction Above: "<<Ratio(sr4_fractionabove,sr4_blips)*100<<" %"<<endl;
cout<<"5.0 - 5.5, Fraction Above: "<<Ratio(sr5_fractionabove,sr5_blips)*100<<" %"<<endl;
cout<<"5.5 - 6.0, Fraction Above: "<<Ratio(sr6_fractionabove,sr6_blips)*100<<" %"<<endl;
cout<<"6.0 - 6.5, Fraction Above: "<<Ratio(sr7_fractionabove,sr7_blips)*100<<" %"<<endl;
cout<<"6.5 - 7.0, Fraction Above: "<<Ratio(sr8_fractionabove,sr8_blips)*100<<" %"<<endl;
cout<<"7.0 - 7.5, Fraction Above: "<<Ratio(sr9_fractionabove,sr9_blips)*100<<" %"<<endl;
cout<<"7.5 - 8.0, Fraction Above: "<<Ratio(sr10_fractionabove,sr10_blips)*100<<" %"<<endl;




 metrics_blips.close();
 graph_blips.close();
 per_graph_blips.close(); 
 graph_rr.close(); 
 graph_rrsk1.close();
 graph_rrsk2.close();
 evd_blips.close();
 abs_rates.close();
 rel_rates.close();
 eff_type1.close();
 eff_type2.close();
 eff_type3.close();
 purity_type1.close();
 purity_type2.close();
 purity_type3.close();



for (int m = 0 ; m < 11 ; m++){

cout<<"Ytop["<<m <<" ]: "<< Ytop[m]<<endl; 

}

for (int m = 0 ; m < 11 ; m++){

cout<<"Ybot["<<m <<" ]: "<< Ybot[m]<<endl;   

}


cout <<"totalEvents: "<<totalEvents<<endl; 
}





int main(int argc, char *argv[]){

std::string  inputFileName = std::string(argv[1]);
std::string outputFileName = std::string(argv[2]);	
std::string outdir = std::string(argv[3]);
int  pdg = atoi(argv[4]); 
std::string label = std::string(argv[5]);
float shift = atof(argv[6]);
std::string  DataType = std::string(argv[7]);
std::string  DetRegion = std::string(argv[8]);



fillHistograms( inputFileName, outputFileName, outdir, pdg, label,  shift,  DataType,  DetRegion );

return 0;

}

