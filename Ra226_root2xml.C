{
	  TFile *f = TFile::Open("Ra226.xml","recreate");
	  TFile *mf = TFile::Open("Ra226.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

