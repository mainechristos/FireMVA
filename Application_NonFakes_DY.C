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

void Application_NonFakes_DY(){

	TMVA::Tools::Instance();

	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" ); 

	float TagMuonAbsEta, TagMuonPt, TagMuonDXY, TagMuonDZ, TagMuonSIP3D, TagMuonPtRatio, TagMuonPtRel, TagMuonJetLRM, TagMuonJetFD, TagMuonJetInOutRatio;
	float TagMuonJetZest, TagMuonJetNoOfConst, TagMuonJetCSV, TagMuonPOGRelPFIsoDBCorrR04,TagMuonRelTrkIsoR03, TagMuonPOGPFChargedHadronIsoR04;
	float TagMuonPOGPFNeutralHadronIsoR04, TagMuonPOGPFPhotonIsoR04, TagMuonPOGPFPUIsoR04;

	//reader->AddVariable("TagMuonPt := TagMuonPt", &TagMuonPt);
	reader->AddVariable("TagMuonAbsEta := TagMuonAbsEta", &TagMuonAbsEta);
	reader->AddVariable("TagMuonDXY := TagMuonDXY", &TagMuonDXY);
	reader->AddVariable("TagMuonDZ := TagMuonDZ", &TagMuonDZ);
	reader->AddVariable("TagMuonSIP3D := TagMuonSIP3D", &TagMuonSIP3D);
	reader->AddVariable("TagMuonPtRatio := TagMuonPtRatio", &TagMuonPtRatio);
	reader->AddVariable("TagMuonPtRel := TagMuonPtRel", &TagMuonPtRel);
	reader->AddVariable("TagMuonJetLRM := TagMuonJetLRM", &TagMuonJetLRM);
	reader->AddVariable("TagMuonJetFD := TagMuonJetFD", &TagMuonJetFD);
	reader->AddVariable("TagMuonJetInOutRatio := TagMuonJetInOutRatio", &TagMuonJetInOutRatio);
	reader->AddVariable("TagMuonJetZest := TagMuonJetZest", &TagMuonJetZest);
	reader->AddVariable("TagMuonJetNoOfConst := TagMuonJetNoOfConst", &TagMuonJetNoOfConst);
	reader->AddVariable("TagMuonJetCSV := TagMuonJetCSV", &TagMuonJetCSV);
	reader->AddVariable("TagMuonPOGRelPFIsoDBCorrR04 := TagMuonPOGRelPFIsoDBCorrR04", &TagMuonPOGRelPFIsoDBCorrR04);
	reader->AddVariable("TagMuonRelTrkIsoR03 := TagMuonRelTrkIsoR03", &TagMuonRelTrkIsoR03);
	reader->AddVariable("TagMuonPOGPFChargedHadronIsoR04 := TagMuonPOGPFChargedHadronIsoR04", &TagMuonPOGPFChargedHadronIsoR04);
	reader->AddVariable("TagMuonPOGPFNeutralHadronIsoR04 := TagMuonPOGPFNeutralHadronIsoR04", &TagMuonPOGPFNeutralHadronIsoR04);
	reader->AddVariable("TagMuonPOGPFPhotonIsoR04 := TagMuonPOGPFPhotonIsoR04", &TagMuonPOGPFPhotonIsoR04);
	reader->AddVariable("TagMuonPOGPFPUIsoR04 := TagMuonPOGPFPUIsoR04", &TagMuonPOGPFPUIsoR04);


	reader->BookMVA( "BDTG method",  "dl/weights/fire_MVA_DY_noMuonPt_BDT.weights.xml");

	TFile *input(0);   
   	input = TFile::Open("/cms/mchristos/ANN/FireMVA/DY_NonFakeMuonTree_Analysis.root");

   	std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

   	std::cout << "--- Select sample" << std::endl;
   	TTree *tree = (TTree*)input->Get("rootTupleTreeVeryLoose/tree");
   	TTreeReader myReader(tree);

   	TTreeReaderValue<float> inTagMuonPt(myReader, "TagMuonPt");
   	TTreeReaderValue<float> inTagMuonAbsEta(myReader, "TagMuonAbsEta");
   	TTreeReaderValue<float> inTagMuonDXY(myReader, "TagMuonDXY");
   	TTreeReaderValue<float> inTagMuonDZ(myReader, "TagMuonDZ");
   	TTreeReaderValue<float> inTagMuonSIP3D(myReader, "TagMuonSIP3D");
   	TTreeReaderValue<float> inTagMuonPtRatio(myReader, "TagMuonPtRatio");
   	TTreeReaderValue<float> inTagMuonPtRel(myReader, "TagMuonPtRel");
   	TTreeReaderValue<float> inTagMuonJetLRM(myReader, "TagMuonJetLRM");
   	TTreeReaderValue<float> inTagMuonJetFD(myReader, "TagMuonJetFD");
   	TTreeReaderValue<float> inTagMuonJetInOutRatio(myReader, "TagMuonJetInOutRatio");
   	TTreeReaderValue<float> inTagMuonJetZest(myReader, "TagMuonJetZest");
   	TTreeReaderValue<int> inTagMuonJetNoOfConst(myReader, "TagMuonJetNoOfConst");
   	TTreeReaderValue<double> inTagMuonJetCSV(myReader, "TagMuonJetCSV");
   	TTreeReaderValue<float> inTagMuonPOGRelPFIsoDBCorrR04(myReader, "TagMuonPOGRelPFIsoDBCorrR04");
   	TTreeReaderValue<float> inTagMuonRelTrkIsoR03(myReader, "TagMuonRelTrkIsoR03");
   	TTreeReaderValue<float> inTagMuonPOGPFChargedHadronIsoR04(myReader, "TagMuonPOGPFChargedHadronIsoR04");
   	TTreeReaderValue<float> inTagMuonPOGPFNeutralHadronIsoR04(myReader, "TagMuonPOGPFNeutralHadronIsoR04");
   	TTreeReaderValue<float> inTagMuonPOGPFPhotonIsoR04(myReader, "TagMuonPOGPFPhotonIsoR04");
   	TTreeReaderValue<float> inTagMuonPOGPFPUIsoR04(myReader, "TagMuonPOGPFPUIsoR04");

   	TFile *endfile = new TFile("outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root","RECREATE");   

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

	   	tree->GetEntry(count);

	   	TagMuonPt = *inTagMuonPt;
	   	TagMuonAbsEta = *inTagMuonAbsEta;
	   	TagMuonDXY = *inTagMuonDXY;
	   	TagMuonDZ = *inTagMuonDZ;
	   	TagMuonSIP3D = *inTagMuonSIP3D;
	   	TagMuonPtRatio = *inTagMuonPtRatio;
	   	TagMuonPtRel = *inTagMuonPtRel;
	   	TagMuonJetLRM = *inTagMuonJetLRM;
	   	TagMuonJetFD = *inTagMuonJetFD;
	   	TagMuonJetInOutRatio = *inTagMuonJetInOutRatio;
	   	TagMuonJetZest = *inTagMuonJetZest;
	   	TagMuonJetNoOfConst = *inTagMuonJetNoOfConst;
	   	TagMuonJetCSV = *inTagMuonJetCSV;
	   	TagMuonPOGRelPFIsoDBCorrR04 = *inTagMuonPOGRelPFIsoDBCorrR04;
	   	TagMuonRelTrkIsoR03 = *inTagMuonRelTrkIsoR03;
	   	TagMuonPOGPFChargedHadronIsoR04 = *inTagMuonPOGPFChargedHadronIsoR04;
	   	TagMuonPOGPFNeutralHadronIsoR04 = *inTagMuonPOGPFNeutralHadronIsoR04;
	   	TagMuonPOGPFPhotonIsoR04 = *inTagMuonPOGPFPhotonIsoR04;
	   	TagMuonPOGPFPUIsoR04 = *inTagMuonPOGPFPUIsoR04;



	    double result =  reader->EvaluateMVA( "BDTG method" );
      	BDTResponse->clear();
      	BDTResponse->push_back(result);
      	found_back_tree->Fill();
      	count++;


  	}

  	sw.Stop();
   	std::cout << "--- End of event loop: "; sw.Print();

     

   
   	found_back_tree->Write();
   

   
   	endfile->Close();               
  
   	delete reader;


	


}