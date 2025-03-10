#include "corsiBlockTest.h"
#include "definitions.h"


CorsiBlockTest::CorsiBlockTest(int numBlocks, int maxSequenceLength) {
    this->numBlocks = numBlocks;
    this->maxSequenceLength = maxSequenceLength;
    this->sequenceLength = 2;  // Start with 2 blocks
    this->sequence = new int[maxSequenceLength];
    this->userInputIndex = 0;
}

void CorsiBlockTest::begin() {
    randomSeed(analogRead(0));  // Initialize random seed
    generateSequence();
}

void CorsiBlockTest::generateSequence() {
    for (int i = 0; i < sequenceLength; i++) {
        sequence[i] = random(0, numBlocks);  // Generate random block indices
    }
}

void CorsiBlockTest::playSequence() {
    for (int i = 0; i < sequenceLength; i++) {
        lightUpBlock(sequence[i]);
        delay(LIGHT_TIME);
    }
    // turn of leds
}

void CorsiBlockTest::waitForUserInput() { // needed?


    
}


void CorsiBlockTest::resetTest() {
    sequenceLength = 2;
}

void CorsiBlockTest::lightUpBlock(int blockIndex) {
    Serial.print("Lighting up block: ");
    Serial.println(blockIndex);
    delay(500);
}

bool CorsiBlockTest::checkUserInput() {
    // Check user input

    

    // if correct move on with next round otherwise remove a life


    // if correct and second round already increase blocks until max sequence is reached
    return false;
}