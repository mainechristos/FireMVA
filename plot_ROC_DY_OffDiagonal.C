void plot_ROC_DY_OffDiagonal(){
  
  float lumi = 1.;
  gStyle->SetOptStat(0);

  //Bg weights and cuts
  TString WeightExpression ="";
  WeightExpression += "1";


  //store total number of fake events and nonfake events    
  double fake_events_iso = 0.0;
  double nonfake_events_iso = 0.0;


  /////////////////////////////
  // isolation graphs        //
  /////////////////////////////


  //Get skimmed TTrees (copied from /cms/multilepton-2/hsaka/Workspace/pyPlotter-2018Maxi/pyPlotter/FIREMVA/)
  TFile *fake_input_iso = TFile::Open( "/cms/mchristos/ANN/FireMVA/DY_FakeMuonTree.root" ); 
  std::cout << "--- Using fakes input file: " << fake_input_iso->GetName() <<         std::endl;

  TFile *nonfake_input_iso = TFile::Open( "/cms/mchristos/ANN/FireMVA/DY_NonFakeMuonTree.root" ); 
  std::cout << "--- Using nonfakes input file: " << nonfake_input_iso->GetName() <<         std::endl;

  TTree *fake_iso = (TTree*)fake_input_iso->Get("rootTupleTreeVeryLoose/tree");
  TTree *nonfake_iso = (TTree*)nonfake_input_iso->Get("rootTupleTreeVeryLoose/tree");

  //Histos to store isolation 
  TH1D *fake_iso_histo= new TH1D("fake_iso_histo","fake_iso_histo",40,0,1);
  TH1D *nonfake_iso_histo= new TH1D("nonfake_iso_histo","nonfake_iso_histo",40,0,1);

  fake_iso->Draw("(TagMuonPOGRelPFIsoDBCorrR04)>>fake_iso_histo",WeightExpression);
  nonfake_iso->Draw("(TagMuonPOGRelPFIsoDBCorrR04)>>nonfake_iso_histo",WeightExpression);

  //default lumi set to 1 for skimmed files
  fake_events_iso += fake_iso_histo->Integral()*lumi;
  fake_iso_histo->Scale(lumi);

  nonfake_events_iso += nonfake_iso_histo->Integral()*lumi;
  nonfake_iso_histo->Scale(lumi);
  

  cout<<"fake Events: "<<fake_events_iso<<endl;
  cout<<"nonfake Events: "<<nonfake_events_iso<<endl;

  //Draw Isolation histograms for fakes and non-fakes 
  TCanvas *cst = new TCanvas("cst","cst",10,100,700,700);

  gPad->SetLogy();
  //gPad->SetGrid();

  nonfake_iso_histo->Draw("HIST");
  nonfake_iso_histo->SetLineWidth(2);
  nonfake_iso_histo->SetLineColor(kBlue);
  
  fake_iso_histo->Draw("SAME HIST");
  fake_iso_histo->SetLineWidth(2);
  fake_iso_histo->SetMarkerStyle(1);
  fake_iso_histo->SetLineColor(kRed);

  


  nonfake_iso_histo->GetXaxis()->SetTitle("Isolation");

  cst->Update();

  TLegend *legend=new TLegend(0.5,0.5,.9,.9);
  legend->AddEntry(fake_iso_histo,("Fakes - Integral: "+std::to_string(fake_iso_histo->Integral())).c_str());
  legend->AddEntry(nonfake_iso_histo,("NonFakes - Integral: "+std::to_string(nonfake_iso_histo->Integral())).c_str());
  legend->Draw();

  cst->SaveAs("DY_fakes_OffDiagonal.png");

  ////////////////////////////
  // Isolation ROC Curve   ///
  ////////////////////////////

  TCanvas *roc = new TCanvas("roc","roc",10,100,700,700);
  gPad->SetGrid();
  int nbins_iso = nonfake_iso_histo->GetNbinsX();

  //Iso fakes Efficiency.
  Double_t nonfakesPoints_iso[nbins_iso], fakesPoints_iso[nbins_iso];
  //stores point tagged for .95 nonfakes efficiency
  Double_t sigeff10[1], bgrej10[1];


   for ( int i = 0; i <= nbins_iso; ++i ) {

    float sig_frac = nonfake_iso_histo->Integral(0,i);
    float back_frac = fake_iso_histo->Integral(0,i);

    nonfakesPoints_iso[i] = sig_frac/nonfake_events_iso;
    fakesPoints_iso[i] = 1-back_frac/fake_events_iso;

    //store point if iso=.15
    if(i==nbins_iso*.15){
      sigeff10[0] = sig_frac/nonfake_events_iso;
      bgrej10[0] = 1-back_frac/fake_events_iso; 
    }

   }

   TGraph *g_iso = new TGraph(nbins_iso,nonfakesPoints_iso,fakesPoints_iso);
   TGraph *g_iso10  = new TGraph(1,sigeff10,bgrej10);

   g_iso->SetMarkerStyle(20);
   g_iso->SetMarkerSize(1);
   g_iso->SetMarkerColor(kBlue);
   g_iso->SetLineWidth(2);
   g_iso->SetLineColor(kBlue);
   g_iso->Draw("ALP");

   g_iso10->SetMarkerStyle(29);
   g_iso10->SetMarkerSize(2);
   g_iso10->SetMarkerColor(kBlack);

   g_iso->GetXaxis()->SetTitle("Signal Efficiency");
   g_iso->GetYaxis()->SetTitle("Background Rejection");

  /////////////////////////////
  // BDT ROC curves          //
  /////////////////////////////

  float fake_events_bdt1 = 0.0;
  float nonfake_events_bdt1 = 0.0;

  //Get skimmed TTrees (copied from /cms/multilepton-2/hsaka/Workspace/pyPlotter-2018Maxi/pyPlotter/FIREMVA/)
  TFile *fake_input_bdt1 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_FakeMuonTree.root" ); 
  std::cout << "--- Using fakes input file: " << fake_input_bdt1->GetName() <<         std::endl;

  TFile *nonfake_input_bdt1 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_NonFakeMuonTree.root" ); 
  std::cout << "--- Using nonfakes input file: " << nonfake_input_bdt1->GetName() <<         std::endl;

  TTree *fake_bdt1 = (TTree*)fake_input_bdt1->Get("rootTupleTreeVeryLoose/tree");
  TTree *nonfake_bdt1 = (TTree*)nonfake_input_bdt1->Get("rootTupleTreeVeryLoose/tree");

  //Histos to store bdt1lation 
  TH1D *fake_bdt1_histo= new TH1D("fake_bdt1_histo","fake_bdt1_histo",40,-1,1);
  TH1D *nonfake_bdt1_histo= new TH1D("nonfake_bdt1_histo","nonfake_bdt1_histo",40,-1,1);

  fake_bdt1->Draw("(BDT)>>fake_bdt1_histo",WeightExpression);
  nonfake_bdt1->Draw("(BDT)>>nonfake_bdt1_histo",WeightExpression);


  fake_events_bdt1 += fake_bdt1_histo->Integral()*lumi;
  fake_bdt1_histo->Scale(lumi);


  nonfake_events_bdt1 += nonfake_bdt1_histo->Integral()*lumi;
  nonfake_bdt1_histo->Scale(lumi);

  cout<<"fake Events: "<<fake_events_bdt1<<endl;
  cout<<"nonfake Events: "<<nonfake_events_bdt1<<endl;

  ////////////////////////////
  //    ROC Curves         ///
  ////////////////////////////

  int nbins_bdt1 = nonfake_bdt1_histo->GetNbinsX();

  Double_t nonfakesPoints_bdt1[nbins_bdt1], fakesPoints_bdt1[nbins_bdt1];

  //goes from left to right (opposite signal bg symmetry as isolation var)
  for ( int i = 0; i <= nbins_bdt1; ++i ) {

    float sig_frac = nonfake_bdt1_histo->Integral(nbins_bdt1-i,nbins_bdt1);
    float back_frac = fake_bdt1_histo->Integral(nbins_bdt1-i,nbins_bdt1);
    nonfakesPoints_bdt1[i] = sig_frac/nonfake_events_bdt1;
    fakesPoints_bdt1[i] = 1-back_frac/fake_events_bdt1;
    //cout<<"Sig_frac: "<<sig_frac<<endl;
    //cout<<"Sig_tot: "<<nonfake_events_bdt1<<endl;
  }

   TGraph *g_bdt1 = new TGraph(nbins_bdt1,nonfakesPoints_bdt1,fakesPoints_bdt1);

   g_bdt1->SetMarkerStyle(20);
   g_bdt1->SetMarkerSize(1);
   g_bdt1->SetMarkerColor(kRed);
   g_bdt1->SetLineWidth(2);
   g_bdt1->SetLineColor(kRed);

  /////////////////////////////
  // Global BDT graphs       //
  /////////////////////////////

   float fake_events_bdt2 = 0.0;
  float nonfake_events_bdt2 = 0.0;

  //Get skimmed TTrees (copied from /cms/multilepton-2/hsaka/Workspace/pyPlotter-2018Maxi/pyPlotter/FIREMVA/)
  TFile *fake_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_TTTrain_FakeMuonTree.root" ); 
  std::cout << "--- Using fakes input file: " << fake_input_bdt2->GetName() <<         std::endl;

  TFile *nonfake_input_bdt2 = TFile::Open( "/cms/mchristos/ANN/FireMVA/outFiles/BDTnoMuonPt_DY_TTTrain_NonFakeMuonTree.root" ); 
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


  ////////////////////////////
  // Global BDT ROC Curve  ///
  ////////////////////////////

  int nbins_bdt2 = nonfake_bdt2_histo->GetNbinsX();

  //Iso fakes Efficiency.
  Double_t nonfakesPoints_bdt2[nbins_bdt2], fakesPoints_bdt2[nbins_bdt2];
  //stores point tagged for .95 nonfakes efficiency


   for ( int i = 0; i <= nbins_bdt2; ++i ) {

    float sig_frac = nonfake_bdt2_histo->Integral(nbins_bdt2-i,nbins_bdt2);
    float back_frac = fake_bdt2_histo->Integral(nbins_bdt2-i,nbins_bdt2);

    nonfakesPoints_bdt2[i] = sig_frac/nonfake_events_bdt2;
    fakesPoints_bdt2[i] = 1-back_frac/fake_events_bdt2;


   }

   TGraph *g_bdt2 = new TGraph(nbins_bdt2,nonfakesPoints_bdt2,fakesPoints_bdt2);

   g_bdt2->SetMarkerStyle(20);
   g_bdt2->SetMarkerSize(1);
   g_bdt2->SetMarkerColor(kGreen);
   g_bdt2->SetLineWidth(2);
   g_bdt2->SetLineColor(kGreen);
   g_bdt2->Draw("ALP");


   g_bdt2->GetXaxis()->SetTitle("Signal Efficiency");
   g_bdt2->GetYaxis()->SetTitle("Background Rejection");
   roc->SaveAs("ROC.png");

  //Draw
   g_iso->Draw("ALP");
   g_bdt2->Draw("ALP SAME");
   g_bdt1->Draw("ALP SAME");


   g_bdt1->GetXaxis()->SetTitle("Signal Efficiency");
   g_bdt1->GetYaxis()->SetTitle("Background Rejection");
   

   //Putting it all together...
   TMultiGraph *mg = new TMultiGraph();
   mg->Add(g_iso);
   mg->Add(g_bdt1);
   mg->Add(g_bdt2);
   mg->Add(g_iso10);
   mg->Draw("ALP");
   mg->SetTitle("Fire MVA Vs Isolation");
   mg->GetXaxis()->SetTitle("Signal Efficiency");
   mg->GetYaxis()->SetTitle("Background Rejection");

   TLegend *legendmg=new TLegend(0.5,0.5,.9,.9);
   //legend->SetHeader("Training Inputs"); // option "C" allows to center the header
   legendmg->AddEntry(g_iso,"TagMuonPOGRelPFIsoDBCorrR04");
   legendmg->AddEntry(g_iso10,"TagMuonPOGRelPFIsoDBCorrR04 == .15");
   legendmg->AddEntry(g_bdt2,"Optimized BDT (no MuonPt) - Trained on TTbar");
   legendmg->AddEntry(g_bdt1,"Optimized BDT (noMuonPt) - Trained on DY");
   
   legendmg->SetBorderSize(0);
   legendmg->Draw();

   roc->SaveAs("ROC_DY_OffDiagonal.png");


}