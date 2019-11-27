#include <String.h>

int dir[6] = {0};
int step[6] = {0};
int enable[6] = {0};
String solve = ""; //ros接数据
bool solve_dir = 0;//0顺1逆
char solve_side = "";
char solve_degree = "";

String all_ctrl = "UDLRFB";

void tranform()
{
    for(int i=0;i<=solve.length();i++)
    {
        if(solve[i]==" ")
        {
            runstep();
            solve_dir = 0;
        }
        if(strchr(all_ctrl.c_str(),solve[i])!=0)
        {
            solve_side = all_ctrl[strchr(all_ctrl.c_str(),solve[i])];
        }
        if(solve[i]=="\'")
        {
            solve_dir = 1;
        }
    }
    runstep(); //完成最后一个指令
    solve = "";
}

void runstep()
{
    //there is nothing :-)
    //waiting for MoYuhuaiyu to finish it 
}

void set_motor (int en_pin)
{
    en_pin;
    int step_pin = en_pin+1;
    int dir_pin = en_pin+2;
    pinMode(en_pin,OUTPUT); // Enable: EN可以使用单片机端口控制，也可以直接连接GND使能
    pinMode(step_pin,OUTPUT); // steps:脉冲个数
    pinMode(dir_pin,OUTPUT); // dir:为方向控制
    digitalWrite(en_pin,LOW); // Set Enable low
}

void setup()
{
    for(int pin=22;pin<=37;pin+=3)
    {
        set_motor(pin);
    }
}

void loop()
{
    if(solve != 0)
    {
        tranform();
    }
}
