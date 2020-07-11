# Making plots for the Higgs to invisible analysis chapter

This README should be an indicator of how to make some of the plots included in the Higgs to invisible analysis chapter, in case they need to be regenerated or I need more context for them.

- [Making plots for the Higgs to invisible analysis chapter](#making-plots-for-the-higgs-to-invisible-analysis-chapter)
  - [`fast-plotter` plots](#-fast-plotter-plots)
  - [Limit and likelihood scan plots](#limit-and-likelihood-scan-plots)
  - [Dark matter limit plot](#dark-matter-limit-plot)
  - [ttbar scale plots](#ttbar-scale-plots)
  - [k-factors](#k-factors)
  - [Things to remember when remaking plots](#things-to-remember-when-remaking-plots)

## `fast-plotter` plots

Some of the plots in [category_optimisations/](category_optimisations), [hem_issue/](hem_issue/), and [region_plots/](region_plots/) came from `fast-plotter`, probably via the script <https://gitlab.cern.ch/cms-chip/chip/-/blob/master/chip_code/make_nonVBF_plots.py>.

The significance line plots in [category_optimisations/](category_optimisations) were made with my fork of `fast-caliper` (<https://gitlab.cern.ch/ebhal/fast-caliper>), and commands similar to [run_all_significances.sh](category_optimisations/run_all_significances.sh).

For the plots in [hem_issue/](hem_issue/) that contain a translucent block the histograms were made with `fast-plotter`, then edited in Preview to add the block itself. Annoyingly, adding the block does so as a pdf annotation, so is essentially saved as metadata and isn't part of the plot itself. To make it part of the plot, in Preview do **File** -> **Export as PDF...**. Then, click **Show Details**, and set **Paper Size** as **8x10 Borderless** so the aspect ratio is as close to the original plot as possible. Any leftover whitespace can be cropped in Preview after the fact.

## Limit and likelihood scan plots

For the code and inputs required to make the limit and likelihood scan plots (in [limits/](limits/) and [likelihood_scan/](likelihood_scan/), respectively), refer to the instructions in <https://gitlab.cern.ch/cms-chip/chip/-/tree/master/fitting> and <https://gitlab.cern.ch/cms-chip/chip/-/tree/master/fitting/plot_fit_results/>. I'll try to maintain keeping a copy of the latest root files and plots in [2016/](2016/), [2017/](2017/), and [2018/](2018/) in case I need a reference or need to regenerate them. The commit datestamp will give an indication as to when they were made.

## Dark matter limit plot

This should be documented in [dark_matter_limit/](dark_matter_limit/), as it is a self-contained `ROOT` macro that makes it.

## ttbar scale plots

To make the plots showing the variations for the variations on the QCD renormalisation and factorisation scale with the ttbar samples, run any of the configs in the chip repo over the NLO ttbar Powheg samples. Then, run `top_systs_postproc.py` to make the plots that include the combinations of individual variations with

```bash
python chip_code/top_systs_postproc.py -e pdf <outdir from carpenter> <year>
```

To make the plots that exclude those variations, comment them out in the `weights_to_plot` dictionary. It might also be worth changing the `matplotlib` colour map to something more contrasting with

```bash
sed -i 's/Set3/tab10/g' chip_code/top_systs_postproc.py
```

Then run the command above to regenerate the plots.

## k-factors

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
