#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(7,8);

byte addresses[][6] = {"1Node","2Node"};

  // The two different roles.
int OUT1 = 3;
int OUT2 = 5;
int OUT3 = 6;
int OUT4 = 9;
char command = '\0';
int pwm_speed = 80; //from 0 - 255
char last_command; //remember the last command for speed adjustment
void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.begin(9600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
   radio.enableDynamicPayloads();


  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop(void){
    
     if( radio.available()){
      unsigned long got_time;                                       // Variable for the received timestamp
      if (radio.available())  {
uint8_t len = radio.getDynamicPayloadSize();        // While there is data ready
        radio.read( &command, len );             // Get the payload
         
     char response[30] = "";
                                       // Now, resume listening so we catch the next packets.     
    switch (command)
  {
    case 'e': //go forward
    Serial.println("Go!!\r\n");       
    analogWrite(OUT1, pwm_speed);   //PWM speed control
    analogWrite(OUT2, 0);   
    analogWrite(OUT3, 0);   
    analogWrite(OUT4, pwm_speed);   //PWM speed control
    last_command = command;    
    command = '\0'; //reset command
    sprintf(response,"Speed %d , direction : forward", pwm_speed );
    break;
    case 'c': //backward
    Serial.println("Back!!\r\n");     
    analogWrite(OUT1, 0);   
    analogWrite(OUT2, pwm_speed);   //PWM speed control    
    analogWrite(OUT3, pwm_speed);   //PWM speed control
    analogWrite(OUT4, 0);   
    last_command = command;    
    command = '\0'; //reset command
    sprintf(response,"Speed %d , direction : backward ", pwm_speed );
    break;   
    case 's': //left
    Serial.println("Left!!\r\n");         
    analogWrite(OUT1, pwm_speed);   
    analogWrite(OUT2, 0);   //PWM speed control    
    analogWrite(OUT3, pwm_speed);   //PWM speed control
    analogWrite(OUT4, 0);          
    last_command = command;    
    command = '\0'; //reset command
    sprintf(response,"Speed %d , direction : left ", pwm_speed );
    break;    
    case 'f': //right
    Serial.println("Right!!\r\n"); 
    analogWrite(OUT1, 0);   
    analogWrite(OUT2, pwm_speed);   //PWM speed control    
    analogWrite(OUT3, 0);   //PWM speed control
    analogWrite(OUT4, pwm_speed);       
    last_command = command;    
    command = '\0'; //reset command
    sprintf(response,"Speed %d , direction : right ", pwm_speed );
    break;           
    case 'd': //stop
    Serial.println("Stop!\r\n");
    
    analogWrite(OUT1, 0);   
    analogWrite(OUT2, 0);   
    analogWrite(OUT3, 0);   
    analogWrite(OUT4, 0);  
    last_command = command;    
    command = '\0'; //reset command
    sprintf(response,"Speed %d , direction : Stopped ", pwm_speed );
    break;    
    case 'j': //reduce speed
    if (pwm_speed >= 5)
    {
      pwm_speed = pwm_speed - 5;      
      command = last_command;
    }
    else
    {
      command = '\0'; //reset command    
    }
    sprintf(response,"Speed %d , direction : None ", pwm_speed );
    break;     
    case 'k': //increase speed
    if (pwm_speed <=250 )
    {
      pwm_speed = pwm_speed + 5;
      command = last_command;
    }
    else
    {
      command = '\0'; //reset command              
    }
    sprintf(response,"Speed %d , direction : none", pwm_speed );  
    break;         
    case '\0':
    //do nothing
    break;    
    default:
    Serial.println("cannot identify command");
    sprintf(response,"cannot identify command", pwm_speed );  
    command = '\0'; //reset command
    break; 
  }
      radio.stopListening();                                        // First, stop listening so we can talk   
      // Send the final one back.
  radio.write(response,strlen(response)) ;     
      radio.startListening(); 

    }
     }
}






