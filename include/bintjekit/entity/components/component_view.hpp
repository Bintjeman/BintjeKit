/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_view.hpp
 */
#ifndef COMPONENT_VIEW_HPP
#define COMPONENT_VIEW_HPP
#pragma once
#include <functional>
#include <vector>
#include "bintjekit/entity/typed_collection.hpp"
namespace bnjkit::entity {
    template<typename T>
    class ComponentView {
    public:
        class Iterator {
        private:
            const ComponentView& m_view;
            size_t m_current_index;
            // Avance jusqu'au prochain élément valide
            void find_next_valid();

        public:
            Iterator(const ComponentView& view, size_t start_index);
            Iterator& operator++();
            bool operator!=(const Iterator& other) const {
                return m_current_index != other.m_current_index;
            }
            typename TypedCollection<T>::EntityPtr operator*() const;
        };
        ComponentView(const TypedCollection<T>& collection,
                      std::function<bool(const typename TypedCollection<T>::EntityPtr&)> filter);
        Iterator begin() const;
        Iterator end() const;
        void freeze();
        void unfreeze();
        [[nodiscard]] bool is_frozen() const;
    private:
        const TypedCollection<T>& m_collection;
        std::function<bool(const typename TypedCollection<T>::EntityPtr&)> m_filter;
        bool m_is_frozen = false;
        std::vector<size_t> m_frozen_indices;
    };
}

#include "bintjekit/entity/components/component_view.inl"
#endif //COMPONENT_VIEW_HPP
