#!/bin/bash

if [ -z $1 ]; then
    echo "No directory specified"
    exit
fi

the_dir=$1

for reg_dir in $(ls -d ${the_dir}/*); do
    for cat_dir in $(ls -d ${reg_dir}/*); do
        mv ${cat_dir}/plot_dataset.met--sig_regions_fit--weight_nominal--project_met-yscale_log.pdf ${reg_dir}/
        mv ${reg_dir}/plot_dataset.met--sig_regions_fit--weight_nominal--project_met-yscale_log.pdf ${cat_dir}.pdf
        rm -rf ${cat_dir}/
    done
    mv ${reg_dir}/category_1.01.pdf ${reg_dir}/ttH_2Boosted.pdf
    mv ${reg_dir}/category_1.02.pdf ${reg_dir}/ttH_1t0b.pdf
    mv ${reg_dir}/category_1.03.pdf ${reg_dir}/ttH_1t1b.pdf
    mv ${reg_dir}/category_1.04.pdf ${reg_dir}/ttH_1W1b.pdf
    mv ${reg_dir}/category_1.05.pdf ${reg_dir}/ttH_1W2b.pdf
    mv ${reg_dir}/category_1.06.pdf ${reg_dir}/ttH_5j1b.pdf
    mv ${reg_dir}/category_1.07.pdf ${reg_dir}/ttH_6j1b.pdf
    mv ${reg_dir}/category_1.08.pdf ${reg_dir}/ttH_5j2b.pdf
    mv ${reg_dir}/category_1.09.pdf ${reg_dir}/ttH_6j2b.pdf
    mv ${reg_dir}/category_2.01.pdf ${reg_dir}/VH_2j0b.pdf
    mv ${reg_dir}/category_2.02.pdf ${reg_dir}/VH_2j1b.pdf
    mv ${reg_dir}/category_2.03.pdf ${reg_dir}/VH_2j2b.pdf
    mv ${reg_dir}/category_2.04.pdf ${reg_dir}/VH_1V.pdf
    mv ${reg_dir}/category_3.01.pdf ${reg_dir}/ggF_2jM.pdf
    mv ${reg_dir}/category_3.02.pdf ${reg_dir}/ggF_3j.pdf
    mv ${reg_dir}/category_3.03.pdf ${reg_dir}/ggF_4j.pdf
    mv ${reg_dir}/category_3.04.pdf ${reg_dir}/ggF_5j.pdf
    mv ${reg_dir}/category_4.01.pdf ${reg_dir}/Monojet_0b.pdf
    mv ${reg_dir}/category_4.02.pdf ${reg_dir}/Monojet_1b.pdf
done
