#include "node.h"
#include <algorithm>
#include <raymath.h>
using namespace Astrocore;

int Node::NODE_INCREMENTOR = 0;

Node::Node()
{
    SetNodeID();
    this->transform = std::unique_ptr<Transform2D>(new Transform2D());
    children = std::vector<Node*>();
}

Node::~Node()
{
    if(isInTree)
    {
        // TODO: De-register from tree (which will call OnTreeExit)
    }

    if(parent != nullptr)
    {
        // Remove ourselves from the child
        parent->RemoveChild(this);
    }
   
    // Delete children
    for(Node* child : children)
    {
        delete child;
        child = nullptr;
    }
}

void Node::SetNodeID()
{
    int id = NODE_INCREMENTOR;
    NODE_INCREMENTOR++;
    nodeID = id;
}

int Node::GetNodeID()
{
    return nodeID;
}

void Node::AddChild(Node* newChild)
{
    std::vector<Node*>::iterator it = std::find(children.begin(), children.end(), newChild);

    // Already has the child: don't do anything
    if(it != children.end())
    {
        return;
    }
    children.push_back(newChild);
    newChild->SetParent(this);
}

void Node::RemoveChild(Node* childToRemove)
{
     std::vector<Node*>::iterator it = std::find(children.begin(), children.end(), childToRemove);

    if(it != children.end())
    {
        children.erase(it);
        return; 
    }
}

void Node::SetParent(Node* newParent)
{
    if(parent != nullptr)
    {
        parent->RemoveChild(this);
    }
    if(newParent != parent)
    {
        parent = newParent;
    }
    //newParent->AddChild(this);
}

Node* Node::GetChildAtIndex(int index)
{
    // Bounds check
    if(index < 0 || index > children.size())
    {
        return nullptr;
    }
    return children.at(index);

}

Transform2D* Node::GetTransform()
{
    return transform.get();
}

Transform2D Node::GetWorldTransform()
{
    if(parent == nullptr)
    {
        Transform2D* t = this->transform.get();
        return Transform2D(t);
    }
    Matrix worldMat = MatrixMultiply(parent->GetWorldTransform().GetMatrix(), MatrixInvert(transform->GetMatrix()));
    return Transform2D(worldMat);
}
