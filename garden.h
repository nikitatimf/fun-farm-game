#pragma once
#include "system.h"
#include "data.h"

// Функция, улучшающая уровень огорода.
// index - индекс поля в массиве структуры полей.
void improve_garden_level(int index);

// Функция, рисующая меню выбора посаженного растения.
// i - индекс поля в массиве структур.
void menu_choise_plant_garden(short i);

// Функция, рисующая поля.
void draw_garden();

// Функция, проверяющая находится ли персонаж внутри поля.
void if_in_garden();

