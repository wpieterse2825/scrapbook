// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>

#include <memory>

#include "foundation/virtual_base.hpp"

namespace wpieterse2825::game_tools {
    class FAllocator : public FVirtualBase {
      public:
        virtual void* Allocate(size_t buffer_size) = 0;
        virtual void  Deallocate(void* buffer)     = 0;

        template <typename TObjectType, typename... TArguments>
        TObjectType* AllocateObject(TArguments&&... arguments);

        template <typename TObjectType>
        void DeallocateObject(TObjectType* object);

        template <typename TObjectType, typename... TArguments>
        TObjectType* AllocateContainer(size_t elements, TArguments&&... arguments);

        template <typename TObjectType>
        void DeallocateContainer(TObjectType* container, size_t elements);
    };

    FAllocator* GetSystemAllocator();

    template <typename TObjectType, typename... TArguments>
    TObjectType* FAllocator::AllocateObject(TArguments&&... arguments) {
        auto object_size        = sizeof(TObjectType);
        auto buffer             = Allocate(object_size);
        auto constructed_buffer = new (buffer) TObjectType(std::forward<TArguments>(arguments)...);

        return constructed_buffer;
    }

    template <typename TObjectType>
    void FAllocator::DeallocateObject(TObjectType* object) {
        object->~TObjectType();

        Deallocate(object);
    }

    template <typename TObjectType, typename... TArguments>
    TObjectType* FAllocator::AllocateContainer(size_t elements, TArguments&&... arguments) {
        auto object_size    = sizeof(TObjectType);
        auto container_size = object_size * elements;
        auto buffer         = static_cast<uint8_t*>(Allocate(container_size));

        for (auto element_index = size_t {0}; element_index < elements; element_index++) {
            auto element_offset = element_index * object_size;
            auto element_buffer = buffer + element_offset;

            new (element_buffer) TObjectType(std::forward<TArguments>(arguments)...);
        }

        return reinterpret_cast<TObjectType*>(buffer);
    }

    template <typename TObjectType>
    void FAllocator::DeallocateContainer(TObjectType* container, size_t elements) {
        for (auto element_index = size_t {0}; element_index < elements; element_index++) {
            auto object = &container[element_index];

            object->~TObjectType();
        }

        Deallocate(container);
    }
} // namespace wpieterse2825::game_tools
