#pragma once

#include <stddef.h>
#include <stdint.h>

#include <memory>

#include "game_tools/virtual_base.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    class Allocator : public VirtualBase {
      public:
        virtual void* Allocate(size_t buffer_size) = 0;
        virtual void  Deallocate(void* buffer)     = 0;

        template <typename ObjectType, typename... Arguments>
        ObjectType* AllocateObject(Arguments&&... arguments);

        template <typename ObjectType>
        void DeallocateObject(ObjectType* object);

        template <typename ObjectType, typename... Arguments>
        ObjectType* AllocateContainer(size_t elements, Arguments&&... arguments);

        template <typename ObjectType>
        void DeallocateContainer(ObjectType* container, size_t elements);
    };

    Allocator* GetSystemAllocator();

    template <typename ObjectType, typename... Arguments>
    ObjectType* Allocator::AllocateObject(Arguments&&... arguments) {
        auto object_size        = sizeof(ObjectType);
        auto buffer             = Allocate(object_size);
        auto constructed_buffer = new (buffer) ObjectType(std::forward<Arguments>(arguments)...);

        return constructed_buffer;
    }

    template <typename ObjectType>
    void Allocator::DeallocateObject(ObjectType* object) {
        object->~ObjectType();

        Deallocate(object);
    }

    template <typename ObjectType, typename... Arguments>
    ObjectType* Allocator::AllocateContainer(size_t elements, Arguments&&... arguments) {
        auto object_size    = sizeof(ObjectType);
        auto container_size = object_size * elements;
        auto buffer         = static_cast<uint8_t*>(Allocate(container_size));

        for (auto element_index = size_t {0}; element_index < elements; element_index++) {
            auto element_offset = element_index * object_size;
            auto element_buffer = buffer + element_offset;

            new (element_buffer) ObjectType(std::forward<Arguments>(arguments)...);
        }

        return reinterpret_cast<ObjectType*>(buffer);
    }

    template <typename ObjectType>
    void Allocator::DeallocateContainer(ObjectType* container, size_t elements) {
        for (auto element_index = size_t {0}; element_index < elements; element_index++) {
            auto object = &container[element_index];

            object->~ObjectType();
        }

        Deallocate(container);
    }
} // namespace wpieterse2825::scrapbook::game_tools
