// /*!
//  * @author bintjeman
//  * @date 26.06.25
//  * @name entitymanager.cpp
//  */
// #include "bintjekit/entity/entitymanager.hpp"
// #include "bintjekit/logger.hpp"
//
// namespace bnjkit {
//     namespace entity {
//         template<typename BaseEntity>
//             requires std::derived_from<BaseEntity, IEntity>
//         EntityManager<BaseEntity>::EntityManager() {
//             m_logger = spdlog::get("entity_manager");
//         }
//
//         template<typename BaseEntity>
//             requires std::derived_from<BaseEntity, IEntity>
//         EntityManager<BaseEntity>::~EntityManager() = default;
//
//         template<typename BaseEntity>
//             requires std::derived_from<BaseEntity, IEntity>
//         void EntityManager<BaseEntity>::update() {
//             for (auto& [type, collection]: m_collections) {
//                 for (auto& entity: collection->get_collection()) {
//                     if (auto ptr = entity.lock()) {
//                         ptr->update();
//                     }
//                 }
//             }
//         }
//     } // entity
// } // bnjkit
