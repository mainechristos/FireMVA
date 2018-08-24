void plot_BDT_DY(){
  
  float lumi = 1.;
  gStyle->SetOptStat(0);

  //Bg weights and cuts
  TString WeightExpression ="";
  WeightExpression += "1";


  //store total number of fake events and nonfake events    


  
  /////////////////////////////
  // Global BDT graphs       //
  /////////////////////////////

  float fake_events_bdt2 = 0.0;
  float nonfake_events_bdt2 = 0.0;

  //Get skimmed TTrees (copied from /cms/multilepton-2/hsaka/Workspace/pyPlotter-2018Maxi/pyPlotter/FIREMVA/)
  TFile *fake_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
  std::cout << "--- Using fakes input file: " << fake_input_bdt2->GetName() <<         std::endl;

  TFile *nonfake_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
  std::cout << "--- Using nonfakes input file: " << nonfake_input_bdt2->GetName() <<         std::endl;

  TTree *fake_bdt2 = (TTree*)fake_input_bdt2->Get("rootTupleTreeVeryLoose/tree");
  TTree *nonfake_bdt2 = (TTree*)nonfake_input_bdt2->Get("rootTupleTreeVeryLoose/tree");

  //Histos to store bdt2lation 
  TH1D *fake_bdt2_histo= new TH1D("fake_bdt2_histo","fake_bdt2_histo",40,-1,1);
  TH1D *nonfake_bdt2_histo= new TH1D("nonfake_bdt2_histo","nonfake_bdt2_histo",40,-1,1);

  fake_bdt2->Draw("(BDT)>>fake_bdt2_histo",WeightExpression);
  nonfake_bdt2->Draw("(BDT)>>nonfake_bdt2_histo",WeightExpression);

  //default lumi set to 1 for skimmed files
  fake_events_bdt2 += fake_bdt2_histo->Integral()*lumi;
  fake_bdt2_histo->Scale(lumi);

  nonfake_events_bdt2 += nonfake_bdt2_histo->Integral()*lumi;
  nonfake_bdt2_histo->Scale(lumi);
  

  cout<<"fake Events: "<<fake_events_bdt2<<endl;
  cout<<"nonfake Events: "<<nonfake_events_bdt2<<endl;

  TCanvas *cst = new TCanvas("cst","stacked hists",10,100,700,700);

  gPad->SetLogy();
  //gPad->SetGrid();

  nonfake_bdt2_histo->Draw("HIST");
  nonfake_bdt2_histo->SetLineWidth(2);
  nonfake_bdt2_histo->SetLineColor(kBlue);
  
  fake_bdt2_histo->Draw("SAME HIST");
  fake_bdt2_histo->SetLineWidth(2);
  fake_bdt2_histo->SetMarkerStyle(1);
  fake_bdt2_histo->SetLineColor(kRed);

  


  nonfake_bdt2_histo->GetXaxis()->SetTitle("BDT");

  cst->Update();

  TLegend *legend=new TLegend(0.5,0.5,.9,.9);
  legend->AddEntry(fake_bdt2_histo,("Fakes - Integral: "+std::to_string(fake_bdt2_histo->Integral())).c_str());
  legend->AddEntry(nonfake_bdt2_histo,("NonFakes - Integral: "+std::to_string(nonfake_bdt2_histo->Integral())).c_str());
  legend->Draw();

  cst->SaveAs("TT_fakes_MuonPt.png");

}