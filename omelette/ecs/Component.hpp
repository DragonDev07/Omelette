#pragma once
#include <memory>

class Component {
    public:
        virtual ~Component() = default; // Virtual destructor for polymorphic deletion
        virtual std::unique_ptr<Component> clone() const = 0; // Clone function for copying components
        virtual void update(float deltaTime) = 0; // Update function for updating component state
};
