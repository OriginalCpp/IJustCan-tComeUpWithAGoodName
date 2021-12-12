#include "GameObject.hpp"
#include "Player.hpp"
#include <vector>


namespace levels
{
    bool setUpLevel(int p_level, Player& p_player, std::vector<GameObject*>& p_objects, SDL_Renderer* p_renderer);
    int setUpLevel1(Player& p_player, std::vector<GameObject*>& p_objects, SDL_Renderer* p_renderer);
}
