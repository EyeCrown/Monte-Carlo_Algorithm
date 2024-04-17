
#include <chrono>

#include "Game.h"
#include "Player.h"
#include "SetList.h"

int main(int argc, char* argv[])
{
    std::cout << "Main begin =====================" << std::endl;

    SetList setList = SetList();

    //std::cout << setList.ToString() << std::endl;

    int winP1 = 0;
    int winP2 = 0;
    
    Player* p1 = new Player(1, setList);
    Player* p2 = new Player(2, setList);
    
    Game* game = new Game(p1, p2);

    int nbGame = 1000;

    std::chrono::time_point<std::chrono::system_clock> start, end;
 
    start = std::chrono::system_clock::now();
    for (int i=0; i < nbGame; i++)
    {
        Player winner = *game->MakeGame(i%2);

        if (winner._id == 1)
            winP1++;
        else
            winP2++;
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
