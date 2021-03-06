/* Copyright (c) IAIK, Graz University of Technology, 2015.
 * All rights reserved.
 * Contact: http://opensource.iaik.tugraz.at
 * 
 * This file is part of the Secure Block Device Library.
 * 
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and SIC. For further information
 * contact us at http://opensource.iaik.tugraz.at.
 * 
 * Alternatively, this file may be used under the terms of the GNU General
 * Public License as published by the Free Software Foundation version 2.
 * 
 * The Secure Block Device Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with the Secure Block Device Library. If not, see <http://www.gnu.org/licenses/>.
 */
///
/// \file
/// \brief Implements functions used to debug the Secure Block Device Library.
///
#include "sbdi_cache.h"

#include <inttypes.h>
#include <stdio.h>

#ifdef SBDI_DEBUG
int debug = 1;
#else
int debug = 0;
#endif

void sbdi_dbg_print_delim()
{
#ifndef SBDI_NO_DEBUG
  printf(
      "================================================================================\n");
#endif
}

void sbdi_dbg_print_block(sbdi_block_t *blk)
{
  assert(blk);
#ifndef SBDI_NO_DEBUG
  printf("[BLK]: {0x%08" PRIx32 ", %p}\n", blk->idx, (void *) blk->data);
#endif
}

void sbdi_dbg_print_sbdi_bl_write_data_block_params(unsigned char *ptr,
    uint32_t idx, size_t off, size_t len)
{
#ifndef SBDI_NO_DEBUG
  printf("[SBDI_BL_WRITE_DB]: (ptr: %p, idx: %" PRIu32 ", off: %zx, len: %zx)\n", ptr,
      idx, off, len);
#endif
}

void sbdi_dbg_print_cache_idx(sbdi_bc_t *cache)
{
  assert(cache);
#ifndef SBDI_NO_DEBUG
  sbdi_bc_idx_t *idx = &cache->index;
  printf("[IDX]: Least Recently Used: %02" PRIu32 "\n", idx->lru);
  for (uint32_t i = 0; i < SBDI_CACHE_MAX_SIZE; ++i) {
    printf("[IDX][%02" PRIu32 "]:{0x%08" PRIx32 ", %02" PRIu32, i,
        idx->list[i].block_idx, idx->list[i].cache_idx);
    char dirty = (sbdi_bc_is_elem_dirty(cache, i)) ? 'd' : ' ';
    sbdi_bc_bt_t t = sbdi_bc_get_blk_type(cache, i);
    char type = ' ';
    switch (t) {
    case SBDI_BC_BT_DATA:
      type = 'd';
      break;
    case SBDI_BC_BT_MNGT:
      type = 'm';
      break;
    default:
      type = 'e';
      break;
    }
    printf(", [%c%c]}\n", dirty, type);
  }
#endif
}
