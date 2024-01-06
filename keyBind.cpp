#include "keyBind.h"

void KeyBinder::bindKey(unsigned char key, std::function<void()> function) {
    keyFunctionBindings.push_back({ key, function });
}

void KeyBinder::handleKeyPress(unsigned char key) {
    for (const auto& binding : keyFunctionBindings) {
        if (binding.key == key) {
            binding.function();
            break;
        }
    }
}