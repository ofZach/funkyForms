//
//  Shapes.cpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#include "Shapes.hpp"

ShapeBase* ShapeFactory(enum ShapeType type)
{
    switch(type)
    {
        case PEBEL1:
            return new ShapePebel1();
            break;
        case PEBEL2:
            return new ShapePebel2();
            break;
        case PEBEL3:
            return new ShapePebel3();
            break;
        case BLOB1:
            return new ShapeBlob1();
            break;
        default:
            break;
    }
}