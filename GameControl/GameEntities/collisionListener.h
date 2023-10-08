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

#include <box2d/box2d.h>

#include <cmath>
#include <iostream> // TODO REMOVE

namespace {

float calcPureVelocity(b2Vec2 p_velocity) {
    return std::hypotf(p_velocity.x, p_velocity.y);
};

bool isDynamic(b2Body* p_body) {
    return p_body->GetType() == b2BodyType::b2_dynamicBody;
}

void dynamicEnergyTransfer(b2Body* p_bodyA, b2Body* p_bodyB) {
        b2Vec2 relativeVelocity = p_bodyA->GetLinearVelocity() - p_bodyB->GetLinearVelocity();
        float pureVelocity = calcPureVelocity(relativeVelocity);
        float energyMultiplier = 0.5 * pureVelocity * pureVelocity;
        float keneticEnergyA = energyMultiplier * p_bodyA->GetMass();
        float keneticEnergyB = energyMultiplier * p_bodyB->GetMass();

        std::cout << "DA_KE: " << keneticEnergyA << "\n";
        std::cout << "DB_KE: " << keneticEnergyB << "\n";
}

void staticEnergyTransfer(b2Body* p_bodyDynamic) {
    float pureVelocity = calcPureVelocity(p_bodyDynamic->GetLinearVelocity());
    float keneticEnergy = 0.5 * p_bodyDynamic->GetMass() * pureVelocity * pureVelocity;

    std::cout << "S__KE: " << keneticEnergy << "\n";
}

}; // end of namespace

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

        // TODO APPEND KE RESULTS TO BODY'S OBJ DATA, IFF VELOCITY IS ABOVE THRESH HOLD
    };

    void EndContact(b2Contact* contact) {
        // TODO PROBS JUST REMOVE...
    };

};

}; // end of namespace entity
