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




void pt_Eff_Master_ptTrain_TT( TString myMethodList = "" )
{
   float lumi = 1.;
   gStyle->SetOptStat(0);


   TString WeightExpression ="";
   TString bdt1_WeightExpression ="";
   TString bdt2_WeightExpression ="";


   WeightExpression += "TagMuonPOGRelPFIsoDBCorrR04<.15";
   bdt1_WeightExpression += "BDT>.77";
   bdt2_WeightExpression += "BDT>.78";

   double fake_events = 0.0;
   double nonfake_events = 0.0;


   /////////////////////////////
   // Add MC Background Trees //
   /////////////////////////////


   TFile *fakes_input = TFile::Open( "/cms/mchristos/ANN/FireMVA/TT_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input->GetName() <<         std::endl;

   TFile *nonfakes_input = TFile::Open( "/cms/mchristos/ANN/FireMVA/TT_NonFakeMuonTree.root" ); 
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

   cst->SaveAs("TT_ptTrain.png");
   

   ///////////////////////////
   //    Adding BDT 1       //
   ///////////////////////////

   TFile *fakes_input_bdt1 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_TT_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt1->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt1 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_TT_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt1->GetName() <<         std::endl;
   
   TTree *fakes_bdt1 = (TTree*)fakes_input_bdt1->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt1 = (TTree*)nonfakes_input_bdt1->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt1_histo= new TH1D("fakes_bdt1_histo","fakes_bdt1_histo",20,0,100);
   TH1D *fakes_bdt1_histo_cut= new TH1D("fakes_bdt1_histo_cut","fakes_bdt1_histo_cut",20,0,100);

   TH1D *nonfakes_bdt1_histo= new TH1D("nonfakes_bdt1_histo","nonfakes_bdt1_histo",20,0,100);
   TH1D *nonfakes_bdt1_histo_cut= new TH1D("nonfakes_bdt1_histo_cut","nonfakes_bdt1_histo_cut",20,0,100);
   
   fakes_bdt1->Draw("(TagMuonPt)>>fakes_bdt1_histo");
   nonfakes_bdt1->Draw("(TagMuonPt)>>nonfakes_bdt1_histo");

   fakes_bdt1->Draw("(TagMuonPt)>>fakes_bdt1_histo_cut",bdt1_WeightExpression);
   nonfakes_bdt1->Draw("(TagMuonPt)>>nonfakes_bdt1_histo_cut",bdt1_WeightExpression);
   
   fake_events=0;
   fake_events += fakes_bdt1_histo->Integral()*lumi;
   fakes_bdt1_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt1_histo->Integral()*lumi;
   nonfakes_bdt1_histo->Scale(lumi);
         
   cout<<"Cutting on BDT 1"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after cut): "<<fakes_bdt1_histo_cut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after cut): "<<nonfakes_bdt1_histo_cut->Integral()*lumi<<endl;
   
   ///////////////////////////
   //    Adding BDT 2       //
   ///////////////////////////

   TFile *fakes_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDToptimized_TT_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt2->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDToptimized_TT_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt2->GetName() <<         std::endl;
   
   TTree *fakes_bdt2 = (TTree*)fakes_input_bdt2->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt2 = (TTree*)nonfakes_input_bdt2->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt2_histo= new TH1D("fakes_bdt2_histo","fakes_bdt2_histo",20,0,100);
   TH1D *fakes_bdt2_histo_cut= new TH1D("fakes_bdt2_histo_cut","fakes_bdt2_histo_cut",20,0,100);

   TH1D *nonfakes_bdt2_histo= new TH1D("nonfakes_bdt2_histo","nonfakes_bdt2_histo",20,0,100);
   TH1D *nonfakes_bdt2_histo_cut= new TH1D("nonfakes_bdt2_histo_cut","nonfakes_bdt2_histo_cut",20,0,100);
   
   fakes_bdt2->Draw("(TagMuonPt)>>fakes_bdt2_histo");
   nonfakes_bdt2->Draw("(TagMuonPt)>>nonfakes_bdt2_histo");

   fakes_bdt2->Draw("(TagMuonPt)>>fakes_bdt2_histo_cut",bdt2_WeightExpression);
   nonfakes_bdt2->Draw("(TagMuonPt)>>nonfakes_bdt2_histo_cut",bdt2_WeightExpression);
   fake_events=0;
   fake_events += fakes_bdt2_histo->Integral()*lumi;
   fakes_bdt2_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt2_histo->Integral()*lumi;
   nonfakes_bdt2_histo->Scale(lumi);
         

   cout<<"Cutting on BDT 2"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after cut): "<<fakes_bdt2_histo_cut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after cut): "<<nonfakes_bdt2_histo_cut->Integral()*lumi<<endl;
   
   ////////////////////////////
   //    Plots             ////
   ////////////////////////////

   TCanvas *Pteff_fakes = new TCanvas("Pteff_fakes","Pteff_fakes",10,100,700,700);
   Pteff_fakes->SetLogy();

   TGraphAsymmErrors *Pt_ratio_iso_fakes = new TGraphAsymmErrors("Pt_ratio_iso_fakes","Pt_ratio_iso_fakes");
   Pt_ratio_iso_fakes->Divide(fakes_histo_cut,fakes_histo);
   Pt_ratio_iso_fakes->SetMarkerStyle(20);
   Pt_ratio_iso_fakes->SetMarkerColor(kBlue);
   
   TGraphAsymmErrors *Pt_ratio_bdt1_fakes = new TGraphAsymmErrors("Pt_ratio_bdt1_fakes","Pt_ratio_bdt1_fakes");
   Pt_ratio_bdt1_fakes->Divide(fakes_bdt1_histo_cut,fakes_bdt1_histo);
   Pt_ratio_bdt1_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt1_fakes->SetMarkerColor(kRed);

   TGraphAsymmErrors *Pt_ratio_bdt2_fakes = new TGraphAsymmErrors("Pt_ratio_bdt2_fakes","Pt_ratio_bdt2_fakes");
   Pt_ratio_bdt2_fakes->Divide(fakes_bdt2_histo_cut,fakes_bdt2_histo);
   Pt_ratio_bdt2_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt2_fakes->SetMarkerColor(kGreen);

   

   

   //Putting it all together...
   TMultiGraph *mg = new TMultiGraph();
   mg->Add(Pt_ratio_iso_fakes);
   mg->Add(Pt_ratio_bdt1_fakes);
   mg->Add(Pt_ratio_bdt2_fakes);


   mg->Draw("AP");
   mg->SetTitle("Background Efficiency");
   mg->GetXaxis()->SetTitle("P_{T} (GeV)");
   mg->GetYaxis()->SetTitle("Efficiency");

   TLegend *legend_fakes=new TLegend(0.5,0.5,.9,.9);
   legend_fakes->AddEntry(Pt_ratio_iso_fakes,"Cutting on Isolation");
   legend_fakes->AddEntry(Pt_ratio_bdt1_fakes,"Cutting on Opt. BDT (no MuonPt)");
   legend_fakes->AddEntry(Pt_ratio_bdt2_fakes,"Cutting on Opt. BDT (including MuonPt)");
   legend_fakes->SetBorderSize(0);
   legend_fakes->Draw("AP");

   Pteff_fakes->SaveAs("PtTrain_TT_fakes.png");



   TCanvas *Pteff_nonfakes = new TCanvas("Pteff_nonfakes","Pteff_nonfakes",10,100,700,700);
   //Pteff_nonfakes->SetLogy();
   TGraphAsymmErrors *Pt_ratio_iso_nonfakes = new TGraphAsymmErrors("Pt_ratio_iso_nonfakes","Pt_ratio_iso_nonfakes");
   Pt_ratio_iso_nonfakes->Divide(nonfakes_histo_cut,nonfakes_histo);
   Pt_ratio_iso_nonfakes->SetMarkerStyle(20);
   Pt_ratio_iso_nonfakes->SetMarkerColor(kBlue);
   
   TGraphAsymmErrors *Pt_ratio_bdt1_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt1_nonfakes","Pt_ratio_bdt1_nonfakes");
   Pt_ratio_bdt1_nonfakes->Divide(nonfakes_bdt1_histo_cut,nonfakes_bdt1_histo);
   Pt_ratio_bdt1_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt1_nonfakes->SetMarkerColor(kRed);

   TGraphAsymmErrors *Pt_ratio_bdt2_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt2_nonfakes","Pt_ratio_bdt2_nonfakes");
   Pt_ratio_bdt2_nonfakes->Divide(nonfakes_bdt2_histo_cut,nonfakes_bdt2_histo);
   Pt_ratio_bdt2_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt2_nonfakes->SetMarkerColor(kGreen);

   

   //Putting it all together...
   TMultiGraph *mg_nonfakes = new TMultiGraph();
   mg_nonfakes->Add(Pt_ratio_iso_nonfakes);
   mg_nonfakes->Add(Pt_ratio_bdt1_nonfakes);
   mg_nonfakes->Add(Pt_ratio_bdt2_nonfakes);

   mg_nonfakes->Draw("AP");
   mg_nonfakes->SetTitle("Signal Efficiency");
   mg_nonfakes->GetXaxis()->SetTitle("P_{T} (GeV)");
   mg_nonfakes->GetYaxis()->SetTitle("Efficiency");

   TLegend *legend_nonfakes=new TLegend(0.5,0.5,.9,.9);
   legend_nonfakes->AddEntry(Pt_ratio_iso_nonfakes,"Cutting on Isolation");
   legend_nonfakes->AddEntry(Pt_ratio_bdt1_nonfakes,"Cutting on Opt. BDT (no MuonPt)");
   legend_nonfakes->AddEntry(Pt_ratio_bdt2_nonfakes,"Cutting on Opt. BDT (including MuonPt)");
   legend_nonfakes->SetBorderSize(0);
   legend_nonfakes->Draw("AP");

   Pteff_nonfakes->SaveAs("Pt_Train_nonfakes.png");

   
   //g->GetXaxis()->SetTitle("Pt Cut");
   //g->GetYaxis()->SetTitle("Efficiency (Fakes)");
   //Pteff->SaveAs("Pt_Eff.png");

}

