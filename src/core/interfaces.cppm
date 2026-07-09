// ---------------------------------------------------------------------------------------------- //
                                 export module core:interfaces;
// ---------------------------------------------------------------------------------------------- //

import lbyte.stx.core;
import std           ;

import :config;
import :types ;

using namespace lbyte::stx;

export namespace bricker
{
    // -- buffer types -----------------------------------------------------------------------------
    using game_buffer = std::mdspan<
        u8,
        std::extents<usize, config::game_height, config::game_width>
    >;

    using const_game_buffer = std::mdspan<
        u8 const,
        std::extents<usize, config::game_height, config::game_width>
    >;

    // -- sound contract ---------------------------------------------------------------------------
    struct sound_controller {
        public:
            virtual ~sound_controller() = default;

            virtual void beep(u32 freq_hz, u32 dur_ms     ) const = 0;
            virtual void play(std::span<note const> melody) const = 0;

            virtual void set_enabled(bool enabled_){ enabled = enabled_; }

            virtual void toggle    ()       { enabled = !enabled; }
            virtual bool is_enabled() const { return enabled    ; }

        protected:
            bool enabled = true;
    };

    struct null_sound_player : sound_controller {
        void beep(u32 freq_hz, u32 dur_ms     ) const override {}
        void play(std::span<note const> melody) const override {}
    };

    // -- game engine contract ---------------------------------------------------------------------
    struct game_engine {
        public:
            virtual ~game_engine() = default;

            virtual void start       (u8 level = 1, u8 speed = 1    ) = 0;
            virtual void handle_input(button btn, button_event event) = 0;

            virtual void update      ( u32         delta_time_ms) = 0;
            virtual void render      ( game_buffer view         ) = 0;

            virtual void set_sound(sound_controller& sound_) { sound = &sound_; }

            virtual bool is_game_over() const noexcept = 0;
            virtual u32  get_score   () const noexcept = 0;
            virtual u8   get_level   () const noexcept = 0;

        protected:
            sound_controller* sound = null;
    };
} // namespace bricker

