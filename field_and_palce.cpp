#include "field_and_palce.h"

// Функция, рисующая игровое поле.
void drawing_field() {
    const short Y_MAX = dimension.Y_MAX;
    const short X_MAX = dimension.X_MAX;
    short& y_person = koord.y_person;
    short& x_person = koord.x_person;
    for (int y = 0; y < Y_MAX; y++) {
        for (int x = 0; x < X_MAX; x++) {
            if (y == 0 || x == 0 || y == Y_MAX - 1 || x == X_MAX - 1) {
                setCursorPosition(x, y);
                cout << "#";
            }
            else if (y == y_person && x == x_person) {
                setCursorPosition(x, y);
                cout << '@';
            }
        }
    }
    // Рисование линий, разделяющих поле на 4 части.
    // Проверка уровень игрока.
    if (app_info.is_all_zone_not_buy) {
        short x = X_MAX / 2;
        short y = Y_MAX / 2;
        short& y_zone = koord.y_place_zone;
        short& x_zone = koord.x_place_zone;
        for (int i = y_zone; i < y * 2; i++) {
            setCursorPosition(x, i);
            cout << "#";
        }
        for (int i = x_zone; i <= x * 2; i++) {
            setCursorPosition(i, y);
            cout << "#";
        }
    }
    inform();
}

// Функия для покупки участков.
void buy_place() {
    app_info.is_in_zone_buy_place = true;
    switch (player_info.place_level) {
    case 0:
        if (GetAsyncKeyState(VK_RETURN) & 0x8000 && player_info.money >= app_info.price_up_level_field[player_info.place_level] && player_info.player_level >= 5) {
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
            cout << "Press 'Enter' if you want to buy this place.";
            if (!was_passed_button()) {
                player_info.money -= app_info.price_up_level_field[player_info.place_level];
                player_info.place_level++;
                koord.y_place_zone = dimension.Y_MAX / 2;
                for (int i = 0; i < dimension.Y_MAX; i++) {
                    setCursorPosition(dimension.X_MAX / 2, i);
                    cout << " ";
                }
            }
        }
        break;
    case 1:
        if (GetAsyncKeyState(VK_RETURN) & 0x8000 && player_info.money >= app_info.price_up_level_field[player_info.place_level] && player_info.player_level >= 10) {
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
            cout << "Press 'Enter' if you want to buy this place.";
            if (!was_passed_button()) {
                player_info.money -= app_info.price_up_level_field[player_info.place_level];
                player_info.place_level++;
                koord.x_place_zone = dimension.X_MAX / 2;
                for (int i = 0; i < dimension.X_MAX; i++) {
                    setCursorPosition(i, dimension.Y_MAX / 2);
                    cout << " ";
                }
            }
        }
        break;
    case 2:
        if (GetAsyncKeyState(VK_RETURN) & 0x8000 && player_info.money >= app_info.price_up_level_field[player_info.place_level] && player_info.player_level >= 15) {
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
            cout << "Press 'Enter' if you want to buy this place.";
            if (!was_passed_button()) {
                player_info.money -= app_info.price_up_level_field[player_info.place_level];
                player_info.place_level++;
                app_info.is_all_zone_not_buy = false;
                for (int i = dimension.Y_MAX / 2; i < dimension.Y_MAX; i++) {
                    setCursorPosition(dimension.X_MAX / 2, i);
                    cout << " ";
                }
                for (int i = dimension.X_MAX / 2; i < dimension.X_MAX; i++) {
                    setCursorPosition(i, dimension.Y_MAX / 2);
                    cout << " ";
                }
            }
        }
        break;
    }
}

// Функция, проверяющая находится ли пользователь
// в зоне, в которой доступна покупка участка.
void if_in_buy_place_zone() {
    // Находится ли в данный момент
    // персонаж в области покупки участка.
    bool is_now_in_zone_buy_place = false;
    if (player_info.place_level == 0 && koord.x_person == (dimension.X_MAX - 1) / 2) {
        bool is_now_in_zone_buy_place = true;
        buy_place();
    }
    else if (player_info.place_level == 1 && koord.x_person < (dimension.X_MAX - 1) / 2
        && koord.y_person == (dimension.Y_MAX - 2) / 2) {
        is_now_in_zone_buy_place = true;
        buy_place();
    }
    else if (player_info.place_level == 2 &&
        ((koord.x_person > (dimension.X_MAX - 1) / 2 && koord.y_person == (dimension.Y_MAX - 2) / 2) ||
            koord.x_person == (dimension.X_MAX - 1) / 2 && (koord.y_person > (dimension.Y_MAX - 1) / 2))) {
        is_now_in_zone_buy_place = true;
        buy_place();
    }
    else if (app_info.is_in_zone_buy_place && !is_now_in_zone_buy_place){
        app_info.is_in_zone_buy_place = false;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "                                                                    ";
    }
}

// Функия для отрисовки данных об игроке.
void inform() {
    short X_MAX = dimension.X_MAX, Y_MAX = dimension.Y_MAX;
    // Стирание предыдущих данных.
    setCursorPosition(X_MAX - 13, Y_MAX);
    cout << "     ";
    setCursorPosition(X_MAX - 20, Y_MAX);
    cout << "money: " << player_info.money;
    setCursorPosition(X_MAX - 13, Y_MAX + 1);
    cout << "     ";
    setCursorPosition(X_MAX - 20, Y_MAX + 1);
    cout << "water: " << player_info.water;
    setCursorPosition(X_MAX - 13, Y_MAX + 2);
    cout << "     ";
    setCursorPosition(X_MAX - 20, Y_MAX + 2);
    cout << fixed;
    cout.precision(0);
    cout << "level: " << player_info.player_level << " (" << player_info.current_exp << "/" << player_info.full_exp << ")";
}