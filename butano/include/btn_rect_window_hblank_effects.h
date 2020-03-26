#ifndef BTN_RECT_WINDOW_HBLANK_EFFECTS_H
#define BTN_RECT_WINDOW_HBLANK_EFFECTS_H

#include "btn_rect_window.h"
#include "btn_optional_fwd.h"
#include "btn_hblank_effect_ptr.h"

namespace btn
{

class rect_window_boundaries_hblank_effect_ptr : public hblank_effect_ptr
{

public:
    [[nodiscard]] static rect_window_boundaries_hblank_effect_ptr create_horizontal(
            rect_window window, const span<const pair<fixed, fixed>>& deltas_ref);

    [[nodiscard]] static optional<rect_window_boundaries_hblank_effect_ptr> optional_create_horizontal(
            rect_window window, const span<const pair<fixed, fixed>>& deltas_ref);

    [[nodiscard]] static rect_window_boundaries_hblank_effect_ptr create_vertical(
            rect_window window, const span<const pair<fixed, fixed>>& deltas_ref);

    [[nodiscard]] static optional<rect_window_boundaries_hblank_effect_ptr> optional_create_vertical(
            rect_window window, const span<const pair<fixed, fixed>>& deltas_ref);

    [[nodiscard]] const rect_window& window() const
    {
        return _window;
    }

    [[nodiscard]] span<const pair<fixed, fixed>> deltas_ref() const;

    void set_deltas_ref(const span<const pair<fixed, fixed>>& deltas_ref);

    void reload_deltas_ref();

private:
    rect_window _window;

    rect_window_boundaries_hblank_effect_ptr(int id, rect_window window);
};

}

#endif