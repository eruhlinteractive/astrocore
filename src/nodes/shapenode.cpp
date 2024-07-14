#include "shapenode.h"

using namespace Astrocore;

ShapeNode::ShapeNode()
{
    shapesToDraw = std::vector<Shape>();
}

ShapeNode::ShapeNode(Shape initialShape) : ShapeNode()
{
    this->shapesToDraw.push_back(initialShape);
}


void ShapeNode::Draw()
{
    for(auto shape : this->shapesToDraw)
    {
        if(shape.isFilled)
        {
            // TODO: Draw with triangle fan
        }
        else
        {
            for(int i=0; i < shape.points.size() -1; i++ )
            {
                DrawLineEx(shape.points[i], shape.points[i+1], shape.lineWidth, shape.color);
            }
            if(shape.isClosed)
            {
                DrawLineEx(shape.points[shape.points.size()-1], shape.points[0], shape.lineWidth, shape.color);
            }
        }
    }
}