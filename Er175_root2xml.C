{
	  TFile *f = TFile::Open("Er175.xml","recreate");
	  TFile *mf = TFile::Open("Er175.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

