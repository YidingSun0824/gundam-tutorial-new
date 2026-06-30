int nEvents{int(1E6)};

struct Event{
  int reaction{-1};
  int selection{-1};
  double enu{std::nan("unset")};
  double pmu{std::nan("unset")};
  double pp{std::nan("unset")};
  double asimovWeight{0.05};
  TClonesArray par1{ "TGraph", 1 };
  TClonesArray par2{ "TGraph", 1 };
  TClonesArray par3{ "TGraph", 1 };
};

void buildInputRootFile(){

  gRandom = new TRandom3(202404); // Initialize with a UUID;

  auto* file = TFile::Open("./inputs/datasets/mydataset.root", "RECREATE");
  auto* tree = new TTree("events", "events");

  Event e{};

  tree->Branch("enu", &e.enu);
  tree->Branch("pmu", &e.pmu);
  tree->Branch("pp", &e.pp);
  tree->Branch("reaction", &e.reaction);
  tree->Branch("selection", &e.selection);
  tree->Branch("asimovWeight", &e.asimovWeight);
  tree->Branch("par1_TGraph", &e.par1);
  tree->Branch("par2_TGraph", &e.par2);
  tree->Branch("par3_TGraph", &e.par3);

  double par_x[7]  = { -3,   -2,   -1,   0,    1,    2,    3   };
  double par1_y[7] = {  1.6,  1.3,  1.1,  1.0,  1.1,  1.3,  1.6 }; // symmetric U-shape
  double par2_y[7] = {  0.8,  0.9,  1.0,  1.0,  1.2,  1.4,  1.6 }; // monotone rise
  double par3_y[7] = {  1.4,  1.2,  1.1,  1.0,  0.9,  0.8,  0.7 }; // monotone fall

  double fraction{0.1}; // shape2/shape1
  auto fShape1 = std::make_unique<TF1>("fShape1", "ROOT::Math::chisquared_pdf(x, 4)", 0, 15);
  auto fShape2 = std::make_unique<TF1>("fShape2", "ROOT::Math::chisquared_pdf(x, 5)", 0, 15);

  double buffer;
  for( int iEvent = 0 ; iEvent < nEvents ; iEvent++ ){

    // let's have an interaction with a given reaction:
    buffer = gRandom->Rndm();
    if     ( buffer < 0.6  ){ e.reaction = 1; }
    else if( buffer < 0.8  ){ e.reaction = 2; }
    else if( buffer < 0.95 ){ e.reaction = 3; }
    else if( buffer < 0.98 ){ e.reaction = 4; }
    else if( buffer < 0.99 ){ e.reaction = 5; }
    else                    { e.reaction = 6; }

    // reaction 1 is the most probable
    if(e.reaction == 1){
      // create the kinematics
      e.enu = fShape1->GetRandom(gRandom);
      e.pmu = std::max( 0., e.enu*(0.95 + 0.05*gRandom->Gaus(0, 1)) - 0.1 );
      e.pp = 0.1*fShape1->GetRandom(gRandom);

      // how has it been detected?
      buffer = gRandom->Rndm();
      if     ( buffer < 0.8  ){ e.selection =  1; }
      else if( buffer < 0.85 ){ e.selection =  2; }
      else if( buffer < 0.95 ){ e.selection =  3; }
      else                    { e.selection = -1; } // invisible
    }
    else {
      e.enu = fShape2->GetRandom(gRandom);
      e.pmu = std::max( 0., e.enu*(0.8 + 0.1*gRandom->Gaus(0, 1)) - 0.2 );
      e.pp = 0.1*fShape2->GetRandom(gRandom);

      buffer = gRandom->Rndm();
      if     ( buffer < 0.15 ){ e.selection =  1; }
      else if( buffer < 0.2  ){ e.selection =  2; }
      else if( buffer < 0.85 ){ e.selection =  3; }
      else if( buffer < 0.95 ){ e.selection =  4; }
      else                    { e.selection = -1; }
    }
    e.par1.Clear("C");  new (e.par1[0]) TGraph(7, par_x, par1_y);
    e.par2.Clear("C");  new (e.par2[0]) TGraph(7, par_x, par2_y);
    e.par3.Clear("C");  new (e.par3[0]) TGraph(7, par_x, par3_y);

    tree->Fill();
  }


  file->WriteObject(tree, "events");
  file->Close();
  std::cout << "File writen in " << file->GetPath() << std::endl;

  exit(0);
}
