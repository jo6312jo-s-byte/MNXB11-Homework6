#include "MovingObject.h"
#include <iostream>
#include <TCanvas.h>

void read() {

    // Initialize pointer to object 
    MovingObject *object{nullptr};

    // Open tree file 
    auto file = TFile::Open("tree_file.root");
    TTree *tree = static_cast<TTree*>(file->Get("tree"));

    // Check if the tree exists
    if (!tree) {
        std::cout << "ERROR: Tree not found..." << std::endl;
    }

    // Set address of object branch
    tree->SetBranchAddress("object", &object);

    // The number of entries
    Long64_t entries = tree->GetEntries();

    // TH2D histogram
    TH2D *h = new TH2D("h", "v_{y} vs v_{x}; v_{x} [m/s]; Vy [m/s]", 100, -1.5, 1.5, 100, -1.5, 1.5);

    // Loop that fills histogram
    for (Long64_t i = 0; i < entries; i++) {

        tree->GetEntry(i);
        h->Fill(object->Vx(), object->Vy());

    }  

    // Remove statistics box so that entire plots are visible
    gStyle->SetOptStat(0); 

    // Center title 
    gStyle->SetTitleX(0.5);       
  
    // Draw and save plot
    TCanvas *c1 = new TCanvas("c1", "Velocity Measurements", 800, 600);
    h->Draw("COLZ");
    c1->SaveAs("velocity_components.pdf");

    // Draw horizontal velocity vs Vz 
    TCanvas *c2 = new TCanvas("c2", "Horizontal velocity vs Vz", 800, 600);

    tree->Draw("object.HorizontalSpeed() : object.Vz() >> htemp(100, -1.5, 1.5, 100, -0.1, 1.5)", "object.Speed()>0.50");
    c2->UseCurrentStyle();

    // Need the pointer for htemp, otherwise the cpp compiler won't find it 
    TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");

    // Set axis labels, title and save scatter plot to file
    htemp->SetTitle("v_{xy} vs v_{z}");
    htemp->GetXaxis()->SetTitle("v_{z} [m/s]");
    htemp->GetYaxis()->SetTitle("v_{xy} [m/s]");
    c2->SaveAs("vxy_vs_vz.pdf");

}