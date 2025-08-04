#include <ctime>

#include "Menu/Menu.h"


int main() {
    // Seeds the random numbers
    srand(time(nullptr));

    Menu menu;
    Menu::State currentState = Menu::State::Main;

    // Continuously run through the menus until the Exit state is returned, then stop the program
    while (currentState != Menu::State::Exit) {
        currentState = menu.Run(currentState);
    }
    return 0;
}
