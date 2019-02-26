#ifndef RASTERIZEENGINE_H
#define RASTERIZEENGINE_H

struct Point2D
{
    float x;
    float y;
};

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

class RasterizeEngine
{
public:
    RasterizeEngine();
    virtual ~RasterizeEngine();

    virtual void draw_point(int x, int y, const Color &color) = 0;

public:
    virtual void draw_line_dda(const Point2D &start, const Point2D &end, const Color &color);
    virtual void draw_line_midpoint(const Point2D &start, const Point2D &end, const Color &color);
    virtual void draw_line_bresenham(const Point2D &start, const Point2D &end, const Color &color);
};


#endif // RASTERIZEENGINE_H
