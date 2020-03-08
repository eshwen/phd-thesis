# phd-thesis

Repository containing everything related to my thesis.

## Table of contents

1. [Immediate to-do items](#immediate_to_do)
2. [Useful links](#useful_links)
3. [General questions and comments](#gen_questions)
4. [Caveats/things to note](#caveats)


## Immediate to-do items <a name="immediate_to_do"></a>

- Import into Overleaf, and sync, for simple editing


## Useful links <a name="useful_links"></a>

- Thesis guidelines from the University: http://www.bristol.ac.uk/academic-quality/pg/pgrcode/annex4/
- Common pitfalls when writing HEP theses (also [locally](helpful_docs/thesis-writing-gotchas.pdf)): https://zenodo.org/record/3228336
- CMS guidelines for authors: https://twiki.cern.ch/twiki/bin/viewauth/CMS/Internal/PubGuidelines
- For choosing fonts: https://thesiswhisperer.com/2016/03/30/what-font-should-i-choose-for-my-thesis/, http://www.indesignskills.com/inspiration/fonts-for-books/, [LaTeX Serif Font Catalogue](https://tug.org/FontCatalogue/seriffonts.html), [Google's serif font catalogue](https://fonts.google.com/?category=Serif)
- Glossary info: https://en.wikibooks.org/wiki/LaTeX/Glossary
- Previous Bristol CMS theses for reference: [Lana's](https://github.com/Lana-B/Thesis), [Alex Titterton's](https://www.dropbox.com/sh/a859z9b7jlfmum4/AAC2CjjkLGmbeSIp5H5gQbEIa?dl=0)
- The Comprehensive LaTeX Symbol List (also [locally](helpful_docs/symbols-a4.pdf)): https://www.ctan.org/pkg/comprehensive


## General questions and comments <a name="gen_questions"></a>

- What should the title of the thesis be? "Dark matter searches at CMS at sqrt(s) = 13 TeV" sounds a bit boring and generic. And should there be a subtitle?
- Can I use different colours for different links (from hyperref package), e.g., urls, references, etc.? Or should it all be black/more muted colours?


## Caveats/things to note <a name="caveats"></a>

- Currently, I use the font "Garamond Expert with New TX Math" for the main text (i.e., with the package `garamondx`). If compiling the document on Overleaf, this should already be installed. However, with TeX Live on Mac, it is not. To circumvent this, I need to follow the instructions at http://tug.org/fonts/getnonfreefonts/:

```bash
curl --remote-name https://www.tug.org/fonts/getnonfreefonts/install-getnonfreefonts
sudo texlua install-getnonfreefonts
getnonfreefonts --user -a
```

- Thesis template comes from [here](https://www.overleaf.com/latex/templates/university-of-bristol-thesis-template/kzqrfvyxxcdm). Has been built upon
- The BibTeX backend of my choice is `biblatex` with the `natbib` package. The backend can be changed to `bibtex` if required as compatibility (as of my last check) isn't an issue
- External helpful documents regarding LaTeX, thesis writing (Bristol-specific and general), etc. can be found in [helpful_docs/](helpful_docs/)
- HEP particles are typeset using the `hepnames` package. With the `italic` option, they are rendered in italics. The default is upright. If I decide to change the style, I can just edit the line that imports the package in [thesismain.tex](./thesismain.tex)
- To add a shorter caption for a figure in the List of Figures, add the shorter caption inside square brackets before the main one, i.e., `\caption[Reduced caption]{Full caption}`. Avoid a full stop at the end of a reduced caption since it looks ugly in the table of contents
- Use a tilde `~` between instead of a space between words and their references, and between numbers/quantities and their units to prevent linebreaks separating them.
