#include <EEPROM.h>

byte samplesPerRead  = 1;    // number of samples per read
long refResistance    = 1e+5; // resistance at 25 degrees C -- can be unsigned
long seriesResistance = 1e+5; // resistance in series w/ the thermistor

void setup(){
    // Step 1: load configuration from EEPROM
    //load_config();
    // Step 2: setup serial communication
    Serial.begin(9600); // Seems like on the 8MHz this is actually 4800 baud
    Serial.println("Ready!");
}


// Appearantly readUntil doesn't have the 64 character limitation
String inputData;
void loop(){
    // Enter command mode and listen to commands.
    // Depending on the command, execute the instructions given
    if (Serial.available() > 0){
        inputData = Serial.readStringUntil('\n');

        // if (inputData.equalsIgnoreCase("Hello")){
        //     Serial.println(refResistance);
        // }
    }
    Serial.flush();
}


// Loads the configuration variables from EEPROM. These are:
// samples per read - address 0         (1 byte)
// resistance at 25 C - address 1-5     (4 bytes)
void load_config(){
    EEPROM.get(0, samplesPerRead); // read from address 0
    EEPROM.get(1, refResistance);  // read from address 1
}


// Saves current global values to EEPROM
// Since the EEPROM has about 100 000 write/erase cycles
// updating writes to the EEPROM only if the value has
// changed, therefor not using erase cycles when unnecessary
// put() can put any data type into memory.
void save_config(){
    EEPROM.put(0, samplesPerRead); // samples at address 0
    EEPROM.put(1, refResistance);  // R25 at address 1-5 (4 bytes)
}