  //mic sensor
const int threshold = 200;


//photosensor lamp
int relayPin = 8;
int brightness = 0;

int sensorLow = 0;
int sensorHigh = 15;
int incomingByte = 0;


//****CHECK PIN NUMBERS***
//themo sensor
//TMP36 Pin Variables
int sensorPin = 6; //the analog pin the TMP36's Vout (sense) pin is connected to
//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures



//hairdryer
int ledPin = 7;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(19200);
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, OUTPUT);

  Serial.println("Arduino is ready!");
}

// the loop routine runs over and over again;
void loop() {

  //mic sensor ints for loop
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  //end mic sensor for loop



  //thermo
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(sensorPin);
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100;
  //converting from 10 mv per degree wit 500 mV offset to degrees ((voltage - 500mV) times 100)
  //end thermo sensor for loop

  int  sample = analogRead(A2);
  int sensorValue = analogRead(A1);

  //Serial.println(sensorValue);


  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  }


  if (incomingByte != 49 && sample > threshold) {
    Serial.println(sample);
    Serial.println(sensorValue);
    digitalWrite(relayPin, HIGH);
    //adding more sensors
    if (sensorValue > 120) {
      digitalWrite(ledPin, HIGH);
      Serial.print("temp: ");
      Serial.println(temperatureC);
      if (temperatureC >= 17) {
        digitalWrite(sensorPin, HIGH);
      }
    }
  }

  else if (incomingByte == 49) {
    // turn off from twitter
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(sensorPin, LOW);
  }

  Serial.print("I received: ");
  Serial.println(incomingByte, DEC);



  delay(500);

}
