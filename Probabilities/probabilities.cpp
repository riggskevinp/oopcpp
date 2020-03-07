#include "probabilities.h"
#include <stdexcept>

Probabilities::Probabilities(double dub)
{
    if(dub < 0 || dub > 1){ // refactor?  Add helper function for valid double check?
        this->probablity = 0;
    } else{
        this->probablity = dub;
    }
}

Probabilities::Probabilities():
    probablity(0)
{

}

double Probabilities::operator &(Probabilities const &obj)
{
    return this->getProbability() * obj.getProbability();
}

void Probabilities::operator =(const double &dub)
{
    if(dub < 0 || dub > 1){
        throw std::runtime_error("Invalid double");
    } else{
        this->probablity = dub;
    }
}

void Probabilities::operator =(const Probabilities &obj)
{
    this->probablity = obj.getProbability();
}

double Probabilities::getProbability() const
{
    return this->probablity;
}
