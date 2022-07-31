#ifndef ACTION_DEF_H
#define ACTION_DEF_H

#define ACTION_DELAY 10
#define ACTION_QUEUE_LENGTH 512

enum ACTIONS
{
    EV_NONE,
    // Action events begin here; max 32
    // These translate to player controldata
    // Actions are used for netplay and demos
    EV_ACTION_UP,       //01
    EV_ACTION_DOWN,     //02
    EV_ACTION_LEFT,     //03
    EV_ACTION_RIGHT,    //04
    EV_ACTION_FIRE,     //05
    EV_ACTION_USE,      //06
    EV_ACTION_07,       //07
    EV_ACTION_08,       //08
    EV_ACTION_09,       //09
    EV_ACTION_10,       //10
    EV_ACTION_11,       //11
    EV_ACTION_12,       //12
    EV_ACTION_13,       //13
    EV_ACTION_14,       //14
    EV_ACTION_15,       //15
    EV_ACTION_16,       //16
    EV_ACTION_17,       //17
    EV_ACTION_18,       //18
    EV_ACTION_19,       //19
    EV_ACTION_20,       //20
    EV_ACTION_21,       //21
    EV_ACTION_22,       //22
    EV_ACTION_23,       //23
    EV_ACTION_24,       //24
    EV_ACTION_25,       //25
    EV_ACTION_26,       //26
    EV_ACTION_27,       //27
    EV_ACTION_28,       //28
    EV_ACTION_29,       //29
    EV_ACTION_30,       //30
    EV_ACTION_31,       //31
    EV_ACTION_32,       //32
    NUM_ACTIONS = 32
};

#define ACTION_UP      BIT(EV_ACTION_UP-1)
#define ACTION_DOWN    BIT(EV_ACTION_DOWN-1)
#define ACTION_LEFT    BIT(EV_ACTION_LEFT-1)
#define ACTION_RIGHT   BIT(EV_ACTION_RIGHT-1)
#define ACTION_FIRE    BIT(EV_ACTION_FIRE-1)
#define ACTION_USE     BIT(EV_ACTION_USE-1)
#define ACTION_07      BIT(EV_ACTION_07-1)
#define ACTION_08      BIT(EV_ACTION_08-1)
#define ACTION_09      BIT(EV_ACTION_09-1)
#define ACTION_10      BIT(EV_ACTION_10-1)
#define ACTION_11      BIT(EV_ACTION_11-1)
#define ACTION_12      BIT(EV_ACTION_12-1)
#define ACTION_13      BIT(EV_ACTION_13-1)
#define ACTION_14      BIT(EV_ACTION_14-1)
#define ACTION_15      BIT(EV_ACTION_15-1)
#define ACTION_16      BIT(EV_ACTION_16-1)
#define ACTION_17      BIT(EV_ACTION_17-1)
#define ACTION_18      BIT(EV_ACTION_18-1)
#define ACTION_19      BIT(EV_ACTION_19-1)
#define ACTION_20      BIT(EV_ACTION_20-1)
#define ACTION_21      BIT(EV_ACTION_21-1)
#define ACTION_22      BIT(EV_ACTION_22-1)
#define ACTION_23      BIT(EV_ACTION_23-1)
#define ACTION_24      BIT(EV_ACTION_24-1)
#define ACTION_25      BIT(EV_ACTION_25-1)
#define ACTION_26      BIT(EV_ACTION_26-1)
#define ACTION_27      BIT(EV_ACTION_27-1)
#define ACTION_28      BIT(EV_ACTION_28-1)
#define ACTION_29      BIT(EV_ACTION_29-1)
#define ACTION_30      BIT(EV_ACTION_30-1)
#define ACTION_31      BIT(EV_ACTION_31-1)
#define ACTION_32      BIT(EV_ACTION_32-1)

#endif/* ACTION_DEF_H */
