{
	  TFile *f = TFile::Open("Example.xml","recreate");
	  TFile *mf = TFile::Open("No252.root");
	  TH1F *h = (TH1F*)mf->Get("3");
	  f->cd();
	  h->Write();
}  

