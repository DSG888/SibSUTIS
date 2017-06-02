#!/usr/bin/env bash

echo "" > "myTask.job"
echo " #PBS -N NBody" >> "myTask.job"
echo " #PBS -l nodes=1:ppn=8" >> "myTask.job"
echo " #PBS -j oe   " >> "myTask.job"
echo " #PBS -q release  " >> "myTask.job"
echo "" >> "myTask.job"
echo "cd \$PBS_O_WORKDIR " >> "myTask.job"
echo "" >> "myTask.job"
i=0

#NBodys

for TH in 1 2 3 4 5 6 7 8
do
	i=$(($i+1))

	echo "export OMP_NUM_THREADS="$TH >> "myTask.job"
	echo "" >> "myTask.job"
	echo "echo ===Потоков: \$OMP_NUM_THREADS" >> "myTask.job"
	echo "echo  " >> "myTask.job"
	
	echo "" >> "myTask.job"

	echo "echo ==V1==" >> "myTask.job"
	echo "./NBodypv1 150 resV1-"$i >> "myTask.job"
	echo "echo ==V1-=" >> "myTask.job"
	echo "echo  " >> "myTask.job"

	echo "" >> "myTask.job"

	echo "echo ==V2==" >> "myTask.job"
	echo "./NBodypv2 150 resV2-"$i >> "myTask.job"
	echo "echo ==V2-=" >> "myTask.job"
	echo "echo  " >> "myTask.job"

	echo "" >> "myTask.job"

	echo "echo ==V3==" >> "myTask.job"
	echo "./NBodypv3 150 resV3-"$i >> "myTask.job"
	echo "echo ==V3-=" >> "myTask.job"
	echo "echo  " >> "myTask.job"

	echo "" >> "myTask.job"

	echo "echo ==V4==" >> "myTask.job"
	echo "./NBodypv4 150 resV4-"$i >> "myTask.job"
	echo "echo ==V4-=" >> "myTask.job"
	echo "echo  " >> "myTask.job"

	echo "" >> "myTask.job"

	echo "echo ==V5==" >> "myTask.job"
	echo "./NBodypv5 150 resV5-"$i >> "myTask.job"
	echo "echo ==V5-=" >> "myTask.job"
	echo "echo  " >> "myTask.job"

	echo "echo ==+" >> "myTask.job"
	echo "" >> "myTask.job"
#	sleep 1
	
	
done
qsub "myTask.job"
