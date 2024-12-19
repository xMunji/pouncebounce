#ifndef BN_REGULAR_BG_ITEMS_MAINSCREEN_H
#define BN_REGULAR_BG_ITEMS_MAINSCREEN_H

#include "bn_regular_bg_item.h"

//{{BLOCK(mainscreen_bn_gfx)

//======================================================================
//
//	mainscreen_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 736 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x32 
//	Total size: 32 + 12444 + 1796 = 14272
//
//	Time-stamp: 2024-12-19, 05:30:46
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAINSCREEN_BN_GFX_H
#define GRIT_MAINSCREEN_BN_GFX_H

#define mainscreen_bn_gfxTilesLen 12444
extern const bn::tile mainscreen_bn_gfxTiles[736];

#define mainscreen_bn_gfxMapLen 1796
extern const bn::regular_bg_map_cell mainscreen_bn_gfxMap[898];

#define mainscreen_bn_gfxPalLen 32
extern const bn::color mainscreen_bn_gfxPal[16];

#endif // GRIT_MAINSCREEN_BN_GFX_H

//}}BLOCK(mainscreen_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item mainscreen(
            regular_bg_tiles_item(span<const tile>(mainscreen_bn_gfxTiles, 736), bpp_mode::BPP_4, compression_type::LZ77), 
            bg_palette_item(span<const color>(mainscreen_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(mainscreen_bn_gfxMap[0], size(32, 32), compression_type::LZ77, 1, false));
}

#endif

