// Code Example for jolliFactory 1X Bi-color LED Matrix Test Check
// The Bi-color LED Matrix shall display in RED, GREEN and then ORANGE in sequence row by row continuously


/* ============================= LED Matrix Display ============================= */
#include <SPI.h>          
       
#define GREEN 0                          
#define RED 1                            

#define offREDoffGREEN 0
#define offREDonGREEN 1
#define onREDoffGREEN 2

#define ISR_FREQ 190     //190=650Hz    // Sets the speed of the ISR

int SPI_CS = 10;// This SPI Chip Select pin controls the MAX7219
int bi_maxInUse = 1; //No. of Bi-color LED Matrix used
int maxInShutdown = RED; // indicates which LED Matrix color is currently off
int SetbrightnessValue = 15;
int colorMode = '3';  // default color (1 = RED, 2 = GREEN, 3 = ORANGE, 4 = blank off)








//**********************************************************************************************************************************************************  
void setup() 
{
  pinMode(SPI_CS, OUTPUT);

  Serial.begin (9600);
  Serial.println("jolliFactory Bi-Color LED Matrix Test Check");              

  SPI.begin(); //setup SPI Interface

  bi_maxTransferAll(0x0F, 0x00);   // 00 - Turn off Test mode
  bi_maxTransferAll(0x09, 0x00);   //Register 09 - BCD Decoding  // 0 = No decoding
  bi_maxTransferAll(0x0B, 0x07);   //Register B - Scan limit 1-7  // 7 = All LEDS
  bi_maxTransferAll(0x0C, 0x01);   // 01 = on 00 = Power saving mode or shutdown

  setBrightness();

  setISRtimer();                        // setup the timer
  startISR();                           // start the timer to toggle shutdown

  clearDisplay(GREEN);
  clearDisplay(RED);
}




//**********************************************************************************************************************************************************  
void loop() 
{
  clearDisplay(RED);
  clearDisplay(GREEN);
    
  for (int i=0;i<8;i++)      
  {
    bi_maxTransferSingle(RED, 1, i,  255);          
    delay(100);
  }
    
  clearDisplay(RED);
  clearDisplay(GREEN);
  
  for (int i=0;i<8;i++)      
  {          
    bi_maxTransferSingle(GREEN, 1, i, 255);
    delay(100);
  }

  clearDisplay(RED);
  clearDisplay(GREEN);
  
  for (int i=0;i<8;i++)      
  {
    bi_maxTransferSingle(RED, 1, i,  255);          
    bi_maxTransferSingle(GREEN, 1, i, 255);
    delay(100);
  }
}





//**********************************************************************************************************************************************************  
// Change Max72xx brightness
void setBrightness()
{      
    bi_maxTransferAll(0x0A, SetbrightnessValue);      //Set Brightness
    bi_maxTransferAll(0x00, 0x00);  //No-op commands
}



//**********************************************************************************************************************************************************  
// Clear Display
void clearDisplay(uint8_t whichColor) //whichColor = 1 for RED, 2 for GREEN
{     
    for (int y=0; y<8; y++) {
      bi_maxTransferSingle(whichColor, 1, y, 0); //Turn all Off  //For X1 LED matrix Game
      bi_maxTransferSingle(whichColor, 2, y, 0); //Turn all Off  //For X1 LED matrix Game
    }
}



//**********************************************************************************************************************************************************  
/**
 * Transfers data to a MAX7219/MAX7221 register of a particular Bi-color LED Matrix module.
 *
 * @param whichMax The Max72xx to load data and value into
 * @param address The register to load data into
 * @param value Value to store in the register
 */
//**********************************************************************************************************************************************************  
void bi_maxTransferAll(uint8_t address, uint8_t value) {
  stopISR();
  digitalWrite(SPI_CS, LOW); 

    for ( int c=1; c<= bi_maxInUse*2;c++) {
        SPI.transfer(address);
        SPI.transfer(value);
    }

  digitalWrite(SPI_CS, HIGH); 
  startISR();
}


 
//**********************************************************************************************************************************************************  
void bi_maxTransferOne(uint8_t whichMax, uint8_t address, uint8_t value) {

  byte noop_reg = 0x00;    //max7219 No op register
  byte noop_value = 0x00;  //value

  stopISR();
  digitalWrite(SPI_CS, LOW); 

  for (int i=bi_maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices 
  {
    if (i==whichMax)
    {
      SPI.transfer(address);
      SPI.transfer(value);

      SPI.transfer(address);
      SPI.transfer(value);

    }
    else
    {
      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);

      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);
    }
  }

  digitalWrite(SPI_CS, HIGH);
  startISR();
}



//**********************************************************************************************************************************************************  
void bi_maxTransferSingle(uint8_t whichColor, uint8_t whichMax, uint8_t address, uint8_t value) {  //whichColor = 1 for RED, 2 for GREEN

  byte noop_reg = 0x00;    //max7219 No op register
  byte noop_value = 0x00;  //value

  stopISR();
  digitalWrite(SPI_CS, LOW); 


if (whichColor==GREEN)
{
  for (int i=bi_maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices 
  {
    if (i==whichMax)
    {
      SPI.transfer(address+1);
      SPI.transfer(value);

      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);

    }
    else
    {
      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);

      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);
    }
  }
}
else
{
  for (int i=bi_maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices 
  {
    if (i==whichMax)
    {
      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);

      SPI.transfer(address+1);
      SPI.transfer(value);

    }
    else
    {
      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);

      SPI.transfer(noop_reg);
      SPI.transfer(noop_value);
    }
  }
}


  digitalWrite(SPI_CS, HIGH);
  startISR();
}



//**********************************************************************************************************************************************************  
void bi_maxShutdown(uint8_t cmd) 
{
  byte noop_reg = 0x00;      //max7219_reg_no_op
  byte shutdown_reg = 0x0c;  //max7219_reg_shutdown
  byte col = 0x01;  //shutdown false
  byte col2 = 0x00;  //shutdown true


  if (cmd == offREDoffGREEN)
  {    
    stopISR();
    digitalWrite(SPI_CS, LOW);

    for (int c =1; c<= bi_maxInUse; c++)
    {
      SPI.transfer(shutdown_reg);
      SPI.transfer(col2);

      SPI.transfer(shutdown_reg);
      SPI.transfer(col2);
    }

    digitalWrite(SPI_CS, HIGH);    
    startISR();
  }
  else if (cmd == offREDonGREEN)
  {
    stopISR();
    digitalWrite(SPI_CS, LOW);

    for (int c =1; c<= bi_maxInUse; c++) 
    {
      SPI.transfer(shutdown_reg); 
      SPI.transfer(col);

      SPI.transfer(shutdown_reg);
      SPI.transfer(col2);
    }

    digitalWrite(SPI_CS, HIGH);
    startISR();
  }
  else if (cmd == onREDoffGREEN)
  {
    stopISR();
    digitalWrite(SPI_CS, LOW);

    for (int c =1; c<= bi_maxInUse; c++) 
    {      
      SPI.transfer(shutdown_reg);
      SPI.transfer(col2);

      SPI.transfer(shutdown_reg);
      SPI.transfer(col);
    }

    digitalWrite(SPI_CS, HIGH);
    startISR();
  }



  //No ops register to shift out instructions   
  stopISR();
  digitalWrite(SPI_CS, LOW);

  for (int c =1; c<= bi_maxInUse; c++) 
  {      
    SPI.transfer(noop_reg);
    SPI.transfer(0x00);

    SPI.transfer(noop_reg);
    SPI.transfer(0x00);
  }

  digitalWrite(SPI_CS, HIGH);
  startISR();
}



//**********************************************************************************************************************************************************
void altShutDown()    //alternate shutdown of MAX7219 chips for RED and GREEN LEDs 
{
  if (colorMode == '3')    //Scrolling in ORANGE
  {
    if(maxInShutdown==RED){
      bi_maxShutdown(onREDoffGREEN);
      maxInShutdown=GREEN;
    } 
    else 
    { 
      bi_maxShutdown(offREDonGREEN);
      maxInShutdown=RED;
    }
  }
  else if (colorMode == '2')   //Scrolling in GREEN
  {
    bi_maxShutdown(offREDonGREEN);
    maxInShutdown=RED;
  }
  else if (colorMode == '1')   //Scrolling in RED
  {
    bi_maxShutdown(onREDoffGREEN);
    maxInShutdown=GREEN;
  }
  else if (colorMode == '4')  //Blank Display
  {
    bi_maxShutdown(offREDoffGREEN);       
    maxInShutdown=GREEN;
  }
} 



//**********************************************************************************************************************************************************
ISR(TIMER2_COMPA_vect) {  //This ISR toggles shutdown between the 2MAX7221's

  if (colorMode == '3')    // ORANGE
  {
    if(maxInShutdown==RED){
      bi_maxShutdown(onREDoffGREEN);
      maxInShutdown=GREEN;
    } 
    else 
    { 
      bi_maxShutdown(offREDonGREEN);
      maxInShutdown=RED;
    }
  }
  else if (colorMode == '2')   // GREEN
  {
    bi_maxShutdown(offREDonGREEN);
    maxInShutdown=RED;
  }
  else if (colorMode == '1')   // RED
  {
    bi_maxShutdown(onREDoffGREEN);
    maxInShutdown=GREEN;
  }
  else if (colorMode == '4')  //Blank Display
  {
    bi_maxShutdown(offREDoffGREEN);       
    maxInShutdown=GREEN;
  }
} 



//**********************************************************************************************************************************************************
void setISRtimer() // setup ISR timer controling toggleing
{ 
  TCCR2A = 0x02;                        // WGM22=0 + WGM21=1 + WGM20=0 = Mode2 (CTC)
  TCCR2B = 0x05;                        // CS22=1 + CS21=0 + CS20=1 = /128 prescaler (125kHz)
  TCNT2 = 0;                            // clear counter
  OCR2A = ISR_FREQ;                     // set TOP (divisor) - see #define
}
     
 
     
//**********************************************************************************************************************************************************
void startISR()    // Starts the ISR
{
  TCNT2 = 0;                            // clear counter (needed here also)
  TIMSK2|=(1<<OCIE2A);                  // set interrupts=enabled (calls ISR(TIMER2_COMPA_vect)
}

  
     
//**********************************************************************************************************************************************************
void stopISR()    // Stops the ISR
{
  TIMSK2&=~(1<<OCIE2A);                  // disable interrupts
}
