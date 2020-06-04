#include "./CMS_lumi.h"

// for re-cast of the limit --> not valid off-shell
static float minDM = 1;
static float maxDM = 62.49;
// for plotting
static float minX = 1;
static float maxX = 1000;
static double minY_dd = 1e-47;
static double maxY_dd = 2e-37;
// step in DM mass for making the plot
static float stepDM = 0.2; // 100 MeV
double const CV = 1e-36;

// calculate the associated dm-nucleon cross section
double dmNucleonXSECScalar(float dmMass, float width, int scale = 0){

  float mN = 0.939;
  float fN = 0.326;

  if(scale == -1)     fN = 0.629;
  else if(scale == 1) fN = 0.260;
  
  float mH = 125;
  float vev = 246;
  float beta = sqrt(1-4*dmMass*dmMass/(mH*mH));
  float numerator = 4*width*pow(mN,4)*pow(fN,2);
  float denominator = pow(mH,3)*pow(vev,2)*beta*pow(dmMass+mN,2);

  return CV*0.3894*1.0e+9*numerator/denominator;
  
}

// calculate the associated dm-nucleon cross section
double dmNucleonXSECFermion(float dmMass, float width, int scale = 0){

  float mN = 0.939;
  float fN = 0.326;

  if(scale == -1)     fN = 0.629;
  else if(scale == 1) fN = 0.260;

  float mH = 125;
  float vev = 246;
  float beta = sqrt(1-4*dmMass*dmMass/(mH*mH));
  float numerator = (8*width*pow(dmMass,2)*pow(mN,4)*pow(fN,2));
  float denominator = pow(mH,5)*pow(vev,2)*pow(beta,3)*pow(dmMass+mN,2);

  return CV*0.3894*1.0e+9*numerator/denominator;
  
}


TGraph* superCDMS();
TGraph* lux();
TGraph* cdmslite();
TGraph* xenon_1txyr();
TGraph* xenon_s2();
TGraph* panda();
TGraph* cresst();
//TGraph* superCDMS();


void makeHiggsPortalPlot(float observedBR, string outputDIR){

  gROOT->SetBatch(kTRUE);
  setTDRStyle();
  system(("mkdir -p "+outputDIR).c_str());

  
  TCanvas* canvas = new TCanvas("canvas","",700,650);
  canvas->cd();
  
  // from BRinv =  GammaInv/(GammaInv+GammaSM)
  float observedGammaInv = observedBR*0.00407/(1-observedBR);

  TGraph* observedBound_scalar = new TGraph();
  TGraph* observedBound_scalar_min = new TGraph();
  TGraph* observedBound_scalar_max = new TGraph();

  TGraph* observedBound_fermion = new TGraph();
  TGraph* observedBound_fermion_min = new TGraph();
  TGraph* observedBound_fermion_max = new TGraph();

  // loop on DM mass values, getting nominal values for lines, and min. and max. values for bands
  int ipoint_fermion = 0;
  int ipoint_scalar = 0;
  for(float dmMass = minDM; dmMass <= maxDM; dmMass = dmMass+stepDM){

    observedBound_fermion->SetPoint(ipoint_fermion,dmMass,dmNucleonXSECFermion(dmMass,observedGammaInv));
    observedBound_fermion_min->SetPoint(ipoint_fermion,dmMass,dmNucleonXSECFermion(dmMass,observedGammaInv,-1));
    observedBound_fermion_max->SetPoint(ipoint_fermion,dmMass,dmNucleonXSECFermion(dmMass,observedGammaInv,1));
    ipoint_fermion++;

    observedBound_scalar->SetPoint(ipoint_scalar,dmMass,dmNucleonXSECScalar(dmMass,observedGammaInv));
    observedBound_scalar_min->SetPoint(ipoint_scalar,dmMass,dmNucleonXSECScalar(dmMass,observedGammaInv,-1));
    observedBound_scalar_max->SetPoint(ipoint_scalar,dmMass,dmNucleonXSECScalar(dmMass,observedGammaInv,1));
    ipoint_scalar++;
  }
  
  // Draw canvas
  TH1* frame = canvas->DrawFrame(minX,minY_dd,maxX,maxY_dd,"");
  frame->GetYaxis()->SetTitle("#sigma^{SI}_{DM-nucleon} [cm^{2}]");
  frame->GetXaxis()->SetTitle("m_{DM} [GeV]");
  frame->GetXaxis()->SetLabelSize(0.032);
  frame->GetYaxis()->SetLabelSize(0.032);
  frame->GetXaxis()->SetTitleSize(0.042);
  frame->GetYaxis()->SetTitleSize(0.042);
  frame->GetYaxis()->SetTitleOffset(1.65);
  frame->GetXaxis()->SetTitleOffset(1.15);
  frame->GetYaxis()->SetRangeUser(minY_dd,maxY_dd);
  canvas->SetLogx();
  canvas->SetLogy();

  gPad->SetLeftMargin(0.14);
  frame->Draw();

  // Set aesthetics for fermion and scalar lines and bands
  int fermion_line_colour = kRed;
  int scalar_line_colour = kOrange - 3;
  int fermion_shade_colour = kRed - 9;
  int scalar_shade_colour = kOrange - 9;
  int nominal_line_width = 3;
  int band_line_width = 0;
  double shade_alpha = 0.5;  // transparency (0. = fully transparent, 1. = opaque)

  observedBound_fermion->SetLineColorAlpha(fermion_line_colour, 1.);
  observedBound_fermion->SetLineWidth(nominal_line_width);
  observedBound_fermion_min->SetLineColorAlpha(fermion_shade_colour, shade_alpha);
  observedBound_fermion_min->SetLineWidth(band_line_width);
  observedBound_fermion_max->SetLineColorAlpha(fermion_shade_colour, shade_alpha);
  observedBound_fermion_max->SetLineWidth(band_line_width);

  observedBound_scalar->SetLineColor(scalar_line_colour);
  observedBound_scalar->SetLineWidth(nominal_line_width);
  observedBound_scalar_min->SetLineColorAlpha(scalar_shade_colour, shade_alpha);
  observedBound_scalar_min->SetLineWidth(band_line_width);
  observedBound_scalar_max->SetLineColorAlpha(scalar_shade_colour, shade_alpha);
  observedBound_scalar_max->SetLineWidth(band_line_width);

  TGraph* observed_fermion_shade = new TGraph();
  TGraph* observed_scalar_shade = new TGraph();
  
  int ipoint_offset = 0;
  for(int n = 0; n < observedBound_fermion_max->GetN(); n++){
    double x,y ;
    observedBound_fermion_max->GetPoint(n,x,y);
    observed_fermion_shade->SetPoint(n,x,y);
    ipoint_offset++;
  }

  int ipoint = 0;
  for(int n = observedBound_fermion_min->GetN() -1; n >= 0; n--){
    double x,y ;
    observedBound_fermion_min->GetPoint(n,x,y);
    observed_fermion_shade->SetPoint(ipoint+ipoint_offset,x,y);    
    ipoint++;
  }

  ipoint_offset = 0;
  for(int n = 0; n < observedBound_scalar_max->GetN(); n++){
    double x,y ;
    observedBound_scalar_max->GetPoint(n,x,y);
    observed_scalar_shade->SetPoint(n,x,y);
    ipoint_offset++;
  }

  ipoint = 0;
  for(int n = observedBound_scalar_min->GetN() -1; n >= 0; n--){
    double x,y ;
    observedBound_scalar_min->GetPoint(n,x,y);
    observed_scalar_shade->SetPoint(ipoint+ipoint_offset,x,y);    
    ipoint++;
  }

  int shade_style = 1001;  // solid fill
  observed_fermion_shade->SetFillStyle(shade_style);
  observed_fermion_shade->SetFillColorAlpha(fermion_shade_colour, shade_alpha);
  observed_fermion_shade->SetLineColor(fermion_line_colour);  // Sets line colour in legend
  observed_fermion_shade->SetLineWidth(nominal_line_width);  // Sets line width in legend
  observed_scalar_shade->SetFillStyle(shade_style);
  observed_scalar_shade->SetFillColorAlpha(scalar_shade_colour, shade_alpha);
  observed_scalar_shade->SetLineColor(scalar_line_colour);
  observed_scalar_shade->SetLineWidth(nominal_line_width);

  // Create lines for direct detection limits and draw
  TGraph *lM0 = xenon_1txyr();
  TGraph *lM1 = lux();
  TGraph *lM2 = panda();
  TGraph *lM3 = cdmslite();
  TGraph *lM4 = cresst();
  //TGraph *lM5 = superCDMS();
  TGraph *lM6 = xenon_s2();

  lM0->SetLineColor(kAzure+8);
  lM1->SetLineColor(kBlue+2);
  lM2->SetLineColor(kBlue);
  lM3->SetLineColor(kGreen);
  lM4->SetLineColor(kGreen+2);
  //lM5->SetLineColor(kSpring+8);
  lM6->SetLineColor(kViolet);

  lM0->Draw("L SAME");
  lM6->Draw("L SAME");
  lM1->Draw("L SAME");
  lM2->Draw("L SAME");
  lM3->Draw("L SAME");
  lM4->Draw("L SAME");
  //lM5->Draw("L SAME");

  // Draw fermion and scalar lines and bands on top
  observed_scalar_shade->Draw("F same");
  observedBound_scalar_min->Draw("L SAME");
  observedBound_scalar_max->Draw("L SAME");

  observed_fermion_shade->Draw("F same");
  observedBound_fermion_min->Draw("L SAME");
  observedBound_fermion_max->Draw("L SAME");
  observedBound_fermion->Draw("L SAME");
  observedBound_scalar->Draw("L SAME");

  // Add annotations and legends
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextFont(72);
  tex->SetLineWidth(2);
  tex->SetTextSize(0.034);
  tex->DrawLatex(0.67,0.86,"#it{90% CL Limits}");
  tex->DrawLatex(0.67,0.81,Form("#it{B(H#rightarrow inv) < %.2f}",observedBR));

  TLatex* tex1 = new TLatex();
  tex1->SetNDC();
  tex1->SetTextFont(72);
  tex1->SetLineWidth(2);
  tex1->SetTextSize(0.034);
  tex1->DrawLatex(0.65,0.75,"#it{Higgs portal models}");

  TLegend *leg_1 = new TLegend(0.69,0.64,0.91,0.73,NULL,"brNDC");
  leg_1->SetFillStyle(0);
  leg_1->SetBorderSize(0);
  leg_1->SetFillColor(0);
  leg_1->AddEntry(observed_fermion_shade,"Fermion DM","FL");
  leg_1->AddEntry(observed_scalar_shade,"Scalar DM","FL");
  leg_1->Draw("same");

  TLatex* tex2 = new TLatex();
  tex2->SetNDC();
  tex2->SetTextFont(72);
  tex2->SetLineWidth(2);
  tex2->SetTextSize(0.034);
  tex2->DrawLatex(0.65,0.59,"#it{Direct Detection}");
  
  TLegend *leg_2 = new TLegend(0.69,0.37,0.93,0.57,NULL,"brNDC");
  leg_2->SetFillStyle(0);
  leg_2->SetBorderSize(0);
  leg_2->SetFillColor(0);
  leg_2->AddEntry(lM0, "XENON1T", "L");
  leg_2->AddEntry(lM6, "XENON1T (S2)", "L");
  leg_2->AddEntry(lM1, "LUX", "L");
  leg_2->AddEntry(lM2, "PandaX-II", "L");
  leg_2->AddEntry(lM3, "CDMSlite", "L");
  leg_2->AddEntry(lM4, "CRESST-III", "L");
  //leg_2->AddEntry(lM5, "SuperCDMS", "L");
  leg_2->Draw("same");
  
  CMS_lumi(canvas,"137");
  canvas->RedrawAxis("samesaxis");
   
  canvas->SaveAs((outputDIR+"/higgsPortalDM.png").c_str(),"png");
  canvas->SaveAs((outputDIR+"/higgsPortalDM.pdf").c_str(),"pdf");  
}


TGraph *superCDMS() {
  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];

  i0++; lX[i0] = 3.5946953342351033; lY[i0]= 9.848667679721256e-40;
  i0++; lX[i0] = 3.75095871431554;   lY[i0] = 4.7369269651270765e-40;
  i0++; lX[i0] = 4.055296786109914;  lY[i0] = 1.731452556791703e-40;
  i0++; lX[i0] = 4.859185478655973;  lY[i0] = 3.335637195211155e-41;
  i0++; lX[i0] = 5.443071002530319;  lY[i0] = 1.4979478319670555e-41;
  i0++; lX[i0] = 6.568479751568511;  lY[i0] = 4.257347230887382e-42;
  i0++; lX[i0] = 7.759712545805536;  lY[i0] = 1.4200965776277166e-42;
  i0++; lX[i0] = 10.195931085528889; lY[i0] = 5.073387251235342e-43;
  i0++; lX[i0] = 13.636666866311272; lY[i0] = 2.930133564061426e-43;
  i0++; lX[i0] = 18.04552501288121;  lY[i0] = 2.0321090962591862e-43;
  i0++; lX[i0] = 23.377104302070727; lY[i0] = 1.941241066769181e-43;
  i0++; lX[i0] = 29.857390063416926; lY[i0] = 2.0321090962591862e-43;

  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;
}


TGraph *cresst(){
  
  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];

  i0++; lX[i0] = 0.16; lY[i0] = 4.73589e-34;
  i0++; lX[i0] = 0.208; lY[i0] = 5.72634e-36;
  i0++; lX[i0] = 0.2704; lY[i0] = 7.3854e-37;
  i0++; lX[i0] = 0.35152; lY[i0] = 2.62798e-37;
  i0++; lX[i0] = 0.456976; lY[i0] = 1.06657e-37;
  i0++; lX[i0] = 0.594069; lY[i0] = 4.2227e-38;
  i0++; lX[i0] = 0.772289; lY[i0] = 1.66904e-38;
  i0++; lX[i0] = 1; lY[i0] = 7.35987e-39;
  i0++; lX[i0] = 1.5; lY[i0] = 2.7698e-39;
  i0++; lX[i0] = 2.25; lY[i0] = 5.6334e-40;
  i0++; lX[i0] = 3.375; lY[i0] = 1.12663e-40;
  i0++; lX[i0] = 5.0625; lY[i0] = 3.79581e-41;
  i0++; lX[i0] = 7.59375; lY[i0] = 1.11803e-41;
  i0++; lX[i0] = 11.3906; lY[i0] = 3.26202e-42;
  i0++; lX[i0] = 17.0859; lY[i0] = 1.48371e-42;
  i0++; lX[i0] = 25.6289; lY[i0] = 1.06977e-42;
  i0++; lX[i0] = 38.4434; lY[i0] = 1.03226e-42;
  i0++; lX[i0] = 57.665; lY[i0] = 1.22993e-42;
  i0++; lX[i0] = 86.4976; lY[i0] = 1.64711e-42;
  i0++; lX[i0] = 129.746; lY[i0] = 2.33581e-42;
     
  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;

}


TGraph *lux(){

  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];
  
  i0++; lX[i0] = 5.230202675339297; lY[i0] =    9.999999999999836e-43;
  i0++; lX[i0] = 5.320175096324759; lY[i0] =    7.906043210907605e-43;
  i0++; lX[i0] = 5.411695265464636; lY[i0] =      6.105402296585314e-43;
  i0++; lX[i0] = 5.50478980785497; lY[i0] =       4.4984326689693795e-43;
  i0++; lX[i0] = 5.599485806609297; lY[i0] =     3.393221771895274e-43;
  i0++; lX[i0] = 5.695810810737687; lY[i0] =     2.6203985288583326e-43;
  i0++; lX[i0] = 5.793792843161313; lY[i0] =     2.0716983998953036e-43;
  i0++; lX[i0] = 5.893460408864902; lY[i0] =     1.5264179671752116e-43;
  i0++; lX[i0] = 5.99484250318941; lY[i0] =      1.2067926406393165e-43;
  i0++; lX[i0] = 6.202868761603334; lY[i0] =     8.891593339164587e-44;
  i0++; lX[i0] = 6.309573444801932; lY[i0] =     6.707035611184258e-44;
  i0++; lX[i0] = 6.418113712446068; lY[i0] =     4.941713361323818e-44;
  i0++; lX[i0] = 6.6408278506348415; lY[i0] =    3.556480306223092e-44;
  i0++; lX[i0] = 6.989473207273485; lY[i0] =     2.500110382617941e-44;
  i0++; lX[i0] = 7.232014017781835; lY[i0] =     1.7575106248547966e-44;
  i0++; lX[i0] = 7.611696816847943; lY[i0] =     1.0481131341546917e-44;
  i0++; lX[i0] = 8.011313071180073; lY[i0] =     7.19685673001147e-45;
  i0++; lX[i0] = 8.576958985908941; lY[i0] =     4.941713361323818e-45;
  i0++; lX[i0] = 9.027251779484576; lY[i0] =     3.641031949310677e-45;
  i0++; lX[i0] = 9.501185073181436; lY[i0] =     2.7464741148160504e-45;
  i0++; lX[i0] = 10.347008713411984; lY[i0] =    1.8858632787726555e-45;
  i0++; lX[i0] = 11.268130079648545; lY[i0] =    1.2354828882567482e-45;
  i0++; lX[i0] = 12.697075549188032; lY[i0] =    7.722449945836333e-46;
  i0++; lX[i0] = 14.803703235666655; lY[i0] =    4.826957437677881e-46;
  i0++; lX[i0] = 16.398903672222477; lY[i0] =    3.4738921120831546e-46;
  i0++; lX[i0] = 19.448624389373624; lY[i0] =    2.4420530945486748e-46;
  i0++; lX[i0] = 22.67543125870801; lY[i0] =     1.930697728883277e-46;
  i0++; lX[i0] = 26.892404165083185; lY[i0] =    1.4563484775012623e-46;
  i0++; lX[i0] = 31.89361179185746; lY[i0] =     1.2354828882567684e-46;
  i0++; lX[i0] = 39.13745601980384; lY[i0] =     1.0481131341546917e-46;
  i0++; lX[i0] = 44.85923383437637; lY[i0] =     1.073030940526174e-46;
  i0++; lX[i0] = 57.937928431613145; lY[i0] =    1.2067926406393363e-46;
  i0++; lX[i0] = 78.75829328777596; lY[i0] =     1.422529313485372e-46;
  i0++; lX[i0] = 100; lY[i0] =                   1.6768329368110306e-46;
  i0++; lX[i0] = 129.1549665014884; lY[i0] =     2.0235896477251638e-46;
  i0++; lX[i0] = 161.21572750178856; lY[i0] =    2.4420530945486748e-46;
  i0++; lX[i0] = 204.696827180752; lY[i0] =      3.0888435964774975e-46;
  i0++; lX[i0] = 264.3761185749101; lY[i0] =     3.906939937054621e-46;
  i0++; lX[i0] = 335.68035509467273; lY[i0] =    5.059197488435864e-46;
  i0++; lX[i0] = 426.2158829015325; lY[i0] =     6.250551925274027e-46;
  i0++; lX[i0] = 532.0175096324763; lY[i0] =     7.906043210907734e-46;
  i0++; lX[i0] = 652.8521141127848; lY[i0] =     1e-45;
  i0++; lX[i0] = 787.5829328777596; lY[i0] =     1.2067926406393363e-45;
  i0++; lX[i0] = 983.0884473994828; lY[i0] =     1.4909716571840752e-45;
  i0++; lX[i0] = 1248.2348288165172; lY[i0] =    1.976598071701651e-45;
  i0++; lX[i0] = 1584.893192461114; lY[i0] =     2.500110382617941e-45;
  i0++; lX[i0] = 1978.3188827841623; lY[i0] =    3.088843596477498e-45;
  i0++; lX[i0] = 2386.5897868585835; lY[i0] =    3.727593720314923e-45;
  i0++; lX[i0] = 2879.116638022353; lY[i0] =     4.498432668969453e-45;
  i0++; lX[i0] = 3593.813663804626; lY[i0] =     5.557736586486892e-45;
  i0++; lX[i0] = 4485.923383437636; lY[i0] =     6.866488450043026e-45;
  i0++; lX[i0] = 5994.8425031894085; lY[i0] =    9.102981779915264e-45;
  i0++; lX[i0] = 7875.829328777596; lY[i0] =     1.2354828882567482e-44;
  i0++; lX[i0] = 11461.96978456578; lY[i0] =     1.7575106248547966e-44;
  i0++; lX[i0] = 16967.959918688968; lY[i0] =   2.6203985288583324e-44;
  i0++; lX[i0] = 26437.61185749096; lY[i0] =    4.0949150623803854e-44;
  i0++; lX[i0] = 35330.366949927295; lY[i0] =   5.557736586486892e-44;
  i0++; lX[i0] = 48026.56010546725; lY[i0] =    7.543120063354607e-44;
  i0++; lX[i0] = 68712.70363478754; lY[i0] =    1.0730309405261566e-43;
  i0++; lX[i0] = 98308.84473994808; lY[i0] =    1.4909716571840507e-43;
    
  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;
    
}


TGraph *cdmslite(){
  
  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];

  // From CDMSlite Run 3 (https://arxiv.org/abs/1808.09098)
  i0++; lX[i0] = 1.500; lY[i0] = 1.7839e-38;
  i0++; lX[i0] = 1.600; lY[i0] = 5.3022e-39;
  i0++; lX[i0] = 1.700; lY[i0] = 1.7048e-39;
  i0++; lX[i0] = 1.900; lY[i0] = 3.7503e-40;
  i0++; lX[i0] = 2.000; lY[i0] = 2.0532e-40;
  i0++; lX[i0] = 2.200; lY[i0] = 8.3277e-41;
  i0++; lX[i0] = 2.500; lY[i0] = 3.2145e-41;
  i0++; lX[i0] = 2.700; lY[i0] = 2.3265e-41;
  i0++; lX[i0] = 3.000; lY[i0] = 1.6343e-41;
  i0++; lX[i0] = 3.200; lY[i0] = 1.4104e-41;
  i0++; lX[i0] = 3.500; lY[i0] = 1.1584e-41;
  i0++; lX[i0] = 3.700; lY[i0] = 1.0323e-41;
  i0++; lX[i0] = 4.000; lY[i0] = 8.6569e-42;
  i0++; lX[i0] = 4.200; lY[i0] = 7.5927e-42;
  i0++; lX[i0] = 4.500; lY[i0] = 6.6421e-42;
  i0++; lX[i0] = 4.700; lY[i0] = 5.8828e-42;
  i0++; lX[i0] = 5.000; lY[i0] = 5.3553e-42;
  i0++; lX[i0] = 5.500; lY[i0] = 4.5599e-42;
  i0++; lX[i0] = 6.000; lY[i0] = 4.1868e-42;
  i0++; lX[i0] = 6.500; lY[i0] = 3.9183e-42;
  i0++; lX[i0] = 7.000; lY[i0] = 3.7979e-42;
  i0++; lX[i0] = 8.000; lY[i0] = 3.6132e-42;
  i0++; lX[i0] = 9.000; lY[i0] = 3.5806e-42;
  i0++; lX[i0] = 10.00; lY[i0] = 3.6453e-42;
    
  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;
  
}


TGraph *xenon_1txyr(){
  
  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];
  
  i0++; lX[i0] = 6.2662857571501345; lY[i0] = 8.543266059341143e-44;
  i0++; lX[i0] = 6.546165237459862; lY[i0] = 6.138103229381494e-44;
  i0++; lX[i0] = 6.779666254444859; lY[i0] = 4.273357542109263e-44;
  i0++; lX[i0] = 7.083000795258592; lY[i0] = 2.837863178135969e-44;
  i0++; lX[i0] = 7.464615600011724; lY[i0] = 1.826158468270242e-44;
  i0++; lX[i0] = 7.9359351889724685; lY[i0] = 1.0861690808398076e-44;
  i0++; lX[i0] = 8.364000229168054; lY[i0] = 6.562873255542149e-45;
  i0++; lX[i0] = 9.047496326054578; lY[i0] = 4.028359352386536e-45;
  i0++; lX[i0] = 9.787282397354216; lY[i0] = 2.358574357958542e-45;
  i0++; lX[i0] = 10.773534028219355; lY[i0] = 1.2966432776590116e-45;
  i0++; lX[i0] = 11.653761493745419; lY[i0] = 8.085228676856251e-46;
  i0++; lX[i0] = 13.051491437918491; lY[i0] = 4.885273571519322e-46;
  i0++; lX[i0] = 14.744023607773366; lY[i0] = 2.9986313485755303e-46;
  i0++; lX[i0] = 16.94685704302921; lY[i0] = 1.929612418460103e-46;
  i0++; lX[i0] = 19.309090031421555; lY[i0] = 1.3433993325988877e-46;
  i0++; lX[i0] = 21.99798577079349; lY[i0] = 1.0608183551394396e-46;
  i0++; lX[i0] = 25.498135022600614; lY[i0] = 9.062853448588874e-47;
  i0++; lX[i0] = 29.81276216010585; lY[i0] = 7.742636826811214e-47;
  i0++; lX[i0] = 34.85334634119006; lY[i0] = 7.502632520822492e-47;
  i0++; lX[i0] = 42.366398703467055; lY[i0] = 7.681925401780325e-47;
  i0++; lX[i0] = 49.31031717163866; lY[i0] = 8.245923781774311e-47;
  i0++; lX[i0] = 58.65047988876358; lY[i0] = 8.921283702446966e-47;
  i0++; lX[i0] = 70.36461542082742; lY[i0] = 1.0118781198504426e-46;
  i0++; lX[i0] = 83.68907499954075; lY[i0] = 1.147701792233362e-46;
  i0++; lX[i0] = 102.15715500762107; lY[i0] = 1.3647174196395528e-46;
  i0++; lX[i0] = 127.98931328428989; lY[i0] = 1.622767907196007e-46;
  i0++; lX[i0] = 154.8790045783498; lY[i0] = 1.9913394573407126e-46;
  i0++; lX[i0] = 200.88081263549006; lY[i0] = 2.5618105424761687e-46;
  i0++; lX[i0] = 249.49149885765476; lY[i0] = 3.193548412908898e-46;
  i0++; lX[i0] = 315.2849237925243; lY[i0] = 4.044246393116117e-46;
  i0++; lX[i0] = 391.58580600176094; lY[i0] = 4.962796825169922e-46;
  i0++; lX[i0] = 490.57577025301464; lY[i0] = 6.284787504342158e-46;
  i0++; lX[i0] = 583.4467421081572; lY[i0] = 7.473159878245431e-46;
  i0++; lX[i0] = 687.904332649574; lY[i0] = 8.886238162743408e-46;
  i0++; lX[i0] = 892.2373394747145; lY[i0] = 1.1253355826007646e-45;
  i0++; lX[i0] = 1167.2979372125035; lY[i0] = 1.494028817264169e-45;
  i0++; lX[i0] = 1437.2660133277113; lY[i0] = 1.8333604707298815e-45;
  i0++; lX[i0] = 1754.3565126041958; lY[i0] = 2.2854638641349838e-45;
  i0++; lX[i0] = 2197.877322459486; lY[i0] = 2.849055140905999e-45;
  i0++; lX[i0] = 2826.141743698262; lY[i0] = 3.5516270124862015e-45;
  i0++; lX[i0] = 3665.501539159193; lY[i0] = 4.6415888336127535e-45;
  i0++; lX[i0] = 4552.440310089992; lY[i0] = 5.878016072274875e-45;
  i0++; lX[i0] = 5753.050071199337; lY[i0] = 7.327524259667632e-45;
  i0++; lX[i0] = 6961.778709595096; lY[i0] = 8.921283702446965e-45;
  i0++; lX[i0] = 8497.879610544662; lY[i0] = 1.0861690808398076e-44;
  i0++; lX[i0] = 9594.342745086236; lY[i0] = 1.2319647754934755e-44;

  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;

}


TGraph *panda(){

  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];

  i0++; lX[i0] = 8.047; lY[i0]=  9.798e-45;
  i0++; lX[i0] = 8.461; lY[i0]=  6.708e-45;
  i0++; lX[i0] = 8.928; lY[i0]=  4.787e-45;
  i0++; lX[i0] = 9.387; lY[i0]=  3.399e-45;
  i0++; lX[i0] = 9.421; lY[i0]=  3.399e-45;
  i0++; lX[i0] = 9.764; lY[i0]=  2.805e-45;
  i0++; lX[i0] = 12.856; lY[i0]=  7.239e-46;
  i0++; lX[i0] = 16.737; lY[i0]=  2.890e-46;
  i0++; lX[i0] = 18.758; lY[i0]=  2.084e-46;
  i0++; lX[i0] = 21.322; lY[i0]=  1.543e-46;
  i0++; lX[i0] = 25.468; lY[i0]=  1.190e-46;
  i0++; lX[i0] = 29.148; lY[i0]=  1.035e-46;
  i0++; lX[i0] = 32.424; lY[i0]=  9.577e-47;
  i0++; lX[i0] = 35.559; lY[i0]=  8.907e-47;
  i0++; lX[i0] = 38.174; lY[i0]=  8.680e-47;
  i0++; lX[i0] = 40.691; lY[i0]=  8.614e-47;
  i0++; lX[i0] = 44.938; lY[i0]=  8.706e-47;
  i0++; lX[i0] = 49.981; lY[i0]=  8.868e-47;
  i0++; lX[i0] = 54.806; lY[i0]=  9.103e-47;
  i0++; lX[i0] = 60.955; lY[i0]=  9.296e-47;
  i0++; lX[i0] = 68.274; lY[i0]=  9.845e-47;
  i0++; lX[i0] = 77.561; lY[i0]=  1.065e-46;
  i0++; lX[i0] = 88.110; lY[i0]=  1.169e-46;
  i0++; lX[i0] = 103.701; lY[i0]=  1.325e-46;
  i0++; lX[i0] = 129.162; lY[i0]=  1.606e-46;
  i0++; lX[i0] = 193.418; lY[i0]=  2.173e-46;
  i0++; lX[i0] = 246.077; lY[i0]=  2.717e-46;
  i0++; lX[i0] = 313.057; lY[i0]=  3.507e-46;
  i0++; lX[i0] = 401.093; lY[i0]=  4.596e-46;
  i0++; lX[i0] = 483.863; lY[i0]=  5.703e-46;
  i0++; lX[i0] = 626.596; lY[i0]=  7.227e-46;
  i0++; lX[i0] = 855.682; lY[i0]=  9.723e-46;
  i0++; lX[i0] = 1236.581; lY[i0]=  1.422e-45;
  i0++; lX[i0] = 1724.982; lY[i0]=  1.923e-45;
  i0++; lX[i0] = 2306.110; lY[i0]=  2.546e-45;
  i0++; lX[i0] = 3428.606; lY[i0]=  3.685e-45;
  i0++; lX[i0] = 4748.818; lY[i0]=  5.088e-45;
  i0++; lX[i0] = 6484.752; lY[i0]=  7.024e-45;
  i0++; lX[i0] = 8792.397; lY[i0]=  9.902e-45;

  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;
}


TGraph *xenon_s2(){
  int i0 = -1;
  double *lX = new double[1000];
  double *lY = new double[1000];

  i0++; lX[i0] = 2.73; lY[i0] = 9.288431945297944e-40;
  i0++; lX[i0] = 2.75; lY[i0] = 6.319272619037612e-40;
  i0++; lX[i0] = 2.8; lY[i0] = 2.8374278176528733e-40;
  i0++; lX[i0] = 3.0; lY[i0] = 3.622317320468634e-41;
  i0++; lX[i0] = 3.2; lY[i0] = 1.0093733554860686e-41;
  i0++; lX[i0] = 3.5; lY[i0] = 2.7078662672268526e-42;
  i0++; lX[i0] = 3.7; lY[i0] = 1.4053651850630283e-42;
  i0++; lX[i0] = 4.0; lY[i0] = 6.436687726874196e-43;
  i0++; lX[i0] = 4.2; lY[i0] = 4.211830689805871e-43;
  i0++; lX[i0] = 4.5; lY[i0] = 2.4748344962496106e-43;
  i0++; lX[i0] = 4.7; lY[i0] = 1.8331569741040645e-43;
  i0++; lX[i0] = 5.0; lY[i0] = 1.244977011390317e-43;
  i0++; lX[i0] = 5.2; lY[i0] = 9.956897569635043e-44;
  i0++; lX[i0] = 5.5; lY[i0] = 7.426357511849602e-44;
  i0++; lX[i0] = 5.7; lY[i0] = 6.016687556292615e-44;
  i0++; lX[i0] = 6.0; lY[i0] = 4.782726128564601e-44;
  i0++; lX[i0] = 6.5; lY[i0] = 3.477937573119966e-44;
  i0++; lX[i0] = 7.0; lY[i0] = 2.6917403365161047e-44;
  i0++; lX[i0] = 7.3; lY[i0] = 2.3633842242886736e-44;
  i0++; lX[i0] = 7.5; lY[i0] = 2.1851572197470983e-44;
  i0++; lX[i0] = 7.6; lY[i0] = 9.507393484521254e-45;
  i0++; lX[i0] = 8.0; lY[i0] = 8.121970339723199e-45;
  i0++; lX[i0] = 9.0; lY[i0] = 5.225694212368943e-45;
  i0++; lX[i0] = 10.0; lY[i0] = 3.88510370427872e-45;
  i0++; lX[i0] = 12.0; lY[i0] = 2.7031851636518367e-45;
  i0++; lX[i0] = 14.0; lY[i0] = 2.069587083451545e-45;
  i0++; lX[i0] = 17.0; lY[i0] = 1.81961709679351e-45;
  i0++; lX[i0] = 17.25; lY[i0] = 1.8095084702151397e-45;
  i0++; lX[i0] = 17.35; lY[i0] = 5.666378567261857e-46;
  i0++; lX[i0] = 18.0; lY[i0] = 5.2416538497478174e-46;
  i0++; lX[i0] = 19.0; lY[i0] = 4.9590827190295596e-46;
  i0++; lX[i0] = 20.0; lY[i0] = 4.777418769166447e-46;
  i0++; lX[i0] = 30.0; lY[i0] = 4.123409777894107e-46;
  i0++; lX[i0] = 35.0; lY[i0] = 4.331329363201274e-46;
  i0++; lX[i0] = 40.0; lY[i0] = 4.561705661798635e-46;
  i0++; lX[i0] = 50.0; lY[i0] = 5.1651794764129515e-46;
  i0++; lX[i0] = 80.0; lY[i0] = 7.373854045315929e-46;
  i0++; lX[i0] = 100.0; lY[i0] = 8.95490641313236e-46;

  TGraph *lLimit = new TGraph(i0,lX,lY);
  lLimit->SetLineWidth(3.);
  return lLimit;
}