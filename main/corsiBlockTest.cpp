#include "corsiBlockTest.h"
#include "definitions.h"


CorsiBlockTest::CorsiBlockTest(int maxSequenceLength, bool withVibration) {
  this->maxSequenceLength = maxSequenceLength;
  this->sequenceLength = 2;  // Start with 2 blocks
  this->sequence = new int[maxSequenceLength];
  this->userInputIndex = 0;
  this->vibration = withVibration;
  if (vibration) {
    threshold = THRESHOLD_VIB;
  } else {
    threshold = THRESHOLD;
  }
  releaseThreshold = threshold - 20; // offset for debouncing
}

void CorsiBlockTest::begin() {
  //randomSeed(analogRead(0));  // Initialize random seed
  // generateSequence();
}

void CorsiBlockTest::generateSequence() {
  // Serial.print("Sequence: ");

  for (int i = 0; i < sequenceLength; i++) {
    sequence[i] = random(0, numBlocks);  // Generate random block indices
    // Serial.print(sequence[i]);
    // Serial.print(" ");
  }
  // Serial.println(";");
}

void CorsiBlockTest::playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    delay(LIGHT_TIME);
    lightUpBlock(sequence[i]);
    if(vibration)
    {
      analogWrite(vibrations[sequence[i]], SPEED);
    }
    delay(LIGHT_TIME);
    vibrationOff();
    ledOff();

  }
  // turn of leds

  
}

void CorsiBlockTest::vibrationOff() {
  analogWrite(vibration1, 0);
  analogWrite(vibration2, 0);
  analogWrite(vibration3, 0);
  analogWrite(vibration4, 0);
  analogWrite(vibrationThumb, 0);
}

void CorsiBlockTest::waitForUserInput() {  // needed?
}


void CorsiBlockTest::resetTest() {
  sequenceLength = 2;
}

void CorsiBlockTest::setSpeed(int speed)
{

  LIGHT_TIME = map(speed, 0, 10, 1500, 500);

}

void CorsiBlockTest::lightUpBlock(int blockIndex) {
  // map to LED

  // analogWrite(blockIndex, SPEED);
  ledOn(ledArray[blockIndex]);
}

int CorsiBlockTest::checkUserInput() {
  // Check user input

  int result = -1;
  bool waitForPress = true;
  ledOff();

  while (waitForPress) {
    if (getFinger1() > threshold) {
      ledOn(1);
      result = 1;
      waitForPress = false;
    } else if (getFinger2() > threshold) {
      ledOn(2);
      result = 2;
      waitForPress = false;

    } else if (getFinger3() > threshold) {
      ledOn(3);
      result = 3;
      waitForPress = false;

    } else if (getFinger4() > threshold) {
      //Serial.println(getFinger4());
      ledOn(4);
      result = 4;
      waitForPress = false;

    } else if (getThumb() > threshold) {
      
      ledOn(ledThumb);
      result = 0; // hardcode for two thumbs...
      waitForPress = false;
    }
  }

  // Serial.println(result);

  // // debounce
  while (getFinger1() > releaseThreshold || getFinger2() > releaseThreshold || getFinger3() > releaseThreshold || getFinger4() > releaseThreshold || getThumb() > releaseThreshold) {
          //Serial.println(getFinger4());

    delay(500);
  }

  return result;
}

void CorsiBlockTest::runCorsiBlockTest() {

  bool oneMoreRound = true;
  bool correct;
  int life = 2;

  begin();


  while (oneMoreRound) {

    // Show sequence
    generateSequence();
    playSequence();

    // get user input 2 times and store result

    int* result = new int[sequenceLength];

    for (int i = 0; i < sequenceLength; i++) {
      result[i] = checkUserInput();
      // Serial.println(result[i]);
    }


    // compare result to shown sequence



    for (int i = 0; i < sequenceLength; i++) {
      if (result[i] != sequence[i]) {
        correct = false;
        break;  // break the loop if one is wrong
      } else {
        correct = true;
      }
    }


    // if right increase lvl, if already max length end game
    // if wrong remove life, if no lifes end game

        Serial.print(sequenceLength);
    Serial.print(",");
    for (int i = 0; i < sequenceLength; i++) {
      
      Serial.print(sequence[i]);
      Serial.print(",");
    }

    for (int i = 0; i < sequenceLength; i++) {

      Serial.print(result[i]);
      Serial.print(",");

    }

    Serial.println("");

    
    

    if (correct) {
      sequenceLength++;
      life = 2;  // reset to 2 for a correct one
    } else {
      life--;
    }

    if (sequenceLength > maxSequenceLength || life < 1) {
      oneMoreRound = false;
      score = sequenceLength-1;
      sequenceLength = 2;
      ledOff();
    }

    // Serial.print("Round Done: ");
    // Serial.print(correct);
    // Serial.print(",");
    // Serial.print(sequenceLength);
    // Serial.print(",");
    // Serial.print(life);
    // Serial.print(",");
    // Serial.print(oneMoreRound);
    // Serial.println(" ");

    

  }
}

int CorsiBlockTest::getScore() {
  return score;
}
