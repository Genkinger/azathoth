#include "AzRenderTarget.hpp"


namespace Az{
    RenderTarget::RenderTarget(int width, int height) : mHeight(height), mWidth(width) {}
    int RenderTarget::GetWidth() const { return mWidth; }
    int RenderTarget::GetHeight() const { return mHeight; }
}