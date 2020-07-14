# Making plots for the theory chapter

The following contains instructions to reproduce plots, or the sources from where I retrieved external plots, for the theory chapter.

- [Making plots for the theory chapter](#making-plots-for-the-theory-chapter)
  - [Dark matter abundance](#dark-matter-abundance)
  - [Feynman diagrams](#feynman-diagrams)
  - [Semi-visible jets](#semi-visible-jets)

## Dark matter abundance

As referenced in the thesis, the figure comes directly from <https://arxiv.org/abs/1303.3040>. Under the **Downloads** menu, select **Other formats**, and download the source containing the figure in pdf format.

## Feynman diagrams

I created the Feynman diagrams myself using the online tool <https://feynman.aivazis.com/>. While they look nice visually, they're a bit of a pain to get right. To make sure text renders in math font, when adding the text I need to wrap it in `$` like in LaTeX. Saving the figures as pdf often doesn't work, so I had to download them in png format. Additionally, the locations of the text in the saved image don't always correspond to where they were intended to be placed. The loops for gluons would also sometimes be inverted. As such, some further formatting in Preview was required in most cases.

There might be better ways to do it with `TikZ` directly in the LaTeX document, but I haven't so far been bothered to learn.

## Semi-visible jets

Just as with the dark matter abundance plot, I pulled these figures directly from the paper's arXiv link at <https://arxiv.org/abs/1707.05326>. Again, I downloaded the source, containing all the figures in pdf format.
