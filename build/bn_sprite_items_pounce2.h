#ifndef BN_SPRITE_ITEMS_POUNCE2_H
#define BN_SPRITE_ITEMS_POUNCE2_H

#include "bn_sprite_item.h"

//{{BLOCK(pounce2_bn_gfx)

//======================================================================
//
//	pounce2_bn_gfx, 32x256@4, 
//	+ palette 16 entries, not compressed
//	+ 128 tiles not compressed
//	Total size: 32 + 4096 = 4128
//
//	Time-stamp: 2024-12-19, 05:30:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_POUNCE2_BN_GFX_H
#define GRIT_POUNCE2_BN_GFX_H

#define pounce2_bn_gfxTilesLen 4096
extern const bn::tile pounce2_bn_gfxTiles[128];

#define pounce2_bn_gfxPalLen 32
extern const bn::color pounce2_bn_gfxPal[16];

#endif // GRIT_POUNCE2_BN_GFX_H

//}}BLOCK(pounce2_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item pounce2(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(pounce2_bn_gfxTiles, 128), bpp_mode::BPP_4, compression_type::NONE, 8), 
            sprite_palette_item(span<const color>(pounce2_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

