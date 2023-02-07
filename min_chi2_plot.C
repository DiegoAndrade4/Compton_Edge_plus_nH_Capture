#include <string>
#include <iostream>
#include <stdio.h> 
#include <TMath.h>
#include <TGraph2D.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH1.h>




void min_chi2_plot(const char* dir, int ndf, const char* datatype) {

   auto c = new TCanvas("c","Run3 Chi2",0,0,600,400);
   auto g = new TGraph2D(Form("%s/chi2_energyshift_run3_%s.txt", dir, datatype));
        g->SetTitle(Form("#chi^{2} Run3 Data, NDF = %d; Energy Shift (%%); SNF; #chi^{2}", ndf));
        gStyle->SetPalette(1);
	gStyle->SetHistTopMargin(0);
       
       //g->Draw("TRIW");
       //g->Draw("surf1");
       g->Draw("tri1 p0");
       //g->Draw("PCOL");
       //g->Draw("LINE"); 
       //g->Draw("CONT5");
	c->Print(Form("%s/CHI2map-Run3-%dndf_%s.png", dir, ndf, datatype));


  auto c1 = new TCanvas("c1","Run3 Chi2NDF",0,0,600,400);
   auto g1 = new TGraph2D(Form("%s/chi2NDF_energyshift_run3_%s.txt", dir, datatype));
        g1->SetTitle(Form("#chi^{2}/NDF Run3 Data, NDF = %d; Energy Shift (%%); SNF; #chi^{2}/NDF", ndf));
        gStyle->SetPalette(1);
        gStyle->SetHistTopMargin(0);
     
       //g1->Draw("TRIW");
       //g1->Draw("surf1");
       g1->Draw("tri1 p0");
       //g1->Draw("PCOL");
       //g1->Draw("LINE");  
       //g1->Draw("CONT5");
        c1->Print(Form("%s/CHI2NDFmap-Run3-%dndf_%s.png", dir, ndf, datatype));








  auto c2 = new TCanvas("c2","Run6 Chi2",0,0,600,400);
   auto g2 = new TGraph2D(Form("%s/chi2_energyshift_run6_%s.txt", dir, datatype));
        g2->SetTitle(Form("#chi^{2} Run6 Data, NDF = %d; Energy Shift (%%); SNF; #chi^{2}", ndf));
        g2->GetXaxis()->SetLabelOffset(5.35); 
	
	gStyle->SetPalette(1);
        gStyle->SetHistTopMargin(0);
       
       //g2->Draw("TRIW");
       //g2->Draw("surf1");
       g2->Draw("tri1 p0");
       //g2->Draw("PCOL");
       //g2->Draw("LINE");
       //g2->Draw("CONT5");
        c2->Print(Form("%s/CHI2map-Run6_%dndf_%s.png", dir,ndf, datatype));


  auto c3 = new TCanvas("c3","Run6 Chi2NDF",0,0,600,400);
   auto g3 = new TGraph2D( Form("%s/chi2NDF_energyshift_run6_%s.txt", dir, datatype));
        g3->SetTitle(Form("#chi^{2}/NDF Run6 Data, NDF = %d; Energy Shift (%%); SNF; #chi^{2}/NDF", ndf));
        gStyle->SetPalette(1);
        gStyle->SetHistTopMargin(0);
       
       //g3->Draw("TRIW");
       //g3->Draw("surf1");
       g3->Draw("tri1 p0");
       //g3->Draw("PCOL");
       //g3->Draw("LINE");
       //g3->Draw("CONT5");
        c3->Print(Form("%s/CHI2NDFmap-Run6_%dndf_%s.png", dir, ndf, datatype));



}
