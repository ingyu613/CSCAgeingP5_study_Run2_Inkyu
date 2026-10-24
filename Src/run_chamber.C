#include <TSystem.h>
#include <iostream>
#include "pressure_dependence_removal.C"

void run_chamber(TString chamber = "ME11a") {
    TString inPath = "/blue/avery/inkyuhwang/CSCAgeingP5_study_Run2_Inkyu/OutputFiles_PV/2022/2022F_1/";
    TString inFile = "csc_output_2022F_1_" + chamber + "_tree.root";
    TString outPath = "./output_2022F/";
    TString plotFolder = "./plotfolder/";

    gSystem->mkdir(outPath, kTRUE);
    gSystem->mkdir(plotFolder, kTRUE);

    std::cout << ">>> Running calibration on chamber: " << chamber << std::endl;
    std::cout << ">>> Input File: " << inPath + inFile << std::endl;

    pressure_dependence_removal pdr;
    pdr.Loop(inPath, inFile, chamber, outPath, plotFolder);

    std::cout << ">>> Processing complete for: " << chamber << std::endl;
}
