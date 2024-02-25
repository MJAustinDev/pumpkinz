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

#include "missionManager.h"
#include "pumpkinPatchMission_1_15.h"
#include "implementedMissions.h"

namespace shadow_pumpkin_caster::missions {

void MissionManager::processEvents() {
    if (m_mission != nullptr) {
        m_mission->processEvents();
    }
}

void MissionManager::draw(const io::visual::Camera &p_camera) {
    if (m_mission != nullptr) {
        m_mission->draw(p_camera);
    }
}

bool MissionManager::startMission(Regions p_region, unsigned int p_mission) {
    if (!isMissionImplemented(p_region, p_mission)) {
        return false;
    }

    if (m_mission != nullptr) {
        m_mission.reset();
    }

    m_mission = std::make_unique<Mission>(p_region, p_mission);
    return true;
}

}; // end of namespace shadow_pumpkin_caster::missions
