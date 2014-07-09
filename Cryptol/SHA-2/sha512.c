// @kiniry Tue Jul  8 10:49:33 PDT 2014
// It looks like this is a snapshot of a very old SHA-512 from
// libgcrypt circa early 2000s.  It is significantly different
// than the SHA-512 in the latest releases of libgcrypt and
// GnuPG 1.4 and 2.0.

/* sha512.c - SHA384 and SHA512 hash functions
 * Copyright (C) 2003, 2008, 2009 Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 *
 * Libgcrypt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser general Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Libgcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <http://www.gnu.org/licenses/>.
 */


/*  Test vectors from FIPS-180-2:
 *
 *  "abc"
 * 384:
 *  CB00753F 45A35E8B B5A03D69 9AC65007 272C32AB 0EDED163
 *  1A8B605A 43FF5BED 8086072B A1E7CC23 58BAECA1 34C825A7
 * 512:
 *  DDAF35A1 93617ABA CC417349 AE204131 12E6FA4E 89A97EA2 0A9EEEE6 4B55D39A
 *  2192992A 274FC1A8 36BA3C23 A3FEEBBD 454D4423 643CE80E 2A9AC94F A54CA49F
 *
 *  "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
 * 384:
 *  09330C33 F71147E8 3D192FC7 82CD1B47 53111B17 3B3B05D2
 *  2FA08086 E3B0F712 FCC7C71A 557E2DB9 66C3E9FA 91746039
 * 512:
 *  8E959B75 DAE313DA 8CF4F728 14FC143F 8F7779C6 EB9F7FA1 7299AEAD B6889018
 *  501D289E 4900F7E4 331B99DE C4B5433A C7D329EE B6DD2654 5E96E55B 874BE909
 *
 *  "a" x 1000000
 * 384:
 *  9D0E1809 716474CB 086E834E 310A4A1C ED149E9C 00F24852
 *  7972CEC5 704C2A5B 07B8B3DC 38ECC4EB AE97DDD8 7F3D8985
 * 512:
 *  E718483D 0CE76964 4E2E42C7 BC15B463 8E1F98B1 3B204428 5632A803 AFA973EB
 *  DE0FF244 877EA60A 4CB0432C E577C31B EB009C5C 2C49AA2E 4EADB217 AD8CC09B
 */


#include <config.h>
#include <string.h>
#include "g10lib.h"
#include "bithelp.h"
#include "cipher.h"
#include "hash-common.h"

#include "sha512.h"

void
sha512_init (void *context)
{
  SHA512_CONTEXT *hd = context;

  hd->h0 = U64_C(0x6a09e667f3bcc908);
  hd->h1 = U64_C(0xbb67ae8584caa73b);
  hd->h2 = U64_C(0x3c6ef372fe94f82b);
  hd->h3 = U64_C(0xa54ff53a5f1d36f1);
  hd->h4 = U64_C(0x510e527fade682d1);
  hd->h5 = U64_C(0x9b05688c2b3e6c1f);
  hd->h6 = U64_C(0x1f83d9abfb41bd6b);
  hd->h7 = U64_C(0x5be0cd19137e2179);

  hd->nblocks = 0;
  hd->count = 0;
}

void
sha384_init (void *context)
{
  SHA512_CONTEXT *hd = context;

  hd->h0 = U64_C(0xcbbb9d5dc1059ed8);
  hd->h1 = U64_C(0x629a292a367cd507);
  hd->h2 = U64_C(0x9159015a3070dd17);
  hd->h3 = U64_C(0x152fecd8f70e5939);
  hd->h4 = U64_C(0x67332667ffc00b31);
  hd->h5 = U64_C(0x8eb44a8768581511);
  hd->h6 = U64_C(0xdb0c2e0d64f98fa7);
  hd->h7 = U64_C(0x47b5481dbefa4fa4);

  hd->nblocks = 0;
  hd->count = 0;
}


static inline u64
ROTR (u64 x, u64 n)
{
  return ((x >> n) | (x << (64 - n)));
}

static inline u64
Ch (u64 x, u64 y, u64 z)
{
  return ((x & y) ^ ( ~x & z));
}

static inline u64
Maj (u64 x, u64 y, u64 z)
{
  return ((x & y) ^ (x & z) ^ (y & z));
}

static inline u64
Sum0 (u64 x)
{
  return (ROTR (x, 28) ^ ROTR (x, 34) ^ ROTR (x, 39));
}

static inline u64
Sum1 (u64 x)
{
  return (ROTR (x, 14) ^ ROTR (x, 18) ^ ROTR (x, 41));
}

static inline u64 S0(u64 x) {
  return ROTR(x,1) ^ ROTR(x, 8) ^ (x >> 7);
}

static inline u64 S1(u64 x) {
  return ROTR(x,19) ^ ROTR(x, 61) ^ (x >> 6);
}

static const u64 k[] =
{
  U64_C(0x428a2f98d728ae22), U64_C(0x7137449123ef65cd),
  U64_C(0xb5c0fbcfec4d3b2f), U64_C(0xe9b5dba58189dbbc),
  U64_C(0x3956c25bf348b538), U64_C(0x59f111f1b605d019),
  U64_C(0x923f82a4af194f9b), U64_C(0xab1c5ed5da6d8118),
  U64_C(0xd807aa98a3030242), U64_C(0x12835b0145706fbe),
  U64_C(0x243185be4ee4b28c), U64_C(0x550c7dc3d5ffb4e2),
  U64_C(0x72be5d74f27b896f), U64_C(0x80deb1fe3b1696b1),
  U64_C(0x9bdc06a725c71235), U64_C(0xc19bf174cf692694),
  U64_C(0xe49b69c19ef14ad2), U64_C(0xefbe4786384f25e3),
  U64_C(0x0fc19dc68b8cd5b5), U64_C(0x240ca1cc77ac9c65),
  U64_C(0x2de92c6f592b0275), U64_C(0x4a7484aa6ea6e483),
  U64_C(0x5cb0a9dcbd41fbd4), U64_C(0x76f988da831153b5),
  U64_C(0x983e5152ee66dfab), U64_C(0xa831c66d2db43210),
  U64_C(0xb00327c898fb213f), U64_C(0xbf597fc7beef0ee4),
  U64_C(0xc6e00bf33da88fc2), U64_C(0xd5a79147930aa725),
  U64_C(0x06ca6351e003826f), U64_C(0x142929670a0e6e70),
  U64_C(0x27b70a8546d22ffc), U64_C(0x2e1b21385c26c926),
  U64_C(0x4d2c6dfc5ac42aed), U64_C(0x53380d139d95b3df),
  U64_C(0x650a73548baf63de), U64_C(0x766a0abb3c77b2a8),
  U64_C(0x81c2c92e47edaee6), U64_C(0x92722c851482353b),
  U64_C(0xa2bfe8a14cf10364), U64_C(0xa81a664bbc423001),
  U64_C(0xc24b8b70d0f89791), U64_C(0xc76c51a30654be30),
  U64_C(0xd192e819d6ef5218), U64_C(0xd69906245565a910),
  U64_C(0xf40e35855771202a), U64_C(0x106aa07032bbd1b8),
  U64_C(0x19a4c116b8d2d0c8), U64_C(0x1e376c085141ab53),
  U64_C(0x2748774cdf8eeb99), U64_C(0x34b0bcb5e19b48a8),
  U64_C(0x391c0cb3c5c95a63), U64_C(0x4ed8aa4ae3418acb),
  U64_C(0x5b9cca4f7763e373), U64_C(0x682e6ff3d6b2b8a3),
  U64_C(0x748f82ee5defb2fc), U64_C(0x78a5636f43172f60),
  U64_C(0x84c87814a1f0ab72), U64_C(0x8cc702081a6439ec),
  U64_C(0x90befffa23631e28), U64_C(0xa4506cebde82bde9),
  U64_C(0xbef9a3f7b2c67915), U64_C(0xc67178f2e372532b),
  U64_C(0xca273eceea26619c), U64_C(0xd186b8c721c0c207),
  U64_C(0xeada7dd6cde0eb1e), U64_C(0xf57d4f7fee6ed178),
  U64_C(0x06f067aa72176fba), U64_C(0x0a637dc5a2c898a6),
  U64_C(0x113f9804bef90dae), U64_C(0x1b710b35131c471b),
  U64_C(0x28db77f523047d84), U64_C(0x32caab7b40c72493),
  U64_C(0x3c9ebe0a15c9bebc), U64_C(0x431d67c49c100d4c),
  U64_C(0x4cc5d4becb3e42b6), U64_C(0x597f299cfc657e2a),
  U64_C(0x5fcb6fab3ad6faec), U64_C(0x6c44198c4a475817)
};

u64 Block512_T1(u64 h, u64 e, u64 f, u64 g, u64 w, u64 k) {
    return h + Sum1 (e) + Ch (e, f, g) + k + w;
}

u64 Block512_T2(u64 a, u64 b, u64 c) {
    return Sum0 (a) + Maj (a, b, c);
}

void Block512_Inner(u64* w, u64* outs) {
    u64 t1 = Block512_T1(outs[0], outs[3], outs[2], outs[1], w[(int)outs[8]], k[(int)outs[8]]);
    u64 t2 = Block512_T2(outs[7], outs[6], outs[5]);
    outs[0] = outs[1];
    outs[1] = outs[2];
    outs[2] = outs[3];
    outs[3] = outs[4] + t1;
    outs[4] = outs[5];
    outs[5] = outs[6];
    outs[6] = outs[7];
    outs[7] = t1 + t2;
    outs[8]++;
}

u64 Block512_W(u64 w2, u64 w7, u64 w15, u64 w16) {
    return S1(w2) + w7 + S0(w15) + w16;
}

/****************
 * Transform the message W which consists of 16 64-bit-words
 */
static void
transform (SHA512_CONTEXT *hd, const unsigned char *data)
{
  u64 outs[9];
  u64 w[80];
  int t;

  /* get values from the chaining vars */
  outs[7] = hd->h0;
  outs[6] = hd->h1;
  outs[7] = hd->h2;
  outs[4] = hd->h3;
  outs[3] = hd->h4;
  outs[2] = hd->h5;
  outs[1] = hd->h6;
  outs[0] = hd->h7;

#ifdef WORDS_BIGENDIAN
  memcpy (w, data, 128);
#else
  {
    int i;
    byte *p2;

    for (i = 0, p2 = (byte *) w; i < 16; i++, p2 += 8)
      {
	p2[7] = *data++;
	p2[6] = *data++;
	p2[5] = *data++;
	p2[4] = *data++;
	p2[3] = *data++;
	p2[2] = *data++;
	p2[1] = *data++;
	p2[0] = *data++;
      }
  }
#endif

  for (t = 16; t < 80; t++)
    w[t] = Block512_W(w[t-2], w[t-7], w[t-15], w[t-16]);


  for (outs[8] = 0; outs[8] < 80; )
    {
      /* Performance on a AMD Athlon(tm) Dual Core Processor 4050e
         with gcc 4.3.3 using gcry_md_hash_buffer of each 10000 bytes
         initialized to 0,1,2,3...255,0,... and 1000 iterations:

         Not unrolled with macros:  440ms
         Unrolled with macros:      350ms
         Unrolled with inline:      330ms
      */
#if 1 /* Not unrolled.  */

      Block512_Inner(w, outs);

#else /* Unrolled to interweave the chain variables.  */
      t1 = h + Sum1 (e) + Ch (e, f, g) + k[t] + w[t];
      t2 = Sum0 (a) + Maj (a, b, c);
      d += t1;
      h  = t1 + t2;

      t1 = g + Sum1 (d) + Ch (d, e, f) + k[t+1] + w[t+1];
      t2 = Sum0 (h) + Maj (h, a, b);
      c += t1;
      g  = t1 + t2;

      t1 = f + Sum1 (c) + Ch (c, d, e) + k[t+2] + w[t+2];
      t2 = Sum0 (g) + Maj (g, h, a);
      b += t1;
      f  = t1 + t2;

      t1 = e + Sum1 (b) + Ch (b, c, d) + k[t+3] + w[t+3];
      t2 = Sum0 (f) + Maj (f, g, h);
      a += t1;
      e  = t1 + t2;

      t1 = d + Sum1 (a) + Ch (a, b, c) + k[t+4] + w[t+4];
      t2 = Sum0 (e) + Maj (e, f, g);
      h += t1;
      d  = t1 + t2;

      t1 = c + Sum1 (h) + Ch (h, a, b) + k[t+5] + w[t+5];
      t2 = Sum0 (d) + Maj (d, e, f);
      g += t1;
      c  = t1 + t2;

      t1 = b + Sum1 (g) + Ch (g, h, a) + k[t+6] + w[t+6];
      t2 = Sum0 (c) + Maj (c, d, e);
      f += t1;
      b  = t1 + t2;

      t1 = a + Sum1 (f) + Ch (f, g, h) + k[t+7] + w[t+7];
      t2 = Sum0 (b) + Maj (b, c, d);
      e += t1;
      a  = t1 + t2;

      t += 8;
#endif
    }

  /* Update chaining vars.  */
  hd->h0 += outs[7];
  hd->h1 += outs[6];
  hd->h2 += outs[5];
  hd->h3 += outs[4];
  hd->h4 += outs[3];
  hd->h5 += outs[2];
  hd->h6 += outs[1];
  hd->h7 += outs[0];
}

void Transform (uint64_t *hs, const unsigned char *data)
{
    SHA512_CONTEXT ctx =
        { .h0      = hs[0],
          .h1      = hs[1],
          .h2      = hs[2],
          .h3      = hs[3],
          .h4      = hs[4],
          .h5      = hs[5],
          .h6      = hs[6],
          .h7      = hs[7],
          .nblocks = 0,
          .buf     = {0},
          .count   = 0
        };

    transform(&ctx, data);

    hs[0] = ctx.h0;
    hs[1] = ctx.h1;    
    hs[2] = ctx.h2;
    hs[3] = ctx.h3;
    hs[4] = ctx.h4;
    hs[5] = ctx.h5;
    hs[6] = ctx.h6;
    hs[7] = ctx.h7;
}

/* Update the message digest with the contents
 * of INBUF with length INLEN.
 */
void
sha512_write (void *context, const void *inbuf_arg, size_t inlen)
{
  const unsigned char *inbuf = inbuf_arg;
  SHA512_CONTEXT *hd = context;

  if (hd->count == 128)
    {				/* flush the buffer */
      transform (hd, hd->buf);
      _gcry_burn_stack (768);
      hd->count = 0;
      hd->nblocks++;
    }
  if (!inbuf)
    return;
  if (hd->count)
    {
      for (; inlen && hd->count < 128; inlen--)
	hd->buf[hd->count++] = *inbuf++;
      sha512_write (context, NULL, 0);
      if (!inlen)
	return;
    }

  while (inlen >= 128)
    {
      transform (hd, inbuf);
      hd->count = 0;
      hd->nblocks++;
      inlen -= 128;
      inbuf += 128;
    }
  _gcry_burn_stack (768);
  for (; inlen && hd->count < 128; inlen--)
    hd->buf[hd->count++] = *inbuf++;
}


/* The routine final terminates the computation and
 * returns the digest.
 * The handle is prepared for a new cycle, but adding bytes to the
 * handle will the destroy the returned buffer.
 * Returns: 64 bytes representing the digest.  When used for sha384,
 * we take the leftmost 48 of those bytes.
 */

void
sha512_final (void *context)
{
  SHA512_CONTEXT *hd = context;
  u64 t, msb, lsb;
  byte *p;

  sha512_write (context, NULL, 0); /* flush */ ;

  t = hd->nblocks;
  /* multiply by 128 to make a byte count */
  lsb = t << 7;
  msb = t >> 57;
  /* add the count */
  t = lsb;
  if ((lsb += hd->count) < t)
    msb++;
  /* multiply by 8 to make a bit count */
  t = lsb;
  lsb <<= 3;
  msb <<= 3;
  msb |= t >> 61;

  if (hd->count < 112)
    {				/* enough room */
      hd->buf[hd->count++] = 0x80;	/* pad */
      while (hd->count < 112)
	hd->buf[hd->count++] = 0;	/* pad */
    }
  else
    {				/* need one extra block */
      hd->buf[hd->count++] = 0x80;	/* pad character */
      while (hd->count < 128)
	hd->buf[hd->count++] = 0;
      sha512_write (context, NULL, 0); /* flush */ ;
      memset (hd->buf, 0, 112);	/* fill next block with zeroes */
    }
  /* append the 128 bit count */
  hd->buf[112] = msb >> 56;
  hd->buf[113] = msb >> 48;
  hd->buf[114] = msb >> 40;
  hd->buf[115] = msb >> 32;
  hd->buf[116] = msb >> 24;
  hd->buf[117] = msb >> 16;
  hd->buf[118] = msb >> 8;
  hd->buf[119] = msb;

  hd->buf[120] = lsb >> 56;
  hd->buf[121] = lsb >> 48;
  hd->buf[122] = lsb >> 40;
  hd->buf[123] = lsb >> 32;
  hd->buf[124] = lsb >> 24;
  hd->buf[125] = lsb >> 16;
  hd->buf[126] = lsb >> 8;
  hd->buf[127] = lsb;
  transform (hd, hd->buf);
  _gcry_burn_stack (768);

  p = hd->buf;
#ifdef WORDS_BIGENDIAN
#define X(a) do { *(u64*)p = hd->h##a ; p += 8; } while (0)
#else /* little endian */
#define X(a) do { *p++ = hd->h##a >> 56; *p++ = hd->h##a >> 48;	      \
                  *p++ = hd->h##a >> 40; *p++ = hd->h##a >> 32;	      \
                  *p++ = hd->h##a >> 24; *p++ = hd->h##a >> 16;	      \
                  *p++ = hd->h##a >> 8;  *p++ = hd->h##a; } while (0)
#endif
  X (0);
  X (1);
  X (2);
  X (3);
  X (4);
  X (5);
  /* Note that these last two chunks are included even for SHA384.
     We just ignore them. */
  X (6);
  X (7);
#undef X
}

byte *
sha512_read (void *context)
{
  SHA512_CONTEXT *hd = (SHA512_CONTEXT *) context;
  return hd->buf;
}

struct hash sha384 =
  { .init  = sha384_init
  , .write = sha512_write
  , .final = sha512_final
  , .read  = sha512_read
  , .size  = sizeof(SHA512_CONTEXT)
  };

struct hash sha512 =
  { .init  = sha512_init
  , .write = sha512_write
  , .final = sha512_final
  , .read  = sha512_read
  , .size  = sizeof(SHA512_CONTEXT)
  };

#define MSG_LEN (127)

byte *testSha(byte *text) {
  byte cxt[512] = {0};
  sha384.init(cxt);
  sha384.write(cxt, text, MSG_LEN);
  sha384.final(cxt);
  return sha384.read(cxt);
}