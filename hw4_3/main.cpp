#include "mbed.h"
#include "uLCD_4DGL.h"

using namespace std::chrono;
#define CENTER_BASE 1500

PwmOut servo_r(D6); // right
PwmOut servo_l(D5); // left

// BufferedSerial pc(USBTX, USBRX);
BufferedSerial uart(D1,D0); //tx,rx
DigitalInOut ping(D12);
uLCD_4DGL uLCD(D10, D9, D2);

void servo_control(int r_speed, int l_speed);

Timer t;

int main() {
   int i; // looping index
   float val;
   char recv[1];
   char trans[1];
   char str_num[100];
   float num1 = 0;
   float num2 = 0;
   int move_us;
   int move_us2;
   float ang_turn;
   float dis_move;

   servo_r.period_ms(20); 
   servo_l.period_ms(20); 
   servo_control(0, 0);
   move_us = 19.5 * 1000000 / 6;
//   pc.set_baud(9600);
   uart.set_baud(9600);
   if (uart.readable()) {
      uart.read(recv, sizeof(recv));
   }
   if (uart.readable()) {
      uart.read(recv, sizeof(recv));
   }

   while(1) {
      if (uart.readable()) {
         uart.read(recv, sizeof(recv));
         uLCD.text_width(1); //4X size text
         uLCD.text_height(2);
         uLCD.color(RED);
         uLCD.cls();
         uLCD.locate(0,0);
         uLCD.printf("recv[0] = %c\n", recv[0]);
         if (recv[0] == '1') {
            servo_control(-33.4775, 0); // 6cm
            wait_us(290000); // turn left big
            servo_control(0, 0); // 6cm
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         else if (recv[0] == '2') {
            servo_control(-33.4775, 0); // 6cm
            wait_us(150000); // turn left big
            servo_control(0, 0); // 6cm
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         else if (recv[0] == '3') {
            servo_control(0, 27.9129); // 6cm
            wait_us(290000); // turn left big
            servo_control(0, 0); // 6cm
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         else if (recv[0] == '4') {
            servo_control(0, 27.9129); // 6cm
            wait_us(150000); // turn left big
            servo_control(0, 0); // 6cm
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         else if (recv[0] == '5') {
            i = 0;
            while (1) {
               if(uart.readable()){
                  uart.read(recv, sizeof(recv));
                  if (recv[0] == '\n') {
                     str_num[i] = '\0';
                     uLCD.locate(0,4);
                     uLCD.printf("I am break");
                     break;
                  }
                  str_num[i] = recv[0];
                  i++;
               }
            }
            num1 = atof(str_num);
            uLCD.text_width(1); //4X size text
            uLCD.text_height(2);
            uLCD.color(RED);
            uLCD.locate(0,6);
            uLCD.printf(str_num);
            uLCD.locate(0,2);
            if (num1 != 0) uLCD.printf("Tx = %8.6lf\r\n", num1);
            move_us = num1 / 6.0 * 1000000;
            servo_control(-33.4775, 27.9129); // 6cm
            wait_us(move_us);
            servo_control(0, 0);
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         else if (recv[0] == '6') {
            i = 0;
            while (1) {
               if(uart.readable()){
                  uart.read(recv, sizeof(recv));
                  if (recv[0] == '\n') {
                     str_num[i] = '\0';
                     uLCD.locate(0,4);
                     uLCD.printf("I am break");
                     break;
                  }
                  str_num[i] = recv[0];
                  i++;
               }
            }
            num1 = atof(str_num);

            i = 0;
            while (1) {
               if(uart.readable()){
                  uart.read(recv, sizeof(recv));
                  if (recv[0] == '\n') {
                     str_num[i] = '\0';
                     uLCD.locate(0,4);
                     uLCD.printf("I am break");
                     break;
                  }
                  str_num[i] = recv[0];
                  i++;
               }
            }
            num2 = atof(str_num);

            uLCD.text_width(1); //4X size text
            uLCD.text_height(2);
            uLCD.color(RED);
            uLCD.cls();
            uLCD.locate(0,4);
            uLCD.printf("num1 = %f", num1);
            uLCD.locate(0,6);
            uLCD.printf("num2 = %f", num2);

            // num1 is total_dis
            // num2 is degree Ry
            if (num2 < 180) {
               // first turn right
               ang_turn = 90 - num2;
               move_us = 3000000.0 * ang_turn / 90;

               // dis_move = total_dis*sin(ang) - le_to_c - ri_to_c*cos(ang)
               num2 = num2 * 3.1415926 / 180;
               dis_move = num1 * sin(num2) - 6.5 - 4.3 * cos(num2);
               if (dis_move > 0) {
                  move_us2 = dis_move * 1000000 / 6;
               }
               else {
                  move_us2 = -dis_move * 1000000 / 6;
               }
               
               servo_control(0, 27.9129); // 6cm
               wait_us(move_us); // turn right 90 - num2 degree
               servo_control(0, 0);
               wait_us(500000);

               if (dis_move > 0) {
                  servo_control(-33.4775, 27.9129);
                  wait_us(move_us2); // move forward
               }
               else {
                  servo_control(28.7020, -34); // back 6cm
                  wait_us(move_us2); // move backward
               }
               servo_control(-33.4775, 0); // 6cm
               wait_us(2900000); // turn left 90 degree
               servo_control(0, 0);
               trans[0] = '1';
               uart.write(trans, 1);   // return the Ack means ok
               trans[0] = '\n';
               uart.write(trans, 1);
            }
            else { // num2 > 180
               num2 = (num2 - 360) * (-1);
               // first turn left
               ang_turn = 90 - num2;
               move_us = 2900000.0 * ang_turn / 90;

               num2 = num2 * 3.1415926 / 180;

               dis_move = num1 * sin(num2) - 4.3 - 6.5 * cos(num2);
               if (dis_move > 0) {
                  move_us2 = dis_move * 1000000 / 6;
               }
               else {
                  move_us2 = -dis_move * 1000000 / 6;
               }

               servo_control(-33.4775, 0); // 6cm
               wait_us(move_us); // turn left 90 - num2 degree
               servo_control(0, 0);
               wait_us(500000);

               if (dis_move > 0) {
                  servo_control(-33.4775, 27.9129);
                  wait_us(move_us2); // move forward
               }
               else {
                  servo_control(28.7020, -34); // back 6cm
                  wait_us(move_us2); // move backward
               }
               servo_control(0, 27.9129); // 6cm
               wait_us(3000000); // turn right 90 degree
               servo_control(0, 0);
               trans[0] = '1';
               uart.write(trans, 1);   // return the Ack means ok
               trans[0] = '\n';
               uart.write(trans, 1);
            }
         }
         else if (recv[0] == '7') {
            servo_control(28.7020, -34); // back 6cm
            wait_us(1000000); // move backward
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         else if (recv[0] == '8') { // success
            i = 0;
            while (1) {
               if(uart.readable()){
                  uart.read(recv, sizeof(recv));
                  if (recv[0] == '\n') {
                     str_num[i] = '\0';
                     uLCD.locate(0,4);
                     uLCD.printf("I am break");
                     break;
                  }
                  str_num[i] = recv[0];
                  i++;
               }
            }
            num1 = atof(str_num);

            i = 0;
            while (1) {
               if(uart.readable()){
                  uart.read(recv, sizeof(recv));
                  if (recv[0] == '\n') {
                     str_num[i] = '\0';
                     uLCD.locate(0,4);
                     uLCD.printf("I am break");
                     break;
                  }
                  str_num[i] = recv[0];
                  i++;
               }
            }
            num2 = atof(str_num);
            
            ping.output();
            ping = 0; wait_us(200);
            ping = 1; wait_us(5);
            ping = 0; wait_us(5);

            ping.input();
            while(ping.read() == 0);
            t.start();
            while(ping.read() == 1); // count how long the ping == 1
            val = t.read();
            uLCD.cls();
            uLCD.text_width(1); //4X size text
            uLCD.text_height(2);
            uLCD.color(GREEN);
            uLCD.locate(0,2);
            uLCD.printf("Ping = %8.6lf\r\n", val*17700.4f);
            uLCD.locate(0,4);
            uLCD.printf("ang = %8.6lf deg\r\n", num2);
            uLCD.locate(0,6);
            uLCD.color(GREEN);
            uLCD.printf("SUCCESS");
            t.stop();
            t.reset();
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack means ok
            trans[0] = '\n';
            uart.write(trans, 1);
         }
         servo_control(0, 0); // 6cm
         
/*         if (recv[0] == 'a') {
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack
            trans[0] = '\n';
            uart.write(trans, 1);
            i = 0;
            while (1) {
               if(uart.readable()){
                  uart.read(recv, sizeof(recv));
                  if (recv[0] == '\n') {
                     str_num1[i] = '\0';
                     uLCD.locate(0,4);
                     uLCD.printf("I am break");
                     break;
                  }
                  str_num1[i] = recv[0];
                  i++;
               }
            }
         }
         num1 = atof(str_num1);
         uLCD.text_width(1); //4X size text
         uLCD.text_height(2);
         uLCD.color(RED);
         uLCD.locate(0,6);
         uLCD.printf(str_num1);
         if (num1 != 0) {
            trans[0] = '1';
            uart.write(trans, 1);   // return the Ack
            trans[0] = '\n';
            uart.write(trans, 1);
         }*/

      }
   }
}

void servo_control(int r_speed, int l_speed) {
   if (r_speed > 200)       r_speed = 200;
   else if (r_speed < -200) r_speed = -200;
   if (l_speed > 200)       l_speed = 200;
   else if (l_speed < -200) l_speed = -200;

   servo_r = (CENTER_BASE + r_speed)/20000.0f;
   servo_l = (CENTER_BASE + l_speed)/20000.0f;
}
