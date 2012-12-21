#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H

/*
 * signed multiply of two 32-bit integers (x and y),
 * returns top 32-bits of 64-bit result
 */
static __inline int MULSHIFT32(int x, int y)
{
	return (int) ((((long long) x) * y ) >> 32);
	//    int zlow;
	//    __asm__ volatile ("smull %0,%1,%2,%3" : "=&r" (zlow), "=r" (y) : "r" (x), "1" (y) : "cc");
    // return y;
}

static __inline short CLIPTOSHORT(int x)
{
	int sign;

	/* clip to [-32768, 32767] */
	sign = x >> 31;
	if (sign != (x >> 15))
		x = sign ^ ((1 << 15) - 1);

	return (short)x;
}

static __inline int FASTABS(int x)
{
	int sign;

	sign = x >> (sizeof(int) * 8 - 1);
	x ^= sign;
	x -= sign;

	return x;
}

static __inline int CLZ(int x)
{
	int numZeros;

	if (!x)
		return (sizeof(int) * 8);

	numZeros = 0;
	while (!(x & 0x80000000)) {
		numZeros++;
		x <<= 1;
	}

	//__asm__ ("clz %0, %1" : "=r" (numZeros) : "r" (x) : "cc");

	return numZeros;
}

typedef long long Word64;

typedef union _U64 {
	Word64 w64;
	struct {
		/* ARM ADS = little endian */
		unsigned int lo32;
		signed int   hi32;
	} r;
} U64;

static __inline Word64 MADD64(Word64 sum64, int x, int y)
{
	return (sum64 + ((long long)x * y));
//	U64 u;
//	u.w64 = sum64;
//
//	__asm__ volatile ("smlal %0,%1,%2,%3" : "+&r" (u.r.lo32), "+&r" (u.r.hi32) : "r" (x), "r" (y) : "cc");
//
//	return u.w64;
}
static __inline Word64 SAR64(Word64 x, int n)
{
	return  x >> n;

}


#endif /* _ASSEMBLY_H */
