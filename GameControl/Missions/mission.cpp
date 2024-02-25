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

#include "mission.h"
#include "implementedMissions.h"

namespace {

using Gavestone = shadow_pumpkin_caster::entity::enemy::Gravestone;
using Skeleton = shadow_pumpkin_caster::entity::enemy::Skeleton;
using MissionEntities_t = shadow_pumpkin_caster::missions::MissionEntities_t;

template <typename T>
void becomeGravestone(b2World &p_world, std::list<std::shared_ptr<Gavestone>> &p_gravestones,
                      std::shared_ptr<T> p_ptr) {
    p_gravestones.push_back(std::make_unique<Gavestone>(p_world, p_ptr->getPosition(),
                                                        p_ptr->getRadius()));
}

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
 * Process game events for entities with no special after death abilities
 * @param p_entities list of entities to process
 * @param p_allEntities structure containing all level entities
 */
template <typename T>
void processHealableList(std::list<std::shared_ptr<T>> &p_entities,
                         MissionEntities_t &p_allEntities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            p_entities.erase(deadEntity);
        } else if ((*it)->getHp() < 100.0f) {
            p_allEntities.hurtEntities.push_back(*it);
        }
    }
}

/**
 * Process game events for entities that become gravestones after death
 * @param p_world box2d world that all entities exist within
 * @param p_entities list of entities to process
 * @param p_allEntities structure containing all level entities
 */
template <typename T>
void processReanimatableList(b2World &p_world, std::list<std::shared_ptr<T>> &p_entities,
                             MissionEntities_t &p_allEntities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            becomeGravestone(p_world, p_allEntities.gravestones, std::move(*deadEntity));
            p_entities.erase(deadEntity);
        } else if ((*it)->getHp() < 100.0f) {
            p_allEntities.hurtEntities.push_back(*it);
        }
    }
}

/**
 * Process game events for spell casting entities that become gravestones after death
 * @param p_world box2d world that all entities exist within
 * @param p_entities list of entities to process
 * @param p_allEntities structure containing all level entities
 * @param p_canCastSpell whether spell casting can begin or not
 * @param p_spell reference to the spell function
 */
template <typename T>
void processSpellCasterList(b2World &p_world, std::list<std::shared_ptr<T>> &p_processEntities,
                            MissionEntities_t &p_allEntities) {
    for (auto it = p_processEntities.begin(); it != p_processEntities.end(); it++) {
        if ((*it)->canCastSpell(p_allEntities)) {
            (*it)->beginCasting();
        }

        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            becomeGravestone(p_world, p_allEntities.gravestones, std::move((*deadEntity)));
            p_processEntities.erase(deadEntity);
        } else {
            if ((*it)->getHp() < 100.0f) {
                p_allEntities.hurtEntities.push_back(*it);
            }
            if ((*it)->isSpellCasted()) {
                (*it)->castSpell(p_world, p_allEntities);
            }
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

Mission::Mission(Regions p_region, unsigned int p_mission):
    m_world(b2Vec2(0.0f, -9.81f)),
    m_playerGun(&m_world, b2Vec2(0.0f, 5.0f))
{
    m_world.SetContactListener(&m_collisionListener);
    auto setUpMission = getMission(p_region, p_mission);
    setUpMission(m_entities, m_world);
}

Mission::~Mission() {

}

void Mission::processEvents() {
    const float kTimeStep = 1.0f/60.0f;
    const int kVelocityIterations = 8;
    const int kPositionIterations = 3;
    m_world.Step(kTimeStep, kVelocityIterations, kPositionIterations);

    m_playerGun.processEvents();
    auto round = m_playerGun.fire();
    if (round != nullptr) {
        addProjectile(round);
    }

    processEntityList(m_entities.projectiles);
    processHealableList(m_entities.destructableBlocks, m_entities);
    processHealableList(m_entities.pumpkins, m_entities);
    processReanimatableList(m_world, m_entities.skeletons, m_entities);
    processHealableList(m_entities.gravestones, m_entities);
    processHealableList(m_entities.ghosts, m_entities);

    processSpellCasterList(m_world, m_entities.necromancers, m_entities);
    processSpellCasterList(m_world, m_entities.witches, m_entities);
    processSpellCasterList(m_world, m_entities.vampires, m_entities);
    m_entities.hurtEntities.clear();
}

void Mission::draw(const io::visual::Camera &p_camera) {
    drawEntityList(m_entities.staticGround, p_camera);
    drawEntityList(m_entities.destructableBlocks, p_camera);
    drawEntityList(m_entities.hurtEntities, p_camera);
    drawEntityList(m_entities.projectiles, p_camera);
    drawEntityList(m_entities.pumpkins, p_camera);
    drawEntityList(m_entities.skeletons, p_camera);
    drawEntityList(m_entities.gravestones, p_camera);
    drawEntityList(m_entities.ghosts, p_camera);
    drawEntityList(m_entities.necromancers, p_camera);
    drawEntityList(m_entities.witches, p_camera);
    drawEntityList(m_entities.vampires, p_camera);

    m_playerGun.draw(p_camera);
}

void Mission::addProjectile(std::shared_ptr<entity::DynamicEntity> p_round) {
    m_entities.projectiles.push_back(std::move(p_round));
}

}; // end of namespace shadow_pumpkin_caster::missions

