#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

int outputPin = 159; //Setup output pin 
//Eagleye 530s : blue-159 red-43, ARTIK 530, ARTIK 710 : blue-38 red-28

bool digitalPinMode(int pin, int dir) {
    FILE * fd;
    char fName[128];

    // Exporting the pin to be used
    // (# echo 'pin number' > /sys/class/gpio/export)
    fd = fopen("/sys/class/gpio/export", "w");
    if (fd == NULL) {
        printf("Error: unable to export pin\n");
        return false;
    }
    fprintf(fd, "%d\n", pin);
    fclose(fd);

    // Setting direction of the pin
    // (# echo out > /sys/class/gpio/gpio135/direction)
    sprintf(fName, "/sys/class/gpio/gpio%d/direction", pin);
    fd = fopen(fName, "w");
    if (fd == NULL) {
        printf("Error: can't open pin direction\n");
        return false;
    }
    if (dir == OUTPUT) fprintf(fd, "out\n"); // Using OUTPUT pin
    else fprintf(fd, "in\n");  // Using INPUT pin

    fclose(fd);
    return true;
}


//Turn On/Off pin
// (# echo 1 > /sys/class/gpio/gpio'pin number'/value)
// (# echo 0 > /sys/class/gpio/gpio'pin number'/value)
bool digitalWrite(int pin, int val) {
    FILE * fd;
    char fName[128];

    // Open pin value file
    sprintf(fName, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(fName, "w");
    if(fd == NULL) {
        printf("Error: can't open pin value\n");
        return false;
    }
    if(val == HIGH) fprintf(fd, "1\n");
    else fprintf(fd, "0\n");

    fclose(fd);
    return true;
}


int setup() {
    if (!digitalPinMode(outputPin, OUTPUT)) return -1;
    return 0;
}

int main(void) {
    if (setup() == -1) {exit(1);}

    while(1) {
        digitalWrite(outputPin, HIGH); // Pin HIGH : LED ON
        sleep(1);
        digitalWrite(outputPin, LOW);  // Pin LOW: LED OFF
        sleep(1);
    }

    return 0;
}
