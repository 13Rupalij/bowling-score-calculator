#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum class FrameType
{
    Normal,
    Spare,
    Strike
};

struct Frame
{
    int throw1 = 0;
    int throw2 = 0;
    int bonus = 0;
    int extraThrow = 0; // only for 10th frame
    FrameType type = FrameType::Normal;
    int frameScore = 0;
};

class BowlingGame
{
public:
    void playGame();

private:
    vector<Frame> frames;

    int getInput(const std::string &prompt, int min, int max);
    void applyBonuses(int currentIndex);
    void printScore();
};
#endif // BOWLING_GAME_H