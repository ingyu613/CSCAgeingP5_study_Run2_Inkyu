#!/bin/bash
#SBATCH --job-name=csc_pdr_all
#SBATCH --account=avery
#SBATCH --qos=avery
#SBATCH --time=02:00:00
#SBATCH --mem=16G
#SBATCH --cpus-per-task=1
#SBATCH --array=0-31
#SBATCH --output=slurm_pdr_all_%A_%a.log

CHAMBERS=(
  "ME11a" "ME11b"
  "ME12HV1" "ME12HV2" "ME12HV3"
  "ME13HV1" "ME13HV2" "ME13HV3"
  "ME21HV1" "ME21HV2" "ME21HV3"
  "ME22HV1" "ME22HV2" "ME22HV3" "ME22HV4" "ME22HV5"
  "ME31HV1" "ME31HV2" "ME31HV3"
  "ME32HV1" "ME32HV2" "ME32HV3" "ME32HV4" "ME32HV5"
  "ME41HV1" "ME41HV2" "ME41HV3"
  "ME42HV1" "ME42HV2" "ME42HV3" "ME42HV4" "ME42HV5"
)

CHAMBER=${CHAMBERS[$SLURM_ARRAY_TASK_ID]}
echo "=========================================================="
echo ">>> SLURM Array Task ID: $SLURM_ARRAY_TASK_ID"
echo ">>> Target Chamber:      $CHAMBER"
echo ">>> Host Node:           $HOSTNAME"
echo ">>> Start Time:          $(date)"
echo "=========================================================="

/cvmfs/cms.cern.ch/common/cmssw-el8 -- bash << CONTAINER_EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /blue/avery/inkyuhwang/CMSSW_16_1_3/src
eval "\$(scramv1 runtime -sh)"
cd /blue/avery/inkyuhwang/CSCAgeing_Analysis_Pipeline/Src

# Reuse pre-compiled shared library without recompilation
root -l -b -q 'run_chamber.C+("'"$CHAMBER"'")'
CONTAINER_EOF

echo ">>> Task $SLURM_ARRAY_TASK_ID ($CHAMBER) finished at: $(date)"
