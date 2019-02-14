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

### Bresnham算法



### References

[wikipedia - DDA algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
[wikipedia - Bresnhams line algorithm](https://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
[tutorialspoint - Computer Graphics Tutorial](https://www.tutorialspoint.com/computer_graphics/index.htm)
[The Bresnham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)
