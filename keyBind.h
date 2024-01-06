#include <functional>
#include <vector>
#include "camera.h"
class KeyBinder {
public:
    struct KeyFunctionBinding {
        unsigned char key;
        std::function<void()> function;
    };
    void bindKey(unsigned char key, std::function<void()> function);
    void handleKeyPress(unsigned char key);
private:
    std::vector<KeyFunctionBinding> keyFunctionBindings;
};