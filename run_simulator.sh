

#!/bin/bash
#PBS -S /bin/bash
#PBS -N space
#PBS -l walltime=01:59:00
#PBS -l select=1:ncpus=32:mem=200mb:scratch_local=10mb

DATADIR="$PBS_O_WORKDIR"
cp $DATADIR/*.cpp $SCRATCHDIR
cp $DATADIR/*.h $SCRATCHDIR
cp $DATADIR/data/* $SCRATCHDIR
cd $SCRATCHDIR || exit 1

source /software/modules/init
module load intelcdk-17.1

#echo -e "CPU INFO\n"
#cat /proc/cpuinfo

echo -e "\nCOMPILATION\n"

icpc -fopenmp -fopt-info-vec -std=c++11 -march=native -Ofast -std=c++11 -qopt-report=1 -qopt-report-file:stdout -qopt-report-phase=vec -o space main.cpp MassPoint.cpp MassPoint.h SpaceSimulator.cpp SpaceSimulator.h GifBuilder.cpp GifBuilder.h gif.cpp gif.h settings.h
echo "Version of GLIBC"
ldd --version

echo -e "\nBenchmark started..."


for thread in 1 2 4 8 16 32 
do
    for instance in 200 400 800 1600 3200
    do
        export OMP_NUM_THREADS="$thread"
        export INSTANCE="$instance"
        echo $OMP_NUM_THREADS
        ./space $DATADIR/data/in_$INSTANCE.txt $DATADIR/data/out_$INSTANCE_$OMP_NUM_THREADS.gif 200
        echo "-----------------------------------------------------------"
    done
done

cp $SCRATCHDIR/out.gif $DATADIR

echo "Benchmark finished..."

