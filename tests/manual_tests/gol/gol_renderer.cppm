/*!
 * @file gol_renderer.cppm
 * @author bintjeman
 * @date 10.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
export module gol:renderer;
import :map;
namespace gol {
    export class GolRenderer : public sf::Drawable {
    public:
        void initialize() {
            vertices_.setPrimitiveType(sf::PrimitiveType::Triangles);
            vertices_.resize(map_->cells.size() * 6);
            color_map_.resize(map_->max_value);
            color_generator();
        }

        void prerendering() {
            for (unsigned int i = 0; i < map_->cells.size(); ++i) {
                const auto cell = map_->cells[i];
                const auto color = color_map_[cell.first];
                const sf::Vector2i pos = map_->index_to_coord(i);
                const auto index = i * 6;
                vertices_[index + 0].color = color;
                vertices_[index + 1].color = color;
                vertices_[index + 2].color = color;
                vertices_[index + 3].color = color;
                vertices_[index + 4].color = color;
                vertices_[index + 5].color = color;
                vertices_[index + 0].position = sf::Vector2f(pos.x*cellule_size.x, pos.y*cellule_size.y);
                vertices_[index + 1].position = sf::Vector2f((pos.x+1)*cellule_size.x, pos.y*cellule_size.y);
                vertices_[index + 2].position = sf::Vector2f((pos.x+1)*cellule_size.x, (pos.y+1)*cellule_size.y);
                vertices_[index + 3].position = sf::Vector2f((pos.x+1)*cellule_size.x, (pos.y+1)*cellule_size.y);
                vertices_[index + 4].position = sf::Vector2f(pos.x*cellule_size.x, (pos.y+1)*cellule_size.y);
                vertices_[index + 5].position = sf::Vector2f((pos.x+0)*cellule_size.x, (pos.y+0)*cellule_size.y);
            }
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(vertices_, states);
        }

        void set_map(std::shared_ptr<Map> map) {
            map_ = map;
        }

    private:
        void color_generator() {
            constexpr unsigned int colors_total = 255 + 255 + 255 + 255 + 255 + 254;
            const auto colors_number = map_->max_value;
            const auto step = colors_total / colors_number;
            for (unsigned int i = 0; i < map_->max_value; ++i) {
                for (unsigned int i = 0; i < colors_number; ++i) {
                    const unsigned int color_index = i * step;
                    color_map_[i] = get_rainbow_color(color_index);
                }
            }
        }

        static sf::Color get_rainbow_color(unsigned int color_index) {
            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
            if (color_index < 255) {
                // Red to Yellow : 255
                r = 255; // 255
                g = static_cast<unsigned char>(color_index); // 0=>255
                b = 0; // 0
            } else if (color_index < 255 + 255) {
                // Yellow to Green : 255 + 255
                r = 255 - (static_cast<unsigned char>(color_index - 255)); // 255=>0
                g = 255; // 255
                b = 0; // 0
            } else if (color_index < 255 + 255 + 255) {
                // Green to Cyan : 255 + 255 + 255
                r = 0; // 0
                g = 255u; // 255
                b = static_cast<unsigned char>(color_index - (255 + 255)); // 0 => 255
            } else if (color_index < 255 + 255 + 255 + 255) {
                // Cyan to Blue : 255 + 255 + 255 + 255
                r = 0;
                g = static_cast<unsigned char>(255 - color_index - (255 + 255 + 255));
                b = 255;
            } else if (color_index < 255 + 255 + 255 + 255 + 255) {
                // Blue to Magenta : 255 + 255 + 255 + 255 + 254
                r = static_cast<unsigned char>(color_index - (255 + 255 + 255 + 255));
                g = 0;
                b = 255;
            } else if (color_index < 255 + 255 + 255 + 255 + 255 + 254) {
                // Magenta to Red : 255 + 255 + 255 + 255 + 255 + 254
                r = 255;
                g = 0;
                b = static_cast<unsigned char>(255 - (color_index - (255 + 255 + 255 + 255 + 255)));
            }


            return sf::Color{r, g, b};
        }

        sf::Vector2f cellule_size{1.f, 1.f};
        std::shared_ptr<Map> map_;
        sf::VertexArray vertices_;
        std::vector<sf::Color> color_map_;
    };
}
