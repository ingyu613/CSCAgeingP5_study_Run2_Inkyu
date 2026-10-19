#!/bin/bash
input_file=$1
output_file=$2
year=$3
dataset=$4

mkdir -p "logs/${year}/${year}${dataset}"
log_file="logs/${year}/${year}${dataset}/$(basename ${input_file}).log"
failed_filelist="logs/failed_filelist_${year}${dataset}.txt"

echo "=== System Info (uname -a) ===" > $log_file
uname -a >> $log_file
echo "" >> $log_file
echo "=== Running executable ===" >> $log_file

# Resolve path to the compiled Analysis_exe binary
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ANALYSIS_EXE="${SCRIPT_DIR}/../../Src/build/Analysis_exe"

if [ ! -f "$ANALYSIS_EXE" ]; then
    echo "ERROR: Executable $ANALYSIS_EXE not found!" >> $log_file
    echo "$input_file $output_file" >> $failed_filelist
    exit 1
fi

# Execute Stage 2 skimmer: <input_ntuple> <output_root> <year>
"$ANALYSIS_EXE" "$input_file" "$output_file" "$year" >> $log_file 2>&1
status=$?

if [ $status -ne 0 ]; then
    echo "ERROR: Analysis failed with exit code $status for $input_file" >> $log_file
    echo "$input_file $output_file" >> $failed_filelist
    exit 2
fi

echo "SUCCESS: Processed $input_file -> $output_file" >> $log_file
exit 0
