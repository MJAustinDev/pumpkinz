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

#include "mission.h"

namespace {

/**
 * Process game events for entities with no special after death abilities
 * @param p_entities list of entities to process
 */
template <typename T>
void processEntityList(std::list<std::shared_ptr<T>> &p_entities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            p_entities.erase(deadEntity);
        }
    }
}

/**
 * Draws all entities within an entity list
 * @param p_entities list of entities contains within unique pointers
 * @param p_camera camera used to draw each entity
 */
template <typename T>
void drawEntityList(std::list<T> &p_entities, const io::visual::Camera &p_camera) {
    for (auto &entity : p_entities) {
        entity->draw(p_camera);
    }
}

}; // end of namespace

namespace shadow_pumpkin_caster::missions {

Mission::Mission(b2World* p_world): m_world(p_world) {

}

Mission::~Mission() {

}

void Mission::processEvents() {
    processEntityList(m_projectiles);
    processEntityList(m_destructableBlocks);
    processEntityList(m_pumpkins);
    processEntityList(m_skeletons);
    processEntityList(m_gravestones);
    processEntityList(m_ghosts);
    processEntityList(m_necromancers);
    processEntityList(m_witches);
    processEntityList(m_vampires);
}

void Mission::draw(const io::visual::Camera &p_camera) {
    drawEntityList(m_staticGround, p_camera);
    drawEntityList(m_destructableBlocks, p_camera);
    drawEntityList(m_hurtEntities, p_camera);
    drawEntityList(m_projectiles, p_camera);
    drawEntityList(m_pumpkins, p_camera);
    drawEntityList(m_skeletons, p_camera);
    drawEntityList(m_gravestones, p_camera);
    drawEntityList(m_ghosts, p_camera);
    drawEntityList(m_necromancers, p_camera);
    drawEntityList(m_witches, p_camera);
    drawEntityList(m_vampires, p_camera);
}

void Mission::addProjectile(std::shared_ptr<entity::DynamicEntity> p_round) {
    m_projectiles.push_back(std::move(p_round));
}

}; // end of namespace shadow_pumpkin_caster::missions

