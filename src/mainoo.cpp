#include <Arduino.h>
#include <stdio.h>


const char string[] = "SOS";
const int length = sizeof string/sizeof *string;

uint8_t morseArray[length]; //for less optimized multibyte system

int ouputPin = 13;  //defines output pin for pinMode and custom functions

class Morser{
    public:
        String _message;
        uint8_t _morseArray[];
    Morser(String input): _message(input){};

    void generateMorse(){
        for (int i=0; i++; i <= _message.length()){
            switch (string[i]){
                case 'A': _morseArray[i] = 0b10110000; break; //0xB0
                case 'O': _morseArray[i] = 0b11111100; break; //0xFC
                case 'S': _morseArray[i] = 0b11101000; break; //0xE8
            }
        }
    }
    void sendSignal(){
        //sends the entire signal
        for(int r=0; r++; r< _message.length()){
            //iterate through letters
            for (int i=0; i++; i<4){
                //iterate through bitPairs
                int signalValue = parseBitPairInstruction(r, i);
                switch(signalValue){
                    case 0: signalfunctions::shortPause();break;
                    case 1: signalfunctions::shortSignal();break;
                    case 2: signalfunctions::longSignal();break;
                }
            }
        }
    }
    int parseBitPairInstruction(int morseIndex, int twoBitIndex){
        //morseIndex is the position of our current signal in the morseArray
        int first = utilities::getBitAt(_morseArray[morseIndex], twoBitIndex+0);
        int second = utilities::getBitAt(_morseArray[morseIndex], twoBitIndex+1);
        return first + second;
    }
};

void setup() {
    // setup code here, runs once:
    //pin definitions
    pinMode(ouputPin, OUTPUT);
}
namespace utilities{
    //organises utility functions in their own namespace

    uint8_t getBitAt(uint8_t n, int k){
        //gets the bit of byte n at position k --zero-indexed??
        return (n >> k) & 1;
    }
}

namespace signalfunctions{
    //organises led signal related functions in their own namespace

    void shortPause(){
        delay(500);
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
}

void loop() {
    // main code here, runs repeatedly:
    Morser morses = Morser("SOS");
    morses.generateMorse();
    morses.sendSignal();
}






