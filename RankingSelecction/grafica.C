{
   TFile *h = new TFile("File.root","RECREATE");

   FILE *f1 = fopen("plot.dat","r");
   Int_t i=0;
   Double_t x[158], y[158];
   while (!feof(f1)){ 
      fscanf(f1,"%lf %lf\n",&x[i],&y[i]);
      i++;
   }

//   for(i=0; i<158; i++) cout << x[i] << " "<< y[i] << endl; 
     TGraph* g1 = new TGraph(158,x,y);

     TCanvas *c1 =new TCanvas("c1","Grafica",600,600);
//     c1->SetLogy();
     c1->SetGridx();
     c1->SetGridy();
     g1->SetLineColor(1);
     g1->SetLineStyle(2);
     g1->SetLineWidth(4);
     g1->SetTitle(";Numero de Variables;AUC");
          
//     g1->SetMinimum(0.000000001);
//     g1->SetMaximum(0.0001);

     g1->Draw("ap");

   g1->GetXaxis()->CenterTitle(true);
   g1->GetYaxis()->CenterTitle(true);

   c1->Modified();

//	TLegend *legend = new TLegend(0.5,0.69,0.89,0.87);
//   legend->AddEntry(g1,"Hola","l");
//   legend->Draw();

   h->Write();     
}
