// ---------------------------------------------------------------------------------------------- //
                                   export module core:types;
// ---------------------------------------------------------------------------------------------- //

import lbyte.stx.core;

using namespace lbyte::stx;

export namespace bricker
{
    // -- system states ----------------------------------------------------------------------------
    enum class system_state : u8 {
        MENU     ,
        PLAYING  ,
        PAUSE    ,
        GAME_OVER
    };

    // -- input buttons ----------------------------------------------------------------------------
    enum class button : u8 {
        UP    ,
        DOWN  ,
        LEFT  ,
        RIGHT ,
        ACTION,
        START ,
        SOUND ,
        RESET
    };

    // -- button events ----------------------------------------------------------------------------
    enum class button_event : u8 {
        PRESSED ,
        RELEASED
    };

    // -- game identifiers -------------------------------------------------------------------------
    enum class game_id : u8 {
        NONE    ,
        SNAKE   ,
        TETRIS  ,
        TANKS   ,
        RACING  ,
        BREAKOUT
    };

    // -- sount note -------------------------------------------------------------------------------
    struct note {
        u32 freq_hz;
        u32 dur_ms ;
    };
} // namespace bricker

