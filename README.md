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

- Do I need to abide by CMS standards and formatting (e.g., British/Americanised words, using upright letters for quarks instead of in math mode)? If so, will need to update some of the macros in [macros.tex](./macros.tex)
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
- External helpful documents regarding LaTeX, thesis writing (Bristol-specific and general), etc. can be found in [helpful_docs/](helpful_docs/)
