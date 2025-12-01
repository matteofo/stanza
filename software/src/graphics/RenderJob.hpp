#pragma once
#include <iostream>

namespace stanza {
    enum RenderJobType {
        RENDER_TEXT,
        RENDER_TEXTURE
    };

    struct RenderJob {
        RenderJobType type;
        
    };
}