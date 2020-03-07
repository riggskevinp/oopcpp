#ifndef PROBABILITIES_H
#define PROBABILITIES_H


class Probabilities
{
public:
    Probabilities(double dub);
    Probabilities();
    double operator &(Probabilities const &obj);
    double operator |(Probabilities &obj);
    double operator ^(Probabilities &obj);
    double operator -(Probabilities &obj);
    double operator ~();
    void operator =(double const &dub);
    void operator =(Probabilities const &obj);
    double getProbability() const;

private:
    double probablity;


};

#endif // PROBABILITIES_H
