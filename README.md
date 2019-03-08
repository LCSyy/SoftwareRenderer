[TOC]

# Software Renderer

## 光栅图形学

### 直线扫描转换算法

#### DDA算法（数字微分法）
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

#### Bresenham算法

主要参考[wikipedia - Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)

Bresenham算法的基本思想是：直线上的点绘制到栅格中时，对于x或者y值而言都有两个可选的像素位置。通过比较可选像素离理论点的距离来决定绘制到那个像素。

```
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
```
以上公式是根据x的递增推导计算的，满足 0 < |k| < 1的情况，且公式p(i)中乘了包含dx,dy，其正负未知，需分情况分别处理。

```
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
```
以上公式是根据y的递增推导计算的，满足1< |k|的情况，且公式p(i)中乘了包含dx,dy，其正负未知，需分情况分别处理。


#### References

[wikipedia - DDA algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
[wikipedia - Bresnhams line algorithm](https://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
[tutorialspoint - Computer Graphics Tutorial](https://www.tutorialspoint.com/computer_graphics/index.htm)
[The Bresnham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)

## 线性代数基础
### 向量
#### 线性运算
v1 + v2
v1 * scalar

#### 数量积
v1 . v2 = x1*x2 + y1*y2

#### 向量积

### 矩阵
参考[矩阵的运算及其运算规律](http://www2.edu-edu.com.cn/lesson_crs78/self/j_0022/soft/ch0605.html)
#### 线性运算
##### 加法
同型矩阵才能进行加法运算。方式是对应元素进行加减。

##### 数乘
标量在矩阵之前。运算方式是矩阵每个元素乘以该标量。

#### 乘法
两个矩阵仅有在第一个矩阵的列数同第二个矩阵的行数相等时才能进行矩阵乘法运算。运算方式是对应行列的各元素对应相乘然后相加得到新矩阵的对应元素。

### 点、向量与矩阵
点，在坐标中表示一个位置，  实际上除此之外它不具备其他任何附加的属性，因此它除了包含坐标分量意外，没有定义其他操作。而何时要将点的值用于何目的，完全取决于实际使用情景。甚至可以用它来存放完全和位置没有关系的数据。

向量，则遵循其数学定义，是既有大小又有方向的量。可使用有向线段来表示。向量是元素只有一行或者一列的矩阵，它们分别称为行矩阵和列矩阵。其具有大小和方向的属性，还定义了向量的数乘、加减、数量积、向量积等操作。

矩阵，...

### 齐次坐标系

## 二维变换

二维变换主要包括平移、旋转和缩放，它们一般被称为几何变换或者建模变换。

首先考虑在二维坐标中，点P(x,y)的几何变换。

### 平移

假设点P平移后为Pt(xt,yt)。如果将坐标位置使用向量表示，其向量的关系为Pt = P + Pd，其中Pd(xd,yd)就是点P的平移量，称之为平移向量或者位移向量。由此可得：

```
[xt, yt] = [x + xd, y + yd]
表示为矩阵形式即为：
[xt yt] = [x y] + [xd yd]
```

### 旋转
假设点P旋转后为Pr(xr,yr)，旋转前角度为a，旋转后为b，旋转的角度为c，即b = a + c。其推导过程如下：
```
[xr, yr] = [r * cos(b), r * sin(b)]
= [r * cos(a + c), r * sin(a + c)]
根据三角恒等式：
cos(a+c) = cos(a)*cos(c)-sin(a)*sin(c)
sin(a+c) = sin(a)*cso(c)+cos(a)*sin(c)
可得：
[r * cos(a + c), r * sin(a + c)]
= [
	r * cos(a) * cos(c) - r * sin(a) * sin(c),
	r * sin(a) * cos(c) + r * cos(a) * sin(c)
  ]
= [x * cos(c) - y * sin(c), y * cos(c) + x * sin(c)]
上式可转换为两矩阵相乘：
[x y] * [cos(c) sin(c)
         -sin(c) cos(c)]
因此可得二维变换中的旋转矩阵为：
[cos(c) sin(c)]
[-sin(c) cos(c)]
```
### 缩放
假设点P缩放后为Ps(xs,ys)，缩放系数为s，缩放矩阵的推导过程如下：
```
[xs,ys] = [x,y] * s
= [x * s, y * s]
= [x * s + y * 0, x * 0 + y * s]
其矩阵乘法形式为：
[x y] * [s 0]
        [0 s]
由此可得二维变换的缩放矩阵为：
[sx 0]
[0 sy]
```
通过上面推导的三个基本几何变换公式，我们可以在二维平面上进行多种顺序和次数的变换。很明显地，三种变换中，进行旋转和缩放时，可以不考虑变换顺序，而有平移变换时则需要考虑。而这种顺序的确定，则取决于我们想要的变换效果。
例如，在这里，我们考虑的是在组合坐标系统中，一个物体存在于其父空间坐标系中，而该物体自己又有本地坐标系。三种变换中，平移是相对父控件坐标系进行的，而旋转和缩放时相对本地坐标系而言的。

### 组合变换
```
[x y] * [ cos(c)*sx  sin(c)*sy ] = [x*cos(c)*sx-y*sin(c)*sx]
        [ -sin(c)*sx cos(c)*sy ]   [x*sin(c)*sy+y*cos(c)*sy]

[x*cos(c)*sx-y*sin(c)*sx x*sin(c)*sy+y*cos(c)*sy] + [dx + dy]
= [x*cos(c)*sx-y*sin(c)*sx+dx x*sin(c)*sy+y*cos(c)*sy + dy]
```

```
[ cos(c)*sx  sin(c)*sy 0]
[ -sin(c)*sx cos(c)*sy 0]
[ dx          dy       1]
```

以上是三种变换的组合变换矩阵，对于一个固定变换的矩阵，就可以使用一个矩阵乘法将最终的变换效果表达出来。但是对于需要每一帧同时进行旋转和缩放的变换来说，将三种变换分开来表示，分别控制是更好的选择。而且在需要获取某一变换的值的时候，更容易获取。

### 其他变换

## 三维变换

### 平移
三维空间中一点P(x,y,z)平移到Pt(xt,yt,zt)。
```
xt = x + dx;
yt = y + dy;
zt = z + dz;
```
转换为矩阵加法：
```
[xt yt zt] = [x y z] + [dx dy dz]
```

### 缩放
P(x,y,z)的各分量缩放系数分别为sx,sy,sz，缩放后得到Ps(xs,ys,zs)
```
xs = x * sx;
ys = y * sy;
zs = z * sz;
```
可使用矩阵乘法表示：
```
[xs ys zs] = [x y z] * [sx 0   0]
                       [0  sy  0]
                       [0  0  sy]
```

### 旋转
一个向量在三维空间中的旋转，可以看做是三个分量各自独立旋转的合作效果。

因此假设，P(x,y,z) 其与各平面的夹角分别为a,b,c，各分量分别旋转da,db,dc度，得到Pr(xr,yr,zr)。我们先推导每一个平面的旋转：

**xoy平面**
在该平面是绕z轴进行旋转。