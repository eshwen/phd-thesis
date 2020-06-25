# Consider rewriting in Python
df="./tbl_dataset.region.min_omega_tilde.category--min_omega_tilde.csv"
split_dfs_dir="input_dfs_min_omega_tilde/"
year=2017
ext="png"

cd fast_caliper

# Post-processes min_omega_tilde dataframe and generate configs for each figure of merit
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s SoverSqrtB $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s SoverSqrtB_uncertainty5pc $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s asimov $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s asimov_uncertainty5pc $df $year

# Run fast-caliper on ttH, VH and ggF categories for each figure of merit, and combine the categories for each process in quadrature sum
./run_caliper_all_categories_and_combine.sh ttH SoverSqrtB
./run_caliper_all_categories_and_combine.sh VH SoverSqrtB
./run_caliper_all_categories_and_combine.sh ggF SoverSqrtB
./run_caliper_all_categories_and_combine.sh ttH SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh VH SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh ggF SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh ttH asimov
./run_caliper_all_categories_and_combine.sh VH asimov
./run_caliper_all_categories_and_combine.sh ggF asimov
./run_caliper_all_categories_and_combine.sh ttH asimov_uncertainty5pc
./run_caliper_all_categories_and_combine.sh VH asimov_uncertainty5pc
./run_caliper_all_categories_and_combine.sh ggF asimov_uncertainty5pc

# Plot the figures of merit for each process and save pdfs
python plot_multi_signifs.py -y $year -e $ext -p ttH out_ttH_combined_SoverSqrtB.csv out_ttH_combined_SoverSqrtB_uncertainty5pc.csv out_ttH_combined_asimov.csv out_ttH_combined_asimov_uncertainty5pc.csv 
python plot_multi_signifs.py -y $year -e $ext -p VH out_VH_combined_SoverSqrtB.csv out_VH_combined_SoverSqrtB_uncertainty5pc.csv out_VH_combined_asimov.csv out_VH_combined_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggF out_ggF_combined_SoverSqrtB.csv out_ggF_combined_SoverSqrtB_uncertainty5pc.csv out_ggF_combined_asimov.csv out_ggF_combined_asimov_uncertainty5pc.csv

# Do the same for min_dphi in monojet case
df="./tbl_dataset.region.min_dphi_4j.category--min_dphi.csv"
split_dfs_dir="input_dfs_min_dphi/"

python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s SoverSqrtB $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s SoverSqrtB_uncertainty5pc $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s asimov $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s asimov_uncertainty5pc $df $year

./run_caliper_all_categories_and_combine.sh monojet SoverSqrtB
./run_caliper_all_categories_and_combine.sh monojet SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh monojet asimov
./run_caliper_all_categories_and_combine.sh monojet asimov_uncertainty5pc

python plot_multi_signifs.py -y $year -e $ext -p monojet out_monojet_combined_SoverSqrtB.csv out_monojet_combined_SoverSqrtB_uncertainty5pc.csv out_monojet_combined_asimov.csv out_monojet_combined_asimov_uncertainty5pc.csv


# Make plots for each individual category
python plot_multi_signifs.py -y $year -e $ext -p ttH_2Boosted output_dfs/out_category_1.01_SoverSqrtB.csv output_dfs/out_category_1.01_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.01_asimov.csv output_dfs/out_category_1.01_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_1t0b output_dfs/out_category_1.02_SoverSqrtB.csv output_dfs/out_category_1.02_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.02_asimov.csv output_dfs/out_category_1.02_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_1t1b output_dfs/out_category_1.03_SoverSqrtB.csv output_dfs/out_category_1.03_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.03_asimov.csv output_dfs/out_category_1.03_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_1w1b output_dfs/out_category_1.04_SoverSqrtB.csv output_dfs/out_category_1.04_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.04_asimov.csv output_dfs/out_category_1.04_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_1w2b output_dfs/out_category_1.05_SoverSqrtB.csv output_dfs/out_category_1.05_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.05_asimov.csv output_dfs/out_category_1.05_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_5j1b output_dfs/out_category_1.06_SoverSqrtB.csv output_dfs/out_category_1.06_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.06_asimov.csv output_dfs/out_category_1.06_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_6j1b output_dfs/out_category_1.07_SoverSqrtB.csv output_dfs/out_category_1.07_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.07_asimov.csv output_dfs/out_category_1.07_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_5j2b output_dfs/out_category_1.08_SoverSqrtB.csv output_dfs/out_category_1.08_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.08_asimov.csv output_dfs/out_category_1.08_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ttH_6j2b output_dfs/out_category_1.09_SoverSqrtB.csv output_dfs/out_category_1.09_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_1.09_asimov.csv output_dfs/out_category_1.09_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p VH_2j0b output_dfs/out_category_2.01_SoverSqrtB.csv output_dfs/out_category_2.01_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_2.01_asimov.csv output_dfs/out_category_2.01_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p VH_2j1b output_dfs/out_category_2.02_SoverSqrtB.csv output_dfs/out_category_2.02_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_2.02_asimov.csv output_dfs/out_category_2.02_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p VH_2j2b output_dfs/out_category_2.03_SoverSqrtB.csv output_dfs/out_category_2.03_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_2.03_asimov.csv output_dfs/out_category_2.03_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p VH_1V output_dfs/out_category_2.04_SoverSqrtB.csv output_dfs/out_category_2.04_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_2.04_asimov.csv output_dfs/out_category_2.04_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggF_2jM output_dfs/out_category_3.01_SoverSqrtB.csv output_dfs/out_category_3.01_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.01_asimov.csv output_dfs/out_category_3.01_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggF_3j output_dfs/out_category_3.02_SoverSqrtB.csv output_dfs/out_category_3.02_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.02_asimov.csv output_dfs/out_category_3.02_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggF_4j output_dfs/out_category_3.03_SoverSqrtB.csv output_dfs/out_category_3.03_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.03_asimov.csv output_dfs/out_category_3.03_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggF_5j output_dfs/out_category_3.04_SoverSqrtB.csv output_dfs/out_category_3.04_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.04_asimov.csv output_dfs/out_category_3.04_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p Monojet_1j0b output_dfs/out_category_4.01_SoverSqrtB.csv output_dfs/out_category_4.01_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_4.01_asimov.csv output_dfs/out_category_4.01_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p Monojet_1j1b output_dfs/out_category_4.02_SoverSqrtB.csv output_dfs/out_category_4.02_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_4.02_asimov.csv output_dfs/out_category_4.02_asimov_uncertainty5pc.csv
