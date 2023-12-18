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
#include "levelManager.h"
#include "menuButton.h"

using namespace shadow_pumpkin_caster;

int main() {

    MenuButton m1(ButtonCoords(-0.5f, 0.5f, 0.7f, 0.9f));

    std::vector<b2Vec2> waterPoints = {
        b2Vec2(-500.0f, 0.5f),
        b2Vec2(-500.0f, -0.5f),
        b2Vec2(500.0f, -0.5f),
        b2Vec2(500.0f, 0.5f)
    };

    if (!glfwInit()) {
        return -1;
    }

    srand(time(NULL));
    visual::Camera camera;
    glfwWindowHint(GLFW_MAXIMIZED, 1); // attempt to start with a maximised window
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Pumpkinz", NULL, NULL); // TODO RENAME GAME...
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    InputController userInput(window, &camera);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear colour to pure black
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set blending function for transparency
    glEnable(GL_BLEND);

    glfwSwapBuffers(window);

    float timer = glfwGetTime();
    bool reset = false; // TODO REMOVE TEMPORY LEVEL SELECTION SYSTEM
    //LevelManager levelManager;

    while (!glfwWindowShouldClose(window)) {

        if (InputController::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }

        /*
        if (InputController::isKeyPressed(GLFW_KEY_R)) {
            if (!reset) {
                reset = true;
            }
        }
        if (reset && !InputController::isKeyPressed(GLFW_KEY_R)) {
            reset = false; // only reset on key release
            levelManager.reset();
        }*/

        // TODO INTEGRATE CONTROLS WITH GAME/LEVEL MANAGEMENT
        b2Vec2 cameraShift(0.0f, 0.0f);
        const float kShiftAmount = 0.0005f;
        if (InputController::isKeyPressed(GLFW_KEY_A)) {
            cameraShift.x -= kShiftAmount;
        }
        if (InputController::isKeyPressed(GLFW_KEY_D)) {
            cameraShift.x += kShiftAmount;
        }

        if (InputController::isKeyPressed(GLFW_KEY_W)) {
            cameraShift.y += kShiftAmount;
        }

        if (InputController::isKeyPressed(GLFW_KEY_S)) {
            cameraShift.y -= kShiftAmount;
        }

        auto scroll = static_cast<float>(InputController::getScrollY());
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

            m1.draw();

            // process game events
            //levelManager.processEvents();
            //levelManager.draw(camera);

            glColor4f(1.0f, 0.2f, 0.2f, 0.5f); // TODO REMOVE TESTING WATER BOX
            camera.drawPolygon(b2Vec2(0.0f, -10.0f), 0.0f, waterPoints);

            glfwSwapBuffers(window);
            timer = glfwGetTime() + (1.0f/60.0f);
        }

        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Exited successfully\n"; // TODO REMOVE LATER
    return 0;
}
