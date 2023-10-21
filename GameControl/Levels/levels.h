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

namespace shadow_pumpkin_caster {
namespace level {

/**
 * Generates the demo world
 * @param p_world box2d world where all entities exist
 * @param p_blocks list that stores all dynamic block entities
 * @param p_terrain list that stores all static terrain entities
 */
void setUpDemoLevel(b2World &p_world, std::list<std::unique_ptr<entity::DynamicEntity>> &p_dynamic,
                    std::list<std::unique_ptr<entity::StaticEntity>> &p_static);

}; // end of namespace level
}; // end of namespace shadow_pumpkin_caster
