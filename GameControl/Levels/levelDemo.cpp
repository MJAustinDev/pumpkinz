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

namespace level {

void setUpDemoLevel(b2World &p_world, std::list<std::unique_ptr<entity::DynamicEntity>> &p_blocks,
                    std::list<std::unique_ptr<entity::StaticEntity>> &p_terrain,
                    std::list<std::unique_ptr<entity::TargetEntity>> &p_enemies) {

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(30.0f, -5.0f),
        b2Vec2(30.0f, 0.0f)
    };

    p_terrain.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape));
    p_terrain.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(25.0f, 0.0f), kGroundShape));
    p_terrain.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(65.0f, 0.0f), kGroundShape));

    const std::vector<b2Vec2> kVerticalBlock = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(1.0f, 0.0f),
        b2Vec2(1.0f, 5.0f),
        b2Vec2(0.0f, 5.0f)
    };

    const std::vector<b2Vec2> kHorizontalBlock = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(5.0f, 0.0f),
        b2Vec2(5.0f, 1.0f),
        b2Vec2(0.0f, 1.0f)
    };

    auto placeTower = [&p_world, &p_blocks, &kVerticalBlock](b2Vec2 p_position) {
        b2Vec2 position = p_position;
        for (int j=0; j<2; j++) {
            for (int i=0; i<3; i++) {
                p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, position, kVerticalBlock));
                position.y += 5.0f;
            }
            position = p_position;
            position.x += 1.0f;
        }
    };

    placeTower(b2Vec2(52.0f, 0.0f));
    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(53.0f, 15.5f), 0.5f));

    placeTower(b2Vec2(67.0f, 0.0f));
    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(68.0f, 15.5f), 0.5f));

    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(69.0f, 0.0f), kVerticalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(69.0f, 5.0f), kHorizontalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(69.0f, 6.0f), kHorizontalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(69.0f, 7.0f), kHorizontalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(73.5f, 0.0f), kVerticalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(74.0f, 5.0f), kHorizontalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(74.0f, 6.0f), kHorizontalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(74.0f, 7.0f), kHorizontalBlock));
    p_blocks.push_back(std::make_unique<entity::DynamicEntity>(p_world, b2Vec2(78.0f, 0.0f), kVerticalBlock));

    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(72.0f, 0.5f), 0.5f));
    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(76.0f, 0.5f), 0.5f));

    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(71.0f, 8.5f), 0.5f));
    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(74.0f, 8.5f), 0.5f));
    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(77.0f, 8.5f), 0.5f));

    placeTower(b2Vec2(79.0f, 0.0f));
    p_enemies.push_back(std::make_unique<entity::TargetEntity>(p_world, b2Vec2(80.0f, 15.5f), 0.5f));

};

}; // end of namespace level
