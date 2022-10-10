#ifndef _DPMI_H
#define _DPMI_H

int dpmi_unlock_region(void *address, unsigned length);
int dpmi_lock_region(void *address, unsigned length);

#endif/* _DPMI_H */
