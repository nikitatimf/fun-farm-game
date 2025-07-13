#include "data.h"

size_of_subjects dimension;

const short kkord::X_PLANT_MENU = dimension.X_MAX / 2 - dimension.X_SIZE_PLANT_MENU / 2;
const short kkord::Y_PLANT_MENU = dimension.Y_MAX / 2 - dimension.Y_SIZE_PLANT_MENU / 2;

const short kkord::X_ANIMALS_MENU = dimension.X_MAX / 2 - dimension.X_SIZE_ANIMALS_MENU / 2;
const short kkord::Y_ANIMALS_MENU = dimension.Y_MAX / 2 - dimension.Y_SIZE_ANIMALS_MENU / 2;

const short kkord::X_FEED_THE_ANIMALS_MENU = dimension.X_MAX / 2 - dimension.X_SIZE_FEED_THE_ANIMALS_MENU / 2;
const short kkord::Y_FEED_THE_ANIMALS_MENU = dimension.Y_MAX / 2 - dimension.Y_SIZE_FEED_THE_ANIMALS_MENU / 2;

const short kkord::X_STORE_AREA = kkord::X_STORE_POSITION + 4;
const short kkord::Y_STORE_AREA = kkord::Y_STORE_POSITION + dimension.HEIGHT_STORE_AREA;

kkord koord;

player_info1 player_info;

const std::string app_text::NAME_ARRAY[13] = {
    "Овес", "Кукуруза", "Пшеница", "Ячмень", "Просо", "Горох",
    "Свекла", "Морковь", "Кaртофель", "Яйца", "Молоко", "Бекон", "Шерсть"
};

const std::string app_text::AMIMAL_GOODS[4] = {
    "Яйца", "Молоко", "Бекон", "Шерсть"
};


const std::string app_text::CHICKEN_FOOD[3] = {
    "Овес", "Кукуруза", "Пшеница"
};

const std::string app_text::SHEEP_FOOD[5] = {
    "Кукуруза", "Овес", "Ячмень", "Горох", "Свекла"
};

const std::string app_text::PIG_FOOOD[6] = {
    "Просо", "Горох", "Ячмень", "Свекла", "Морковь", "Кaртофель"
};

const std::string app_text::head_animals_menu[4] = {
    "Загон с курицами", "Загон со свиньями", "Загон с коровами", "Загон с овечками"
};

const short app_text::STRLEN_ZAG_ANIM[4] = { 16, 17, 17, 16 };

const std::string app_text::BUY_ANIMALS[4] = { "курицу", "свинью", "корову", "овечку" };
const std::string app_text::ANIMAL_GOOD[4] = { "яйца", "бекон", "молоко", "шерсть" };

app_text text;

const short app_info_game::SALE_PRICE[13] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
const short app_info_game::BUY_PRICE[13] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
const short app_info_game::EXP_FOR_PLANT = 500;
const short app_info_game::EXP_FOR_ANIMALS = 15;

app_info_game app_info;

garden_game garden[20];

animals_house_game animals_house[4];