#ifndef NODE
#define NODE

#include <vector>
#include <memory>
#include "../component/transform.h"
#include <string>
#include "../systems/scenetree.h"
#include "treenode.h"
namespace Astrocore
{
    class Node : public TreeNode
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
        //SceneTree* registeredTree = nullptr; // TODO: Make this a pointer to the scene tree

    public:
        std::string name;
        Node();
        Node(std::string name);
        ~Node();

        void OnTreeEnter();
        void OnTreeExit();
        //virtual void EnterTree(SceneTree* tree);
        //virtual void ExitTree();
        int GetNodeID();
        // Heirarchy access
        Node* GetParent();
        void SetParent(Node* newParent);
        std::vector<Node*> GetAllChildren();
        Node* GetChildAtIndex(int index);
        void AddChild(Node* newChild);
        void RemoveChild(Node* childToRemove);

        inline bool GetInheritsParentTransform() {return inheritParentTransform;}
        void SetInheritsParentTransform(bool shouldInheritParentTransform);
        inline void SetIsWorldMatrixDirty(bool isWorldMatrixDirty){ this->isWorldMatrixDirty = isWorldMatrixDirty; }

        void Update(float deltaTime) override;
        //void FixedUpdate(float deltaTime) override; // TODO:
        // Transform manipulation
        // TODO: Have the two transforms linked, so updating one also updates the other
        Transform2D* GetTransform(); // Local transform
        Transform2D GetWorldTransform();   // Worldspace transform


        // Operator overload
        inline bool operator==(Node& other){return other.GetNodeID() == nodeID; }
    };
}
#endif