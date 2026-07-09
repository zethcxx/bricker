// ---------------------------------------------------------------------------------------------- //
                                   export module core:engine;
// ---------------------------------------------------------------------------------------------- //

import lbyte.stx.core;
import std           ;

import :interfaces;
import :types     ;
import :config    ;

using namespace lbyte::stx;
using namespace std       ;

namespace bricker
{
    // -- engine -----------------------------------------------------------------------------------
    export class engine {
        private:
            // -- members --------------------------------------------------------------------------
            system_state state     = system_state::MENU;
            game_id      active_id = game_id     ::NONE;

            array<u8, config::total_pixels> buffer {};

            unique_ptr<game_engine     > active_game = null;
            unique_ptr<sound_controller> sound       = make_unique<null_sound_player>();

        public:
            // -- constructors ---------------------------------------------------------------------
            engine()                         = default; // constructor defaul --------
            engine(engine&&)                 = default; // move constructor ----------
            engine& operator=(engine&&)      = default; // move Assignment operator --

            engine(const engine&)            = delete ; // copy constructor ----------
            engine& operator=(const engine&) = delete ; // copy Assignment operator --

            // -- lifecycle ------------------------------------------------------------------------
            auto set_game(game_id id, unique_ptr<game_engine> game, u8 level = 1, u8 speed = 1) {
                state       = system_state::PLAYING;
                active_id   = id;
                active_game = move(game);

                active_game->set_sound(*sound);
                active_game->start(level, speed);
                sound->beep(660, 80);
            }

            auto update(u32 delta_time_ms) {
                if (state == system_state::PLAYING && active_game) {
                    active_game->update(delta_time_ms);

                    if (active_game->is_game_over())
                        state = system_state::GAME_OVER;
                }
            }

            auto render() {
                if (active_game) {
                    game_buffer view{buffer.data()};
                    active_game->render(view);
                }
            }

            // -- input ----------------------------------------------------------------------------
            auto handle_input(button btn, button_event event) {
                using enum system_state;
                using enum button_event;
                using enum button;

                switch ( state ) {
                    case PLAYING:
                        if ( btn == START and event == PRESSED ) {
                            state = PAUSE;
                            return;
                        }

                        if ( btn == SOUND and event == PRESSED ) {
                            sound->toggle();

                            if (sound->is_enabled())
                                sound->beep(1100, 40);

                            return;
                        }

                        if (active_game)
                            active_game->handle_input(btn, event);

                        break;

                    case PAUSE:
                        if ( btn == START and event == PRESSED ) {
                            state = PLAYING;

                        } else if ( btn == RESET and event == PRESSED ) {
                            state = MENU;
                            active_game.reset();
                        }

                        break;

                    case GAME_OVER:
                        if ( event == PRESSED and (btn == START or btn == RESET) ) {
                            state = MENU;
                            active_game.reset();
                        }

                        break;

                    case MENU: break;
                }
            }

            // -- sound ----------------------------------------------------------------------------
            auto set_sound_controller(unique_ptr<sound_controller> controller) {
                if (not controller) return;

                bool was = sound->is_enabled();
                sound = std::move(controller);
                sound->set_enabled(was);

                if (active_game)
                    active_game->set_sound(*sound);
            }

            auto is_sound_enabled() const { return sound->is_enabled(); }

            // -- queries --------------------------------------------------------------------------
            auto get_buffer_view   () const { return const_game_buffer{ buffer.data() }; }

            auto get_current_state () const noexcept -> system_state { return state;     }
            auto get_active_game_id() const noexcept -> game_id      { return active_id; }

            auto get_score() const noexcept { return active_game ? active_game->get_score() : 0; }
            auto get_level() const noexcept { return active_game ? active_game->get_level() : 0; }
    };
} // namespace bricker

