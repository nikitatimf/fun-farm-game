#pragma once
#include "system.h"
#include "data.h"

// Функция, улучшающая колодец.
void improve_well_level();

// Функция, рисующая колодец.
void drawing_well();

// Добыча воды в колодце.
// И проверка, находится ли персонаж в 
// области перед колодцем.
void water_in_wel();

// Функция, проверяющая находится ли персонаж
// перед колодцем.
void if_in_well();
