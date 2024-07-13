#ifndef NODE
#define NODE

#include <vector>
#include <memory>
#include "../component/transform.h"
#include <string>

namespace Astrocore
{
    class SceneTree;
    class Node
    {
    static int NODE_INCREMENTOR;
    private:
        
        void SetNodeID(); // Called internally to create a runtime-unique id
        // Note: Using raw pointers here since we have no ownership over the 
        // child objects
        int nodeID = -1;

        bool inheritParentTransform = true;
        bool isWorldMatrixDirty = true;    // True if the parent matrix has changed

        std::vector<Node*> children;
        Node* parent = nullptr;
        std::unique_ptr<Transform2D> transform;
        std::unique_ptr<Transform2D> worldTransform;
        bool isInTree = false;
        SceneTree* registeredTree = nullptr; // TODO: Make this a pointer to the scene tree

    public:
        std::string name;
        Node();
        Node(std::string name);
        ~Node();

        virtual void OnTreeEnter(SceneTree* tree) { isInTree = true;};
        virtual void OnTreeExit()  { isInTree = false;};
        int GetNodeID();
        // Heirarchy access
        Node* GetParent();
        void SetParent(Node* newParent);
        std::vector<Node*> GetAllChildren();
        Node* GetChildAtIndex(int index);
        void AddChild(Node* newChild);
        void RemoveChild(Node* childToRemove);

        // Gameloop
        virtual void Update(float deltaTime){};
        virtual void FixedUpdate(float deltaTime){};

        inline bool GetInheritsParentTransform() {return inheritParentTransform;}
        void SetInheritsParentTransform(bool shouldInheritParentTransform);
        inline void SetIsWorldMatrixDirty(bool isWorldMatrixDirty){ this->isWorldMatrixDirty = isWorldMatrixDirty; }

        // Transform manipulation
        // TODO: Have the two transforms linked, so updating one also updates the other
        Transform2D* GetTransform(); // Local transform
        Transform2D GetWorldTransform();   // Worldspace transform


        // Operator overload
        inline bool operator==(Node& other){return other.GetNodeID() == nodeID; }
    };
}
#endif