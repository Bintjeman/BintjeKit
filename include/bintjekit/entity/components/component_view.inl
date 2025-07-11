/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_view.inl
 */

#ifndef COMPONENT_VIEW_INL
#define COMPONENT_VIEW_INL
#pragma once
#include "bintjekit/entity/typed_collection.hpp"
#include "bintjekit/entity/entity_collection.hpp"
namespace bnjkit::entity {
    template<typename T>
    void ComponentView<T>::Iterator::find_next_valid() {
        if (m_view.m_is_frozen) {
            // En mode gelé, on est déjà sur des indices valides
            return;
        }

        while (m_current_index < m_view.m_collection.size()) {
            if (m_view.m_filter(m_view.m_collection.entities()[m_current_index])) {
                break;
            }
            ++ m_current_index;
        }
    }
    template<typename T>
    ComponentView<T>::Iterator::Iterator(const ComponentView& view, const size_t start_index): m_view(view),
        m_current_index(start_index) {
        if (!m_view.m_is_frozen) {
            find_next_valid();
        }
    }
    template<typename T>
    typename ComponentView<T>::Iterator& ComponentView<T>::Iterator::operator++() {
        if (m_view.m_is_frozen) {
            ++ m_current_index;
        } else {
            ++ m_current_index;
            find_next_valid();
        }
        return * this;
    }
    template<typename T>
    typename ComponentView<T>::EntityPtr ComponentView<T>::Iterator::operator*() const {
        return m_view.m_collection.entities()[m_current_index];
    }
    template<typename T>
    ComponentView<T>::ComponentView(const EntityCollection& collection, std::function<bool(const EntityPtr&)> filter): m_collection(
        collection) {
        m_filter = filter;
        m_is_frozen = false;
    }

    template<typename T>
    typename ComponentView<T>::Iterator ComponentView<T>::begin() const {
        if (m_is_frozen) {
            return Iterator(* this, 0);
        }
        return Iterator(* this, 0);
    }
    template<typename T>
    typename ComponentView<T>::Iterator ComponentView<T>::end() const {
        if (m_is_frozen) {
            return Iterator(* this, m_frozen_indices.size());
        }
        return Iterator(* this, m_collection.size());
    }
    template<typename T>
    void ComponentView<T>::freeze() {
        if (m_is_frozen) return;

        m_frozen_indices.clear();
        for (size_t i = 0; i < m_collection.size(); ++ i) {
            if (m_filter(m_collection.entities()[i])) {
                m_frozen_indices.push_back(i);
            }
        }
        m_is_frozen = true;
    }
    template<typename T>
    void ComponentView<T>::unfreeze() {
        m_is_frozen = false;
        m_frozen_indices.clear();
    }
    template<typename T>
    bool ComponentView<T>::is_frozen() const { return m_is_frozen; }
}
#endif //COMPONENT_VIEW_INL
