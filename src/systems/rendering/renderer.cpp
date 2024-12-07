#include "../../../include/astrocore/systems/rendering/renderer.h"

using namespace Astrocore;

Renderer::Renderer()
{
    //SetFinalTargetDimensions(GetScreenWidth(), GetScreenHeight());
    renderTargets = std::map<std::string, RenderTarget*>();

    // Create and add basic rendering target with a cam
    basicTarget = new RenderTarget("basic");
    renderTargets.emplace("basic", basicTarget);
}


void Renderer::UpdateRenderRects(float screenWidth, float screenHeight)
{
    float centerRenderOffsetX = 0;
    float centerRenderOffsetY = 0;
    switch (scaleRenderFlag)
    {
        case SCALE_STRETCH_FILL:
        {
            srcRect = {0, 0, targetRenderResolution.x, targetRenderResolution.y};
            break;
        }
           
        case SCALE_FIT_WIDTH:
        {
            float aspectRatio = targetRenderResolution.x / targetRenderResolution.y;
            float widthFillPercent = targetRenderResolution.x /(float)GetScreenWidth();
            float newHeight = (float)targetRenderResolution.y * (widthFillPercent * aspectRatio);
           
            centerRenderOffsetY = (-newHeight/2.0);
            //centerRenderOffsetY = -screenWidthDiff;
            srcRect = {0, 0, targetRenderResolution.x, newHeight};
            break;
        }
    }

    destRect = {centerRenderOffsetX, centerRenderOffsetY, (float)GetScreenWidth(), (float)GetScreenHeight()};
}

void Renderer::SetFinalTargetDimensions(float width, float height)
{
    // track the initial dimensions to maintain the 
    Vector2 initialDimensions = targetRenderResolution;

    if(IsRenderTextureValid(finalRenderTexture))
    {
        UnloadRenderTexture(finalRenderTexture);
    }

    targetRenderResolution = {width, height};

    this->finalRenderTexture = LoadRenderTexture(width, height);
    SetTextureWrap(finalRenderTexture.texture, TEXTURE_WRAP_CLAMP);


    if(basicTarget != nullptr)
    {
        basicTarget->SetRenderTargetDimensions(width, height);
        basicTarget->SetDestRect({0,0,width, height});
        basicTarget->SetSourceRect({0,0,width, height});
    }

    UpdateRenderRects(GetScreenWidth(), GetScreenHeight());
    
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
    if(IsRenderTextureValid(finalRenderTexture))
    {
        UnloadRenderTexture(finalRenderTexture);
    }
}

void Renderer::SetClearColor(Color newColor)
{
    clearColor = newColor;        
}


void Renderer::SetRenderStretchMode(RenderScaleFlag modeFlag)
{
    scaleRenderFlag = modeFlag;
}


void Renderer::Render(std::vector<std::weak_ptr<TreeNode>>* nodesToDraw)
{
    // Recalculate the render sizes
    if(IsWindowResized())
    {
        UpdateRenderRects(GetScreenWidth(), GetScreenHeight());
    }

    BeginDrawing();
    ClearBackground(RED);
    // Render each of the targets
    std::map<std::string, RenderTarget*>::iterator it;

    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToTarget(nodesToDraw);
    }

    // Render each of the targets to the final render texture
    BeginTextureMode(finalRenderTexture);
    ClearBackground(clearColor);
    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToFinal();
    }
    EndTextureMode(); // finalRenderTarget

    // Render the final texture to the screen
    DrawTexturePro(finalRenderTexture.texture, srcRect, destRect, {0,0}, 0, WHITE);
    EndDrawing();
}