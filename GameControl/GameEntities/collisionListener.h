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

#include <box2d/box2d.h>
#include <cmath>
#include "dynamicEntity.h"
#include "entityData.h"

namespace {

using bodyData = shadow_pumpkin_caster::entity::EntityBodyData;

/**
 * Normalises a velocity vector to work out the true speed
 * @param p_velocity vector to be normalised
 * @return normalised velocity
 */
float calcPureVelocity(b2Vec2 p_velocity) {
    return std::hypotf(p_velocity.x, p_velocity.y);
};

/**
 * Verifies if a b2body is dynamic or not
 * @param p_body body to check the type of
 * @return true iff the body is dynamic
 */
bool isDynamic(b2Body* p_body) {
    return p_body->GetType() == b2BodyType::b2_dynamicBody;
};

/**
 * Verifies if an entity's type is 'impact damage immune'
 * @param p_bodyDataPtr ptr to entity's body data
 * @return true iff the type is 'impact damage immune'
 */
bool isImpactImmune(bodyData* p_bodyDataPtr) {
    return p_bodyDataPtr->m_type == shadow_pumpkin_caster::entity::EntityType::impactDamageImmune;
}

/**
 * Verifies if an entity's type is projectile
 * @param p_bodyDataPtr ptr to entity's body data
 * @return true iff the type is projectile
 */
bool isProjectile(bodyData* p_bodyDataPtr) {
    return p_bodyDataPtr->m_type == shadow_pumpkin_caster::entity::EntityType::projectile;
}

/**
 * Applies kinetic energy transfer to two colliding objects
 * @param p_bodyA physics body of the first object
 * @param p_bodyB physics body of the second object
 */
void dynamicEnergyTransfer(b2Body* p_bodyA, b2Body* p_bodyB) {
    auto* dataPtrA = reinterpret_cast<bodyData*>(p_bodyA->GetUserData().pointer);
    auto* dataPtrB = reinterpret_cast<bodyData*>(p_bodyB->GetUserData().pointer);
    if ((isImpactImmune(dataPtrA) && !isProjectile(dataPtrB)) ||
        (isImpactImmune(dataPtrB) && !isProjectile(dataPtrA))) {
        return; // ghosts/vampires only take damage from direct hits
    }

    b2Vec2 relativeVelocity = p_bodyA->GetLinearVelocity() - p_bodyB->GetLinearVelocity();
    float pureVelocity = calcPureVelocity(relativeVelocity);
    float energyMultiplier = 0.5 * pureVelocity * pureVelocity;
    float kineticEnergyA = energyMultiplier * p_bodyA->GetMass();
    float kineticEnergyB = energyMultiplier * p_bodyB->GetMass();

    dataPtrA->m_energies.push_back(kineticEnergyB);
    dataPtrB->m_energies.push_back(kineticEnergyA);
};

/**
 * Applies total kinetic energy transfer to an object colliding with an immovable wall
 * @param p_bodyDynamic physics body of the colliding object
 */
void staticEnergyTransfer(b2Body* p_bodyDynamic) {
    auto* dataPtr = reinterpret_cast<bodyData*>(p_bodyDynamic->GetUserData().pointer);
    if (isImpactImmune(dataPtr)) {
        return; // ghosts/vampires don't take impact damage
    }

    float pureVelocity = calcPureVelocity(p_bodyDynamic->GetLinearVelocity());
    float kineticEnergy = 0.5 * p_bodyDynamic->GetMass() * pureVelocity * pureVelocity;
    dataPtr->m_energies.push_back(kineticEnergy);
};

}; // end of namespace

namespace shadow_pumpkin_caster {
namespace entity {

class CollisionListener : public b2ContactListener {

private:

    void BeginContact(b2Contact* contact) {
        auto bodyA = contact->GetFixtureA()->GetBody();
        auto bodyB = contact->GetFixtureB()->GetBody();

        if (isDynamic(bodyA) && isDynamic(bodyB)) {
            dynamicEnergyTransfer(bodyA, bodyB);

        } else if (isDynamic(bodyA)) {
            staticEnergyTransfer(bodyA);

        } else if (isDynamic(bodyB)) {
            staticEnergyTransfer(bodyB);
        }
    };
};

}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
