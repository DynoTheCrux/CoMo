#ifndef corsiBlockTest_header
#define corsiBlockTest_header

class CorsiBlockTest {
public:
    CorsiBlockTest(int maxSequenceLength, bool withVibration);

    void begin();
    void generateSequence();
    void playSequence();
    void waitForUserInput();
    int checkUserInput();
    void resetTest();
    void runCorsiBlockTest();
    int getScore();
    void setSpeed(int speed);
    
private:
    int* sequence;  // Holds the sequence of block indexes
    int sequenceLength;  // Current sequence length
    int maxSequenceLength;  // Maximum difficulty level
    int numBlocks = 5;  // Number of blocks in the test
    int userInputIndex;  // Tracks user input position
    int LIGHT_TIME = 500; // ms
    int threshold;
    int releaseThreshold;
    int score = -1;
    bool vibration = false;

    void lightUpBlock(int blockIndex); // will be LED
    int getUserInput();  // get user Input from the buttons
    void vibrationOff();
};



#endif