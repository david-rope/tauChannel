{
   TFile *h = new TFile("File.root","RECREATE");

   FILE *f1 = fopen("plot.dat","r");
   Int_t i=0;
   Int_t x[159];
   Double_t y[159];

   while (!feof(f1)){ 
      fscanf(f1,"%d %lf\n",&x[i],&y[i]);
      i++;
   }


   Double_t m, aux;
   Int_t index;
   Int_t j, k;
   
   for(j=0; j<158;j++)
   {
     index=j;   
     m=y[j];      
     for(k=j+1; k<159; k++)  
     {   
       if(m>y[k])
       {
         index=k;
         m=y[k];    
       }
     }

     if(index != j)
     {
       aux=y[j];
       y[j]=y[index];
       y[index]=aux;
       aux=x[j];
       x[j]=x[index];
       x[index]=aux;
     }   

   }

//   for(i=0; i<159;i++)
//   {
//      cout << i << "   "  << x[i] << "   " <<y[i] << endl;    
//   }

   Int_t p[159];
   Double_t r[159],q[159];

   i=0;  
   k=0;
   index=0;
   while(i < 158)
   {
     p[index]=x[i];
     r[index]=x[i];
     q[index]=y[i];

     m=y[i];
     k=i+1;

     while(m == y[k])
     {
       k++; 
     }      

     index++;
     i=k;  
   }   

   
////////////////////////////////////////////////////////////


   for(i=0; i<159; i++) cout << p[i] << " "<< q[i] << endl; 

     TGraph* g1 = new TGraph(41,r,q);

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

////////////////////////////////////////////////////////////


//   for(i=0; i<159;i++)
//   {
//     cout << i << "   "  << p[i] << "   " <<q[i] << endl;    
//   }
   
   FILE *f = fopen("plotSlope.dat","w"); 

   i=0;
   while(p[i]!=0)
   {
     fprintf(f, "Ranking %d\n", p[i]);
     i++;
   }
  
   fclose(f);
   
}




































