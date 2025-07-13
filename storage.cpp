#include "storage.h"

// Проверяет возможность добавления продуктов в склад.
// add - кол-во добавляемых продуктов.
// Если места для добавления не достаточно - возвращается 0,
// иначе - 1.
short warehouse_storage(short add) {
    short num_goods = 0;
    // Находится сумма продуктов.
    for (int i = 0; i < 9; i++) {
        num_goods += player_info.sum_culture[i];
        if (i < 4) {
            num_goods += player_info.sum_animal_goods[i];
        }
    }
    // Проверка на вместимость.
    if (num_goods + add >= app_info.warehouse_storage) {
        app_info.is_free_storage = false;
        system("cls");
        cout << "Storage is full";
        Sleep(2000);
        system("cls");
        return 0;
    }
    return 1;

}

// Функия, улучшающая уровень склада.
void improve_storage() {
    // Списание денег за улучшение.
    player_info.money -= app_info.price_up_level_storage[app_info.storage_level - 1];
    // Увеличение уровня и вместимости склада.
    app_info.storage_level++;
    app_info.warehouse_storage *= 1.5;
    // Проверка на возможность дальнейшего улучшения.
    if ((app_info.storage_level == 1 && player_info.player_level <= 6) ||
        (app_info.storage_level == 2 && player_info.player_level <= 12) ||
        (app_info.storage_level == 3 && player_info.player_level <= 18) ||
        (app_info.storage_level == 4 && player_info.player_level <= 18) ||
        (app_info.storage_level == 5 && player_info.player_level <= 24) ||
        app_info.storage_level == 6) {
        app_info.chance_improve_storage = false;
    }
}

// Функция, отображающая меню склада.
void storage_menu() {
    system("cls");
    const short& Y_MAX = dimension.Y_MAX;
    const short& X_MAX = dimension.X_MAX;
    while (true) {
        for (int y = 0; y < Y_MAX; y++) {
            for (int x = 0; x < X_MAX; x++) {
                if (y == 0 || x == 0 ||
                    y == Y_MAX - 1 || x == X_MAX - 1) {
                    setCursorPosition(x, y);
                    cout << '#';
                }
            }
        }
        // Вывод количества растительных культур.
        for (int i = 0; i < 9; i++) {
            setCursorPosition(2, 1 + i);
            cout << text.string_culture[i] << " - " << player_info.sum_culture[i];
        }
        // Вывод количества животных продуктов.
        for (int i = 0; i < 4; i++) {
            setCursorPosition(2, 10 + i);
            cout << text.AMIMAL_GOODS[i] << " - " << player_info.sum_animal_goods[i];
        }
        // При нажатии клавиши Escape, меню закрывается.
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            system("cls");
            break;
        }
    }
}

// Функция, рисующая склад.
void drawing_storage() {
    const short& Y_STORAGE = koord.Y_STORAGE;
    const short& X_STORAGE = koord.X_STORAGE;
    char storage1[] = "      ______";
    char storage2[] = "|/          \\|";
    char storage3[] = "|            |";
    setCursorPosition(X_STORAGE, Y_STORAGE);
    cout << storage1;
    setCursorPosition(X_STORAGE + 2, Y_STORAGE + 1);
    cout << storage2;
    setCursorPosition(X_STORAGE + 2, Y_STORAGE + 2);
    cout << storage3;
    setCursorPosition(X_STORAGE + 2, Y_STORAGE + 3);
    cout << storage3;

    // Цикл для подсчета заполненности склада.
    short num_goods = 0;
    for (int i = 0; i < 9; i++) {
        num_goods += player_info.sum_culture[i];
        if (i < 4) {
            num_goods += player_info.sum_animal_goods[i];
        }
    }
    // Вывод заполненности склада.
    setCursorPosition(X_STORAGE + 12, Y_STORAGE);
    cout << num_goods << "/" << app_info.warehouse_storage;
    // Вывод уровня склада.
    for (int i = 0; i < app_info.storage_level; i++) {
        setCursorPosition(X_STORAGE + i, Y_STORAGE);
        cout << "\033[33m*\033[0m";
    }
}

// Функцич, проверяющая находится ли персонаж в области, перед складом.
void if_in_storage() {
    const short& Y_STORAGE = koord.Y_STORAGE;
    const short& X_STORAGE = koord.X_STORAGE;

    short& y_person = koord.y_person;
    short& x_person = koord.x_person;
    // Проверка на то, стоит ли персонаж в области перед складом.
    bool is_now_near_storage = false;
    if (x_person > X_STORAGE + 2 && x_person < X_STORAGE + 15 &&
        y_person == Y_STORAGE + 4) {
        is_now_near_storage = true;
        app_info.is_near_storage = true;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "Press 'Enter' to open menu.";
        // Есди нажата и отпущена клавиша Enter, открывается
        // меню склада.
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!was_passed_button()) {
                system("cls");
                storage_menu();
            }
        }
        // Если доступно улучшение склада.
        if (app_info.chance_improve_storage) {
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION + 1);
            cout << "Enter 'q' to impove storage level. Price: " << app_info.price_up_level_storage[app_info.storage_level - 1];
            // Если нажата клавиша "Q" и у игрока достаточно денег.
            if ((GetAsyncKeyState(0x51) & 0x8000) && player_info.money >= app_info.price_up_level_storage[app_info.storage_level - 1]) {
                if (!was_passed_button()) {
                    improve_storage();
                }
            }
            // Если нажата клавиша "Q" и у игрока не достаточно денег.
            else if (GetAsyncKeyState(0x51) & 0x8000 && player_info.money < app_info.price_up_level_storage[app_info.storage_level - 1]) {
                system("cls");
                cout << "Подзаработайте еще " << app_info.price_up_level_storage[app_info.storage_level - 1] - player_info.money << " денег";
                Sleep(2000);
                system("cls");
            }
        }
    }
    else if (app_info.is_near_storage && !is_now_near_storage) {
        app_info.is_near_storage = false;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "                                 ";
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION+1);
        cout << "                                                       ";
    }
}