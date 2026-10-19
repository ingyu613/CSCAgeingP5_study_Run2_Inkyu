#!/bin/bash
#SBATCH --job-name=csc_stage2
#SBATCH --output=logs/slurm-%A_%a.out
#SBATCH --error=logs/slurm-%A_%a.err
#SBATCH --time=00:30:00
#SBATCH --mem=2000MB
#SBATCH --qos=avery
#SBATCH --account=avery
#SBATCH --cpus-per-task=1

echo "Host: $(hostname)"
echo "FILELIST: $FILELIST"
echo "SLURM_ARRAY_TASK_ID: $SLURM_ARRAY_TASK_ID"

# Fetch line corresponding to SLURM_ARRAY_TASK_ID (1-indexed)
line=$(sed -n "$((SLURM_ARRAY_TASK_ID + 1))p" "$FILELIST")
input_file=$(echo "$line" | cut -d' ' -f1)
output_file=$(echo "$line" | cut -d' ' -f2)
year=$(echo "$line" | cut -d' ' -f3)
dataset=$(echo "$line" | cut -d' ' -f4)

echo "Input:   $input_file"
echo "Output:  $output_file"
echo "Year:    $year"
echo "Dataset: $dataset"

./single_file_run.sh "$input_file" "$output_file" "$year" "$dataset"
