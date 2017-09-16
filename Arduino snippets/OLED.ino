// Arduino Shields OLED Univision F01Shield demo code
// Saved by Simulator for Arduino V0.94
// Saved by Simulator for Arduino V0.92
// Saved by Simulator for Arduino V0.92
// Saved by Simulator for Arduino V0.92
// www.arduino.com.au
// v1.00 10-Oct-2011 - first release
// tested on Arduino Uno

#include "ssd1339.h" // include display definitions
//#include "font8.h" // include 8bit font
//#include "bitmaps.h"// include some pictures
//#include "arduinoa.h"
//#include "arduino1.h"
//#include "arduino2.h"

// definitions
const int EPin = 8; // enable pin
const int RwPin = 9; // read/write pin
const int DCPin = 10; // data command pin
const int CsPin = 11; // chip select pin
const int Enable12VPin = 12; // Enable 12V supply
const int OLEDRstPin = 13; // OLED Reset pin

const int switch1 = 0; // left switch
const int switch2 = 1;
const int switch3 = 2;
const int switch4 = 3; // right switch

int bgrnd_color = BLACK;
int display = NORMAL;
int font_color = GREEN;

char* s_disp[] = {"--OFF---","Normal  ","Invert  ","Sideways","Side_Inv"};
//#include "ssd1339.c"
  
void setup() // standard arduino setup initializing loop
{
  pinMode(EPin, OUTPUT);   
  pinMode(RwPin, OUTPUT); 
  pinMode(DCPin, OUTPUT);
  pinMode(CsPin, OUTPUT); 
  pinMode(Enable12VPin, OUTPUT); 
  pinMode(OLEDRstPin, OUTPUT); 
  
  digitalWrite(Enable12VPin,HIGH);
  digitalWrite(OLEDRstPin,HIGH);
  
  init_colorlcd(display); 
}



void loop() // standard arduino loop
{
 
//  puts8(10,10,"This is a test");
    xyputs(0,0,GREEN,BLACK,s_disp[display]);
    xyputs(0,10,GREEN,BLACK,"This is a test");
    draw_line(30,18,100,30,BLUE16);
    draw_rectangle(25,32,60,50,YELLOW16,RED16);
    draw_circle(90,60,10,WHITE16,GREEN16);
//    do_picture(0,70,100,52,laser_label[0]);        
    do_picture(20,70,10,14,usb_logo[0]);
    delay(2000);


 //  do_picture(0,60,10,14,usb_logo[0]);
//    do_picture(0,60,97,50,RAVAS[0]);
//    clear_screen();
//    do_picture(0,0,60,57,arduinox[0]);
//    do_picture(0,0,60,57,arduino1[0]);

    delay(2000);
    
  if (display==NORMAL) {
    display = INVERT;
  } else if (display==INVERT) {
    display = SIDEWAYS;
  } else if (display==SIDEWAYS) {
    display = SIDEINV;
  } else {
    display = NORMAL;
  }
  init_colorlcd(display); // initialise to new orientation    
}

void  command(int cmd)
{
//    if (display>=F11_NORMAL) {
//        commandx(cmd);
//        return;
//    }


    digitalWrite(DCPin,LOW);
    digitalWrite(RwPin,LOW);

    DDRD = 0xff;
    PORTD = cmd;

    digitalWrite(EPin,HIGH);    
    digitalWrite(CsPin,LOW);  
    digitalWrite(CsPin,HIGH);
    digitalWrite(EPin,LOW);    
}

void  data(int b)
{
//    if (display>=F11_NORMAL) {
//        datax(b);
//        return;
//    }

    digitalWrite(DCPin,HIGH);
    digitalWrite(RwPin,LOW);

    DDRD = 0xff;
    PORTD = b;

    digitalWrite(EPin,HIGH);    
    digitalWrite(CsPin,LOW);  
    digitalWrite(CsPin,HIGH);
    digitalWrite(EPin,LOW); 
}

void   init_colorlcd(int disp)
{

//    if (disp>=F11_NORMAL) { // F11_Normal=3
//        init_colorlcd_1351();
//        return;
//    }

//    PORTA.OUT |= EN_OLED; // turn off
    delay(10);

// command(0xfd);   // unlock
// command(0xb1);
    command(DISPLAY_OFF); // turn off display
    command(CLOCK_DIV); // b3
    data(0x90);

    command(DISP_OFFSET); // a2 set display offset
    if ((disp==NORMAL)||(disp==INVERT)) { 
      data(0x80);
    } else if (disp==SIDEWAYS) { // ||(disp==SIDEINV)
      data(0x84);
    } else { // ||(disp==SIDEINV)
      data(0x80);
    }

    command(MUX_RATIO); // ca set multiplex ratio
    data(131);

    command(MASTER_CONFIG); // ad set multiplex ratio
    data(0x8e);


    command(DISP_START); // a1 display start line
    if ((disp==NORMAL)||(disp==SIDEWAYS)) {
        data(0);
    } else if (disp==INVERT) {
        data(4);
    } else {
        data(4);
    } 

    command(SET_REMAP); // a0 segment remap set to 0x30
    if (disp==NORMAL) {
        data(0x30);
    } else if (disp==INVERT) {
        data(0x22);
    } else if (disp==SIDEWAYS) {
        data(0x21);
     } else  { // if (disp==SIDEINV)
        data(0x33);
    }

    command(MASTER_CURRENT); // c7 master current control
    data(0x0a);
    command(PRECHARGE); // bb precharge
    data(0x1f); //1c
    data(0x1f); // 1c
    data(0x1f); // 1c
    command(CONTRAST_CURRENT); // c1 contrast control
    data(0xff); // c8
    data(0xff); //80
    data(0xff); //c8

    command(VCOMH); // be vcomh
    data(0x1f);
    command(PHASE_LENGTH); // b1
    data(0x74); // was 74
//  command(0xb0);
//  data(0x0);
//  command(0xa6);

    command(POWER_SAVE);
    command(0);
    command(SLEEP_OFF);

    command(DISPLAY_NORMAL);
//  gotoxy(0,0);



    command(FILL_ENABLE);
    data(1); // turn on fill mode
    clear_screen();

}


void  gotoxy(int x, int y)
{
    int offset,yoffset;

    offset = 0;
    yoffset = 0;
    if ((display==INVERT)||(display==SIDEINV)) {
        offset = 4;
    }

     if (display==SIDEINV) {
        yoffset = 4;
    }

    command(SET_COLUMN); // 15
    data(x+offset);
    data(127+offset);

    command(SET_ROW); //75
    data(y+yoffset);
    data(127+yoffset);
}

void  set_screen(int color)
{
int x,y;

    gotoxy(0,0);

    command(WRITE_RAM);
    for (x=0; x<128; x++) {
        for (y=0; y<128; y++) {
//            if (display>=F11_NORMAL) {
//                data(f11[color]);
//                data(f11[color]);
//            } else {
                data(color);
//            }
        }
    }

//    bgrnd_color = color;
}


//// return color in 16bit 5-6-5 for b-g-r
//int find_color(int r, int g, int b)
//{
//    return((b<<11)+(g<<5)+r);
//}
//
//#define BORDER GREY16

void clear_screen(void)
{
    set_screen(BLACK);
}

const unsigned int amask[16] = {0x8000,0x4000,0x2000,0x1000,0x800,0x400,0x200,0x100,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
const byte mask[6] = {0x20,0x10,0x08,0x04,0x02,0x01};

void xyputs(unsigned char x, unsigned char y, int color, int bgrnd, char *s)
{
byte d;
char *s1;


    if (bgrnd==_) {
        bgrnd = bgrnd_color;
    }

    if (color==_) {
        font_color = color;
    }

    if ((display==INVERT)||(display==SIDEINV)) {
        x += 4;
    }
    if (display==SIDEINV) {
        y += 4;
    }
    
  if (display>=SIDEWAYS) {
      command(SET_COLUMN); // 15
      data(y);
      data(y+6);
      command(SET_ROW); //75
      data(x);
      data(x+strlen(s)*6-1);
  } else {      
    command(SET_COLUMN); // 15
    data(x);
    data(x+strlen(s)*6-1);
    command(SET_ROW); //75
    data(y);
    data(y+6);
  }


    command(WRITE_RAM);

    for (y=0; y<7; y++) {
        s1 = s;
        while (*s1) {
//     e = *s1++;
//    if ((e<0x20)||(e>=0x80)) { // skip unprintable characters
//     e = ' ';
//    }
            d = font[*s1++ - 0x20][y];
            for (x=0; x<6; x++) {
                if ((d&mask[x])!=0) {
//                    if (display>=F11_NORMAL) {
//                        data(f11[color]);
//                        data(f11[color]);
//                    } else {
            data(color);
//                    }
                } else {
//                    if (display>=F11_NORMAL) {
//                        data(f11[bgrnd]);
//                        data(f11[bgrnd]);
//                    } else {
                        data(bgrnd);
//                    }
                }
//     waitms(2);
            }
        }
    }
    font_color = color;
}

void puts8(int x, int y, char *s)
{
    xyputs(x,y,font_color,BLACK,s);
}


void draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, int color)
{
    if ((display==INVERT)||(display==SIDEINV)) {
        x1 += 4;
        x2 += 4;
    }
    if (display==SIDEINV) {
        y1 += 4;
        y2 += 4;
    }

    command(DRAW_LINE);
    data(x1);
    data(y1);
    data(x2);
    data(y2);
    data(color>>8);
    data(color&0xff);
    delay(2);// for safety
}


void draw_rectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, int color, int fill_color)
{
    if ((display==INVERT)||(display==SIDEINV)) {
        x1 += 4;
        x2 += 4;
    }
    if (display==SIDEINV) {
        y1 += 4;
        y2 += 4;
    }
    command(DRAW_RECT);
    data(x1);
    data(y1);
    data(x2);
    data(y2);
    data(color>>8);
    data(color&0xff);
    data(fill_color>>8);
    data(fill_color&0xff);
    delay(2); // stops screen going strange
}

void draw_circle(unsigned char x1, unsigned char y1, unsigned char radius, int color, int fill_color)
{
    if ((display==INVERT)||(display==SIDEINV)) {
        x1 += 4;
    }
    if (display==SIDEINV) {
        y1 += 4;
    }
    command(DRAW_CIRCLE);
    data(x1);
    data(y1);
    data(radius);
    data(color>>8);
    data(color&0xff);
    data(fill_color>>8);
    data(fill_color&0xff);
    delay(2); // for safety
}

void enable_fill(unsigned char mode)
{
    command(FILL_ENABLE);
    data(mode);
}

//void scroll(byte start, byte number, byte mode)
//{
//    command(HOR_SCROLL);
//    data(0);
//    data(start);
//    data(number);
//    data(mode);
//    data(0);
//
//    command(START_SCROLL);
//}


//
//void bitmap(const BYTE *bp)
//{
//    byte x,y;
//
//    gotoxy(0,0);
//    command(WRITE_RAM);
//    for (x=0; x<128; x++) {
//        for (y=0; y<128; y++) {
// //           data(*bp);
////            if (display>=F11_NORMAL) {
////                data(f11[*bp]);
////                data(f11[*bp++]);
////            } else {
//                data(*bp++);
////            }
//        }
//    }
//}

void do_picture(int x, int y, int width, int height, const unsigned char *bp)
{

    if ((display==INVERT)||(display==SIDEINV)) {
        x += 4;
    }

    if (display==SIDEINV) {
        y += 4;
    }

  if (display>=SIDEWAYS) {
      command(SET_COLUMN); // 15
      data(y);
      data(y+height-1);
      command(SET_ROW); //75
      data(x);
      data(x+width-1);
  } else {    
      command(SET_COLUMN); // 15
      data(x);
      data(x+width-1);
      command(SET_ROW); //75
      data(y);
      data(y+height-1);
    }
    command(WRITE_RAM);
    for (x=0; x<width; x++) {
        for (y=0; y<height; y++) {
//            if (display>=F11_NORMAL) {
//                data(f11[*bp]);
//                data(f11[*bp++]);
//            } else {
                data(*bp++);
//            }
        }
    }
}



