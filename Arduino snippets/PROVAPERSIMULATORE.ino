	int sensorPin = 0;    // select the input pin for the potentiometer  
// Saved by Simulator for Arduino V0.97B
	int ledPin = 13;		// select the pin for the LED
	int ledPin1 = 12;		// select the pin for the LED  
	int sensorValue = 0;  // variable to store the value coming from the sensor  
	
	
	void setup() {  
		// declare the ledPin as an OUTPUT: 
			pinMode(ledPin, OUTPUT); 
			pinMode(ledPin1, OUTPUT);
		 	Serial.begin(9600);
	}  
 
	void loop() {  
		// read the value from the sensor:  
		sensorValue = analogRead(sensorPin);
		//Value = analogRead(sensorPin);
		Serial.println(sensorValue);
		//float voltage = (float)sensorValue*(5,0 / 1023,0);
		float voltage = sensorValue * (5.0 / 1023.0);
		// print out the value you read
		Serial.println(voltage);
		// turn the ledPin on 
		digitalWrite(ledPin, HIGH);
		digitalWrite(ledPin1, HIGH);
		// stop the program for <sensorValue> milliseconds:  
		delay(sensorValue);          
		// turn the ledPin off:          
		digitalWrite(ledPin, LOW);
		digitalWrite(ledPin1, LOW);
		// stop the program for for <sensorValue> milliseconds: / 
		delay(sensorValue);  
	 
	} 
