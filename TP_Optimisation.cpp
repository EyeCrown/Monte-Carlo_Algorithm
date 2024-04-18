
#include <chrono>
#include <iomanip>

#include "Board.h"
#include "Player.h"
#include "SetList.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    std::chrono::duration<double> all_duration = std::chrono::duration<double>::zero();

    
    SetList* setList = new SetList();
    setList->WriteSetList();
    int nbGame = 1000, nbLoop = 10, winP1 = 0, totalWin = 0;
    
    Player* p1 = new Player(setList, 1);
    Player* p2 = new Player(setList, 2);

    p1->WriteAmountOfCardsPerCostHistogram("AmountOfCardsPerCostDataBegin.csv");
    
    Board* boardGame = new Board();

    int lastWinP1 = nbGame/2;
    int sumTurns = 0;
    for (int loop=0; loop < nbLoop; loop++)
    {
        winP1 = 0;
        p1->ChangeOneCard();
        
        start = std::chrono::system_clock::now();
        /*for (int i=0; i < nbGame/2; i++)
        {
            if (boardGame->DoGame(*p1, *p2) == p1->ID)
                winP1++;
            sumTurns += boardGame->nbTurn;
        }
        for (int i=0; i < nbGame/2; i++)
        {
            
            if (boardGame->DoGame(*p2, *p1) == p1->ID)
                winP1++;
            sumTurns += boardGame->nbTurn;
        }*/
        winP1 = boardGame->DoLoop(p1, p2, nbGame);
        end = std::chrono::system_clock::now();
        
        if (winP1 < lastWinP1)
            p1->UndoChangeOneCard();

        totalWin += winP1;
        float rate = (float) winP1 / (float) nbGame;
        
        elapsed_seconds = end - start;
        all_duration += elapsed_seconds;
        std::cout << std::fixed;
        std::cout.precision(2);
        std::cout << "P1: " << (rate * 100.0f) << "% win rate  <|";
        std::cout.precision(5);
        std::cout << "|> time: " << elapsed_seconds.count() << "s" << std::endl; 

        std::cout << "Average number of turn: " << (float) sumTurns/(float) nbGame << std::endl;
    }
    
    p1->WriteAmountOfCardsPerCostHistogram("AmountOfCardsPerCostDataEnd.csv");

    std::cout << "Total duration: " << all_duration.count()  << "s." << std::endl;

    float rate = (float) totalWin / (float) (nbGame * nbLoop);

    std::cout << "Final win rate: " << rate << "." << std::endl;
    
    return 0;
}

void WriteWinRate()
{
    csvfile csv("Winrate.csv");

    
}
