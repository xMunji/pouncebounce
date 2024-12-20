#ifndef BN_REGULAR_BG_ITEMS_BACKGROUND_H
#define BN_REGULAR_BG_ITEMS_BACKGROUND_H

#include "bn_regular_bg_item.h"

//{{BLOCK(background_bn_gfx)

//======================================================================
//
//	background_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 847 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), huf compressed, 32x32 
//	Total size: 32 + 12544 + 1944 = 14520
//
//	Time-stamp: 2024-12-19, 05:30:46
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_BN_GFX_H
#define GRIT_BACKGROUND_BN_GFX_H

#define background_bn_gfxTilesLen 12544
extern const bn::tile background_bn_gfxTiles[847];

#define background_bn_gfxMapLen 1944
extern const bn::regular_bg_map_cell background_bn_gfxMap[972];

#define background_bn_gfxPalLen 32
extern const bn::color background_bn_gfxPal[16];

#endif // GRIT_BACKGROUND_BN_GFX_H

//}}BLOCK(background_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item background(
            regular_bg_tiles_item(span<const tile>(background_bn_gfxTiles, 847), bpp_mode::BPP_4, compression_type::LZ77), 
            bg_palette_item(span<const color>(background_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(background_bn_gfxMap[0], size(32, 32), compression_type::HUFFMAN, 1, false));
}

#endif

