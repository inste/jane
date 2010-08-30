//      const.h
//      
//      Copyright 2010 Ilya <ilya@laptop>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#ifndef _CONST_H_
#define _CONST_H_


// Atom types

#define SYM_NUM			1	// Number (stored in char *)
#define SYM_BRK_OPEN 	10	// Open brackets
#define SYM_BRK_CLOSE 	20	// Close brackets
#define SYM_OPS_ADD		30 	// Low-priority
#define SYM_OPS_SUB		35
#define SYM_OPS_MUL		40  // Middle-priority
#define SYM_OPS_DIV		45
#define SYM_OPS_EXP		50  // Highest priority
#define SYM_FUNC		60  // Function
#define SYM_SYMBOL		70  // Variable or constant
#define	SYM_VOID		0	// Nothing :)

// Prio of operations

#define PRIO_HIGHER				100  // ^
#define PRIO_UPPER_MIDDLE		75	 // *, /
#define PRIO_MIDDLE				50  // +, -
#define	PRIO_UNDER_MIDDLE		25  // <, >, <=, >=
#define	PRIO_LOW				0  // !=, ==

// Multibyte operators shortcode

#define	SYM_MBOP_EQ		100 // Equal
#define	SYM_MBOP_NOTEQ	110 // Not equal
#define	SYM_MBOP_SSM	120 // Strictly smaller
#define	SYM_MBOP_SAE	130 // Smaller or equal
#define	SYM_MBOP_SBG	140 // Strictly bigger
#define	SYM_MBOP_BAE	150 // Equal or bigger

// Working types

#define		SYM_TYPE_RATIONAL		1
#define		SYM_TYPE_FUNC			100


// Memory 

#define		PAGE_SIZE				4096

#endif /* _CONST_H_ */
