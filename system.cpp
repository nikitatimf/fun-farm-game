#include "system.h"
#include "data.h"


// Функция для перемещения курсура в заданные координаты.
void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursoreInfo;
    GetConsoleCursorInfo(hConsole, &cursoreInfo);
    cursoreInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursoreInfo);
    COORD position = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, position);
}

// Функция, проверяющая, была ли отпущена клавиша Enter, S, W.
// Если была отпущена - возвращается 0, иначе - 1.
short was_passed_button() {
    bool button = false;
    while (true) {
        // Проверка на нажатие "Enter".
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            button = true;
        }
        // Проверка на нажатие "Escape".
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            button = true;
        }
        // Проверка на нажатие "S".
        else if (GetAsyncKeyState(0x53) & 0x8000) {
            button = true;
        }
        // Проверка на нажатие "W".
        else if (GetAsyncKeyState(0x57) & 0x8000) {
            button = true;
        }
        // Проверка на нажатие "Q".
        else if (GetAsyncKeyState(0x51) & 0x8000) {
            button = true;
        }
        else if (button) {
            button = false;
            return 0;
        }
    }
    return 1;
}

// Функция, срабатывающая при достижении игроком нового уровня.
// И открывает улучшения объектов, при достижении нужного уровня.
// index - plant или animal, от этого зависит кол-во начисляемого опыта.
// num_animal - кол-во животных, в случае index == plant, полученный 
// Опыт умножается на num_animal*/
void new_level(string index, short num_animal) {
    short& level = player_info.player_level;
    float& full_exp = player_info.full_exp;
    short& current_exp = player_info.current_exp;

    // Начисление опыта.
    current_exp += index == "plant" ? app_info.EXP_FOR_PLANT : app_info.EXP_FOR_ANIMALS * num_animal;

    // Если опыт дошел до нового уровня.
    while (current_exp >= full_exp) {
        current_exp -= full_exp;
        full_exp *= 1.1;
        level++;

        for (int i = 0; i < 20; i++) {
            if (5 * garden[i].level <= level && garden[i].level < 4) {
                garden[i].chance_improve = true;
            }
        }        
        if (level % 4 == 0 && app_info.wel_level <= 4) {
            app_info.chance_improve_wel = true;
        }
        for (int i = 0; i < 4; i++) {
            if ((level % 4 == 0) && (animals_house[i].level <= 4)) {
                animals_house[i].chance_improving = true;
            }
        }

        if (6 * app_info.storage_level <= level && app_info.storage_level < 4) {
            app_info.chance_improve_storage = true;
        }
    }
}

// Функция, которая ищет элемент element в массиве
// arr, и возвращает индекс элемента.
// Если элемент не найден - возвращается -1.
int find_elem(string element, string arr[]) {
    for (int i = 0; i < text.NUM_CULTURE; i++) {
        if (element == arr[i]) {
            return i;
        }
    }
    return -1;
}

// Функция для управления персонажем.
void control() {
    short& y_person = koord.y_person;
    short& x_person = koord.x_person;
    const short& Y_MAX = dimension.Y_MAX;
    const short& X_MAX = dimension.X_MAX;
    switch (player_info.place_level) {
        // Верхняя, левая зона.
    case 0:
        // Нажатие на "W".
        if ((GetAsyncKeyState(0x57) & 0x8000) && y_person > 1) {
            y_person--;
            setCursorPosition(x_person, y_person + 1);
            // Стирание предыдыщего положения игрока.
            cout << ' ';
        }
        // Нажатие на "S".
        if ((GetAsyncKeyState(0x53) & 0x8000) && y_person < Y_MAX - 2 && y_person < (Y_MAX - 2) / 2) {
            y_person++;
            setCursorPosition(x_person, y_person - 1);
            cout << ' ';
        }
        // Нажатие на "D".
        if ((GetAsyncKeyState(0x44) & 0x8000) && x_person < (X_MAX - 1) / 2) {
            x_person++;
            setCursorPosition(x_person - 1, y_person);
            cout << ' ';
        }
        // Нажатие на "A".
        if ((GetAsyncKeyState(0x41) & 0x8000) && x_person > 1) {
            x_person--;
            setCursorPosition(x_person + 1, y_person);
            cout << ' ';
        }
        break;
        // Верхния ряд.
    case 1:
        // Нажатие на "W".
        if ((GetAsyncKeyState(0x57) & 0x8000) && y_person > 1) {
            y_person--;
            setCursorPosition(x_person, y_person + 1);
            cout << ' ';
        }
        // Нажатие на "S".
        if ((GetAsyncKeyState(0x53) & 0x8000) && y_person < Y_MAX - 2 && y_person < (Y_MAX - 2) / 2) {
            y_person++;
            setCursorPosition(x_person, y_person - 1);
            cout << ' ';
        }
        // Нажатие на "D".
        if ((GetAsyncKeyState(0x44) & 0x8000) && x_person < X_MAX - 2) {
            x_person++;
            setCursorPosition(x_person - 1, y_person);
            cout << ' ';
        }
        // Нажатие на "A".
        if ((GetAsyncKeyState(0x41) & 0x8000) && x_person > 1) {
            x_person--;
            setCursorPosition(x_person + 1, y_person);
            cout << ' ';
        }
        break;
        // Верхний ряд и нижняя, левая зона.
    case 2:
        // Нажатие на "W".
        if ((GetAsyncKeyState(0x57) & 0x8000) && y_person > 1) {
            y_person--;
            setCursorPosition(x_person, y_person + 1);
            cout << ' ';
        }
        // Нажатие на "S".
        if ((GetAsyncKeyState(0x53) & 0x8000)) {
            if (y_person < Y_MAX - 2 && x_person < X_MAX / 2 + 1) {
                y_person++;
                setCursorPosition(x_person, y_person - 1);
                cout << ' ';
            }
            else if (y_person < (Y_MAX - 2) / 2 && x_person > X_MAX / 2) {
                y_person++;
                setCursorPosition(x_person, y_person - 1);
                cout << ' ';
            }
        }
        // Нажатие на "D".
        if ((GetAsyncKeyState(0x44) & 0x8000) && x_person < X_MAX - 2) {
            if (y_person < (Y_MAX - 1) / 2 + 1) {
                x_person++;
                setCursorPosition(x_person - 1, y_person);
                cout << ' ';
            }
            else if (y_person > (Y_MAX - 1) / 2 && x_person < (X_MAX - 1) / 2) {
                x_person++;
                setCursorPosition(x_person - 1, y_person);
                cout << ' ';
            }
        }
        // Нажатие на "A".
        if ((GetAsyncKeyState(0x41) & 0x8000) && x_person > 1) {
            x_person--;
            setCursorPosition(x_person + 1, y_person);
            cout << ' ';
        }
        break;
        // Все поле.
    case 3:
        // Нажатие на "W".
        if ((GetAsyncKeyState(0x57) & 0x8000) && y_person > 1) {
            y_person--;
            setCursorPosition(x_person, y_person + 1);
            cout << ' ';
        }
        // Нажатие на "S".
        if ((GetAsyncKeyState(0x53) & 0x8000) && y_person < Y_MAX - 2) {

            y_person++;
            setCursorPosition(x_person, y_person - 1);
            cout << ' ';
        }
        // Нажатие на "D".
        if ((GetAsyncKeyState(0x44) & 0x8000) && x_person < X_MAX - 2) {
            x_person++;
            setCursorPosition(x_person - 1, y_person);
            cout << ' ';
        }
        // Нажатие на "A".
        if ((GetAsyncKeyState(0x41) & 0x8000) && x_person > 1) {
            x_person--;
            setCursorPosition(x_person + 1, y_person);
            cout << ' ';
        }
        break;
    }
}

// Функция, задающая начальные значения переменным в структурах.
void start_value() {
    garden[0].x_position = 5;
    garden[1].x_position = 15;
    garden[2].x_position = 40;
    garden[3].x_position = 65;
    garden[4].x_position = 69;
    garden[5].x_position = 90;
    garden[6].x_position = 130;
    garden[7].x_position = 145;
    garden[8].x_position = 85;
    garden[9].x_position = 130;
    garden[10].x_position = 7;
    garden[11].x_position = 30;
    garden[12].x_position = 35;
    garden[13].x_position = 50;
    garden[14].x_position = 65;
    garden[15].x_position = 80;
    garden[16].x_position = 100;
    garden[17].x_position = 120;
    garden[18].x_position = 130;
    garden[19].x_position = 140;

    garden[0].y_position = 15;
    garden[1].y_position = 15;
    garden[2].y_position = 13;
    garden[3].y_position = 5;
    garden[4].y_position = 11;
    garden[5].y_position = 3;
    garden[6].y_position = 15;
    garden[7].y_position = 10;
    garden[8].y_position = 14;
    garden[9].y_position = 5;
    garden[10].y_position = 25;
    garden[11].y_position = 33;
    garden[12].y_position = 21;
    garden[13].y_position = 35;
    garden[14].y_position = 27;
    garden[15].y_position = 25;
    garden[16].y_position = 23;
    garden[17].y_position = 22;
    garden[18].y_position = 35;
    garden[19].y_position = 34;

    animals_house[0].x_position = 5;
    animals_house[1].x_position = 110;
    animals_house[2].x_position = 49;
    animals_house[3].x_position = 130;

    animals_house[0].y_position = 5;
    animals_house[1].y_position = 10;
    animals_house[2].y_position = 27;
    animals_house[3].y_position = 25;

    animals_house[0].animal_time = 10;//300;
    animals_house[1].animal_time = 1;// 600;
    animals_house[2].animal_time = 1;// 400;
    animals_house[3].animal_time = 1;// 350;

    for (int i = 0; i < 20; i++) {
        app_info.kov_growing[i] = 1;
    }

}
