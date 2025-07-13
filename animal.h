#pragma once
#include "system.h"
#include "data.h"


// Функция, улучшающая загон с животными.
// index - индекс загона в массиве структур.
void improve_animal_house(short index);

// Функция, рисующая загон с животными.
void draw_animals_house();

// Функция, работающая со временем загона.
void animal_goods();

// Функция, рисующая меню кормления животных.
// num - индекс животного в массиве.
short feed_the_animals(int num);

// Функция, рисующая и отвечающая за функционал меню загона с животными.
short animals_house_menu(int num);

// Функция, проверяющая, находится ли персонаж внутри загона с животными.
void if_in_animals_house();