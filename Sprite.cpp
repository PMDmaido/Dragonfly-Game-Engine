// 
// Sprite.cpp
//

#include "Sprite.h"
#include <iostream> // For debugging (if needed)
#include "LogManager.h"

namespace df {

    Sprite::Sprite() {
        m_width = 0;
        m_height = 0;
        m_max_frame_count = 0;
        m_frame_count = 0;
        m_color = Color::WHITE;
        m_slowdown = 1;
        m_frame = new Frame;
        m_label = "";
    }

    Sprite::Sprite(int max_frames) {
        m_width = 0;
        m_height = 0;
        m_max_frame_count = max_frames;
        m_frame_count = 0;
        m_color = Color::WHITE;
        m_slowdown = 1;
        m_frame = new Frame[max_frames];
        m_label = "";
    }

    Sprite::~Sprite() {
        if (!m_frame) {
            delete[] m_frame;
        }
    }

    void Sprite::setWidth(int new_width) {
        m_width = new_width;
    }

    int Sprite::getWidth() const {
        return m_width;
    }

    void Sprite::setHeight(int new_height) {
        m_height = new_height;
    }

    int Sprite::getHeight() const {
        return m_height;
    }

    void Sprite::setColor(Color new_color) {
        m_color = new_color;
    }

    Color Sprite::getColor() const {
        return m_color;
    }

    int Sprite::getFrameCount() const {
        return m_frame_count;
    }

    int Sprite::addFrame(Frame new_frame) {
        if (m_frame_count == m_max_frame_count) {
            return -1; // Frame array is full
        }
        m_frame[m_frame_count] = new_frame;
        m_frame_count++;
        return 0; // Success
    }

    Frame Sprite::getFrame(int frame_number) const {
        if (frame_number < 0 || frame_number >= m_frame_count) {
            return Frame(); // Return an empty frame if out of range
        }
        return m_frame[frame_number];
    }

    void Sprite::setLabel(std::string new_label) {
        m_label = new_label;
    }

    std::string Sprite::getLabel() const {
        return m_label;
    }

    void Sprite::setSlowdown(int new_sprite_slowdown) {
        m_slowdown = new_sprite_slowdown;
    }

    int Sprite::getSlowdown() const {
        return m_slowdown;
    }

    int Sprite::draw(int frame_number, Vector position) const {

        if (frame_number < 0 || frame_number >= m_frame_count) {
            return -1; // Invalid frame index
        }

        return m_frame[frame_number].draw(position, m_color);
    }
}