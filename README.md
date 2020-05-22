# phd-thesis

[![Build Status](https://travis-ci.com/eshwen/phd-thesis.svg?token=XYfJ1ZWVhoKbK3NhXnLP&branch=master)](https://travis-ci.com/eshwen/phd-thesis) [![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/eshwen/phd-thesis?include_prereleases)](https://github.com/eshwen/phd-thesis/releases/latest) ![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/eshwen/phd-thesis) ![GitHub repo size](https://img.shields.io/github/repo-size/eshwen/phd-thesis) ![GitHub top language](https://img.shields.io/github/languages/top/eshwen/phd-thesis)

[![GitHub Releases (by Asset - normal pdf)](https://img.shields.io/github/downloads/eshwen/phd-thesis/latest/Eshwen_Bhal_thesis.pdf?color=ff69b4)](https://github.com/eshwen/phd-thesis/releases/latest/download/Eshwen_Bhal_thesis.pdf) [![GitHub Releases (by Asset - draft pdf)](https://img.shields.io/github/downloads/eshwen/phd-thesis/latest/Eshwen_Bhal_thesis_draft.pdf?color=ff69b4)](https://github.com/eshwen/phd-thesis/releases/latest/download/Eshwen_Bhal_thesis_draft.pdf) [![GitHub Releases (by Asset - word count)](https://img.shields.io/github/downloads/eshwen/phd-thesis/latest/word_count.html?color=ff69b4)](https://github.com/eshwen/phd-thesis/releases/latest/download/word_count.html)

Repository containing everything related to my thesis.

## Table of Contents

- [phd-thesis](#phd-thesis)
  - [Table of Contents](#table-of-contents)
  - [General information](#general-information)
  - [Structure and features](#structure-and-features)
    - [Font](#font)
    - [Bibliography](#bibliography)
    - [Glossary](#glossary)
    - [HEP particles](#hep-particles)
    - [Word count](#word-count)
    - [Continuous integration](#continuous-integration)
  - [Compiling the document](#compiling-the-document)
    - [Normal compilation - Visual Studio Code](#normal-compilation---visual-studio-code)
    - [Draft compilation - Visual Studio Code](#draft-compilation---visual-studio-code)
    - [Normal compilation - CLI](#normal-compilation---cli)
    - [Draft compilation - CLI](#draft-compilation---cli)
    - [Normal compilation - TeXShop](#normal-compilation---texshop)
    - [Draft compilation - TeXShop](#draft-compilation---texshop)
  - [Formatting and style guidelines](#formatting-and-style-guidelines)
    - [Questions regarding formatting](#questions-regarding-formatting)
  - [Badges](#badges)
  - [Useful links](#useful-links)

[_Table of contents generated with markdown-toc_](http://ecotrust-canada.github.io/markdown-toc/)

## General information

This thesis uses the memoir document class, based off the template from [here](https://www.overleaf.com/latex/templates/university-of-bristol-thesis-template/kzqrfvyxxcdm). It has been designed to conform with the thesis guidelines from the University of Bristol [here](http://www.bristol.ac.uk/academic-quality/pg/pgrcode/annex4/). More information on the technical details can be found below. External helpful documents regarding LaTeX, thesis writing (Bristol-specific and general), etc. can be found in [helpful_docs/](helpful_docs/) or [Useful links](#useful-links).

## Structure and features

The master TeX file to compile is [thesismain.tex](./thesismain.tex). In here, all of the required packages are imported and the structure of the document is laid out. The [frontmatter/](./frontmatter/) directory contains the tex files for the preliminary pages - title, abstract, declaration, and dedication. The chapters themselves are contained within their own subdirectory in [chapters/](./chapters/). The [backmatter/](./backmatter/) directory contains the bibliography and glossary files. Then, additional user-defined macros are mostly consolidated in [macros.tex](macros.tex).

### Font

The font of my choice is **Garamond Expert with New TX Math** for the main text (i.e., with the package `garamondx` - see [here](helpful_docs/garamondx-doc.pdf)). As well as being visually appealing, it supports bold, italic, and small cap styles that other Garamond variants do not. If compiling the document on Overleaf, this should already be installed. However, it is not bundled with TeX Live due to licensing. To circumvent this, one can follow the instructions at <http://tug.org/fonts/getnonfreefonts/>:

```bash
curl --remote-name https://www.tug.org/fonts/getnonfreefonts/install-getnonfreefonts
sudo texlua install-getnonfreefonts
getnonfreefonts --user -a
```

If the above doesn't work (sometimes the `microtype` package kinda fails to map things properly), also try

```bash
sudo getnonfreefonts --sys -a
updmap-sys
```

If those two commands don't resolve it, additionally run

```bash
updmap-user
```

Note that New TX Math is _not_ used to render mathematical symbols in the thesis; the conventional AMS Math with its associated packages are instead used. While New TX Math may look a bit more natural inline to accompany Garamond text, I prefer the styling of AMS Math. Of course, if the font(s) are not to your taste, you can skip this step and replace the relevant preamble lines with whatever you desire.

### Bibliography

To process the bibliography, the backend of my choice is `biber` in conjunction with the `biblatex` package, since it's much more modern that the `bibtex`-`natbib` combination. Therefore, it should be relatively future-proof. As of the bibliography style, I am kind of attached to [SIAM](https://www.bibtex.com/s/bibliography-style-base-siam/), but that is only natively part of `bibtex`-`natbib`. So I've added a minimal, slightly-tweaked reimplementation of it. A macro to replicate `natbib`'s `\citenum` command has also been added. To remove them and use a conventional style, one only needs to remove the macros below the `\usepackage[...]{biblatex}`, and add the desired style in the `biblatex` package options.

### Glossary

A glossary and list of acronyms have been added, since HEP is full of acronyms, initialisms and nomenclature. As such, the compilation requires an additional `makeglossaries` step after the bibtex/biber stage.

If the glossary fails to render properly between compilations, delete files with extensions `.acn`, `.acr`, `.glo`, and `.gls`, then recompile.

### HEP particles

HEP particles and processes are typeset by importing the `hepnames` package (which also imports various other supporting ones). With the `italic` option, they are rendered in italics. The default is upright. To change the style, just edit the line that imports the package in [thesismain.tex](./thesismain.tex). More info. can be found in [Useful links](#useful-links). For additional symbols, quantities, units, programs, and operators commonly used in particle physics, the [`physics`](https://ctan.org/pkg/physics) package, and a copy of CMS'[`ptdr-definitions`](ptdr-definitions.sty), have also been imported.

### Word count

A word count for the thesis can be estimated by using the `TeXcount` package. It should be installable like any other (La)TeX package, but also has a website where you can manually download it: <https://app.uio.no/ifi/texcount/>. The following command can be run from the terminal (and is also run whenever my [continuous integration pipeline](#continuous-integration) is executed):

```sh
texcount -html -inc ./thesismain.tex > word_count.html
```

This spits out a `word_count.html` file that can be viewed to get a rough idea of the thesis' footprint. The website above has more options for different metrics, and how to handle certain cases.

### Continuous integration

I've written a CI pipeline utilising Travis to compile the document. This includes a normal pdf, draft-mode pdf, and a rough word count. The configuration file [.travis.yml](./.travis.yml) and Tex Live install files from [texlive/](./texlive/) are based on <https://github.com/PHPirates/travis-ci-latex-pdf>, with some modifications by myself.

If one wishes to implement a similar pipeline, those instructions should be checked first. On every push, the pipeline is run: a basic TeX Live distro is installed along with all the required packages, the commands from [Normal compilation - CLI](#normal-compilation---cli) and [Draft compilation - CLI](#draft-compilation---cli) are run to create the pdfs, and finally the word count is estimated as in [Word count](#word-count).

I can see whether the documents compile successfully or not by the pipeline passing or failing. When a new tag is created, the output files mentioned above are uploaded to the **Assets** drop down menu for the release/tag to accompany the default source code archives. The badges on the homepage of the repo also contain download links to the latest versions of each file.

Note that the configuration of this CI is fairly specific to the implementation of my thesis, and not all features may work if the repository is private. These are:

- Adding commands to the config file to install `garamondx`, and to generate glossaries
- Creating the draft pdf, which requires passing the `draft` option specifically to the `memoir` class. Different document classes may require a different implementation to create a draft version
- Adding a GitHub token in the `deploy` stage of the config file. This is done to authenticate the upload of files when a new tag is made
  - The variable `GITHUB_CI_TOKEN` is a secure variable specific to me (Eshwen), so must be generated individually for a user to make use of the feature. More information is linked about [deployment](https://docs.travis-ci.com/user/deployment) and [GitHub tokens](https://github.com/settings/tokens)
- The package `texliveonfly` is used to install the packages required for compiling the document. But it doesn't always seem to install the dependencies. So I've had to add some packages to [texlive/texlive_packages](./texlive/texlive_packages) through trial-and-error by checking the logs from failed builds. Using new packages in the document therefore carries this small risk of failing the pipeline. This can be easily debugged, however

Because of the design choices above, the Tex Live version of the pipeline was necessary. If one is using more conventional implementations, there are several alternative instructions at <https://github.com/PHPirates/travis-ci-latex-pdf> that might be easier to pursue.

## Compiling the document

**Disclaimer**: I haven't tried compiling on Overleaf, only on my local MacTeX/TeX Live distributions and in the CI pipeline. So your mileage may vary depending on your IDE/OS of choice.

The master TeX file to compile is [thesismain.tex](./thesismain.tex). There are essentially two types of document that can be produced: the normal pdf, and a draft version (e.g., for circulation to colleagues/supervisor for review). The draft version triggers the `\ifdraftdoc` block in [thesismain.tex](./thesismain.tex), and currently includes the following:

- Turns on a draft watermark with the date the pdf was made
- Adds line numbers for easier referencing to specific points
- Still renders figures properly, unlike the default (i.e., does not just render a border where the figure normally is, as is the defaut)
- Should still render hyperlinks/cross-references properly, unlike the default (but may not, depending on your TeX distribution and packages)

If switching between these two types, it's probably safest to delete the auxiliary files so the document can be freshly compiled for each case. I've written a handy little script [trash_aux_files.sh](./trash_aux_files.sh) that does this for you.

Documented below are some of the options that I've personally used to compile the document (in the order I would recommend). Note that your mileage may vary as per the disclaimer above.

### Normal compilation - Visual Studio Code

To compile in Visual Studio Code, install the **LaTeX Workshop** extension (see [documentation](https://github.com/James-Yu/LaTeX-Workshop/wiki)). The build commands are similar to TeXShop, but can be customised, e.g., to get the glossary to compile properly. Copy the snippet from [vscode_settings.json](vscode_settings.json) into your Visual Studio Code's `settings.json`. After reloading the program, just go to the TeX sidebar -> Build LaTeX project -> **Recipe: Fully compile with glossary**. If you don't have a glossary, you can compile with **Recipe: pdflatexmk**.

### Draft compilation - Visual Studio Code

If you don't mind editing [thesismain.tex](./thesismain.tex), add the `draft` option in the `\documentclass[...]{memoir}` line in [thesismain.tex](./thesismain.tex), then compile normally as above.

If you do not wish to edit [thesismain.tex](./thesismain.tex) itself, you can just run the Visual Studio Code recipe "Fully compile draft with glossary".

### Normal compilation - CLI

In the terminal, the sequence goes

```sh
pdflatex -synctex=1 -interaction=nonstopmode thesismain.tex
biber thesismain
makeglossaries thesismain
pdflatex -synctex=1 -interaction=nonstopmode thesismain.tex
pdflatex -synctex=1 -interaction=nonstopmode thesismain.tex
```

If you're using `bibtex` as a backend, just replace `biber` with `bibtex`. Also, if you're not using a glossary, you should be able to compile everything in one line with:

```sh
latexmk -synctex=1 -interaction=nonstopmode -pdf thesismain.tex
```

### Draft compilation - CLI

```sh
pdflatex -synctex=1 -interaction=nonstopmode "\PassOptionsToClass{draft}{memoir}\input{thesismain}"
biber thesismain
makeglossaries thesismain
pdflatex -synctex=1 -interaction=nonstopmode "\PassOptionsToClass{draft}{memoir}\input{thesismain}"
pdflatex -synctex=1 -interaction=nonstopmode "\PassOptionsToClass{draft}{memoir}\input{thesismain}"
```

Depending on the document class used, you may be able to change the `pdflatex` lines to `pdflatex -synctex=1 -interaction=nonstopmode -draftmode thesismain.tex`.

### Normal compilation - TeXShop

To compile in TeXShop on Mac, select **pdflatexmk** from the drop-down menu next to **Typeset**, then hit the **Typeset** button. This can misbehave when new references or glossary terms are added, possibly due to conflicts or file changes when the hyperlinks are applied. If this is the case, run [trash_aux_files.sh](./trash_aux_files.sh) to wipe all of the auxiliary files and recompile.

### Draft compilation - TeXShop

Add the `draft` option in the `\documentclass[...]{memoir}` line in [thesismain.tex](./thesismain.tex), then compile as above.

## Formatting and style guidelines

The following are some notes on formatting guidelines and style, just to remain consistent throughout the document and writing process:

- Internal links/cross-references:
  - For the text that appears in reference to items in the Table of Contents (short captions or the regular caption if a short one isn't used, chapters, sections, subsections, etc.), try to avoid referencing glossary and acronym terms. Instead, just write the normal words: `CMS` instead of `\acrshort{cms}`. Otherwise, the internal links generated can take take a user to that definition in the glossary/acronym page if they accidentally click the referenced term
  - Use abbreviations instead of the actual words when cross referencing, i.e., Chpt./Fig./Tab./Ref. instead of Chapter/Figure/Table/Reference
- Punctuation:
  - For references, cite _before_ any punctuation (such as a full stop)
  - For footnotes on the other hand, the reference should come _after_ punctuation
  - For quotation marks, open the quote with a double backtick ` `` `. Close with two single quotes `''` so that the style of the opening and closing quotation marks match
  - When to use hyphens, en-dashes and em-dashes: <https://www.chicagomanualofstyle.org/qanda/data/faq/topics/HyphensEnDashesEmDashes/faq0002.html>
- Spacing:
  - When declaring an equation environment, leave at most a single blank line between the text preceding and succeeding the equation. Otherwise, asymmetric vertical space before or after the equation may be left
  - Use a tilde `~` instead of a space between words and their references to prevent line breaks separating them. This includes both citations and cross-references
  - Between a number and its unit, use `\,` for a thin space (i.e., separation smaller than a traditional space)
- Bibliography:
  - When the bibliography is displayed and initials for the authors' first names are used, collaborations may also be rendered with initials, i.e., "C. Collaboration" instead of "CMS Collaboration". To fix this, just wrap the author name in double curly braces instead of quotes or single braces, i.e., `author = {{CMS Collaboration}}`
  - Use ISO4 abbreviations for journals instead of their full titles
  - For journals with multiple series, e.g., Physics Letters A and Physics Letters B, make sure the series is in the `journal` rather than the `volume` field
  - Remove `issn` and `isbn` fields for entries that are not books
  - Try to typeset math in a consistent way to the main text but without the use of macros, e.g., `$\sqrt{s} = \text{13\,TeV}$`, so that the `.bib` file can stand alone
  - For DOIs, remove the preceding `https://doi.org/` in `doi` fields
  - When explicitly referring to a reference with "Ref.", use `\citenum{}` instead of `\cite{}` so that the number isn't wrapped in square brackets
    - The `\citenum` command isn't available natively in `biblatex`. I've written a re-implementation just after the package is imported in [thesismain.tex](./thesismain.tex), but it can sometimes add an erroneous space after it before subsequent puncuation, e.g., `Ref. 42 )` instead of `Ref. 42)`. I've added another macro to input a small amount of negative space (`\citnumNegSpace`), so just need to watch out for that and use it if necessary
- Misc. style tips:
  - For when to write numbers in words or numerals, see <https://www.scribbr.com/academic-writing/numbers/> for help
  - To add a shorter caption for a figure/table in the List of Figures/Tables, add it inside square brackets before the main one (i.e., `\caption[Short caption]{Full caption}`)
    - Avoid a full stop at the end of a short caption since it looks ugly in the LoF/T, and omit references/citations from short captions for the same reason
  - Where appropriate, use small caps to refer to software programs. If the software is an acronym, use lowercase letters (e.g., "CMSSW" would be `\textsc{cmssw}`)
  - When introducing new, lesser-known scientific terms or definitions, I can do so in italics, e.g., `\emph{pileup}`
    - If, on the other hand, it is more of a colloquialism or something specific to the experiment (especially if it's a word that's used in everyday language) wrap it in quotation marks, e.g., ``` ``barrel''```
    - Italics are still fine to use for emphasis, but use them sparingly as it should, in most cases, be obvious from the syntax
- More formatting/stylistic guidelines can be found in <https://zenodo.org/record/3228336> ([local copy](helpful_docs/thesis-writing-gotchas.pdf))

### Questions regarding formatting

- What should the title of the thesis be? "Dark matter searches at CMS at sqrt(s) = 13 TeV" sounds a bit boring and generic. And should there be a subtitle?
- Can I use different colours for different links (from hyperref package), e.g., urls, references, etc.? Or should it all be black/more muted colours?
- For certain words used often like "reweight" and "misreconstruct", should there be hyphens ("re-weight", "mis-reconstruct", etc.)?
- The alignment of each page in the thesis is off-centre, i.e., optimised for double-sided printing and binding. When circulating a pdf copy, should I make a single-sided version where the alignment is the same for every page?

## Badges

Badges are pretty useful to highlight the important aspects of a repo to any potential forker/contributor. The build status badge is from [Travis](https://travis-ci.com/), linked to my CI pipeline. All of the others are from Shields ([webpage](https://shields.io/), [repo](https://github.com/badges/shields)). They are free to use, but obviously the badges are tied to the original fork of the repository. So to continue using them in your own fork, you can generate them yourself with these as inspiration. Note that not every badge may work if the repository is private. Server load can also mean that not every badge icon may render each time the repo is viewed. Any hyperlinks should still work though, e.g., for the downloads of latest pdfs.

**While the repository is private, the build status badge from Travis requires a security token to display properly. This can be removed once the repo is made public again**

## Useful links

- Thesis guidelines from the University: <http://www.bristol.ac.uk/academic-quality/pg/pgrcode/annex4/>
- Common pitfalls when writing HEP theses: <https://zenodo.org/record/3228336> ([local copy](helpful_docs/thesis-writing-gotchas.pdf))
- Previous Bristol CMS theses for reference: [Lana's](https://github.com/Lana-B/Thesis), [Alex Titterton's](https://www.dropbox.com/sh/a859z9b7jlfmum4/AAC2CjjkLGmbeSIp5H5gQbEIa?dl=0)
- CMS guidelines for authors: <https://twiki.cern.ch/twiki/bin/viewauth/CMS/Internal/PubGuidelines>
- CMS procedure for approvals (in case I want to show "unapproved" results): <https://twiki.cern.ch/twiki/bin/viewauth/CMS/PhysicsApprovals>
- For choosing fonts: <https://thesiswhisperer.com/2016/03/30/what-font-should-i-choose-for-my-thesis/>, <http://www.indesignskills.com/inspiration/fonts-for-books/>, [LaTeX Serif Font Catalogue](https://tug.org/FontCatalogue/seriffonts.html), [Google's serif font catalogue](https://fonts.google.com/?category=Serif)
- Glossary info: <https://en.wikibooks.org/wiki/LaTeX/Glossary>
- The Comprehensive LaTeX Symbol List: <https://www.ctan.org/pkg/comprehensive> ([local copy](helpful_docs/symbols-a4.pdf))
- Symbol list for particle names: [`hepnicenames`](http://mirrors.ctan.org/macros/latex/contrib/hepnames/hepnicenames-rm.pdf) ([local copy](helpful_docs/hepnicenames-rm.pdf)), [`heppennames`](http://mirrors.ctan.org/macros/latex/contrib/hepnames/heppennames-rm.pdf) ([local copy](helpful_docs/heppennames-rm.pdf)), [`ptdr-definitions`](ptdr-definitions.sty) (additional macros for CMS publications)
- Generating a table of contents automatically for a GitHub README: <https://ecotrust-canada.github.io/markdown-toc/>
- Previewing a GitHub README: <https://jbt.github.io/markdown-editor/>
