
@{{BLOCK(apple_bn_gfx)

@=======================================================================
@
@	apple_bn_gfx, 32x32@4, 
@	+ palette 16 entries, not compressed
@	+ 16 tiles not compressed
@	Total size: 32 + 512 = 544
@
@	Time-stamp: 2024-12-19, 05:30:45
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global apple_bn_gfxTiles		@ 512 unsigned chars
	.hidden apple_bn_gfxTiles
apple_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x005D0000,0x05550000,0x555D0000,0x95550000,0x5A900000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x06675000,0x06666670,0x06666667,0x07666665
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x50000000,0x55000000,0x15000000,0x11500000,0x11500000,0x11100000
	.word 0x59500000,0x5A551150,0xA3131115,0x31311111,0x11331111,0x11111111,0x13B33111,0x31153511
	.word 0x00776667,0x00311565,0x53131358,0x31313111,0x13131311,0x31113131,0x13111113,0x31111111
	.word 0x00000000,0x00000000,0x00000000,0x00000005,0x00000053,0x00000031,0x00000513,0x00000531

	.word 0x11100000,0x11100000,0x13100000,0x11100000,0x13000000,0x31000000,0x19000000,0x37000000
	.word 0x11111331,0x1111B531,0x11113B31,0x11111131,0x11111111,0x11111111,0x11111111,0x11111131
	.word 0x11111111,0x31111111,0x33111111,0x31111111,0x31331111,0x31311111,0x31131111,0x31111111
	.word 0x00000333,0x00000531,0x00000313,0x00000531,0x00000053,0x00000031,0x00000003,0x00000005
	.word 0x70000000,0x80000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x13331333,0x31313131,0x33131318,0x31313180,0x73335500,0x00000000,0x00000000,0x00000000
	.word 0x53331111,0x51313131,0x03133313,0x00513135,0x0007533D,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global apple_bn_gfxPal		@ 32 unsigned chars
	.hidden apple_bn_gfxPal
apple_bn_gfxPal:
	.hword 0x73E0,0x23BF,0x1E9F,0x12B5,0x0900,0x21C4,0x10EF,0x473F
	.hword 0x1CE8,0x25F5,0x0868,0x044A,0x258F,0x3AFF,0x0000,0x0000

@}}BLOCK(apple_bn_gfx)
