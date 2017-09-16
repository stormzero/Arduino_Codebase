/*
Simple Arduino project for those who don't want to learn C++.
Control of an Arduino board using simple ASCII commands sent
from a Terminal or via a serial port from within another
program such as Visual Basic or Visual C#
(C) Phil Morris 2013 All rights reserved

Basic Commands: (All commands end with Carriage Return (ASCII 13)

V                            Print version
RT                            Reset all pins to inputs
DA                            Read ALL digital pin values
ON                            Turn ON OK responses to commands (default)
OF                            Turn OFF OK responses to commands
PM,pin,(I)(O)(P)            Set Pin to INPUT, OUTPUT or INPUT_PULLUP
PR,pin                        Read Pin state
PW,pin,(H)(L)                Set Pin to HIGH or LOW
AR                            Read Analog Pin values
SA,(I)(O)                    Set all pins to INPUT or OUTPUT
BI,start,number                Set block of pins to INPUT starting at pin#
BO,start,number                Set block of pins to OUTPUT starting at pin#
BR,start,number                Get states of a block of pins
BW,start,number,(B)(H),data    Write a block of pins. Data is in hex or binary < lsb

Error messages:

1    Invalid Parameters
2    Not enough hex characters
3    Not enough binary characters
4    Invalid hex character
5    Invalid binary character

===================================================================*/

//#include <Streaming.h>

//Array:

char analogArray[32] = "A,";    // used to build an array of the analog outputs
String messStrings[3]={"Command too short!", "Invalid parameters!", "Pin must be > 1!"};
char binTemp[4];

char inBuffer[65];
char binBits[20];

//Constant:

const int LOWPIN = 2;                    // lowest pin number that can be used
const char HEX2BIN[] = "0000000100100011010001010110011110001001101010111100110111101111";
const char VERSION[] = "V 1.0.0";

//Char:

char tempHex;

//Integer:

int charPos = 0;                // pointer to the elements of the inBuffer array
int CR = 13;                    // Carriage Return
int pinNum = 0;                    // used by the pin parsing function
int startPin = 0;                // used for block modes
int startPos = 0;                // used for block modes            
int lpCnt = 0;                    //for "for" loops;
int analogValue;                // used for analog pin reading
int blockData;                    // used for block write command
int nextData;                    // used as a pointer to data after pin numbers

//Boolean:

bool okFlag = true;                // used for the OK responses

void setup()
{
    Serial.begin(57600);            // start the serial port
}

void loop()
{
    Get_Serial();                // check the serial port input buffer and get any messages

    switch(inBuffer[0])            // switch on the first character of the input buffer
    {
        case 'V':                // Version print function
        {
            Version();
            break;
        }
        case 'R':                // R_Commands function
        {
            R_Commands();
            break;
        }
        case 'O':                // OK response on/off
        {
            O_Commands();
            break;
        }
        case 'P':                // Pin commands function
        {
            P_Commands();
            break;
        }
        case 'A':                // Analog pin function
        {
            AnalogPinMode();
            break;
        }
        case 'D':
        {
            D_Commands();
            break;
        }
        case 'S':
        {
            S_Commands();
            break;
        }
        case 'B':
        {
            B_Commands();
            break;
        }
    }
    
}

void Get_Serial()
{
    memset(&inBuffer[0], 0, sizeof(inBuffer));            // zero the inBuffer array
        if(!Serial.available()) return;                    // see if there are characters in the serial buffer
            Serial.readBytesUntil(CR, inBuffer, 64);    // if there are, read them into the inBuffer
                UpperCase(inBuffer,sizeof(inBuffer));    // uppercase convert for development
                
                //Serial.print(inBuffer);                                //JUST FOR DEV WORK
                //Serial << " Len " << strlen(inBuffer) << endl;        //JUST FOR DEV WORK
}

void Version()
{
    Serial.println(VERSION);    // print the version number
}

void D_Commands()    // we got here if the first command letter was "D"
{

    switch(inBuffer[1])
    {
        case 'A':                                        // read ALL digital pin states
        {
            analogArray[0] = 'D';                        // use the analogArray and set start to "D"

            for(lpCnt = 2;lpCnt < 20;lpCnt++)            // loop all pins 2 thru 19
            {
                analogArray[lpCnt] = digitalRead(lpCnt) + '0';                // add ASCII "0" to value and store it in array
            }
            analogArray[lpCnt] = 0;                        // close the end of the array
            Serial.println(analogArray);                // show the world
        } 
    }

}

void R_Commands()    // we got here if the first command letter was "R"
{
    // set all pins to inputs except 0 & 1 which we
    // are using for the serial port

    switch(inBuffer[1])
    {
        case 'T':
            {
                Set_All(INPUT);
                okFlag = true;    // Reset the OK flag
                SendOK();        // Send OK response
                break;
            }
        default: { ErrorMessage(0); }
    }
}

void O_Commands()    // we got here if the first command letter was "O"
{
    switch(inBuffer[1])
    {
        case 'N':
        {
            okFlag = true;
            SendOK();
            break;
        }
        case 'F':
        {
            okFlag = false;
            break;
        }
    }
}

void P_Commands()    // we got here if the first command letter was "P"
{
    // check the second command letter, either M, R or W
    // also remember that we are using pins 2 thru 19
    
    switch(inBuffer[1])
    {
        case 'M':    // Pin Mode
        {
            if(!Get_Decimal(6,3))
            {
                ErrorMessage(1);
                break;
             }

            //if(inBuffer[charPos] == ',') nextPos = 6;    // sub command must be the next character
            
            if(inBuffer[nextData] == 'I') pinMode(pinNum,INPUT);
            if(inBuffer[nextData] == 'O') pinMode(pinNum,OUTPUT);
            if(inBuffer[nextData] == 'P') pinMode(pinNum,INPUT_PULLUP);
            SendOK();
            break;
        }
        case 'R':    // Pin Read
        {
            if(!Get_Decimal(4,3))
            {
                ErrorMessage(1);
                break;
             }

            Serial.println(digitalRead(pinNum),DEC);    //show the world
            break;
        }
        case 'W':    // Pin Write
        {
            if(!Get_Decimal(6,3))
            {
                ErrorMessage(1);
                break;
             }
            
            if(inBuffer[nextData] == 'H') digitalWrite(pinNum,HIGH);
            if(inBuffer[nextData] == 'L') digitalWrite(pinNum,LOW);
            SendOK();
            break;
        }

    }
}

void AnalogPinMode()    // we got here if the first command letter was "A"
{
    // check the second command letter, either M, R or W
    // also remember that we are using pins 0 thru 5!
    // Arduino will accept pins 14 thru 19 as A0 - A5


    switch(inBuffer[1])                                // only using "R" for now
    {
        case 'R':                                    // will output all the analog readings in analogArray[]
        {                                            // format A,0000,0000,0000,0000,0000,0000

            analogArray[0] = 'A';                    // set the first character to "A"
            charPos = 2;                            //first analog reading position in the array

            for(int i = 14;i < 20;i++)                // cycle thru pins 14 to 19
            {
                analogValue = analogRead(i);        // get the value of pin "i"

                for (int j = 3;j > -1;j--)            // convert and add the pin value to the analog array
                {
                    analogArray[j + charPos] = (analogValue % 10) + '0';
                    analogValue = abs(analogValue / 10);
                }
                    
                charPos += 4;                        // bump the pointer to the next position
                analogArray[charPos] = ',';            // add a comma between the values in the array
                charPos++;                            // bump the pointer just once more
            }
            analogArray[charPos - 1] = 0;            // set the end of the array
            Serial.println(analogArray);            // show the public the results
            break;                                    // now get out of here
        }
    
    }

}

void B_Commands()    // we got here if the first command letter was "B"
{
    switch(inBuffer[1])                                // second char of inBuffer
    {
        case 'I':                                    // Block set INPUT
        {
            Block_Set(INPUT);
            SendOK();
            break;
        }
        case 'O':                                    // Block set OUTPUT
        {
            Block_Set(OUTPUT);
            SendOK();
            break;
        }
        case 'R':                                    // Block Read
        {
            Block_Read();
            break;
        }
        case 'W':                                    // Block Write
        {
            Block_Write();
            break;
        }
    }
}

void S_Commands()    // we got here if the first command letter was "S"
{
    switch(inBuffer[1])
    {
        case 'A':                            // this is Set All pins
        {
            switch(inBuffer[3])
            {
                case 'I':                    // set all to INPUT
                {
                    Set_All(INPUT);
                    SendOK();
                    break;
                }
                case 'O':                    // set all to OUTPUT
                {
                    Set_All(OUTPUT);
                    SendOK();
                    break;
                }
                default: ErrorMessage(1);
            }
        }
    }
}

bool Get_Decimal(int cmdLen, int startPos)
{
// gets a decimal number starting at startPos and ending at the next "," or EOS;
// also return the start of the next block of data in nextData
// cmdLen is the minimum length of the command string
// startPos is the point in the inBuffer to start the parsing
    
        pinNum = 0;                                            // clear the holder for the decimal result
            nextData = 0;                                        // clear the next data pointer

        if(strlen(inBuffer) < cmdLen)                        // check that the command is as long as we expect
            {
                ErrorMessage(1);
                return false;
            }

        int buffLength = strlen(inBuffer);                    // get the length of inBuffer

    // look for the next comma or the End Of String. nextData will be 1 more than the number of characters to convert

        char tempDec = '0';

            for(int i = startPos;i < buffLength + 1;i++)
                {
                    tempDec = inBuffer[i];
                    if(tempDec == ',' || tempDec == 0)
                        {
                            nextData = i;
                            break;
                        }
                }

    // now convert the buffer characters to decimal

        int multiplier = 1;

        for(int i = nextData - 1;i > startPos - 1;i--)        // convert backwards
            {
                pinNum += (inBuffer[i] - '0') * multiplier;
                multiplier *= 10;
            }

    // finally, if nextData points at the EOS, zero nextData. if not bump it up 1

        nextData++;
            if(tempDec == 0) nextData = 0;
                //Serial << "Pin " << pinNum << " Next " << nextData << endl;    // JUST FOR DEV WORK
                    return pinNum;
}

void SendOK()
{
    if(okFlag) Serial.println("OK");
}

void UpperCase(char* pArray, int arrayLength)
{
    for(int i = 0; i < arrayLength; i++)
    {
        if(pArray[i] >= 'a' && pArray[i] <= 'z') pArray[i] -= ' ';
    }
}

void ErrorMessage(int message)
{
// prints the error message

    Serial.print("Error:> ");
        Serial.println(message);
            inBuffer[0] = 0;    // kill the inBuffer
}

void Block_Set(int mode)
{
// mode is either INPUT or OUTPUT
// startPin is the first pin to set
// pinNum is the number of pins to set

            if(!Block_Find(6)) return;                // returns startPin and pinNum

            for(lpCnt = startPin;lpCnt < (startPin + pinNum);lpCnt++)
            {
                pinMode(lpCnt,mode);                // set the pins
            }
}

void Block_Read()
{
// reads the state of a block of pins
// we can use the analogArray for this task

            analogArray[0] = 'B';                    // set the first character of the array to "B"
            
            if(!Block_Find(6)) return;

            charPos = 2;                            // we'll use charPos as a counter for the array

            for(lpCnt = startPin;lpCnt < (startPin + pinNum);lpCnt++)
            {
                analogArray[charPos] = digitalRead(lpCnt) + '0';
                charPos++;
            }
            analogArray[charPos] = 0;                // terminate the array
            Serial.println(analogArray);
}

void Block_Write()
{
// format is BW,start pin, number of pins, data in hex binary characters e.g 10110 < lsb
// command length is important so we have to check that there are enough data characters

        if(!Block_Find(9)) return;                        // is address data valid?

        // we should have the start pin and the number of pins
        // startPin = start, pinNum = number of pins, nextData points to the data type e.g. B(inary) or H(ex)
        // now get the hex data in the next 5 bytes of the inBuffer

        switch(inBuffer[nextData])
        {
            case 'H':
            {
                // first check that there enough hex characters

                nextData++;    // now pointing at the hex data

                if(pinNum > (strlen(inBuffer) - nextData) * 4)    // check number of bits in the hex data
                    {
                        //Serial << "You don't have enough hex characters!" << endl; // make this an error message later
                        return;
                    }

                // loop for the number of hex characters in the buffer

                int checkHex = 0;

                for(lpCnt = 0;lpCnt < (strlen(inBuffer) - nextData);lpCnt++)    // convert hex string into integer
                    {
                        tempHex = inBuffer[lpCnt + nextData];                        // get the first hex character
                        
                        
                        if(tempHex >= '0' && tempHex <= '9') checkHex = inBuffer[lpCnt + nextData] - '0';
                        if(tempHex >= 'A' && tempHex <= 'F') checkHex = (inBuffer[lpCnt + nextData] - 'A') + 10;
                        

                        // by now checkHex contains 0 to 15 (0 - F) as a pointer for the HEX2BIN string
                        // char binBits[18] will hold bits msb first

                        // get the binary data for the hex character from the HEX2BIN string

                        for(int i = 0;i < 4;i++) binBits[i + (lpCnt * 4)] = HEX2BIN[(checkHex * 4) + i];
                    }

                        // now write the pins from the binary data using the pinNum integer starting at startPin
                        // any aditional bits will be ignored. the binary data is taken in reverse order
                        // there are 20 bits in the binBits string but we start at pinNum - 1

                        int downCnt = pinNum - 1;

                        for(int i = 0;i < pinNum;i++)
                            {
                                digitalWrite(startPin+i,binBits[downCnt] - '0');
                                downCnt--;
                                //Serial << "Pin " << startPin + i << " Data " << binBits[downCnt] << " Down count " << downCnt << endl;
                            }


                        //Serial << "Start " << startPin << " Written " << pinNum << endl;
                        break;
            }
        case 'B':
            {
                // startPin = first pin to write
                // pinNum = number pins to write
    
                // first check that there enough binary characters

                nextData++;    // now pointing at the binary data

                    if(pinNum != (strlen(inBuffer) - nextData))    // check number of bits in the binary data = pinNum
                        {
                            //Serial << "Incorrect number of binary characters!" << endl; // make this an error message later
                            break;
                        }

                // get the binary string characters and convert to integer and write to pins

                    int downCnt = strlen(inBuffer) - 1;
                    int checkBit = 0;
                        
                        for(int i = 0;i < pinNum;i++)
                            {
                                checkBit = inBuffer[downCnt] - '0';
                                if(checkBit < 0 or checkBit > 1)        // just make sure that the binary data is valid
                                    {
                                        //Serial << "Invalid binary data!" << endl;
                                        break;
                                    }
                                digitalWrite(startPin+i,checkBit);
                                downCnt--;
                                //Serial << "Pin " << startPin + i << " Data " << binBits[downCnt] << " Down count " << downCnt << endl;
                            }
                            
                        //Serial << "Start " << startPin << " Written " << pinNum << endl;
                        break;
            }
        default:
            {
                //Serial << "Did you forget the data qualifier B or H after the pin numbers?" << endl;
            }

        }

}



void Set_All(int mode)
{
// sets all pins to either INPUT or OUTPUT

        for(lpCnt = 2;lpCnt < 20;lpCnt++) pinMode(lpCnt,mode);
}

bool Block_Find(int cmd)
{

// cmd contains the minimum command string length expected
// finds 2 sets of pin numbers. startPin will contain the start pin
// pinNum will contain the number of pins to work on

            if(!Get_Decimal(cmd,3))                // get the pin number to start at
            {
                ErrorMessage(1);
                return false;
            }


            startPin = pinNum;                    // startPin becomes the start pin
            
            if(!Get_Decimal(cmd,nextData))        // get the number of pins to use in pinNum
            {
                ErrorMessage(1);
                return false;
            }

            if(startPin + pinNum > 20)                // check that we don't go beyond pin 19
            {
                ErrorMessage(1);
                return false;
            }

            //Serial << "Pin " << startPin << " Pins " << pinNum << " Next " << nextData << endl;
            return true;
}
