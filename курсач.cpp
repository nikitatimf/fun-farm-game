#include <iostream>
#include <random>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;

void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_CURSOR_INFO cursoreInfo;
    //GetConsoleCursorInfo(hConsole, &cursoreInfo);
    //cursoreInfo.bVisible = false;
    //SetConsoleCursorInfo(hConsole, &cursoreInfo);
    COORD position = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, position);
}

struct kkord {
    short y_person = 5, x_person = 5;
    const short y_max = 40, x_max = 156;
    short y_zone = 0, x_zone = 0;
    const short y_well=10, x_well=50;
    const short y_storage = 10, x_storage = 80;
    const short y_notification = y_max, x_notification = 0;
    const short weight = 8, height = 4;
    const short x_size_plant_menu = 50, y_size_plant_menu = 11;
    const short x_plant_menu = x_max / 2 - x_size_plant_menu / 2;
    const short y_plant_menu = y_max / 2 - y_size_plant_menu / 2;
    short x_curs_pos = 98, y_curs_pos = 16;
    
    const short x_animals_house = 5, y_animals_house = 5;
    const short x_size_animals_house = 10, y_size_animals_house = 5;
    const short an_house_weight = 11, an_house_height = 5;
}koord;

struct player_info {
    short money = 1000;
    short level = 0;
    short water = 10;
    int sum_culture[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
}player_info;

struct app_info {
    bool zone = true;
    bool well_water = true;
    short perez_wel = 1;
    char well = '1';
    bool start_koord_garden = true;
    chrono::time_point<chrono::high_resolution_clock> well_time;
    short time_plant_garden[9] = { 300, 450, 345, 330, 240, 240, 330, 360, 330 };
    string string_culture[9] = { "Овес", "Кукуруза", "Пшеница", "Ячмень", "Просо", "Горох",
        "Свекла", "Морковь", "Кaртофель" };
    const short kolvo_animal = 5;
}app_info;

struct garden {
    short x_position = 0, y_position = 0;
    string area = "     ";
    chrono::time_point<chrono::high_resolution_clock> g_clock;
    bool ifplant = false;
    enum culture {
        Овес,
        Кукуруза,
        Пшеница, 
        Ячмень, 
        Просо, 
        Горох,
        Свекла, 
        Морковь,
        Кaртофель
    }culture1;
    
}garden[20] = {};

struct animals_house {
    const short x_position = 5, y_position = 5;
}animals_house[5] = {};

void koord_garden() {
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
}

void storage_menu() {
    system("cls");
    const short& y_max = koord.y_max;
    const short& x_max = koord.x_max;
    while (true) {
        for (int y = 0; y < y_max; y++) {
            for (int x = 0; x < x_max; x++) {
                if (y == 0 || x == 0 ||
                    y == y_max - 1 || x == x_max - 1) {
                    setCursorPosition(x, y);
                    cout << '#';
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            setCursorPosition(2, 1+i);
            cout << app_info.string_culture[i] << " - " << player_info.sum_culture[i];
        }
        if (_kbhit()) {
            char input = _getch();
            if (input == '1') {
                system("cls");
                break;
            }
        }
    }
}

void drawing_well() {
    const short& y_well = koord.y_well;
    const short& x_well = koord.x_well;
    char well1[] = "  / \\ ";
    char well2[] = "/_____\\ ";
    char well3[] = " || ||  ";
    setCursorPosition(x_well, y_well);
    cout << well1;
    setCursorPosition(x_well, y_well+1);
    cout << well2;
    setCursorPosition(x_well, y_well+2);
    cout << well3;
    
}

void water_in_wel() {
    bool water = true;
    setCursorPosition(koord.x_well + 3, koord.y_well - 1);
    cout << (app_info.well_water ? app_info.well : ' ');
    if (koord.x_person > koord.x_well && koord.x_person < koord.x_well + 6 &&
        koord.y_person == koord.y_well + 3) {
        setCursorPosition(koord.x_notification, koord.y_notification);
        cout << "Enter 1 if you want to take water.";
        char input;
        if (_kbhit()) {
            input = _getch();
            if (input == '1' && app_info.well_water) {
                player_info.water++;
                app_info.well_time = chrono::high_resolution_clock::now();
                app_info.well_water = false;
            }
        }
    }
    chrono::seconds time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - app_info.well_time);
    if (time.count() == app_info.perez_wel && !app_info.well_water) {
        app_info.well_water = true;
    }
}

void drawing_storage() {
    const short& y_storage = koord.y_storage;
    const short& x_storage = koord.x_storage;

    short& y_person = koord.y_person;
    short& x_person = koord.x_person;

    char storage1[] = "___________________";
    char storage2[] = "|/          \\|";
    char storage3[] = "|            |";
    setCursorPosition(x_storage, y_storage);
    cout << storage1;
    setCursorPosition(x_storage+2, y_storage+1);
    cout << storage2;
    setCursorPosition(x_storage+2, y_storage+2);
    cout << storage3;
    setCursorPosition(x_storage+2, y_storage+3);
    cout << storage3;
    if (x_person > x_storage + 2 && x_person < x_storage + 15 &&
        y_person == y_storage+4 ) {
        setCursorPosition(koord.x_notification, koord.y_notification);
        cout << "Нажмите 1";
        char input;
        if (_kbhit()) {
            input = _getch();
            if (input == '1') {
                storage_menu();
            }
        }
    }
}

void control() {
    short& y_person = koord.y_person;
    short& x_person = koord.x_person;
    const short& y_max = koord.y_max;
    const short& x_max = koord.x_max;
    char input;
    if (_kbhit()) {
        input = _getch();
        switch (player_info.level) {
        case 0:
            if (input == 'w' && y_person > 1) {
                y_person--;
                setCursorPosition(x_person, y_person + 1);
                cout << ' ';
            }
            if (input == 's' && y_person < y_max - 2&&y_person < (y_max-1)/2) {
                y_person++;
                setCursorPosition(x_person, y_person - 1);
                cout << ' ';
            }
            if (input == 'd' && x_person < (x_max-1)/2) {
                x_person++;
                setCursorPosition(x_person - 1, y_person);
                cout << ' ';
            }
            if (input == 'a' && x_person > 1) {
                x_person--;
                setCursorPosition(x_person + 1, y_person);
                cout << ' ';
            }
            break;
        case 1:
            if (input == 'w' && y_person > 1) {
                y_person--;
                setCursorPosition(x_person, y_person + 1);
                cout << ' ';
            }
            if (input == 's' && y_person < y_max - 2 && y_person < (y_max - 1) / 2) {
                y_person++;
                setCursorPosition(x_person, y_person - 1);
                cout << ' ';
            }
            if (input == 'd' && x_person < x_max - 2) {
                x_person++;
                setCursorPosition(x_person - 1, y_person);
                cout << ' ';
            }
            if (input == 'a' && x_person > 1) {
                x_person--;
                setCursorPosition(x_person + 1, y_person);
                cout << ' ';
            }
            break;
        case 2:
            if (input == 'w' && y_person > 1) {
                y_person--;
                setCursorPosition(x_person, y_person + 1);
                cout << ' ';
            }
            if (input == 's') {
                if (y_person < y_max - 2 && x_person < x_max / 2+1) {
                    y_person++;
                    setCursorPosition(x_person, y_person - 1);
                    cout << ' ';
                }
                else if (y_person < (y_max-1) / 2 && x_person > x_max / 2) {
                    y_person++;
                    setCursorPosition(x_person, y_person - 1);
                    cout << ' ';
                }
            }
            if (input == 'd' && x_person < x_max - 2) {
                if (y_person < (y_max - 1) / 2 + 1) {
                    x_person++;
                    setCursorPosition(x_person - 1, y_person);
                    cout << ' ';
                }
                else if (y_person > (y_max - 1) / 2 && x_person < (x_max-1) / 2) {
                    x_person++;
                    setCursorPosition(x_person - 1, y_person);
                    cout << ' ';
                }
            }
            if (input == 'a' && x_person > 1) {
                x_person--;
                setCursorPosition(x_person + 1, y_person);
                cout << ' ';
            }
            break;
        case 3:
            if (input == 'w' && y_person > 1) {
                y_person--;
                setCursorPosition(x_person, y_person + 1);
                cout << ' ';
            }
            if (input == 's' && y_person < y_max - 2) {
                
                y_person++;
                setCursorPosition(x_person, y_person - 1);
                cout << ' ';
            }
            if (input == 'd' && x_person < x_max - 2) {
                x_person++;
                setCursorPosition(x_person - 1, y_person);
                cout << ' ';
            }
            if (input == 'a' && x_person > 1) {
                x_person--;
                setCursorPosition(x_person + 1, y_person);
                cout << ' ';
            }
            break;
        }
        
    }
}

void drawing_zone() {
    if (app_info.zone) {
        short x = koord.x_max / 2;
        short y = koord.y_max / 2;
        short& y_zone = koord.y_zone;
        short& x_zone = koord.x_zone;
        for (int i = y_zone; i < y * 2; i++) {
            setCursorPosition(x, i);
            cout << "#";
        }
        for (int i = x_zone; i <= x * 2; i++) {
            setCursorPosition(i, y);
            cout << "#";
        }
    }

}

void drawing_field() {
    const short& y_max = koord.y_max;
    const short& x_max = koord.x_max;

    short& y_person = koord.y_person;
    short& x_person = koord.x_person;
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            if (y == 0 || x == 0 || y == y_max-1 || x == x_max-1) {
                setCursorPosition(x, y);
                cout << '#';
            }
            else if (y == y_person && x == x_person) {
                setCursorPosition(x, y);
                cout << '@';
            }
        }
    }
    setCursorPosition(x_max-20,y_max);
    cout << "money: " << player_info.money;
    setCursorPosition(x_max - 13, y_max + 1);
    cout << "     ";
    setCursorPosition(x_max - 20, y_max+1);
    cout << "water: " << player_info.water;
}

void buy_place() {
    char choise;
    switch (player_info.level) {
    case 0:
        setCursorPosition(koord.x_notification, koord.y_notification);
        cout << "Enter '1' if you want to buy this place.";
        if (_kbhit()) {
            choise = _getch();
            if (choise == '1') {
                player_info.level++;
                koord.y_zone = koord.y_max/2;
                for (int i = 0; i < koord.y_max; i++) {
                    setCursorPosition(koord.x_max/2, i);
                    cout << " ";
                }
            }
        }
        break;
    case 1:
        setCursorPosition(koord.x_notification, koord.y_notification);
        cout << "Enter '1' if you want to buy this place.";
        if (_kbhit()) {
            choise = _getch();
            if (choise == '1') {
                player_info.level++;
                koord.x_zone = koord.x_max / 2;
                for (int i = 0; i < koord.x_max; i++) {
                    setCursorPosition(i, koord.y_max / 2);
                    cout << " ";
                }
            }
        }
        break;
    case 2:
        setCursorPosition(koord.x_notification, koord.y_notification);
        cout << "Enter '1' if you want to buy this place.";
        if (_kbhit()) {
            choise = _getch();
            if (choise == '1') {
                player_info.level++;
                app_info.zone = false;
                for (int i = koord.y_max/2; i < koord.y_max; i++) {
                    setCursorPosition(koord.x_max/2, i);
                    cout << " ";
                }
                for (int i = koord.x_max / 2; i < koord.x_max; i++) {
                    setCursorPosition(i, koord.y_max/2);
                    cout << " ";
                }
            }
        }
        break;
    }
}

void menu_choise_plant_garden(short i) {
    short &x_curs_pos = koord.x_curs_pos, &y_curs_pos = koord.y_curs_pos;
    string culture[] = { "Овес", "Кукуруза", "Пшеница", "Ячмень", "Просо", "Горох",
        "Свекла", "Морковь", "Кaртофель"};
    system("cls");
    while (true) {
        for (short x = koord.x_plant_menu; x < koord.x_size_plant_menu+koord.x_plant_menu; x++) {
            for (short y = koord.y_plant_menu; y < koord.y_size_plant_menu+koord.y_plant_menu; y++) {
                if (x == koord.x_plant_menu || y == koord.y_plant_menu ||
                    x==koord.x_plant_menu+koord.x_size_plant_menu-1||
                    y== koord.y_plant_menu + koord.y_size_plant_menu - 1) {
                    setCursorPosition(x, y);
                    cout << "#";
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            setCursorPosition(koord.x_plant_menu + 1, koord.y_plant_menu + i + 1);
            cout << culture[i];
        }
        setCursorPosition(x_curs_pos, y_curs_pos);
        cout << "<-";
        char input2 = _getch();
        if (input2 == 'w' && y_curs_pos > koord.y_plant_menu + 1) {
            y_curs_pos--;
            setCursorPosition(x_curs_pos, y_curs_pos + 1);
            cout << "  ";
        }
        else if (input2 == 's' && y_curs_pos < koord.y_plant_menu + koord.y_size_plant_menu - 2) {
            y_curs_pos++;
            setCursorPosition(x_curs_pos, y_curs_pos - 1);
            cout << "  ";
        }
        else if (GetAsyncKeyState('1') ) {
            garden[i].culture1 = (garden::culture)(y_curs_pos - 16);
            break;
        }  
    }
    system("cls");
}

void draw_garden() {
    char garden1[] = " _____ ";
    char garden2[] = "|";
    char garden3[] = " ¯¯¯¯¯ ";
    for (int i = 0; i < 20; i++) {
        chrono::seconds time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - garden[i].g_clock);
        if (garden[i].area == ":::::" && time.count() == app_info.time_plant_garden[garden[i].culture1]) {
            garden[i].area = "*****";
        }
        setCursorPosition(garden[i].x_position, garden[i].y_position);
        cout <<  garden1;
        setCursorPosition(garden[i].x_position, garden[i].y_position+1);
        cout << garden2 << garden[i].area;
        setCursorPosition(garden[i].x_position, garden[i].y_position+2);
        cout << garden2 << garden[i].area;
        setCursorPosition(garden[i].x_position + koord.weight-2, garden[i].y_position + 1);
        cout << garden2;
        setCursorPosition(garden[i].x_position + koord.weight-2, garden[i].y_position + 2);
        cout << garden2;
        setCursorPosition(garden[i].x_position, garden[i].y_position+3);
        cout << garden3;
        if (garden[i].ifplant) {
            setCursorPosition(garden[i].x_position, garden[i].y_position + 5);
            cout << garden[i].culture1;
            setCursorPosition(garden[i].x_position+1, garden[i].y_position);
            cout << (app_info.time_plant_garden[garden[i].culture1] - time.count()) / 60 << ":";
            if ((app_info.time_plant_garden[garden[i].culture1] - time.count()) % 60 < 10) {
                cout << "0" <<  (app_info.time_plant_garden[garden[i].culture1] - time.count()) % 60;
            }
            else {
                cout << (app_info.time_plant_garden[garden[i].culture1] - time.count()) % 60;
            }
        }
        if (app_info.time_plant_garden[garden[i].culture1] - time.count() == 0) {
            garden[i].ifplant = false;
            setCursorPosition(garden[i].x_position, garden[i].y_position + 4);
            cout << "    ";
        }     
    }
}

void if_in_garden() {
    const short& x_person = koord.x_person;
    const short& y_person = koord.y_person;
    const short& height = koord.height;
    const short& weight = koord.weight;

    for (int i = 0; i < 20; i++) {
        if (x_person > garden[i].x_position &&
            x_person < garden[i].x_position + weight &&
            y_person > garden[i].y_position &&
            y_person < garden[i].y_position + height) {
            setCursorPosition(koord.x_notification, koord.y_notification);
            cout << "Enter 1 by do garden";
            string input;
            /*if (_kbhit()) {
                input = _getch();
                if (input == "1") {
                    menu_choise_plant_garden(i);
                    garden[i].area = ". . .";
                    
                }
                
            }*/
            if (GetAsyncKeyState('1') & 0x8000) {
                menu_choise_plant_garden(i);
                garden[i].area = ". . .";
            }
            
            if (GetAsyncKeyState('2') && player_info.water >= 1 && garden[i].area == ". . .") {
                garden[i].area = ":::::";
                garden[i].g_clock = chrono::high_resolution_clock::now();
                player_info.water--;
                garden[i].ifplant = true;
            }
            if (input == "3" && garden[i].area == "*****") {
                garden[i].area = "     ";
                player_info.sum_culture[garden[i].culture1]++;
            }
        }            
    }
}

void draw_animals_house() {
    for (short i = 0; i < 5; i++) {
        const short &x_animals_house = animals_house[i].x_position, &y_animals_house = animals_house[i].y_position;
        short x_size_animals_house = koord.x_size_animals_house,
            y_size_animals_house = koord.y_size_animals_house;

        char house_animals1[] = " __________ ";
        char house_animals2[] = "|";
        char house_animals3[] = " ¯¯¯¯¯¯¯¯¯¯ ";
        setCursorPosition(x_animals_house, y_animals_house);
        cout << house_animals1;
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
        setCursorPosition(x_animals_house, y_animals_house + 5);
        cout << house_animals3;
    }
}

void if_in_animals_house() {
    const short& x_person = koord.x_person;
    const short& y_person = koord.y_person;
    const short& height = koord.an_house_height;
    const short& weight = koord.an_house_weight;
    for (int i = 0; i < 5; i++) {
        if (x_person > animals_house[i].x_position &&
            x_person < animals_house[i].x_position + weight &&
            y_person > animals_house[i].y_position &&
            y_person < animals_house[i].y_position + height) {;
        }
    }
}



int main()
{
    system("pause");
    while (true) {
        if (app_info.start_koord_garden) {
            koord_garden();
            app_info.start_koord_garden = false;
        }
        if_in_garden();
        water_in_wel();
        drawing_well();
        drawing_storage();
        draw_garden();
        if_in_animals_house();
        
        setCursorPosition(0, 0);
        drawing_field();
        drawing_zone();
        control();
        draw_animals_house();
        if (player_info.level == 0 && koord.x_person == (koord.x_max-1) / 2) {
            buy_place();
        }
        else if (player_info.level == 1 && koord.x_person < (koord.x_max-1)/2
            &&  koord.y_person == (koord.y_max-1)/2) {
            buy_place();
        }
        else if (player_info.level == 2 &&
            ((koord.x_person > (koord.x_max - 1) / 2 && koord.y_person == (koord.y_max - 1) / 2) || 
                koord.x_person == (koord.x_max-1)/2 && (koord.y_person > (koord.y_max-1)/2))) {
            buy_place();
        }
        else {
            setCursorPosition(koord.x_notification, koord.y_notification);
            cout << "                                                                    ";
        }
        Sleep(100);

    }
    return 0;
}