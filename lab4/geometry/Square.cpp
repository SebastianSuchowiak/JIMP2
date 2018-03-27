//
// Created by sebastian on 20.03.18.
//

#include <algorithm>
#include "Square.h"

namespace geometry {

    Square::Square(Point apoint1, Point apoint2, Point apoint3, Point apoint4) {
        double minSide = ;
        double maxSide = std::max(apoint4.Distance(apoint3), apoint4.Distance(apoint2), apoint4.Distance(apoint1));
        double a = 2 * pow(minSide, 2);
        double b = pow(maxSide, 2);
        if (apoint1 == std::min(apoint4.Distance(apoint3), apoint4.Distance(apoint2), apoint4.Distance(apoint1))) {
            point1 = apoint1;
            point2 = apoint2;
            point3 = apoint3;
            point4 = apoint4;
        } else {
            point1 = Point(0,0);
            point2 = Point(0,0);
            point3 = Point(0,0);
            point4 = Point(0,0);
        }
    }

    double Square::Circumference() {
        return std::min(point1.Distance(point2), point1.Distance(point3)) * 4;
    }

    double Square::Area() {
        return pow(std::min(point1.Distance(point2), point1.Distance(point3)), 2);
    }

}