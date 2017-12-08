#include <Arduino.h>
#include <stdio.h>


const char string[] = "SOS";
const int length = sizeof string/sizeof *string;

uint8_t morseArray[length]; //for less optimized multibyte system
//uint8_t morseInput = 0; //still unused, for optimized single byte system

int ouputPin = 13;  //defines output pin for pinMode and custom functions

void setup() {
    // setup code here, runs once:

    //parse string to MorseByteArray
    for (int i=0; i++; i<=length){
        switch (string[i]){
            case 'A': morseArray[i] = 0xB0; break;
            case 'O': morseArray[i] = 0xFC; break;
            case 'S': morseArray[i] = 0xE8; break;
        }

    }

    //pin definitions
    pinMode(ouputPin, OUTPUT);
}

uint8_t getBitAt(uint8_t n, int k){
    //gets the bit of n at position k --zero-indexed??
    return (n >> k) & 1;
}

void shortSignal(){
    //sends a short signal on the outputPin
    digitalWrite(ouputPin, HIGH);
    delay(500);
    digitalWrite(ouputPin, LOW);
    delay(250);
}

void longSignal(){
    //sends a long signal on the outputPin
    digitalWrite(ouputPin, HIGH);
    delay(1000);
    digitalWrite(ouputPin, LOW);
    delay(250);
}

void convertToSignal(int a){
    //
    for(int r=0; r+=2; r<=6){
        uint8_t first = getBitAt(a, r+1);
        uint8_t second = getBitAt(a, r+2);

        if (first && second){
            longSignal();
        }
        else if (first || second){
            shortSignal();
        }
        else{
            break;
        }
    }

}

void sendMorse(uint8_t arr[length]){
    //passes single bytes of the array to be converted to signals
    for (int i=0; i++; i<=length){
        convertToSignal(arr[i]);
    }
}

void loop() {
    // main code here, runs repeatedly:
    sendMorse(morseArray);
}






