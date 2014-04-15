
		### Job name
		#PBS -N Encode12

		### out files
		#PBS -e ./log/Encode12.err
		#PBS -o ./log/Encode12.log

		### put the job to which queue (qwork)
		#PBS -q qwork
		

		# show the time and information
		echo Working directory is $PBS_O_WORKDIR
		cd $PBS_O_WORKDIR
		echo Running on host `hostname`
		echo Start time is `date`
		time1=`date +%s`
		echo Directory is `pwd`
		

		# run the script
		MCR_tmp="/tmp/mcr_$RANDOM"
		mkdir $MCR_tmp
		export MCR_CACHE_ROOT=$MCR_tmp
		python encode.py --version 6 --phase 1 --camera 12
		rm -rf $MCR_tmp                                                
		

		echo End time is `date`
		time2=`date +%s`
		echo Computing time is `echo $time2-$time1 | bc` sec
		
