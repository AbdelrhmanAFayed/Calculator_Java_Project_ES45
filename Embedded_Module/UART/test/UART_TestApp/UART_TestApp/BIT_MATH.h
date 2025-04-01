/*
 * BIT_MATH.h
 *
 * Created: 12/11/2024 2:05:50 PM
 *  Author: Mousa Mahmoud
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Var, BitNum)	((Var) |= (1U << (BitNum)))
#define CLR_BIT(Var, BitNum)	((Var) &= ~(1U << (BitNum)))
#define TGL_BIT(Var, BitNum)	((Var) ^= (1U << (BitNum)))
#define GET_BIT(Var, BitNum)	(((Var) >> (BitNum)) & 1U)

#define SET_BITS(Reg, Mask)		((Reg) |= (Mask))
#define CLR_BITS(Reg, Mask)		((Reg) &= ~(Mask))

#define WRITE_REG(Reg, Val)		((Reg) = (Val))
#define READ_REG(Reg)			((Reg))

#endif /* BIT_MATH_H_ */