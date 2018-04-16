{
	  gROOT->Reset();
	    
	  // Draw histos filled by Geant4 simulation 
	  //   
	  TFile f("Er175.root");
      //TFile f("csv4_h1_1.csv");
		    
	  TCanvas* c1 = new TCanvas("c1", "  ");
	  c1->SetLogy(1);
	  c1->cd();
	  c1->Update();
				  
      TH1D* hist = (TH1D*)f.Get("3");
	  hist->Draw("HIST");    
}  

