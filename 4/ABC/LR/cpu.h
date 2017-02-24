#ifndef CPU_H
#define CPU_H

struct device {
	unsigned F1 : 1;
	unsigned F2 : 1;
	unsigned S : 1;
	unsigned Z : 1;
	unsigned AC : 1;
	unsigned P : 1;
	unsigned C : 1;
} Flags;

#endif
