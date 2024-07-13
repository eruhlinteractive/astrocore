#include "renderer.h"

using namespace Astrocore;

void Renderer::Render(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw)
{
    BeginDrawing();
    ClearBackground(WHITE);
    // Do drawing of each node
    for(int i = 0; i < nodesToDraw->size();i++)
    {
        std::shared_ptr<TreeNode> node = nodesToDraw->at(i).lock();
        if(node->IsDrawn())
        {
            node->Draw();
        }
    }

    EndDrawing();
}