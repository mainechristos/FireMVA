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




void Train_Electrons_DY_IDvars( TString myMethodList = "" )
{

   TMVA::Tools::Instance();
   std::map<std::string,int> Use;

   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   TString outfileName( "class_perf/fire_MVA_DY_IDvarsElectrons.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "fire_MVA_DY_IDvarsElectrons", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification" );

   TMVA::DataLoader* dl = new TMVA::DataLoader("dl");

   dl->AddVariable("ElectronPt");
   dl->AddVariable("abs(ElectronEta)");
   dl->AddVariable("ElectronDXY");
   dl->AddVariable("ElectronDZ");
   dl->AddVariable("ElectronSIP3D");
   dl->AddVariable("ElectronPtRatio");
   dl->AddVariable("ElectronPtRel");
   dl->AddVariable("ElectronJetLRM");
   dl->AddVariable("ElectronJetFD");
   dl->AddVariable("ElectronJetInOutRatio");
   dl->AddVariable("ElectronJetZest");
   dl->AddVariable("ElectronJetNoOfConst");
   dl->AddVariable("ElectronJetCSV");
   dl->AddVariable("ElectronRelPFIsoPUCorr");
   dl->AddVariable("ElectronRelTrkIso");
   dl->AddVariable("ElectronPFChargedHadronIso");
   dl->AddVariable("ElectronPFNeutralHadronIso");
   dl->AddVariable("ElectronPFPhotonIso");
   dl->AddVariable("ElectronJetMuonEnergyFraction");
   dl->AddVariable("ElectronJetElectronEnergyFraction");

   dl->AddVariable("ElectronMissingHits");
   dl->AddVariable("ElectronPassConversionVeto");
   dl->AddVariable("ElectronEInverseMinusPInverse");
   dl->AddVariable("ElectronHoE");
   dl->AddVariable("ElectronDeltaPhiTrkSC");
   dl->AddVariable("ElectronDeltaEtaTrkSeedSC");
   dl->AddVariable("ElectronFull5x5SigmaIEtaIEta");
   dl->AddVariable("ElectronPt");



   //dl->AddVariable("ElectronJetPhotonEnergyFraction");

   //dl->AddVariable("ElectronPFPUIso");


   float lumi = 1.;
   gStyle->SetOptStat(0);

   //Bg weights and cuts
   TString WeightExpression ="";
   WeightExpression += "ElectronPtNorm";

   //store total number of fake events and nonfake events    
   double fake_events = 0.0;
   double nonfake_events = 0.0;


   /////////////////////////////
   // Add MC Background Trees //
   /////////////////////////////


   //Get skimmed TTrees (copied from /cms/multilepton-2/hsaka/Workspace/pyPlotter-2018Maxi/pyPlotter/FIREMVA/)
   TFile *fakes_input = TFile::Open( "/cms/mchristos/ANN/FireMVA/2017/DY11to16_FakeElectronTree.root" ); 
   std::cout << "--- Using fakes input file: " << fakes_input->GetName() <<         std::endl;

   TFile *nonfakes_input = TFile::Open( "/cms/mchristos/ANN/FireMVA/2017/TMVA/DY_WZElectronTree_PtNorm_TMVA.root" ); 
   std::cout << "--- Using nonfakes input file: " << nonfakes_input->GetName() <<         std::endl;

   TTree *fakes = (TTree*)fakes_input->Get("rootTupleTreeVeryLoose/tree");
   TTree *nonfakes = (TTree*)nonfakes_input->Get("rootTupleTreeVeryLoose/tree");

   //Histos to store isolation 
   TH1D *fakes_histo= new TH1D("fakes_histo","fakes_histo",300,0,600);
   TH1D *nonfakes_histo= new TH1D("nonfakes_histo","nonfakes_histo",300,0,600);

   fakes->Draw("(ElectronPt)>>fakes_histo");
   nonfakes->Draw("(ElectronPt)>>nonfakes_histo",WeightExpression);


   fake_events += fakes_histo->Integral()*lumi;
   fakes_histo->Scale(lumi);

   nonfake_events += nonfakes_histo->Integral()*lumi;
   nonfakes_histo->Scale(lumi*2);
   //nonfakes_histo->Add(nonfakes_histo);
      

   
   cout<<"fake Events: "<<fake_events<<endl;
   cout<<"nonfake Events: "<<nonfake_events<<endl;

   
   TCanvas *cst = new TCanvas("cst","cst",10,100,700,700);

   fakes_histo->Draw("HIST");
   fakes_histo->SetLineWidth(2);
   fakes_histo->SetMarkerStyle(1);
   fakes_histo->SetLineColor(kRed);

   nonfakes_histo->Draw("SAME HIST");
   nonfakes_histo->SetLineWidth(2);
   nonfakes_histo->SetLineColor(kBlue);

   fakes_histo->GetXaxis()->SetTitle("P_{T} (GeV)");

   cst->Update();

   TLegend *legend=new TLegend(0.5,0.5,.9,.9);
   legend->AddEntry(fakes_histo,("Fakes - Integral: "+std::to_string(fakes_histo->Integral())).c_str());
   legend->AddEntry(nonfakes_histo,("NonFakes - Integral: "+std::to_string(nonfakes_histo->Integral())).c_str());
   
   
   
   
   legend->Draw();

   cst->SaveAs("DY_fakes.png");
   


   dl->AddBackgroundTree ( fakes, 1); 
   //dl->SetBackgroundWeightExpression("ElectronPtNorm");

   dl->AddSignalTree ( nonfakes, 1);
   dl->SetSignalWeightExpression("ElectronPtNorm");

   dl->PrepareTrainingAndTestTree( "1", "1",
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
   
   //factory->BookMethod( dl, TMVA::Types::kBDT, "10 Trees","!H:!V:NTrees=10:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "50 Trees","!H:!V:NTrees=50:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "150 Trees","!H:!V:NTrees=150:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "450 Trees","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "850 Trees","!H:!V:NTrees=850:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "1000 Trees","!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "2000 Trees","!H:!V:NTrees=2000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "5000 Trees","!H:!V:NTrees=5000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   

   //factory->BookMethod( dl, TMVA::Types::kBDT, "Depth 2","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Depth 3","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=3" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Depth 6","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=6" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Depth 10","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=10" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Depth 20","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=20" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Depth 100","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=100" );
   
   
   //factory->BookMethod( dl, TMVA::Types::kBDT, "MinNodeSize 1.0","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "MinNodeSize 2.5","!H:!V:NTrees=450:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "MinNodeSize 7.5","!H:!V:NTrees=450:MinNodeSize=7.5%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "MinNodeSize 10","!H:!V:NTrees=450:MinNodeSize=10.0%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "MinNodeSize 20","!H:!V:NTrees=450:MinNodeSize=20.0%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "MinNodeSize 30","!H:!V:NTrees=450:MinNodeSize=30.0%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Shrinkage .01","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.01:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Shrinkage .1","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Shrinkage .5","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Shrinkage 1","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=1:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Shrinkage 2","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=2:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Shrinkage 3","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=3:nCuts=20:MaxDepth=2" );
   

   //factory->BookMethod( dl, TMVA::Types::kBDT, "NCuts 1","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=1:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "NCuts 2","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=2:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "NCuts 5","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=5:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "NCuts 10","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=10:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "NCuts 20","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=20:MaxDepth=2" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "NCuts 100","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=100:MaxDepth=2" );
   
   
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Identity","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=100:MaxDepth=2::VarTransform=I" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "PCA","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=100:MaxDepth=2::VarTransform=P" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Decorrelation","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=100:MaxDepth=2::VarTransform=D" );
   //factory->BookMethod( dl, TMVA::Types::kBDT, "Gaussian","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=100:MaxDepth=2::VarTransform=G" );
   

   factory->BookMethod( dl, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=450:MinNodeSize=1.0%:BoostType=Grad:Shrinkage=.5:nCuts=100:MaxDepth=2::VarTransform=I" );


   factory->TrainAllMethods();

   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;


   delete factory;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()){;
         TMVA::TMVAGui( outfileName );
   }



}

