//
//  Shape.cpp
//  Character
//
//  Created by Zerc on 6/24/16.
//
//

#include "Shape.hpp"
ShapeBase* ShapeFactory(enum shapeType type)
{
    switch(type)
    {
        case shape_triangle:
            return new TriangleShape();
            break;
        case shape_ellipse:
            return new EllipseShape();
            break;
        case shape_rectangle:
            return new RectShape();
            break;
        case shape_claw:
            return new ClawShape();
            break;
        default:
            break;
    }
}