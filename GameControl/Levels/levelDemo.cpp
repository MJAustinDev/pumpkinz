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

#include "levels.h"

namespace {

}; // end of namespace

namespace level {

void setUpDemoLevel(b2World &p_world, std::list<std::unique_ptr<entity::DynamicEntity>> &p_blocks,
                    std::list<std::unique_ptr<entity::StaticEntity>> &p_terrain) {

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(30.0f, -5.0f),
        b2Vec2(30.0f, 0.0f)
    };

    p_terrain.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape));
    p_terrain.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(25.0f, 0.0f), kGroundShape));
    p_terrain.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(65.0f, 0.0f), kGroundShape));

    const std::vector<b2Vec2> kMainBlock = {
        b2Vec2(-0.5f, 0.0f),
        b2Vec2(0.5f, 0.0f),
        b2Vec2(0.5f, 5.0f),
        b2Vec2(-0.5f, 5.0f)
    };
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(50.2f, 40.0f), kMainBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(50.0f, 50.0f), kMainBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(50.0f, 60.0f), kMainBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(-5.0f, 60.0f), kMainBlock));

};

}; // end of namespace level