# Making Higgs portal dark matter summary plots

One needs ROOT installed since a ROOT macro (kindly provided by Raffaele Gerosa from [here](https://gitlab.cern.ch/cms-hcg/cadi/hig-17-023/-/tree/master/HiggsInvisibleCombination%2FHiggsPortalDM), with the header [CMS_lumi.h](https://gitlab.cern.ch/cms-hcg/cadi/hig-17-023/-/blob/master/HiggsInvisibleCombination/CMS_lumi.h)). Then, just run it with

```bash
root -l -b -q makeHiggsPortalPlot.C\(<limitvalue>,\"<output_dir>\"\)
```

where `limitvalue` is a decimal, not percentage. The backslashes are required to escape the brackets and allow argument parsing.

The direct detection limits are old (since the values are from around the time HIG-17-023 was published), so will need to be updated:

- CDMSlite values from <https://arxiv.org/abs/1509.02448> (Run 2?). Update to <https://arxiv.org/abs/1808.09098> (Run 3).
