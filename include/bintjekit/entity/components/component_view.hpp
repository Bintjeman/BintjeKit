/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_view.hpp
 */
#ifndef COMPONENT_VIEW_HPP
#define COMPONENT_VIEW_HPP
#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "bintjekit/entity/fwd.hpp"
namespace bnjkit::entity {
    template<typename T>
    class ComponentView {
    public:
        using EntityPtr = std::shared_ptr<T>;

        class Iterator {
        private:
            const ComponentView& m_view;
            size_t m_current_index;
            void find_next_valid();
        public:
            Iterator(const ComponentView& view, size_t start_index);
            Iterator& operator++();
            bool operator!=(const Iterator& other) const {
                return m_current_index != other.m_current_index;
            }
            EntityPtr operator*() const;
        };

        ComponentView(const EntityCollection& collection,
                      std::function<bool(const EntityPtr&)> filter);
        Iterator begin() const;
        Iterator end() const;
        void freeze();
        void unfreeze();
        [[nodiscard]] bool is_frozen() const;

    private:
        const EntityCollection& m_collection;
        std::function<bool(const EntityPtr&)> m_filter;
        bool m_is_frozen = false;
        std::vector<size_t> m_frozen_indices;
    };
}

#include "bintjekit/entity/components/component_view.inl"
#endif //COMPONENT_VIEW_HPP
