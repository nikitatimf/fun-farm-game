#pragma once
#include "system.h"
#include "field_and_palce.h"
#include "data.h"

// Функция, отрисовывающая магазин.
void draw_store();

// Функция, рисующая меню покупки.
short sale_or_buy_goods(short choice);

// Функция, рисующая меню магазина.
void store_menu();

// Если персонаж находится в области перед магазином.
void if_in_store_area();