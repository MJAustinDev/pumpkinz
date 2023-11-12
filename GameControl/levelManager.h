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
#include <memory>
#include "camera.h"
#include "collisionListener.h"
#include "staticEntity.h"
#include "dynamicEntity.h"
#include "player.h"
#include "pumpkin.h"
#include "skeleton.h"
#include "gravestone.h"

namespace shadow_pumpkin_caster {

class LevelManager {

public:

    LevelManager();
    ~LevelManager();

    void processEvents();

    void draw(const visual::Camera &p_camera);

    void reset();

    struct LevelEntities {
        std::list<std::unique_ptr<entity::StaticEntity>> m_static;
        std::list<std::unique_ptr<entity::DynamicEntity>> m_dynamic;
        std::list<std::unique_ptr<entity::enemy::Skeleton>> m_skeletons;
        std::list<std::unique_ptr<entity::enemy::Gravestone>> m_gravestones;
    };

private:

    entity::CollisionListener m_collisionListener;
    b2World m_world;
    LevelEntities m_entities;
    Player m_player;

    void clearAll();

};

}; // end of namespace shadow_pumpkin_caster
