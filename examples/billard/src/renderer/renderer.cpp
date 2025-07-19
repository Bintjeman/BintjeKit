/*!
 * @author bintjeman
 * @date 19.07.25
 * @name renderer.cpp
 */

#include "renderer.hpp"

namespace bil {
    Renderer::Renderer() :DefaultRenderer(){
        m_logger->info("BillardRenderer created");
    }
    Renderer::~Renderer() {
        m_logger->info("BillardRenderer destroyed");
    }
    void Renderer::configure() {
        DefaultRenderer::configure();
        resize_views();
    }
    std::string Renderer::name() const {
        return "BillardRenderer";
    }
} // bil