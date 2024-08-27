#ifndef BIT_MASTH_H
#define BIT_MASTH_H

#define SET_BIT(REG , BIT_REG)   (REG|=(1<<BIT_REG))
#define CLR_BIT(REG , BIT_REG)   (REG&=!(1<<BIT_REG))
#define TOG_BIT(REG , BIT_REG)   (REG^=(1<<BIT_REG))
#define GET_BIT(REG , BIT_REG)   ((REG<<BIT_REG)&1)

#endif