#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"
#include "TVector.h"
#include <string>
#include <iostream>
#include "TGraph.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLine.h"
#include<stdio.h>
#include "TAttFill.h"
#include "TBox.h"
#include "THStack.h"

#include "TLegend.h"
#include <iomanip>      // std::setprecision
#include <fstream>


// ====================================================================================
// Calculates the chi-squared goodness of match between two histograms. It is assumed
// that the 1st histograms (h1) is data and the 2nd (h2) is MC. 
void CalcChi2(TH1D* h1, TH1D* h2, double& chi2Sum, int& ndf, float x1=-9e9, float x2=9e9){
  int nbins = h1->GetNbinsX();
  if( nbins != h2->GetNbinsX() ) { std::cout<<"Bins don't match!!!\n"; return;}
  chi2Sum = 0.;
  ndf     = 0;
  for(int i=1; i<=nbins; i++){
    float x_l = h1->GetXaxis()->GetBinLowEdge(i);
    float x_u = h1->GetXaxis()->GetBinLowEdge(i+1);
    float x   = h1->GetXaxis()->GetBinCenter(i);
    if( x_l < x1 || x_u > x2 ) continue;
    float b1 = float(h1->GetBinContent(i));
    float b2 = float(h2->GetBinContent(i));
    float e1 = h1->GetBinError(i);
    float e2 = h2->GetBinError(i);
    float sig = sqrt( pow(e1,2) + pow(e2,2) );
    if( sig == 0. ) continue;
    //std::cout<<"bin "<<i<<"  val1= "<<b1<<" +/- "<<e1<<", val2= "<<b2<<" +/- "<<e2<<"\n";
    chi2Sum += pow( (b1-b2)/sig, 2 );
    ndf++;
  }
  std::cout<<"ChiSquare comparison: "<<nbins<<" bins total, "<<ndf<<" bins used, sum_chi2 = "<<chi2Sum<<"\n";
  return ;
}


//==================================================================================

void DrawRectangle(float xi, float yi, float xf, float yf, int width, int rgb){

/*
float xi = 3.6;
float yi = 60000;
float xf = 3.9;
float yf = 70000; 

int width = 1; int rgb = 2 ;
*/

TLine *line1 = new TLine(xi,yi,xf,yi);
TLine *line2 = new TLine(xf,yi,xf,yf);
TLine *line3 = new TLine(xf,yf,xi,yf);
TLine *line4 = new TLine(xi,yf,xi,yi); 
           
    line1->SetLineWidth(width);
    line2->SetLineWidth(width);
    line3->SetLineWidth(width);
    line4->SetLineWidth(width);
    line1->SetLineColor(rgb);
    line2->SetLineColor(rgb);
    line3->SetLineColor(rgb);
    line4->SetLineColor(rgb);
    line1->Draw();
    line2->Draw(); 
    line3->Draw();
    line4->Draw();

}

//=================================================================================

//==============================================
// Plot Bkg subtracted histograms
//==============================================

void Plot_Bkg(TH1D* h1, TH1D* h2, TH1D* h3, const char* hTitle, const char* hName,  const char* MainDir, const char* Dir, bool addNeutrons, float eShift, float NormF , bool doPlot ) {
//h1 G10 hist
//h2 NonG10 hist
//h3 hdiff

TCanvas *c = new TCanvas("c", "canvas", 200, 10, 1000, 800);

h1->Draw("hist same");
h2->Draw("hist same");
h3->Draw("hist same");


auto Legend = new TLegend(0.55,0.7,0.9,0.9);
     Legend->SetHeader(Form("%s", hTitle ) ,"C" ); // option "C" allows to center the header
     Legend->AddEntry(h1,"G10 blips","l");
     Legend->AddEntry(h2,"Non G10 blips","l");
     Legend->AddEntry(h3,"G10 - Non G10 blips","l");
     c->Update();
     Legend->Draw();

if(doPlot == 1){
addNeutrons ? c->Print(Form("%s/%s/wn_BkgSub_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ))  : c->Print(Form("%s/%s/BkgSub_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ));
gPad->SetLogy();
addNeutrons ? c->Print(Form("%s/%s/wn_BkgSub_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF )) : c->Print(Form("%s/%s/BkgSub_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF ));
}

}



//=========================================================



void Plot_Components(TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, TH1D* h5, const char* hTitle, const char* hName,  const char* MainDir, const char* Dir, bool addNeutrons, float SRUx1, float SRUx2,  float eShift, float NormF ) {
TCanvas *c = new TCanvas("c1", "canvas1", 200, 10, 1000, 800);

//h1 Total
//h2 MC
//h3 Overlay


h1->Draw("hist same");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same"); 
h5->Draw("hist same");


h1->SetLineColor(1) ; h1->SetMarkerColor(1) ;
h2->SetLineColor(2) ; h2->SetMarkerColor(2) ;
h3->SetLineColor(4) ; h3->SetMarkerColor(4) ;
h4->SetLineColor(3) ; h4->SetMarkerColor(3) ; h4->SetLineStyle(2); 
h5->SetLineColor(6) ; h5->SetMarkerColor(6) ; h5->SetLineStyle(2);

h1->GetXaxis()->SetRangeUser( SRUx1, SRUx2 );

auto Legend = new TLegend(0.55,0.7,0.9,0.9);
     Legend->SetHeader(Form("%s", hTitle ) ,"C" ); // option "C" allows to center the header
     Legend->AddEntry(h1,"MC-Overlay blips","l");
     Legend->AddEntry(h3,"Overlay blips","l");
      Legend->AddEntry(h2,"MC blips","l");
     Legend->AddEntry(h4,"MC_e- blips","l");
     Legend->AddEntry(h5,"MC_e+ blips","l");
     c->Update();
     Legend->Draw();

if(eShift == 0){
addNeutrons ? c->Print(Form("%s/%s/wn_Components_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ))   :  c->Print(Form("%s/%s/Components_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ));


gPad->SetLogy();
addNeutrons ? c->Print(Form("%s/%s/wn_Components_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF )) : c->Print(Form("%s/%s/Components_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF ));
}

}

//========================================================
void Plot_Components_Process(TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, TH1D* h5, TH1D* h6, const char* hTitle, const char* hName,  const char* MainDir, const char* Dir, bool addNeutrons, float SRUx1, float SRUx2,  float eShift, float NormF ) {
TCanvas *c = new TCanvas("c2", "canvas2", 200, 10, 1000, 800);


//h1 MC
//h2 primary
//h3 compton
//h4 photo
//h5 pairprod
//h6 Otherproc

h1->Draw("hist same");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");
h5->Draw("hist same");
h5->Draw("hist same");
h6->Draw("hist same");

h1->SetLineColor(1) ; h1->SetMarkerColor(1) ;
h2->SetLineColor(3) ; h2->SetMarkerColor(3) ;
h3->SetLineColor(4) ; h3->SetMarkerColor(4) ;
h4->SetLineColor(2) ; h4->SetMarkerColor(2) ; //h4->SetLineStyle(2);
h5->SetLineColor(6) ; h5->SetMarkerColor(6) ; //h5->SetLineStyle(2);
h6->SetLineColor(7) ; h6->SetMarkerColor(7) ; // h6->SetLineStyle(2);

h1->GetXaxis()->SetRangeUser( SRUx1, SRUx2 );

auto Legend = new TLegend(0.55,0.7,0.9,0.9);
     Legend->SetHeader(Form("%s", hTitle ) ,"C" ); // option "C" allows to center the header
     Legend->AddEntry(h1,"MC Total blips","l");
     Legend->AddEntry(h3,"Compton Scat","l");
      Legend->AddEntry(h4,"Photoelectric","l");
     Legend->AddEntry(h5,"Pair prod","l");
     Legend->AddEntry(h2,"Primary","l");
     Legend->AddEntry(h6,"Other","l");
     c->Update();
     Legend->Draw();

if(eShift == 0){
addNeutrons ? c->Print(Form("%s/%s/wn_ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ))   :  c->Print(Form("%s/%s/ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ));


gPad->SetLogy();
addNeutrons ? c->Print(Form("%s/%s/wn_ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF )) : c->Print(Form("%s/%s/ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF ));
}

}
//=========================================================

void Plot_Components_Process_Stk(TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, TH1D* h5, TH1D* h6, const char* hTitle, const char* hName,  const char* MainDir, const char* Dir, bool addNeutrons, float eShift, float NormF ) {
TCanvas *c = new TCanvas("c2s", "canvas2s", 200, 10, 1000, 800);


//h1 MC
//h2 primary
//h3 compton
//h4 photo
//h5 pairprod
//h6 Otherproc

 THStack *hs = new THStack("hs","Processes");

//h1->SetLineColor(2) ; h1->SetMarkerColor(2) ;  
//h1->SetFillColor(2) ;
//h2->SetLineColor(3) ; h2->SetMarkerColor(3) ; 
 h2->SetFillColor(3) ;
//h3->SetLineColor(4) ; h3->SetMarkerColor(4) ;  
h3->SetFillColor(4) ;
//h4->SetLineColor(kOrange) ; h4->SetMarkerColor(kOrange) ;
 h4->SetFillColor(kOrange) ; //h4->SetLineStyle(2);
//h5->SetLineColor(6) ; h5->SetMarkerColor(6) ;  
h5->SetFillColor(6) ;//h5->SetLineStyle(2);
//h6->SetLineColor(7) ; h6->SetMarkerColor(7) ;
  h6->SetFillColor(7) ; // h6->SetLineStyle(2);

//hs->Add(h1);
hs->Add(h2);
hs->Add(h3);
hs->Add(h4);
hs->Add(h5);
hs->Add(h6);

hs->Draw("lego1");


auto Legend = new TLegend(0.55,0.7,0.9,0.9);
     Legend->SetHeader(Form("%s", hTitle ) ,"C" ); // option "C" allows to center the header
    // Legend->AddEntry(h1,"MC Total blips","l");
     Legend->AddEntry(h3,"Compton Scat","l");
      Legend->AddEntry(h4,"Photoelectric","l");
     Legend->AddEntry(h5,"Pair prod","l");
     Legend->AddEntry(h2,"Primary","l");
     Legend->AddEntry(h6,"Other","l");
     c->Update();
     Legend->Draw();

if(eShift == 0){
addNeutrons ? c->Print(Form("%s/%s/wn_ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f_Stk.png"    , MainDir, Dir, hName, eShift, NormF ))   :  c->Print(Form("%s/%s/ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f_Stk.png"    , MainDir, Dir, hName, eShift, NormF ));


gPad->SetLogy();
addNeutrons ? c->Print(Form("%s/%s/wn_ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f_Stk_Log.png", MainDir, Dir, hName, eShift, NormF )) : c->Print(Form("%s/%s/ProcessComponents_%s-EShift_%2.2fpercent_SNF_%1.2f_Stk_Log.png", MainDir, Dir, hName, eShift, NormF ));
}







}

//=========================================================

void Plot_Histograms(TH1D* h1, TH1D* h2,  const char* hTitle, const char* hName,  const char* MainDir, const char* Dir, bool addNeutrons,  float eShift, float NormF ) {
TCanvas *c = new TCanvas("c3", "canvas3", 200, 10, 1000, 800);

//h1 run3 data
//h2 run6 data

h2->Scale( h1->Integral() / h2->Integral() );


h1->SetLineColor(1) ; h1->SetMarkerColor(1) ;
h2->SetLineColor(222) ; h2->SetMarkerColor(222);

h1->Draw("hist same E0");
h2->Draw("hist same E0");


auto Legend = new TLegend(0.55,0.7,0.9,0.9);
     Legend->SetHeader(Form("%s", hTitle ) ,"C" ); // option "C" allows to center the header
     Legend->AddEntry(h1,"Run 3 data","l");
     Legend->AddEntry(h2,"Run 6 data norm","l");
 
     c->Update();
     Legend->Draw();

h1->GetYaxis()->SetRangeUser(0.01,40000);
c->Update();

if(eShift == 0){
addNeutrons ?  c->Print(Form("%s/%s/wn_DataRelativeShift_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ))    :  c->Print(Form("%s/%s/DataRelativeShift_%s-EShift_%2.2fpercent_SNF_%1.2f.png"    , MainDir, Dir, hName, eShift, NormF ));


gPad->SetLogy(1);

//c->Update();

addNeutrons ? c->Print(Form("%s/%s/wn_DataRelativeShift_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF )) : c->Print(Form("%s/%s/DataRelativeShift_%s-EShift_%2.2fpercent_SNF_%1.2f_Log.png", MainDir, Dir, hName, eShift, NormF ));
}

}


//=========================================================

void Plot_EShift(TH1D* h1, TH1D* h2, TH1D* h3, TH1D* hK40, int runNumber, const char* hTitle, const char* hName,  const char* MainDir, const char* Dir,  float eShift, float NormF, float SRUx1, float SRUx2 , float SRUy1, float SRUy2 , bool addNeutrons, bool addK40Gammas, bool doPlot, /* float Chi2, int ndf,*/bool IsMCOverlay,	float X1_Fit, float X2_Fit) {

	
if(NormF != -1) {

ofstream chi2_energyshift_run3;
ofstream chi2NDF_energyshift_run3;
ofstream chi2_energyshift_run6;
ofstream chi2NDF_energyshift_run6;


const char *inputFileNameGraph   = (IsMCOverlay == 1) ? Form("%s/chi2_energyshift_run3_overlay.txt", MainDir )    : Form("%s/chi2_energyshift_run3_fullmc.txt", MainDir ) ;
const char *inputFileNameGraph1  = (IsMCOverlay == 1) ? Form("%s/chi2NDF_energyshift_run3_overlay.txt", MainDir)  : Form("%s/chi2NDF_energyshift_run3_fullmc.txt", MainDir) ;
const char *inputFileNameGraph2  = (IsMCOverlay == 1) ? Form("%s/chi2_energyshift_run6_overlay.txt", MainDir)    : Form("%s/chi2_energyshift_run6_fullmc.txt", MainDir) ;
const char *inputFileNameGraph3  = (IsMCOverlay == 1) ? Form("%s/chi2NDF_energyshift_run6_overlay.txt", MainDir) : Form("%s/chi2NDF_energyshift_run6_fullmc.txt", MainDir) ;



chi2_energyshift_run3.open (inputFileNameGraph,std::ofstream::in |std::ofstream::app);
chi2NDF_energyshift_run3.open (inputFileNameGraph1,std::ofstream::in |std::ofstream::app);
chi2_energyshift_run6.open (inputFileNameGraph2,std::ofstream::in |std::ofstream::app);
chi2NDF_energyshift_run6.open (inputFileNameGraph3,std::ofstream::in |std::ofstream::app);	
	
	
	
	
//h1 data 
//h2 shifted MC gammas
//h3 shifted MC neutrons

TCanvas *c = new TCanvas("c", "canvas", 200, 10, 1000, 800);

h1->Sumw2();
h2->Sumw2();
h3->Sumw2();

//cout<<"h1 Entries: "<<h1->GetEntries()<<"Integral:  "<<h1->GetIntegral() <<endl; 
//cout<<"h2 Entries: "<<h2->GetEntries()<<"Integral:  "<<h2->GetIntegral() <<endl;
//cout<<"h3 Entries: "<<h3->GetEntries()<<"Integral:  "<<h3->GetIntegral() <<endl;


 TPad *p1 = new TPad("p1","p1",0.0,0.4,1.0,1.0);
//   p1->SetFillColor(kBlue);
p1->Draw();

p1->cd(0);



h1->SetLineColor(1); h1->SetMarkerColor(1);

h1->GetXaxis()->SetRangeUser( SRUx1, SRUx2 );

h1->Draw("hist same");



TH1D* hTotalMC = (TH1D*) h2->Clone("hTotalMC");
hTotalMC->Sumw2();

//cout<<"hMC Entries: "<<hTotalMC->GetEntries()<<endl;

if(addNeutrons == 1) hTotalMC->Add(h3, 1.); 
if(addK40Gammas == 1) hTotalMC->Add(hK40, 1.);


//cout<<"Afeter addNeutrons = "<<addNeutrons<<" ;    hMC Entries: "<<hTotalMC->GetEntries()<<endl;


hTotalMC->Scale( h1->Integral() / hTotalMC->Integral() );
hTotalMC->Scale( NormF );
hTotalMC->SetLineColor(222); hTotalMC->SetMarkerColor(222);
hTotalMC->Draw("hist same");


TBox *box = new TBox(X1_Fit, 0.0 , X2_Fit, SRUy2);
box->SetFillColor(kViolet);
box->SetFillStyle(3003);
box->Draw();

c->Update();


double Chi2; int ndf;

 

CalcChi2(h1, hTotalMC, Chi2, ndf, X1_Fit, X2_Fit); //Chi2 Calculation

if(doPlot == 1) cout<<"Run number:"<<runNumber<<",   Fit Region: [ "<< X1_Fit<<" - "<<X2_Fit<<" ] MeV "<<ndf<<endl;
if(doPlot == 1) cout<<"Chi2 calculation info, Chi2: "<< Chi2 <<" NDF: "<<ndf<<endl; 

if(runNumber == 3  ) {chi2_energyshift_run3<<eShift<<"\t"<<NormF<<"\t" <<Chi2<<"\t"<<endl;
                   chi2NDF_energyshift_run3<<eShift<<"\t"<<NormF<<"\t"<<Chi2/ndf<<"\t"<<endl; } 
       
else if(runNumber == 6 ) {chi2_energyshift_run6<<eShift<<"\t"<<NormF<<"\t" <<Chi2<<"\t"<<endl;
                         chi2NDF_energyshift_run6<<eShift<<"\t"<<NormF<<"\t"<<Chi2/ndf<<"\t"<<endl; }
else cout<<" Run Number is "<<runNumber<<endl; 	
	
	


auto Legend = new TLegend(0.45,0.6,0.9,0.9);

     Legend->SetHeader(Form("%s -  #chi^{2}: %6.2f,  #chi^{2}/NDF: %5.2f ", hTitle, Chi2, Chi2/ndf ),"C");
     Legend->AddEntry(h1,"data G10- Non G10 blips","l");
     if( addK40Gammas == 0 && addNeutrons == 0) Legend->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF ) ) ;
     if( addK40Gammas == 0 && addNeutrons == 1) Legend->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma, 1eV n. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF) ) ;
     if( addK40Gammas == 1 && addNeutrons == 0) Legend->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma, 1.4MeV #gamma. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF) ) ;
     if( addK40Gammas == 1 && addNeutrons == 1) Legend->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma, 1.4MeV #gamma, 1eV n. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF) ) ;

     c->Update();
     Legend->Draw();

p1->Modified();
c->Update();
c->cd(0);


//Second Pad

TPad *p2 = new TPad("p2","p2",0.0,0.0,1.0,0.4);
// p2->SetTopMargin(0.0); 
//p2->SetFillColor(kRed);
p2->Draw();

p2->cd(0);

TH1D* h4 = (TH1D*) hTotalMC->Clone("h4");
h4->Sumw2();
h4->SetTitle(Form(" MC %2.2f %%_Eshift_%1.2f_SpecNorm / Data BkgSub", eShift, NormF )  );

   h4->GetYaxis()->SetRangeUser(0.5,1.5);
  h4->GetXaxis()->SetRangeUser( SRUx1, SRUx2 ); 
   h4->GetYaxis()->SetTitle("Ratio:  MC / Data                    ");
   h4->Divide(h1);
   h4->Draw(); 
 
   TLine *line1 = new TLine(0,1,5,1);
        line1->SetLineWidth(1);
        line1->SetLineColor(1);
        line1->Draw();

TBox *box2 = new TBox(X1_Fit, 0.5 , X2_Fit, 1.5);
box2->SetFillColor(kViolet);
box2->SetFillStyle(3003);
box2->Draw();



c->Update();	
c->cd(0);


p1->cd(0);
c->Update();


//h1->GetYaxis()->SetRangeUser( YRU_lower, YRU_upper);

if(doPlot == 1 ){ if( addK40Gammas == 0 && addNeutrons == 0)  c->Print(Form("%s/%s/Ratio_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));
                  if( addK40Gammas == 0 && addNeutrons == 1)  c->Print(Form("%s/%s/Ratio_Included_n_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));
                  if( addK40Gammas == 1 && addNeutrons == 0)  c->Print(Form("%s/%s/Ratio_Included_k40gam_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));
                  if( addK40Gammas == 1 && addNeutrons == 1)  c->Print(Form("%s/%s/Ratio_Included_n_k40gam_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));  }

c->Update();


p1->cd(0);


//c->cd(1);
h1->GetYaxis()->SetRangeUser(  SRUy1, SRUy2);
//h1->GetXaxis()->SetRangeUser( SRUx1, SRUx2 );

p2->Modified();
c->Update();


//box->DrawBox(X1_Fit, 0.0 , X2_Fit, YRU_upper);


auto Legend2 = new TLegend(0.45,0.6,0.9,0.9);

     Legend2->SetHeader(Form("%s -  #chi^{2}: %6.2f,  #chi^{2}/NDF: %5.2f ", hTitle, Chi2, Chi2/ndf ),"C");
     Legend2->AddEntry(h1,"data G10- Non G10 blips","l");
     if( addK40Gammas == 0 && addNeutrons == 0) Legend2->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF ) ) ;
     if( addK40Gammas == 0 && addNeutrons == 1) Legend2->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma, 1eV n. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF) ) ;
     if( addK40Gammas == 1 && addNeutrons == 0) Legend2->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma, 1.4MeV #gamma. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF) ) ;
     if( addK40Gammas == 1 && addNeutrons == 1) Legend2->AddEntry(hTotalMC , Form(" MC 2.6MeV #gamma, 1.4MeV #gamma, 1eV n. EShift: %2.2f %%, SNF: %1.2f",eShift, NormF) ) ;

     
	     
     c->Update();
     Legend2->Draw();

box->SetFillColor(kViolet);
box->SetFillStyle(3003);
//box->Draw();
p1->Modified();
c->Update();

if(doPlot == 1 ){ if( addK40Gammas == 0 && addNeutrons == 0)  c->Print(Form("%s/%s/zoom-Ratio_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));
                  if( addK40Gammas == 0 && addNeutrons == 1)  c->Print(Form("%s/%s/zoom-Ratio_Included_n_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));
                  if( addK40Gammas == 1 && addNeutrons == 0)  c->Print(Form("%s/%s/zoom-Ratio_Included_k40gam_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));
                  if( addK40Gammas == 1 && addNeutrons == 1)  c->Print(Form("%s/%s/zoom-Ratio_Included_n_k40gam_%s-EShift_%2.2fpercent_SNF_%1.2f.png", MainDir, Dir, hName, eShift, NormF ));  }


chi2_energyshift_run3.close();
chi2NDF_energyshift_run3.close();
chi2_energyshift_run6.close();
chi2NDF_energyshift_run6.close();


}// if NormF != -1


}





//=========================================================












void Plot_Eshift_Chi2CalcFit(string inputRun3G10 , string inputRun3G10Exc, string inputRun6G10 , string inputRun6G10Exc , string inputMCGammasG10, string inputMCGammasG10Exc,  string inputMCNeutronsG10, string inputMCNeutronsG10Exc,  string inputMCK40G10, string inputMCK40G10Exc, const char* mainDir,  const char* dir, float EShift,  float SpectrumNormF, float SpectrumNormFRun6, bool isMCOverlay , bool AddNeutrons, bool AddK40Gammas, bool plot, float x1_fit, float x2_fit){


//gEnv->SetValue("OpenGL.CanvasPreferGL",1);

//cout<<"IsMCOverlay is set to: "<<isMCOverlay<<endl; 
(isMCOverlay == 1) ? cout<<"IsMCOverlay is set to TRUE "<<endl : cout<<"IsMCOverlay is set to FALSE "<<endl ; 
const char* command = Form("mkdir -p %s/%s/", mainDir, dir);
system(command);


TFile* fileRun3G10          = new TFile(inputRun3G10.c_str(),"READ"); //run3

TFile* fileRun3G10Exc       = new TFile(inputRun3G10Exc.c_str(),"READ"); //run3

TFile* fileRun6G10          = new TFile(inputRun6G10.c_str(),"READ"); //run6

TFile* fileRun6G10Exc       = new TFile(inputRun6G10Exc.c_str(),"READ"); //run6

TFile* fileMCGammasG10      = new TFile(inputMCGammasG10.c_str(),"READ");//Gammas

TFile* fileMCGammasG10Exc   = new TFile(inputMCGammasG10Exc.c_str(),"READ"); //Gammas

TFile* fileMCNeutronsG10    = new TFile(inputMCNeutronsG10.c_str(),"READ");//Neutrons

TFile* fileMCNeutronsG10Exc = new TFile(inputMCNeutronsG10Exc.c_str(),"READ"); //Neutrons

TFile* fileMCK40G10    = new TFile(inputMCK40G10.c_str(),"READ");// K40 Gammas

TFile* fileMCK40G10Exc = new TFile(inputMCK40G10Exc.c_str(),"READ"); // K40 Gammass



TH1D* data_blip_run3_G10 = (TH1D*) fileRun3G10->Get("H_blip_Energy"); // For data H_blip_Energy = H_blip_Energy_mc and H_blip_Energy_overlay is empty
      data_blip_run3_G10->Sumw2();

TH1D* data_blip_run3_G10Exc = (TH1D*) fileRun3G10Exc->Get("H_blip_Energy");
      data_blip_run3_G10Exc->Sumw2();


TH1D* data_blip_run6_G10 = (TH1D*) fileRun6G10->Get("H_blip_Energy");
      data_blip_run6_G10->Sumw2();

TH1D* data_blip_run6_G10Exc = (TH1D*) fileRun6G10Exc->Get("H_blip_Energy");
      data_blip_run6_G10Exc->Sumw2();


//=================================================================================================================================================

//******************
//* 2.6 MeV Gammas *
//******************

//G10
TH1D* gammas_blip_EShifted_Xperc_G10_overlay = (TH1D*) fileMCGammasG10->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
if(isMCOverlay == 1)  gammas_blip_EShifted_Xperc_G10_overlay->Sumw2();
//gammas_blip_EnergyShift_Xperc_overlay->Sumw2();
TH1D* gammas_blip_EShifted_Xperc_G10_mc = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc->Sumw2()  ;
//gammas_blip_EnergyShift_Xperc_mc->Sumw2();

//MC components

TH1D* gammas_blip_EShifted_Xperc_G10_mc_gammas = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_gammas" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_gammas->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_protons = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_protons" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_protons->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_eminus = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eminus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_eminus->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_eplus = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eplus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_eplus->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_other = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherpdg" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_other->Sumw2()  ;


//MC process type
TH1D* gammas_blip_EShifted_Xperc_G10_mc_primary = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_primary" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_primary ->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_compton = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_compton" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_compton ->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_photoe = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_photoe" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_photoe ->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_pairprod = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_pairprod" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_pairprod ->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10_mc_otherproc = (TH1D*) fileMCGammasG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherproc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10_mc_otherproc ->Sumw2()  ;

// Shifted H
TH1D* gammas_blip_EShifted_Xperc_G10 = (TH1D*) fileMCGammasG10->Get( (isMCOverlay == 1) ?  "H_blip_Energy" : "H_blip_Energy" );
gammas_blip_EShifted_Xperc_G10->Sumw2();

//=========================================
//G10Exc
TH1D* gammas_blip_EShifted_Xperc_G10Exc_overlay = (TH1D*) fileMCGammasG10Exc->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
if(isMCOverlay == 1)  gammas_blip_EShifted_Xperc_G10Exc_overlay->Sumw2();
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc->Sumw2()  ;


//G10Exc - MC components
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_gammas = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_gammas" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_gammas->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_protons = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_protons" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_protons->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_eminus = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eminus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_eminus->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_eplus = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eplus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_eplus->Sumw2()  ;
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_other = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherpdg" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_other->Sumw2()  ;


//G10Exc - MC process type
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_primary = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_primary" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_primary ->Sumw2()  ;  
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_compton = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_compton" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_compton ->Sumw2()  ;  
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_photoe = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_photoe" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_photoe ->Sumw2()  ;  
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_pairprod = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_pairprod" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_pairprod ->Sumw2()  ;  
TH1D* gammas_blip_EShifted_Xperc_G10Exc_mc_otherproc = (TH1D*) fileMCGammasG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherproc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammas_blip_EShifted_Xperc_G10Exc_mc_otherproc ->Sumw2()  ;  

//Shifted H
TH1D* gammas_blip_EShifted_Xperc_G10Exc = (TH1D*) fileMCGammasG10Exc->Get( (isMCOverlay == 1) ?  "H_blip_Energy" : "H_blip_Energy" );
gammas_blip_EShifted_Xperc_G10Exc->Sumw2();


//=========================================================================================================================================================

//****************
//* 1eV Neutrons *
//****************

//G10
TH1D* neutrons_blip_EShifted_Xperc_G10_overlay = (TH1D*) fileMCNeutronsG10->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
if(isMCOverlay == 1)  neutrons_blip_EShifted_Xperc_G10_overlay->Sumw2();
TH1D* neutrons_blip_EShifted_Xperc_G10_mc = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc->Sumw2()  ;

//MC components
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_gammas = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_gammas" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_gammas->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_protons = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_protons" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_protons->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_eminus = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eminus" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_eminus->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_eplus = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eplus" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_eplus->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_other = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherpdg" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_other->Sumw2()  ;

//process type
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_primary = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_primary" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_primary ->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_compton = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_compton" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_compton ->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_photoe = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_photoe" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_photoe ->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_pairprod = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_pairprod" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_pairprod ->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10_mc_otherproc = (TH1D*) fileMCNeutronsG10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherproc" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10_mc_otherproc ->Sumw2()  ;


// Shifted H
TH1D* neutrons_blip_EShifted_Xperc_G10 = (TH1D*) fileMCNeutronsG10->Get( (isMCOverlay == 1) ?  "H_blip_Energy" : "H_blip_Energy" );
neutrons_blip_EShifted_Xperc_G10->Sumw2();

//========================================


//G10Exc
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_overlay = (TH1D*) fileMCNeutronsG10Exc->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
if(isMCOverlay == 1)  neutrons_blip_EShifted_Xperc_G10Exc_overlay->Sumw2();
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc->Sumw2()  ;

//G10Exc - MC components
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_gammas = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_gammas" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_gammas->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_protons = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_protons" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_protons->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_eminus = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eminus" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_eminus->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_eplus = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eplus" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_eplus->Sumw2()  ;
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_other = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherpdg" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_other->Sumw2()  ;

//G10Exc - MC process type
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_primary = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_primary" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_primary ->Sumw2()  ; 
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_compton = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_compton" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_compton ->Sumw2()  ; 
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_photoe = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_photoe" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_photoe ->Sumw2()  ; 
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_pairprod = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_pairprod" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_pairprod ->Sumw2()  ; 
TH1D* neutrons_blip_EShifted_Xperc_G10Exc_mc_otherproc = (TH1D*) fileMCNeutronsG10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherproc" :" H_blip_Energy" );
if(isMCOverlay == 1) neutrons_blip_EShifted_Xperc_G10Exc_mc_otherproc ->Sumw2()  ; 

// Shifted H
TH1D* neutrons_blip_EShifted_Xperc_G10Exc = (TH1D*) fileMCNeutronsG10Exc->Get( (isMCOverlay == 1) ?  "H_blip_Energy" : "H_blip_Energy" );
neutrons_blip_EShifted_Xperc_G10Exc->Sumw2();



//====================================================================================================================================================

//**************
//* K40 gammas *
//**************

//G10
TH1D* gammasK40_blip_EShifted_Xperc_G10_overlay = (TH1D*) fileMCK40G10->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
if(isMCOverlay == 1)  gammasK40_blip_EShifted_Xperc_G10_overlay->Sumw2();
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc->Sumw2()  ;

//MC components
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_gammas = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_gammas" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_gammas->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_protons = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_protons" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_protons->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_eminus = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eminus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_eminus->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_eplus = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eplus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_eplus->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_other = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherpdg" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_other->Sumw2()  ;

//MC process type
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_primary = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_primary" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_primary ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_compton = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_compton" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_compton ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_photoe = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_photoe" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_photoe ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_pairprod = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_pairprod" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_pairprod ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10_mc_otherproc = (TH1D*) fileMCK40G10 ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherproc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10_mc_otherproc ->Sumw2()  ;

//Shifted H
TH1D* gammasK40_blip_EShifted_Xperc_G10 = (TH1D*) fileMCK40G10->Get( (isMCOverlay == 1) ?  "H_blip_Energy" : "H_blip_Energy" );
gammasK40_blip_EShifted_Xperc_G10->Sumw2();

//========================================

//G10Exc
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_overlay = (TH1D*) fileMCK40G10Exc->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
if(isMCOverlay == 1)  gammasK40_blip_EShifted_Xperc_G10Exc_overlay->Sumw2();
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc->Sumw2()  ;


//G10Exc - MC components

TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_gammas = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_gammas" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_gammas->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_protons = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_protons" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_protons->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_eminus = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eminus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_eminus->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_eplus = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_eplus" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_eplus->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_other = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherpdg" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_other->Sumw2()  ;



//G10ExcExc - MC process typ
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_primary = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_primary" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_primary ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_compton = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_compton" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_compton ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_photoe = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_photoe" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_photoe ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_pairprod = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_pairprod" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_pairprod ->Sumw2()  ;
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc_mc_otherproc = (TH1D*) fileMCK40G10Exc ->Get( (isMCOverlay == 1) ? "H_blip_Energy_mc_otherproc" :" H_blip_Energy" );
if(isMCOverlay == 1) gammasK40_blip_EShifted_Xperc_G10Exc_mc_otherproc ->Sumw2()  ;






//G10Exc - Shifted H
TH1D* gammasK40_blip_EShifted_Xperc_G10Exc = (TH1D*) fileMCK40G10Exc->Get( (isMCOverlay == 1) ?  "H_blip_Energy" : "H_blip_Energy" );
gammasK40_blip_EShifted_Xperc_G10Exc->Sumw2();
//===========================================================================================================================================================



/*

//NonG10MC
TH1D* gammas_blip_EnergyShift_Xperc_overlay_G10Exc = (TH1D*) fileMCG10Exc->Get( (isMCOverlay == 1) ? "H_blip_Energy_overlay" :" H_blip_Energy_overlay" );
//if(isMCOverlay == 1)  gammas_blip_EnergyShift_Xperc_overlay_G10Exc->Sumw2() ;
if(isMCOverlay == 1) gammas_blip_EnergyShift_Xperc_overlay_G10Exc->Sumw2();
//gammas_blip_EnergyShift_Xperc_overlay_G10Exc->Sumw2();

TH1D* gammas_blip_EnergyShift_Xperc_mc_G10Exc = (TH1D*) fileMCG10Exc->Get( (isMCOverlay == 1) ? "H_blip_Energy" :" H_blip_Energy_mc" );
if(isMCOverlay == 1)  gammas_blip_EnergyShift_Xperc_mc_G10Exc->Sumw2() ;
//gammas_blip_EnergyShift_Xperc_mc_G10Exc->Sumw2();

TH1D* gammas_blip_EnergyShift_Xperc_G10Exc = (TH1D*) fileMCG10Exc->Get( (isMCOverlay == 1) ?  "H_blip_Energy_mc" : "H_blip_Energy" );
      gammas_blip_EnergyShift_Xperc_G10Exc->Sumw2();


*/





cout<<"Loaded files"<<endl;


/*
ofstream chi2_energyshift_run3;
ofstream chi2NDF_energyshift_run3;
ofstream chi2_energyshift_run6;
ofstream chi2NDF_energyshift_run6;


const char *inputFileNameGraph   = (isMCOverlay == 1) ? Form("%s/chi2_energyshift_run3_overlay.txt", mainDir )    : Form("%s/chi2_energyshift_run3_fullmc.txt", mainDir ) ;
const char *inputFileNameGraph1  = (isMCOverlay == 1) ? Form("%s/chi2NDF_energyshift_run3_overlay.txt", mainDir)  : Form("%s/chi2NDF_energyshift_run3_fullmc.txt", mainDir) ;
const char *inputFileNameGraph2  = (isMCOverlay == 1) ? Form("%s/chi2_energyshift_run6_overlay.txt", mainDir)    : Form("%s/chi2_energyshift_run6_fullmc.txt", mainDir) ; 
const char *inputFileNameGraph3  = (isMCOverlay == 1) ? Form("%s/chi2NDF_energyshift_run6_overlay.txt", mainDir) : Form("%s/chi2NDF_energyshift_run6_fullmc.txt", mainDir) ;



chi2_energyshift_run3.open (inputFileNameGraph,std::ofstream::in |std::ofstream::app);
chi2NDF_energyshift_run3.open (inputFileNameGraph1,std::ofstream::in |std::ofstream::app);
chi2_energyshift_run6.open (inputFileNameGraph2,std::ofstream::in |std::ofstream::app);
chi2NDF_energyshift_run6.open (inputFileNameGraph3,std::ofstream::in |std::ofstream::app);
*/


int nBins = 100; 

gStyle->SetOptStat(0);


data_blip_run3_G10->SetLineColor(95); data_blip_run3_G10->SetMarkerColor(95);//G10 run3
data_blip_run3_G10Exc->SetLineColor(4); data_blip_run3_G10Exc->SetMarkerColor(4);//Non-G10 run3

data_blip_run6_G10->SetLineColor(97); data_blip_run6_G10->SetMarkerColor(97);//G10 Rn
data_blip_run6_G10Exc->SetLineColor(54); data_blip_run6_G10Exc->SetMarkerColor(54);//Non-G10 Rn


//mc components of gammas and neutrons
gammas_blip_EShifted_Xperc_G10_mc->SetLineColor(93) ; gammas_blip_EShifted_Xperc_G10_mc->SetMarkerColor(93) ; //G10 Gammas
gammas_blip_EShifted_Xperc_G10Exc_mc->SetLineColor(64) ; gammas_blip_EShifted_Xperc_G10Exc_mc->SetMarkerColor(64) ; //Non-G10 Gammas

neutrons_blip_EShifted_Xperc_G10_mc->SetLineColor(81) ; neutrons_blip_EShifted_Xperc_G10_mc->SetMarkerColor(81) ; //G10 Neutrons
neutrons_blip_EShifted_Xperc_G10Exc_mc->SetLineColor(61) ; neutrons_blip_EShifted_Xperc_G10Exc_mc->SetMarkerColor(61) ; //Non-G10 Neutrons



// Subtraction Run3 Data
TH1D* hDiffRun3 = (TH1D*) data_blip_run3_G10->Clone("hDiffRun3");
hDiffRun3->Sumw2(); 
hDiffRun3->Add(data_blip_run3_G10Exc, -1.);
hDiffRun3->SetLineColor(1); hDiffRun3->SetMarkerColor(1);

// Subtraction Run6 Data
TH1D* hDiffRun6 = (TH1D*) data_blip_run6_G10->Clone("hDiffRun6");
hDiffRun6->Sumw2();
hDiffRun6->Add(data_blip_run6_G10Exc, -1.);
hDiffRun6->SetLineColor(13); hDiffRun6->SetMarkerColor(13);

// Subtraction MC gammas ONLY mc component
TH1D* hDiffMCGammas = (TH1D*) gammas_blip_EShifted_Xperc_G10_mc->Clone("hDiffMCGammas");
hDiffMCGammas->Sumw2();
hDiffMCGammas->Add(gammas_blip_EShifted_Xperc_G10Exc_mc, -1.);
hDiffMCGammas->SetLineColor(14); hDiffMCGammas->SetMarkerColor(14); //hDiffMCGammas->SetLineStyle(2);

// Subtraction MC neutrons ONLY mc component
TH1D* hDiffMCNeutrons = (TH1D*) neutrons_blip_EShifted_Xperc_G10_mc->Clone("hDiffMCNeutrons");
hDiffMCNeutrons->Sumw2();
hDiffMCNeutrons->Add(neutrons_blip_EShifted_Xperc_G10Exc_mc, -1.);
hDiffMCNeutrons->SetLineColor(15); hDiffMCNeutrons->SetMarkerColor(15); //hDiffMC->SetLineStyle(2);

// Subtraction MC K40gammas ONLY mc component
TH1D* hDiffMCK40Gammas = (TH1D*) gammasK40_blip_EShifted_Xperc_G10_mc->Clone("hDiffMCK40Gammas");
hDiffMCK40Gammas->Sumw2();
hDiffMCK40Gammas->Add(gammasK40_blip_EShifted_Xperc_G10Exc_mc, -1.);
hDiffMCK40Gammas->SetLineColor(14); hDiffMCK40Gammas->SetMarkerColor(14); //hDiffMCK40Gammas->SetLineStyle(2);



// Data Normalized histogram
TH1D* hDiffRun6Norm = (TH1D*) hDiffRun6->Clone("hDiffRun6Norm");
hDiffRun6Norm->Scale(hDiffRun3->Integral()/hDiffRun6Norm->Integral() );//Run6 Normalized to Run3
hDiffRun6Norm->SetLineColor(kViolet); hDiffRun6Norm->SetMarkerColor(kViolet);


data_blip_run3_G10->SetLineColor(95); data_blip_run3_G10->SetMarkerColor(95);//G10 run3
data_blip_run3_G10Exc->SetLineColor(4); data_blip_run3_G10Exc->SetMarkerColor(4);//Non-G10 run3
data_blip_run6_G10->SetLineColor(97); data_blip_run6_G10->SetMarkerColor(97);//G10 Rn
data_blip_run6_G10Exc->SetLineColor(54); data_blip_run6_G10Exc->SetMarkerColor(54);//Non-G10 Rn


//gammas_blip_EShifted_Xperc_G10_mc->SetLineColor(2) ; gammas_blip_EShifted_Xperc_G10_mc->SetMarkerColor(2) ;
//gammas_blip_EnergyShift_Xperc_overlay->SetLineColor(4) ; gammas_blip_EnergyShift_Xperc_overlay->SetMarkerColor(4) ;
//gammas_blip_EnergyShift_Xperc_mc->SetLineColor(1) ; gammas_blip_EnergyShift_Xperc_mc->SetMarkerColor(1) ;




//=====================================================================================================================================
/*
cout<<"data3 G10 2.6MeV entries "<<data_blip_run3_G10->GetEntries()<<endl;
cout<<"Data3  NonG10 2.6MeV entries "<<data_blip_run3_G10Exc->GetEntries()<<endl;
cout<<"Data3 hdiff  entries "<<hDiffRun3->GetEntries()<< " Integral: "<< hDiffRun3->GetIntegral() <<endl;


cout<<"GAMMAS G10 2.6MeV entries "<<gammas_blip_EShifted_Xperc_G10->GetEntries()<<endl;
cout<<"GAMMAS NonG10 2.6MeV entries "<<gammas_blip_EShifted_Xperc_G10Exc->GetEntries()<<endl;
cout<<"GAMMAS 2.6MeV entries "<<hDiffMCGammas->GetEntries()<< " Integral: "<< hDiffMCGammas->GetIntegral() <<endl;

cout<<"Neutrons G10 2.6MeV entries "<<neutrons_blip_EShifted_Xperc_G10->GetEntries()<<endl;
cout<<"Neutrons 2.6MeV entries "<<neutrons_blip_EShifted_Xperc_G10Exc->GetEntries()<<endl;
cout<<"Neutrons hdiff entries "<<hDiffMCNeutrons->GetEntries()<< " Integral: "<< hDiffMCGammas->GetIntegral() <<endl;
*/
//========================================================
// Bkg subtraction plots
//========================================================
Plot_Bkg(data_blip_run3_G10, data_blip_run3_G10Exc, hDiffRun3, "Run 3 Data Blips", "Run3", mainDir, dir, AddNeutrons,  EShift, SpectrumNormF, plot );  //SpectrumNormF or SpectrumNormFRun6 either 

Plot_Bkg(data_blip_run6_G10, data_blip_run6_G10Exc, hDiffRun6, "Run 6 Data Blips", "Run6", mainDir, dir, AddNeutrons,  EShift, SpectrumNormFRun6, plot );

//Only mc component for gammas and neutrons

Plot_Bkg(gammas_blip_EShifted_Xperc_G10_mc, gammas_blip_EShifted_Xperc_G10Exc_mc, hDiffMCGammas, "2.6MeV-Gamma Blips", "2.6MeV-Gammas", mainDir, dir, AddNeutrons, EShift, SpectrumNormF, plot );

Plot_Bkg(neutrons_blip_EShifted_Xperc_G10_mc, neutrons_blip_EShifted_Xperc_G10Exc_mc, hDiffMCNeutrons, "1eV-Neutron Blips", "1eV-Neutrons", mainDir, dir, AddNeutrons,  EShift, SpectrumNormF, plot );

Plot_Bkg(gammasK40_blip_EShifted_Xperc_G10_mc, gammasK40_blip_EShifted_Xperc_G10Exc_mc, hDiffMCK40Gammas, "1.4MeV-Gamma Blips", "1.4MeV-Gammas", mainDir, dir, AddNeutrons, EShift, SpectrumNormF, plot );



//==============================================
// EShift and Chi2 calculation
//==============================================


double CHI2; int NDF; 

Plot_EShift(hDiffRun3, hDiffMCGammas, hDiffMCNeutrons, hDiffMCK40Gammas, 3 ,"Run 3 Data ", "run3data",  mainDir, dir,  EShift, SpectrumNormF, /*srux1*/0,/*srux2*/ 5, /*sruy1*/ 0 ,/*sruy2*/ 7000, AddNeutrons, AddK40Gammas, plot, isMCOverlay , x1_fit, x2_fit );
/*
chi2_energyshift_run3<<EShift<<"\t"<<SpectrumNormF<<"\t" <<CHI2<<"\t"<<endl;
chi2NDF_energyshift_run3<<EShift<<"\t"<<SpectrumNormF<<"\t"<<CHI2/NDF<<"\t"<<endl;
*/       
//else cout<<"Not run3  Chi2: "<<Chi2<<"  ndf: "<<ndf<<endl ;




Plot_EShift(hDiffRun6, hDiffMCGammas, hDiffMCNeutrons, hDiffMCK40Gammas, 6 ,"Run 6 Data ", "run6data",  mainDir, dir,  EShift, SpectrumNormFRun6,/*srux1*/0,/*srux2*/ 5,/*sruy1*/ 0 ,/*sruy2*/  800, AddNeutrons, AddK40Gammas, plot, isMCOverlay , x1_fit, x2_fit );
/*
chi2_energyshift_run6<<EShift<<"\t"<<SpectrumNormFRun6<<"\t" <<CHI2<<"\t"<<endl;
chi2NDF_energyshift_run6<<EShift<<"\t"<<SpectrumNormFRun6<<"\t"<<CHI2/NDF<<"\t"<<endl;
*/

//============================================================================================================




//================================================
//   Relative Shift Run3 and radon
//================================================


Plot_Histograms(hDiffRun3, hDiffRun6, "Relative Shift", "relshiftrun3-6", mainDir, dir, AddNeutrons,  EShift, SpectrumNormF );



if(isMCOverlay == 1 && plot == 1){

Plot_Components(gammas_blip_EShifted_Xperc_G10, gammas_blip_EShifted_Xperc_G10_mc, gammas_blip_EShifted_Xperc_G10_overlay, gammas_blip_EShifted_Xperc_G10_mc_eminus, gammas_blip_EShifted_Xperc_G10_mc_eplus, "2.6 MeV Gammas ", "componentsGammas", mainDir, dir, AddNeutrons, 0, 5, EShift, SpectrumNormF );

Plot_Components(neutrons_blip_EShifted_Xperc_G10, neutrons_blip_EShifted_Xperc_G10_mc, neutrons_blip_EShifted_Xperc_G10_overlay, neutrons_blip_EShifted_Xperc_G10_mc_eminus, neutrons_blip_EShifted_Xperc_G10_mc_eplus, " 1.0 eV Neutrons", "componentsNeutrons", mainDir, dir, AddNeutrons, 0, 5,  EShift, SpectrumNormF );

Plot_Components(gammasK40_blip_EShifted_Xperc_G10, gammasK40_blip_EShifted_Xperc_G10_mc, gammasK40_blip_EShifted_Xperc_G10_overlay, gammasK40_blip_EShifted_Xperc_G10_mc_eminus, gammasK40_blip_EShifted_Xperc_G10_mc_eplus, "1.4 MeV Gammas ", "componentsK40Gammas", mainDir, dir, AddNeutrons, 0, 5, EShift, SpectrumNormF );



Plot_Components_Process( gammas_blip_EShifted_Xperc_G10_mc,  gammas_blip_EShifted_Xperc_G10_mc_primary, gammas_blip_EShifted_Xperc_G10_mc_compton, gammas_blip_EShifted_Xperc_G10_mc_photoe ,gammas_blip_EShifted_Xperc_G10_mc_pairprod, gammas_blip_EShifted_Xperc_G10_mc_otherproc," 2.6 MeV Gammas", "processcomponents2pt6Gammas", mainDir, dir, AddNeutrons, 0, 5,  EShift, SpectrumNormF );

Plot_Components_Process( neutrons_blip_EShifted_Xperc_G10_mc,  neutrons_blip_EShifted_Xperc_G10_mc_primary, neutrons_blip_EShifted_Xperc_G10_mc_compton, neutrons_blip_EShifted_Xperc_G10_mc_photoe ,neutrons_blip_EShifted_Xperc_G10_mc_pairprod, neutrons_blip_EShifted_Xperc_G10_mc_otherproc," 1.0 eV Neutrons", "processcomponentsNeutrons", mainDir, dir, AddNeutrons, 0, 5,  EShift, SpectrumNormF );

Plot_Components_Process( gammasK40_blip_EShifted_Xperc_G10_mc,  gammasK40_blip_EShifted_Xperc_G10_mc_primary, gammasK40_blip_EShifted_Xperc_G10_mc_compton, gammasK40_blip_EShifted_Xperc_G10_mc_photoe ,gammasK40_blip_EShifted_Xperc_G10_mc_pairprod, gammasK40_blip_EShifted_Xperc_G10_mc_otherproc," 1.4 MeV Gammas", "processcomponents1pt4Gammas", mainDir, dir, AddNeutrons, 0, 5,  EShift, SpectrumNormF );




//Plot_Components_Process_Stk( neutrons_blip_EShifted_Xperc_G10_mc,  neutrons_blip_EShifted_Xperc_G10_mc_primary, neutrons_blip_EShifted_Xperc_G10_mc_compton, neutrons_blip_EShifted_Xperc_G10_mc_photoe ,neutrons_blip_EShifted_Xperc_G10_mc_pairprod, neutrons_blip_EShifted_Xperc_G10_mc_otherproc," 1.0 eV Neutrons", "processcomponentsNeutrons", mainDir, dir, AddNeutrons,  EShift, SpectrumNormF );





}












/*
fileG10 ->Close();
fileG10Exc ->Close();
file ->Close();
file1 ->Close();
file2 ->Close();
file3 ->Close();
file4 ->Close();
*/

}
