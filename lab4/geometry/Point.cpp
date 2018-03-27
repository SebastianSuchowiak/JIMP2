//Definicja znajduje się w pliku Point.cpp
#include <cmath>
#include <ostream>
#include "Point.h"
namespace geometry {
    using ::std::ostream;
    using ::std::endl;
    using ::std::pow;
    using ::std::sqrt;

    /* Aby wskazać, ze definicja funkcji dotyczy metody danej klasy
      stosujemy tzw. operator zasięgu - "::"
    */

    //Specjalna inicjalizacja zmiennych. Zmienne są inicjowane
    //nim zostanie wywołane ciało konstruktora
    Point::Point() : x_(0), y_(0) {
    }

    double Point::GetX() const {
        return x_;
    }

    void Point::SetY(double y_) {
        Point::y_ = y_;
    }

    void Point::SetX(double x_) {
        Point::x_ = x_;
    }

    double Point::GetY() const {
        return y_;
    }

    Point::Point(double x, double y): x_(x), y_(y) {

    }

    Point::~Point() {

    }

    double Point::Distance(const Point &other) const {
        return sqrt(pow(GetX() - other.GetX(), 2) + pow(GetY() - other.GetY(), 2));
    }

    void Point::ToString(ostream *out) const {
        (*out) << "(" << GetX() << ";" << GetY() << ")";
    }
}