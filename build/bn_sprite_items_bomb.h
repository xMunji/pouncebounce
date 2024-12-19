#ifndef BN_SPRITE_ITEMS_BOMB_H
#define BN_SPRITE_ITEMS_BOMB_H

#include "bn_sprite_item.h"

//{{BLOCK(bomb_bn_gfx)

//======================================================================
//
//	bomb_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 32 + 512 = 544
//
//	Time-stamp: 2024-12-19, 05:30:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOMB_BN_GFX_H
#define GRIT_BOMB_BN_GFX_H

#define bomb_bn_gfxTilesLen 512
extern const bn::tile bomb_bn_gfxTiles[16];

#define bomb_bn_gfxPalLen 32
extern const bn::color bomb_bn_gfxPal[16];

#endif // GRIT_BOMB_BN_GFX_H

//}}BLOCK(bomb_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item bomb(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(bomb_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(bomb_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

