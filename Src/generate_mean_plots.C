#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "MeanPlots.C"

void generate_mean_plots() {
    std::vector<TString> chambers = {
        "ME11a", "ME11b",
        "ME12HV1", "ME12HV2", "ME12HV3",
        "ME13HV1", "ME13HV2", "ME13HV3",
        "ME21HV1", "ME21HV2", "ME21HV3",
        "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4", "ME22HV5",
        "ME31HV1", "ME31HV2", "ME31HV3",
        "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4", "ME32HV5",
        "ME41HV1", "ME41HV2", "ME41HV3",
        "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4", "ME42HV5"
    };

    std::vector<std::pair<float, float>> slopes_plus;
    std::vector<std::pair<float, float>> slopes_minus;
    std::vector<TString> valid_chambers_plus;
    std::vector<TString> valid_chambers_minus;

    TString inDir = "output_2022F/";
    TString outDir = "./plots_2022F/MeanPlots/";
    gSystem->mkdir(outDir, kTRUE);

    for (const auto& ch : chambers) {
        TString fitFile = inDir + "outf_dataset_" + ch + "_output_everything.root";
        TFile* f = TFile::Open(fitFile);
        if (!f || f->IsZombie()) {
            std::cerr << "Warning: Could not open " << fitFile << std::endl;
            continue;
        }

        TTree* tree_good = (TTree*)f->Get("tree_all_goodchannels_pressure");
        if (!tree_good) tree_good = (TTree*)f->Get("_pressure/tree_all_goodchannels_pressure");
        if (!tree_good) tree_good = (TTree*)f->Get("pressure/tree_all_goodchannels_pressure");

        if (!tree_good || tree_good->GetEntries() == 0) {
            std::cerr << "Warning: Missing slope tree in " << fitFile << std::endl;
            f->Close();
            continue;
        }

        Float_t slope_plus = 0, slope_err_plus = 0;
        Float_t slope_minus = 0, slope_err_minus = 0;
        tree_good->SetBranchAddress("_slope_goodchannels_plus", &slope_plus);
        tree_good->SetBranchAddress("_slope_error_goodchannels_plus", &slope_err_plus);
        tree_good->SetBranchAddress("_slope_goodchannels_minus", &slope_minus);
        tree_good->SetBranchAddress("_slope_error_goodchannels_minus", &slope_err_minus);

        // Read Entry 0 for Plus Endcap
        tree_good->GetEntry(0);
        float s_plus = slope_plus;
        float e_plus = slope_err_plus;
        float s_minus = slope_minus;
        float e_minus = slope_err_minus;

        // If tree has multiple entries, Minus Endcap is stored in Entry 1
        if (tree_good->GetEntries() > 1) {
            tree_good->GetEntry(1);
            if (std::abs(slope_minus) > 1e-6) {
                s_minus = slope_minus;
                e_minus = slope_err_minus;
            } else if (std::abs(slope_plus) > 1e-6) {
                s_minus = slope_plus;
                e_minus = slope_err_plus;
            }
        }

        std::cout << Form("Chamber: %-9s | Plus: %8.5f +/- %8.5f | Minus: %8.5f +/- %8.5f",
                          ch.Data(), s_plus, e_plus, s_minus, e_minus) << std::endl;

        if (!std::isnan(s_plus) && std::abs(s_plus) > 1e-6) {
            slopes_plus.push_back({s_plus, e_plus});
            valid_chambers_plus.push_back(ch);
        }

        if (!std::isnan(s_minus) && std::abs(s_minus) > 1e-6) {
            slopes_minus.push_back({s_minus, e_minus});
            valid_chambers_minus.push_back(ch);
        }

        f->Close();
    }

    // Generate Plus Endcap Summary Plot
    if (!valid_chambers_plus.empty()) {
        MeanPlot mp_plus;
        mp_plus.initialise(slopes_plus, valid_chambers_plus, "2022F", "_pressure", "plus_endcap", outDir, "Run 2022F (+Endcap)");
        mp_plus.plot_mean();
    }

    // Generate Minus Endcap Summary Plot
    if (!valid_chambers_minus.empty()) {
        MeanPlot mp_minus;
        mp_minus.initialise(slopes_minus, valid_chambers_minus, "2022F", "_pressure", "minus_endcap", outDir, "Run 2022F (-Endcap)");
        mp_minus.plot_mean();
    }

    std::cout << ">>> Mean slope summary plots updated in: " << outDir << std::endl;
}
