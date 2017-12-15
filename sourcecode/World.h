#include <SFML/Graphics.hpp>
#include <vector>





class World //draw map
{
public:
        World() = default;
        ~World() = default;
        World(const World&) = default;
        void render_window(); //ritar upp World
private:
        void collision();
        void pause_game();
        void lose_game();
        int point;
        void get_point();
};
