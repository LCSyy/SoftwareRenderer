# Software Renderer

## 直线扫描转换算法

### DDA算法（数字微分法）
在绘制直线时，给定直线上两点P0(x0,y0)，P1(x1,y1)，以及根据直线微分方程 `y=kx+b`，通过x值的变化来计算对应y值，或者反过来根据y值的变化计算x值。以前一种方式为例：

起始点的x<sub>i</sub> = x0, 则下一点的x值为： x<sub>i+1</sub> = x0 + stepX。 则可得 y<sub>i+1</sub> = y<sub>i</sub> + k * stepX。

```
stepX的计算。沿x的变化方向计算直线的各点的坐标值时，在x轴方向上，应该是一次移动一个像素的。向右移动时，需要加一，向左移动时需要减一。
```

在 k <= 1时，单纯通过以上公式绘制的直线是正常和符合我们想要的结果的。但是当斜率 k > 1时，就会发现绘制的直线点变稀疏、不连续了。

斜率k值大于1，直线上的多个点可能x值相同但y值不同，而又是按照x的增加来计算y值，一些点没有被绘制。

解决的办法就是针对k值是否大于1进行分别处理。在|k|<=1时，按照x进行计算，|k|>1时，按照y进行计算。

按照y值进行计算时，公式变为：y<sub>i+1</sub> = y<sub>i</sub> + 1，x<sub>i+1</sub> = x0 + stepX / k.

**代码实现**
```
draw_line(p0,p1) {
    dx = p1.x - p0.x;
    dy = p1.y - p0.y;

    increment = 0;

    if(abs(dy)<=abs(dx)) {
        increment = abs(dx);
    } else {
        increment = abs(dy);
    }

    // increment = 0 时的默认值
    step_x = 0;
    step_y = 1;

    if(increment) {
        step_x = dx / increment;
        step_y = dy / increment;
    }

    x = p0.x;
    y = po.y;

    for(i = 0; i < increment; ++i) {
        //  加 0.5 的作用是消除浮点数转换为整型时的误差。
        set_pixel(int(x+0.5),int(y+0.5),color);
        x += step_x;
        y += step_y;
    }
}

```

**总结**
DDA算法将直线的方程中存在的乘法运算转换为了加法运算，提高了运算效率。

### Bresenham算法

主要参考[wikipedia - Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)

Bresenham算法的基本思想是：直线上的点绘制到栅格中时，对于x或者y值而言都有两个可选的像素位置。通过比较可选像素离理论点的距离来决定绘制到那个像素。

y = k * x + b

(x0,y0) (x1,y1)

0 < |k| < 1:

y(i) = k * x(i) + b
y_lower(i) = y_draw(i-1)
y_upper(i) = y_draw(i-1) + step_y

d(i) = y_upper(i) - y(i) - y(i) + y_lower(i)
= y_draw(i-1) + y_draw(i-1) + step_y  - 2 * (k * x(i) + b)
= 2 * y_draw(i-1) + step_y - 2 * k * x(i) - 2 * b
= 2 * y_draw(i-1) + step_y - 2 * k * (x0 + i * step_x) - 2 * b
= 2 * y_draw(i-1) + step_y - 2 * k * x0 - 2 * k * i * step_x - 2 * b
= 2 * y_draw(i-1) - 2 * k * i * step_x + step_y - 2 * k * x0 - 2 * b

p(i) = dx * d(i)
= 2 * y_draw(i-1) * dx - 2 * k * i * step_x * dx + step_y * dx - 2 * k * x0 * dx - 2 * b * dx
= 2 * y_draw(i-1) * dx - 2 * dy * i * step_x + step_y * dx - 2 * dy * x0 - 2 * b * dx
= 2 * y_draw(i-1) * dx - 2 * dy * i * step_x + step_y * dx - 2 * dy * x0 - 2 * (y0 - dy/dx * x0) * dx
= 2 * y_draw(i-1) * dx - 2 * dy * i * step_x + step_y * dx - 2 * dy * x0 - 2 * y0 * dx + 2 * dy * x0
= 2 * y_draw(i-1) * dx - 2 * dy * i * step_x + step_y * dx - 2 * y0 * dx
= 2 * y_draw(i-1) * dx - 2 * dy * i * step_x + C

C = step_y * dx - 2 * y0 * dx
p(0) = 2 * y0 * dx + C
     = step_y * dx

p(i+1) = p(i) + 2 * [y_draw(i) - y_draw(i-1)] * dx - 2 * dy * step_x

以上公式是根据x的递增推导计算的，满足 0 < |k| < 1的情况，且公式p(i)中乘了包含dx,dy，其正负未知，需分情况分别处理：


1 < |k|:

x(i) = [y(i) - b] / k
x_lower(i) = x_draw(i-1)
x_upper(i) = x_draw(i-1) + step_x

d(i) = x_upper(i) - x(i) - x(i) + x_lower(i)
= 2 * x_draw(i-1) + step_x - 2 * x(i)
= 2 * x_draw(i-1) + step_x - 2 * [(y(i) - b) / k]
= 2 * x_draw(i-1) + step_x - 2 * [y0 + i * step_y - b / k]
= 2 * x_draw(i-1) + step_x - 2 * y0/k - 2 * i * step_y/k + 2 * b / k

p(i) = dy * d(i)
= 2 * x_draw(i-1) * dy + step_x * dy - 2 * y0 * dx - 2 * i * step_y * dx + 2 * b * dx
= 2 * x_draw(i-1) * dy - 2 * i * step_y * dx + step_x * dy - 2 * y0 * dx + 2 * b * dx
= 2 * x_draw(i-1) * dy - 2 * i * step_y * dx + step_x * dy - 2 * y0 * dx + 2 * (y0 - dy/dx * x0) * dx
= 2 * x_draw(i-1) * dy - 2 * i * step_y * dx + step_x * dy - 2 * y0 * dx + 2 * y0 * dx - 2 * dy * x0
= 2 * x_draw(i-1) * dy - 2 * i * step_y * dx + step_x * dy - 2 * dy * x0
= 2 * x_draw(i-1) * dy - 2 * i * step_y * dx + C

C = step_x * dy - 2 * dy * x0
p(0) = 2 * x0 * dy + C
     = step_x * dy

p(i+1) = p(i) + 2 * [x_draw(i) - x_draw(i-1)] * dy - 2 * dx * step_y

以上公式是根据y的递增推导计算的，满足1< |k|的情况，且公式p(i)中乘了包含dx,dy，其正负未知，需分情况分别处理：


### References

[wikipedia - DDA algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
[wikipedia - Bresnhams line algorithm](https://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
[tutorialspoint - Computer Graphics Tutorial](https://www.tutorialspoint.com/computer_graphics/index.htm)
[The Bresnham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)
