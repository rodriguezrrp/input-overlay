/**
 * This file is part of input-overlay
 * which is licensed under the GPL v2.0
 * See LICENSE or http://www.gnu.org/licenses
 * github.com/univrsal/input-overlay
 */
#pragma once

#include <string>
#include "graphics/vec2.h"
#include "graphics/graphics.h"

typedef struct gs_image_file gs_image_file_t;

/**
 * Which data holder to read element
 * data from
 */
enum class data_source
{
    NONE = -1, DEFAULT, GAMEPAD, MOUSE_POS /* TODO: use this?*/
};

namespace sources
{
    class overlay_settings;
}

class ccl_config;

#ifdef _WIN32
enum element_type;
#else

#include "../layout_constants.hpp"

#endif

class element_data
{
public:
    explicit element_data(element_type type);
    virtual ~element_data() = default;

    element_type get_type() const;

    /* true if data should not me removed */
    virtual bool is_persistent()
    { return false; }

    /* used if is persistent */
    virtual void merge(element_data* other)
    {
        UNUSED_PARAMETER(other);
        /* NO-OP */
    }

protected:
    element_type m_type;
};

class element
{
public:
    virtual ~element() = default;

    element();

    element(element_type type);

    virtual void load(ccl_config* cfg, const std::string &id) = 0;

    virtual void
    draw(gs_effect_t* effect, gs_image_file_t* m_image, element_data* data, sources::overlay_settings* settings) = 0;

    element_type get_type() const;

    uint16_t get_keycode() const;

    virtual data_source get_source();

protected:
    void read_mapping(ccl_config* cfg, const std::string &id);

    void read_pos(ccl_config* cfg, const std::string &id);

    vec2 m_pos = {};
    gs_rect m_mapping = {};

    element_type m_type;
    uint16_t m_keycode;
};
