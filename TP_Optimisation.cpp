
#include <chrono>

#include "Board.h"
#include "Game.h"
#include "OPlayer.h"
#include "Player.h"
#include "SetList.h"

int main(int argc, char* argv[])
{
    std::cout << "Main begin =====================" << std::endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    SetList setList = SetList();


    int winP1 = 0, winP2 = 0;
    
    OPlayer* p1 = new OPlayer(setList);
    OPlayer* p2 = new OPlayer(setList);
    
    
    Board* boardGame = new Board();
    
    
    int nbGame = 10;

    //boardGame->Init(p1, p2);

    start = std::chrono::system_clock::now();
    for (int i=0; i < nbGame/2; i++)
    {
        int winner = boardGame->DoGame(*p1, *p2);
        winner ? ++winP1 : ++winP2;
    }
    for (int i=0; i < nbGame/2; i++)
    {
        int winner = boardGame->DoGame(*p2, *p1);
        winner ? ++winP2 : ++winP1;
    }
    
    end = std::chrono::system_clock::now();

    float rate1 = (float) winP1 / (float) nbGame;
    float rate2 = (float) winP2 / (float) nbGame;
    
    std::cout << "Player 1 wins: " + std::to_string(winP1) + "  "+ std::to_string(rate1 * 100.0f) +"%    |||| Player 2 wins: "  + std::to_string(winP2) + "  "+ std::to_string(rate2 * 100.0f) +"%" << std::endl;
    
 
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    
    return 0;
}
