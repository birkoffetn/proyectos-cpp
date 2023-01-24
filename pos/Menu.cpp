#include "Menu.hpp"

#include <iostream>

Menu::Menu(const std::string &title) : title(title)
{
    bool &run = isRunning;
    items.push_back(std::make_pair("Salir", [&run]()
                                   { run = false; }));
}

void Menu::operator()()
{
    size_t index = 0;
    char opcion;
    isRunning = true;
    while (isRunning)
    {
        system("clear");
        std::cout << "\n\n         => " << title << "\n\n";
        for (size_t i = 0; i < items.size(); ++i)
        {
            std::cout << (i == index ? " -> " : "    ") << items[i].first << "\n";
        }
        std::cout << "\n        Opcion: ";
        opcion = std::cin.get();
        std::cin.get();
        if (opcion == 's' || opcion == 'S')
        {
            index += 1;
            index %= items.size();
        }
        else if (opcion == 'W' || opcion == 'w')
        {
            if (index == 0)
            {
                index += items.size();
            }
            index -= 1;
        }
        else if (opcion == '\n')
        {
            items[index].second();
        }
    }
}