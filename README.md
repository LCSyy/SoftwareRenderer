# Software Renderer

## 直线扫描转换算法

### DDA算法（数字微分法）
基本原理：根据直线斜截式方程 `y = kx + b` 推导。

已知点 P<sub>i</sub>(x<sub>i</sub>,y<sub>i</sub>)，在栅格中，下一个点 P<sub>i+1</sub> 的 x 值，即为：

x<sub>i+1</sub> = x<sub>i</sub> + stepX

其中 stepX 即为1.则 P<sub>i+1</sub> 的 y 值即为：

y<sub>i+1</sub> = y<sub>i</sub> + stepY

其中 stepY = k * stepX = k.

综上，即可得DDA算法的公式：

给定直线上两点，可得：
(1) k = (y1 - y0) / (x1 - x0)
(2) x<sub>i+1</sub> = x<sub>i</sub> + 1
(3) y<sub>i+1</sub> = y<sub>i</sub> + k

伪代码实现：
```
draw_line_dda(p0,p1) {
    k = 0;
    dx = p1.x - p0.x;
    dy = p1.y - p0.y;

    // 避免除0
    if(dx)
        k = dy / dx;
    
    x = p0.x;
    y = p0.y;
    
    if(abs(dy) <= abs(dx)) {
        for(i = 0; i < abs(dx); ++i) {
            set_pixel(x,int(y+0.5),color);
            if(dx>0)
                x += 1;
            else if(dx<0)
                x -= 1;
            y += k;
        }
    } else {
        for(i = 0; i < abs(dy); ++i) {
            set_pixel(int(x+0.5),y,color);
            x += k;
            if(dy > 0)
                y += 1;
            else if(dy < 0)
                y -= 1;
        }
    }
}
```

**总结**

DDA算法将直线的方程中存在的乘法运算转换为了加法运算，提高了运算效率。
其存在的问题是：
- 存在浮点型向整形的转换；
- 如果斜率的绝对值大于1，描绘直线的点会变稀疏，不连续；
