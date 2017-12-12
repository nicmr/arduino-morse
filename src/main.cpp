#include <Arduino.h>
#include <stdio.h>

int ouputPin = 13;  //defines output pin for pinMode and custom functions

class Morser{
    public:
        String _message;
        uint8_t _morseArray[];
    Morser(String input): _message(input){};

    void generateMorse(){
        for (int i=0; i++; i <= _message.length()){
            switch (_message[i]){
                case 'A': _morseArray[i] = 0b10110000; break; //0xB0
                case 'B': _morseArray[i] = 0b11101010; break; //0xB0
                case 'C': _morseArray[i] = 0b11101110; break; //0xB0
                case 'D': _morseArray[i] = 0b11101000; break; //0xB0
                case 'E': _morseArray[i] = 0b10000000; break; //0xB0
                case 'F': _morseArray[i] = 0b10101110; break; //0xB0
                case 'G': _morseArray[i] = 0b11111000; break; //0xB0
                case 'H': _morseArray[i] = 0b10101010; break; //0xB0
                case 'I': _morseArray[i] = 0b10100000; break; //0xB0
                case 'J': _morseArray[i] = 0b10111111; break; //0xB0
                case 'K': _morseArray[i] = 0b11101100; break; //0xB0
                case 'L': _morseArray[i] = 0b10111010; break; //0xB0
                case 'M': _morseArray[i] = 0b11110000; break; //0xB0
                case 'N': _morseArray[i] = 0b11100000; break; //0xB0
                case 'O': _morseArray[i] = 0b11111100; break; //0xFC
                case 'P': _morseArray[i] = 0b10111110; break; //0xB0
                case 'Q': _morseArray[i] = 0b11111011; break; //0xB0
                case 'R': _morseArray[i] = 0b10111000; break; //0xB0
                case 'S': _morseArray[i] = 0b10101000; break; //0xE8
                case 'T': _morseArray[i] = 0b11000000; break; //0xB0
                case 'U': _morseArray[i] = 0b10101100; break; //0xB0
                case 'V': _morseArray[i] = 0b10101011; break; //0xB0
                case 'W': _morseArray[i] = 0b10111100; break; //0xB0
                case 'X': _morseArray[i] = 0b11101011; break; //0xB0
                case 'Y': _morseArray[i] = 0b11101111; break; //0xB0
                case 'Z': _morseArray[i] = 0b11111010; break; //0xB0
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
