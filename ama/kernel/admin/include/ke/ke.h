
// ke.h

#ifndef __KE_H
#define __KE_H    1

unsigned long keGetSystemMetrics(int index);
void keDie(void);
void keSoftDie(void);
int keIsQemu(void);

int keCloseInitProcess(void);
void keReboot(void);
void ke_x64ExecuteInitialProcess(void);
int keInitialize(int phase);

#endif  


