#include "renderer.h"

using namespace Astrocore;

Renderer::Renderer()
{
    //SetFinalTargetDimensions(GetScreenWidth(), GetScreenHeight());
    renderTargets = std::map<std::string, RenderTarget*>();

    // Create and add basic rendering target
    basicTarget = new RenderTarget();
    renderTargets.emplace("basic", basicTarget);
}

void Renderer::SetFinalTargetDimensions(float width, float height)
{
    if(IsRenderTextureReady(finalRenderTexture))
    {
        UnloadRenderTexture(finalRenderTexture);
    }

    this->finalRenderTexture = LoadRenderTexture(width, height);
    virtualScreenWidth = GetScreenWidth()/width;

    if(basicTarget != nullptr)
    {
        basicTarget->SetRenderTargetDimensions(width, height);
        basicTarget->SetDestRect({0,0,width, height});
        basicTarget->SetSourceRect({0,0,width, height});
    }
    
    srcRect = {0,0, width, -height};
    destRect = {0,0,(float)GetScreenWidth(), (float)GetScreenHeight()};
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
    if(IsRenderTextureReady(finalRenderTexture))
    {
        UnloadRenderTexture(finalRenderTexture);
    }
}

void Renderer::Render(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw)
{
    BeginDrawing();
    
    // Render each of the targets
    std::map<std::string, RenderTarget*>::iterator it;

    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToTarget(nodesToDraw);
    }

    // Render each of the targets to the final render texture
    BeginTextureMode(finalRenderTexture);
    ClearBackground(WHITE);
    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToFinal();
    }
    EndTextureMode(); // finalRenderTarget

    // Render the final texture to the screen
    DrawTexturePro(finalRenderTexture.texture, srcRect, destRect, {0,0}, 0, WHITE);
    EndDrawing();
}