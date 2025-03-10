#ifndef corsiBlockTest_header
#define corsiBlockTest_header

class CorsiBlockTest {
public:
    CorsiBlockTest(int numBlocks, int maxSequenceLength);

    void begin();
    void generateSequence();
    void playSequence();
    void waitForUserInput();
    bool checkUserInput();
    void resetTest();
    
private:
    int* sequence;  // Holds the sequence of block indexes
    int sequenceLength;  // Current sequence length
    int maxSequenceLength;  // Maximum difficulty level
    int numBlocks;  // Number of blocks in the test
    int userInputIndex;  // Tracks user input position
    int LIGHT_TIME = 1000; // ms

    void lightUpBlock(int blockIndex); // will be LED
    int getUserInput();  // get user Input from the buttons
};



#endif