/*
 * Copyright (c) 2020-2023 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_HW_BG_BLOCKS_H
#define BN_HW_BG_BLOCKS_H

#include "bn_assert.h"
#include "bn_alignment.h"
#include "bn_compression_type.h"
#include "bn_hw_memory.h"
#include "bn_hw_decompress.h"
#include "bn_hw_bg_blocks_constants.h"

extern "C"
{
    BN_CODE_IWRAM void bn_hw_bg_blocks_commit_half_words(
            const uint16_t* source_data_ptr, unsigned half_words, uint16_t offset, uint16_t* destination_vram_ptr);

    BN_CODE_IWRAM void bn_hw_bg_blocks_commit_words(
            const unsigned* source_data_ptr, unsigned words, unsigned word_offset, unsigned* destination_vram_ptr);

    BN_CODE_IWRAM void bn_hw_bg_blocks_commit_blocks(
            const unsigned* source_data_ptr, unsigned blocks, unsigned word_offset, unsigned* destination_vram_ptr);
}

namespace bn::hw::bg_blocks
{
    [[nodiscard]] constexpr int max_blocks()
    {
        return 32;
    }

    [[nodiscard]] constexpr int tiles_alignment_blocks_count()
    {
        return 8;
    }

    [[nodiscard]] constexpr int max_bpp_4_regular_tiles_blocks_count()
    {
        return 16;
    }

    [[nodiscard]] constexpr int max_bpp_8_regular_tiles_blocks_count()
    {
        return 32;
    }

    [[nodiscard]] constexpr int max_affine_tiles_blocks_count()
    {
        return 8;
    }

    [[nodiscard]] constexpr int half_words_per_block()
    {
        return bg_maps::cells_count() / bg_maps::blocks_count();
    }

    [[nodiscard]] inline uint16_t* vram(int block_index)
    {
        return reinterpret_cast<uint16_t*>(MEM_VRAM) + (block_index * half_words_per_block());
    }

    inline void commit(const uint16_t* source_ptr, compression_type compression, int count, uint16_t* destination_ptr)
    {
        switch(compression)
        {

        case compression_type::NONE:
            hw::memory::copy_words(source_ptr, count / 2, destination_ptr);
            break;

        case compression_type::LZ77:
            hw::decompress::lz77_vram(source_ptr, destination_ptr);
            break;

        case compression_type::RUN_LENGTH:
            hw::decompress::rl_vram(source_ptr, destination_ptr);
            break;

        case compression_type::HUFFMAN:
            hw::decompress::huff(source_ptr, destination_ptr);
            break;

        default:
            BN_ERROR("Unknown compression type: ", int(compression));
            break;
        }
    }

    [[nodiscard]] inline uint16_t regular_map_cells_offset(unsigned tiles_offset, unsigned palette_offset)
    {
        return uint16_t((palette_offset << 12) + tiles_offset);
    }

    [[nodiscard]] inline uint16_t affine_map_cells_offset(unsigned tiles_offset)
    {
        return uint16_t((tiles_offset << 8) + tiles_offset);
    }
}

#endif
