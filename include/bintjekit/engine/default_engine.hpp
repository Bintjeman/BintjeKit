/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_engine.hpp
 */

#ifndef DEFAULT_ENGINE_HPP
#define DEFAULT_ENGINE_HPP
#pragma once
#include "i_engine.hpp"

namespace bnjkit::engine {
    class DefaultEngine : public IEngine {
        public:
        DefaultEngine();
        ~DefaultEngine() override;
        void configure() override;
        [[nodiscard]] std::string name() const override;
    };
}

#endif //DEFAULT_ENGINE_HPP
