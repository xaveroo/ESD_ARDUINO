#include <SPI.h>

// #define DATAOUT     11  //COPI
// #define DATAIN      12  //CIPO
// #define SPICLOCK    13  //sck
// #define CHIPSELECT  10  //cs

// SPI peripheral

char buff [50];
byte c;
volatile byte indx;
volatile boolean received;
volatile boolean answer;

void setup (void) {
   Serial.begin (115200);
   while(!Serial){;}
   Serial.println("Serial initiated");
   pinMode(MISO, OUTPUT);           // have to send on master in so it set as output
   SPCR |= _BV(SPE);                // turn on SPI in slave mode
   indx = 0;                        // buffer empty
   SPI.attachInterrupt();           // turn on interrupt
}
ISR(SPI_STC_vect){                  // SPI interrupt routine { 
   c = SPDR;                        // read byte from SPI Data Register
   received=true;                   // raise flags
   answer=true;
   
  //  
  //  if (indx < sizeof buff) {
  //     buff[indx++] = c; // save data in the next index in the array buff
  //     // if (c == '\r') //check for the end of the word
  //  }
}

void loop (void) {

if(received==true){
  Serial.print("received new value: ");
  Serial.println(c);
  received=false;
}
  if((c==88) & (answer==true)){
    Serial.println("starting transmission");
    SPDR = 45,HEX;
    answer = false;
  }

}
