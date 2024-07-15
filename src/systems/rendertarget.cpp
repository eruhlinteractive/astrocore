#include "rendertarget.h"
using namespace Astrocore;

RenderTarget::RenderTarget()
{
    // Default to the current width/height
    SetRenderTargetDimensions(GetScreenWidth(), GetScreenHeight());
}

void RenderTarget::SetRenderTargetDimensions(float width, float height)
{
    if(IsRenderTextureReady(renderTarget))
    {
        UnloadRenderTexture(renderTarget);
    }
    renderTarget = LoadRenderTexture(width, height);
}

void RenderTarget::SetScreenDimensions(float posX, float posY, float scale)
{
    finalPos = {posX, posY};
    finalScale = scale;
}

void RenderTarget::DrawToTarget(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw)
{
    BeginTextureMode(renderTarget);
    BeginMode2D(*renderCamera);

    // Do drawing of each node
    for(int i = 0; i < nodesToDraw->size();i++)
    {
        std::shared_ptr<TreeNode> node = nodesToDraw->at(i).lock();
        if(node->IsDrawn())
        {
            node->Draw();
        }
    }
    EndMode2D();
    EndTextureMode();
}

<<<<<<< HEAD
void RenderTarget::SetActiveCamera(Camera2D* cam)
{
    renderCamera = cam;
}

=======
>>>>>>> 05b9bb25ff425d582a8759aefa8770b315c22ce4
void RenderTarget::DrawToFinal()
{
    DrawTextureEx(renderTarget.texture,finalPos,0, finalScale, WHITE);
}