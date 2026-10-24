#include "MeanPlots.h"

void MeanPlot::initialise(std::vector<std::pair<float, float>> mean_vector,
                          std::vector<TString> chamber, TString year_value,
                          TString var_name, TString fit_type, TString save_path,
                          TString cut_string_name) {
    fit_name = fit_type;
    var = var_name;
    cut_string = cut_string_name;
    result_path = save_path;
    year = year_value;

    for (size_t i = 0; i < chamber.size(); i++) {
        mean_values_vector.push_back(mean_vector[i].first);
        mean_error_values_vector.push_back(mean_vector[i].second);
        chamber_name.push_back(chamber[i]);
    }
}

void MeanPlot::plot_mean() {
    std::vector<float> value(chamber_name.size());
    for (size_t i = 0; i < chamber_name.size(); i++) {
        value[i] = i + 1;
    }

    graph_mean_values = new TGraphErrors(chamber_name.size(), value.data(),
                                         mean_values_vector.data(), 0,
                                         mean_error_values_vector.data());
    graph_mean_values->GetXaxis()->SetTickLength(1);

    if (var == "_pressure") {
        graph_mean_values->GetYaxis()->SetRangeUser(-0.010, 0.002);
    } else if (var == "_pressure_second") {
        graph_mean_values->GetYaxis()->SetRangeUser(-0.0005, 0.0005);
    } else if (var == "_instlumi") {
        graph_mean_values->GetYaxis()->SetRangeUser(-0.00001, 0.00001);
    } else {
        graph_mean_values->GetYaxis()->SetRangeUser(-0.001, 0.001);
    }

    for (size_t i = 0; i < chamber_name.size(); i++) {
        graph_mean_values->GetXaxis()->SetBinLabel(
            graph_mean_values->GetXaxis()->FindBin(i + 1.), chamber_name[i]);
    }
    graph_mean_values->GetXaxis()->SetTitleOffset(0.1);

    TCanvas *canv1 = new TCanvas("canv1", "Mean Slope Plot", 1000, 600);
    canv1->cd();
    canv1->SetLeftMargin(0.12);
    canv1->SetGrid();
    gPad->SetGrid();
    graph_mean_values->Draw("AP");
    graph_mean_values->SetTitle("");

    Double_t *gr_xarray = graph_mean_values->GetX();
    Double_t *gr_yarray = graph_mean_values->GetY();

    std::map<TString, int> marker_colour = {
        {"ME11a", 8}, {"ME11b", 8},
        {"ME12HV1", 2}, {"ME12HV2", 2}, {"ME12HV3", 2},
        {"ME13HV1", 2}, {"ME13HV2", 2}, {"ME13HV3", 2},
        {"ME21HV1", 4}, {"ME21HV2", 4}, {"ME21HV3", 4},
        {"ME22HV1", 2}, {"ME22HV2", 2}, {"ME22HV3", 2}, {"ME22HV4", 2}, {"ME22HV5", 2},
        {"ME31HV1", 4}, {"ME31HV2", 4}, {"ME31HV3", 4},
        {"ME32HV1", 2}, {"ME32HV2", 2}, {"ME32HV3", 2}, {"ME32HV4", 2}, {"ME32HV5", 2},
        {"ME41HV1", 4}, {"ME41HV2", 4}, {"ME41HV3", 4},
        {"ME42HV1", 2}, {"ME42HV2", 2}, {"ME42HV3", 2}, {"ME42HV4", 2}, {"ME42HV5", 2}
    };

    TLegend *legend_1 = new TLegend(0.7, 0.7, 0.9, 0.9);
    for (size_t j = 0; j < chamber_name.size(); j++) {
        TMarker *m = new TMarker(gr_xarray[j], gr_yarray[j], 20);
        m->SetMarkerColor(marker_colour[chamber_name[j]]);
        m->Draw();

        if (j == 0) legend_1->AddEntry(m, " ME11a, ME11b (10^{0})", "p");
        if (j == 3) legend_1->AddEntry(m, " Outer Chambers (10^{0})", "p");
        if (j == 8) legend_1->AddEntry(m, " Inner Chambers (20^{0})", "p");
    }
    legend_1->Draw("SAME");

    TLatex *cmslabel_1 = new TLatex(0.18, 0.82, "CMS #bf{#it{Preliminary}}");
    cmslabel_1->SetNDC(kTRUE);
    cmslabel_1->SetTextSize(0.06);
    cmslabel_1->SetTextFont(42);
    cmslabel_1->Draw("same");

    TLatex *text2 = new TLatex(0.46, 0.56, cut_string);
    text2->SetTextFont(42);
    text2->SetTextSize(0.04);
    text2->SetNDC(kTRUE);
    text2->Draw("same");

    canv1->SaveAs(result_path + "mean_slope_values_" + var + "_" + year + "_" + fit_name + ".pdf");
}
