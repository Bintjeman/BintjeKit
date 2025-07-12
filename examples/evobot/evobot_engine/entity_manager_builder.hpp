/*!
 * @author bintjeman
 * @date 12.07.25
 * @name entity_manager_builder.hpp
 */
#ifndef ENTITY_MANAGER_BUILDER_HPP
#define ENTITY_MANAGER_BUILDER_HPP
#pragma once
namespace evo::entity {
    class EvoEntityManager;
    class EntityManagerBuilder {
    public:
        static void setup_default_collections(EvoEntityManager& manager);
        static void setup_default_components(EvoEntityManager& manager);
        static void build_default(EvoEntityManager& manager);
    };
} // evo::entity
#endif //ENTITY_MANAGER_BUILDER_HPP
