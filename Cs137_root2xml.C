{
	  TFile *f = TFile::Open("Cs137.xml","recreate");
	  TFile *mf = TFile::Open("Cs137.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

