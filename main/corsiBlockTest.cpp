#include "corsiBlockTest.h"
#include "definitions.h"


CorsiBlockTest::CorsiBlockTest(int maxSequenceLength, bool withVibration) {
  this->maxSequenceLength = maxSequenceLength;
  this->sequenceLength = 2;  // Start with 2 blocks
  this->sequence = new int[maxSequenceLength];
  this->userInputIndex = 0;
  if (withVibration) {
    threshold = THRESHOLD_VIB;
  } else {
    threshold = THRESHOLD;
  }
}

void CorsiBlockTest::begin() {
  //randomSeed(analogRead(0));  // Initialize random seed
  // generateSequence();
}

void CorsiBlockTest::generateSequence() {
  Serial.print("Sequence: ");

  for (int i = 0; i < sequenceLength; i++) {
    sequence[i] = random(0, numBlocks);  // Generate random block indices
    Serial.print(sequence[i]);
    Serial.print(" ");
  }
  Serial.println(";");
}

void CorsiBlockTest::playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    lightUpBlock(sequence[i]);
    delay(LIGHT_TIME);
  }
  // turn of leds

  ledOff();
}

void CorsiBlockTest::waitForUserInput() {  // needed?
}


void CorsiBlockTest::resetTest() {
  sequenceLength = 2;
}

void CorsiBlockTest::lightUpBlock(int blockIndex) {
  // map to LED

  // analogWrite(blockIndex, SPEED);
  ledOn(blockIndex);
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
      ledOn(4);
      result = 4;
      waitForPress = false;

    } else if (getThumb() > threshold) {
      ledOn(ledThumb);
      result = ledThumb;
      waitForPress = false;
    }
  }

  Serial.println(result);

  // // debounce
  while (getFinger1() > threshold || getFinger2() > threshold || getFinger3() > threshold || getFinger4() > threshold || getThumb() > threshold) {
    delay(200);
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

    
    

    if (correct) {
      sequenceLength++;
      life = 2;  // reset to 2 for a correct one
    } else {
      life--;
    }

    if (sequenceLength > maxSequenceLength || life < 1) {
      oneMoreRound = false;
    }

    Serial.print("Round Done: ");
    Serial.print(correct);
    Serial.print(",");
    Serial.print(sequenceLength);
    Serial.print(",");
    Serial.print(life);
    Serial.print(",");
    Serial.print(oneMoreRound);
    Serial.println(" ");

  }
}

int CorsiBlockTest::getScore() {
  score = sequenceLength;
  return score;
}
