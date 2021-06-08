# hw4_3
import pyb, sensor, image, time, math

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) # we run out of memory if the resolution is much bigger...
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
clock = time.clock()

f_x = (2.8 / 3.984) * 160 # find_apriltags defaults to this if not set
f_y = (2.8 / 2.952) * 120 # find_apriltags defaults to this if not set
c_x = 160 * 0.5 # find_apriltags defaults to this if not set (the image.w * 0.5)
c_y = 120 * 0.5 # find_apriltags defaults to this if not set (the image.h * 0.5)
kx = 4 / 2.2
kz = 20 / -8.4
def degrees(radians):
    return (180 * radians) / math.pi

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)
while(True):
    clock.tick()
    img = sensor.snapshot()
    i = 0 # used to chech if there is tag in the screen
    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y): # defaults to TAG36H11
        i = 1 # there is tag
        img.draw_rectangle(tag.rect(), color = (255, 0, 0))
        img.draw_cross(tag.cx(), tag.cy(), color = (0, 255, 0))
        # The conversion is nearly 6.2cm to 1 -> translation
        print_args = (tag.x_translation(), tag.y_translation(), tag.z_translation(), \
             degrees(tag.x_rotation()), degrees(tag.y_rotation()), degrees(tag.z_rotation()))
        print("Tx: %f, Ty %f, Tz %f, Rx %f, Ry %f, Rz %f" % print_args)
        dx = kx * tag.x_translation()
        dz = kz * tag.z_translation()
        total_dis = (dx**2 + dz**2)**0.5
    if (i == 1): # there is tag in the screen
        if (abs(tag.x_translation()) > 1.5):
            if (tag.x_translation() > 0):
                uart.write(("1").encode())
                print(1)
            else:
                uart.write(("3").encode())
                print(3)
        elif (abs(tag.x_translation()) > 0.8):
            if (tag.x_translation() > 0):
                uart.write(("2").encode())
                print(2)
            else:
                uart.write(("4").encode())
                print(4)
        elif (total_dis > 25):
            uart.write(("5").encode())
            print(5)
            time.sleep(0.3)
            total_dis = total_dis - 20 + 2
            print("total_dis = ", total_dis)
            uart.write(("%5.4f\n"%(total_dis)).encode())
            time.sleep(5)
        elif ((degrees(tag.y_rotation()) > 5 and degrees(tag.y_rotation()) < 90) or (degrees(tag.y_rotation()) < 355 and degrees(tag.y_rotation()) > 270)):
            uart.write(("6").encode())
            print(6)
            time.sleep(0.3)

            uart.write(("%5.4f\n%5.4f\n"%(total_dis, degrees(tag.y_rotation()))).encode())
            print("total_dis = ", total_dis)
            print("Ry = ", degrees(tag.y_rotation()))
            time.sleep(10)
        elif (total_dis < 13):
            uart.write(("7").encode()) # go backwrad
            time.sleep(2)
            print("NO tag")
            Ack1 = uart.read(3)
            print("Ack1 = ", Ack1)
            if (Ack1 == b'1\n'): print("success")
        else:
            uart.write(("8").encode())
            print(8)
            time.sleep(0.3)
            uart.write(("%5.4f\n%5.4f\n"%(total_dis, degrees(tag.y_rotation()))).encode())
            print("total_dis = ", total_dis)
            print("Ry = ", degrees(tag.y_rotation()))
            time.sleep(10)


        time.sleep(2)
        Ack1 = uart.read(3)
        print("Ack1 = ", Ack1)
        if (Ack1 == b'1\n'): print("success")
    else:
        uart.write(("7").encode()) # go backwrad
        time.sleep(2)
        print("NO tag")
        Ack1 = uart.read(3)
        print("Ack1 = ", Ack1)
        if (Ack1 == b'1\n'): print("success")


      # Translation units are unknown. Rotation units are in degrees.
      #uart.write(("Tx: %f, Ty %f, Tz %f, Rx %f, Ry %f, Rz %f" % print_args).encode())
      #uart.write("a".encode())
      #time.sleep(0.3)
      #Ack1 = uart.read(3)
      #print("Ack1 = ", Ack1)
"""   if (Ack1 == b'1\n'):
        uart.write(("%5.4f\n"%tag.x_translation()).encode())
        #print("%5.4f\n"%tag.x_translation())
        time.sleep(0.6)
        Ack2 = uart.read(3)
        print("Ack2 = ", Ack2)"""
   #uart.write(("FPS %f\r\n" % clock.fps()).encode())
   #print("FPS %f\r\n" % clock.fps())
