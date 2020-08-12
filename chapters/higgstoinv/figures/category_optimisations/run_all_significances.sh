cd <dir to fast_caliper repo>
source esh_setup_env.sh

# Consider rewriting in Python
df="./tbl_dataset.region.min_omega_tilde.category--min_omega_tilde.csv"
split_dfs_dir="input_dfs_min_omega_tilde/"
year=2017
ext="pdf"

# Post-processes min_omega_tilde dataframe and generate configs for each figure of merit
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s SoverSqrtB $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s SoverSqrtB_uncertainty5pc $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s asimov $df $year
python post_proc_dfs_for_caliper.py -o $split_dfs_dir -s asimov_uncertainty5pc $df $year

# Run fast-caliper on ttH, VH and ggH categories for each figure of merit, and combine the categories for each process in quadrature sum
# If fast-caliper command doesn't exist, it may not be pip-installed. Run 'pip install -e .' from this directory to fix it
./run_caliper_all_categories_and_combine.sh ttH SoverSqrtB
./run_caliper_all_categories_and_combine.sh VH SoverSqrtB
./run_caliper_all_categories_and_combine.sh ggH SoverSqrtB
./run_caliper_all_categories_and_combine.sh ttH SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh VH SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh ggH SoverSqrtB_uncertainty5pc
./run_caliper_all_categories_and_combine.sh ttH asimov
./run_caliper_all_categories_and_combine.sh VH asimov
./run_caliper_all_categories_and_combine.sh ggH asimov
./run_caliper_all_categories_and_combine.sh ttH asimov_uncertainty5pc
./run_caliper_all_categories_and_combine.sh VH asimov_uncertainty5pc
./run_caliper_all_categories_and_combine.sh ggH asimov_uncertainty5pc

# Plot the figures of merit for each process, adding a vertical line for the analysis-level cut and save pdfs
python plot_multi_signifs.py -a 0.3 -y $year -e $ext -p ttH out_ttH_combined_SoverSqrtB.csv out_ttH_combined_SoverSqrtB_uncertainty5pc.csv out_ttH_combined_asimov.csv out_ttH_combined_asimov_uncertainty5pc.csv 
python plot_multi_signifs.py -a 0.5 -y $year -e $ext -p VH out_VH_combined_SoverSqrtB.csv out_VH_combined_SoverSqrtB_uncertainty5pc.csv out_VH_combined_asimov.csv out_VH_combined_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -a 0.7 -y $year -e $ext -p ggH out_ggH_combined_SoverSqrtB.csv out_ggH_combined_SoverSqrtB_uncertainty5pc.csv out_ggH_combined_asimov.csv out_ggH_combined_asimov_uncertainty5pc.csv

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
python plot_multi_signifs.py -y $year -e $ext -p ggH_2jM output_dfs/out_category_3.01_SoverSqrtB.csv output_dfs/out_category_3.01_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.01_asimov.csv output_dfs/out_category_3.01_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggH_3j output_dfs/out_category_3.02_SoverSqrtB.csv output_dfs/out_category_3.02_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.02_asimov.csv output_dfs/out_category_3.02_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggH_4j output_dfs/out_category_3.03_SoverSqrtB.csv output_dfs/out_category_3.03_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.03_asimov.csv output_dfs/out_category_3.03_asimov_uncertainty5pc.csv
python plot_multi_signifs.py -y $year -e $ext -p ggH_5j output_dfs/out_category_3.04_SoverSqrtB.csv output_dfs/out_category_3.04_SoverSqrtB_uncertainty5pc.csv output_dfs/out_category_3.04_asimov.csv output_dfs/out_category_3.04_asimov_uncertainty5pc.csv
