/*
 * Created September 28, 2019 by Wesley Stirk
 * 
 * This will be test code for the FemtosatMem Library.
 * It should verify that the hardware is active and that all functions work. 
 * 
 * Last updated November 6, 2019 by Hunter Hoffman
 * 
 */

#include <Wire.h>

#include "FemtosatMem.h"

FemtosatMem mem;

#define WAIT_TIME 3 //the number of milliseconds to wait before trying the memory module again. 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  Wire.begin(); //start the wire library
  char fileName[] = "lib.txt"; //set the file name. 
  Serial.print(fileName);
  Serial.print(" has length of ");
  Serial.println(sizeof(fileName));
  mem.begin(fileName, sizeof(fileName)); //initialize the memory module
		//It includes setting the file name. 


  char data[] = "my data goes here"; //this is where you would put data into a character array
  mem.Save(data, sizeof(data)); //and save the data to the memory module. 

  int beforeTime = millis();
  int afterTime = 0;
	
	
  // Time to do some timing analysis
  Serial.println("When sending two characters, the wait time is (in milliseconds):");
  for(int i = 0; i < 10; ++i)
  {
	while(!mem.Ready()) //waiting until the memory is ready to receive more. Otherwise it won't register what is sent to it. 
	//This is the manual option.
	{
	  delay(WAIT_TIME); //wait to give the module time to run. 
	}
	afterTime = millis();
	Serial.println(afterTime - beforeTime);
    int num = sprintf(data, "%d\n", i); // get the memory to save. 
    beforeTime = millis();
	mem.Save(data, num);
  }
  
  //library option - less code, but less control 
  
  Serial.println("Repeated but with the library method: ");
  for(int i = 10; i < 20; ++i)
  {
	int num = sprintf(data, "%d\n", i);
	beforeTime = millis();
	mem.Save(data, num, true);
	afterTime = millis();
	Serial.println(afterTime - beforeTime);
  }
     
  

}

void loop() {
	
}
