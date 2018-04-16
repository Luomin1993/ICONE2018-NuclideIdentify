{
	  TFile *f = TFile::Open("Ba133.xml","recreate");
	  TFile *mf = TFile::Open("Ba133.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

