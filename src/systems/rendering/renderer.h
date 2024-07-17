#ifndef RENDERER
#define RENDERER

#ifndef RAYLIB_H
#include <raylib.h>
#endif // !RAYLIB_H

#include <memory>
#include "../../nodes/node.h"
#include "rendertarget.h"

namespace Astrocore
{
    class Renderer
    {
        private:
            RenderTexture2D finalRenderTexture;
            float virtualScreenWidth = 1;   // Scaling factor of the finalRenderTarget to fit in the window
            // TODO: Add render bit flags for layers to use
            std::map<std::string, RenderTarget*> renderTargets;
            Rectangle srcRect;
            Rectangle destRect;
            RenderTarget* basicTarget;

        public:
            Renderer();
            ~Renderer();
            void SetFinalTargetDimensions(float width, float height);

            void AddRenderTarget(std::string name, RenderTarget* target);
            RenderTarget* GetRenderTarget(std::string name);

        // Basic renderer
        // TODO: Add layer sorting, etc
            void Render(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw);
    };
}

#endif // !RENDERER