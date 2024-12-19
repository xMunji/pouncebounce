#ifndef BN_BG_PALETTE_ITEMS_BACKGROUNDLONG_H
#define BN_BG_PALETTE_ITEMS_BACKGROUNDLONG_H

#include "bn_bg_palette_item.h"

//{{BLOCK(backgroundlong_bn_gfx)

//======================================================================
//
//	backgroundlong_bn_gfx, 1024x1024@4, 
//	+ palette 16 entries, not compressed
//	Total size: 32 = 32
//
//	Time-stamp: 2024-12-19, 05:30:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUNDLONG_BN_GFX_H
#define GRIT_BACKGROUNDLONG_BN_GFX_H

#define backgroundlong_bn_gfxPalLen 32
extern const bn::color backgroundlong_bn_gfxPal[16];

#endif // GRIT_BACKGROUNDLONG_BN_GFX_H

//}}BLOCK(backgroundlong_bn_gfx)

namespace bn::bg_palette_items
{
    constexpr inline bg_palette_item backgroundlong(span<const color>(backgroundlong_bn_gfxPal, 16), 
            bpp_mode::BPP_8, compression_type::NONE);
}

#endif

