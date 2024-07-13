#ifndef TREENODE
#define TREENODE


namespace Astrocore
{
    // An object that is able to be registered/interacted with in a tree
    class SceneTree; // Forward declaration
    class TreeNode 
    {
    private:
        bool isInTree = false;
        SceneTree* registeredTree = nullptr; // TODO: Make this a pointer to the scene tree
    protected:
        bool isDrawn = false;
        int zIndex = 0;
    
    public:
        virtual void EnterTree(SceneTree* tree){};
        virtual void ExitTree(){};

        virtual void Draw(){};
        void GetZIndex();
        bool IsDrawn() {return isDrawn;};

        virtual void Update(float deltaTime){};
        virtual void FixedUpdate(float deltaTime){};
    };
}

#endif // !TREENODE