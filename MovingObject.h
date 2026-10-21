// Header guards prevents the header file being included several 
// times in a file. This, in turn, prevents function variables being 
// defined more than once. #pragma once is less error prone and makes 
// it so that the compiler itself tracks the header file identity. The 
// developer do not need to define a unique macro for the header file.  
// Using #pragma once is therefore also less susceptible to human errors.
#pragma once

#include <TObject.h>

class MovingObject : public TObject {
public:
    MovingObject();
    MovingObject(Double_t vx, Double_t vy, Double_t vz);
    ~MovingObject() override;

    Double_t Vx() const;
    Double_t Vy() const;
    Double_t Vz() const;

    Double_t Speed() const;
    Double_t HorizontalSpeed() const;

    void SetVelocity(Double_t vx, Double_t vy, Double_t vz);

private:
    Double_t fVx;
    Double_t fVy;
    Double_t fVz;

    ClassDef(MovingObject, 1);
};





