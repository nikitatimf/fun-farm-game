#ifndef DATA_H
#define DATA_H
#include <chrono>
using namespace std;

// Структура, хранящая размеры объектов.
struct size_of_subjects {
    // Размеры поля в координатах Х и Y.
    static const short Y_MAX = 41, X_MAX = 156;

    // Ширина и высота огорода.
    static const short GARDEN_WEIGHT = 8, GARDEN_HEIGHT = 4;
    // Размеры меню огорода в координтах X и Y.
    static const short X_SIZE_PLANT_MENU = 50, Y_SIZE_PLANT_MENU = 11;

    // Ширина области перед магазином.
    static const short WEIGHT_STORE_AREA = 10;
    // Высота магазина.
    static const short HEIGHT_STORE_AREA = 6;
    // Расстояние между линиями разметки в меню магазина.
    static const short X_STORE_MENU_LINE = X_MAX / 7, Y_STORE_MENU_LINE = Y_MAX / 2;

    // Размеры загона с животными.
    static const short ANIMALS_HOUSE_WEIGHT = 11, ANIMALS_HOUSE_HEIGHT = 5;
    // Размеры меню загона с животными в координатах Х и Y.
    static const short X_SIZE_ANIMALS_MENU = 50, Y_SIZE_ANIMALS_MENU = 6;
    // Размеры меню кормления животных в координатах Х и Y.
    static const short X_SIZE_FEED_THE_ANIMALS_MENU = 50, Y_SIZE_FEED_THE_ANIMALS_MENU = 12;
}extern dimension;

// Структура, хранящая координаты объектов.
struct kkord {
    // Координаты персонажа.
    short y_person = 11, x_person = 31;

    // Координаты, начала рисовки линий, отделяющих поля, доступные для покупки.
    short y_place_zone = 0, x_place_zone = 0;

    // Координыты колодца.
    static const short Y_WELL = 10, X_WELL = 50;

    // Координаты склада.
    static const short Y_STORAGE = 10, X_STORAGE = 80;

    // Координаты меню огорода.
    static const short X_PLANT_MENU, Y_PLANT_MENU;

    // Координаты магазина.
    static const short X_STORE_POSITION = 25, Y_STORE_POSITION = 5;

    // Координаты курсора в меню огорода.
    short x_curs_pos_garden_menu = 98, y_curs_pos_garden_menu = 16;

    // Координаты области вывода информации.
    static const short Y_NOTIFICATION = dimension.Y_MAX, X_NOTIFICATION = 0;

    // Координаты меню загона с животными.
    static const short X_ANIMALS_MENU, Y_ANIMALS_MENU;

    // Координаты меню кормления животных.
    static const short X_FEED_THE_ANIMALS_MENU, Y_FEED_THE_ANIMALS_MENU;

    // Координаты области перед магазином.
    static const short X_STORE_AREA, Y_STORE_AREA;
}extern koord;

// Структура, хранящая данные о результатах игрока.
struct player_info1 {
    // Уровень игрока.
    short player_level = 1;
    // Опыт.
    short current_exp = 0;
    // Опыт, требуемый для перехода на новый уровень.
    float full_exp = 50;
    // Уровень игрового поля.
    short place_level = 0;
    // Деньги.
    short money = 1000;
    // Количество воды.
    short water = 1010;
    // Кольчество растительных продуктов.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель.
    short sum_culture[9] = { 1000, 0, 0, 0, 0, 0, 0, 0, 0 };
    // Количество животных продуктов.
    // Яйца молоко бекон шерсть.
    short sum_animal_goods[4] = { 0, 0, 0, 0 };
    // Количество животных.
    // Курица свинья корова овечка.
    short num_animals[4] = { 0, 0, 0, 0 };
}extern player_info;

// Структура, хранящая данные о игре.
struct app_info_game {
    // Если все области земли куплены - false.
    bool is_all_zone_not_buy = true;
    // Собрана ли вода в колодце.
    bool well_water = true;
    // Доступно ли улучшение склада.
    bool chance_improve_storage = false;
    // Доступно ли улучшение колодца.
    bool chance_improve_wel = false;
    // Есть ли место в колодце.
    bool is_free_storage = true;
    // Находился ли персонаж внутри загона.
    bool is_in_animal_house = false;
    // Находился ли персонаж в области покупки участка.
    bool is_in_zone_buy_place = false;
    // Находился ли персонаж внутри огорода.
    bool is_in_garden = false;
    // Находился ли персонаж перед колодцем.
    bool is_near_well = false;
    // Находился ли персонаж перед складом.
    bool is_near_storage = false;
    // Находился ли персонаж перед складом.
    bool is_near_store = false;
    // Хранит время начала сбора воды в колодце.
    chrono::time_point<chrono::high_resolution_clock> well_time;
    // Цены продажи продуктов в магазине.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель яйца молоко бекон шерсть.
    static const short SALE_PRICE[13];
    // Цены покупки продуктов в магазине.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель яйца молоко бекон шерсть.
    static const short BUY_PRICE[13];

    // Время роста культур.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель.
    short time_plant_garden[9] = { 1, 10, 10, 1,1 ,1 ,1 ,1 ,1 }/*{300, 450, 345, 330, 240, 240, 330, 360, 330}*/;

    // Коэфициент роста растений на огороде
    // Время роста умножается на коэфициент поля.
    float kov_growing[20];

    // Стоимость животных.
    // Курица, свинья, корова, овечка.
    short animals_price[4] = { 10, 10, 10, 10 };

    // Время сбора воды в колодце.
    short perez_wel = 5;

    // Опыт, получаемый при сборе выращенной культуре.
    static const short EXP_FOR_PLANT;
    // Опыт, получаемый при сборе продуктов животных.
    static const short EXP_FOR_ANIMALS; 

    // Вместимость склада.
    int warehouse_storage = 5000;

    // Уровень колодца.
    short wel_level = 1;
    // Уровень склада.
    short storage_level = 1;

    // Цена повышения уровня огорода.
    short price_up_level_garden[3] = {100, 200, 300};
    // Цена повышения уровня загона с животными.
    short price_up_level_animal_house[3] = { 100, 200, 300 };
    // Цена повышения уровня колодца.
    short price_up_level_well[3] = { 100, 200, 100 };
    // Цена повышения уровня склада.
    short price_up_level_storage[5] = { 100, 200, 100, 100, 100  };
    // Цена покупки земли.
    short price_up_level_field[3] = { 100, 200, 100 };
}extern app_info;

// Структура, хранящая все текстовае данные.
struct app_text {
    // Количество садовых культур.
    static const short NUM_CULTURE = 9;
    static const string NAME_ARRAY[13];
    static const string AMIMAL_GOODS[4];
    string string_culture[9] = {"Овес", "Кукуруза", "Пшеница", "Ячмень", "Просо", "Горох",
    "Свекла", "Морковь", "Кaртофель"};

    // Культуры, которую ест курица.
    static const string CHICKEN_FOOD[3];
    // Количество культур, которые ест курица.
    static const short NUM_CHICKEN_FOOD = 3;
    // Культуры, которые ест овечка.
    static const string SHEEP_FOOD[5];
    // Количество культур, которые ест овечка.
    static const short NUM_SHEEP_FOOD = 5;
    // Культуры, которые ест свинья.
    static const string PIG_FOOOD[6];
    // Количество культур, которые ест свинья.
    static const short NUM_PIG_FOOD = 6;
    // Максимально количество культур, которое ест животные.
    static const short MAX_NUM_FOOD = 6;
    static const string head_animals_menu[4];
    // Количество  символов в заголовке животных.
    static const short STRLEN_ZAG_ANIM[4];
    static const string BUY_ANIMALS[4];
    static const string ANIMAL_GOOD[4];
}extern text;

// Структура, хранящая данные о огородах.
struct garden_game {
    // Возможность улучшения поля.
    bool chance_improve = false;
    // Координаты поля.
    short x_position = 0, y_position = 0;
    // Уровень поля.
    short level = 1;
    // Заполненность поля.
    string area = "     ";
    // Время начала роста.
    chrono::time_point<chrono::high_resolution_clock> g_clock;
    // Засажено ли поле.
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
}extern garden[20];

// Структура для зранения данных о загонах.
struct animals_house_game {
    // Доступно ли улучшение.
    bool chance_improving = false;
    // Пасутся ли животные.
    bool busy_animal = false;
    // Есть ли продукты в загоне.
    bool goods_in_house = false;
    // Ели ли животные
    bool animals_eaten = false;

    // Уровень загона.
    short level = 1;

    // Количество продуктов, получаемое от 1 животного.
    short goods_giving_animal = 1;
    // Количество продуктов в загоне.
    short goods = 0;

    // Координаты загона.
    short x_position = 0, y_position = 0;


    // Время, когда животные начали пастись.
    chrono::time_point<chrono::high_resolution_clock> anim_clock;
    // Время, которое пасутся животные.
    short animal_time = 0;

}extern animals_house[4];

#endif