#ifndef MeanPlots_h
#define MeanPlots_h

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <TString.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMarker.h>
#include <TLatex.h>
#include <TPad.h>

class MeanPlot {
public:
    TString fit_name;
    TString var;
    TString cut_string;
    TString result_path;
    TString year;
    std::vector<float> mean_values_vector;
    std::vector<float> mean_error_values_vector;
    std::vector<TString> chamber_name;
    TGraphErrors *graph_mean_values;

    void initialise(std::vector<std::pair<float, float>> mean_vector,
                    std::vector<TString> chamber, TString year_value,
                    TString var_name, TString fit_type, TString save_path,
                    TString cut_string_name);
    void plot_mean();
};

#endif
