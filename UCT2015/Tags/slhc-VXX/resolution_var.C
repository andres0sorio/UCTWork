TGraphErrors * readTypeThree( const char * fname) 
{

  ifstream in;
  in.open(fname); //
  
  double en, flux, fluxerr;

  double offset = 5;

  TGraphErrors * graphT3 = new TGraphErrors(); 

  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en >> flux >> fluxerr; //we read 3 columns of data
    
    graphT3->SetPoint( i , en + offset , flux);
    graphT3->SetPointError( i,  0.0, fluxerr);
    
    ++i;
    
  }

  std::cout << "Total points read: " << i << std::endl;
  
  in.close();

  return graphT3;

}

void makePlots() {

  //. Plots of separate data and different data formats
  //.
  //. The available data formats and their matching Graph objects are:
  //. 6 columns data (x,y, x1, x2, y1, y2) == TGraphAsymmErrors
  //. 4 columns data (x,y, xerr, yerr) == TGraphErrors
  //. 3 columns data (x,y, yerr) == TGraphErros ( xerr = 0.0)
  //. 2 columns data (x,y) == TGraph
  //.
  //.... 
  
  int ndataset = 0;
  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  
  // 1. 3 columns data
  
  TGraphErrors * graphT3 = readTypeThree("logs/reso_vs_pt_Stg1.csv");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  
  graphT3 = readTypeThree("logs/reso_vs_pt_Stg2.csv");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;

  graphT3 = readTypeThree("logs/reso_vs_pt_Stg1MC.csv");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  
  graphT3 = readTypeThree("logs/reso_vs_pt_Stg2MC.csv");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);
  
  //If you need log scale on both axis - uncomment the following lines
  //canvas->SetLogx();
  //canvas->SetLogy();
  
  //Set the minimum and maximum for the whole graph
  //Min a max for Axis
  float xmin =  15.0;
  float xmax =  150.0;
  float ymin = 0.001;
  float ymax = 0.50;
  
  //Datasets options (Markers: style, color, size) : You can also do it by hand using the interactive Editor
  int style[15];
  int color[15];
  float size[15];
  
  //For dataset No1
  style[0] = 25;
  color[0] = 2;
  size[0]  = 1.0;
  
  //For dataset No2
  style[1] = 26;
  color[1] = 4;
  size[1]  = 1.0;

  //For dataset No1
  style[2] = 26;
  color[2] = 1;
  size[2]  = 1.0;
  
  //For dataset No2
  style[3] = 26;
  color[3] = 1;
  size[3]  = 1.0;
  
  // Loop over all Graphs and draw them in the Canvas
  // Min,Max for X and Y axis are set on the first Graph that is plotted
  
  ndataset = allgraphs->GetSize(); //Get the ndatasets from the size of the List
  
  TLegend * leg = new TLegend(0.21,0.72,0.44,0.86);
  
  leg->SetBorderSize(0);
  leg->SetTextSize(0.032);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  TList * v_Labels = new TList();
  
  TObjString *label_current;
  label_current = new TObjString( "Stage 1" );
  v_Labels->Add( label_current ); 
  label_current = new TObjString( "Stage 2" );
  v_Labels->Add( label_current ); 
  label_current = new TObjString( "Stage 1 (MC)" );
  v_Labels->Add( label_current ); 
  label_current = new TObjString( "Stage 2 (MC)" );
  v_Labels->Add( label_current ); 

  // Loop now over the List using the index k
  
  for(int k=0; k < ndataset; ++k) {
    
    if( k == 0 ) {
      //this is our first graph and it is special (to define axis min,max)
      ((TGraph*)allgraphs->At(k))->SetMinimum(ymin);
      ((TGraph*)allgraphs->At(k))->SetMaximum(ymax);
      ((TGraph*)allgraphs->At(k))->Draw("AP");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(xmin, xmax);
      //set the color options
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetFillColor( 10 );

      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitle("reco #tau Pt ");
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitle("L1 #tau Et resolution (#sigma)");
      
      ((TGraph*)allgraphs->At(k))->Draw("AP"); // Draw option AP A=draw axis P=draw a marker for the data

      TString stage1Leg = ((TObjString*)v_Labels->At(k))->GetString();
      
      leg->AddEntry( ((TGraph*)allgraphs->At(k)) , stage1Leg.Data() );

    }
    else {
      
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetFillColor( 10 );

      TString stage1Leg = ((TObjString*)v_Labels->At(k))->GetString();
      
      leg->AddEntry( ((TGraph*)allgraphs->At(k)) , stage1Leg.Data() );

      ((TGraph*)allgraphs->At(k))->Draw("P"); // since we have already plotted the axis on the first graph we only need option P
            
    }
    
  }

  leg->Draw();

  TString path("./slhc-plots/resolution/Taus/noPUC/isoStudies");

  std::stringstream saveAs;
  
  saveAs.str("");
  saveAs << path << "/eps/rlx_resolution_Ptbins" << ".eps";
  canvas->SaveAs( saveAs.str().c_str() );
  
  saveAs.str("");
  saveAs << path << "/pdf/rlx_resolution_Ptbins" << ".pdf";
  canvas->SaveAs( saveAs.str().c_str() );

  saveAs.str("");
  saveAs << path << "/png/rlx_resolution_Ptbins" << ".png";
  canvas->SaveAs( saveAs.str().c_str() );
  
  
  /// All done!
  
}

