

#include "FemtosatMem.h"

/*
 * Starts all operations needed to communicate with the memory module. 
 */
bool FemtosatMem::begin(char* fileName, uint8_t fileNameSize)
{
  Wire.begin(); //todo: what if this has already been called? Will this cause issues?

  this->SetFile(fileName, fileNameSize, true);
  
  return true;
}

/*
 * Tests the basic functionality of the memory module. 
 */
bool FemtosatMem::Test()
{
  return true;
}

/*
 * Returns a boolean indicating whether the memory module is ready to receive more data. 
 */
bool FemtosatMem::Ready()
{

  Wire.requestFrom(this->I2C_ADDRESS, 1); //request the one needed byte from the memory module. 

  char returnVal = 'f';
  while(Wire.available())
  {
    returnVal = Wire.read();
  }
  if(returnVal == 'y')
  { //yes they are ready.
    return true;
  }
  else if(returnVal == 'n')
  { //no they are not ready.
    return false;
  }
  else
  {
    #ifdef DEBUGGING
    Serial.println("Something is wrong witht the FemtosatMem Library!");
    #endif
    return false;
  }
}

/*
 * Saves the information in the buffer by sending it to the memory module.
 * 
 * bufferSize MUST be in bytes
 * 
 * By default it does not do error checking. 
 *  If the error checking flag is true it will keep trying for waitTime number
 *  of milliseconds before giving up. 
 * If error checking it will return a boolean to indicate whether it was successful. 
 * If not error checking it will always return true.
 */
bool FemtosatMem::Save(void* buffer, size_t bufferSize, bool errorChecking, int waitTime)
{
  if(errorChecking)
    {
      if(!this->ErrorCheckingWait(waitTime))
      {
        return false;
      }
    }

    Wire.beginTransmission(this->I2C_ADDRESS); //start the transmission
    Wire.write('d'); //prepend an f to indicate that this will be a file transmission
    Wire.write((uint8_t*)buffer, bufferSize); //then send the rest of the file name. 
    Wire.endTransmission(); //and don't forget to end the transmission. 
    
    return true;
}


/*
 * It will change the file that is getting written to. 
 * 
 * fileNameSize is the number of characters to be transmitted.
 * 
 * This is communicated to the memory module, 
 *  so it has the same error checking constraints as the Save function had
 */
 bool FemtosatMem::SetFile(char* fileName, size_t fileNameSize, bool errorChecking, int waitTime)
 {
    if(errorChecking)
    {
      if(!this->ErrorCheckingWait(waitTime))
      {
        return false;
      }
    }

    Wire.beginTransmission(this->I2C_ADDRESS); //start the transmission
    Wire.write('f'); //prepend an f to indicate that this will be a file transmission
    Wire.write(fileName, fileNameSize); //then send the rest of the file name. 
    Wire.endTransmission(); //and don't forget to end the transmission. 
    
    
    return true;
 }

 /*
 * Does the waiting and continuosly checks if the memory module is ready to receive more input.
 * Returns true if the memory module is good for communicating
 * False otherwise .
 */
bool FemtosatMem::ErrorCheckingWait(int waitTime, int waitInterval)
{
  int initTime = millis(); //find the initial time from starting.
  while(millis() - initTime <= waitTime) //keep trying to reach the memory module until the time is up. 
  {
    if(this->Ready()) //if the memory module is ready, then stop the loop and return the result. 
    {
      return true;
    }
	delay(waitInterval);
  }
  return false; //if after all of that time it still isn't ready, then return the false flag. 
}
