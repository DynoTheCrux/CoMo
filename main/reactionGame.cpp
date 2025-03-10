#include "reactionGame.h"
#include "definitions.h"
//#include "show.h"

int rndNumVib = 0;
int rndNumLed = 0;
int idx = 0;
int indexOld = 0;
int vibration = 0;
int cntWrong = 0;
int threshold;
int uniqueNumbers[] = {0, 1, 2, 3, 4};
int arraySize = 20;
int randomNumbers[20];
bool correctButton;
unsigned long timer, starttimer, stoptimer;

void action1() {
  // initialization
  correctButton = false;
  prestate1 = false;
  prestate2 = false;
  prestate3 = false;
  prestate4 = false;
  prestateThumb = false;

  generateRandomNumbers(randomNumbers, arraySize);

  delay(200); //vibration does not start early

  //game ends after 20 buttons are pushed
  for (int i = 0; i < 20; i++) {
    // start timer after 1st pushed button
    // if (i == 1) {
    //   starttimer = millis();
    // }
    generateActivation(randomNumbers[i]);
    checkUserInput(); 
    delay(100);  
  }
  ledOff();
  gameFinished = true;
}

/**
 * generates 20 random numbers between 0 and 4, ensuring each number is repeated 4 times
*/
void generateRandomNumbers(int outputArray[], int size) {
    // Seed the random number generator
    randomSeed(millis());

    // Create an array with 5 unique numbers (0 to 4)
    int uniqueNumbers[] = {0, 1, 2, 3, 4};

    // Populate the output array by repeating each unique number 4 times
    int currentIndex = 0;
    for (int i = 0; i < size; ++i) {
        outputArray[i] = uniqueNumbers[currentIndex];
        if ((i + 1) % 4 == 0) {
            currentIndex = (currentIndex + 1) % 5;
        }
    }

    // Shuffle the array using Fisher-Yates algorithm
    for (int i = size - 1; i > 0; --i) {
        int j = random(0, i + 1);
        int temp = outputArray[i];
        outputArray[i] = outputArray[j];
        outputArray[j] = temp;
    }
}

/**
 * generates a random vibration
 * generates a random number and compares it to the last one to not select the same pin again
 * sets the according pin to SPEED to activate the vibration motor
*/
void generateActivation(int random) {
  rndNumVib = vibrations[random];  //generates a random vibration
  rndNumLed = ledArray[random];    //generates a random led

  delay(1500);
  starttimer = millis();
  switch (mode) {
    case vib:
      threshold = THRESHOLD_VIB;
      Serial.print("vib, ");
      analogWrite(rndNumVib, SPEED);
      break;
    case led:
      threshold = THRESHOLD;
      Serial.print("led, ");
      ledOn(rndNumLed);
      break;
    case both:
      threshold = THRESHOLD_VIB;
      Serial.print("both, ");
      analogWrite(rndNumVib, SPEED);
      ledOn(rndNumLed);
      break;
  }
  Serial.print("active, ");
  Serial.print((rndNumLed == 5) ? 0 : rndNumLed);
}

/**
 * checks the pushed buttons of the user and compares them to the randomized vibration
 * leaves while loop if vibration and button of the same finger are set to high
*/
void checkUserInput() {
  bool state = false;
  correctButton = false;
  prestate1 = false;
  prestate2 = false;
  prestate3 = false;
  prestate4 = false;
  prestateThumb = false;

  while (!state) { 
  check:
    if (rndNumVib == vibration1) { 
      if(getFinger1() >= threshold) {
        analogWrite(vibration1, 0);   //turns off vibration motor
        ledOff();
        stoptimer = millis();
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }
      // checks if another button is pushed and increments cntWrong 
      else if ((getFinger2() >= threshold) && !prestate2 && !correctButton){
        Serial.print(", pressed, 2");
        cntWrong ++;
        prestate2 = true;
      }
      else if ((getFinger3() >= threshold) && !prestate3 && !correctButton){
        Serial.print(", pressed, 3");
        cntWrong ++;
        prestate3 = true;
      }
      else if ((getFinger4() >= threshold) && !prestate4 && !correctButton){
        Serial.print(", pressed, 4");
        cntWrong ++;
        prestate4 = true;
      }
      else if ((getThumb() >= threshold) && !prestateThumb && !correctButton){
        Serial.print(", pressed, 0");
        cntWrong ++;
        prestateThumb = true;
      } 
    }

    else if (rndNumVib == vibration2) { //analogRead(vibration2) == SPEED
      if (getFinger2() >= threshold) {  
        analogWrite(vibration2, 0);   //turns off vibration motor
        ledOff();
        stoptimer = millis();
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((getFinger1() >= threshold) && !prestate1 && !correctButton){
        Serial.print(", pressed, 1");
        cntWrong ++;
        prestate1 = true;
      }
      else if ((getFinger3() >= threshold) && !prestate3 && !correctButton){
        Serial.print(", pressed, 3");
        cntWrong ++;
        prestate3 = true;
      }
      else if ((getFinger4() >= threshold) && !prestate4 && !correctButton){
        Serial.print(", pressed, 4");
        cntWrong ++;
        prestate4 = true;
      }
      else if ((getThumb() >= threshold) && !prestateThumb && !correctButton){
        Serial.print(", pressed, 0");
        cntWrong ++;
        prestateThumb = true;
      }   
    }
    
    else if (rndNumVib == vibration3) {  //analogRead(vibration3) == SPEED
      if (getFinger3() >= threshold) {
        ledOff();   
        analogWrite(vibration3, 0);   //turns off vibration motor
        stoptimer = millis();
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((getFinger1() >= threshold) && !prestate1 && !correctButton){
        Serial.print(", pressed, 1");
        cntWrong ++;
        prestate1 = true;
      }
      else if ((getFinger2() >= threshold) && !prestate2 && !correctButton){
        Serial.print(", pressed, 2");
        cntWrong ++;
        prestate2 = true;
      }
      else if ((getFinger4() >= threshold) && !prestate4 && !correctButton){
        Serial.print(", pressed, 4");
        cntWrong ++;
        prestate4 = true;
      } 
      else if ((getThumb() >= threshold) && !prestateThumb && !correctButton){
        Serial.print(", pressed, 0");
        cntWrong ++;
        prestateThumb = true;
      }  
    }
    
    else if (rndNumVib == vibration4) { //analogRead(vibration4) == SPEED
      if (getFinger4() >= threshold) {
        ledOff();   
        analogWrite(vibration4, 0);   //turns off vibration motor
        stoptimer = millis();
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((getFinger1() >= threshold) && !prestate1 && !correctButton){
        Serial.print(", pressed, 1");
        cntWrong ++;
        prestate1 = true;
      }
      else if ((getFinger2() >= threshold) && !prestate2 && !correctButton){
        Serial.print(", pressed, 2");
        cntWrong ++;
        prestate2 = true;
      }
      else if ((getFinger3() >= threshold) && !prestate3 && !correctButton){
        Serial.print(", pressed, 3");
        cntWrong ++;
        prestate3 = true;
      }  
      else if ((getThumb() >= threshold) && !prestateThumb && !correctButton){
        Serial.print(", pressed, 0");
        cntWrong ++;
        prestateThumb = true;
      }  
    }
    else if (rndNumVib == vibrationThumb) { // analogRead(vibrationThumb) == SPEED
      if (getThumb() >= threshold) {
        ledOff();   
        analogWrite(vibrationThumb, 0);   //turns off vibration motor
        stoptimer = millis();
        correctButton = true;         //sets variable to remeber the right button had been pushed
      }    
      // checks if another button is pushed and increments cntWrong 
      else if ((getFinger1() >= threshold) && !prestate1 && !correctButton){
        Serial.print(", pressed, 1");
        cntWrong ++;
        prestate1 = true;
        delay(100);
      }
      else if ((getFinger2() >= threshold) && !prestate2 && !correctButton){
        Serial.print(", pressed, 2");
        cntWrong ++;
        prestate2 = true;
      }
      else if ((getFinger3() >= threshold) && !prestate3 && !correctButton){
        Serial.print(", pressed, 3");
        cntWrong ++;
        prestate3 = true;
      }  
      else if ((getFinger4() >= threshold) && !prestate4 && !correctButton){
        Serial.print(", pressed, 4");
        cntWrong ++;
        prestate4 = true;
      } 
    }
    
    if ((getFinger1() < ZERO) && (getFinger2() < ZERO) && (getFinger3() < ZERO) && (getFinger4() < ZERO) && (getThumb() < ZERO)) {
      prestate1 = false;
      prestate2 = false;
      prestate3 = false;
      prestate4 = false;
      prestateThumb = false;

      // only leave while loop if correct button has been pushed and is released again to avoid wrong counting in next iteration
      if(correctButton) {
        Serial.print(", ");
        Serial.println(stoptimer - starttimer);
        //Serial.println();
        state = true;
      }
    }
  }        
}

