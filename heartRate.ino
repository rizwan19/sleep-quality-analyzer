//--------Use This Sketch To------------------------------------------
//1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
//2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
//3) Learn about using a PulseSensor Library "Object".
//4) Blinks LED on PIN 13 with user's Heartbeat.
//--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.

int val;
int tempPin = 1;
int i=0, j=0,k;
int heartBeats[100];
int ldrValues[100];
int tempValues[100];
int flag=0;
int tempflag=0;
int maxBPM=0;
int sumBeat = 0;
int beatCount = 0;
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   


  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {
  int buttonValue = analogRead(A4);
  if(buttonValue==1023){
    if(flag==1)
    {
      tempflag=0;
    }
    else{
      tempflag=1;
    }
  }
  if(tempflag == 1)
  {
    flag=1;
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
  val = analogRead(tempPin);
  float mv = (val/1024.0)*5000;
  float cel = mv/10;

  int soundValue=analogRead(A3);
  int sensorValue = analogRead(A2);

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.print("Heart Rate: "); // If test is "true", print a message "a heartbeat happened".
 ;                        // Print phrase "BPM: " 
 Serial.print(myBPM);                        // Print the value inside of myBPM.  pulseSensor.sawStartOfBeat()
 Serial.println(" BPM");
 heartBeats[j] = myBPM;
 ldrValues[j] = sensorValue;
 tempValues[j] = int(cel);
 sumBeat = sumBeat+myBPM;
 beatCount++;
 if(myBPM>maxBPM){
  maxBPM = myBPM;
 }
 j++;
}

  
  
  Serial.print("TEMPERATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  int val = 1000;
  
 int custval = sensorValue*0.9+61.0+cel*2+soundValue*0.1;
  analogWrite(9, custval);
  Serial.print("Light: ");
  Serial.print(sensorValue);
  Serial.println(" lux");
  if(soundValue==0){
    Serial.print("Sound: ");
    Serial.println(0);
    }
  if(soundValue>0){
    Serial.print("Sound: ");
    Serial.println(1);
    }
  for(k=0;k<30;k++){
    Serial.print("-");
  }
  Serial.println("");
  i++;
  }
//  else
//  {
//    if(i==15)
//    {
//      for(k=0;k<j;k++)
//      {
//        Serial.print("Temperature:");
//        Serial.print(tempValues[k]);
//        Serial.print("  ");
//        Serial.print("Light:");
//        Serial.print(ldrValues[k]);
//        Serial.print("Lux  ");
//        Serial.print("Heartbeats: ");
//        Serial.print(heartBeats[k]);
//        Serial.println("BPM  ");
//      }
//      i++;
//    }
//  }
  else{
    if(flag==1)
    {
      for(k=0;k<j;k++)
      {
        Serial.print("Temperature:");
        Serial.print(tempValues[k]);
        Serial.print("  ");
        Serial.print("Light:");
        Serial.print(ldrValues[k]);
        Serial.print("Lux  ");
        Serial.print("Heartbeats: ");
        Serial.print(heartBeats[k]);
        Serial.println("BPM  ");
      }
      flag=0;
      int averageBeat = sumBeat/beatCount;
      Serial.print("Max Heart Beat: ");
        Serial.println(maxBPM);
        Serial.print("Average Heart Rate: ");
        Serial.print(averageBeat);
        Serial.println(" BPM");
        if(averageBeat>100)
        {
          Serial.println("The quality of sleep was not good!");
        }
        else if(averageBeat
        >80)
        {
          Serial.println("The quality of sleep was good!");
        }
        else
        {
          Serial.println("The quality of sleep was profound!");
        }
    }
  }
  delay(1000);
}
