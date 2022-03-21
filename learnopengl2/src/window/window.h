#define __APPLE true
#include "includes.h"
#include "utils/disposable.h"

#ifndef APP_WINDOW
#define APP_WINDOW
class Window: public Disposable {
    private:
        bool glfwInitStatus;
    public: 
        Window(int width, int height, const char *title);

        GLFWwindow *window;

        void show(void (*onUpdate)(Window *window));
        void setFramebufferSizeCallback(void (*sizeCallback)(GLFWwindow *window,int width, int height));
        void dispose() override;
};
#endif