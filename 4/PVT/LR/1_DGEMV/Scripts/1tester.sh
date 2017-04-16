#!/usr/bin/env bash

for TH in 1 2 3 4 5 6 7 8
do
	for SIZE in 5000 10000 15000 20000 25000 30000
	do
		sleep 6
		echo $TH $SIZE
		while [ "0" != `qstat |grep "DTONP"|grep "Q"|wc -l` ] || [ "0" != `qstat |grep "DTONP"|grep "R"|wc -l` ] || [ "0" != `qstat |grep "DTONP"|grep "E"|wc -l` ]; do
			echo "sleep"
			sleep 1
		done

		echo "" > myTask.job
		echo " #PBS -N DTONP" >> myTask.job
		echo " #PBS -l nodes=1:ppn=8" >> myTask.job
		echo " #PBS -j oe   " >> myTask.job
		echo " #PBS -q release  " >> myTask.job
		echo "" >> myTask.job
		echo "cd \$PBS_O_WORKDIR " >> myTask.job
		echo "" >> myTask.job
		echo "export OMP_NUM_THREADS="$TH >> myTask.job
		echo "" >> myTask.job
		echo "echo Потоков: \$OMP_NUM_THREADS" >> myTask.job
		echo "./DGEMV $SIZE $SIZE" >> myTask.job
		echo "" >> myTask.job

		sleep 1
		qsub myTask.job
		rm myTask.job

	done

done

