/**
 * MIT License
 *
 * Copyright (c) 2023-2024 Matthew James Austin
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

#include <list>
#include <memory>
#include "collisionListener.h"
#include "pages.h"
#include "gun.h"
#include "missionEntities.h"

namespace shadow_pumpkin_caster::missions {

class Mission {

public:

    Mission(Regions p_region, unsigned int p_mission);
    ~Mission();

    void processEvents();

    void draw(const io::visual::Camera &p_camera);

private:

    entity::CollisionListener m_collisionListener;
    b2World m_world;
    Gun m_playerGun;
    MissionEntities_t m_entities;

    void addProjectile(std::shared_ptr<entity::DynamicEntity> p_round);

};

}; // end of namespace shadow_pumpkin_caster::missions

