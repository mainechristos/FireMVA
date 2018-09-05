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

void Application_Fakes_DY_Full(){

	TMVA::Tools::Instance();

	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" ); 

	float LightLeptonEta, LightLeptonPt, LightLeptonDXY, LightLeptonDZ, LightLeptonSIP3D, LightLeptonPtRatio, LightLeptonPtRel, LightLeptonJetLRM, LightLeptonJetFD, LightLeptonJetInOutRatio;
	float LightLeptonJetZest, LightLeptonJetNoOfConst, LightLeptonJetCSV, LightLeptonRelPFIsoPUCorr,LightLeptonRelTrkIso, LightLeptonPFChargedHadronIso;
	float LightLeptonPFNeutralHadronIso, LightLeptonPFPhotonIso, LightLeptonPFPUIso;
	float SoftNonFakeMuonPtRank, LightLeptonNoIDJetDRmin, LightLeptonIP3D, LightLeptonJetMuonEnergyFraction, LightLeptonJetElectronEnergyFraction, LightLeptonJetPhotonEnergyFraction, LightLeptonJetVtxMass, LightLeptonJetVtxNtracks, LightLeptonJetVtx3DVal, LightLeptonJetVtx3DSig;
  int LightLeptonN;

	//reader->AddVariable("LightLeptonPt := TagMuonPt", &LightLeptonPt);
	reader->AddVariable("LightLeptonEta := TagMuonAbsEta", &LightLeptonEta);
	reader->AddVariable("LightLeptonDXY := TagMuonDXY", &LightLeptonDXY);
	reader->AddVariable("LightLeptonDZ := TagMuonDZ", &LightLeptonDZ);
	reader->AddVariable("LightLeptonSIP3D := TagMuonSIP3D", &LightLeptonSIP3D);
	reader->AddVariable("LightLeptonPtRatio := TagMuonPtRatio", &LightLeptonPtRatio);
	reader->AddVariable("LightLeptonPtRel := TagMuonPtRel", &LightLeptonPtRel);
	reader->AddVariable("LightLeptonJetLRM := TagMuonJetLRM", &LightLeptonJetLRM);
	reader->AddVariable("LightLeptonJetFD := TagMuonJetFD", &LightLeptonJetFD);
	reader->AddVariable("LightLeptonJetInOutRatio := TagMuonJetInOutRatio", &LightLeptonJetInOutRatio);
	reader->AddVariable("LightLeptonJetZest := TagMuonJetZest", &LightLeptonJetZest);
	reader->AddVariable("LightLeptonJetNoOfConst := TagMuonJetNoOfConst", &LightLeptonJetNoOfConst);
	reader->AddVariable("LightLeptonJetCSV := TagMuonJetCSV", &LightLeptonJetCSV);
	reader->AddVariable("LightLeptonRelPFIsoPUCorr := TagMuonPOGRelPFIsoDBCorrR04", &LightLeptonRelPFIsoPUCorr);
	reader->AddVariable("LightLeptonRelTrkIso := TagMuonRelTrkIsoR03", &LightLeptonRelTrkIso);
	reader->AddVariable("LightLeptonPFChargedHadronIso := TagMuonPOGPFChargedHadronIsoR04", &LightLeptonPFChargedHadronIso);
	reader->AddVariable("LightLeptonPFNeutralHadronIso := TagMuonPOGPFNeutralHadronIsoR04", &LightLeptonPFNeutralHadronIso);
	reader->AddVariable("LightLeptonPFPhotonIso := TagMuonPOGPFPhotonIsoR04", &LightLeptonPFPhotonIso);
	reader->AddVariable("LightLeptonPFPUIso := TagMuonPOGPFPUIsoR04", &LightLeptonPFPUIso);
	//reader->AddVariable("SoftNonFakeMuonPtRank := SoftNonFakeMuonPtRank", &SoftNonFakeMuonPtRank);
  //reader->AddVariable("LightLeptonNoIDJetDRmin := TagMuonNoIDJetDRmin", &LightLeptonNoIDJetDRmin);
  //reader->AddVariable("LightLeptonIP3D := TagMuonIP3D", &LightLeptonIP3D);
  //reader->AddVariable("LightLeptonJetMuonEnergyFraction := TagMuonJetMuonEnergyFraction", &LightLeptonJetMuonEnergyFraction);
  //reader->AddVariable("LightLeptonJetElectronEnergyFraction := TagMuonJetElectronEnergyFraction", &LightLeptonJetElectronEnergyFraction);
  //reader->AddVariable("LightLeptonJetPhotonEnergyFraction := TagMuonJetPhotonEnergyFraction", &LightLeptonJetPhotonEnergyFraction);
  //reader->AddVariable("LightLeptonJetVtxMass := TagMuonJetVtxMass", &LightLeptonJetVtxMass);
  //reader->AddVariable("LightLeptonJetVtxNtracks := TagMuonJetVtxNtracks", &LightLeptonJetVtxNtracks);
  //reader->AddVariable("LightLeptonJetVtx3DVal := TagMuonJetVtx3DVal", &LightLeptonJetVtx3DVal);
  //reader->AddVariable("LightLeptonJetVtx3DSig := TagMuonJetVtx3DSig", &LightLeptonJetVtx3DSig);




	reader->BookMVA( "BDTG method",  "dl/weights/fire_MVA_DY_noMuonPt_BDT.weights.xml");

	TFile *input(0);   
   	input = TFile::Open("/cms/mchristos/ANN/FireMVA/InputBundle_TT_Input_0_Tree.root");

   	std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

   	std::cout << "--- Select sample" << std::endl;
   	TTree *tree = (TTree*)input->Get("rootTupleTreeVeryLoose/tree");
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
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtxMass(myReader, "LightLeptonJetVtxMass");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtxNtracks(myReader, "LightLeptonJetVtxNtracks");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtx3DVal(myReader, "LightLeptonJetVtx3DVal");
   TTreeReaderValue<vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >> inLightLeptonJetVtx3DSig(myReader, "LightLeptonJetVtx3DSig");
   TTreeReaderValue<vector<int>> inLightLeptonN(myReader, "LightLeptonN");
   TTreeReaderValue<vector<int>> inLightLeptonFlavor(myReader, "LightLeptonFlavor");




   	TFile *endfile = new TFile("outFiles/BDTnoMuonPt_TTFull_DYTrain_FakeMuonTree.root","RECREATE");   

   	endfile->cd();

   	endfile->mkdir("rootTupleTreeVeryLoose/");
   	endfile->cd("rootTupleTreeVeryLoose/");
   	TTree *found_back_tree = tree->CloneTree(0);

   	std::vector<double> *BDTResponse = new std::vector<double>(0);
   	found_back_tree->Branch("BDT",&BDTResponse);

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
        
        if(inLightLeptonFlavor->at(i)!=2){
          
          BDTResponse->push_back(10000);

        }else{

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
          LightLeptonJetVtxMass = inLightLeptonJetVtxMass->at(i);
          LightLeptonJetVtxNtracks = inLightLeptonJetVtxNtracks->at(i);
          LightLeptonJetVtx3DVal = inLightLeptonJetVtx3DVal->at(i);
          LightLeptonJetVtx3DSig = inLightLeptonJetVtx3DSig->at(i);



          double result =  reader->EvaluateMVA( "BDTG method" );
          BDTResponse->push_back(result);

          
          

        }
      }
      found_back_tree->Fill();
      count++;


	   	


  	}

  	sw.Stop();
   	std::cout << "--- End of event loop: "; sw.Print();

     

   
   	found_back_tree->Write();
   

   
   	endfile->Close();               
  
   	delete reader;


	


}