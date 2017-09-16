#include <Arduino.h>

 //Declaring analog input pins
const int temperature_level_pin = A1;
const int vibration_level_pin = A2;
const int fluid_level_pin = A3;

//Digital Pins
const int temperature_output_pin = 3;
const int level_output_pin = 5;
const int vibration_exceeded_maximum = 4;

const int S0 = 6;
const int S1 = 7;
const int S2 = 8;

int level_array[3];       //Initialises empty arrays
int temperature_array[3]; //for storing sensor values
int vibration_array[3];

int *array_ptr; // array pointer
int (*ptr_function)(int); //initialise a function pointer

int temperature, vibration_amplitude, fluid_level;

String datastring;

int populate_array(int (*function_pointer)(int), int input_pin, int *sensor_array){
    int i;

    for(i=0;i<3;i++){
        *(sensor_array + i) = function_pointer(input_pin);
        }
    return 0;

}

int fluid_level_calculation(int fluid_pin_in) {

    int i = 0;

    //1
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
	
    //2
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
    //3
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
    //4
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
    //5
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
    //6
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
    //7
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}
    //8
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    if(analogRead(fluid_pin_in > 100){
		i++;
	}

    return (8 -i);
}

int temperature_difference_calculation(int temperature_pin_in) {

    int raw_reading; //Local variable for storing analog read value

    raw_reading = analogRead(temperature_pin_in); //Read analog value
                                                  //from pin specified in function argument

    return (raw_reading/10);  //Return analog read value
                              //divided by 10 to compensate for
                              //system gain and V/degC
}

int vibration_amplitude_calculation(int vibration_pin_in) {

    int raw_reading; //Local variable for storing analog read value

    raw_reading = analogRead(vibration_pin_in); //Read analog value
                                                //from pin specified in function argument
    return (raw_reading / 1000); //Return measured value divided
                                 //by 1000 since 1V/g
}

int averaging(int *array_name) {

    int i,j; //Set local variables

    for(i=0;i<3;i++){      //For loop to total the values
        j = j + *(array_name + i); //stored in the array
    }

    return (j /3); //Return the average
}

void temperature_difference_output(int temperature, int temperature_output_pin){
    int signal_to_BG_driver;

    signal_to_BG_driver = (temperature * 37); // Maximum output when fluid level is 7; 7*37=259 accounting for integer rounding errors

    analogWrite(temperature_output_pin, signal_to_BG_driver);
}

void vibration_visual_alert(int vibration_exceeded_maximum, int vibration_amplitude){
        if(vibration_amplitude > 2){
            digitalWrite(vibration_exceeded_maximum, HIGH);
            }
        else{
            digitalWrite(vibration_exceeded_maximum, LOW);
        }
}
void fluid_level_alert(int fluid_level, int level_output_pin){
	if(fluid_level < 4){
		digitalWrite(level_output_pin, HIGH);
	} else{
		digitalWrite(level_output_pin, LOW);
	}
}


void setup() {

    int i;

    for(i = 0;i < 7;i++){
        pinMode(i, OUTPUT);
    }

    Serial.begin(9600);

}

void loop() {

    array_ptr = &vibration_array[0]; //pointer to start of level array
    ptr_function = &vibration_amplitude_calculation; //function pointer to the calculation function

    populate_array(int (*ptr_function)(int), vibration_level_pin, array_ptr);

    vibration_amplitude = averaging(array_ptr);

    array_ptr = &temperature_array[0];
    ptr_function = &temperature_difference_calculation;

    populate_array(ptr_function, temperature_level_pin, array_ptr);

    temperature = averaging(array_ptr);


    fluid_level = fluid_level_calculation(fluid_level_pin);

    fluid_level_output(fluid_level, level_output_pin);
    vibration_visual_alert(vibration_exceeded_maximum, vibration_amplitude);

    datastring = "";

    datastring = String(temperature) + " " +String(vibration_amplitude) + " " + String(fluid_level);
    Serial.println(datastring);
}





