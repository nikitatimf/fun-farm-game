#pragma once
#include <chrono>
using namespace std;

// Структура, хранящая размеры объектов.
extern struct size_of_subjects {
    // Размеры поля в координатах Х и Y.
    const short Y_MAX = 41, X_MAX = 156;

    // Ширина и высота огорода.
    const short GARDEN_WEIGHT = 8, GARDEN_HEIGHT = 4;
    // Размеры меню огорода в координтах X и Y.
    const short X_SIZE_PLANT_MENU = 50, Y_SIZE_PLANT_MENU = 11;

    // Ширина области перед магазином.
    const short WEIGHT_STORE_AREA = 10;
    // Высота магазина.
    const short HEIGHT_STORE_AREA = 6;
    // Расстояние между линиями разметки в меню магазина.
    const short X_STORE_MENU_LINE = X_MAX / 7, Y_STORE_MENU_LINE = Y_MAX / 2;

    // Размеры загона с животными.
    const short ANIMALS_HOUSE_WEIGHT = 11, ANIMALS_HOUSE_HEIGHT = 5;
    // Размеры меню загона с животными в координатах Х и Y.
    const short X_SIZE_ANIMALS_MENU = 50, Y_SIZE_ANIMALS_MENU = 6;
    // Размеры меню кормления животных в координатах Х и Y.
    const short X_SIZE_FEED_THE_ANIMALS_MENU = 50, Y_SIZE_FEED_THE_ANIMALS_MENU = 12;
}dimension;

// Структура, хранящая координаты объектов.
extern struct kkord {
    // Координаты персонажа.
    short y_person = 11, x_person = 31;

    // Координаты, начала рисовки линий, отделяющих поля, доступные для покупки.
    short y_place_zone = 0, x_place_zone = 0;

    // Координыты колодца.
    const short Y_WELL = 10, X_WELL = 50;

    // Координаты склада.
    const short Y_STORAGE = 10, X_STORAGE = 80;

    // Координаты меню огорода.
    const short X_PLANT_MENU = dimension.X_MAX / 2 - dimension.X_SIZE_PLANT_MENU / 2,
        Y_PLANT_MENU = dimension.Y_MAX / 2 - dimension.Y_SIZE_PLANT_MENU / 2;
    // Координаты курсора в меню огорода.
    short x_curs_pos_garden_menu = 98, y_curs_pos_garden_menu = 16;

    // Координаты области вывода информации.
    const short Y_NOTIFICATION = dimension.Y_MAX, X_NOTIFICATION = 0;

    // Координаты меню загона с животными.
    const short X_ANIMALS_MENU = dimension.X_MAX / 2 - dimension.X_SIZE_ANIMALS_MENU / 2,
        Y_ANIMALS_MENU = dimension.Y_MAX / 2 - dimension.Y_SIZE_ANIMALS_MENU / 2;
    // Координаты меню кормления животных.
    const short X_FEED_THE_ANIMALS_MENU = dimension.X_MAX / 2 - dimension.X_SIZE_FEED_THE_ANIMALS_MENU / 2,
        Y_FEED_THE_ANIMALS_MENU = dimension.X_MAX / 2 - dimension.Y_SIZE_FEED_THE_ANIMALS_MENU / 2;

    // Координаты магазина.
    const short X_STORE_POSITION = 25, Y_STORE_POSITION = 5;
    // Координаты области перед магазином.
    const short X_STORE_AREA = X_STORE_POSITION + 4,
        Y_STORE_AREA = Y_STORE_POSITION + dimension.HEIGHT_STORE_AREA;
}koord;

// Структура, хранящая данные о результатах игрока.
extern struct player_info {
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
    short water = 1000;
    // Кольчество растительных продуктов.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель.
    short sum_culture[9] = { 10, 0, 0, 0, 0, 0, 0, 0, 0 };
    // Количество животных продуктов.
    // Яйца молоко бекон шерсть.
    short sum_animal_goods[4] = { 0, 0, 0, 0 };
    // Количество животных.
    // Курица свинья корова овечка.
    short num_animals[4] = { 0, 0, 0, 0 };
}player_info;

// Структура, хранящая все текстовае данные.
extern struct app_text {
    // Количество садовых культур.
    const short NUM_CULTURE = 9;
    string string_culture[9] = { "Овес", "Кукуруза", "Пшеница", "Ячмень", "Просо", "Горох",
                                 "Свекла", "Морковь", "Кaртофель" };
    const string NAME_ARRAY[13] = { "Овес", "Кукуруза", "Пшеница", "Ячмень", "Просо", "Горох",
                              "Свекла", "Морковь", "Кaртофель", "Яйца", "Молоко", "Бекон", "Шерсть" };
    const string AMIMAL_GOODS[4] = { "Яйца", "Молоко", "Бекон", "Шерсть" };
    // Культуры, которую ест курица.
    const string CHICKEN_FOOD[3] = { "Овес", "Кукуруза", "Пшеница" };
    // Количество культур, которые ест курица.
    const short NUM_CHICKEN_FOOD = 3;
    // Культуры, которые ест овечка.
    const string SHEEP_FOOD[5] = { "Кукуруза", "Овес", "Ячмень", "Горох", "Свекла" };
    // Количество культур, которые ест овечка.
    const short NUM_SHEEP_FOOD = 5;
    // Культуры, которые ест свинья.
    const string PIG_FOOOD[6] = { "Просо", "Горох", "Ячмень", "Свекла", "Морковь", "Кaртофель" };
    // Количество культур, которые ест свинья.
    const short NUM_PIG_FOOD = 6;
    // Максимально количество культур, которое ест животные.
    const short MAX_NUM_FOOD = 6;
    string head_animals_menu[4] = { "Загон с курицами", "Загон со свиньями", "Загон с коровами", "Загон с овечками" };
    // Количество  символов в заголовке животных.
    const short STRLEN_ZAG_ANIM[4] = { 16, 17, 17, 16 };
    const string BUY_ANIMALS[4] = { "курицу", "свинью", "корову", "овечку" };
    const string ANIMAL_GOOD[4] = { "яйца", "бекон", "молоко", "шерсть" };
}text;

// Структура, хранящая данные о игре.
extern struct app_info {
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

    // Хранит время начала сбора воды в колодце.
    chrono::time_point<chrono::high_resolution_clock> well_time;
    // Цены продажи продуктов в магазине.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель яйца молоко бекон шерсть.
    const short SALE_PRICE[13] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    // Цены покупки продуктов в магазине.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель яйца молоко бекон шерсть.
    const short BUY_PRICE[13] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

    // Время роста культур.
    // Овес кукуруза пшеница ячмень просо горох свекла морковь кaртофель.
    short time_plant_garden[9] = { 10, 10, 10, 1,1 ,1 ,1 ,1 ,1 }/*{300, 450, 345, 330, 240, 240, 330, 360, 330}*/;

    // Время сбора воды в колодце.
    short perez_wel = 5;

    // Опыт, получаемый при сборе выращенной культуре.
    const short EXP_FOR_PLANT = 300;
    // Опыт, получаемый при сборе продуктов животных.
    const short EXP_FOR_ANIMALS = 50; // 2

    // Вместимость склада.
    short warehouse_storage = 50;

    // Уровень колодца.
    short wel_level = 1;
    // Уровень склада.
    short storage_level = 1;
}app_info;

// Структура, хранящая данные о огородах.
extern struct garden {
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
}garden[20] = {};

// Структура для зранения данных о загонах.
extern struct animals_house {
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

}animals_house[4] = {};