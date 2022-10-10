#include "_common.h"
#include <i86.h>
#include <dos.h>

static int total_bytes = 0;

int dpmi_unlock_region(void *address, unsigned length)
{
	union REGS regs;
	unsigned int linear;

	linear = (unsigned int) address;

	total_bytes -= length;
	//mprintf( 1, "DPMI unlocked %d bytes\n", total_bytes );

	memset(&regs,0,sizeof(regs));
	regs.w.ax = 0x601;					// DPMI Unlock Linear Region
	regs.w.bx = (linear >> 16);		// Linear address in BX:CX
	regs.w.cx = (linear & 0xFFFF);

	regs.w.si = (length >> 16);		// Length in SI:DI
	regs.w.di = (length & 0xFFFF);
	int386 (0x31, &regs, &regs);

	return (! regs.w.cflag);			// Return 0 if can't lock
}

int dpmi_lock_region(void *address, unsigned length)
{
	union REGS regs;
	unsigned int linear;

	ASSERT(length != 0);

	linear = (unsigned int) address;

	total_bytes += length;
	//mprintf( 1, "DPMI Locked down %d bytes\n", total_bytes );

	memset(&regs,0,sizeof(regs));
	regs.w.ax = 0x600;					// DPMI Lock Linear Region
	regs.w.bx = (linear >> 16);		// Linear address in BX:CX
	regs.w.cx = (linear & 0xFFFF);

	regs.w.si = (length >> 16);		// Length in SI:DI
	regs.w.di = (length & 0xFFFF);
	int386 (0x31, &regs, &regs);
	
	return (! regs.w.cflag);			// Return 0 if can't lock
}