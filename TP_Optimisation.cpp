
#include <chrono>
#include <iomanip>
#include <set>
#include <thread>

#include "Board.h"
#include "Player.h"
#include "SetList.h"

// ne pas tester avec 1 seule game parce que chiant
int nbGame = 1000, nbLoop = 2000, winP1 = 0, totalWin = 0, lastWinP1 = 0, avgNbTurn = 0;
const int nbThreads = 4;

std::string foldername = "";//"/csv/";

/*
 * Write CSV file with winrate
 */
void WriteWinRate(std::string filename, float* winRateArray, float* avgNbTurnArray)
{
    csvfile csv(filename);
    csv << "Iteration" << "Win rate" << "Avg nb turn" << endrow;
    for (int i = 0; i < nbLoop; i++)
    {
        csv << i+1 << winRateArray[i] << avgNbTurnArray[i] << endrow;
    }
}

void DoLoop(Board* board, int nbOfGame)
{
    board->DoLoop(nbOfGame, avgNbTurn, winP1);
}

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::system_clock> startProgram = std::chrono::system_clock::now();

    srand(time(nullptr));
    std::chrono::duration<double> all_duration = std::chrono::duration<double>::zero();

    SetList* setList = new SetList();
    Player* p1 = new Player(setList, 1);
    Player* p2 = new Player(setList, 2);

    Board* boards[nbThreads];
    for (int i=0; i<nbThreads; i++)
        boards[i] = new Board(p1, p2);
    std::vector<std::thread> threads;

    p1->WriteAmountOfCardsPerCostHistogram(foldername + "AmountOfCardsPerCostDataBegin.csv");
    p1->WriteDeck(foldername + "DeckBegin.csv");

    float winRateArray[nbLoop];
    float avgNbTurnArray[nbLoop];

    for (int loop=0; loop < nbLoop; loop++)
    {
        avgNbTurn = 0;
        winP1 = 0;
        p1->ChangeOneCard();
        
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        for (int i = 0; i < nbThreads; i++)
            threads.push_back(std::thread(DoLoop, boards[i], nbGame/nbThreads));
        for (auto &th : threads)
            th.join();
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

        if (winP1 >= lastWinP1)
            lastWinP1 = winP1;
        else
            p1->UndoChangeOneCard();
        
        totalWin += winP1;
        float rate = (float) winP1 / (float) nbGame;
        float lastRate = (float) lastWinP1 / (float) nbGame;

        winRateArray[loop] = winP1;
        avgNbTurnArray[loop] = (int) avgNbTurn/nbGame;

        std::chrono::duration<double> elapsed_seconds = end - start;
        all_duration += elapsed_seconds;

        threads.clear();

        if (true)
        {
            std::cout << std::fixed;
            std::cout.precision(2);
            std::cout << "| P1: " << (rate * 100.0f) << "% win <> " << (lastRate * 100.0f) << "% last win |";
            std::cout.precision(7);
            std::cout << "| time: " << elapsed_seconds.count() << "s |";
            std::cout.precision(2);
            std::cout << "| Avg nb turn: " << (float)avgNbTurn/(float)nbGame << std::endl;
        }
    }

    p1->WriteAmountOfCardsPerCostHistogram(foldername + "AmountOfCardsPerCostDataEnd.csv");
    p1->WriteDeck(foldername + "DeckEnd.csv");

    WriteWinRate(foldername + "WinRate.csv", winRateArray, avgNbTurnArray);

    std::cout << "Total loop duration: " << all_duration.count()  << "s." << std::endl;
    float rate = (float) totalWin / (float) (nbGame * nbLoop);
    std::cout << "Final win rate: " << rate << "." << std::endl;

    std::chrono::time_point<std::chrono::system_clock> endProgram = std::chrono::system_clock::now();
    std::chrono::duration<double> durationProgram = endProgram - startProgram;
    std::cout << "Program duration: " << durationProgram.count()  << "s." << std::endl;
    return 0;
}


