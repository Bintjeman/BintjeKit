/*!
 * @author bintjeman
 * @date 19.07.25
 * @name billard.hpp
 */

#ifndef BILLARD_HPP
#define BILLARD_HPP
#pragma once
#include <bintjekit/engine/default_engine.hpp>

namespace bil {
    class Billard final : public bnjkit::engine::DefaultEngine {
    public:
        Billard();
        ~Billard() override;
        void configure() override;
        void add_ball();
        void update() override;
        [[nodiscard]] std::string name() const override;

    private:
        std::size_t m_min_ball{5};
        std::size_t m_max_ball{10};
    };
} // bil

#endif //BILLARD_HPP
