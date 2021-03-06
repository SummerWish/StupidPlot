#pragma once

#include <memory>
#include <string>
#include <intrin.h>

#include <gdiplus.h>

#include <plot/graphic.h>
#include <plot/types.h>
#include <formula/exp.h>

namespace StupidPlot
{
    namespace Formula
    {
        class ExpDrawer : public Plot::Graphic
        {
        public:
            ExpressionPtr       expression;

            ExpDrawer(
                std::wstring _exp,
                std::map<std::wstring, double> & _constVars,
                Gdiplus::Color _color
                )
                : Plot::Graphic(Plot::GraphicType::FORMULA_EXPRESSION, _color)
            {
                try
                {
                    expression = ExpressionPtr(new Expression(_exp, _constVars));
                    isValid = true;
                }
                catch (std::runtime_error ex)
                {
                    errorMessage = Util::utf8_decode(ex.what());
                    isValid = false;
                }
            }

            virtual bool evalAndTransform(
                double xMin,
                double xMax,
                double canvasLeft,
                double canvasRight,
                double canvasBottom,
                double canvasTop,
                int & n,
                Plot::DoubleArr & x,
                Plot::DoubleArr & y
                )
            {
                UNREFERENCED_PARAMETER(canvasLeft);
                UNREFERENCED_PARAMETER(canvasRight);

                if (!isValid) return false;

                n = clipWidth;
                x = std::shared_ptr<double>(new double[n], array_deleter<double>());
                y = std::shared_ptr<double>(new double[n], array_deleter<double>());
                expression->eval(xMin, xMax, n, x, y);
                batchTransformX(canvasLeft, canvasRight, x.get(), n);
                batchTransformY(canvasBottom, canvasTop, y.get(), n);

                return true;
            }
        };
    }
}