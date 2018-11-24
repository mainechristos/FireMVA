#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TMVA/Tools.h"

using namespace TMVA;

void Application_Fakes_2L_2017(){

  TMVA::Tools::Instance();

  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader2 = new TMVA::Reader( "!Color:!Silent" ); 

  float LightLeptonEta, LightLeptonPt, LightLeptonDXY, LightLeptonDZ, LightLeptonSIP3D, LightLeptonPtRatio, LightLeptonPtRel, LightLeptonJetLRM, LightLeptonJetFD, LightLeptonJetInOutRatio;
  float LightLeptonJetZest, LightLeptonJetNoOfConst, LightLeptonJetCSV, LightLeptonRelPFIsoPUCorr,LightLeptonRelTrkIso, LightLeptonPFChargedHadronIso;
  float LightLeptonPFNeutralHadronIso, LightLeptonPFPhotonIso, LightLeptonPFPUIso;
  float SoftNonFakeMuonPtRank, LightLeptonNoIDJetDRmin, LightLeptonIP3D, LightLeptonJetMuonEnergyFraction, LightLeptonJetElectronEnergyFraction, LightLeptonJetPhotonEnergyFraction, LightLeptonJetVtxMass, LightLeptonJetVtxNtracks, LightLeptonJetVtx3DVal, LightLeptonJetVtx3DSig;
  int LightLeptonN;

  reader1->AddVariable("LightLeptonPt := ElectronPt", &LightLeptonPt);
  reader1->AddVariable("LightLeptonEta := abs(ElectronEta)", &LightLeptonEta);
  reader1->AddVariable("LightLeptonDXY := ElectronDXY", &LightLeptonDXY);
  reader1->AddVariable("LightLeptonDZ := ElectronDZ", &LightLeptonDZ);
  reader1->AddVariable("LightLeptonSIP3D := ElectronSIP3D", &LightLeptonSIP3D);
  reader1->AddVariable("LightLeptonPtRatio := ElectronPtRatio", &LightLeptonPtRatio);
  reader1->AddVariable("LightLeptonPtRel := ElectronPtRel", &LightLeptonPtRel);
  reader1->AddVariable("LightLeptonJetLRM := ElectronJetLRM", &LightLeptonJetLRM);
  reader1->AddVariable("LightLeptonJetFD := ElectronJetFD", &LightLeptonJetFD);
  reader1->AddVariable("LightLeptonJetInOutRatio := ElectronJetInOutRatio", &LightLeptonJetInOutRatio);
  reader1->AddVariable("LightLeptonJetZest := ElectronJetZest", &LightLeptonJetZest);
  reader1->AddVariable("LightLeptonJetNoOfConst := ElectronJetNoOfConst", &LightLeptonJetNoOfConst);
  reader1->AddVariable("LightLeptonJetCSV := ElectronJetCSV", &LightLeptonJetCSV);
  reader1->AddVariable("LightLeptonRelPFIsoPUCorr := ElectronRelPFIsoPUCorr", &LightLeptonRelPFIsoPUCorr);
  reader1->AddVariable("LightLeptonRelTrkIso := ElectronRelTrkIso", &LightLeptonRelTrkIso);
  reader1->AddVariable("LightLeptonPFChargedHadronIso := ElectronPFChargedHadronIso", &LightLeptonPFChargedHadronIso);
  reader1->AddVariable("LightLeptonPFNeutralHadronIso := ElectronPFNeutralHadronIso", &LightLeptonPFNeutralHadronIso);
  reader1->AddVariable("LightLeptonPFPhotonIso := ElectronPFPhotonIso", &LightLeptonPFPhotonIso);
  //reader1->AddVariable("LightLeptonPFPUIso := ElectronPOGPFPUIsoR04", &LightLeptonPFPUIso);
  //reader1->AddVariable("SoftNonFakeMuonPtRank := SoftNonFakeMuonPtRank", &SoftNonFakeMuonPtRank);
  //reader1->AddVariable("LightLeptonNoIDJetDRmin := ElectronNoIDJetDRmin", &LightLeptonNoIDJetDRmin);
  //reader1->AddVariable("LightLeptonIP3D := ElectronIP3D", &LightLeptonIP3D);
  reader1->AddVariable("LightLeptonJetMuonEnergyFraction := ElectronJetMuonEnergyFraction", &LightLeptonJetMuonEnergyFraction);
  reader1->AddVariable("LightLeptonJetElectronEnergyFraction := ElectronJetElectronEnergyFraction", &LightLeptonJetElectronEnergyFraction);
  //reader1->AddVariable("LightLeptonJetPhotonEnergyFraction := ElectronJetPhotonEnergyFraction", &LightLeptonJetPhotonEnergyFraction);
  //reader1->AddVariable("LightLeptonJetVtxMass := ElectronJetVtxMass", &LightLeptonJetVtxMass);
  //reader1->AddVariable("LightLeptonJetVtxNtracks := ElectronJetVtxNtracks", &LightLeptonJetVtxNtracks);
  //reader1->AddVariable("LightLeptonJetVtx3DVal := ElectronJetVtx3DVal", &LightLeptonJetVtx3DVal);
  //reader1->AddVariable("LightLeptonJetVtx3DSig := ElectronJetVtx3DSig", &LightLeptonJetVtx3DSig);

  reader2->AddVariable("LightLeptonPt := MuonPt", &LightLeptonPt);
  reader2->AddVariable("LightLeptonEta := abs(MuonEta)", &LightLeptonEta);
  reader2->AddVariable("LightLeptonDXY := MuonDXY", &LightLeptonDXY);
  reader2->AddVariable("LightLeptonDZ := MuonDZ", &LightLeptonDZ);
  reader2->AddVariable("LightLeptonSIP3D := MuonSIP3D", &LightLeptonSIP3D);
  reader2->AddVariable("LightLeptonPtRatio := MuonPtRatio", &LightLeptonPtRatio);
  reader2->AddVariable("LightLeptonPtRel := MuonPtRel", &LightLeptonPtRel);
  reader2->AddVariable("LightLeptonJetLRM := MuonJetLRM", &LightLeptonJetLRM);
  reader2->AddVariable("LightLeptonJetFD := MuonJetFD", &LightLeptonJetFD);
  reader2->AddVariable("LightLeptonJetInOutRatio := MuonJetInOutRatio", &LightLeptonJetInOutRatio);
  reader2->AddVariable("LightLeptonJetZest := MuonJetZest", &LightLeptonJetZest);
  reader2->AddVariable("LightLeptonJetNoOfConst := MuonJetNoOfConst", &LightLeptonJetNoOfConst);
  reader2->AddVariable("LightLeptonJetCSV := MuonJetCSV", &LightLeptonJetCSV);
  reader2->AddVariable("LightLeptonRelPFIsoPUCorr := MuonRelPFIsoPUCorr", &LightLeptonRelPFIsoPUCorr);
  reader2->AddVariable("LightLeptonRelTrkIso := MuonRelTrkIso", &LightLeptonRelTrkIso);
  reader2->AddVariable("LightLeptonPFChargedHadronIso := MuonPFChargedHadronIso", &LightLeptonPFChargedHadronIso);
  reader2->AddVariable("LightLeptonPFNeutralHadronIso := MuonPFNeutralHadronIso", &LightLeptonPFNeutralHadronIso);
  reader2->AddVariable("LightLeptonPFPhotonIso := MuonPFPhotonIso", &LightLeptonPFPhotonIso);
  //reader2->AddVariable("LightLeptonPFPUIso := MuonPOGPFPUIsoR04", &LightLeptonPFPUIso);
  //reader2->AddVariable("SoftNonFakeMuonPtRank := SoftNonFakeMuonPtRank", &SoftNonFakeMuonPtRank);
  //reader2->AddVariable("LightLeptonNoIDJetDRmin := MuonNoIDJetDRmin", &LightLeptonNoIDJetDRmin);
  //reader2->AddVariable("LightLeptonIP3D := MuonIP3D", &LightLeptonIP3D);
  reader2->AddVariable("LightLeptonJetMuonEnergyFraction := MuonJetMuonEnergyFraction", &LightLeptonJetMuonEnergyFraction);
  reader2->AddVariable("LightLeptonJetElectronEnergyFraction := MuonJetElectronEnergyFraction", &LightLeptonJetElectronEnergyFraction);
  //reader2->AddVariable("LightLeptonJetPhotonEnergyFraction := MuonJetPhotonEnergyFraction", &LightLeptonJetPhotonEnergyFraction);
  //reader2->AddVariable("LightLeptonJetVtxMass := MuonJetVtxMass", &LightLeptonJetVtxMass);
  //reader2->AddVariable("LightLeptonJetVtxNtracks := MuonJetVtxNtracks", &LightLeptonJetVtxNtracks);
  //reader2->AddVariable("LightLeptonJetVtx3DVal := MuonJetVtx3DVal", &LightLeptonJetVtx3DVal);
  //reader2->AddVariable("LightLeptonJetVtx3DSig := MuonJetVtx3DSig", &LightLeptonJetVtx3DSig);




  reader1->BookMVA( "BDTG method",  "/cms/mchristos/ANN/FireMVA/L3Only/dl/weights/fire_MVA_PtInclusiveElectrons_BDT.weights.xml");
  reader2->BookMVA( "BDTG method",  "/cms/mchristos/ANN/FireMVA/L3Only/dl/weights/fire_MVA_PtInclusiveMuons_BDT.weights.xml");


  TFile *input(0);   
    input = TFile::Open("/cms/mchristos/ANN/FireMVA/2017/runPlotter_2L_NTupleMaker_2017/InputBundle_Data_Input_28_Tree.root");
    //input = TFile::Open("outFiles/Application_1/InputBundle_Data_Input_28_Tree/BDT3_tree.root");
    std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

    std::cout << "--- Select sample" << std::endl;
    TTree *tree = (TTree*)input->Get("rootTupleTreeVeryLoose/tree");
    TTree *PsetInputsTree = (TTree*)input->Get("PsetInputsTree");
    PsetInputsTree->SetName("PsetInputsTree");
    TTreeReader myReader(tree);


   

  TTreeReaderValue<vector<float>> inLightLeptonPt(myReader, "LightLeptonPt");
   TTreeReaderValue<vector<float>> inLightLeptonEta(myReader, "LightLeptonEta");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonDXY(myReader, "LightLeptonDXY");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonDZ(myReader, "LightLeptonDZ");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonSIP3D(myReader, "LightLeptonSIP3D");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonPtRatio(myReader, "LightLeptonPtRatio");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonPtRel(myReader, "LightLeptonPtRel");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetLRM(myReader, "LightLeptonJetLRM");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetFD(myReader, "LightLeptonJetFD");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetInOutRatio(myReader, "LightLeptonJetInOutRatio");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetZest(myReader, "LightLeptonJetZest");
   TTreeReaderValue<vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >> inLightLeptonJetNoOfConst(myReader, "LightLeptonJetNoOfConst");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetCSV(myReader, "LightLeptonJetCSV");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonRelPFIsoPUCorr(myReader, "LightLeptonRelPFIsoPUCorr");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonRelTrkIso(myReader, "LightLeptonRelTrkIso");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonPFChargedHadronIso(myReader, "LightLeptonPFChargedHadronIso");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonPFNeutralHadronIso(myReader, "LightLeptonPFNeutralHadronIso");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonPFPhotonIso(myReader, "LightLeptonPFPhotonIso");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonPFPUIso(myReader, "LightLeptonPFPUIso");
   //TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inSoftNonFakeMuonPtRank(myReader, "SoftNonFakeMuonPtRank");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonNoIDJetDRmin(myReader, "LightLeptonNoIDJetDRmin");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonIP3D(myReader, "LightLeptonIP3D");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetMuonEnergyFraction(myReader, "LightLeptonJetMuonEnergyFraction");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetElectronEnergyFraction(myReader, "LightLeptonJetElectronEnergyFraction");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetPhotonEnergyFraction(myReader, "LightLeptonJetPhotonEnergyFraction");
   ///TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtxMass(myReader, "LightLeptonJetVtxMass");
   //TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtxNtracks(myReader, "LightLeptonJetVtxNtracks");
   //TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtx3DVal(myReader, "LightLeptonJetVtx3DVal");
   //TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtx3DSig(myReader, "LightLeptonJetVtx3DSig");
   TTreeReaderValue<vector<int>> inLightLeptonN(myReader, "LightLeptonN");
   TTreeReaderValue<vector<int>> inLightLeptonFlavor(myReader, "LightLeptonFlavor");




    TFile *endfile = new TFile("outFiles/Application_1/InputBundle_Data_Input_28_Tree/BDT1_tree.root","RECREATE");   

    endfile->cd();

    PsetInputsTree->Write();

    endfile->mkdir("rootTupleTreeVeryLoose/");
    endfile->cd("rootTupleTreeVeryLoose/");
    TTree *found_back_tree = tree->CloneTree(0);

    std::vector<float> *BDTResponse = new std::vector<float>(0);
    found_back_tree->Branch("LightLeptonBDTPtInclusiveLeptons",&BDTResponse);

   std::vector<float> vecVar(4); // vector for EvaluateMVA tests

   std::cout << "--- Processing: " << tree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   int count = 0;

  while (myReader.Next()) {

      if (count%1000 == 0) std::cout << "--- ... Processing event: " << count << std::endl;
      BDTResponse->clear();

      tree->GetEntry(count);

      if(inLightLeptonN->empty()){
        LightLeptonN = 0;
      }else{
        LightLeptonN = inLightLeptonN->at(0);
      }

      for(int i=0; i<LightLeptonN; i++){
        
        if(inLightLeptonFlavor->at(i)!=2&&inLightLeptonFlavor->at(i)!=1){
          
          BDTResponse->push_back(10000);

          }else if(inLightLeptonFlavor->at(i)==1){

            LightLeptonPt = inLightLeptonPt->at(i);
            LightLeptonEta = abs(inLightLeptonEta->at(i));
            LightLeptonDXY = inLightLeptonDXY->at(i);
            LightLeptonDZ = inLightLeptonDZ->at(i);
            LightLeptonSIP3D = inLightLeptonSIP3D->at(i);
            LightLeptonPtRatio = inLightLeptonPtRatio->at(i);
            LightLeptonPtRel = inLightLeptonPtRel->at(i);
            LightLeptonJetLRM = inLightLeptonJetLRM->at(i);
            LightLeptonJetFD = inLightLeptonJetFD->at(i);
            LightLeptonJetInOutRatio = inLightLeptonJetInOutRatio->at(i);
            LightLeptonJetZest = inLightLeptonJetZest->at(i);
            LightLeptonJetNoOfConst = inLightLeptonJetNoOfConst->at(i);
            LightLeptonJetCSV = inLightLeptonJetCSV->at(i);
            LightLeptonRelPFIsoPUCorr = inLightLeptonRelPFIsoPUCorr->at(i);
            LightLeptonRelTrkIso = inLightLeptonRelTrkIso->at(i);
            LightLeptonPFChargedHadronIso = inLightLeptonPFChargedHadronIso->at(i);
            LightLeptonPFNeutralHadronIso = inLightLeptonPFNeutralHadronIso->at(i);
            LightLeptonPFPhotonIso = inLightLeptonPFPhotonIso->at(i);
            LightLeptonPFPUIso = inLightLeptonPFPUIso->at(i);
            //SoftNonFakeMuonPtRank = inSoftNonFakeMuonPtRank->at(i);
            LightLeptonNoIDJetDRmin = inLightLeptonNoIDJetDRmin->at(i);
            LightLeptonIP3D = inLightLeptonIP3D->at(i);
            LightLeptonJetMuonEnergyFraction = inLightLeptonJetMuonEnergyFraction->at(i);
            LightLeptonJetElectronEnergyFraction = inLightLeptonJetElectronEnergyFraction->at(i);
            LightLeptonJetPhotonEnergyFraction = inLightLeptonJetPhotonEnergyFraction->at(i);
            //LightLeptonJetVtxMass = inLightLeptonJetVtxMass->at(i);
            //LightLeptonJetVtxNtracks = inLightLeptonJetVtxNtracks->at(i);
            //LightLeptonJetVtx3DVal = inLightLeptonJetVtx3DVal->at(i);
            //LightLeptonJetVtx3DSig = inLightLeptonJetVtx3DSig->at(i);



            float result1 =  reader1->EvaluateMVA( "BDTG method" );
            BDTResponse->push_back(result1);

          }else if(inLightLeptonFlavor->at(i)==2){

            LightLeptonPt = inLightLeptonPt->at(i);
            LightLeptonEta = abs(inLightLeptonEta->at(i));
            LightLeptonDXY = inLightLeptonDXY->at(i);
            LightLeptonDZ = inLightLeptonDZ->at(i);
            LightLeptonSIP3D = inLightLeptonSIP3D->at(i);
            LightLeptonPtRatio = inLightLeptonPtRatio->at(i);
            LightLeptonPtRel = inLightLeptonPtRel->at(i);
            LightLeptonJetLRM = inLightLeptonJetLRM->at(i);
            LightLeptonJetFD = inLightLeptonJetFD->at(i);
            LightLeptonJetInOutRatio = inLightLeptonJetInOutRatio->at(i);
            LightLeptonJetZest = inLightLeptonJetZest->at(i);
            LightLeptonJetNoOfConst = inLightLeptonJetNoOfConst->at(i);
            LightLeptonJetCSV = inLightLeptonJetCSV->at(i);
            LightLeptonRelPFIsoPUCorr = inLightLeptonRelPFIsoPUCorr->at(i);
            LightLeptonRelTrkIso = inLightLeptonRelTrkIso->at(i);
            LightLeptonPFChargedHadronIso = inLightLeptonPFChargedHadronIso->at(i);
            LightLeptonPFNeutralHadronIso = inLightLeptonPFNeutralHadronIso->at(i);
            LightLeptonPFPhotonIso = inLightLeptonPFPhotonIso->at(i);
            LightLeptonPFPUIso = inLightLeptonPFPUIso->at(i);
            //SoftNonFakeMuonPtRank = inSoftNonFakeMuonPtRank->at(i);
            LightLeptonNoIDJetDRmin = inLightLeptonNoIDJetDRmin->at(i);
            LightLeptonIP3D = inLightLeptonIP3D->at(i);
            LightLeptonJetMuonEnergyFraction = inLightLeptonJetMuonEnergyFraction->at(i);
            LightLeptonJetElectronEnergyFraction = inLightLeptonJetElectronEnergyFraction->at(i);
            LightLeptonJetPhotonEnergyFraction = inLightLeptonJetPhotonEnergyFraction->at(i);
            //LightLeptonJetVtxMass = inLightLeptonJetVtxMass->at(i);
            //LightLeptonJetVtxNtracks = inLightLeptonJetVtxNtracks->at(i);
            //LightLeptonJetVtx3DVal = inLightLeptonJetVtx3DVal->at(i);
            //LightLeptonJetVtx3DSig = inLightLeptonJetVtx3DSig->at(i);



          float result2 =  reader2->EvaluateMVA( "BDTG method" );
          BDTResponse->push_back(result2);

          
          

        }
      }
      found_back_tree->Fill();
      count++;


      


    }

    sw.Stop();
    std::cout << "--- End of event loop: "; sw.Print();

     

   
    found_back_tree->Write();
   

   
    endfile->Close();               
  
    delete reader1;
    delete reader2;

  


}