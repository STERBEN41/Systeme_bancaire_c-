#include <iostream>
#include "banque.h"
#include "menu.h"

using namespace std;

int main()
{
    Banque banque("B1", "TontinePro Banque");
    Menu menu(banque);
    menu.lancer();
    return 0;
}
