//Lab 1_Capacitive Sensing

//This project is a simple interactive sound and light system 
//using three capacitive touch sensors connected to an ESP32.
//Single Touch: Each sensor produces a distinct sound.
//Right Swipe: Detects a right swipe; plays a rising melody; turns the LED ON.
//Left Swipe: Detects a left swipe; plays a falling melody; turns the LED OFF.


//Capacitive touch sensor pins
const int TOUCH_PIN1 = 32;
const int TOUCH_PIN2 = 33;
const int TOUCH_PIN3 = 12;

//LED pin
const int LED_PIN = 27;

//Buzzer pin
const int BUZZER_PIN = 25;

//Touch thresholds
const int threshold1 = 925;  
const int threshold2 = 830;  
const int threshold3 = 800;  

void playTone(int freq, int duration) {
  //Set the pitch
  analogWriteFrequency(BUZZER_PIN, freq); 
  analogWrite(BUZZER_PIN, 128);            
  delay(duration);
  analogWrite(BUZZER_PIN, 0); //Turn the buzzer off
}

//Set to play multiple notes in sequence
void playMelody(const int notes[], int numNotes, int noteDuration) {
  //Start at 0 and continue untill all notes have been played
  for (int i = 0; i < numNotes; i++) {
    playTone(notes[i], noteDuration);
  }
}

//When touching each sensor
const int TOUCH1_TONE = 800;   
const int TOUCH2_TONE = 1200;   
const int TOUCH3_TONE = 2000; 
const int TOUCH_TONE_DURATION = 80; //ms

//Set the melodies when swiping right and left
const int RIGHT_MELODY[] = {262, 330, 392, 523};   //rising
const int LEFT_MELODY[]  = {523, 392, 330, 262};   //falling
const int MELODY_NOTE_DURATION = 120;  //ms per note

//Swipe time window set up
const unsigned long swipeTimeout = 150;

//Swipe states
int swipeState = 0;
unsigned long swipeStartTime = 0;

//Previous sensor states
bool isSensorTouched1 = false;
bool isSensorTouched2 = false;
bool isSensorTouched3 = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Start");
  Serial.println("RIGHT SWIPE -> LED ON");
  Serial.println("LEFT SWIPE -> LED OFF");
  Serial.println("Single touch");
}


void loop() {
  //Read the sensor values
  int sensedValue1 = touchRead(TOUCH_PIN1);
  int sensedValue2 = touchRead(TOUCH_PIN2);
  int sensedValue3 = touchRead(TOUCH_PIN3);

  //Check if sensors are touched
  bool touched1 = sensedValue1 < threshold1;
  bool touched2 = sensedValue2 < threshold2;
  bool touched3 = sensedValue3 < threshold3;

  //Check if sensor1/2/3 touched now and was them touched before
  bool newTouch1 = touched1 && !isSensorTouched1;
  bool newTouch2 = touched2 && !isSensorTouched2;
  bool newTouch3 = touched3 && !isSensorTouched3;

  if (newTouch1) playTone(TOUCH1_TONE, TOUCH_TONE_DURATION);
  if (newTouch2) playTone(TOUCH2_TONE, TOUCH_TONE_DURATION);
  if (newTouch3) playTone(TOUCH3_TONE, TOUCH_TONE_DURATION);

  //Swipe detection
  if (swipeState == 0) {

    if (newTouch1) {
      swipeState = 1;
      swipeStartTime = millis();
      Serial.println("Sensor 1 touched.");
    }

    else if (newTouch3) {
      swipeState = 3;
      swipeStartTime = millis();
      Serial.println("Sensor 3 touched.");
    }
  }

  //Right swipe: 1-2-3
  else if (swipeState == 1) {
    if (newTouch2 && millis() - swipeStartTime <= swipeTimeout) {
      swipeState = 2;
      swipeStartTime = millis();
      Serial.println("1 - 2");
    }
    else if (millis() - swipeStartTime > swipeTimeout) {
      //Serial.println("Sensor 1 was simple touched.");
      swipeState = 0;
    }
  }

  else if (swipeState == 2) {
    if (newTouch3 && millis() - swipeStartTime <= swipeTimeout) {
      Serial.println("1 - 2 - 3");
      Serial.println("Right swipe ->");

      digitalWrite(LED_PIN, HIGH);
      playMelody(RIGHT_MELODY, 4, MELODY_NOTE_DURATION);
      Serial.println("LED ON");

      swipeState = 0;
    }
    else if (millis() - swipeStartTime > swipeTimeout) {
      //Serial.println("Right swipe failed.");
      swipeState = 0;
    }
  }

  //Left swipe: 3-2-1
  else if (swipeState == 3) {
    if (newTouch2 && millis() - swipeStartTime <= swipeTimeout) {
      swipeState = 4;
      swipeStartTime = millis();
      Serial.println("3 - 2");
    }
    else if (millis() - swipeStartTime > swipeTimeout) {
      //Serial.println("Sensor 3 was simple touched.");
      swipeState = 0;
    }
  }

  else if (swipeState == 4) {
    if (newTouch1 && millis() - swipeStartTime <= swipeTimeout) {
      Serial.println("3 - 2 - 1");
      Serial.println("Left swipe <-");

      digitalWrite(LED_PIN, LOW);
      playMelody(LEFT_MELODY, 4, MELODY_NOTE_DURATION);
      Serial.println("LED OFF");

      swipeState = 0;
    }
    else if (millis() - swipeStartTime > swipeTimeout) {
      //Serial.println("Left swipe failed.");
      swipeState = 0;
    }
  }

  //Save sensor states
  isSensorTouched1 = touched1;
  isSensorTouched2 = touched2;
  isSensorTouched3 = touched3;

  delay(5);
}
