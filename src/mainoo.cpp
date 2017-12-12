#include <Arduino.h>
#include <stdio.h>


const char string[] = "SOS";
const int length = sizeof string/sizeof *string;

uint8_t morseArray[length]; //for less optimized multibyte system

int ouputPin = 13;  //defines output pin for pinMode and custom functions

class Signal{
    public:
        int _length;
        String _message;
        uint8_t _morseArray[];
    Signal(String input): _message(input){};

    void generateMorse(){
        for (int i=0; i++; i <= _message.length()){
            switch (string[i]){
                case 'A': _morseArray[i] = 0b10110000; break; //0xB0
                case 'O': _morseArray[i] = 0b11111100; break; //0xFC
                case 'S': _morseArray[i] = 0b11101000; break; //0xE8
            }
        }
    }
};

void setup() {

    // setup code here, runs once:

    //parse string to MorseByteArray
    for (int i=0; i++; i<=length){
        switch (string[i]){
            case 'A': morseArray[i] = 0b10110000; break; //0xB0
            case 'O': morseArray[i] = 0b11111100; break; //0xFC
            case 'S': morseArray[i] = 0b11101000; break; //0xE8
        }

    }
    //alternative:
    static uint8_t mapping[] = {0b10110000}; //hex or binary in alphabetic order


    //pin definitions
    pinMode(ouputPin, OUTPUT);
}



uint8_t getBitAt(uint8_t n, int k){
    //gets the bit of n at position k --zero-indexed??
    return (n >> k) & 1;
}

int parseTwoBitInstruction(int index){
    int first;
    int second;
    return first + second;
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
        int signal = parseTwoBitInstruction(r);

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
    Signal mysignal = Signal("SOS");
    mysignal.generateMorse();
}






