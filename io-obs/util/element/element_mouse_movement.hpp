/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#pragma once

#include "element_texture.hpp"
#include "util/layout_constants.hpp"

enum stat_type
{
    stat_pos,
    stat_scroll_amount,
    stat_lmb,
    stat_rmb,
    stat_mmb
};

/* Contains all information about mouse movement,
 * button clicks and scroll motion
 */
class element_data_mouse_stats : public element_data
{
public:
    element_data_mouse_stats(int16_t x, int16_t y);

    element_data_mouse_stats(stat_type type);

    element_data_mouse_stats(int scroll_amount);

    bool is_persistent() override;

    void merge(element_data* other) override;

    float get_mouse_angle(sources::shared_settings* settings);

    void get_mouse_offset(sources::shared_settings* settings,
        const vec2& center, vec2& out, const uint8_t radius) const;
private:
    stat_type m_type;

    int16_t m_x{}, m_y{};
    int16_t m_last_x{}, m_last_y{};
    uint32_t m_lmbcount_total{}, m_lmbcount_current{}, m_rmbcount_total{}, m_rmbcount_current{},
        m_mmbcount_total{}, m_mmbcount_current{};
    int32_t m_wheel_up_total{}, m_wheel_down_total{}, m_wheel_current{};

    float m_old_angle{};
};

class element_mouse_movement : public element_texture
{
public:
    element_mouse_movement();

    void load(ccl_config* cfg, const std::string& id) override;

    void draw(gs_effect_t* effect, gs_image_file_t* image,
        element_data* data, sources::shared_settings* settings) override;

    data_source get_source() override { return MOUSE_POS; }

private:
    mouse_movement_type m_movement_type;
    vec2 m_offset_pos = {};
    uint8_t m_radius = 0;
};
