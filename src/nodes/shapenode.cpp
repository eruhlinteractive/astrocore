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

    Matrix transMat = GetWorldTransform().GetMatrix();
    for(auto shape : shapesToDraw)
    {
        if(shape.isFilled)
        {
            // TODO: Draw with triangle fan
        }
        else
        {
            for(int i=0; i < shape.points.size() -1; i++ )
            {

                DrawLineEx(Vector2Transform(shape.points[i],transMat), Vector2Transform(shape.points[i+1],transMat), shape.lineWidth, shape.color);
            }
            if(shape.isClosed)
            {
                DrawLineEx(Vector2Transform(shape.points[shape.points.size()-1],transMat), Vector2Transform(shape.points[0], transMat), shape.lineWidth, shape.color);
            }
        }
    }
}