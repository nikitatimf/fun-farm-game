#include "store.h"
#include "storage.h"

// Функция, отрисовывающая магазин.
void draw_store() {
    const short x = koord.X_STORE_POSITION;
    const short y = koord.Y_STORE_POSITION;
    string store[6];
    store[0] = "  /¯¯¯/¯¯|¯¯\\¯¯¯\\";
    store[1] = " /___/___|___\\___\\";
    store[2] = "    |         |";
    store[3] = "   _|_||___*__|_";
    store[4] = "    |         |";
    store[5] = "    |---------|";
    for (int i = 0; i < 6; i++) {
        setCursorPosition(25, 5 + i);
        cout << store[i];
    }
}

// Функция, рисующая меню покупки.
// choice - номер выбранного продукта.
// Возвращает 1 если была нажата клавиша Escape.
short sale_or_buy_goods(short choice) {
    system("cls");
    // 1 - верхняя, левая кнопка.
    // 2 - верхняя, правая кнопка.
    // 3 - нижняя, левая кнопка.
    // 4 - нижняя, правая кнопка.
    // 5 - кнопка "готово".
    short zone = 1;
    // Размеры меню.
    const short X_FIELD_SIZE = 41, Y_FIELD_SIZE = 15;
    // Координаты начала рисовки меню.
    short x_start = 58, y_start = 13;
    // Количество купленных и проданных продуктов.
    short num_buy = 0, num_sale = 0;
    // Сумма купленных и проданных продуктов.
    int sum_buy = 0, sum_sale = 0;
    // Размеры кнопки "Готово".
    short weight_buttonn = 16, height_button = 5;
    // Координаты начала рисовки кнопки "Готово".
    short x_start_button = (dimension.X_MAX - weight_buttonn) / 2,
        y_start_button = y_start + Y_FIELD_SIZE + 3;
    // Символ заполнения линий меню.
    string simbol = "`";
    // Время показа информации в строке информации.
    chrono::time_point<chrono::high_resolution_clock> time;

    // Вывод продукта над которым совершаются манипуляции.
    setCursorPosition(58, 12);
    cout << text.NAME_ARRAY[choice];

    while (true) {
        // Если информация в строке уведомлений держится более
        // 5 секунд - она стирается.
        chrono::seconds time1 = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - time);
        if (time1.count() > 5) {
            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
            cout << "                                    ";
        }
        // Вывод информации о деньгах, уровне и воды.
        inform();
        // Отрисовка кнопки "Готово".
        for (int i = x_start_button; i < x_start_button + weight_buttonn; i++) {
            for (int j = y_start_button; j < y_start_button + height_button; j++) {
                if (i == x_start_button || j == y_start_button || i == x_start_button + weight_buttonn - 1
                    || j == y_start_button + height_button - 1) {
                    setCursorPosition(i, j);
                    cout << simbol;
                }
            }
        }
        // Отрисовка окна.
        for (int x = x_start; x < x_start + X_FIELD_SIZE; x++) {
            for (int y = y_start; y < y_start + Y_FIELD_SIZE; y++) {
                if (x == x_start || x == x_start + X_FIELD_SIZE - 1 || y == y_start + Y_FIELD_SIZE - 1) {
                    setCursorPosition(x, y);
                    cout << "`";
                }
                // Отрисовка вертикальных линий в окне.
                if (x == x_start + 6 || x == x_start + X_FIELD_SIZE - 7) {
                    setCursorPosition(x, y);
                    cout << "`";
                }
                // Отрисовка горизонтальных линии в окне.
                if ((x < x_start + 17 || x > x_start + 23) && (y == y_start + (Y_FIELD_SIZE - 1) / 2 || y == y_start)) {
                    setCursorPosition(x, y);
                    cout << "`";
                }

                // Выделение текущей кнопки жирным.
                switch (zone) {
                case 1:
                    if ((x <= x_start + 6 && (y == y_start || y == y_start + (Y_FIELD_SIZE - 1) / 2)) ||
                        (y < y_start + (Y_FIELD_SIZE - 1) / 2 && (x == x_start || x == x_start + 6))) {
                        setCursorPosition(x, y);
                        cout << "#";
                    }
                    break;
                case 2:
                    if ((x >= x_start + X_FIELD_SIZE - 6 && (y == y_start || y == y_start + (Y_FIELD_SIZE) / 2)) ||
                        (y <= y_start + (Y_FIELD_SIZE - 1) / 2 && (x == x_start + X_FIELD_SIZE - 1 || x == x_start + X_FIELD_SIZE - 7))) {
                        setCursorPosition(x, y);
                        cout << "#";
                    }
                    break;
                case 3:
                    if ((x <= x_start + 6 && (y == y_start + (Y_FIELD_SIZE - 1) / 2 || y == y_start + Y_FIELD_SIZE - 1)) ||
                        (y >= y_start + (Y_FIELD_SIZE - 1) / 2 && (x == x_start || x == x_start + 6))) {
                        setCursorPosition(x, y);
                        cout << "#";
                        simbol = "`";
                    }
                    break;
                case 4:
                    if (x >= x_start + X_FIELD_SIZE - 6 && (y == y_start + (Y_FIELD_SIZE - 1) / 2 || y == y_start + Y_FIELD_SIZE - 1) ||
                        (y >= y_start + (Y_FIELD_SIZE - 1) / 2 && (x == x_start + X_FIELD_SIZE - 7 || x == x_start + X_FIELD_SIZE - 1))) {
                        setCursorPosition(x, y);
                        cout << "#";
                    }
                    break;
                case 5:
                    simbol = "#";
                    break;
                }

            }
        }
        setCursorPosition(x_start + 17, y_start);
        cout << "Покупка";
        setCursorPosition(x_start + 10, y_start + 3);
        cout << "Количество: " << num_buy;
        setCursorPosition(x_start + 10, y_start + 4);
        cout << "Стоимость: " << sum_buy;
        setCursorPosition(x_start + 17, y_start + Y_FIELD_SIZE / 2);
        cout << "Продажа";
        setCursorPosition(x_start + 10, y_start + Y_FIELD_SIZE / 2 + 3);
        cout << "Количество: " << num_sale;
        setCursorPosition(x_start + 10, y_start + Y_FIELD_SIZE / 2 + 4);
        cout << "Стоимость: " << sum_sale;
        setCursorPosition(x_start_button + 5, y_start_button + 2);
        cout << "Готово";
        setCursorPosition(x_start + 3, y_start + Y_FIELD_SIZE / 4);
        cout << "-";
        setCursorPosition(x_start + 3, y_start + 3 * (Y_FIELD_SIZE - 1) / 4);
        cout << "-";
        setCursorPosition(x_start + X_FIELD_SIZE - 4, y_start + Y_FIELD_SIZE / 4);
        cout << "+";
        setCursorPosition(x_start + X_FIELD_SIZE - 4, y_start + 3 * (Y_FIELD_SIZE - 1) / 4);
        cout << "+";
        // Если была нажата кнопка Escape.
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            bool is_escape = false;
            if (!was_passed_button()){
                return 1;
            }
        }
        // Если была нажата кнопка Enter.
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            switch (zone) {
            case 1:
                if (num_buy) {
                    num_buy--;
                    sum_buy += app_info.BUY_PRICE[choice];
                }
                setCursorPosition(x_start + 22, y_start + 3);
                cout << "      ";
                setCursorPosition(x_start + 21, y_start + 4);
                cout << "      ";
                Sleep(30);
                break;
            case 2:
                num_buy++;
                sum_buy -= app_info.BUY_PRICE[choice];
                Sleep(30);
                break;
            case 3:
                if (num_sale) {
                    num_sale++;
                    sum_sale -= app_info.SALE_PRICE[choice];
                }
                setCursorPosition(x_start + 22, y_start + Y_FIELD_SIZE / 2 + 3);
                cout << "      ";
                setCursorPosition(x_start + 21, y_start + Y_FIELD_SIZE / 2 + 4);
                cout << "      ";
                Sleep(30);
                break;
            case 4:
                num_sale--;
                sum_sale += app_info.SALE_PRICE[choice];
                Sleep(30);
                break;
            case 5:
                if (!was_passed_button()) {
                    if (!warehouse_storage(num_buy + num_sale)) {
                        sum_sale = 0;
                        sum_buy = 0;
                        num_sale = 0;
                        num_buy = 0;
                        break;
                    }
                    if (player_info.money - sum_buy + sum_sale >= 0) {
                        if ((choice <= 8) && (player_info.sum_culture[choice] + num_sale + num_buy >= 0)) {
                            player_info.sum_culture[choice] += num_buy + num_sale;
                            player_info.money += sum_sale + sum_buy;
                        }
                        else if ((choice > 8) && (player_info.sum_animal_goods[choice - 8 - 1] + num_sale + num_buy >= 0)) {
                            player_info.sum_animal_goods[choice - 8 - 1] += num_buy + num_sale;
                            player_info.money += sum_sale + sum_buy;
                        }
                        else {
                            setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
                            cout << "Наличие не может быть отрицательным";
                            time = chrono::high_resolution_clock::now();
                        }
                    }
                    else {
                        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
                        cout << "Не хватает денег";
                        time = chrono::high_resolution_clock::now();
                    }
                    sum_sale = 0;
                    sum_buy = 0;
                    num_sale = 0;
                    num_buy = 0;
                    setCursorPosition(x_start + 22, y_start + 3);
                    cout << "      ";
                    setCursorPosition(x_start + 21, y_start + 4);
                    cout << "      ";
                    setCursorPosition(x_start + 22, y_start + Y_FIELD_SIZE / 2 + 3);
                    cout << "      ";
                    setCursorPosition(x_start + 21, y_start + Y_FIELD_SIZE / 2 + 4);
                    cout << "      ";
                    break;
                }
            }
            
        }
        // Если была нажата кнопка "А".
        if ((GetAsyncKeyState(0x41) & 0x8000) && (zone == 2 || zone == 4)) {
            zone--;
        }
        // Если была нажата кнопка "D".
        else if ((GetAsyncKeyState(0x44) & 0x8000) && (zone == 1 || zone == 3)) {
            zone++;
        }
        // Если была нажата кнопка "W".
        else if ((GetAsyncKeyState(0x57) & 0x8000) && (zone == 3 || zone == 4 || zone == 5)) {
            Sleep(100);
            zone -= 2;
        }
        // Если была нажата кнопка "S".
        else if ((GetAsyncKeyState(0x53) & 0x8000) && zone != 5) {
            Sleep(100);
            zone += 2;
            if (zone > 5) {
                zone = 5;
            }
        }
    }
}

// Функция, рисующая меню магазина.
void store_menu() {
    system("cls");
    // Максимальное количество ячеек по горизонтали и вертикали.
    const short x_zone_limit = 7, y_zone_limit = 2;
    // Текущее значение ячейки.
    short x_zone = 1, y_zone = 1;
    // Текущая ячейка.
    short choice = 0;
    while (true) {
        // Отрисовка меню.
        for (int x = 0; x < dimension.X_MAX - 1; x++) {
            for (int y = 0; y < dimension.Y_MAX; y++) {
                // Отрисовка такущей ячейки.
                if ((y == dimension.Y_STORE_MENU_LINE * y_zone - dimension.Y_STORE_MENU_LINE || y == dimension.Y_STORE_MENU_LINE * y_zone)
                    && (x >= dimension.X_STORE_MENU_LINE * (x_zone - 1) && x <= dimension.X_STORE_MENU_LINE * x_zone) ||
                    (x == dimension.X_STORE_MENU_LINE * (x_zone - 1) || x == dimension.X_STORE_MENU_LINE * x_zone)
                    && (y >= dimension.Y_STORE_MENU_LINE * y_zone - dimension.Y_STORE_MENU_LINE && y <= dimension.Y_STORE_MENU_LINE * y_zone)) {
                    setCursorPosition(x, y);
                    cout << "#";
                    continue;
                }
                // Отрисовка остального меню.
                if (x == 0 || x == dimension.X_MAX - 1 ||
                    y == 0 || y == dimension.Y_MAX - 1 ||
                    x % dimension.X_STORE_MENU_LINE == 0 ||
                    y == dimension.Y_STORE_MENU_LINE) {
                    setCursorPosition(x, y);
                    cout << "`";
                }
            }
        }
        // Для растительности.
        for (int i = 0; i < 7; i++) {
            setCursorPosition(4 + dimension.X_STORE_MENU_LINE * i, 1);
            cout << text.NAME_ARRAY[i];
            setCursorPosition(4 + dimension.X_STORE_MENU_LINE * i, 18 - 1);
            cout << "Покупка: " << app_info.BUY_PRICE[i];
            setCursorPosition(4 + dimension.X_STORE_MENU_LINE * i, 19 - 1);
            cout << "Продажа: " << app_info.SALE_PRICE[i];
        }
        // Для животных.
        for (int i = 7; i < 13; i++) {
            setCursorPosition(1 + 3 + dimension.X_STORE_MENU_LINE * (i - 7), 21);
            cout << text.NAME_ARRAY[i];
            setCursorPosition(4 + dimension.X_STORE_MENU_LINE * (i - 7), 38 - 1);
            cout << "Покупка: " << app_info.BUY_PRICE[i];
            setCursorPosition(4 + dimension.X_STORE_MENU_LINE * (i - 7), 39 - 1);
            cout << "Продажа: " << app_info.SALE_PRICE[i];


        }

        setCursorPosition(3, 3);
        cout << "\033[33m     ⣰⢦⡀⠀⠀⡀";
        setCursorPosition(3, 4);
        cout << " ⣀⣤⣄⠀⣇⠀⡇⡔⠋⡇";
        setCursorPosition(3, 5);
        cout << "⠈⠳⣄⣨⠷⠬⣟⠀⣧⠴⡧⠒⢲⠂";
        setCursorPosition(3, 6);
        cout << "  ⣰⠚⢙⣗⣠⡝⢦⡼⠥⢴⡯⣄⣀";
        setCursorPosition(3, 7);
        cout << "⠀⠐⠛⠒⢻⠃⢀⣧⣤⡵⡴⢯⣠⣴⠃";
        setCursorPosition(3, 8);
        cout << "  ⠀⠀⠘⠛⣟⢁⡰⠃⢷⢾⡁⢈⡷⠆";
        setCursorPosition(3, 9);
        cout << "  ⠀⠀⠀⠀⢩⠟⠉⣻⢾⣤⠞⠳⣄⠀";
        setCursorPosition(3, 10);
        cout << "    ⠀⠀⢉⡿⢿⣁⣿⣈⣳⠶⠚⠂";
        setCursorPosition(3, 11);
        cout << "     ⠐⠧⠤⠴⢻⠋⢇⠀⢱";
        setCursorPosition(3, 12);
        cout << "       ⠀⡰⠃⡟⠒⣍⠉⠁";
        setCursorPosition(3, 13);
        cout << "     ⢀⡠⠞⠁⠀⠙⠤⣼";
        setCursorPosition(3, 14);
        cout << " ⢀⡤⠴⠒⠋\033[0m";

        setCursorPosition(25, 3);
        cout << "\033[33m       ⠀⠀⠀⠀⢀⣄⣤⣄";
        setCursorPosition(25, 4);
        cout << "\033[32m    ⠀⢀⠀⠀⠀\033[33m⢠⠾⠩⠠⡣⢛";
        setCursorPosition(25, 5);
        cout << "\033[32m   ⠀⠴⠯⣯⣦\033[33m⡰⠙⠙⠡⢋⠠⢱⠀";
        setCursorPosition(25, 6);
        cout << "\033[32m    ⠀⡘\033[33m⢠⡝⠔⠄⠀⠊⠂⠤⡈";
        setCursorPosition(25, 7);
        cout << "\033[32m   ⡠⢤\033[33m⢈⢍⠂⠈⠐⠃⠄⠰⢠";
        setCursorPosition(25, 8);
        cout << "\033[32m ⠀⠎⠀⢁⢉⠾⢦⡀\033[33m⠎⡰⠄⠠⠇";
        setCursorPosition(25, 9);
        cout << "\033[32m ⢸⠀⡔⠂⠀⠀⡀⢫\033[33m⠠⠁⢢⡌";
        setCursorPosition(25, 10);
        cout << "\033[32m⢀⣿⢾⠁⠀⢠⠀⠃⢸⠀\033[33m⢁⠞\033[32m⢀⠑";
        setCursorPosition(25, 11);
        cout << "\033[32m⠈⠁⡘⠀⠀⡘⠘⡀⢠⢢⡎⠉⣤⡗";
        setCursorPosition(25, 12);
        cout << "\033[32m ⠀⡇⠀⢀⠁⠰⢀⠜⠋⠀⢰⡏";
        setCursorPosition(25, 13);
        cout << "\033[32m ⠀⠰⠀⠈⡠⡠⠊⠀⠀⠀⠘⠁";
        setCursorPosition(25, 14);
        cout << "\033[32m  ⠸⣦⠜⠋";
        setCursorPosition(25, 15);
        cout << "\033[32m ⠘⠐⠚";

        setCursorPosition(51, 3);
        cout << "\033[33m   ⡠⠙⠄";
        setCursorPosition(51, 4);
        cout << "⠀⠀⠀⠈⠀⠊";
        setCursorPosition(51, 5);
        cout << "⡖⠤⡀⢜⠀⣘⢀⡤⢲";
        setCursorPosition(51, 6);
        cout << "⠑⡀⠐⢵⣦⡯⠂⢀⠊";
        setCursorPosition(51, 7);
        cout << "⡬⣰⣄⠀⣭⠁⣠⣆⢥";
        setCursorPosition(51, 8);
        cout << "⠣⠀⠡⣉⡖⣉⠜⠁⠜";
        setCursorPosition(51, 9);
        cout << "⣐⠠⡀⠈⣛⠁⢀⠄⣂";
        setCursorPosition(51, 10);
        cout << "⢇⠉⢏⡂⡭⢐⡹⠉⡸";
        setCursorPosition(51, 11);
        cout << "⠠⢄⠀⠑⠷⠋⠀⡠⠄";
        setCursorPosition(51, 12);
        cout << "⡏⠲⡖⢄⣛⡠⢾⠒⢹";
        setCursorPosition(51, 13);
        cout << "⢈⡀⠈⠡⣿⠌⠁⢀⡡";
        setCursorPosition(51, 14);
        cout << "⠀⠀⢤⡀⠶⢀⡴";
        setCursorPosition(51, 15);
        cout << "⠀⠀⠀⠈⠻⠁⠀⠀";

        setCursorPosition(73, 2);
        cout << "  ⡷⡀⢠";
        setCursorPosition(73, 3);
        cout << "⠸⡀⢧⠹⣄⣆⢀";
        setCursorPosition(73, 4);
        cout << "⢂⢻⠺⢆⡟⠘⣾⠀⡀";
        setCursorPosition(73, 5);
        cout << " ⡮⠧⡀⠃⡰⠉⢧⠁";
        setCursorPosition(73, 6);
        cout << "⢣⡹⡄⠈⠹⠁⠀⡼⢲⢀";
        setCursorPosition(73, 7);
        cout << "⢀⢻⡉⠐⠢⡧⠊⠀⣞⡔⡀";
        setCursorPosition(73, 8);
        cout << "⢠⢳⡳⠤⡀⢠⠀⡰⠋⣿⡀";
        setCursorPosition(73, 9);
        cout << " ⠣⣣⡀⠀⠙⡎⠀⢀⢿⡇";
        setCursorPosition(73, 10);
        cout << " ⠢⡹⡉⠢⢄⠃⡠⠊⣸⡜";
        setCursorPosition(73, 11);
        cout << "  ⠘⡏⢂⡀⢉⠀⡐⢹⠃";
        setCursorPosition(73, 12);
        cout << "   ⠘⣆⠑⢺⠌⠀⡞";
        setCursorPosition(73, 13);
        cout << "    ⠈⢦⡈⣄⠜";
        setCursorPosition(73, 14);
        cout << "      ⠉⡏";
        setCursorPosition(73, 15);
        cout << "       ⡇";
        setCursorPosition(73, 16);
        cout << "      ⢠⠇";

        setCursorPosition(90, 3);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠄⡀";
        setCursorPosition(90, 4);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢄⡨⣒⡡⠐";
        setCursorPosition(90, 5);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠖⡏⢠⢋⡰⡡⠄";
        setCursorPosition(90, 6);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⢀⢤⠊⡉⡰⠮⠉⡍⠏⠂";
        setCursorPosition(90, 7);
        cout << "⠀⠀⠀⠀⠀⠀⠀⡔⠊⢸⣴⢉⣁⠰⠈⡀⢀⠀⠄";
        setCursorPosition(90, 8);
        cout << "⠀⠀⠀⠀⢀⠰⢙⣀⠗⠓⢠⢴⠗⠞⣙⣭⣃⠖⡐⠈";
        setCursorPosition(90, 9);
        cout << "⠀⠀⠀⠀⡎⡰⠬⢉⣩⣫⠧⠞⣚⡩⠥⠒⠚";
        setCursorPosition(90, 10);
        cout << "⠀⠀⠀⢠⢟⡶⠖⠩⠵⠒⠋⠉";
        setCursorPosition(90, 11);
        cout << "⠀⢀⣔⠕⠁";
        setCursorPosition(90, 12);
        cout << "⡠⠋";
        setCursorPosition(90, 13);
        cout << "⠁\033[0m";

        setCursorPosition(113, 3);
        cout << "\033[33m ⣰⢻⣿⣷⣀⠀⠀⠀⠀⣺⣻⠇";
        setCursorPosition(113, 4);
        cout << "\033[32m ⣧⣾\033[33m⠉⠹⡟⠳⣶⣶⠾⣟⣷⣤⡀";
        setCursorPosition(113, 5);
        cout << "\033[32m⡼⠁⣾⠒⠒⢧⡀\033[33m⠀⢹⣇⠈⠁";
        setCursorPosition(113, 6);
        cout << "\033[32m⣿⠄⢿⣇⣀⣀⣇⠀\033[33m⣸⣿⣄";
        setCursorPosition(113, 7);
        cout << "\033[32m⡟⠀⠘⣿⡀⠀⠉⢳⢇\033[33m⣟⡿⠷⠂";
        setCursorPosition(113, 8);
        cout << "\033[32m⢧⡀⡀⢡⢷⠔⠒⠺⢾⡋";
        setCursorPosition(113, 9);
        cout << "⠀⢻⡅⠀⠱⡳⡄⣤⢤⣷⣄";
        setCursorPosition(113, 10);
        cout << "⠀⠘⡆⠀⢀⠘⢜⢦⡀⠀⠙⣷⣄";
        setCursorPosition(113, 11);
        cout << "⠀⠀⠘⠓⢾⠀⠀⠐⢝⣳⣏⡙⠛⣷";
        setCursorPosition(113, 12);
        cout << "⠀⠀⠀⠀⠈⠳⣤⣰⠀⠈⠙⠫⠗⣾⣧⡀";
        setCursorPosition(113, 13);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠙⠶⠶⠶⠶⠿⠿⠇\033[0m";

        setCursorPosition(135, 3);
        cout << "\033[32m ⠀⠀⢠⠊⢽⡉⠷⠄⢀⣤⠄⣄⡀";
        setCursorPosition(135, 4);
        cout << "⣀⣤⣤⠤⣜⣕⠢⣱⢠⣻⠳⡴⡺⡄⢱";
        setCursorPosition(135, 5);
        cout << "⠀⣾⡒⣶⢒⣛⠦⠯⡆⠸⣇⣸⣚⢩⢌⣹⡜";
        setCursorPosition(135, 6);
        cout << "⠀⣾⡒⣶⢒⣛⠦⠯⡆⠸⣇⣸⣚⢩⢌⣹⡜";
        setCursorPosition(135, 7);
        cout << "\033[35m⠀⠀⠀⣀⣤⡤⠤⣠\033[32m⡿⣶⣿⣭⣵⣀⣄⠂⢊⡣";
        setCursorPosition(135, 8);
        cout << "\033[35m⠀⠀⠞⠑⠂⠀⠀⠀⠹⣿\033[32m⠛⠛⢽⠰⣖⢳⢾⠇";
        setCursorPosition(135, 9);
        cout << "\033[35m⠀⠈⡀⠀⠀⠀⠀⠀⠀⢲⠀⠀\033[32m⠘⡖⢱⢸";
        setCursorPosition(135, 10);
        cout << "\033[35m⠀⣤⠇⠀⠀⠀⠀⠰⢾⠜⠀⠀⠀\033[32m⠩⠾⠉";
        setCursorPosition(135, 11);
        cout << "\033[35m⢀⣷⠩⠋⠛⠒⠒⠉⠁";
        setCursorPosition(135, 12);
        cout << "⠹\033[0m";

        setCursorPosition(3, 23);
        cout << "\033[32m ⣾⣞⣆⡀⣠⣤⡄⠀⣀⣀⡀⡼⣿⢲";
        setCursorPosition(3, 24);
        cout << "⣠⡿⣮⣣⣿⣝⡿⠀⠀⢻⣿⢕⣾⣺⣹⢶⣻⣶";
        setCursorPosition(3, 25);
        cout << "⠹⠽⠽⣿⣿⣿⠀⠀⠀⠀⠉⢹⣷⣿⣿⠯⠟⠁";
        setCursorPosition(3, 26);
        cout << "\033[31m⠀⠀⠀⣻⢿⡿\033[31m⠉⢳⠀⠀⢀⠖\033[32m⣿⣿⢿⡁";
        setCursorPosition(3, 27);
        cout << "\033[31m⠀⠀⠀⢧⠐⠀⢀⠹⡀⠀⢸⠐⠂⠀⢲⠇";
        setCursorPosition(3, 28);
        cout << "⠀⠀⠀⠈⢣⠂⠈⠀⣥⠀⢸⠨⠤⠄⡼";
        setCursorPosition(3, 29);
        cout << "⠀⠀⠀⠀⠈⢣⠀⣨⢠⠀⢸⡀⠀⢲⠃";
        setCursorPosition(3, 30);
        cout << " ⠀⠀⠀⠀⠀⢳⠀⠀⡆⢸⠐⠂⡎";
        setCursorPosition(3, 31);
        cout << " ⠀⠀⠀⠀⠀⠀⢱⠉⣥⢸⠠⡼⠁";
        setCursorPosition(3, 32);
        cout << " ⠀⠀⠀⠀⠀⠀⠀⢳⣉⢸⡣⠃\033[0m";

        setCursorPosition(26, 27);
        cout << "\033[33m⠀⠀⠀⣠⠴⠒⠒⠶⠊⠉⠉⣙⠢⣄⡀";
        setCursorPosition(26, 28);
        cout << "⠀⡴⠋⠈⢠⠀⢀⡀⠀⠀⠀⠈⠀⠀⠹⡄";
        setCursorPosition(26, 29);
        cout << "⢸⡃⡀⠀⠈⠀⠀⠀⢀⠀⠀⡀⠀⠸⢃⡇";
        setCursorPosition(26, 30);
        cout << "⠸⣅⠀⠄⠀⠀⠀⠀⡙⠀⡀⠐⠀⢀⡼";
        setCursorPosition(26, 31);
        cout << "⠀⠈⠙⠲⠾⣆⣀⡤⠤⠶⠷⠶⠚⠉\033[0m";

        setCursorPosition(45, 23);
        cout << " ⠀⠀⠀⠀⠀⣠⣤⣀⠀⠀⠀⢦⣤⣄⣀⡀";
        setCursorPosition(45, 24);
        cout << " ⠀⠀⢀⣠⠞⠛⠛⠛⠛⠁⠀⠉⠛⠛⠛⢦⣀";
        setCursorPosition(45, 25);
        cout << "⠀⠀⠀⡾⠱⠷⠀⠀⠀⠀⠀⠀⠛⠃⠀⠀⠀⠙⣆";
        setCursorPosition(45, 26);
        cout << "⠀⠀⣰⠇⠀⠀\033[33m⢀⣼⡶⢿⣿⣿⣷⣶⡀\033[0m⠀⠀⠀⢸⡆";
        setCursorPosition(45, 27);
        cout << "⢀⣼⠏⠀⠀⠀\033[33m⣾⣿⣧⣾⣿⣿⣿⣿⣿⡀\033[0m⠀⣤⠀⢷";
        setCursorPosition(45, 28);
        cout << "⢸⡇⠀⣠⡄⠀\033[33m⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟\033[0m⠛⠀⠀⡾";
        setCursorPosition(45, 29);
        cout << "⠘⣷⠄⠈⠁\033[33m⠀⢿⣿⣿⣿⣿⣿⣿⣿⠿⠀\033[0m⠀⣀⣼⠇";
        setCursorPosition(45, 30);
        cout << "⠀⢿⡄⠀⠀⠀⣀\033[33m⠙⠻⠿⠿⠿⠛⠋⠀\033[0m⠀⢠⣿⠃";
        setCursorPosition(45, 31);
        cout << "⠀⠸⣧⡀⠘⠃⠿⠇⠀⠀⠀⠀⠀⠀⠀⣠⣿⡟";
        setCursorPosition(45, 32);
        cout << "⠀⠀⠈⠛⢷⣶⣶⣦⣄⣀⣠⣤⣦⣶⡾⠟⠉";
        setCursorPosition(45, 33);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠛⠉";

        setCursorPosition(71, 25);
        cout << "⠀    ⠰⠤⠍⠉⣉⣁⠀⠆";
        setCursorPosition(71, 26);
        cout << "⠀⠀⠀⠀⠀⠀⢠⣐⣿⣿⣿⣷⡞⠉⠳⡄";
        setCursorPosition(71, 27);
        cout << "⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⡀⠀⢰⠇";
        setCursorPosition(71, 28);
        cout << "\033[36m⣂⣀⣀⣀\033[37m⠀⢠⣿⣿⣿⣿⣿⣿⣷⣴⡟";
        setCursorPosition(71, 29);
        cout << "\033[36m⣿⣿⣿⡟\033[37m⠀⣿⣿⣿⣿⣿⣿⣿⣿⡇";
        setCursorPosition(71, 30);
        cout << "\033[36m⣿⣿⣿⡇\033[37m⠀⠹⣿⣿⣿⣿⣿⣿⣿⠃";
        setCursorPosition(71, 31);
        cout << "\033[36m⢿⣿⣿⠇\033[37m⠀⠀⠈⢿⣿⣿⣿⠟⠁";

        setCursorPosition(91, 25);
        cout << "⠀⠀⠀⠀⠀⠀    \033[31m⣀⣠⠏⢳⣄";
        setCursorPosition(91, 26);
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀\033[31m⢠⡟⢉\033[37m⣠⡤⠟\033[31m⢈⡳⣄";
        setCursorPosition(91, 27);
        cout << "⠀⠀⠀⠀⠀⠀\033[31m⣠⠶⠚⠀\033[37m⡾⠀\033[31m⡤⠶⠚\033[37m⢀⡽";
        setCursorPosition(91, 28);
        cout << "⠀⠀⠀⠀\033[31m⢀⣰⠇\033[37m⢠⠖⠋\033[31m⢁⡼⠁\033[37m⣴⠚⠋";
        setCursorPosition(91, 29);
        cout << "⠀⠀⠀\033[31m⡞⠉\033[37m⣁⣤⠟\033[31m⢠⡞⢉\033[37m⣠⡴⠃";
        setCursorPosition(91, 30);
        cout << "\033[31m⢀⡴⠞⠁\033[37m⣸⠁\033[31m⣠⠴⠞⠀\033[37m⡾⠁";
        setCursorPosition(91, 31);
        cout << "\033[31m⣏\033[37m⢀⡴⠚⠁\033[31m⣠⠇\033[37m⢠⠖⠋⠁";
        setCursorPosition(91, 32);
        cout << "\033[31m⠙⢮⡀\033[31m⡞⠉\033[37m⣁⣠⠟";
        setCursorPosition(91, 33);
        cout << "\033[31m ⠀⠀⠙⢧\033[37m⣸⠁";

        setCursorPosition(114, 26);
        cout << "\033[36m⠀⠀⠀⠀⠀⠀⣠⠤⠶⣒⣲⢠⣄";
        setCursorPosition(114, 27);
        cout << "⠀⠀⠀⠀⢀⠾⠭⣉⡒⢢⠇⡜⢸⢳⡀";
        setCursorPosition(114, 28);
        cout << "⠀⠀⠀⠀⣬⣁⣒⠲⢬⠏⡸⢠⠃⡜⣷";
        setCursorPosition(114, 29);
        cout << "⠀⠀⠀⠀⢗⠂⠤⡭⢋⠜⡠⢃⡜⢌⡾";
        setCursorPosition(114, 30);
        cout << "⠀⠀⠀⠀⠘⢭⢋⠴⣋⠜⡡⡚⢌⡪⠃";
        setCursorPosition(114, 31);
        cout << "⠀⠀⠀⠀⢀⠬⠗⠮⢥⣮⡱⠬⠊⠁";
        setCursorPosition(114, 32);
        cout << "⠙⠢⠤⠤⠊\033[0m";
        // Если была нажата кнопка Escape.
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            system("cls");
            break;
        }
        // Если была нажата кнопка Enter.
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            sale_or_buy_goods(choice);
            break;
        }
        // Если была нажата кнопка "А".
        else if ((GetAsyncKeyState(0x41) & 0x8000) && x_zone > 1) {
            x_zone--;
            choice--;
            Sleep(10);
        }
        // Если была нажата кнопка "D".
        else if ((GetAsyncKeyState(0x44) & 0x8000) && ((x_zone < x_zone_limit && y_zone == 1) || (x_zone < x_zone_limit - 1 && y_zone == 2))) {
            x_zone++;
            choice++;
            Sleep(100);
        }
        // Если была нажата кнопка "W".
        else if ((GetAsyncKeyState(0x57) & 0x8000) && y_zone > 1) {
            y_zone--;
            choice -= 7;
            Sleep(10);
        }
        // Если была нажата кнопка "S".
        else if ((GetAsyncKeyState(0x53) & 0x8000) && y_zone < y_zone_limit && x_zone != x_zone_limit) {
            y_zone++;
            choice += 7;
            Sleep(100);
        }
    }
}

// Если персонаж находится в области перед магазином.
void if_in_store_area() {
    const short x_area = koord.X_STORE_AREA,
        y_area = koord.Y_STORE_AREA,
        weight = dimension.WEIGHT_STORE_AREA,
        x_person = koord.x_person,
        y_person = koord.y_person;
    bool is_now_near_store = false;
    if (x_person >= x_area && x_person <= x_area + weight
        && y_person == y_area) {
        is_now_near_store = true;
        app_info.is_near_store = true;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "Press 'Enter' to go to the menu.";
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!was_passed_button()) {
                store_menu();
                system("cls");
            }
        }
    }
    else if (app_info.is_near_store && !is_now_near_store) {
        app_info.is_near_store = false;
        setCursorPosition(koord.X_NOTIFICATION, koord.Y_NOTIFICATION);
        cout << "                                    ";
    }
}