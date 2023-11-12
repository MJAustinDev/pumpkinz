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

#include <iostream>
#include <limits>
#include "levelManager.h"
#include "levels.h"

namespace {

constexpr float kTimeStep() { return 1.0f/60.0f; }
constexpr int kVelocityIterations() { return 8; }
constexpr int kPositionIterations() { return 3; }

using Gavestone = shadow_pumpkin_caster::entity::enemy::Gravestone;

template <typename T>
void processEntityList(std::list<std::unique_ptr<T>> &p_entities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            p_entities.erase(deadEntity);
        }
    }
}

template <typename T>
void processEntityList(b2World &p_world, std::list<std::unique_ptr<T>> &p_entities,
                       std::list<std::unique_ptr<Gavestone>> &m_gravestones) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            m_gravestones.push_back(std::make_unique<Gavestone>(p_world,
                                                                (*deadEntity)->getPosition(),
                                                                (*deadEntity)->getRadius()));
            p_entities.erase(deadEntity);
        }
    }
}

template <typename T>
void drawEntityList(std::list<std::unique_ptr<T>> &p_entities, const visual::Camera &p_camera) {
    for (auto &entity : p_entities) {
        entity->draw(p_camera);
    }
}

};

namespace shadow_pumpkin_caster {

LevelManager::LevelManager(): m_world(b2Vec2(0.0f, -9.81f)),
                              m_player(&m_world, b2Vec2(0.0f, 5.0f)) {
    reset();
    m_world.SetContactListener(&m_collisionListener);
}

LevelManager::~LevelManager() {
    clearAll();
}

void LevelManager::processEvents() {
    m_world.Step(kTimeStep(), kVelocityIterations(), kPositionIterations());
    processEntityList(m_entities.m_dynamic);
    processEntityList(m_world, m_entities.m_skeletons, m_entities.m_gravestones);
    processEntityList(m_entities.m_gravestones);

    m_player.processEvents();
}

void LevelManager::draw(const visual::Camera &p_camera) {
    drawEntityList(m_entities.m_dynamic, p_camera);
    drawEntityList(m_entities.m_static, p_camera);
    drawEntityList(m_entities.m_skeletons, p_camera);
    drawEntityList(m_entities.m_gravestones, p_camera);

    m_player.draw(p_camera);
}

void LevelManager::reset() {
    clearAll();
    std::cout << "Level: ";
    int level;
    std::cin >> level;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (level) {
        case 1: level::setUpLevel_1(m_world, m_entities); break;
        case 2: level::setUpLevel_2(m_world, m_entities); break;
        case 3: level::setUpLevel_3(m_world, m_entities); break;
        case 4: level::setUpLevel_4(m_world, m_entities); break;
        case 5: level::setUpLevel_5(m_world, m_entities); break;

        default: level::setUpDemoLevel(m_world, m_entities);
    }
}

void LevelManager::clearAll() {
    m_entities.m_static.clear();
    m_entities.m_dynamic.clear();
    m_entities.m_skeletons.clear();
    m_entities.m_gravestones.clear();
    m_player.clearAllDynamicEntities();
}

}; // end of namespace shadow_pumpkin_caster