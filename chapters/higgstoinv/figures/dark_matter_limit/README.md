# Making Higgs portal dark matter summary plots

One needs ROOT installed since a ROOT macro (kindly provided by Raffaele Gerosa from [here](https://gitlab.cern.ch/cms-hcg/cadi/hig-17-023/-/tree/master/HiggsInvisibleCombination%2FHiggsPortalDM), with the header [CMS_lumi.h](https://gitlab.cern.ch/cms-hcg/cadi/hig-17-023/-/blob/master/HiggsInvisibleCombination/CMS_lumi.h)). Then, just run it with

```bash
root -l -b -q makeHiggsPortalPlot.C\(<limitvalue>,\"<output_dir>\"\)
```

where `limitvalue` is a decimal, not percentage. The backslashes are required to escape the brackets and allow argument parsing.

The direct detection limits are old (since the values are from around the time HIG-17-023 was published), so will need to be updated:

- CDMSlite values from <https://arxiv.org/abs/1808.09098> (latest results). Provided by member of the CDMS Collaboration
- LUX values from <https://arxiv.org/abs/1608.07648> (latest results)
- XENON-1T values from <https://arxiv.org/abs/1805.12562> (latest results)
- XENON-S2 values from <https://arxiv.org/abs/1907.11485> (latest results). CSV file from <https://arxiv.org/src/1907.11485v2/anc/5a_results_si_nr.csv>
- CRESST-III values from <https://arxiv.org/abs/1904.00498> (latest results). CSV file from <https://arxiv.org/src/1905.07335v3/anc/C3P1_DetA_DataRelease_SI.xy>
- PandaX-II values from <https://arxiv.org/abs/1708.06917> (latest results)
