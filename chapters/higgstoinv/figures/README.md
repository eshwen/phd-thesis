# Making plots for the Higgs to invisible analysis chapter

This README should be an indicator of how to make some of the plots included in the Higgs to invisible analysis chapter, in case they need to be regenerated or I need more context for them.

- [Making plots for the Higgs to invisible analysis chapter](#making-plots-for-the-higgs-to-invisible-analysis-chapter)
  - [`fast-plotter` plots](#fast-plotter-plots)
    - [Category optimisations](#category-optimisations)
    - [HEM issue](#hem-issue)
    - [Full Run-2 region plots](#full-run-2-region-plots)
  - [Dark matter limit plot](#dark-matter-limit-plot)
  - [Fit overview](#fit-overview)
  - [Limit and likelihood scan](#limit-and-likelihood-scan)
  - [NLO k-factors](#nlo-k-factors)
  - [Trigger efficiencies](#trigger-efficiencies)
  - [ttbar scale](#ttbar-scale)
  - [Things to remember when remaking plots](#things-to-remember-when-remaking-plots)

## `fast-plotter` plots

Some of the plots in [category_optimisations/](category_optimisations), [hem_issue/](hem_issue/), and [region_plots/](region_plots/) came from `fast-plotter`, potentially via the script <https://gitlab.cern.ch/cms-chip/chip/-/blob/master/chip_code/make_nonVBF_plots.py>.

### Category optimisations

The significance line plots in [category_optimisations/](category_optimisations) were made with my fork of `fast-caliper` (<https://gitlab.cern.ch/ebhal/fast-caliper>), and commands similar to [run_all_significances.sh](category_optimisations/run_all_significances.sh). The histograms came from `make_nonVBF_plots.py`.

### HEM issue

For the plots in [hem_issue/](hem_issue/) that contain a translucent block the histograms were made with `fast-plotter`, then edited in Preview to add the block itself. Annoyingly, adding the block does so as a pdf annotation, so is essentially saved as metadata and isn't part of the plot itself. To make it part of the plot, in Preview do **File** -> **Export as PDF...**. Then, click **Show Details**, and set **Paper Size** as **8x10 Borderless** so the aspect ratio is as close to the original plot as possible. Any leftover whitespace can be cropped in Preview after the fact. To get the dataframes used to make the plot, I had to run the latest 2018 config in the chip repo, commenting out the HEM vetoes in the cut flow.

### Full Run-2 region plots

The full Run-2 signal region, control region, and sideband plots were made using the instructions [here](https://gitlab.cern.ch/cms-chip/chip/-/blob/master/configs/nonVBF_instructions.md#plots-for-2016-18-combined).

## Dark matter limit plot

This should be documented in [dark_matter_limit/](dark_matter_limit/), as it is a self-contained `ROOT` macro that makes it.

## Fit overview

This is a self-contained plot in [fit_overview.pptx](fit_overview.pptx). Editable in PowerPoint, the single slide can then be saved as a pdf.

## Limit and likelihood scan

For the code and inputs required to make the limit and likelihood scan plots (in [limits/](limits/) and [likelihood_scan/](likelihood_scan/), respectively), refer to the instructions in <https://gitlab.cern.ch/cms-chip/chip/-/tree/master/fitting> and <https://gitlab.cern.ch/cms-chip/chip/-/tree/master/fitting/plot_fit_results/>. I'll try to maintain keeping a copy of the latest root files and plots in [2016/](2016/), [2017/](2017/), and [2018/](2018/) in case I need a reference or need to regenerate them. The commit datestamp will give an indication as to when they were made.

## NLO k-factors

In the chip repo, navigate to the `chip_code/` directory. For the 2D NLO QCD k-factor plots, just run

```bash
python plot_k_factors.py -p ../input_weight_data/nloSF_files/2Dkfactor_nonVBF_wjet.root
mv 2Dkfactor_nonVBF_wjet.pdf 2D_wjets.pdf
python plot_k_factors.py -p ../input_weight_data/nloSF_files/2Dkfactor_nonVBF_zjet.root
mv 2Dkfactor_nonVBF_zjet.pdf 2D_zll.pdf
python plot_k_factors.py -p ../input_weight_data/nloSF_files/2Dkfactor_nonVBF_znn.root
mv 2Dkfactor_nonVBF_znn.pdf 2D_znunu.pdf
```

For the 1D NLO QCD k-factor for gamma + jets, run

```bash
python plot_k_factors.py -d kfactor_monojet_qcd ../input_weight_data/nloSF_files/merged_kfactors_gjets.root
mv merged_kfactors_gjets.pdf 1D_gjets_qcd.pdf
```

and to plot all the electroweak k-factor together, run

```bash
python plot_k_factors.py -d kfactor_monojet_ewk ../input_weight_data/nloSF_files/merged_kfactors_{g,w,z}jets.root
mv merged_kfactors_zjets.pdf 1D_all_ewk.pdf
```

## Trigger efficiencies

For the plots of the trigger efficiencies, the dataframes are already available in chip under `input_weight_data/nonvbf_trigger_files/`. They can be remade if, e.g., the binning needs to be adjusted. I would then need to run, e.g.,

```bash
year=2016
if (( $year == 2016 )); then
    lumi=35920
elif (( $year == 2017 )); then
    lumi=41530
elif (( $year == 2018 )); then
    lumi=59740
fi
fast_carpenter --mode <mode> --outdir <outdir> ./samples/unskimmed/$year/all.yml ./configs/nonVBF_trigger/${year}_MET-MHT_efficiency.yml
```

But because this runs on unskimmed files, they must be readable over xrootd.

### 1D plots

The trigger efficiencies are made, by default, in 2D as a function of MET and MHT. To collapse the MHT dimension and plot them in 1D as a function of MET, run

```bash
cd chip_code
python trigger_turnons_1D.py <dataframe> <year>
```

For example, if running over the dataframes already in chip, do, e.g.,

```bash
year=2016
cd chip_code
python trigger_turnons_1D.py ../input_weight_data/nonvbf_trigger_files/$year/tbl_dataset.online.offline.met.mht--met_mht.csv $year
```

A cut on the MHT can be specified if you don't want to absorb the entire MHT dimension (as it would include underflow and low values). A default is placed at 200 GeV, since that's our analysis-level selection. But the value can be changed with the `-m` argument.

### 2D plots

A script is included in the chip repo to plot the trigger efficiencies and write the scale factors. To make them look more aesthetic, I made a copy of it and changed the styling. Run

```bash
cd chip_code/standalone_tools
python calculate_trigger_effs_esh_colormesh.py -c ../../samples/unskimmed/$year/all.yml -l $lumi -o trigger_effs_${year} <outdir from carpenter>/tbl_dataset.online.offline.met.mht--met_mht.csv
```

Don't worry about the errors that occur later on. They only affect the scale factor plots. For example, if running over the dataframes already in chip, do

```bash
cd chip_code/standalone_tools
python calculate_trigger_effs_esh_colormesh.py -c ../../samples/unskimmed/$year/all.yml -l $lumi -o trigger_effs_${year} ../../input_weight_data/nonvbf_trigger_files/$year/tbl_dataset.online.offline.met.mht--met_mht.csv
```

which will make the MET-MHT trigger turn ons in 2D as a function of both MET and MHT, and separately for data and MC. To annotate each cell in the plot with its efficiency, add the argument `-a` above. The styling, etc., can be easily changed in the `plot_2d()` function.



## ttbar scale

To make the plots showing the variations for the variations on the QCD renormalisation and factorisation scale with the ttbar samples, run any of the configs in the chip repo over the NLO ttbar Powheg samples. Then, run `top_systs_postproc.py` to make the plots that include the combinations of individual variations with

```bash
python chip_code/top_systs_postproc.py -e pdf <outdir from carpenter> <year>
```

To make the plots that exclude those variations, comment them out in the `weights_to_plot` dictionary. It might also be worth changing the `matplotlib` colour map to something more contrasting with

```bash
sed -i 's/Set3/tab10/g' chip_code/top_systs_postproc.py
```

Then run the command above to regenerate the plots.

## Things to remember when remaking plots

For all plots:

- Make sure status annotation next to "CMS" is correct, i.e., Preliminary/Work in progress/no annotation
- Make sure they're in pdf format if possible, since they're likely to be vector graphics. Especially if coming from `ROOT`, use pdfs as pngs are quite low resolution

For plots with `fast-plotter` (perhaps within <https://gitlab.cern.ch/cms-chip/chip/-/blob/master/chip_code/make_nonVBF_plots.py>):

- Add the variable replacements (region, category, lepton) when making region plots with `fast-plotter`
- Use the right x-axis limits so there's no horizontal space between the histograms and axis limits. This might be achievable generally within the plotting config by setting `limits: {x: 0%}` and `show_over_underflow: False`. So I may not have to manually set the limits for each plot
- Add the bin widths on the y-axis label if the bin width is constant. Achievable in the plotting config with the `ylabel` kwarg
- Make sure signal line colours are consistent (broken in `fast-plotter` as of v0.8.0)
- Make sure any plots in the ggF categories are labelled/annotated with "ggH", not "ggF"

For limit and likelihood plots:

- Make sure they are visually consistent (i.e., same size, with same "CMS" annotation, lumi, same labels for categories, etc.) if they are not produced together
