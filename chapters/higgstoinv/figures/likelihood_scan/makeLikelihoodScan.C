#include "../CMS_lumi.h"

class likelihoodPoint {

public:

  likelihoodPoint(float r, float nll){
    r_ = r;
    nll_ = nll;
  }

  bool operator < (const likelihoodPoint & a) const{
    if(r_ < a.r_) return true;
    else return false;
  }

  float r_;
  float nll_;

};


TGraph* get_points_and_sort(TTree* limit_tree, TGraph* limit_graph){
  int ipoint = 0;
  float min  = 0;

  TTreeReader reader(limit_tree);
  TTreeReaderValue<float> r (reader,"r");
  TTreeReaderValue<float> deltaNLL (reader,"deltaNLL");

  while(reader.Next()){
    if(*r < 0)
      continue;
    if(2*(*deltaNLL) < min)
      min = 2*(*deltaNLL);
  }
  reader.SetEntry(0);
  
  while(reader.Next()){
    if(*r < 0)
      continue;
    limit_graph->SetPoint(ipoint, *r, 2*(*deltaNLL)+fabs(min));
    ipoint++;
  }
  limit_graph->Sort();

  return limit_graph;
}


// code to plot likelihood scans
void makeLikelihoodScan(string outputPlots){

  gROOT->SetBatch(kTRUE);
  setTDRStyle();

  system(("mkdir -p "+outputPlots).c_str());

  TCanvas* canvas = new TCanvas ("canvas","",600,600);
  canvas->cd();

  TFile* file_scan_combined_exp = new TFile("./2017/combined_exp.root", "READ");
  TFile* file_scan_ttH_exp = new TFile("./2017/ttH_exp.root", "READ");
  TFile* file_scan_VH_exp = new TFile("./2017/VH_exp.root", "READ");
  TFile* file_scan_ggH_exp = new TFile("./2017/ggH_exp.root", "READ");
  TFile* file_scan_monojet_exp = new TFile("./2017/Monojet_exp.root", "READ");
  // TFile* file_scan_monojet_obs = new TFile("higgsCombineTest_monojet_obs.MultiDimFit.mH125.root", "READ");

  // Define TTrees that get the limit
  TTree* limit_scan_combined_exp = (TTree*) file_scan_combined_exp->Get("limit");
  TTree* limit_scan_ttH_exp = (TTree*) file_scan_ttH_exp->Get("limit");
  TTree* limit_scan_VH_exp = (TTree*) file_scan_VH_exp->Get("limit");
  TTree* limit_scan_ggH_exp = (TTree*) file_scan_ggH_exp->Get("limit");
  TTree* limit_scan_monojet_exp = (TTree*) file_scan_monojet_exp->Get("limit");
  //TTree* limit_scan_monojet_obs = (TTree*) file_scan_monojet_obs->Get("limit");

  // Define TGraphs that are formatted and actually plotted
  TGraph* scan_combined_exp = new TGraph();
  TGraph* scan_ttH_exp = new TGraph();
  TGraph* scan_VH_exp = new TGraph();
  TGraph* scan_ggH_exp = new TGraph();
  TGraph* scan_monojet_exp = new TGraph();
  //TGraph* scan_monojet_obs = new TGraph();

  // Add points to the graphs
  scan_combined_exp = get_points_and_sort(limit_scan_combined_exp, scan_combined_exp);
  scan_ttH_exp = get_points_and_sort(limit_scan_ttH_exp, scan_ttH_exp);
  scan_VH_exp = get_points_and_sort(limit_scan_VH_exp, scan_VH_exp);
  scan_ggH_exp = get_points_and_sort(limit_scan_ggH_exp, scan_ggH_exp);
  scan_monojet_exp = get_points_and_sort(limit_scan_monojet_exp, scan_monojet_exp);
  //scan_monojet_obs = get_points_and_sort(limit_scan_monojet_obs, scan_monojet_obs);

  double line_width = 3;
  double obs_line_style = 3;  // solid
  double exp_line_style = 7;  // dashed

  //// Produce the final plot
  scan_combined_exp->GetXaxis()->SetTitle("B(H #rightarrow inv)");
  scan_combined_exp->GetXaxis()->SetTitleOffset(1.1);
  scan_combined_exp->GetYaxis()->SetTitle("-2 #Delta Log(L)");
  scan_combined_exp->GetYaxis()->SetTitleOffset(1.1);
  scan_combined_exp->GetXaxis()->SetRangeUser(0, 1);
  scan_combined_exp->GetYaxis()->SetRangeUser(0, 10);
  scan_combined_exp->SetLineColor(kBlack);
  scan_combined_exp->SetLineWidth(line_width);
  scan_combined_exp->SetLineStyle(exp_line_style);
  scan_combined_exp->Draw("AL");
  //scan_combined_obs->SetLineColor(kBlack);
  //scan_combined_obs->SetLineWidth(obs_line_style);
  //scan_combined_obs->Draw("Lsame");

  scan_ttH_exp->SetLineColor(kBlue);
  scan_ttH_exp->SetLineWidth(line_width - 1);
  scan_ttH_exp->SetLineStyle(exp_line_style);
  scan_ttH_exp->Draw("Lsame");

  scan_VH_exp->SetLineColor(kRed);
  scan_VH_exp->SetLineWidth(line_width - 1);
  scan_VH_exp->SetLineStyle(exp_line_style);
  scan_VH_exp->Draw("Lsame");

  scan_ggH_exp->SetLineColor(kGreen);
  scan_ggH_exp->SetLineWidth(line_width - 1);
  scan_ggH_exp->SetLineStyle(exp_line_style);
  scan_ggH_exp->Draw("Lsame");

  scan_monojet_exp->SetLineColor(kOrange);
  scan_monojet_exp->SetLineWidth(line_width - 1);
  scan_monojet_exp->SetLineStyle(exp_line_style);
  scan_monojet_exp->Draw("Lsame");

  //scan_monoj_obs->SetLineColor(kOrange);
  //scan_monoj_obs->SetLineWidth(line_width - 1);
  //scan_monoj_obs->SetLineStyle(obs_line_style);
  //scan_monoj_obs->Draw("Lsame");

  // Legend for each process
  TLegend leg (0.75, 0.17, 0.93, 0.37);
  leg.SetFillColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  leg.SetTextSize(0.034);
  leg.SetTextFont(42);
  leg.AddEntry(scan_ttH_exp, "ttH", "L");
  leg.AddEntry(scan_VH_exp, "VH", "L");
  leg.AddEntry(scan_ggH_exp, "ggH", "L");
  leg.AddEntry(scan_monojet_exp, "Monojet", "L");
  //leg.AddEntry(scan_monoj_obs, "ggH-tagged", "L");
  leg.Draw("same");

  // Legend for combined curves
  TLegend leg2 (0.58, 0.17, 0.74, 0.37);
  leg2.SetFillColor(0);
  leg2.SetFillStyle(0);
  leg2.SetBorderSize(0);
  //leg2.AddEntry(scan_combined_obs, "Observed", "L");
  leg2.AddEntry(scan_combined_exp, "Expected", "L");
  leg2.Draw("same");

  CMS_lumi(canvas, "41.5");
  canvas->SaveAs((outputPlots+"/scan_profile_likelihood.pdf").c_str(), "pdf");  
}
