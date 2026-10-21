#include "MovingObject.h"
#include <TObject.h>

void write() {

    // Initialize moving object
    MovingObject *object{nullptr};

    // Create ROOT file, "RECREATE" overwrites any instance
    // of ROOT file with same name
    TFile f("tree_file.root", "RECREATE");

    // Create a TTree
    TTree *tree = new TTree("tree", "velocity measurement tree");

    // The branches of the tree
    tree->Branch("object", &object);

    Double_t vx{};
    Double_t vy{};
    Double_t vz{};

    // Initialize object on the heap
    object = new MovingObject();
  
    // Set random seed
    gRandom->SetSeed(42);

    // Fill tree with random data 
    const Int_t N = 10000;
    for (Int_t i = 0; i < N; i++) {
        
        // Random numbers are distributed according to a Gaussian
        // with mean = 0.0 and sigma = 0.30
        vx = gRandom->Gaus(0.0, 0.30);
        vy = gRandom->Gaus(0.0, 0.30);
        vz = gRandom->Gaus(0.0, 0.30);

        // Set new velocity
        object->SetVelocity(vx, vy, vz);

        // Fill tree
        tree->Fill();
    }

    // Delete object 
    delete object;
    
    // save tree
    tree->AutoSave();
    
}