#include "animal.h"
#include "field_and_palce.h"

// Функция, улучшающая загон с животными.
// index - индекс загона в массиве структур.
void improve_animal_house(short index) {
    player_info.money -= app_info.price_up_level_animal_house[animals_house[index].level - 1];
    animals_house[index].level++;
    animals_house[index].goods_giving_animal++;
    // Если после улучшения, следующее улучшение недоступно.
    if ((animals_house[index].level == 2 && player_info.player_level <= 8) ||
        (animals_house[index].level == 3 && player_info.player_level <= 12) ||
        (animals_house[index].level == 4)) {
        animals_house[index].chance_improving = false;
    }
}

// Функция, рисующая загон с животными.
void draw_animals_house() {
    char house_animals1[] = " ___";
    char house_animals2[] = "|";
    char house_animals3[] = "    ¯¯¯¯¯¯¯ ";
    for (short i = 0; i < 4; i++) {
        const short x_animals_house = animals_house[i].x_position, 
                    y_animals_house = animals_house[i].y_position;
        // Отрисовка загона.
        setCursorPosition(x_animals_house, y_animals_house);
        cout << animals_house[i].goods << house_animals1 << player_info.num_animals[i] << "/20";
        setCursorPosition(x_animals_house, y_animals_house + 1);
        cout << house_animals2;
        setCursorPosition(x_animals_house + 11, y_animals_house + 1);
        cout << house_animals2;
        setCursorPosition(x_animals_house, y_animals_house + 2);
        cout << house_animals2;
        setCursorPosition(x_animals_house + 11, y_animals_house + 2);
        cout << house_animals2;
        setCursorPosition(x_animals_house, y_animals_house + 3);
        cout << house_animals2;
        setCursorPosition(x_animals_house + 11, y_animals_house + 3);
        cout << house_animals2;
        setCursorPosition(x_animals_house, y_animals_house + 4);
        cout << house_animals2;
        setCursorPosition(x_animals_house + 11, y_animals_house + 4);
        cout << house_animals2;

        chrono::seconds time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - animals_house[i].anim_clock);
        // Отрисовка уровня загона.
        for (int k = 0; k < animals_house[i].level; k++) {
            setCursorPosition(x_animals_house + k, y_animals_house + 4);
            cout << "\033[33m*\033[0m";
        }
        setCursorPosition(x_animals_house, y_animals_house + 5);
        cout << house_animals3;
        // Отрисовка оставшегося времени.
        if (animals_house[i].busy_animal) {
            cout << "\b\b\b\b\b" << (animals_house[i].animal_time - time.count()) / 60 << ":";
            if ((animals_house[i].animal_time - time.count()) % 60 < 10) {
                cout << "0" << (animals_house[i].animal_time - time.count()) % 60;
            }
            else {
                cout << (animals_house[i].animal_time - time.count()) % 60;
            }
        }

    }
}

// Функция, работающая со временем загона.
void animal_goods() {
    for (int i = 0; i < 4; i++) {
        // Если животные покормлены.
        if (player_info.num_animals[i] > 0 && !animals_house[i].busy_animal && !animals_house[i].goods_in_house && animals_house[i].animals_eaten) {
            animals_house[i].anim_clock = chrono::high_resolution_clock::now();
            animals_house[i].animals_eaten = false;
            animals_house[i].busy_animal = true;
        }
        // Если животные звакончили работу.
        chrono::seconds time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - animals_house[i].anim_clock);
        if (player_info.num_animals[i] > 0 && time.count() >= animals_house[i].animal_time &&
            animals_house[i].busy_animal && !animals_house[i].goods_in_house) {
            animals_house[i].goods += animals_house[i].goods_giving_animal * player_info.num_animals[i];
            animals_house[i].busy_animal = false;
            animals_house[i].goods_in_house = true;
        }
    }
}

// Функция, рисующая меню кормления животных.
// num - индекс животного в массиве.
// Возвращает 0 - если животное было покормлено
// 1 - если нет.
short feed_the_animals(int num) {
    system("cls");
    int x_start_window = koord.X_ANIMALS_MENU,
        y_start_window = koord.Y_ANIMALS_MENU;
    short x_curs_pos = koord.X_ANIMALS_MENU + dimension.X_SIZE_ANIMALS_MENU - 4;
    short y_curs_pos = koord.Y_ANIMALS_MENU + dimension.Y_SIZE_ANIMALS_MENU - 5;
    while (true) {
        // Отрисовка рамки меню.
        for (short x = koord.X_FEED_THE_ANIMALS_MENU; x < dimension.X_SIZE_FEED_THE_ANIMALS_MENU + koord.X_FEED_THE_ANIMALS_MENU; x++) {
            for (short y = koord.Y_ANIMALS_MENU; y < text.MAX_NUM_FOOD + koord.Y_ANIMALS_MENU + 2; y++) {
                if (x == koord.X_ANIMALS_MENU || y == koord.Y_ANIMALS_MENU ||
                    x == koord.X_ANIMALS_MENU + dimension.X_SIZE_ANIMALS_MENU - 1 ||
                    y == koord.Y_ANIMALS_MENU + text.MAX_NUM_FOOD + 1) {
                    setCursorPosition(x, y);
                    cout << "#";
                }
            }
        }
        // Вывод над рамкой заголовка с указанием животного.
        switch (num) {
        case 0:
            for (int i = 0; i < text.NUM_CHICKEN_FOOD; i++) {
                setCursorPosition(koord.X_ANIMALS_MENU + 1, koord.Y_ANIMALS_MENU + i + 1);
                cout << text.CHICKEN_FOOD[i] << " - " << player_info.sum_culture[find_elem(text.CHICKEN_FOOD[i], text.string_culture)];
            }
            break;
        case 1:
            for (int i = 0; i < text.NUM_PIG_FOOD; i++) {
                setCursorPosition(koord.X_ANIMALS_MENU + 1, koord.Y_ANIMALS_MENU + i + 1);
                cout << text.PIG_FOOOD[i] << " - " << player_info.sum_culture[find_elem(text.PIG_FOOOD[i], text.string_culture)];;
            }
            break;
        case 3:
            for (int i = 0; i < text.NUM_SHEEP_FOOD; i++) {
                setCursorPosition(koord.X_ANIMALS_MENU + 1, koord.Y_ANIMALS_MENU + i + 1);
                cout << text.SHEEP_FOOD[i] << " - " << player_info.sum_culture[find_elem(text.SHEEP_FOOD[i], text.string_culture)];;
            }
            break;
        }
        setCursorPosition(x_curs_pos, y_curs_pos);
        cout << "<-";
        // Управление стрекой.
        switch (num) {
        case 0:
            // Если нажата кнопка "W" стрелка двигается вверх.
            if ((GetAsyncKeyState(0x57) & 0x0001) && y_curs_pos > koord.Y_ANIMALS_MENU + 1) {
                if (!was_passed_button()) {
                    y_curs_pos--;
                    setCursorPosition(x_curs_pos, y_curs_pos + 1);
                    // Закрашивание предыдущей стрелки.
                    cout << "  ";
                }
            }
            // Если нажата кнопка "S" стрелка двигается вверх.
            else if ((GetAsyncKeyState(0x53) & 0x0001) && y_curs_pos < koord.Y_ANIMALS_MENU + text.NUM_CHICKEN_FOOD) {
                if (!was_passed_button()) {
                    y_curs_pos++;
                    setCursorPosition(x_curs_pos, y_curs_pos - 1);
                    cout << "  ";
                }
            }
            break;
        case 1:
            // Если нажата кнопка "W" стрелка двигается вверх.
            if ((GetAsyncKeyState(0x57) & 0x8000) && y_curs_pos > koord.Y_ANIMALS_MENU + 1) {
                if (!was_passed_button()) {
                    y_curs_pos--;
                    setCursorPosition(x_curs_pos, y_curs_pos + 1);
                    cout << "  ";
                }
            }
            // Если нажата кнопка "S" стрелка двигается вверх.
            else if ((GetAsyncKeyState(0x53) & 0x8000) && y_curs_pos < koord.Y_ANIMALS_MENU + text.NUM_PIG_FOOD) {
                if (!was_passed_button()) {
                    y_curs_pos++;
                    setCursorPosition(x_curs_pos, y_curs_pos - 1);
                    cout << "  ";
                }
            }
            break;
        case 3:
            // Если нажата кнопка "W" стрелка двигается вверх.
            if ((GetAsyncKeyState(0x57) & 0x8000) && y_curs_pos > koord.Y_ANIMALS_MENU + 1) {
                if (!was_passed_button()) {
                    y_curs_pos--;
                    setCursorPosition(x_curs_pos, y_curs_pos + 1);
                    cout << "  ";
                }
            }
            // Если нажата кнопка "V" стрелка двигается вверх.
            else if ((GetAsyncKeyState(0x53) & 0x8000) && y_curs_pos < koord.Y_ANIMALS_MENU + text.NUM_SHEEP_FOOD) {
                if (!was_passed_button()) {
                    y_curs_pos++;
                    setCursorPosition(x_curs_pos, y_curs_pos - 1);
                    cout << "  ";
                }
            }
            break;
        }


        // Если нажата Escape - выход из меню.
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            if (!was_passed_button()) {
                system("cls");
            }
            break;
        }
        // Если нажата Enter - выбор соответствующего пункта.
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            switch (num) {
                // Если игрок находится в загоне с курицами.
                // Каждый из внутренних case указывает на тот или иной раститительный продукт.
            case 0:
                switch (y_curs_pos) {
                case 18:
                    if (player_info.sum_culture[find_elem(text.CHICKEN_FOOD[0], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.CHICKEN_FOOD[0], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 19:
                    if (player_info.sum_culture[find_elem(text.CHICKEN_FOOD[1], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.CHICKEN_FOOD[1], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 20:
                    if (player_info.sum_culture[find_elem(text.CHICKEN_FOOD[2], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.CHICKEN_FOOD[2], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                }
                break;
                // Если игрок находится в загоне со свиньями.
            case 1:
                switch (y_curs_pos) {
                case 18:
                    if (player_info.sum_culture[find_elem(text.PIG_FOOOD[0], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.PIG_FOOOD[0], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 19:
                    if (player_info.sum_culture[find_elem(text.PIG_FOOOD[1], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.PIG_FOOOD[1], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 20:
                    if (player_info.sum_culture[find_elem(text.PIG_FOOOD[2], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.PIG_FOOOD[2], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 21:
                    if (player_info.sum_culture[find_elem(text.PIG_FOOOD[3], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.PIG_FOOOD[3], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 22:
                    if (player_info.sum_culture[find_elem(text.PIG_FOOOD[4], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.PIG_FOOOD[4], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 23:
                    if (player_info.sum_culture[find_elem(text.PIG_FOOOD[5], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.PIG_FOOOD[5], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                }
                break;
                // Если игрок находится в загоне с овечками.
            case 3:
                switch (y_curs_pos) {
                case 18:
                    if (player_info.sum_culture[find_elem(text.SHEEP_FOOD[0], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.SHEEP_FOOD[0], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 19:
                    if (player_info.sum_culture[find_elem(text.SHEEP_FOOD[1], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.SHEEP_FOOD[1], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 20:
                    if (player_info.sum_culture[find_elem(text.SHEEP_FOOD[2], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.SHEEP_FOOD[2], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 21:
                    if (player_info.sum_culture[find_elem(text.SHEEP_FOOD[3], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.SHEEP_FOOD[3], text.string_culture)]--;
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                case 22:
                    if (player_info.sum_culture[find_elem(text.SHEEP_FOOD[4], text.string_culture)] >= player_info.num_animals[num] &&
                        !animals_house[num].animals_eaten) {
                        player_info.sum_culture[find_elem(text.SHEEP_FOOD[4], text.string_culture)] -= player_info.num_animals[num];
                        animals_house[num].animals_eaten = true;
                    }
                    break;
                }
                break;
            }
            // Если животное покормлено - выход из меню.
            if (animals_house[num].animals_eaten) {
                system("cls");
                return 0;
            }
        }
    }
    return 1;
}

// Функция, рисующая и отвечающая за функционал меню загона с животными.
// num - индекс животного в массиве.
// Возвращает 0 - если животное было покормлено.
short animals_house_menu(int num) {
    system("cls");
    const short y_max = dimension.Y_MAX;
    const short x_max = dimension.X_MAX;
    int x_start_window = koord.X_ANIMALS_MENU,
        y_start_window = koord.Y_ANIMALS_MENU;
    short x_curs_pos = koord.X_ANIMALS_MENU + dimension.X_SIZE_ANIMALS_MENU - 4;
    short y_curs_pos = koord.Y_ANIMALS_MENU + dimension.Y_SIZE_ANIMALS_MENU - 5;
    while (true) {
        // Отрисовка рамки меню.
        for (short x = x_start_window; x < dimension.X_SIZE_ANIMALS_MENU + koord.X_ANIMALS_MENU; x++) {
            for (short y = y_start_window; y < dimension.Y_SIZE_ANIMALS_MENU + koord.Y_ANIMALS_MENU; y++) {
                if (x == x_start_window || y == y_start_window ||
                    x == x_start_window + dimension.X_SIZE_ANIMALS_MENU - 1 ||
                    y == y_start_window + dimension.Y_SIZE_ANIMALS_MENU - 1) {
                    setCursorPosition(x, y);
                    cout << "#";
                }
            }
        }
        inform();
        short x_zag = x_start_window + (dimension.X_SIZE_ANIMALS_MENU - text.STRLEN_ZAG_ANIM[num]) / 2;
        // Отрисовка пунктов меню.
        setCursorPosition(x_zag, y_start_window - 1);
        cout << text.head_animals_menu[num];
        setCursorPosition(x_start_window + 1, y_start_window + 1);
        cout << "Купить " << text.BUY_ANIMALS[num] << " " << player_info.num_animals[num]<<"/20" << "      price: " << app_info.animals_price[num];
        setCursorPosition(x_start_window + 1, y_start_window + 2);
        cout << "Покормить " << text.BUY_ANIMALS[num];
        setCursorPosition(x_start_window + 1, y_start_window + 3);
        cout << "Собрать " << text.AMIMAL_GOODS[num] << " " << animals_house[num].goods;
        

        setCursorPosition(x_curs_pos, y_curs_pos);
        cout << "<-";
        // Управление курсором меню.
        // Если нажата клавиша "W" - стрелка поднимается вверх.
        if ((GetAsyncKeyState(0x57) & 0x8000) && y_curs_pos > y_start_window + 1) {
            if (!was_passed_button()) {
                y_curs_pos--;
                setCursorPosition(x_curs_pos, y_curs_pos + 1);
                // Стирание предыдущей стрелки.
                cout << "  ";
            }
        }
        // Если нажата клавиша "S" - стрелка поднимается вверх.
        else if ((GetAsyncKeyState(0x53) & 0x8000) && y_curs_pos < y_start_window + dimension.Y_SIZE_ANIMALS_MENU - 3) {
            if (!was_passed_button()) {
                y_curs_pos++;
                setCursorPosition(x_curs_pos, y_curs_pos - 1);
                cout << "  ";
            }
        }
        // Если была нажата клавиша Enter - выбирается соответствующий пункт меню.
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!was_passed_button()) {
                switch (y_curs_pos) {
                    // Пункт "Купить животное".
                case 18:
                    if (player_info.num_animals[num] < 20 && player_info.money >= app_info.animals_price[num]) {
                        player_info.money -= app_info.animals_price[num];
                        player_info.num_animals[num]++;
                        system("cls");
                    }
                    else if (player_info.num_animals[num] >= 20) {
                        system("cls");
                        cout << "Больше некуда.";
                        Sleep(2000);
                        system("cls");
                    }
                    else if (player_info.money < app_info.animals_price[num]) {
                        system("cls");
                        cout << "Подзаработай еще немного денег.";
                        Sleep(2000);
                        system("cls");
                    }

                    break;
                    // Пункт "Кормить животное".
                case 19:
                    if (!animals_house[num].busy_animal && !animals_house[num].goods_in_house && !animals_house[num].animals_eaten && player_info.num_animals[num] > 0) {
                        if (num != 2 && !feed_the_animals(num)) {
                            return 0;
                        }
                    }
                    break;
                    // Пункт "Собрать животные продукты".
                case 20:
                    if (animals_house[num].goods_in_house) {
                        player_info.sum_animal_goods[num] += animals_house[num].goods;
                        animals_house[num].goods = 0;
                        animals_house[num].goods_in_house = false;
                        setCursorPosition(x_start_window + 13, y_start_window + 3);
                        new_level("anim", player_info.num_animals[num]);
                        cout << "    ";
                    }
                    break;
                }
            }
        }
        // Если нажата клавиша Escape - выход из меню.
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            system("cls");
            break;
        }
    }
}

// Функция, проверяющая, находится ли персонаж внутри загона с животными.
void if_in_animals_house() {
    const short x_person = koord.x_person;
    const short y_person = koord.y_person;
    const short HEIGHT = dimension.ANIMALS_HOUSE_HEIGHT;
    const short WEIGHT = dimension.ANIMALS_HOUSE_WEIGHT;
    // Переменная, хранящая значение, находится ли
    // в данный момент персонаж в загоне для животных.
    bool is_now_in_animals_house = false;
    for (int i = 0; i < 4; i++) {
        if (x_person > animals_house[i].x_position &&
            x_person < animals_house[i].x_position + WEIGHT &&
            y_person > animals_house[i].y_position &&
            y_person < animals_house[i].y_position + HEIGHT) {
            is_now_in_animals_house = true;
            app_info.is_in_animal_house = true;
            // Если была нажата клавиша Enter.
            if (GetAsyncKeyState(VK_RETURN) && !animals_house[i].busy_animal) {
                if (!was_passed_button()) {
                    animals_house_menu(i);
                }
            }
            // Если есть возможность улучшения.
            if (animals_house[i].chance_improving) {
                setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION + 1);
                cout << "Enter 'q' to impovr garden level. Price: " << app_info.price_up_level_animal_house[animals_house[i].level - 1];
                // Если была нажата клавиша "Q" и денег на улучшение хватает.
                if (GetAsyncKeyState(0x51) & 0x8000 && player_info.money >= app_info.price_up_level_animal_house[animals_house[i].level - 1]) {
                    if (!was_passed_button()) {
                        improve_animal_house(i);
                    }
                }
                // Если была нажата клавиша "Q" и денег на улучшение не хватает.
                else if (GetAsyncKeyState(0x51) & 0x8000 && player_info.money < app_info.price_up_level_animal_house[animals_house[i].level - 1]) {
                    system("cls");
                    cout << "Подзаработайте еще " << app_info.price_up_level_animal_house[animals_house[i].level - 1] - player_info.money << " денег";
                    Sleep(2000);
                    system("cls");
                }
            }
        }
    }
    if (is_now_in_animals_house) {
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "Press 'Enter' to go to the menu";
    }
    else if (!is_now_in_animals_house && app_info.is_in_animal_house) {
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "                                             ";
        app_info.is_in_animal_house = false;
    }
}