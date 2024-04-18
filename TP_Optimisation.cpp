
#include <chrono>
#include <iomanip>

#include "Board.h"
#include "Player.h"
#include "SetList.h"

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::system_clock> start, end;

    std::chrono::duration<double> all_duration = std::chrono::duration<double>::zero();

    
    SetList* setList = new SetList();

    int nbGame = 1000, nbLoop = 1000;
    
    int winP1 = 0, totalWin = 0;
    
    Player* p1 = new Player(setList);
    Player* p2 = new Player(setList);
    
    Board* boardGame = new Board();

    int lastWinP1 = nbGame/2;
    
    for (int loop=0; loop < nbLoop; loop++)
    {
        winP1 = 0;
        p1->ChangeOneCard();

        
        start = std::chrono::system_clock::now();
        for (int i=0; i < nbGame; i++)
        {
            int winner;

            i%2 ? winner = boardGame->DoGame(*p1, *p2) : winner = boardGame->DoGame(*p2, *p1);
            
            winner ? ++winP1 : winP1;
        }
        end = std::chrono::system_clock::now();
        
        if (winP1 < lastWinP1)
            p1->UndoChangeOneCard();

        totalWin += winP1;
        float rate = (float) winP1 / (float) nbGame;
        
        std::chrono::duration<double> elapsed_seconds = end - start;
        all_duration += elapsed_seconds;
        std::cout << std::fixed;
        std::cout.precision(2);
        std::cout << "P1: " << (rate * 100.0f) << "% win rate  <|";
        std::cout.precision(5);
        std::cout << "|> time: " << elapsed_seconds.count() << "s" << std::endl;
    }
    
    std::cout << "Total duration: " << all_duration.count()  << "s." << std::endl;

    float rate = (float) totalWin / (float) (nbGame * nbLoop);

    std::cout << "From 0.5 win rate to " << rate << "." << std::endl;
    
    return 0;
}
