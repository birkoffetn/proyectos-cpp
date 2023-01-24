#ifndef __MENU__HPP__
#define __MENU__HPP__

#include <functional>
#include <vector>
#include <string>

class Menu
{
public:
    Menu(const std::string &title);
    void operator()();
    template <typename Fun>
    void addItem(const std::string &item, Fun fun);

private:
    std::string title;
    bool isRunning;
    std::vector<std::pair<std::string, std::function<void()>>> items;
};

template <typename Fun>
void Menu::addItem(const std::string &item, Fun fun)
{
    auto i = items.size() - 1;
    items.push_back(items.back());
    items[i] = std::make_pair(item, fun);
}

#endif
