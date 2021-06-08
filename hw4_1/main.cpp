#include "mbed.h"
#include "mbed_rpc.h"

using namespace std::chrono;
#define CENTER_BASE 1500

PwmOut servo_r(D6);
PwmOut servo_l(D5);
BufferedSerial xbee(D1, D0);

void servo_control(int r_speed, int l_speed);
void parking(Arguments *in, Reply *out);
RPCFunction rpcparking(&parking, "parking");
double d1, d2, direction;
int move_us;

int main() {
   
   servo_r.period_ms(20); 
   servo_l.period_ms(20); 
   servo_control(0, 0);

   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
      RPC::call(buf, outbuf);
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

void parking(Arguments *in, Reply *out)
{
    
    // In this scenario, when using RPC delimit the two arguments with a space.
    d1 = in->getArg<double>();
    d2 = in->getArg<double>();
    direction = in->getArg<double>();

    if (direction == 1) {
        move_us = (d2 + 2) * 1000000 / 6;
        servo_control(28.7020, -34); // back 6cm
        wait_us(move_us);
        servo_control(0, -35); // back turn left 6cm
        ThisThread::sleep_for(2900ms);
        move_us = (d1 + 4) * 1000000 / 6;
        servo_control(28.7020, -34); // back 6cm
        wait_us(move_us);
    }
    else if (direction == 2) {
        move_us = (d1 + 4) * 1000000 / 6;
        servo_control(28.7020, -34); // back 6cm
        wait_us(move_us);
    }
    else if (direction == 3) {
        move_us = (d2 + 2) * 1000000 / 6;
        servo_control(28.7020, -34); // back 6cm
        wait_us(move_us);
        servo_control(28.7020, 0); // back 6cm
        ThisThread::sleep_for(2850ms);
        move_us = (d1 + 4) * 1000000 / 6;
        servo_control(28.7020, -34); // back 6cm
        wait_us(move_us);
    }
    servo_control(0, 0);

    return;
}