#!/usr/bin/env bash

i=0

echo "" > "myTask"$i".job"
echo " #PBS -N NBodyY"$i >> "myTask"$i".job"
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

	echo "echo ==V1== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "./NBodypv1 150 resV1-"$TH" >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ==V1-= >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"

	echo "echo ==V2== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "./NBodypv2 150 resV2-"$TH" >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ==V2-= >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"

	echo "echo ==V3== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "./NBodypv3 150 resV3-"$TH" >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ==V3-= >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"

	echo "echo ==V4== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "./NBodypv4 150 resV4-"$TH" >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ==V4-= >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "" >> "myTask"$i".job"

	echo "echo ==V5== >> REZ"$i".o0" >> "myTask"$i".job"
	echo "./NBodypv5 150 resV5-"$TH" >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo ==V5-= >> REZ"$i".o0" >> "myTask"$i".job"
	echo "echo   >> REZ"$i".o0" >> "myTask"$i".job"

	echo "echo ==+ >> REZ"$i".o0" >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
#	sleep 1
	
	
done
qsub "myTask"$i".job"
