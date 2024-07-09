#ifndef NODE
#define NODE
#endif

#include <vector>
#include <memory>
#include "../component/transform.h"

namespace Astrocore
{/* data */
    class Node
    {
    static int NODE_INCREMENTOR;
    private:
        void SetNodeID(); // Called internally to create a runtime-unique id
        // Note: Using raw pointers here since we have no ownership over the 
        // child objects
        int nodeID = -1;
        std::vector<Node*> children;
        Node* parent;
        std::unique_ptr<Transform2D> transform;
        bool isInTree = false;
        void* registeredTree; // TODO: Make this a pointer to the scene tree

    public:
        Node(/* args */);
        ~Node();

        void OnTreeEnter(void* tree) { isInTree = true;};
        void OnTreeExit()  { isInTree = false;};
        int GetNodeID();
        // Heirarchy access
        Node* GetParent();
        std::vector<Node*> GetAllChildren();
        Node* GetChildAtIndex(int index);
        void AddChild(Node* newChild);
        void RemoveChild(Node* childToRemove);
        
        // Transform manipulation
        Transform2D* GetTransform(); // Local transform
        Transform2D* GetWorldTransform();   // Worldspace transform


        // Operator overload
        inline bool operator==(Node& other){return other.GetNodeID() == nodeID; }
    };
}