#include <SPI.h>

#define handshake 1
#define send_val 69


// #define DATAOUT     11  //COPI
// #define DATAIN      12  //CIPO
// #define SPICLOCK    13  //sck
// #define CHIPSELECT  10  //cs

// SPI peripheral

char buff [50];
byte c;
volatile byte indx;
volatile boolean received;


void setup (void) {
   Serial.begin (115200);
   while(!Serial){;}
   Serial.println("Serial initiated");
   pinMode(MISO, OUTPUT);               // have to send on master in so it set as output
   SPCR |= _BV(SPE);                    // turn on SPI in slave mode
   indx = 0;                            // buffer empty
   SPI.attachInterrupt();               // turn on interrupt
}
ISR(SPI_STC_vect){                      // SPI interrupt routine { 
   c = SPDR;                            // read byte from SPI Data Register
   received=true; 
  // buffer longer messages (inside service routine??)
  //  if (indx < sizeof buff) {
  //     buff[indx++] = c; // save data in the next index in the array buff
  //     // if (c == '\r') //check for the end of the word
  //  }
}

void loop (void) {

  if(received==true&c!=0){                // for whatever reason receives "0" after sending value
    Serial.print("received new value: ");
    Serial.println(c);
    if(c==handshake){
      SPDR = send_val, DEC;
      delay(15);
      Serial.print("value confirmed. sending: ");
      Serial.println(send_val);
    }
    delay(15);
    received=false;
  }
}
