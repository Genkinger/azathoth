#pragma once


namespace Az{
    class RenderTarget{
        protected:
            int     mWidth;
            int     mHeight;
            RenderTarget(int width, int height);
        public:
            int GetHeight() const;
            int GetWidth() const;
    };
}