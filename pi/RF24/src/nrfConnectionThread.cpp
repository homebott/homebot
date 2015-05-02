#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>
#include <pthread.h> 

using namespace std;
int write_to_buffer(char *data){
	memcpy(data,writebuffer,30);
	memset(&writebuffer[30],"\0",1);
	write=1;
	return 1;
}
int data_from_read(char *data){
	memcpy(data,readbuffer,30);
	memset(&readbuffer[30],"\0",1);
	read = 1;
	return 1;
}
int data_to_write(char *data){
	if(write == 1){
		memcpy(writebuffer,data,30);
        	memset(&data[30],"\0",1);
		write = 0
	}	

int read_from_buffer(char *data){
	if(read == 1){
		memcpy(readbuffer,data,30);
		memset(&data[30],"\0",1);
		read=0;
	}
}
int 
//
// Hardware configuration
//

// CE Pin, CSN Pin, SPI Speed

// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 1Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_26, BCM2835_SPI_SPEED_1MHZ);

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 8Mhz

// Radio pipe addresses for the 2 nodes to communicate.
//const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

void  *connectionNRF(char *NodeName){

  RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);
  const uint8_t pipes[][6] = {"1Node","2Node"};

  // Setup and configure rf radio
  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);
  // Dump the configuration of the rf unit for debugging
  radio.printDetails();

      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
      radio.startListening();

	
	// forever loop
	while (1){ 

			if ( radio.available() ){
				// Dump the payloads until we've gotten everything
				unsigned long got_time;


				// Fetch the payload, and see if this was the last one.
				radio.read( &got_data,30);
				data_from_read(&got_data); 
				
			}
			if(data_to_write(&send_data)) {

				radio.stopListening();

				radio.write( &send_data,30);

				// Now, resume listening so we catch the next packets.
				radio.startListening();

			}				
		
		}

	} // forever loop
   pthread_exit(NULL);
  return 0;
}
uint8_t readbuffer[31],writebuffer[31];
bool read,write;
int main()
{
	char send_data[31],recv_data[31];
	char i[]="ABCD";
	pthread_t threads;
  	rc = pthread_create(&threads, NULL, 
                         connectionNRF , (void *)i);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
	while(1){
		cin>>send_data;
		write_to_buffer(&send_data);
		read_from_buffer(&recv_data);
		cout<<recv_data;
	}
   	pthread_exit(NULL);
}
