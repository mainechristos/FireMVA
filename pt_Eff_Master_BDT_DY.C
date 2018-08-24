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




void pt_Eff_Master_BDT_DY( TString myMethodList = "" )
{
   float lumi = 1.;
   gStyle->SetOptStat(0);


   TString bdt1_WeightExpression ="";
   TString bdt2_WeightExpression ="";
   TString bdt3_WeightExpression ="";
   TString bdt4_WeightExpression ="";
   TString bdt5_WeightExpression ="";


   bdt1_WeightExpression += "BDT>.807";
   bdt2_WeightExpression += "BDT>.67";
   bdt3_WeightExpression += "BDT>.39";
   bdt4_WeightExpression += "BDT>-.2";
   bdt5_WeightExpression += "BDT>-.91";

   double fake_events = 0.0;
   double nonfake_events = 0.0;


   

   ///////////////////////////
   //    Adding BDT 1       //
   ///////////////////////////

   TFile *fakes_input_bdt1 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt1->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt1 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt1->GetName() <<         std::endl;
   
   TTree *fakes_bdt1 = (TTree*)fakes_input_bdt1->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt1 = (TTree*)nonfakes_input_bdt1->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt1_histo= new TH1D("fakes_bdt1_histo","fakes_bdt1_histo",20,0,100);
   TH1D *fakes_bdt1_histo_ptcut= new TH1D("fakes_bdt1_histo_ptcut","fakes_bdt1_histo_ptcut",20,0,100);

   TH1D *nonfakes_bdt1_histo= new TH1D("nonfakes_bdt1_histo","nonfakes_bdt1_histo",20,0,100);
   TH1D *nonfakes_bdt1_histo_ptcut= new TH1D("nonfakes_bdt1_histo_ptcut","nonfakes_bdt1_histo_ptcut",20,0,100);
   
   fakes_bdt1->Draw("(TagMuonPt)>>fakes_bdt1_histo");
   nonfakes_bdt1->Draw("(TagMuonPt)>>nonfakes_bdt1_histo");

   fakes_bdt1->Draw("(TagMuonPt)>>fakes_bdt1_histo_ptcut",bdt1_WeightExpression);
   nonfakes_bdt1->Draw("(TagMuonPt)>>nonfakes_bdt1_histo_ptcut",bdt1_WeightExpression);
   

   fake_events += fakes_bdt1_histo->Integral()*lumi;
   fakes_bdt1_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt1_histo->Integral()*lumi;
   nonfakes_bdt1_histo->Scale(lumi);
         
   cout<<"Cutting on BDT1"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after Pt cut): "<<fakes_bdt1_histo_ptcut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after Pt cut): "<<nonfakes_bdt1_histo_ptcut->Integral()*lumi<<endl;
   

   ///////////////////////////
   //    Adding BDT 2       //
   ///////////////////////////

   TFile *fakes_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt2->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt2->GetName() <<         std::endl;
   
   TTree *fakes_bdt2 = (TTree*)fakes_input_bdt2->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt2 = (TTree*)nonfakes_input_bdt2->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt2_histo= new TH1D("fakes_bdt2_histo","fakes_bdt2_histo",20,0,100);
   TH1D *fakes_bdt2_histo_ptcut= new TH1D("fakes_bdt2_histo_ptcut","fakes_bdt2_histo_ptcut",20,0,100);

   TH1D *nonfakes_bdt2_histo= new TH1D("nonfakes_bdt2_histo","nonfakes_bdt2_histo",20,0,100);
   TH1D *nonfakes_bdt2_histo_ptcut= new TH1D("nonfakes_bdt2_histo_ptcut","nonfakes_bdt2_histo_ptcut",20,0,100);
   
   fakes_bdt2->Draw("(TagMuonPt)>>fakes_bdt2_histo");
   nonfakes_bdt2->Draw("(TagMuonPt)>>nonfakes_bdt2_histo");

   fakes_bdt2->Draw("(TagMuonPt)>>fakes_bdt2_histo_ptcut",bdt2_WeightExpression);
   nonfakes_bdt2->Draw("(TagMuonPt)>>nonfakes_bdt2_histo_ptcut",bdt2_WeightExpression);
   fake_events=0;
   fake_events += fakes_bdt2_histo->Integral()*lumi;
   fakes_bdt2_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt2_histo->Integral()*lumi;
   nonfakes_bdt2_histo->Scale(lumi);
         

   cout<<"Cutting on BDT2"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after Pt cut): "<<fakes_bdt2_histo_ptcut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after Pt cut): "<<nonfakes_bdt2_histo_ptcut->Integral()*lumi<<endl;

   ///////////////////////////
   //    Adding BDT 3       //
   ///////////////////////////

   TFile *fakes_input_bdt3 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt3->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt3 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt3->GetName() <<         std::endl;
   
   TTree *fakes_bdt3 = (TTree*)fakes_input_bdt3->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt3 = (TTree*)nonfakes_input_bdt3->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt3_histo= new TH1D("fakes_bdt3_histo","fakes_bdt3_histo",20,0,100);
   TH1D *fakes_bdt3_histo_ptcut= new TH1D("fakes_bdt3_histo_ptcut","fakes_bdt3_histo_ptcut",20,0,100);

   TH1D *nonfakes_bdt3_histo= new TH1D("nonfakes_bdt3_histo","nonfakes_bdt3_histo",20,0,100);
   TH1D *nonfakes_bdt3_histo_ptcut= new TH1D("nonfakes_bdt3_histo_ptcut","nonfakes_bdt3_histo_ptcut",20,0,100);
   
   fakes_bdt3->Draw("(TagMuonPt)>>fakes_bdt3_histo");
   nonfakes_bdt3->Draw("(TagMuonPt)>>nonfakes_bdt3_histo");

   fakes_bdt3->Draw("(TagMuonPt)>>fakes_bdt3_histo_ptcut",bdt3_WeightExpression);
   nonfakes_bdt3->Draw("(TagMuonPt)>>nonfakes_bdt3_histo_ptcut",bdt3_WeightExpression);
   
   fake_events=0;
   fake_events += fakes_bdt3_histo->Integral()*lumi;
   fakes_bdt3_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt3_histo->Integral()*lumi;
   nonfakes_bdt3_histo->Scale(lumi);
         
   cout<<"Cutting on BDT3"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after Pt cut): "<<fakes_bdt3_histo_ptcut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after Pt cut): "<<nonfakes_bdt3_histo_ptcut->Integral()*lumi<<endl;

   ///////////////////////////
   //    Adding BDT 4       //
   ///////////////////////////

   TFile *fakes_input_bdt4 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt4->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt4 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt4->GetName() <<         std::endl;
   
   TTree *fakes_bdt4 = (TTree*)fakes_input_bdt4->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt4 = (TTree*)nonfakes_input_bdt4->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt4_histo= new TH1D("fakes_bdt4_histo","fakes_bdt4_histo",20,0,100);
   TH1D *fakes_bdt4_histo_ptcut= new TH1D("fakes_bdt4_histo_ptcut","fakes_bdt4_histo_ptcut",20,0,100);

   TH1D *nonfakes_bdt4_histo= new TH1D("nonfakes_bdt4_histo","nonfakes_bdt4_histo",20,0,100);
   TH1D *nonfakes_bdt4_histo_ptcut= new TH1D("nonfakes_bdt4_histo_ptcut","nonfakes_bdt4_histo_ptcut",20,0,100);
   
   fakes_bdt4->Draw("(TagMuonPt)>>fakes_bdt4_histo");
   nonfakes_bdt4->Draw("(TagMuonPt)>>nonfakes_bdt4_histo");

   fakes_bdt4->Draw("(TagMuonPt)>>fakes_bdt4_histo_ptcut",bdt4_WeightExpression);
   nonfakes_bdt4->Draw("(TagMuonPt)>>nonfakes_bdt4_histo_ptcut",bdt4_WeightExpression);
   
   fake_events=0;
   fake_events += fakes_bdt4_histo->Integral()*lumi;
   fakes_bdt4_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt4_histo->Integral()*lumi;
   nonfakes_bdt4_histo->Scale(lumi);
         
   cout<<"Cutting on BDT4"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after Pt cut): "<<fakes_bdt4_histo_ptcut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after Pt cut): "<<nonfakes_bdt4_histo_ptcut->Integral()*lumi<<endl;

   ///////////////////////////
   //    Adding BDT 5       //
   ///////////////////////////

   TFile *fakes_input_bdt5 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input_bdt5->GetName() <<         std::endl;

   TFile *nonfakes_input_bdt5 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input_bdt5->GetName() <<         std::endl;
   
   TTree *fakes_bdt5 = (TTree*)fakes_input_bdt5->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes_bdt5 = (TTree*)nonfakes_input_bdt5->Get("rootTupleTreeVeryLoose/tree");
   
   
   TH1D *fakes_bdt5_histo= new TH1D("fakes_bdt5_histo","fakes_bdt5_histo",20,0,100);
   TH1D *fakes_bdt5_histo_ptcut= new TH1D("fakes_bdt5_histo_ptcut","fakes_bdt5_histo_ptcut",20,0,100);

   TH1D *nonfakes_bdt5_histo= new TH1D("nonfakes_bdt5_histo","nonfakes_bdt5_histo",20,0,100);
   TH1D *nonfakes_bdt5_histo_ptcut= new TH1D("nonfakes_bdt5_histo_ptcut","nonfakes_bdt5_histo_ptcut",20,0,100);
   
   fakes_bdt5->Draw("(TagMuonPt)>>fakes_bdt5_histo");
   nonfakes_bdt5->Draw("(TagMuonPt)>>nonfakes_bdt5_histo");

   fakes_bdt5->Draw("(TagMuonPt)>>fakes_bdt5_histo_ptcut",bdt5_WeightExpression);
   nonfakes_bdt5->Draw("(TagMuonPt)>>nonfakes_bdt5_histo_ptcut",bdt5_WeightExpression);
   
   fake_events=0;
   fake_events += fakes_bdt5_histo->Integral()*lumi;
   fakes_bdt5_histo->Scale(lumi);

   nonfake_events=0;
   nonfake_events += nonfakes_bdt5_histo->Integral()*lumi;
   nonfakes_bdt5_histo->Scale(lumi);
         
   cout<<"Cutting on BDT5"<<endl;
   cout<<"fake Events (total): "<<fake_events<<endl;
   cout<<"nonfake Events (total): "<<nonfake_events<<endl;
   cout<<"fake Events (after Pt cut): "<<fakes_bdt5_histo_ptcut->Integral()*lumi<<endl;
   cout<<"nonfake Events (after Pt cut): "<<nonfakes_bdt5_histo_ptcut->Integral()*lumi<<endl;

   ////////////////////////////
   //    Plots             ////
   ////////////////////////////

   TCanvas *Pteff_fakes = new TCanvas("Pteff_fakes","Pteff_fakes",10,100,700,700);
   Pteff_fakes->SetLogy();

   
   TGraphAsymmErrors *Pt_ratio_bdt1_fakes = new TGraphAsymmErrors("Pt_ratio_bdt1_fakes","Pt_ratio_bdt1_fakes");
   Pt_ratio_bdt1_fakes->Divide(fakes_bdt1_histo_ptcut,fakes_bdt1_histo);
   Pt_ratio_bdt1_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt1_fakes->SetMarkerColor(kRed);

   TGraphAsymmErrors *Pt_ratio_bdt2_fakes = new TGraphAsymmErrors("Pt_ratio_bdt2_fakes","Pt_ratio_bdt2_fakes");
   Pt_ratio_bdt2_fakes->Divide(fakes_bdt2_histo_ptcut,fakes_bdt2_histo);
   Pt_ratio_bdt2_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt2_fakes->SetMarkerColor(kBlue);

   TGraphAsymmErrors *Pt_ratio_bdt3_fakes = new TGraphAsymmErrors("Pt_ratio_bdt3_fakes","Pt_ratio_bdt3_fakes");
   Pt_ratio_bdt3_fakes->Divide(fakes_bdt3_histo_ptcut,fakes_bdt3_histo);
   Pt_ratio_bdt3_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt3_fakes->SetMarkerColor(kMagenta-1);

   TGraphAsymmErrors *Pt_ratio_bdt4_fakes = new TGraphAsymmErrors("Pt_ratio_bdt4_fakes","Pt_ratio_bdt4_fakes");
   Pt_ratio_bdt4_fakes->Divide(fakes_bdt4_histo_ptcut,fakes_bdt4_histo);
   Pt_ratio_bdt4_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt4_fakes->SetMarkerColor(kOrange+1);

   TGraphAsymmErrors *Pt_ratio_bdt5_fakes = new TGraphAsymmErrors("Pt_ratio_bdt5_fakes","Pt_ratio_bdt5_fakes");
   Pt_ratio_bdt5_fakes->Divide(fakes_bdt5_histo_ptcut,fakes_bdt5_histo);
   Pt_ratio_bdt5_fakes->SetMarkerStyle(20);
   Pt_ratio_bdt5_fakes->SetMarkerColor(kGreen+3);

   

   //Putting it all together...
   TMultiGraph *mg = new TMultiGraph();
   mg->Add(Pt_ratio_bdt1_fakes);
   mg->Add(Pt_ratio_bdt2_fakes);
   mg->Add(Pt_ratio_bdt3_fakes);
   mg->Add(Pt_ratio_bdt4_fakes);
   mg->Add(Pt_ratio_bdt5_fakes);

   mg->Draw("AP");
   mg->SetTitle("Background Efficiency");
   mg->GetXaxis()->SetTitle("P_{T} (GeV)");
   mg->GetYaxis()->SetTitle("Efficiency");

   TLegend *legend_fakes=new TLegend(0.5,0.5,.9,.9);
   legend_fakes->AddEntry(Pt_ratio_bdt1_fakes,"Cutting on Opt. BDT (no MuonPt) - 80\% Signal Eff.");
   legend_fakes->AddEntry(Pt_ratio_bdt2_fakes,"Cutting on Opt. BDT (no MuonPt) - 85\% Signal Eff.");
   legend_fakes->AddEntry(Pt_ratio_bdt3_fakes,"Cutting on Opt. BDT (no MuonPt) - 90\% Signal Eff.");
   legend_fakes->AddEntry(Pt_ratio_bdt4_fakes,"Cutting on Opt. BDT (no MuonPt) - 95\% Signal Eff.");
   legend_fakes->AddEntry(Pt_ratio_bdt5_fakes,"Cutting on Opt. BDT (no MuonPt) - 99\% Signal Eff.");
   legend_fakes->SetBorderSize(0);
   legend_fakes->Draw("AP");

   Pteff_fakes->SaveAs("PtNonFakes_Varied_Effs_DY.png");



   TCanvas *Pteff_nonfakes = new TCanvas("Pteff_nonfakes","Pteff_nonfakes",10,100,700,700);

   TGraphAsymmErrors *Pt_ratio_bdt1_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt1_nonfakes","Pt_ratio_bdt1_nonfakes");
   Pt_ratio_bdt1_nonfakes->Divide(nonfakes_bdt1_histo_ptcut,nonfakes_bdt1_histo);
   Pt_ratio_bdt1_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt1_nonfakes->SetMarkerColor(kRed);

   TGraphAsymmErrors *Pt_ratio_bdt2_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt2_nonfakes","Pt_ratio_bdt2_nonfakes");
   Pt_ratio_bdt2_nonfakes->Divide(nonfakes_bdt2_histo_ptcut,nonfakes_bdt2_histo);
   Pt_ratio_bdt2_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt2_nonfakes->SetMarkerColor(kBlue);

   TGraphAsymmErrors *Pt_ratio_bdt3_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt3_nonfakes","Pt_ratio_bdt3_nonfakes");
   Pt_ratio_bdt3_nonfakes->Divide(nonfakes_bdt3_histo_ptcut,nonfakes_bdt3_histo);
   Pt_ratio_bdt3_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt3_nonfakes->SetMarkerColor(kMagenta-1);

   TGraphAsymmErrors *Pt_ratio_bdt4_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt4_nonfakes","Pt_ratio_bdt4_nonfakes");
   Pt_ratio_bdt4_nonfakes->Divide(nonfakes_bdt4_histo_ptcut,nonfakes_bdt4_histo);
   Pt_ratio_bdt4_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt4_nonfakes->SetMarkerColor(kOrange+1);

   TGraphAsymmErrors *Pt_ratio_bdt5_nonfakes = new TGraphAsymmErrors("Pt_ratio_bdt5_nonfakes","Pt_ratio_bdt5_nonfakes");
   Pt_ratio_bdt5_nonfakes->Divide(nonfakes_bdt5_histo_ptcut,nonfakes_bdt5_histo);
   Pt_ratio_bdt5_nonfakes->SetMarkerStyle(20);
   Pt_ratio_bdt5_nonfakes->SetMarkerColor(kGreen+3);

   

   //Putting it all together...
   TMultiGraph *mg_nonfakes = new TMultiGraph();
   mg_nonfakes->Add(Pt_ratio_bdt1_nonfakes);
   mg_nonfakes->Add(Pt_ratio_bdt2_nonfakes);
   mg_nonfakes->Add(Pt_ratio_bdt3_nonfakes);
   mg_nonfakes->Add(Pt_ratio_bdt4_nonfakes);
   mg_nonfakes->Add(Pt_ratio_bdt5_nonfakes);

   mg_nonfakes->Draw("AP");
   mg_nonfakes->SetTitle("Signal Efficiency");
   mg_nonfakes->GetXaxis()->SetTitle("P_{T} (GeV)");
   mg_nonfakes->GetYaxis()->SetTitle("Efficiency");

   TLegend *legend_nonfakes=new TLegend(0.5,0.5,.9,.9);
   legend_nonfakes->AddEntry(Pt_ratio_bdt1_nonfakes,"Cutting on Opt. BDT (no MuonPt) - Pt Inclusive - 80\% Signal Eff.");
   legend_nonfakes->AddEntry(Pt_ratio_bdt2_nonfakes,"Cutting on Opt. BDT (no MuonPt) - Pt Inclusive - 85\% Signal Eff.");
   legend_nonfakes->AddEntry(Pt_ratio_bdt3_nonfakes,"Cutting on Opt. BDT (no MuonPt) - Pt Inclusive - 90\% Signal Eff.");
   legend_nonfakes->AddEntry(Pt_ratio_bdt4_nonfakes,"Cutting on Opt. BDT (no MuonPt) - Pt Inclusive - 95\% Signal Eff.");
   legend_nonfakes->AddEntry(Pt_ratio_bdt5_nonfakes,"Cutting on Opt. BDT (no MuonPt) - Pt Inclusive - 99\% Signal Eff.");
   legend_nonfakes->SetBorderSize(0);
   legend_nonfakes->Draw("AP");

   Pteff_nonfakes->SaveAs("PtNonFakes_Varied_Effs_DY.png");

   
   //g->GetXaxis()->SetTitle("Pt Cut");
   //g->GetYaxis()->SetTitle("Efficiency (Fakes)");
   //Pteff->SaveAs("Pt_Eff.png");

}

