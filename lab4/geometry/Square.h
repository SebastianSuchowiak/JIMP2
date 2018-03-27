//
// Created by sebastian on 20.03.18.
//

#ifndef JIMP_EXERCISES_SQUARE_H
#define JIMP_EXERCISES_SQUARE_H

#include <Point.h>

namespace geometry {
    class Square {
    public:
        Square(Point point1, Point point2, Point point3, Point point4);
        double Circumference();
        double Area();
    private:
        Point point1, point2, point3, point4;
    };
}

#endif //JIMP_EXERCISES_SQUARE_H
