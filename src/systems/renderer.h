#ifndef RENDERER
#define RENDERER

#ifndef RAYLIB_H
#include <raylib.h>
#endif // !RAYLIB_H

#include <memory>
#include "../nodes/node.h"


namespace Astrocore
{
    class Renderer
    {
        //private:
        //    Texture2D renderText;

        public:

        // Basic renderer
        // TODO: Add layer sorting, etc
        void Render(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw);
    };
}

#endif // !RENDERER