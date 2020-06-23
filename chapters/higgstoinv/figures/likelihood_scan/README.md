# Making likelihood scan plots

One needs ROOT installed since a ROOT macro (kindly provided by Raffaele Gerosa from [here](https://gitlab.cern.ch/cms-hcg/cadi/hig-17-023/-/tree/master/HiggsInvisibleCombination/ProfileLikelihoodScans), with the header [CMS_lumi.h](https://gitlab.cern.ch/cms-hcg/cadi/hig-17-023/-/blob/master/HiggsInvisibleCombination/CMS_lumi.h)). To make the root files with `Combine` that contain the likelihood scan information, run, e.g., the following commands on your datacards:

```bash
combineCards.py <datacards> > all.txt
text2workspace.py all.txt -m 125 --channel-masks
combine -M MultiDimFit all.txt -t -1 --expectSignal 0 --rMin 0 --rMax 5 --points 51 -m 125 --algo grid
```

**Currently, this macro only plots the expected limits. Remove the `-t -1 --expectSignal 0` in the above command to compute the scan for the observed limit. The `text2workspace` command may also need to be changed.**

Then, run the macro with

```bash
root -l -b -q makeLikelihoodScan.C\(\"<output_dir>\"\)
```

Please note that the files, processing, and aesthetics for each file (axis ranges, lumi, etc.) are hardcoded. So to add new files, a few lines will need to be added. But they can be done in the same way as those already plotted.
