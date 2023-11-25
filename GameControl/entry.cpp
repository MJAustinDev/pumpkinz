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

using namespace shadow_pumpkin_caster;

int main() {

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
    // glfwWindowHint(GLFW_MAXIMIZED, 1); // attempt to start with a maximised window // TODO ENABLE WHEN RATIO IS COMPLETED
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Pumpkinz", NULL, NULL); // TODO RENAME GAME...
    InputController userInput(window, &camera);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glClearColor(0.10f,0.10f,0.25f,1.0f); // set clear colour
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set blending function for transparency
    glEnable(GL_BLEND);

    glViewport(0, 0, 1600, 900); // TODO CHANGE VIEWPORT SO RATIO-ED

    glfwSwapBuffers(window);

    float timer = glfwGetTime();
    bool reset = false; // TODO REMOVE TEMPORY LEVEL SELECTION SYSTEM
    LevelManager levelManager;

    while (!glfwWindowShouldClose(window)) {

        if (InputController::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }

        if (InputController::isKeyPressed(GLFW_KEY_R)) {
            if (!reset) {
                reset = true;
            }
        }
        if (reset && !InputController::isKeyPressed(GLFW_KEY_R)) {
            reset = false; // only reset on key release
            levelManager.reset();
        }

        if (timer < glfwGetTime()) {
            glClear(GL_COLOR_BUFFER_BIT);

            // process game events
            levelManager.processEvents();
            levelManager.draw(camera);

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
