#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"




void pt_Eff_Master_cuts_DY( TString myMethodList = "" )
{
   float lumi = 1.;
   gStyle->SetOptStat(0);


   TString WeightExpression ="";
   TString optcut1_WeightExpression ="";
   TString optcut2_WeightExpression ="";
   TString optcut3_WeightExpression ="";


   WeightExpression += "TagMuonPOGRelPFIsoDBCorrR04<.15";
   optcut1_WeightExpression += "TagMuonPOGRelPFIsoDBCorrR04<.15&&TagMuonSIP3D<4.0";
   optcut2_WeightExpression += "TagMuonPOGRelPFIsoDBCorrR04<.15&&TagMuonJetCSV<0.7";
   optcut3_WeightExpression += "TagMuonPOGRelPFIsoDBCorrR04<.15&&TagMuonJetCSV<0.7&&TagMuonSIP3D<4.0";

   double fake_events = 0.0;
   double nonfake_events = 0.0;


   /////////////////////////////
   // Add MC Background Trees //
   /////////////////////////////


   TFile *fakes_input = TFile::Open( "/cms/mchristos/ANN/FireMVA/DY_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input->GetName() <<         std::endl;

   TFile *nonfakes_input = TFile::Open( "/cms/mchristos/ANN/FireMVA/DY_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input->GetName() <<         std::endl;
   
   TTree *fakes = (TTree*)fakes_input->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes = (TTree*)nonfakes_input->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_histo= new TH1D("fakes_histo","fakes_histo",20,0,100);
   TH1D *fakes_histo_cut= new TH1D("fakes_histo_cut","fakes_histo_cut",20,0,100);

   TH1D *nonfakes_histo= new TH1D("nonfakes_histo","nonfakes_histo",20,0,100);
   TH1D *nonfakes_histo_cut= new TH1D("nonfakes_histo_cut","nonfakes_histo_cut",20,0,100);
   
   fakes->Draw("(TagMuonPt)>>fakes_histo");
   nonfakes->Draw("(TagMuonPt)>>nonfakes_histo");

   fakes->Draw("(TagMuonPt)>>fakes_histo_cut",WeightExpression);
   nonfakes->Draw("(TagMuonPt)>>nonfakes_histo_cut",WeightExpression);
   

   fake_events += fakes_histo->Integral()*lumi;
   fakes_histo->Scale(lumi);


   nonfake_events += nonfakes_histo->Integral()*lumi;
   nonfakes_histo->Scale(lumi);
         
   cout<<"Cutting on Isolation"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after cut): "<<fakes_histo_cut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after cut): "<<nonfakes_histo_cut->Integral()*lumi<<endl;
   
   TCanvas *cst = new TCanvas("cst","stacked hists",10,100,700,700);

   fakes_histo->Draw("HIST");
   fakes_histo->SetLineWidth(2);
   fakes_histo->SetMarkerStyle(1);
   fakes_histo->SetLineColor(kRed);

   nonfakes_histo->Draw("SAME HIST");
   nonfakes_histo->SetLineWidth(2);
   nonfakes_histo->SetLineColor(kBlue);

   fakes_histo->GetXaxis()->SetTitle("P_{T}");

   cst->Update();

   TLegend *legend=new TLegend(0.5,0.5,.9,.9);
   legend->AddEntry(fakes_histo,("Fakes - Integral: "+std::to_string(fakes_histo->Integral())).c_str());
   legend->AddEntry(nonfakes_histo,("NonFakes - Integral: "+std::to_string(nonfakes_histo->Integral())).c_str());
   
   
   
   
   legend->Draw();

   cst->SaveAs("optcutsDY_fakes.png");
   
   //////////////////////////////////
   // Add MC Cuts Based analysis 1 //
   //////////////////////////////////


   TH1D *fakes_histo_optcut1= new TH1D("fakes_histo_optcut1","fakes_histo_optcut1",20,0,100);

   TH1D *nonfakes_histo_optcut1= new TH1D("nonfakes_histo_optcut1","nonfakes_histo_optcut1",20,0,100);
   

   fakes->Draw("(TagMuonPt)>>fakes_histo_optcut1",optcut1_WeightExpression);
   nonfakes->Draw("(TagMuonPt)>>nonfakes_histo_optcut1",optcut1_WeightExpression);
   
   fake_events = 0;
   fake_events += fakes_histo->Integral()*lumi;
   fakes_histo->Scale(lumi);

   nonfake_events = 0;
   nonfake_events += nonfakes_histo->Integral()*lumi;
   nonfakes_histo->Scale(lumi);
         
   cout<<"Optimized Cutting"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after cut): "<<fakes_histo_optcut1->Integral()*lumi<<endl;
   cout<<"nonfake Events (after cut): "<<nonfakes_histo_optcut1->Integral()*lumi<<endl;

   //////////////////////////////////
   // Add MC Cuts Based analysis 2 //
   //////////////////////////////////


   TH1D *fakes_histo_optcut2= new TH1D("fakes_histo_optcut2","fakes_histo_optcut2",20,0,100);

   TH1D *nonfakes_histo_optcut2= new TH1D("nonfakes_histo_optcut2","nonfakes_histo_optcut2",20,0,100);
   

   fakes->Draw("(TagMuonPt)>>fakes_histo_optcut2",optcut2_WeightExpression);
   nonfakes->Draw("(TagMuonPt)>>nonfakes_histo_optcut2",optcut2_WeightExpression);
   
   fake_events = 0;
   fake_events += fakes_histo->Integral()*lumi;
   fakes_histo->Scale(lumi);

   nonfake_events = 0;
   nonfake_events += nonfakes_histo->Integral()*lumi;
   nonfakes_histo->Scale(lumi);
         
   cout<<"Optimized Cutting"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after cut): "<<fakes_histo_optcut2->Integral()*lumi<<endl;
   cout<<"nonfake Events (after cut): "<<nonfakes_histo_optcut2->Integral()*lumi<<endl;


   //////////////////////////////////
   // Add MC Cuts Based analysis 3 //
   //////////////////////////////////


   TH1D *fakes_histo_optcut3= new TH1D("fakes_histo_optcut3","fakes_histo_optcut3",20,0,100);

   TH1D *nonfakes_histo_optcut3= new TH1D("nonfakes_histo_optcut3","nonfakes_histo_optcut3",20,0,100);
   

   fakes->Draw("(TagMuonPt)>>fakes_histo_optcut3",optcut3_WeightExpression);
   nonfakes->Draw("(TagMuonPt)>>nonfakes_histo_optcut3",optcut3_WeightExpression);
   
   fake_events = 0;
   fake_events += fakes_histo->Integral()*lumi;
   fakes_histo->Scale(lumi);

   nonfake_events = 0;
   nonfake_events += nonfakes_histo->Integral()*lumi;
   nonfakes_histo->Scale(lumi);
         
   cout<<"Optimized Cutting"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after cut): "<<fakes_histo_optcut3->Integral()*lumi<<endl;
   cout<<"nonfake Events (after cut): "<<nonfakes_histo_optcut3->Integral()*lumi<<endl;

   ////////////////////////////
   //    Plots             ////
   ////////////////////////////

   TCanvas *Pteff_fakes = new TCanvas("Pteff_fakes","Pteff_fakes",10,100,700,700);
   Pteff_fakes->SetLogy();
   
   TGraphAsymmErrors *Pt_ratio_iso_fakes = new TGraphAsymmErrors("Pt_ratio_iso_fakes","Pt_ratio_iso_fakes");
   Pt_ratio_iso_fakes->Divide(fakes_histo_cut,fakes_histo);
   Pt_ratio_iso_fakes->SetMarkerStyle(20);
   Pt_ratio_iso_fakes->SetMarkerColor(kRed+1);

   TGraphAsymmErrors *Pt_ratio_optcut1_fakes = new TGraphAsymmErrors("Pt_ratio_optcut1_fakes","Pt_ratio_optcut1_fakes");
   Pt_ratio_optcut1_fakes->Divide(fakes_histo_optcut1,fakes_histo);
   Pt_ratio_optcut1_fakes->SetMarkerStyle(20);
   Pt_ratio_optcut1_fakes->SetMarkerColor(kOrange+1);

   TGraphAsymmErrors *Pt_ratio_optcut2_fakes = new TGraphAsymmErrors("Pt_ratio_optcut2_fakes","Pt_ratio_optcut2_fakes");
   Pt_ratio_optcut2_fakes->Divide(fakes_histo_optcut2,fakes_histo);
   Pt_ratio_optcut2_fakes->SetMarkerStyle(20);
   Pt_ratio_optcut2_fakes->SetMarkerColor(kViolet-5);

   TGraphAsymmErrors *Pt_ratio_optcut3_fakes = new TGraphAsymmErrors("Pt_ratio_optcut3_fakes","Pt_ratio_optcut3_fakes");
   Pt_ratio_optcut3_fakes->Divide(fakes_histo_optcut3,fakes_histo);
   Pt_ratio_optcut3_fakes->SetMarkerStyle(20);
   Pt_ratio_optcut3_fakes->SetMarkerColor(kGreen+1);
   
 
   

   //Putting it all together...
   TMultiGraph *mg = new TMultiGraph();
   mg->Add(Pt_ratio_iso_fakes);
   mg->Add(Pt_ratio_optcut1_fakes);
   mg->Add(Pt_ratio_optcut2_fakes);
   mg->Add(Pt_ratio_optcut3_fakes);


   mg->Draw("AP");
   mg->SetTitle("Background Efficiency");
   mg->GetXaxis()->SetTitle("P_{T} (GeV)");
   mg->GetYaxis()->SetTitle("Efficiency");

   TLegend *legend_fakes=new TLegend(0.5,0.5,.9,.9);
   legend_fakes->AddEntry(Pt_ratio_iso_fakes,"reliso<0.15");
   legend_fakes->AddEntry(Pt_ratio_optcut1_fakes,"reliso<0.15 && sip3d<4");
   legend_fakes->AddEntry(Pt_ratio_optcut2_fakes,"reliso<0.15 && jetcsv<0.7");
   legend_fakes->AddEntry(Pt_ratio_optcut3_fakes,"reliso<0.15 && sip3d<4 & jetcsv<0.7");

   legend_fakes->SetBorderSize(0);

   legend_fakes->Draw("AP");

   Pteff_fakes->SaveAs("optcuts_DY_fakes.png");

   TCanvas *Pteff_nonfakes = new TCanvas("Pteff_nonfakes","Pteff_nonfakes",10,100,700,700);
   //Pteff_nonfakes->SetLogy();
   
   TGraphAsymmErrors *Pt_ratio_iso_nonfakes = new TGraphAsymmErrors("Pt_ratio_iso_nonfakes","Pt_ratio_iso_nonfakes");
   Pt_ratio_iso_nonfakes->Divide(nonfakes_histo_cut,nonfakes_histo);
   Pt_ratio_iso_nonfakes->SetMarkerStyle(20);
   Pt_ratio_iso_nonfakes->SetMarkerColor(kRed+1);

   TGraphAsymmErrors *Pt_ratio_optcut1_nonfakes = new TGraphAsymmErrors("Pt_ratio_optcut1_nonfakes","Pt_ratio_optcut1_nonfakes");
   Pt_ratio_optcut1_nonfakes->Divide(nonfakes_histo_optcut1,nonfakes_histo);
   Pt_ratio_optcut1_nonfakes->SetMarkerStyle(20);
   Pt_ratio_optcut1_nonfakes->SetMarkerColor(kOrange+1);

   TGraphAsymmErrors *Pt_ratio_optcut2_nonfakes = new TGraphAsymmErrors("Pt_ratio_optcut2_nonfakes","Pt_ratio_optcut2_nonfakes");
   Pt_ratio_optcut2_nonfakes->Divide(nonfakes_histo_optcut2,nonfakes_histo);
   Pt_ratio_optcut2_nonfakes->SetMarkerStyle(20);
   Pt_ratio_optcut2_nonfakes->SetMarkerColor(kViolet-5);

   TGraphAsymmErrors *Pt_ratio_optcut3_nonfakes = new TGraphAsymmErrors("Pt_ratio_optcut3_nonfakes","Pt_ratio_optcut3_nonfakes");
   Pt_ratio_optcut3_nonfakes->Divide(nonfakes_histo_optcut3,nonfakes_histo);
   Pt_ratio_optcut3_nonfakes->SetMarkerStyle(20);
   Pt_ratio_optcut3_nonfakes->SetMarkerColor(kGreen+1);
   

   

   //Putting it all together...
   TMultiGraph *mg_nonfakes = new TMultiGraph();
   mg_nonfakes->Add(Pt_ratio_iso_nonfakes);
   mg_nonfakes->Add(Pt_ratio_optcut1_nonfakes);
   mg_nonfakes->Add(Pt_ratio_optcut2_nonfakes);
   mg_nonfakes->Add(Pt_ratio_optcut3_nonfakes);


   mg_nonfakes->Draw("AP");
   mg_nonfakes->SetTitle("Signal Efficiency");
   mg_nonfakes->GetXaxis()->SetTitle("P_{T} (GeV)");
   mg_nonfakes->GetYaxis()->SetTitle("Efficiency");

   TLegend *legend_nonfakes=new TLegend(0.5,0.5,.9,.9);
   legend_nonfakes->AddEntry(Pt_ratio_iso_nonfakes,"reliso<0.15");
   legend_nonfakes->AddEntry(Pt_ratio_optcut1_nonfakes,"reliso<0.15 && sip3d<4");
   legend_nonfakes->AddEntry(Pt_ratio_optcut2_nonfakes,"reliso<0.15 && jetcsv<0.7");
   legend_nonfakes->AddEntry(Pt_ratio_optcut3_nonfakes,"reliso<0.15 && sip3d<4 & jetcsv<0.7");

   legend_nonfakes->SetBorderSize(0);

   legend_nonfakes->Draw("AP");

   Pteff_nonfakes->SaveAs("otpcuts_DY_nonfakes.png");

}

