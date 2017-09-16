#include <SoftwareSerial.h>
// Saved by Simulator for Arduino V0.98.B.1

#include <SD.h>

#include <TinyGPS.h>

/*

This file is modified from _02_07_gpsSD, not tested, to reduce size and include file

 name generator at the begining of the set up. file name generator usese date from gps.

*/

//********************

TinyGPS gps;

SoftwareSerial nss(3, 4);

static char dtostrfbuffer[20]; //buffer to hold string

 

//Define String

File myFile;

String SD_date_time = "invalid";

String SD_lat = "invalid";

String SD_lon = "invalid";

String SD_alt = "invalid";

String SD_crs = "invalid";

String SD_spd = "invalid";

String SD_event = 0;

String dataString = "";

String fileName = "";

char filename;

int event = 0;

 

byte CS = 10;

byte LED = 13;

byte LEDred = 6;

 

static void gpsdump(TinyGPS &gps);

static bool feedgps();

//static void print_float(float val, float invalid, int len, int prec, int SD_val);

static void print_int(unsigned long val, unsigned long invalid, int len);

static void print_date(TinyGPS &gps);

// static void print_str(const char *str, int len);

 

void setup()

{

  pinMode(CS, OUTPUT); //CHIP SELECT PIN FOR SD CARD

  pinMode(LED, OUTPUT); // recording data

  pinMode(LEDred, OUTPUT); //error

 

  //  Serial.begin(115200);

  nss.begin(4800);

 

  //Connect to the SD Card

  if(!SD.begin(CS))

  {

    //insert here a red light for card failure

    // Serial.write("card failed...");

    digitalWrite(LEDred, HIGH); //card failed to open

    return;

  } // end if

  // generate name for file from gps date function

  bool newdata = false;

  if (feedgps()) newdata = true;

  print_date(gps);

  if (SD_date_time != "invalid") {

    fileName = fileName + ".fdr";

 

    char filename[fileName.length()+1];

    fileName.toCharArray(filename, sizeof(filename));

 

    myFile = SD.open(filename, FILE_WRITE);

    myFile.close();

 

  }

 

 

}

 

void loop()

{

  bool newdata = false;

  unsigned long start = millis();

 

  // Every second we print an update

  while (millis() - start < 1000)

  {

    if (feedgps())

      newdata = true;

  }

 

  gpsdump(gps);

 

  dataString = "DATA," + SD_event + "," + "59," + SD_lon + "," + SD_lat + "," + SD_alt +  ",0,0,0,0,0,0," + SD_crs + "," + SD_spd + "," ;

 

  // Serial.println (dataString);

 

  /// this will check for valid data before writing to SD card

  if(SD_date_time != "invalid"){ 

    digitalWrite(LED, HIGH); // Writing to card

    // open the data CSV File

    char filename[fileName.length()+1];

    fileName.toCharArray(filename, sizeof(filename));

    File dataFile = SD.open(filename, FILE_WRITE);

    if (dataFile)dataFile.println(dataString);

    else digitalWrite(LEDred, HIGH); //indicat error

    dataFile.close();

  }

  else {

    for (int i=0; i<100; ++i) {

      digitalWrite(LEDred, HIGH);   // turn the LED on (HIGH is the voltage level)

      delay(1000);               // wait for a second

      digitalWrite(LEDred, LOW);    // turn the LED off by making the voltage LOW

      delay(1000);               // wait for a second

    }

  }

}

 

 

static void gpsdump(TinyGPS &gps)

{

  float flat, flon;

// unsigned long age, date, time, chars = 0;

   unsigned long age;

  // print_date(gps);

  gps.f_get_position(&flat, &flon, &age);

  SD_lon = dtostrf(flon, 10,5,dtostrfbuffer);

  SD_lat = dtostrf(flat, 10,5,dtostrfbuffer);

  unsigned int alt = gps.f_altitude();

  unsigned int msl = alt * 3.28084;

  SD_alt = dtostrf(msl,10,5,dtostrfbuffer);

  unsigned int crs = gps.f_course();

  SD_crs = dtostrf(crs,10,5,dtostrfbuffer);

  unsigned int spd = gps.f_speed_mph();

  SD_spd = dtostrf(spd,10,5,dtostrfbuffer);

 

  // print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 9, 5, 1);

  // print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 10, 5, 2);

  // print_float(msl, TinyGPS::GPS_INVALID_F_ALTITUDE, 8, 2, 3);

  //  print_float(gps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2, 4);

  //  print_float(gps.f_speed_kmph(), TinyGPS::GPS_INVALID_F_SPEED, 6, 2, 5);

 

  Serial.println();

  SD_event = dtostrf(event,10,5,dtostrfbuffer);

  event++;

 

}

 

static void print_int(unsigned long val, unsigned long invalid, int len)

{

  char sz[32];

  if (val == invalid)

    strcpy(sz, "000000");

  else

    sprintf(sz, "%ld", val);

  sz[len] = 0;

  for (int i=strlen(sz); i<len; ++i)

    sz[i] = ' ';

  if (len > 0)

    sz[len-1] = ' ';

  Serial.print(sz);

  feedgps();

}

/*

static void  print_float(float val, float invalid, int len, int prec, int SD_val)

{

char sz[32];

if (val == invalid)

{

strcpy(sz, "000000");

sz[len] = 0;

if (len > 0)

 sz[len-1] = ' ';

for (int i=7; i<len; ++i)

sz[i] = ' ';

Serial.print(sz);

if (SD_val == 1) SD_lat = sz;

else if (SD_val == 2) SD_lon = sz;

else if (SD_val == 3) SD_alt = sz;

else if (SD_val == 4) SD_crs = sz;

else if (SD_val == 5) SD_spd = sz;

}

else

{

Serial.print(val, prec);

if (SD_val == 1) SD_lat = dtostrf(val,10,5,dtostrfbuffer);

else if (SD_val == 2) SD_lon = dtostrf(val,10,5,dtostrfbuffer);

else if (SD_val == 3) SD_alt = dtostrf(val,10,5,dtostrfbuffer);

else if (SD_val == 4) SD_crs = dtostrf(val,10,5,dtostrfbuffer);

else if (SD_val == 5) SD_spd = dtostrf(val,10,5,dtostrfbuffer);


 int vi = abs((int)val);

int flen = prec + (val < 0.0 ? 2 : 1);

flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;

for (int i=flen; i<len; ++i)

Serial.print(" ");

}

feedgps();

}

*/

static void print_date(TinyGPS &gps)

{

  int year;

  byte month, day, hour, minute, second, hundredths;

  unsigned long age;

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);

  if (age == TinyGPS::GPS_INVALID_AGE)

  {

    //   Serial.print("00/00/00    00:00:00    ");

    SD_date_time = "invalid";

  }

  else

  {

    char sz[32];

    char dt[16];

    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d   ",

    month, day, year, hour, minute, second);

    Serial.print(sz);

    SD_date_time = sz;

    sprintf(dt, "%02d%02d%02d%02d",month, day, minute, second);

    fileName = dt;

  }

  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);

  feedgps();

}

/*

static void print_str(const char *str, int len)

{

int slen = strlen(str);

for (int i=0; i<len; ++i)

Serial.print(i<slen ? str[i] : ' ');

feedgps();

}

*/

static bool feedgps()

{

  while (nss.available())

  {

    if (gps.encode(nss.read()))

      return true;

  }

  return false;

}
