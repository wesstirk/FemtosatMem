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



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  Wire.begin(); //start the wire library
  char fileName[] = "lib.txt"; //set the file name. 
  Serial.print(fileName);
  Serial.println(sizeof(fileName));
  mem.begin(fileName, sizeof(fileName));


  char data[] = "my data goes here";
  mem.Save(data, sizeof(data));

  for(int i = 0; i < 10; ++i)
  {
    int num = sprintf(data, "%d\n", i);
    mem.Save(data, num);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
