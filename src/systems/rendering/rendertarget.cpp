#include "rendertarget.h"
using namespace Astrocore;

RenderTarget::RenderTarget()
{
}

void RenderTarget::SetRenderTargetDimensions(float width, float height)
{
    if(IsRenderTextureReady(renderTarget))
    {
        UnloadRenderTexture(renderTarget);
    }
    
    renderTarget = LoadRenderTexture(width, height);
}

void RenderTarget::SetSourceRect(Rectangle src)
{
   sourceRect = src;
}

void RenderTarget::SetDestRect(Rectangle dest)
{
    destRect = dest;
}

void RenderTarget::DrawToTarget(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw)
{
   
    BeginTextureMode(renderTarget);
    BeginMode2D(*renderCamera);
    ClearBackground(BLANK);

    // Do drawing of each node
    for(int i = 0; i < nodesToDraw->size();i++)
    {
        std::shared_ptr<TreeNode> node = nodesToDraw->at(i).lock();
        if(node->IsDrawn())
        {
            node->Draw();
        }
    }
    
    DrawRectangle(renderCamera->target.x + 10, renderCamera->target.y + 10,10,10,RED);
    //DrawRectangle(sourceRect.x + sourceRect.width/2.0 + renderCamera->target.x, sourceRect.y + sourceRect.height/2.0 + renderCamera->target.y,100,100,RED);
    EndMode2D();
    EndTextureMode();
   
    //DrawTexture(renderTarget.texture, 0, 0, WHITE);
}

void RenderTarget::SetActiveCamera(Camera2D* cam)
{
    renderCamera = cam;
}

void RenderTarget::DrawToFinal()
{   
    //Rectangle source = sourceRect;
    //source.height = -sourceRect.height; // Flip y of rendering to texture
    DrawTexturePro(renderTarget.texture, sourceRect, destRect, {0, 0}, 0, WHITE);
    //DrawTexture(renderTarget.texture,0,0,WHITE);
}