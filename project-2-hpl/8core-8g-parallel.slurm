#!/bin/bash

#SBATCH -J test               # Job name
#SBATCH -o job.%j.out         # Name of stdout output file (%j expands to jobId)
#SBATCH -N 2                  # Total number of nodes requested
#SBATCH -n 16                 # Total number of mpi tasks requested
#SBATCH -p 8core
#SBATCH -t 01:00:00           # Run time (hh:mm:ss) - 1 minute

echo "Running xhpl with: $cmd on $SLURM_JOB_NODELIST in directory "`pwd`

# Launch MPI-based executable

export LINPACK_EXE='/opt/ohpc/pub/compiler/intel-18/mkl/benchmarks/mp_linpack/xhpl_intel64_dynamic'

module purge
module load intel/Developer-2018.1

mpiexec $LINPACK_EXE

