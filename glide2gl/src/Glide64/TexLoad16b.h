/*
* Glide64 - Glide video plugin for Nintendo 64 emulators.
* Copyright (c) 2002  Dave2001
* Copyright (c) 2003-2009  Sergey 'Gonetz' Lipski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

//****************************************************************
//
// Glide64 - Glide Plugin for Nintendo 64 emulators
// Project started on December 29th, 2001
//
// Authors:
// Dave2001, original author, founded the project in 2001, left it in 2002
// Gugaman, joined the project in 2002, left it in 2002
// Sergey 'Gonetz' Lipski, joined the project in 2002, main author since fall of 2002
// Hiroshi 'KoolSmoky' Morii, joined the project in 2007
//
//****************************************************************
//
// To modify Glide64:
// * Write your name and (optional)email, commented by your work, so I know who did it, and so that you can find which parts you modified when it comes time to send it to me.
// * Do NOT send me the whole project or file that you modified.  Take out your modified code sections, and tell me where to put them.  If people sent the whole thing, I would have many different versions, but no idea how to combine them all.
//
//****************************************************************

#define NBITS32_16B (sizeof(uint32_t) * 8)
#define NBITS16_16B (sizeof(uint16_t) * 8)

static INLINE void load16bRGBA(uint8_t *src, uint8_t *dst, int wid_64, int height, int line, int ext)
{
  int v9;
  uint32_t v10;
  uint32_t v11;
  uint32_t *v12;
  uint32_t *v13;
  int v14;
  uint32_t v15;
  uint32_t v16;
  int v17;
  int v18;
  uint32_t *v6 = (uint32_t *)src;
  uint32_t *v7 = (uint32_t *)dst;
  int v8 = height;

  do
  {
    v17 = v8;
    v9 = wid_64;
    do
    {
      v10 = m64p_swap32(*v6);
      v11 = m64p_swap32(v6[1]);
      ALOWORD(v10) = __ROR16((uint16_t)v10, 1, NBITS16_16B);
      ALOWORD(v11) = __ROR16((uint16_t)v11, 1, NBITS16_16B);
      v10 = __ROR32(v10, 16, NBITS32_16B);
      v11 = __ROR32(v11, 16, NBITS32_16B);
      ALOWORD(v10) = __ROR16((uint16_t)v10, 1, NBITS16_16B);
      ALOWORD(v11) = __ROR16((uint16_t)v11, 1, NBITS16_16B);
      *v7 = v10;
      v7[1] = v11;
      v6 += 2;
      v7 += 2;
      --v9;
    }
    while ( v9 );
    if ( v17 == 1 )
      break;
    v18 = v17 - 1;
    v12 = (uint32_t *)&src[(line + (uintptr_t)v6 - (uintptr_t)src) & 0xFFF];
    v13 = (uint32_t *)((char *)v7 + ext);
    v14 = wid_64;
    do
    {
      v15 = m64p_swap32(v12[1]);
      v16 = m64p_swap32(*v12);
      ALOWORD(v15) = __ROR16((uint16_t)v15, 1, NBITS16_16B);
      ALOWORD(v16) = __ROR16((uint16_t)v16, 1, NBITS16_16B);
      v15 = __ROR32(v15, 16, NBITS32_16B);
      v16 = __ROR32(v16, 16, NBITS32_16B);
      ALOWORD(v15) = __ROR16((uint16_t)v15, 1, NBITS16_16B);
      ALOWORD(v16) = __ROR16((uint16_t)v16, 1, NBITS16_16B);
      *v13 = v15;
      v13[1] = v16;
      v12 += 2;
      v13 += 2;
      --v14;
    }
    while ( v14 );
    v6 = (uint32_t *)&src[(line + (uintptr_t)v12 - (uintptr_t)src) & 0xFFF];
    v7 = (uint32_t *)((char *)v13 + ext);
    v8 = v18 - 1;
  }
  while ( v18 != 1 );
}

static INLINE void load16bIA(uint8_t *src, uint8_t *dst, int wid_64, int height, int line, int ext)
{
   uint32_t *v11, *v12, v14;
   int32_t v9, v15, v16;

   uint32_t *v6 = (uint32_t *)src;
   uint32_t *v7 = (uint32_t *)dst;
   int32_t   v8 = height;

   do
   {
      v15 = v8;
      v9 = wid_64;
      do
      {
         *v7++ = *v6++;
         *v7++ = *v6++;
      }while (--v9 );
      if ( v15 == 1 )
         break;
      v16 = v15 - 1;
      v11 = (uint32_t *)((int8_t *)v6 + line);
      v12 = (uint32_t *)((int8_t *)v7 + ext);
      v9 = wid_64;
      do
      {
         v14 = *v11;
         *v12++ = v11[1];
         *v12++ = v14;
         v11 += 2;
      }while (--v9 );
      v6 = (uint32_t *)((int8_t *)v11 + line);
      v7 = (uint32_t *)((int8_t *)v12 + ext);
      v8 = v16 - 1;
   }while ( v16 != 1 );
}

//****************************************************************
// Size: 2, Format: 0
//

uint32_t Load16bRGBA (uintptr_t dst, uintptr_t src, int wid_64, int height, int line, int real_width, int tile)
{
   int ext;
  if (wid_64 < 1)
     wid_64 = 1;
  if (height < 1)
     height = 1;
  ext = (real_width - (wid_64 << 2)) << 1;

  load16bRGBA((uint8_t *)src, (uint8_t *)dst, wid_64, height, line, ext);

  return (1 << 16) | GR_TEXFMT_ARGB_1555;
}

//****************************************************************
// Size: 2, Format: 3
//
// ** by Gugaman/Dave2001 **

uint32_t Load16bIA (uintptr_t dst, uintptr_t src, int wid_64, int height, int line, int real_width, int tile)
{
   int ext;
   if (wid_64 < 1)
      wid_64 = 1;
   if (height < 1)
      height = 1;
   ext = (real_width - (wid_64 << 2)) << 1;

   load16bIA((uint8_t *)src, (uint8_t *)dst, wid_64, height, line, ext);

   return (1 << 16) | GR_TEXFMT_ALPHA_INTENSITY_88;
}

//****************************************************************
// Size: 2, Format: 1
//

uint16_t yuv_to_rgb565(uint8_t y, uint8_t u, uint8_t v)
{
   float r = y + (1.370705f * (v-128));
   float g = y - (0.698001f * (v-128)) - (0.337633f * (u-128));
   float b = y + (1.732446f * (u-128));

   r *= 0.125f;
   g *= 0.25f;
   b *= 0.125f;
   //clipping the result
   if (r > 31) r = 31;
   if (g > 63) g = 63;
   if (b > 31) b = 31;
   if (r < 0) r = 0;
   if (g < 0) g = 0;
   if (b < 0) b = 0;
   return (uint16_t)(((uint16_t)(r) << 11) |
         ((uint16_t)(g) << 5) |
         (uint16_t)(b) );
   //*/
   /*
      const uint32_t c = y - 16;
      const uint32_t d = u - 128;
      const uint32_t e = v - 128;

      uint32_t r =  (298 * c           + 409 * e + 128) & 0xf800;
      uint32_t g = ((298 * c - 100 * d - 208 * e + 128) >> 5) & 0x7e0;
      uint32_t b = ((298 * c + 516 * d           + 128) >> 11) & 0x1f;

      WORD texel = (WORD)(r | g | b);

      return texel;
      */
}

//****************************************************************
// Size: 2, Format: 1
//

uint32_t Load16bYUV (uintptr_t dst, uintptr_t src,
      int wid_64, int height, int line, int real_width, int tile)
{
   uint16_t i;
   uint32_t *mb = (uint32_t*)(gfx_info.RDRAM+rdp.addr[g_gdp.tile[tile].tmem]); //pointer to the macro block
   uint16_t *tex = (uint16_t*)dst;

   for (i = 0; i < 128; i++)
   {
      uint32_t  t = mb[i]; //each uint32_t contains 2 pixels
      uint8_t  y1 = (uint8_t)t&0xFF;
      uint8_t  v  = (uint8_t)(t>>8)&0xFF;
      uint8_t  y0 = (uint8_t)(t>>16)&0xFF;
      uint8_t  u  = (uint8_t)(t>>24)&0xFF;
      uint16_t c = yuv_to_rgb565(y0, u, v);

      *(tex++) = c;
      c = yuv_to_rgb565(y1, u, v);
      *(tex++) = c;
   }
   return (1 << 16) | GR_TEXFMT_RGB_565;
}
