{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 /*\par
  UDPSendReceive.pde:\par
 This sketch receives UDP message strings, prints them to the serial port\par
 and sends an "acknowledge" string back to the sender\par
 \par
 A Processing sketch is included at the end of file that can be used to send \par
 and received messages for testing with a computer.\par
 \par
 created 21 Aug 2010\par
 by Michael Margolis\par
 \par
 This code is in the public domain.\par
 */\par
\par
\par
#include <SPI.h>         // needed for Arduino versions later than 0018\par
#include <Ethernet.h>\par
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008\par
\par
\par
// Enter a MAC address and IP address for your controller below.\par
// The IP address will be dependent on your local network:\par
byte mac[] = \{  \par
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED \};\par
IPAddress ip(192, 168, 1, 177);\par
\par
#define UDP_TX_PACKET_MAX_SIZE 100\par
\par
unsigned int localPort = 8888;      // local port to listen on\par
\par
// buffers for receiving and sending data\par
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,\par
char  ReplyBuffer[] = "acknowledged";       // a string to send back\par
\par
// An EthernetUDP instance to let us send and receive packets over UDP\par
EthernetUDP Udp;\par
\par
void setup() \{\par
  // start the Ethernet and UDP:\par
  Ethernet.begin(mac,ip);\par
  Udp.begin(localPort);\par
\par
  Serial.begin(9600);\par
\}\par
\par
void loop() \{\par
  // if there's data available, read a packet\par
  int packetSize = Udp.parsePacket();\par
  if(packetSize)\par
  \{\par
    Serial.print("Received packet of size ");\par
    Serial.println(packetSize);\par
    Serial.print("From ");\par
    IPAddress remote = Udp.remoteIP();\par
    for (int i =0; i < 4; i++)\par
    \{\par
      Serial.print(remote[i], DEC);\par
      if (i < 3)\par
      \{\par
        Serial.print(".");\par
      \}\par
    \}\par
    Serial.print(", port ");\par
    Serial.println(Udp.remotePort());\par
\par
    // read the packet into packetBufffer\par
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);\par
    Serial.println("Contents:");\par
    Serial.println(packetBuffer);\par
\par
    // send a reply, to the IP address and port that sent us the packet we received\par
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());\par
    Udp.write(ReplyBuffer);\par
    Udp.endPacket();\par
  \}\par
  delay(10);\par
\}\par
\par
\par
/*\par
  Processing sketch to run with this example\par
 =====================================================\par
 \par
 // Processing UDP example to send and receive string data from Arduino \par
 // press any key to send the "Hello Arduino" message\par
 \par
 \par
 import hypermedia.net.*;\par
 \par
 UDP udp;  // define the UDP object\par
 \par
 \par
 void setup() \{\par
 udp = new UDP( this, 6000 );  // create a new datagram connection on port 6000\par
 //udp.log( true ); \tab\tab // <-- printout the connection activity\par
 udp.listen( true );           // and wait for incoming message  \par
 \}\par
 \par
 void draw()\par
 \{\par
 \}\par
 \par
 void keyPressed() \{\par
 String ip       = "192.168.1.177";\tab // the remote IP address\par
 int port        = 8888;\tab\tab // the destination port\par
 \par
 udp.send("Hello World", ip, port );   // the message to send\par
 \par
 \}\par
 \par
 void receive( byte[] data ) \{ \tab\tab\tab // <-- default handler\par
 //void receive( byte[] data, String ip, int port ) \{\tab // <-- extended handler\par
 \par
 for(int i=0; i < data.length; i++) \par
 print(char(data[i]));  \par
 println();   \par
 \}\par
 */\par
\par
\par
\par
}
 