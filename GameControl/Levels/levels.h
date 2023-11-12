/**
 * MIT License
 *
 * Copyright (c) 2023 Matthew James Austin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "box2d/box2d.h"
#include <list>
#include <memory>
#include "dynamicEntity.h"
#include "staticEntity.h"
#include "targetEntity.h"
#include "levelManager.h"

namespace shadow_pumpkin_caster {
namespace level {

template<typename T>
void addDynamic(std::list<std::unique_ptr<shadow_pumpkin_caster::entity::DynamicEntity>> &p_dynamic, std::unique_ptr<T> p_ptr) {
    p_dynamic.push_back(static_cast<std::unique_ptr<shadow_pumpkin_caster::entity::DynamicEntity>>(p_ptr.release()));
}

/**
 * Generates the demo world
 * @param p_world box2d world where all entities exist
 * @param p_entities entity container structure
 */
void setUpDemoLevel(b2World &p_world, LevelManager::LevelEntities &p_entities);

/**
 * Generates level 1
 * @param p_world box2d world where all entities exist
 * @param p_entities entity container structure
 */
void setUpLevel_1(b2World &p_world, LevelManager::LevelEntities &p_entities);

/**
 * Generates level 2
 * @param p_world box2d world where all entities exist
 * @param p_entities entity container structure
 */
void setUpLevel_2(b2World &p_world, LevelManager::LevelEntities &p_entities);


/**
 * Generates level 3
 * @param p_world box2d world where all entities exist
 * @param p_entities entity container structure
 */
void setUpLevel_3(b2World &p_world, LevelManager::LevelEntities &p_entities);


/**
 * Generates level 4
 * @param p_world box2d world where all entities exist
 * @param p_entities entity container structure
 */
void setUpLevel_4(b2World &p_world, LevelManager::LevelEntities &p_entities);

/**
 * Generates level 5
 * @param p_world box2d world where all entities exist
 * @param p_entities entity container structure
 */
void setUpLevel_5(b2World &p_world, LevelManager::LevelEntities &p_entities);

}; // end of namespace level
}; // end of namespace shadow_pumpkin_caster
