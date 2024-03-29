# Making plots for the semi-visible jets chapter

To make signal MC distributions for my thesis, see the instructions in [Making the samples](#making-the-samples). To make the plot(s) of Lambda_dark vs m_dark, see [Lambda_dark vs m_dark](#lambdadark-vs-mdark).

- [Making plots for the semi-visible jets chapter](#making-plots-for-the-semi-visible-jets-chapter)
  - [Making the samples](#making-the-samples)
  - [Analysis](#analysis)
    - [Setup](#setup)
    - [MadGraph vs Pythia comparisons](#madgraph-vs-pythia-comparisons)
      - [Running `fast-carpenter` to get the dataframes](#running-fast-carpenter-to-get-the-dataframes)
      - [Running `fast-plotter` to get the plots](#running-fast-plotter-to-get-the-plots)
    - [Variations on the s-channel and t-channel benchmark models](#variations-on-the-s-channel-and-t-channel-benchmark-models)
      - [Getting the dataframes](#getting-the-dataframes)
      - [Getting the plots](#getting-the-plots)
  - [Lambda_dark vs m_dark](#lambdadark-vs-mdark)
  - [Mass insertion diagram](#mass-insertion-diagram)
  - [Things to remember when remaking plots](#things-to-remember-when-remaking-plots)

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
fast_curator -d <dataset name> -o ./samples/svj/<dataset name>.yaml -m "stitching_flag=False" -m "filter_efficiency=1.0" --mc <path to ROOT file>
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
parts=( "1" "2" )
plot_config_dir="$PWD/plotting_configs/svj_plotting_configs"
for part in "${parts[@]}"; do
    plots_outdir="$PWD/svj_comparisons_AN/plots_part${part}/"
    dfs_dir="$PWD/svj_comparisons_AN/dfs_part${part}"

    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_dijet_deta.yaml -o $plots_outdir $dfs_dir/tbl_dataset.dijet_deta--dijet_deta_df.csv
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_dijet_mt.yaml -o $plots_outdir $dfs_dir/tbl_dataset.dijet_mt--dijet_mt_df.csv
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_ht.yaml -o $plots_outdir $dfs_dir/tbl_dataset.ht--HT_df.csv
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_jet_eta.yaml -o $plots_outdir $dfs_dir/{tbl_dataset.leadFatJet_eta--lead_jet_eta.csv,tbl_dataset.sublFatJet_eta--subl_jet_eta.csv}
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_jet_phi.yaml -o $plots_outdir $dfs_dir/{tbl_dataset.leadFatJet_phi--lead_jet_phi.csv,tbl_dataset.sublFatJet_phi--subl_jet_phi.csv}
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_jet_pt.yaml -o $plots_outdir $dfs_dir/{tbl_dataset.dijet_pt--dijet_pt_df.csv,tbl_dataset.leadFatJet_pt--lead_jet.csv,tbl_dataset.sublFatJet_pt--subl_jet.csv}
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_metovermt.yaml -o $plots_outdir $dfs_dir/tbl_dataset.met_over_mt--met_mt_df.csv
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_mht_met.yaml -o $plots_outdir $dfs_dir/{tbl_dataset.met--MET_df.csv,tbl_dataset.mht_pt--MHT_df.csv}
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_min_dphi.yaml -o $plots_outdir $dfs_dir/tbl_dataset.min_dphi--min_dphi_df.csv
    fast_plotter -c $plot_config_dir/svj_plot_config_part${part}_njet.yaml -o $plots_outdir $dfs_dir/tbl_dataset.njet--n_jets.csv

    # Rename the plots, stripping parts of the long filenames
    pushd $plots_outdir
    for f in $(ls plot_dataset.*.pdf); do mv $f "${f#plot_dataset.*}"; done
    for g in $(ls *--*.pdf); do mv $g "${g%%-*}.pdf"; done
    popd
done
```

which will make two sets of plots in `svj_comparisons_AN/plots_part{1,2}`. By default, they will include the ratio sub-plot for MadGraph/Pythia if "MadGraph" is any of the dataset names. To remove this, edit [this bit](https://github.com/eshwen/fast-plotter/blob/8ddf1bbf367f69a1fcad150f0771409876f03e81/fast_plotter/plotting.py#L182-L186) to uncomment the first line and comment the others. Plots made without the ratio subplot should be identical to those in the semi-visible jets analysis note (AN-19-061), the only differences being different signal line colours and widths, and smaller margins.

If I was using a later version of `fast-plotter` (where I'd still have to fix the signal line ordering and solidity, and maybe the reduced padding), I could possibly use variable replacements to set the x-axis ranges and y-axis label so I only need one plotting config. But maybe that's something for the future.

These plots should be stored in [madgraph_pythia_comparisons/](madgraph_pythia_comparisons/). Copies of the dataframes used to make the plots should also be stored in the event the plots themselves need to be regenerated.

### Variations on the s-channel and t-channel benchmark models

#### Getting the dataframes

To run the s-channel signal samples with variations on the benchmark point SVJ_3000_20_0.3_peak or t-channel samples with variations on the SVJ_2000_20_0.5_peak benchmark, from the top-level directory of the chip repo, first set an environment variable to indicate which type to run:

```bash
svj_model="s"  # for s-channel. Replace "s" with "t" for t-channel
if [[ $svj_model == "s" ]]; then
    med="Zp"
else
    med="Phi"
fi
```

```bash
fast_carpenter --ncores 2 --outdir svj_${svj_model}_thesis_benchmark_variations_aD ./samples/svj/svj_signals_esh_${svj_model}_2016_thesis_benchmark_variations_aD.yaml ./configs/svj_comparisons_2016.yaml
fast_carpenter --ncores 2 --outdir svj_${svj_model}_thesis_benchmark_variations_mD ./samples/svj/svj_signals_esh_${svj_model}_2016_thesis_benchmark_variations_mD.yaml ./configs/svj_comparisons_2016.yaml
fast_carpenter --ncores 2 --outdir svj_${svj_model}_thesis_benchmark_variations_m${med} ./samples/svj/svj_signals_esh_${svj_model}_2016_thesis_benchmark_variations_m${med}.yaml ./configs/svj_comparisons_2016.yaml
fast_carpenter --ncores 2 --outdir svj_${svj_model}_thesis_benchmark_variations_rinv ./samples/svj/svj_signals_esh_${svj_model}_2016_thesis_benchmark_variations_rinv.yaml ./configs/svj_comparisons_2016.yaml
```

The same processing config as the MadGraph-Pythia comparisons is used for simplicity.

#### Getting the plots

To make the plots, run

```bash
df="tbl_dataset.dijet_mt--dijet_mt_df.csv"  # tbl_dataset.met--MET_df.csv for MET, tbl_dataset.min_dphi--min_dphi_df.csv for min dphi, tbl_dataset.njet--n_jets.csv for number of jets, tbl_dataset.dijet_pt--dijet_pt_df.csv for dijet pt
if [[ "$df" == *"--dijet_mt"* ]]; then
    plotting_cfg=$(readlink -m plotting_configs/svj_plotting_configs/svj_plot_config_benchmark_variations_dijet_mt.yaml)
elif [[ "$df" == *"--MET"* ]]; then
    plotting_cfg=$(readlink -m plotting_configs/svj_plotting_configs/svj_plot_config_benchmark_variations_met.yaml)
elif [[ "$df" == *"--min_dphi"* ]]; then
    plotting_cfg=$(readlink -m plotting_configs/svj_plotting_configs/svj_plot_config_benchmark_variations_min_dphi.yaml)
elif [[ "$df" == *"--n_jets"* ]]; then
    plotting_cfg=$(readlink -m plotting_configs/svj_plotting_configs/svj_plot_config_benchmark_variations_njet.yaml)
elif [[ "$df" == *"--dijet_pt"* ]]; then
    plotting_cfg=$(readlink -m plotting_configs/svj_plotting_configs/svj_plot_config_benchmark_variations_dijet_pt.yaml)
fi

if [[ $svj_model == "s" ]]; then
    sed -i 's/4e7/4e6/g' $plotting_cfg
elif [[ $svj_model == "t" ]]; then
    sed -i 's/4e6/4e7/g' $plotting_cfg
fi
out_dirs=( "svj_${svj_model}_thesis_benchmark_variations_mD" "svj_${svj_model}_thesis_benchmark_variations_m${med}" "svj_${svj_model}_thesis_benchmark_variations_rinv" )
for dir in "${out_dirs[@]}"; do
    fast_plotter -c $plotting_cfg -o $dir $dir/$df
done
```

The upper-limit on the y-axis needs to be changed for t-channel because the cross section (from MadGraph) for low mPhi is high. Because of the fact I'm only including 4 lines instead of 5 for the alpha_dark variation, if I want the the colours to be consistent, I'll have to change [this line](https://github.com/eshwen/fast-plotter/blob/esh_v0.2.1_fixes/fast_plotter/plotting.py#L57) in `fast-plotter`, changing `.96` to `.808` and re-run the plotting with

```bash
sed -i 's/.96/.808/g' ../src/fast-plotter/fast_plotter/plotting.py
fast_plotter -c $plotting_cfg -o svj_${svj_model}_thesis_benchmark_variations_aD svj_${svj_model}_thesis_benchmark_variations_aD/$df
sed -i 's/.808/.96/g' ../src/fast-plotter/fast_plotter/plotting.py
if [[ $svj_model == "s" ]]; then
    sed -i 's/4e7/4e6/g' $plotting_cfg
elif [[ $svj_model == "t" ]]; then
    sed -i 's/4e6/4e7/g' $plotting_cfg
fi
```

If not plotting any variables other than the dijet MT, delete the other dataframes with, e.g.,

```bash
shopt -s extglob
for dir in "${out_dirs[@]}"; do
    for redundant_file in $dir/!($df|*.pdf); do
        rm $redundant_file
    done
done
```

**COULD INSTEAD PUT ALL OUTPUT PLOTS IN ONE NEW DIRECTORY, WHERE AFTER EACH PLOT IS CREATED, IT'S RENAMED AS ABOVE. PULL THE DATAFRAME IN FROM THE RESPECTIVE DIRECTORY AND RENAME THAT ACCORDINGLY AS WELL, SO I HAVE ONE DIRECTORY CONTAINING ALL THE VARIATION PLOTS AND DATAFRAMES.**

## Lambda_dark vs m_dark

I have a little script in my [SemivisibleJets](https://github.com/eshwen/SemivisibleJets) repo to plot this with `matplotlib`: <https://github.com/eshwen/SemivisibleJets/blob/master/utils/plot_lambdaD_v_mDH.py>. It can just be executed with

```bash
python plot_lambdaD_v_mDH.py
```

Since the script is so small, everything within it should be pretty self-explanatory.

## Mass insertion diagram

This is taken directly from the semi-visible jets analysis note AN-19-061. The repo link is [here](https://gitlab.cern.ch/tdr/notes/AN-19-061), with the permalink to the figure [here](https://gitlab.cern.ch/tdr/notes/AN-19-061/-/blob/4f97acefe944aa033b8a9b6ca914ee477e790359/img/signal/mass_insertion_diagram.pdf).

## Things to remember when remaking plots

- Make sure there are no "CMS" annotations on any of them as the results are not approved
- Make sure they're in pdf format if possible, since they're likely to be vector graphics

For plots with `fast-plotter` (perhaps within <https://gitlab.cern.ch/cms-chip/chip/-/blob/master/chip_code/make_nonVBF_plots.py>):

- Use the right x-axis limits so there's no horizontal space between the histograms and axis limits.
- Add the bin widths on the y-axis label if the bin width is constant. Achievable in the plotting config with the `ylabel` kwarg
- Make sure signal line colours are consistent (broken in `fast-plotter` as of v0.8.0)
