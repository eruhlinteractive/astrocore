#include "renderer.h"

using namespace Astrocore;

Renderer::Renderer()
{
    //SetFinalTargetDimensions(GetScreenWidth(), GetScreenHeight());
    renderTargets = std::map<std::string, RenderTarget*>();
}

void Renderer::SetFinalTargetDimensions(float width, float height)
{
    if(IsRenderTextureReady(finalRenderTarget))
    {
        UnloadRenderTexture(finalRenderTarget);
    }

    this->finalRenderTarget = LoadRenderTexture(width, height);
    virtualScreenWidth = GetScreenWidth()/width;
}

void Renderer::AddRenderTarget(std::string name, RenderTarget* target)
{
    renderTargets.insert({name, target});
}

RenderTarget* Renderer::GetRenderTarget(std::string name)
{
    return renderTargets.at(name);
}

Renderer::~Renderer()
{
    if(IsRenderTextureReady(finalRenderTarget))
    {
        UnloadRenderTexture(finalRenderTarget);
    }
}

void Renderer::Render(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw)
{
    BeginDrawing();
    ClearBackground(WHITE);
    // Render each of the targets
    std::map<std::string, RenderTarget*>::iterator it;
    
    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToTarget(nodesToDraw);
    }

    // Render each of the targets to the final render texture
    BeginTextureMode(finalRenderTarget);
    ClearBackground(WHITE);
    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToFinal();
    }

    EndTextureMode(); // finalRenderTarget

    // Render the final texture to the screen
    DrawTextureEx(finalRenderTarget.texture,{0,0}, 0, virtualScreenWidth, WHITE);
    EndDrawing();
}