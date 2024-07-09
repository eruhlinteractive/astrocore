#include "node.h"
using namespace Astrocore;

Node::Node()
{
    if(NODE_INCREMENTOR == NULL)
    {
      NODE_INCREMENTOR  = 0;
    }
    SetNodeID();

    transform = std::unique_ptr<Transform2D>(new Transform2D());
    children = std::vector<Node*>();
}

Node::~Node()
{
    if(isInTree)
    {
        // TODO: De-register from tree (which will call OnTreeExit)
    }

    // Remove ourselves from the child
    parent->RemoveChild(this);

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
    //int indexOfChild
}