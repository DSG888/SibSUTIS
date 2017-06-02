#!/usr/bin/env bash

i=0

echo "" > "myTask"$i".job"
echo " #PBS -N qsortp"$i >> "myTask"$i".job"
echo " #PBS -l nodes=1:ppn=8" >> "myTask"$i".job"
echo " #PBS -j oe   " >> "myTask"$i".job"
echo " #PBS -q release  " >> "myTask"$i".job"
echo "" >> "myTask"$i".job"
echo "cd \$PBS_O_WORKDIR " >> "myTask"$i".job"
echo "" >> "myTask"$i".job"


#NBodys

for TH in 1 2 3 4 5 6 7 8
do
	#i=$(($i+1))

	echo "export OMP_NUM_THREADS="$TH >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
	echo "echo ===Потоков: \$OMP_NUM_THREADS >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"
	
	echo "" >> "myTask"$i".job"

	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"



	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"



	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"




	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"


	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"


	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"



	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"




	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"



	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ====== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"



	echo "./qsort 100000000 1 >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"


	echo "echo ==+ >> REZ"$i".o0" >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
#	sleep 1
	
	
done
qsub "myTask"$i".job"
