#!/bin/bash
#SBATCH --job-name=csc_pdr_me11a
#SBATCH --account=avery
#SBATCH --qos=avery
#SBATCH --time=02:00:00
#SBATCH --mem=16G
#SBATCH --cpus-per-task=1
#SBATCH --output=slurm_pdr_ME11a_%j.log

/cvmfs/cms.cern.ch/common/cmssw-el8 -- bash << 'CONTAINER_EOF'
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /blue/avery/inkyuhwang/CMSSW_16_1_3/src
eval "$(scramv1 runtime -sh)"
cd /blue/avery/inkyuhwang/CSCAgeing_Analysis_Pipeline/Src

rm -f run_chamber_C*
root -l -b -q 'run_chamber.C+("ME11a")'
CONTAINER_EOF
