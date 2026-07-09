// ---------------------------------------------------------------------------------------------- //
                                   export module core:config;
// ---------------------------------------------------------------------------------------------- //

import lbyte.stx.core;
import std           ;

using namespace lbyte::stx;

export namespace bricker::config
{
    // -- grid dimensions --------------------------------------------------------------------------
    inline constexpr u8  game_width   { 10                        };
    inline constexpr u8  game_height  { 20                        };
    inline constexpr u16 total_pixels { game_width * game_height  };

    // -- game limits ------------------------------------------------------------------------------
    inline constexpr u8  max_speed    { 10                        };
    inline constexpr u8  max_level    { 10                        };

    // -- timing -----------------------------------------------------------------------------------
    inline constexpr u32 base_tick_ms { 500                       };

} // namespace bricker::config

