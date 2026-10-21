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
    TH2D *h = new TH2D("h", "Vy vs Vx; Vx [m/s]; Vy [m/s]", 100, -1.5, 1.5, 100, -1.5, 1.5);

    // Loop that fills histogram
    for (Long64_t i = 0; i < entries; i++) {

        tree->GetEntry(i);
        h->Fill(object->Vx(), object->Vy());
        std::cout << object->Vx()<< std::endl;
    }

    // Draw and save plot
    TCanvas *c1 = new TCanvas("c1", "velocity measurements", 800, 600);
    h->Draw("COLZ");
    c1->SaveAs("velocity_components.pdf");

}