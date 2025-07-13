#pragma once
#include "system.h"
#include "data.h"

// Функция, рисующая игровое поле.
void drawing_field();

// Функия для покупки участков.
void buy_place();

// Функия для отрисовки данных об игроке.
void inform();

// Функция, проверяющая находится ли пользователь
// в зоне, в которой доступна покупка участка.
void if_in_buy_place_zone();