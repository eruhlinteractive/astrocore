#ifndef RENDERTARGET
#define RENDERTARGET
#include <memory>
#include "../component/transform.h"
#include <vector>
#include "../nodes/treenode.h"

#ifndef RAYLIB_H
#include <raylib.h>
#endif // !RAYLIB_H

// Represents a single render target for a camera
namespace Astrocore
{
    class RenderTarget
    {
        private:
            RenderTexture2D renderTarget;
            Camera2D* renderCamera;
            Vector2 finalPos = {0,0};
            float finalScale = 1;

        public:
            RenderTarget();
            void SetRenderTargetDimensions(float width, float height);  // Set the resolution of the target texture
            void SetScreenDimensions(float posX, float posY, float scale);    // Sets the screen-space size and pos of rendered image
            void DrawToTarget(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw);
            void SetActiveCamera(Camera2D* cam);
            void DrawToFinal();
    };
}

#endif // !RENDERTARGET