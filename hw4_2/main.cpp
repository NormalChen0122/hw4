#include"mbed.h"

// BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

#define CENTER_BASE 1500

PwmOut servo_r(D6);
PwmOut servo_l(D5);

void servo_control(int r_speed, int l_speed) {
   if (r_speed > 200)       r_speed = 200;
   else if (r_speed < -200) r_speed = -200;
   if (l_speed > 200)       l_speed = 200;
   else if (l_speed < -200) l_speed = -200;

   servo_r = (CENTER_BASE + r_speed)/20000.0f;
   servo_l = (CENTER_BASE + l_speed)/20000.0f;
}

int main(){
   servo_r.period_ms(20); 
   servo_l.period_ms(20);
   servo_control(0, 0);
   uart.set_baud(9600);
   ThisThread::sleep_for(2s);
   servo_control(-33.4775, 27.9129); // 6cm
   servo_control(0, 0);
   ThisThread::sleep_for(2s);
   servo_control(-33.4775, 27.9129); // 6cm
   while(1){
      if(uart.readable()){
         char recv[1];
         uart.read(recv, sizeof(recv));
         if (recv[0] == '1') { // Pan left, turn left and trun right
            servo_control(-42.8398, 27.9129); // 8cm right, 6 cm left
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 27.9129); // 6cm
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 37.1777); // 6cm right, 8 cm left
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 27.9129); // 6cm
         }
         else if (recv[0] == '2') { // Pan right, turn right and then trun left
            servo_control(-32.2775, 37.1777); // 6cm right, 8 cm left
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 27.9129); // 6cm
            ThisThread::sleep_for(1000ms);
            servo_control(-42.8398, 27.9129); // 8cm right, 6 cm left
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 27.9129); // 6cm
         }
         else if (recv[0] == '3') { // turn right
            servo_control(-32.2775, 37.1777); // 6cm right, 8 cm left
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 27.9129); // 6cm
         }
         else if (recv[0] == '4') { // turn left
            servo_control(-42.8398, 27.9129); // 8cm right, 6 cm left
            ThisThread::sleep_for(1000ms);
            servo_control(-32.2775, 27.9129); // 6cm
         }
         else if (recv[0] == '5') { // stop
            servo_control(0, 0);
            break;
         }
      }
   }
}
