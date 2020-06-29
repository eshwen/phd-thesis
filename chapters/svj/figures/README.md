# Making signal plots

To make signal MC distributions for my thesis, see the instructions below.

## Making the samples

To produce the actual nanoAOD samples, follow the instructions at <https://github.com/eshwen/SemivisibleJets>. But since the setup of the code only seems to work on lxplus, after making the files transfer them over to Bristol's server with `rsync`. It's probably also a good idea to keep them on hdfs. See <https://hadoop.apache.org/docs/r2.4.1/hadoop-project-dist/hadoop-common/FileSystemShell.html> for commands (e.g., creating directories and copying files over). After the samples are in their proper place, the analysis and plotting is done with the FAST tools within the chip repository.

## Analysis

### Setup

First, checkout the `esh_svj` branch from [my fork](https://gitlab.cern.ch/ebhal/chip/) of chip. Also, install my edits to `fast-plotter` v0.2.1:

```bash
pip install -e git+https://github.com/eshwen/fast-plotter.git@esh_v0.2.1_fixes#egg=fast-plotter
pip install pandas==0.25.3  # since v1.0.0 and later don't work with this branch
```

Stylistically, things are different compared to the later versions (dashed lines over solid for signal, changes to how regexes are handled, etc.). This branch fixes some bugs/problems in v0.2.1 (the dataset order in `utils.py`, using tight margins to limit unused whitespace, etc.). These changes are best made in a separate conda environment to the main one I use for the chip repo, just so I'm not constantly reinstalling `fast-plotter` and `pandas` etc. So follow all the instructions to setting up the environment as normal, but at the end, run the two lines above.

On sc01, I've set up the environment under `/software/eb16003/miniconda3_esh_svj_plotting` and can initialise it with `source ~/svj_chip-setup.sh`.

Dataset configs can be produced with `fast-curator` if not done so already. Run

```bash
fast_curator -d <dataset name> -o ./samples/svj/<dataset name>.yaml -m "stitching_flag=False" -m "filter_efficiency=1.0" <path to ROOT file>
```

for each sample. To properly interface with the cross section reweighting scribbler, the above metadata arguments are required in the dataset config, as well as the entries

- `n_unskimmed_events`: can just be the same as `nevents`
- `xs`: the cross section from MadGraph or something. Since, in `fast-plotter`, MC is normalised _to_ the cross section, to have it normalise to unity, set the cross section as 1/`nevents`

### MadGraph vs Pythia comparisons

#### Running `fast-carpenter` to get the dataframes

To make comparison plots between my MadGraph implementation and Fermilab's Pythia one, from the top-level directory of the chip repo, run

```bash
fast_carpenter --ncores 2 --outdir ./svj_comparisons_AN/dfs_part1/ ./samples/svj/all_svj_signals_2016_part1.yaml ./configs/svj_comparisons_2016.yaml
fast_carpenter --ncores 2 --outdir ./svj_comparisons_AN/dfs_part2/ ./samples/svj/all_svj_signals_2016_part2.yaml ./configs/svj_comparisons_2016.yaml
```

#### Running `fast-plotter` to get the plots

Run over each dataframe with plotting configs tailored to them (for correct x-axis ranges and y-axis bin widths):

```bash
plot_config_dir="$PWD/plotting_configs/svj_plotting_configs"
plots_outdir_part1="$PWD/svj_comparisons_AN/plots_part1/"
dfs_dir_part1="$PWD/svj_comparisons_AN/dfs_part1"

fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_dijet_deta.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/tbl_dataset.dijet_deta--dijet_deta_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_dijet_mt.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/tbl_dataset.dijet_mt--dijet_mt_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_ht.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/tbl_dataset.ht--HT_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_jet_eta.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/{tbl_dataset.leadFatJet_eta--lead_jet_eta.csv,tbl_dataset.sublFatJet_eta--subl_jet_eta.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_jet_phi.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/{tbl_dataset.leadFatJet_phi--lead_jet_phi.csv,tbl_dataset.sublFatJet_phi--subl_jet_phi.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_jet_pt.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/{tbl_dataset.dijet_pt--dijet_pt_df.csv,tbl_dataset.leadFatJet_pt--lead_jet.csv,tbl_dataset.sublFatJet_pt--subl_jet.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_metovermt.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/tbl_dataset.met_over_mt--met_mt_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_mht_met.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/{tbl_dataset.met--MET_df.csv,tbl_dataset.mht_pt--MHT_df.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_min_dphi.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/tbl_dataset.min_dphi--min_dphi_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part1_njet.yaml -o $plots_outdir_part1 ${dfs_dir_part1}/tbl_dataset.njet--n_jets.csv

plots_outdir_part2="$PWD/svj_comparisons_AN/plots_part2/"
dfs_dir_part2="$PWD/svj_comparisons_AN/dfs_part2"

fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_dijet_deta.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/tbl_dataset.dijet_deta--dijet_deta_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_dijet_mt.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/tbl_dataset.dijet_mt--dijet_mt_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_ht.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/tbl_dataset.ht--HT_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_jet_eta.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/{tbl_dataset.leadFatJet_eta--lead_jet_eta.csv,tbl_dataset.sublFatJet_eta--subl_jet_eta.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_jet_phi.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/{tbl_dataset.leadFatJet_phi--lead_jet_phi.csv,tbl_dataset.sublFatJet_phi--subl_jet_phi.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_jet_pt.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/{tbl_dataset.dijet_pt--dijet_pt_df.csv,tbl_dataset.leadFatJet_pt--lead_jet.csv,tbl_dataset.sublFatJet_pt--subl_jet.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_metovermt.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/tbl_dataset.met_over_mt--met_mt_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_mht_met.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/{tbl_dataset.met--MET_df.csv,tbl_dataset.mht_pt--MHT_df.csv}
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_min_dphi.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/tbl_dataset.min_dphi--min_dphi_df.csv
fast_plotter -c ${plot_config_dir}/svj_plot_config_part2_njet.yaml -o $plots_outdir_part2 ${dfs_dir_part2}/tbl_dataset.njet--n_jets.csv
```

which will make two sets of plots in `$plots_outdir_part1` and `$plots_outdir_part2`. By default, they will include the ratio sub-plot for MadGraph/Pythia if "MadGraph" is any of the dataset names. To remove this, edit [this bit](https://github.com/eshwen/fast-plotter/blob/8ddf1bbf367f69a1fcad150f0771409876f03e81/fast_plotter/plotting.py#L182-L186) to uncomment the first line and comment the others. Plots made without the ratio subplot should be identical to those in the semi-visible jets analysis note (AN-19-061), the only differences being different signal line colours and widths, and smaller margins.

If I was using a later version of `fast-plotter` (where I'd still have to fix the signal line ordering and solidity, and maybe the `bbox_inches='tight'` option when saving), I could possibly use variable replacements to set the x-axis ranges and y-axis label so I only need one plotting config. But maybe that's something for the future.

To semi-automate the renaming of plots, do

```bash
cd $plots_outdir_part1
for f in $(ls plot_dataset.*.pdf); do mv $f "${f#plot_dataset.*}"; done
for g in $(ls *--*.pdf); do mv $g "${g%%-*}.pdf"; done
cd -
cd $plots_outdir_part2
for f in $(ls plot_dataset.*.pdf); do mv $f "${f#plot_dataset.*}"; done
for g in $(ls *--*.pdf); do mv $g "${g%%-*}.pdf"; done
cd -
```

These plots should be stored in [madgraph_pythia_comparisons/](madgraph_pythia_comparisons/). Copies of the dataframes used to make the plots should also be stored in the event the plots themselves need to be regenerated.

### s-channel and t-channel MadGraph plots

#### Getting the dataframes

To run all s-channel and t-channel signals together, from the top-level directory of the chip repo, run

```bash
fast_carpenter --outdir svj_s_t_thesis_all ./samples/svj/svj_signals_esh_2016_thesis_all.yaml ./configs/svj_s_t_channel_thesis_2016.yaml
```

The main processing config is `configs/svj_s_t_channel_thesis_2016.yaml`. Only cross section reweighting and the definitions of necessary variables should be performed.

The signal samples can also be split into two "sets", i.e., each set will be on a separate plot to avoid too many signal lines cluttering things. Run these sets with

```bash
fast_carpenter --outdir svj_s_t_thesis_set1 ./samples/svj/svj_signals_esh_2016_thesis_set1.yaml ./configs/svj_s_t_channel_thesis_2016.yaml
fast_carpenter --outdir svj_s_t_thesis_set2 ./samples/svj/svj_signals_esh_2016_thesis_set2.yaml ./configs/svj_s_t_channel_thesis_2016.yaml
```

#### Getting the plots

WIP.
