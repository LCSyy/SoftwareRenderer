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
}

void RasterizeEngine::draw_line_midpoint(const Point2D &start, const Point2D &end, const Color &color)
{

}

void RasterizeEngine::draw_line_bresenham(const Point2D &start, const Point2D &end, const Color &color)
{
    int sx = static_cast<int>(start.x);
    int sy = static_cast<int>(start.y);
    int ex = static_cast<int>(end.x);
    int ey = static_cast<int>(end.y);

    int dx = ex - sx;
    int dy = ey - sy;

    int stride;
    int step_x = 0;
    int step_y = 0;

    if(dx>0) step_x = 1;
    else if(dx<0) step_x = -1;
    if(dy>0) step_y = 1;
    else if(dy<0) step_y = -1;

    if(std::abs(dy) < std::abs(dx)) {
        stride = dx;
        for(; sx != ex; sx += step_x) {

        }
    } else {
        stride = dy;

        for(; sy != ey; sy += step_y) {

        }
    }

    /*

    auto plotLow = [this, &dx,&dy, &color](int x0, int y0, int x1){
        int yi = 1;
        if(dy<0) {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx;
        int y_ = y0;

        for(int x_ = x0; x_ < x1; ++x_) {
            draw_point(x_,y_,color);
            if(D > 0) {
                y_ += yi;
                D = D - 2 * dx;
            }
            D = D + 2 * dy;
        }
    };

    auto plotHigh = [this,&dx,&dy, &color](int x0, int y0, int y1){
        int xi = 1;
        if(dx < 0) {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy;
        int x_ = x0;
        for(int y_ = y0; y_ < y1; ++y_) {
            draw_point(x_,y_,color);
            if(D > 0) {
                x_ += xi;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
        }
    };

    if(std::abs(dy) <= std::abs(dx)) {
        if(dx<=0) {
            plotLow(ex,ey,sx);
        } else {
            plotLow(sx,sy,ex);
        }
    } else {
        if(dy<=0) {
            plotHigh(ex,ey,sy);
        } else {
            plotHigh(sx,sy,ey);
        }
    }
    */
}
