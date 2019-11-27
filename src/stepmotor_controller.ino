#include <ros.h>
#include <string.h>
#include <std_msgs/String.h>
// a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r
// U  U' U2 R  R' R2 F  F' F2 D  D' D2 L  L' L2 B  B' B2 

// D  F  L  B  R  U
// 22,25,28,31,34,37  DIR
// 23,26,29,32,35,38  STEP
// 24,27,30,33,36,39  EN


String solve = "";  //ros接数据
int stop_ = 0;

void solveCallBack(const std_msgs::String &solve_msg)
{
  solve = solve_msg.data;
}

ros::NodeHandle cubot_motor;
ros::Subscriber<std_msgs::String> solve_message_sub("chatter", solveCallBack);

void tranform()
{
    for (int i = 0; i <= solve.length(); i++)
    {
        switch (solve[i])
        {
        case 'a':
            motor('U', 0);
            break;
        case 'b':
            motor('U', 1);
            break;
        case 'c':
            motor('U', 2);
            break;
        case 'd':
            motor('R', 0);
            break;
        case 'e':
            motor('R', 1);
            break;
        case 'f':
            motor('R', 2);
            break;
        case 'g':
            motor('F', 0);
            break;
        case 'h':
            motor('F', 1);
            break;
        case 'i':
            motor('F', 2);
            break;
        case 'j':
            motor('D', 0);
            break;
        case 'k':
            motor('D', 1);
            break;
        case 'l':
            motor('D', 2);
            break;
        case 'm':
            motor('L', 0);
            break;
        case 'n':
            motor('L', 1);
            break;
        case 'o':
            motor('L', 2);
            break;
        case 'p':
            motor('B', 0);
            break;
        case 'q':
            motor('B', 1);
            break;
        case 'r':
            motor('B', 2);
            break;
        }
        delay(1000);
    }
}
// a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r
// U  U' U2 R  R' R2 F  F' F2 D  D' D2 L  L' L2 B  B' B2 

// D  F  L  B  R  U
// 22,25,28,31,34,37  DIR
// 23,26,29,32,35,38  STEP

void motor(char side, int type)
{

    int step;
    int dir;
    switch (side)
    {
    case 'D':
        step = 23;
        dir = step + 1;
        break;
    case 'F':
        step = 26;
        dir = step + 1;
        break;
    case 'L':
        step = 29;
        dir = step + 1;
        break;
    case 'B':
        step = 32;
        dir = step + 1;
        break;
    case 'R':
        step = 35;
        dir = step + 1;
        break;
    case 'U':
        step = 38;
        dir = step + 1;
        break;
    }
    switch (type)
    {
    case 0:
        digitalWrite(dir, HIGH);
        for (int i = 0; i < 50; i++)
        {
            digitalWrite(step, HIGH);
            delayMicroseconds(2000);
            digitalWrite(step, LOW);
            delayMicroseconds(2000);
        }
        break;
    case 1:
        digitalWrite(dir, LOW);
        for (int i = 0; i < 50; i++)
        {
            digitalWrite(step, HIGH);
            delayMicroseconds(2000);
            digitalWrite(step, LOW);
            delayMicroseconds(2000);
        }
        break;
    case 2:
        for (int i = 0; i < 100; i++)
        {
            digitalWrite(step, HIGH);
            delayMicroseconds(2000);
            digitalWrite(step, LOW);
            delayMicroseconds(2000);
        }
        break;
    }
}


void set_motor(int en_pin)
{
    en_pin;
    int step_pin = en_pin + 1;
    int dir_pin = en_pin + 2;
    pinMode(en_pin, OUTPUT);   // Enable: EN可以使用单片机端口控制，也可以直接连接GND使能
    pinMode(step_pin, OUTPUT); // steps:脉冲个数
    pinMode(dir_pin, OUTPUT);  // dir:为方向控制
    digitalWrite(en_pin, LOW); // Set Enable low
}

void setup()
{
    cubot_motor.initNode();
    cubot_motor.subscribe(solve_message_sub);
    Serial.begin(9600);
    for (int pin = 22; pin <= 37; pin += 3)
    {
        set_motor(pin);
    }
}

void loop()
{
    if (solve!=""&&stop_ == 0)
    {
        tranform();
        Serial.print("23333");
        stop_ = 1;
    }
}
