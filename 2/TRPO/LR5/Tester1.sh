for A in abc -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10
do
	for B in abc -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10
	do
		for C in abc -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10
		do
			echo "На входе А=" $A "B=" $B "C=" $C >> RESULT.txt
			./bin/QuadraticEquation $A $B $C >> RESULT.txt
			echo "" >> RESULT.txt
		done
	done
done
