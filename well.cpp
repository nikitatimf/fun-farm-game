#include "well.h"

// Функция, улучшающая колодец.
void improve_well_level() {
    // Списывание денег за улучшение.
    player_info.money -= app_info.price_up_level_well[app_info.wel_level - 1];
    // Повышвем урровень и уменьшаем время добычи воды.
    app_info.wel_level++;
    app_info.perez_wel *= 0.90;
    // Проверка на возможность дальнейшего улучшения.
    if ((app_info.wel_level == 2 && player_info.player_level <= 4) ||
        (app_info.wel_level == 3 && player_info.player_level <= 8) ||
        (app_info.wel_level == 4 && player_info.player_level <= 12) ||
        app_info.wel_level >= 4) {
        app_info.chance_improve_wel = false;
    }
}

// Функция, рисующая колодец.
void drawing_well() {
    const short& Y_WELL = koord.Y_WELL;
    const short& X_WELL = koord.X_WELL;
    const char WELL[3][8] = { "  / \\" ,
                              "/     \\",
                              " || ||" };
    // Рисовка колодца.
    for (int i = 0; i < 3; i++) {
        setCursorPosition(X_WELL, Y_WELL + i);
        cout << WELL[i];
    }
    // Рисовка уровня колодца.
    for (int i = 0; i < app_info.wel_level; i++) {
        setCursorPosition(1 + X_WELL + i, Y_WELL + 1);
        cout << "\033[33m*\033[0m";
    }
}

// Добыча воды в колодце.
// И проверка, находится ли персонаж в 
// области перед колодцем.
void water_in_wel() {
    // Если вода в колодце есть - true
    // иначе - false.
    bool water = true;
    // Рисуется указатель, показывающий, есть ли вода
    // иначе - оставшееся время.
    chrono::seconds time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - app_info.well_time);
    if (app_info.well_water) {
        setCursorPosition(koord.X_WELL + 3, koord.Y_WELL - 1);
        cout << "\033[36m^\033[0m";
    }
    else {
        setCursorPosition(koord.X_WELL + 2, koord.Y_WELL - 1);
        cout << (app_info.perez_wel - time.count()) / 60 << ":";
        if ((app_info.perez_wel - time.count()) % 60 < 10) {
            cout << "0" << (app_info.perez_wel - time.count()) % 60;
        }
        else {
            cout << (app_info.perez_wel - time.count()) % 60;
        }
    }
    // Проверка на то, добылась ли вода в колодце.
    time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - app_info.well_time);
    if (time.count() == app_info.perez_wel && !app_info.well_water) {
        app_info.well_water = true;
        setCursorPosition(koord.X_WELL + 2, koord.Y_WELL - 1);
        cout << "      ";
    }
}

// Функция, проверяющая находится ли персонаж
// перед колодцем.
void if_in_well() {
    // Находится ли персонаж перед колодцем.
    bool is_now_near_well = false;
    // Проверка на то, стоит ли персонаж в области перед колодцем.
    if (koord.x_person > koord.X_WELL && koord.x_person < koord.X_WELL + 6 &&
        koord.y_person == koord.Y_WELL + 3) {
        is_now_near_well = true;
        app_info.is_near_well = true;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "Press 'Enter' to take water.";
        // Проверка на то, была ли нажата и отпущена клавиша Enter.
        if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && app_info.well_water) {
            if (!was_passed_button()) {
                player_info.water++;
                app_info.well_time = chrono::high_resolution_clock::now();
                app_info.well_water = false;
            }
        }
        // Если есть возможность улучшения колодца.
        if (app_info.chance_improve_wel) {
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION + 1);
            cout << "Enter 'q' to impovу well level. Price: " << app_info.price_up_level_well[app_info.wel_level - 1];
            // Если была нажата клавиша "Q" и достаточно денег для улучшения.
            if ((GetAsyncKeyState(0x51) & 0x8000) && player_info.money >= app_info.price_up_level_well[app_info.wel_level - 1]) {
                // Если клавиша была отпущена.
                if (!was_passed_button()) {
                    improve_well_level();
                }
            }
            // Если нажата клавиша "Q" и у игрока не достаточно денег.
            else if (GetAsyncKeyState(0x51) & 0x8000 && player_info.money < app_info.price_up_level_well[app_info.wel_level - 1]) {
                system("cls");
                cout << "Подзаработайте еще " << app_info.price_up_level_well[app_info.wel_level - 1] - player_info.money << " денег";
                Sleep(2000);
                system("cls");
            }
        }
    }
    // Стирание надписи в меню уведомлений.
    else if (app_info.is_near_well && !is_now_near_well) {
        app_info.is_near_well = false;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "                                     ";
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION+1);
        cout << "                                                      ";
    }
}