# Untitled - By: user - 週日 六月 6 2021

import pyb, sensor, image, time, math
#设置阈值，（0，100）检测黑色线
THRESHOLD = (0, 80) # Grayscale threshold for dark things...

#设置是否使用img.binary()函数进行图像分割
BINARY_VISIBLE = True # 首先执行二进制操作，以便您可以看到正在运行的线性回归...虽然可能会降低FPS。
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA) # QVGA ==> 320 * 240
sensor.skip_frames(time = 2000)
clock = time.clock()
ROI=(20,0,280,70)

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)
count = 0
while(True):
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD]) if BINARY_VISIBLE else sensor.snapshot()
    # Returns a line object similar to line objects returned by find_lines() and
    # find_line_segments(). You have x1(), y1(), x2(), y2(), length(),
    # theta() (rotation in degrees), rho(), and magnitude().
    #
    # magnitude() represents how well the linear regression worked. It goes from
    # (0, INF] where 0 is returned for a circle. The more linear the
    # scene is the higher the magnitude.

    # 函数返回回归后的线段对象line，有x1(), y1(), x2(), y2(), length(), theta(), rho(), magnitude()参数。
    # x1 y1 x2 y2分别代表线段的两个顶点坐标，length是线段长度，theta是线段的角度。
    # magnitude表示线性回归的效果，它是（0，+∞）范围内的一个数字，其中0代表一个圆。如果场景线性回归的越好，这个值越大。
    line = img.get_regression([(255,255) if BINARY_VISIBLE else THRESHOLD], roi=ROI)
    # 255和255是因為我只有一種一種元阻，每種都有最小灰度值和最大灰度值
    img.draw_rectangle(ROI)

    if (line):
        img.draw_line(line.line(), color = 127)
#        print(line.line())
#        print((line.line()[0] + line.line()[3]) / 2)
        #print("rho = ", line.rho(), "theta = ", line.theta())
#        print("與中間差", abs(line.rho())-img.width()/2)
        print(line.magnitude())
        #print(((line.line()[0] + line.line()[2]) / 2) - (img.width() / 2))
        #print((line.line()[0] + line.line()[2]) / 2)
       # print(img.width() / 2)

        if (line.magnitude() > 5):
            if (line.line()[0] < img.width() * 4 / 10.0):
                uart.write(('3').encode())
                print("uart", 3)
            elif (line.line()[0] > img.width() * 6 / 10.0):
                uart.write(('4').encode())
                print("uart", 4)
        else:
            count = count + 1
            if (count > 1):
                uart.write(('5').encode())
                print("uart", 5)
                count = 0
#    else:
#        count = count + 1
#        if (count > 2):
#            uart.write(('5').encode())
#            count = 0

# uart.write(("Tx: %f, Ty %f, Tz %f, Rx %f, Ry %f, Rz %f" % print_args).encode())
    time.sleep_ms(1000)
    #print("FPS %f, mag = %s" % (clock.fps(), str(line.magnitude()) if (line) else "N/A"))
