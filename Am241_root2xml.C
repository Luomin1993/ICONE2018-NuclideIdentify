{
	  TFile *f = TFile::Open("Am241.xml","recreate");
	  TFile *mf = TFile::Open("Am241.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

