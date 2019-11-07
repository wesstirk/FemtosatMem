#ifndef FEMTOSAT_MEM
#define FEMTOSAT_MEM

#include <Arduino.h>
#include <Wire.h>

#define MEM_MODULE_I2C_ADDRESS 0xf0

#define MESSAGE_MAX_LENGTH 256

class FemtosatMem
{
  public:
  /*
   * Constructor for the memory module.
   * Doesn't do anything other than assign initial values. 
   */
    FemtosatMem(uint16_t i2cAddress=MEM_MODULE_I2C_ADDRESS)
    {
      this->I2C_ADDRESS = i2cAddress;
    }

    /*
     * Starts all operations needed to communicate with the memory module. 
     */
    bool begin(char* fileName, uint8_t fileNameSize);

    /*
     * Tests the basic functionality of the memory module. 
     * Not yet implemented.
     */
    bool Test();

    /*
     * Returns a boolean indicating whether the memory module is ready to receive more data. 
     */
    bool Ready();

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
    bool Save(void* buffer, size_t bufferSize, bool errorChecking=false, int waitTime=200);


    /*
     * It will change the file that is getting written to. 
     * 
     * fileNameSize is the number of characters to be transmitted.
     * 
     * This is communicated to the memory module, 
     *  so it has the same error checking constraints as the Save function had
     */
     bool SetFile(char* fileName, size_t fileNameSize, bool errorChecking=false, int waitTime=200);
    


  private:

    /*
     * Does the waiting and continuosly checks if the memory module is ready to receive more input.
     */
    bool ErrorCheckingWait(int waitTime);

    uint8_t I2C_ADDRESS;
  
};


#endif
