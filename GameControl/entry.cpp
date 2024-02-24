/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "GLFW/glfw3.h"
#include "box2d/box2d.h"
#include <iostream>
#include <time.h>
#include <list>
#include <memory>
#include <limits>
#include "camera.h"
#include "levels.h"
#include "collisionListener.h"
#include "player.h"
#include "inputController.h"
#include "menuPage.h"
#include "missionManager.h"

using namespace shadow_pumpkin_caster;

bool isPressedOnce(int p_key, bool &p_isPressed) {
    if (io::input::InputController::isKeyPressed(p_key)) {
        p_isPressed = true;
    }
    if (p_isPressed && !io::input::InputController::isKeyPressed(p_key)) {
        p_isPressed = false;
        return false;
    }
    return true;
}

int main() {

    Page menuPage;
    turnToMainMenu(menuPage);

    if (!glfwInit()) {
        return -1;
    }

    srand(time(NULL));
    io::visual::Camera camera;
    glfwWindowHint(GLFW_MAXIMIZED, 1); // attempt to start with a maximised window
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Pumpkinz", NULL, NULL); // TODO RENAME GAME...
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    io::input::InputController userInput(window, &camera);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear colour to pure black
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set blending function for transparency
    glEnable(GL_BLEND);

    glfwSwapBuffers(window);

    float timer = glfwGetTime();
    missions::MissionManager missionManager;
    bool inGame = false;
    bool isEscPressed = false;

    while (!glfwWindowShouldClose(window)) {

        // TODO INTEGRATE CONTROLS WITH GAME/LEVEL MANAGEMENT
        b2Vec2 cameraShift(0.0f, 0.0f);
        const float kShiftAmount = 0.0005f;
        if (io::input::InputController::isKeyPressed(GLFW_KEY_A)) {
            cameraShift.x -= kShiftAmount;
        }
        if (io::input::InputController::isKeyPressed(GLFW_KEY_D)) {
            cameraShift.x += kShiftAmount;
        }

        if (io::input::InputController::isKeyPressed(GLFW_KEY_W)) {
            cameraShift.y += kShiftAmount;
        }

        if (io::input::InputController::isKeyPressed(GLFW_KEY_S)) {
            cameraShift.y -= kShiftAmount;
        }

        auto scroll = static_cast<float>(io::input::InputController::getScrollY());
        camera.moveBy(cameraShift, 0.01f * scroll);

        if (timer < glfwGetTime()) {
            glClear(GL_COLOR_BUFFER_BIT);

            // draw backing colour
            glColor4f(0.10f, 0.10f, 0.25f, 1.0f);
            glBegin(GL_POLYGON);
                glVertex2f(-1.0f, -1.0f);
                glVertex2f(-1.0f, 1.0f);
                glVertex2f(1.0f, 1.0f);
                glVertex2f(1.0f, -1.0f);
            glEnd();

            if (inGame) {
                missionManager.processEvents();
                missionManager.draw(camera);

                inGame = isPressedOnce(GLFW_KEY_ESCAPE, isEscPressed);
            } else {
                PageReturnData pageData = processPage(menuPage);
                switch (pageData.m_action) {
                    case PageAction::goMainMenu: { turnToMainMenu(menuPage); break; }
                    case PageAction::goLevelSelect: { turnToLevelSelect(menuPage); break; }
                    case PageAction::goHelp: { break; }
                    case PageAction::quit: { glfwSetWindowShouldClose(window, GLFW_TRUE); break; }
                    case PageAction::goMissionSelect: {
                        turnToMission(menuPage, pageData.m_region);
                        break;
                    }
                    case PageAction::startLevel: {
                        inGame = true;
                        missionManager.startMission(); // pageData.m_region, pageData.m_mission
                        break;
                    }
                }
                drawPage(menuPage);
            }

            glfwSwapBuffers(window);
            timer = glfwGetTime() + (1.0f/60.0f);
        }

        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Exited successfully\n"; // TODO REMOVE LATER
    return 0;
}
