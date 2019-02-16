
#include <wiringPi.h>
#include <string.h>
#include <PCD8544.h>

#include "menubar.h"

#define BTN1 7
#define BTN2 0
#define BTN3 21
#define BTN4 22
#define BL 30

MenuBar menuBar("Main Menu");

bool light = true;
MenuItem setting3("Light: ON");

void initPin()
{
    pinMode (BL, OUTPUT);
    digitalWrite(BL, HIGH);

    pinMode (BTN1, INPUT);
    pullUpDnControl (BTN1, PUD_UP) ;

    pinMode (BTN2, INPUT);
    pullUpDnControl (BTN2, PUD_UP) ;

    pinMode (BTN3, INPUT);
    pullUpDnControl (BTN3, PUD_UP) ;

    pinMode (BTN4, INPUT);
    pullUpDnControl (BTN4, PUD_UP) ;
}

void helloWorld()
{
    LCDclear();
    LCDdrawstring_P(0, 0, "Hello World");
    LCDdisplay();
}

void changeLight()
{
    light = !light;
    if (light) setting3.setTitle("Light: On");
    else setting3.setTitle("Light: OFF");
    menuBar.update();
    digitalWrite(BL, light);
}

void showLogo()
{
    LCDclear();
    LCDshowLogo();
    LCDdisplay();
    delay(2000);
    menuBar.update();
}

int main()
{
    wiringPiSetup();
    initPin();

    LCDInit();

    MenuItem prog("Program");
    MenuItem thresh("Threshold");
    MenuItem sys("System");
    MenuItem option("Option");
    MenuItem file("File Explorer");
    MenuItem cpu("CPU Show");

    MenuItem prog1("Detect Ball");
    MenuItem prog2("Hello World");
    MenuItem prog3("Calculator");
    MenuItem prog4("Show Logo");

    prog.addItem(&prog1);
    prog.addItem(&prog2);
    prog.addItem(&prog3);
    prog.addItem(&prog4);

    MenuItem setting1("LCD Contrast");
    MenuItem setting2("LCD Bias");

    sys.addItem(&setting1);
    sys.addItem(&setting2);
    sys.addItem(&setting3);

    menuBar.addItem(&prog);
    menuBar.addItem(&thresh);
    menuBar.addItem(&sys);
    menuBar.addItem(&option);
    menuBar.addItem(&file);
    menuBar.addItem(&cpu);

    prog2.setAction(helloWorld);
    prog4.setAction(showLogo);
    setting3.setAction(changeLight);

    while (true)
    {
        if(digitalRead (BTN1) == LOW)
        {
            menuBar.back();
            delay(250);
        }
        if(digitalRead (BTN2) == LOW)
        {
            menuBar.up();
            delay(250);
        }
        if(digitalRead (BTN3) == LOW)
        {
            menuBar.down();
            delay(250);
        }
        if(digitalRead (BTN4) == LOW)
        {
            menuBar.enter();
            delay(250);
        }
    }

    return 0;
}
