{
	  TFile *f = TFile::Open("I131.xml","recreate");
	  TFile *mf = TFile::Open("I131.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

