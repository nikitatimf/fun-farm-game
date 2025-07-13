#include "garden.h"
#include "storage.h"
#include "system.h"

// Функция, улучшающая уровень огорода.
// index - индекс поля в массиве структуры полей.
void improve_garden_level(int index) {
    // Списывание денег за улучшение.
    player_info.money -= app_info.price_up_level_garden[garden[index].level - 1];
    garden[index].level++;
    app_info.kov_growing[index] *= 0.9;
    // Проверка на возможность дальнейшего улучшения.
    if (garden[index].level == 2 && player_info.player_level < 10) {
        garden[index].chance_improve = false;
    }
    // Проверка на возможность дальнейшего улучшения.
    else if (garden[index].level == 3 && player_info.player_level < 15) {
        garden[index].chance_improve = false;
    }
    // Если уровень поля 4, его улучшение не возможна.
    else if (garden[index].level > 3) {
        garden[index].chance_improve = false;
    }
}

// Функция, рисующая меню выбора посаженного растения.
// i - индекс поля в массиве структур.
void menu_choise_plant_garden(short i) {
    string* culture = text.string_culture;
    short x_curs_pos = koord.x_curs_pos_garden_menu, y_curs_pos = koord.y_curs_pos_garden_menu;
    system("cls");
    while (true) {
        // Отрисовка окна.
        for (short x = koord.X_PLANT_MENU; x < dimension.X_SIZE_PLANT_MENU + koord.X_PLANT_MENU; x++) {
            for (short y = koord.Y_PLANT_MENU; y < dimension.Y_SIZE_PLANT_MENU + koord.Y_PLANT_MENU; y++) {
                if (x == koord.X_PLANT_MENU || y == koord.Y_PLANT_MENU ||
                    x == koord.X_PLANT_MENU + dimension.X_SIZE_PLANT_MENU - 1 ||
                    y == koord.Y_PLANT_MENU + dimension.Y_SIZE_PLANT_MENU - 1) {
                    setCursorPosition(x, y);
                    cout << "#";
                }
            }
        }
        // Отрисовка списка культур для их выбора.
        for (int i = 0; i < 9; i++) {
            setCursorPosition(koord.X_PLANT_MENU + 1, koord.Y_PLANT_MENU + i + 1);
            cout << culture[i];
        }
        setCursorPosition(x_curs_pos, y_curs_pos);
        cout << "<-";
        // Если нажата клавиша "W" - курсор передвигается вверх.
        if ((GetAsyncKeyState(0x57) & 0x8000) && y_curs_pos > koord.Y_PLANT_MENU + 1) {
            if (!was_passed_button()) {
                y_curs_pos--;
                setCursorPosition(x_curs_pos, y_curs_pos + 1);
                cout << "  ";
            }
        }
        // Если нажата клавиша "S" - курсор передвигается вниз.
        else if ((GetAsyncKeyState(0x53) & 0x8000) && y_curs_pos < koord.Y_PLANT_MENU + dimension.Y_SIZE_PLANT_MENU - 2) {
            if (!was_passed_button()) {
                y_curs_pos++;
                setCursorPosition(x_curs_pos, y_curs_pos - 1);
                cout << "  ";
            }
        }
        // Если нажата клавиша Enter - на поле высаживается
        // соответствующая культура.
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!was_passed_button()) {
                garden[i].area = "\033[36m. . .\033[0m";
                garden[i].culture1 = (garden_game::culture)(y_curs_pos - 16);
                break;
            }
        }
        // Если нажата клавиша Escape - выход из меню.
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
    }
    system("cls");
}

// Функция, рисующая поля.
void draw_garden(){
    char garden1[] = " _____ ";
    char garden2[] = "|";
    char garden3[] = "¯¯ ";
    for (int i = 0; i < 20; i++) {
        short x_position = garden[i].x_position, y_position = garden[i].y_position;
        // Проверка на то, вырасла ли культура.
        chrono::seconds time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - garden[i].g_clock);
        if (garden[i].area == "\033[32m:::::\033[0m" && time.count() == (int)(app_info.time_plant_garden[garden[i].culture1] * app_info.kov_growing[i])) {
            garden[i].area = "\033[33m*****\033[0m";
        }
        // Отрисовка поля.
        setCursorPosition(x_position, y_position);
        cout << garden1;
        setCursorPosition(x_position, y_position + 1);
        cout << garden2 << garden[i].area;
        setCursorPosition(x_position, y_position + 2);
        cout << garden2 << garden[i].area;
        setCursorPosition(x_position + dimension.GARDEN_WEIGHT - 2, y_position + 1);
        cout << garden2;
        setCursorPosition(x_position + dimension.GARDEN_WEIGHT - 2, y_position + 2);
        cout << garden2;
        setCursorPosition(x_position + 4, y_position + 3);
        cout << garden3;
        // Отображение вреимени, оставшееся до сбора посадки.
        if (garden[i].ifplant) {
            setCursorPosition(x_position + 1, y_position);
            cout << ((int)(app_info.time_plant_garden[garden[i].culture1]*app_info.kov_growing[i]) - time.count()) / 60 << ":";
            if (((int)(app_info.time_plant_garden[garden[i].culture1] * app_info.kov_growing[i]) - time.count()) % 60 < 10) {
                cout << "0" << ((int)(app_info.time_plant_garden[garden[i].culture1] * app_info.kov_growing[i]) - time.count()) % 60;
            }
            else {
                cout << ((int)(app_info.time_plant_garden[garden[i].culture1] * app_info.kov_growing[i]) - time.count()) % 60;
            }
        }
        // Если поле не занято, его внутренность не заполняем.
        if ((int)(app_info.time_plant_garden[garden[i].culture1] * app_info.kov_growing[i]) - time.count() == 0) {
            garden[i].ifplant = false;
            setCursorPosition(x_position, y_position + 4);
            cout << "    ";
        }
        // Отображение уровня.
        for (int j = 0; j < garden[i].level; j++) {
            setCursorPosition(x_position + j, y_position + 3);
            cout << "\033[33m*\033[0m";
            continue;
        }
    }
}

// Функция, проверяющая находится ли персонаж внутри поля.
void if_in_garden() {
    const short& x_person = koord.x_person;
    const short& y_person = koord.y_person;
    const short height = dimension.GARDEN_HEIGHT;
    const short weight = dimension.GARDEN_WEIGHT;
    // Находится ли персонаж в огороде.
    bool is_now_in_garden = false;
    for (int i = 0; i < 20; i++) {
        if (x_person > garden[i].x_position &&
            x_person < garden[i].x_position + weight &&
            y_person > garden[i].y_position &&
            y_person < garden[i].y_position + height) {
            app_info.is_in_garden = true;
            is_now_in_garden = true;
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
            if (garden[i].area == "     ") {
                cout << "Press 'Enter' to go to the menu.";
            }
            else if (garden[i].area == "\033[36m. . .\033[0m") {
                cout << "Press 'Enter' to water the garden.";
            }
            else if (garden[i].area == "*****") {
                cout << "Press 'Enter' to harvest.";
            }
            // Если поле ничем не засажено.
            if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && garden[i].area == "     ") {
                if (!was_passed_button()) {
                    menu_choise_plant_garden(i);
                }
            }
            // Если поле засажено, но не полито.
            if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && player_info.water >= 1 && garden[i].area == "\033[36m. . .\033[0m") {
                if (!was_passed_button()) {
                    garden[i].area = "\033[32m:::::\033[0m";
                    garden[i].g_clock = chrono::high_resolution_clock::now();
                    player_info.water--;
                    garden[i].ifplant = true;
                }
            }
            // Если культура в поле выросла.
            if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && garden[i].area == "\033[33m*****\033[0m") {
                if (!was_passed_button()) {
                    garden[i].area = "     ";
                    // Проверка на то, вмещается ли урожай в складе.
                    if (warehouse_storage(1)) {
                        player_info.sum_culture[garden[i].culture1]++;
                        new_level("plant");
                    }
                }
            }
            // Если есть возможность улучшения поля.
            if (garden[i].chance_improve) {
                setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION + 1);
                cout << "Enter 'q' to impovr garden level. Price: " << app_info.price_up_level_garden[garden[i].level-1];
                // Если нажата клавиша "Q" и у игрока достаточно денег.
                if ((GetAsyncKeyState(0x51) & 0x8000) && player_info.money >= app_info.price_up_level_garden[garden[i].level - 1]) {
                    if (!was_passed_button()) {
                        improve_garden_level(i);
                    }
                }
                // Если нажата клавиша "Q" и у игрока не достаточно денег.
                else if (GetAsyncKeyState(0x51) & 0x8000 && player_info.money < app_info.price_up_level_garden[garden[i].level - 1]) {
                    system("cls");
                    cout << "Подзаработайте еще " << app_info.price_up_level_garden[garden[i].level - 1] - player_info.money << " денег";
                    Sleep(2000);
                    system("cls");
                }
            }
        }
        // Стирание сообщени я в меню уведомлений.
        if (app_info.is_in_garden && !is_now_in_garden) {
            app_info.is_in_garden = false;
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
            cout << "                                  ";
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION + 1);
            cout << "                                                    ";
        }
    }
}