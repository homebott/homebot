#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>
using namespace std;
//
// Hardware configuration
//

// CE Pin, CSN Pin, SPI Speed

// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 1Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_26, BCM2835_SPI_SPEED_1MHZ);

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);


// Radio pipe addresses for the 2 nodes to communicate.
const uint8_t pipes[][6] = {"1Node","2Node"};
//const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };


int main(int argc, char** argv){



  radio.begin();
radio.enableDynamicPayloads();
 radio.setAutoAck(1);
  radio.setRetries(15,15);
  radio.printDetails();



  string input = "";
  char command[30] = "";
  char myChar = {0};


      	radio.openWritingPipe(pipes[0]);
      	radio.openReadingPipe(1,pipes[1]);
	
	radio.stopListening();
	while (1)
	{
			cout<<"Enter your choice :";
			cin>>command;
			cin.ignore();
			if(parsecommand(command)){
			if (!radio.write( &myChar, sizeof(char) )){
				printf("failed.\n");
			}
			else {
			cout<<"Success\n";
			} 
			else
			cout<<"Bad Command";
			}
			// Describe the results

	} // forever loop

  return 0;
}
int parsecommand(char *cmd){
	int len = strlen(cmd)
	if(len > 4 || len < 3 )
	return 0;
	for(i = 0 ; cmd[i] != '\0';i++){
	if(i==0){
	if (cmd[i]=='f'||cmd[i]=='b'||cmd[i]=='r'||cmd[i]=='l'||cmd[i]=='s'||cmd[i]=='f')
	}
	if(i==1)
	if(i>1)

