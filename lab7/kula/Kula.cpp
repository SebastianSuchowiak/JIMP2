//
// Created by sebastian on 16.04.18.
//

#include "Kula.h"

Kolo::Kolo(double x, double y, double r) :
        m_x{x},
        m_y{y},
        m_r{r}{}

double Kolo::Pole() {
    return M_1_PI*pow(m_r, 2);
}

Kula::Kula(double x, double y, double z, double r) : Kolo(x, y, r) {
    m_z = z;
}

double Kula::Pole() {
    return M_1_PI*4*pow(m_r, 2);
}
