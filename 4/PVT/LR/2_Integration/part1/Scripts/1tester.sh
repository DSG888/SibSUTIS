#!/usr/bin/env bash

i=0
for TH in 1 2 3 4 5 6 7 8
do
#	sleep 6
#	echo $TH
	i=$(($i+1))
	
#	while [ "0" != `qstat |grep "DTONP"|grep "Q"|wc -l` ] || [ "0" != `qstat |grep "DTONP"|grep "R"|wc -l` ] || [ "0" != `qstat |grep "DTONP"|grep "E"|wc -l` ]; do
#		echo "sleep"
#		sleep 1
#	done

	echo "" > "myTask"$i".job"
	echo " #PBS -N exp"$i >> "myTask"$i".job"
	echo " #PBS -l nodes=1:ppn=8" >> "myTask"$i".job"
	echo " #PBS -j oe   " >> "myTask"$i".job"
	echo " #PBS -q release  " >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
	echo "cd \$PBS_O_WORKDIR " >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
	echo "export OMP_NUM_THREADS="$TH >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
	echo "echo Потоков: \$OMP_NUM_THREADS" >> "myTask"$i".job"
	echo "./INTEGRv1" >> "myTask"$i".job"
	echo "echo ===" >> "myTask"$i".job"
	echo "./INTEGRv2" >> "myTask"$i".job"
	echo "echo ===" >> "myTask"$i".job"
	echo "./INTEGRv3" >> "myTask"$i".job"
	echo "" >> "myTask"$i".job"
	sleep 1
	
	qsub "myTask"$i".job"
done
