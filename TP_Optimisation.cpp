
#include <chrono>
#include <iomanip>
#include <set>
#include <thread>

#include "Board.h"
#include "Player.h"
#include "SetList.h"



int nbGame = 1000, nbLoop = 1000, winP1 = 0, totalWin = 0, lastWinP1 = 0, avgNbTurn = 0;
const int nbThreads = 4;


void DoLoop(Board* board, int nbOfGame)
{
    board->DoLoop(nbOfGame, avgNbTurn, winP1);
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    std::chrono::duration<double> all_duration = std::chrono::duration<double>::zero();

    SetList* setList = new SetList();
    Player* p1 = new Player(setList, 1);
    Player* p2 = new Player(setList, 2);

    Board* boards[nbThreads];
    for (int i=0; i<nbThreads; i++)
        boards[i] = new Board(p1, p2);
    std::vector<std::thread> threads;

    p1->WriteAmountOfCardsPerCostHistogram("AmountOfCardsPerCostDataBegin.csv");
    p1->WriteDeck("DeckBegin.csv");
    
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
        
        if (winP1 > lastWinP1)
            lastWinP1 = winP1;
        else
            p1->UndoChangeOneCard();
        
        
        totalWin += winP1;
        float rate = (float) winP1 / (float) nbGame;
        float lastRate = (float) lastWinP1 / (float) nbGame;
        
        std::chrono::duration<double> elapsed_seconds = end - start;
        all_duration += elapsed_seconds;

        threads.clear();
        
        if (false)
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
    
    p1->WriteAmountOfCardsPerCostHistogram("AmountOfCardsPerCostDataEnd.csv");
    p1->WriteDeck("DeckEnd.csv");

    std::cout << "Total duration: " << all_duration.count()  << "s." << std::endl;

    float rate = (float) totalWin / (float) (nbGame * nbLoop);

    std::cout << "Final win rate: " << rate << "." << std::endl;
    
    return 0;
}






void WriteWinRate()
{
    csvfile csv("Winrate.csv");

    
}
