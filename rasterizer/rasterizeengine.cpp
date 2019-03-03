#include "rasterizeengine.h"
#include <cmath>
#include <iostream>

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
    int x = sx;
    int y = sy;
    int step_x = 0;
    int step_y = 0;

    if(dx > 0)
        step_x = 1;
    else if(dx < 0)
        step_x = -1;

    if(dy > 0)
        step_y = 1;
    else if(dy < 0)
        step_y = -1;

    if(dy==0) { // k = 0
        for(int i = 0; i != dx; i += step_x, x+= step_x) {
            draw_point(x,y,color);
        }
    } else if(dx == 0) {
        for(int i = 0; i != dy; i += step_y, y+= step_y) {
            draw_point(x,y,color);
        }
    } else if(std::abs(dy) == std::abs(dx)){
        for(int i = 0; i != dx; i += step_x,x += step_x, y+= step_y) {
            draw_point(x,y,color);
        }
    } else if(std::abs(dy)<std::abs(dx)) { // 0 < |k| < 1
        int p = step_y * dx;
        int lower_step = 2 * dy * step_x;
        int upper_step = 2 * step_y * dx - 2 * dy * step_x;
        if((dx>0 && dy<0) || (dx<0 && dy>0)) { // -1 < k < 0
            for(int i = 0; i != dx; i += step_x, x += step_x) {
                if(p <= 0) {
                    draw_point(x,y,color);
                    p -= lower_step;
                } else if(p > 0) {
                    draw_point(x,y,color);
                    y += step_y;
                    p += upper_step;
                }
            }
        } else if((dx>0 && dy>0) || (dx<0 && dy<0)) { // 0 < k < 1
            for(int i = 0; i != dx; i += step_x, x += step_x) {
                if(p <= 0) {
                    draw_point(x,y,color);
                    p += lower_step;
                } else if(p > 0) {
                    draw_point(x,y,color);
                    y += step_y;
                    p -= upper_step;
                }
            }
        }
    } else if(std::abs(dy) > std::abs(dx)) {
        int p = step_x * dy;
        int lower_step = 2 * dx * step_y;
        int upper_step = 2 * step_x * dy - 2 * dx * step_y;
        if((dx>0 && dy<0) || (dx<0 && dy>0)) {
            for(int i = 0; i != dy; i += step_y, y += step_y) {
                if(p<=0) {
                    draw_point(x,y,color);
                    p -= lower_step;
                } else if(p>0) {
                    draw_point(x,y,color);
                    x += step_x;
                    p += upper_step;
                }
            }
        } else if((dx>0 && dy>0) || (dx<0 && dy<0)) {
            for(int i = 0; i != dy; i += step_y, y += step_y) {
                if(p<=0) {
                    draw_point(x,y,color);
                    p += lower_step;
                } else if(p>0) {
                    draw_point(x,y,color);
                    x += step_x;
                    p -= upper_step;
                }
            }
        }
    }
}
