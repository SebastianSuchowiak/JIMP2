//
// Created by sebastian on 16.04.18.
//

#ifndef JIMP_EXERCISES_KULA_H
#define JIMP_EXERCISES_KULA_H

#include <cmath>

class Kolo {

public:
    Kolo(double x, double y, double r);
    virtual double Pole();

protected:
    double m_x;
    double m_y;
    double m_r;

};

class Kula: public Kolo {

public:
    Kula(double x, double y, double z, double r);
    double Pole() override;

private:
    double m_z;
};


#endif //JIMP_EXERCISES_KULA_H
