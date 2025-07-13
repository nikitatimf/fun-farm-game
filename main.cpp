#include <windows.h>
#include <iostream>
#include <chrono>

#include "data.h"
#include "garden.h"
#include "system.h"
#include "storage.h"
#include "animal.h"
#include "store.h"
#include "well.h";
#include "field_and_palce.h"
using namespace std;

int main(){
    // Для корректного вывода игры на экран, просиб
    // игрока нажать кнопку F11.
    cout << "Для начала игры нажмите кнопку F11";
    while (true) {
        if (GetAsyncKeyState(VK_F11) & 0x8000) {
            break;
        }
    }
    start_value();
    while (true) {
        drawing_field();
        control();
        if_in_buy_place_zone();

        draw_garden();
        if_in_garden();

        water_in_wel();
        drawing_well();
        if_in_well();
        
        drawing_storage();
        if_in_storage();

        draw_animals_house();
        if_in_animals_house();
        animal_goods();
        
        draw_store();
        if_in_store_area();
    }
    return 0;
}