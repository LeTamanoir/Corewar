	.name "Tyron"
	.comment "Just a basic pompes, traction program"

#yo les rats

	sti r1, %:hi, %1
hi:	live %123
	ld %0, r3
	zjmp %:hi
