#include "rasterizeengine.h"
#include <cmath>

RasterizeEngine::RasterizeEngine()
{

}

RasterizeEngine::~RasterizeEngine()
{

}

void RasterizeEngine::draw_line_dda(const Point2D &start, const Point2D &end, const Color &color)
{
    /*
    float dx = end.x - start.x;
    float dy = end.y - start.y;

    float stride = 0;
    if(std::abs(dy) <= std::abs(dx))
        stride = std::abs(dx);
    else
        stride = std::abs(dy);

    float step_x = 0.0f;
    float step_y = 1.0f;

    if(stride > 0.0f) {
        step_x = dx / static_cast<float>(stride);
        step_y = dy / static_cast<float>(stride);
    }

    float x = start.x;
    float y = start.y;

    for(int i = 0; i < stride; ++i) {
        draw_point(static_cast<int>(x+0.5f),static_cast<int>(y+0.5f),color);
        x += step_x;
        y += step_y;
    }
    */
}

void RasterizeEngine::draw_line_midpoint(const Point2D &start, const Point2D &end, const Color &color)
{

}

void RasterizeEngine::draw_line_bresenham(const Point2D &start, const Point2D &end, const Color &color)
{
    /*
    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    auto plotLow = [&painter,&dx,&dy](int x0, int y0, int x1){
        int yi = 1;
        if(dy<0) {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx;
        int y = y0;

        for(int x = x0; x < x1; ++x) {
            painter->drawPoint(x,y);
            if(D > 0) {
                y += yi;
                D = D - 2 * dx;
            }
            D = D + 2 * dy;
        }
    };

    auto plotHigh = [&painter,&dx,&dy](int x0, int y0, int y1){
        int xi = 1;
        if(dx < 0) {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy;
        int x = x0;
        for(int y = y0; y < y1; ++y) {
            painter->drawPoint(x,y);
            if(D > 0) {
                x += xi;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
        }
    };

    if(std::abs(dy) <= std::abs(dx)) {
        if(dx<=0) {
            plotLow(end.x(),end.y(),start.x());
        } else {
            plotLow(start.x(),start.y(),end.x());
        }
    } else {
        if(dy<=0) {
            plotHigh(end.x(),end.y(),start.y());
        } else {
            plotHigh(start.x(),start.y(),end.y());
        }
    }
    */
}
