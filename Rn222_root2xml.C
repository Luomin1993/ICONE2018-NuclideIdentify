{
	  TFile *f = TFile::Open("Rn222.xml","recreate");
	  TFile *mf = TFile::Open("Rn222.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

