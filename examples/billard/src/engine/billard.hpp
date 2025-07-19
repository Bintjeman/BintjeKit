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
    class Billard : public bnjkit::engine::DefaultEngine {
    public:
        Billard();
        ~Billard() override;
        void configure() override;
        void add_ball();
        [[nodiscard]] std::string name() const override;

    private:
    };
} // bil

#endif //BILLARD_HPP
