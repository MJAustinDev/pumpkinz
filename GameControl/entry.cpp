/*

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "GLFW/glfw3.h"
#include "box2d/box2d.h"

#include <iostream>
#include <time.h>

int main() {

    srand(time(NULL));

    if (!glfwInit()) {
        return -1;
    }

    // glfwWindowHint(GLFW_MAXIMIZED, 1); // attempt to start with a maximised window // TODO ENABLE WHEN RATIO IS COMPLETED
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Pumpkinz", NULL, NULL); // TODO RENAME GAME...

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // glfwSetKeyCallback(window, keyHandler); // TODO KEY HANDLER FUNCTION

    glClearColor(0.10f,0.10f,0.25f,1.0f); // set clear colour
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set blending function for transparency
    glEnable(GL_BLEND);

    glViewport(0, 0, 1600, 900); // TODO CHANGE VIEWPORT SO RATIO-ED

    float timer = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        if (timer < glfwGetTime()) {
            glClear(GL_COLOR_BUFFER_BIT);

            // process game events
            // world.Step((1.0f/60.0f), 8, 3);

            // draw game world

            glfwSwapBuffers(window);
            timer = glfwGetTime() + (1.0f/60.0f);
        }

        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Exited successfully\n"; // TODO REMOVE LATER
    return 0;
}
