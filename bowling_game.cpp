#include "bowling_game.h"

void BowlingGame::playGame(void)
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Frame " << (i + 1) << "\n";

        Frame frame;
        frame.throw1 = getInput("  First roll: ", 0, 10);

        // Strike detection (only 1 roll)
        if (i < 9 && frame.throw1 == 10)
        {
            frame.type = FrameType::Strike;
            frame.throw2 = 0;
        }
        else
        {
            int max2 = (i < 9) ? (10 - frame.throw1) : 10;
            frame.throw2 = getInput("  Second roll: ", 0, max2);

            if (frame.throw1 + frame.throw2 == 10)
            {
                frame.type = FrameType::Spare;
            }
            else
            {
                frame.type = FrameType::Normal;
            }
        }

        // 10th frame: allow extra roll if spare or strike
        if (i == 9 && (frame.throw1 == 10 || frame.throw1 + frame.throw2 == 10))
        {
            frame.extraThrow = getInput("  Bonus roll: ", 0, 10);
        }

        frames.push_back(frame);
        applyBonuses(i);
    }
    printScore();
}

int BowlingGame::getInput(const string &prompt, int min, int max)
{
    int val;
    while (true)
    {
        cout << prompt;
        cin >> val;
        if (std::cin.fail() || val < min || val > max)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number between " << min << " and " << max << "\n";
        }
        else
        {
            return val;
        }
    }
}
void BowlingGame::applyBonuses(int currentIndex)
{
    Frame &current = frames[currentIndex];
    if (currentIndex >= 1)
    {
        Frame &prev = frames[currentIndex - 1];
        if (prev.type == FrameType::Spare)
        {
            prev.bonus = current.throw1;
        }
        else if (prev.type == FrameType::Strike)
        {
            prev.bonus = current.throw1 + current.throw2;
        }
    }
    if (currentIndex >= 2)
    {
        Frame &prev2 = frames[currentIndex - 2];
        Frame &prev1 = frames[currentIndex - 1];
        if (prev2.type == FrameType::Strike && prev1.type == FrameType::Strike)
        {
            prev2.bonus = prev1.throw1 + current.throw1;
        }
    }
    if (currentIndex == 9)
    {
        current.frameScore = current.throw1 + current.throw2 + current.extraThrow;
    }
    else
    {
        current.frameScore = current.throw1 + current.throw2;
    }
}
void BowlingGame::printScore()
{
    int total = 0;
    for (int i = 0; i < frames.size(); ++i)
    {
        Frame &f = frames[i];
        int frameTotal = f.bonus + f.frameScore;
        total += frameTotal;
    }
    std::cout << "Final Score of the single player: " << total << "\n";
}