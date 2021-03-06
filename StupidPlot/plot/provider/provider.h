#pragma once

#include <vector>
#include <windows.h>
#include <gdiplus.h>

#include <plot/types.h>

using std::vector;

namespace StupidPlot
{
    namespace Plot
    {
        namespace Provider
        {
            struct POINTF
            {
                float x;
                float y;
            };

            class Provider
            {
            protected:
                HDC         hdc;

                int canvasWidth, canvasHeight;
                int canvasOffsetX, canvasOffsetY;

            public:
                Provider(HDC _hdc)
                {
                    hdc = _hdc;
                }

                virtual void drawGridLine(bool vertical, const shared_ptr<int> & points, int length, Gdiplus::Color color) = 0;

                virtual void drawAxis(bool vertical, int axisPos, const shared_ptr<int> & ticks, const shared_ptr<double> & tickLabels, int length, int tickRadius, Gdiplus::Color color) = 0;

                virtual void drawPlotLine(const DoubleArr & x, const DoubleArr & y, int length, Gdiplus::Color color, int width) = 0;

                virtual void beginDraw(int left, int top, int width, int height, Gdiplus::Color bgColor)
                {
                    UNREFERENCED_PARAMETER(bgColor);

                    canvasWidth = width;
                    canvasHeight = height;
                    canvasOffsetX = left;
                    canvasOffsetY = top;
                }

                virtual void endDraw() = 0;
            };

            typedef std::shared_ptr<Provider> ProviderPtr;
        }
    }
}