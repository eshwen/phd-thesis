# phd-thesis

Repository containing everything related to my thesis.

## Table of Contents

- [phd-thesis](#phd-thesis)
  - [Immediate to-do items](#immediate-to-do-items)
  - [Useful links](#useful-links)
  - [General questions and comments](#general-questions-and-comments)
  - [Caveats/things to note](#caveats-things-to-note)
  - [Formatting guidelines](#formatting-guidelines)
  - [Draft versions of the pdf](#draft-versions-of-the-pdf)

## Immediate to-do items

- Import into Overleaf, and sync, for simple editing

## Useful links

- Thesis guidelines from the University: <http://www.bristol.ac.uk/academic-quality/pg/pgrcode/annex4/>
- Common pitfalls when writing HEP theses (also [locally](helpful_docs/thesis-writing-gotchas.pdf)): <https://zenodo.org/record/3228336>
- CMS guidelines for authors: <https://twiki.cern.ch/twiki/bin/viewauth/CMS/Internal/PubGuidelines>
- CMS procedure for approvals (in case I want to show "unapproved" results): <https://twiki.cern.ch/twiki/bin/viewauth/CMS/PhysicsApprovals>
- For choosing fonts: <https://thesiswhisperer.com/2016/03/30/what-font-should-i-choose-for-my-thesis/>, <http://www.indesignskills.com/inspiration/fonts-for-books/>, [LaTeX Serif Font Catalogue](https://tug.org/FontCatalogue/seriffonts.html), [Google's serif font catalogue](https://fonts.google.com/?category=Serif)
- Glossary info: <https://en.wikibooks.org/wiki/LaTeX/Glossary>
- Previous Bristol CMS theses for reference: [Lana's](https://github.com/Lana-B/Thesis), [Alex Titterton's](https://www.dropbox.com/sh/a859z9b7jlfmum4/AAC2CjjkLGmbeSIp5H5gQbEIa?dl=0)
- The Comprehensive LaTeX Symbol List (also [locally](helpful_docs/symbols-a4.pdf)): <https://www.ctan.org/pkg/comprehensive>
- Symbol list for particle names (also locally - [`hepnicenames`](helpful_docs/hepnicenames-rm.pdf), [`heppennames`](helpful_docs/heppennames-rm.pdf), [`ptdr-definitions` (additional macros for CMS publications)](ptdr-definitions.sty)): [`hepnicenames`](http://mirrors.ctan.org/macros/latex/contrib/hepnames/hepnicenames-rm.pdf), [`heppennames`](http://mirrors.ctan.org/macros/latex/contrib/hepnames/heppennames-rm.pdf)

## General questions and comments

- What should the title of the thesis be? "Dark matter searches at CMS at sqrt(s) = 13 TeV" sounds a bit boring and generic. And should there be a subtitle?
- Can I use different colours for different links (from hyperref package), e.g., urls, references, etc.? Or should it all be black/more muted colours?
- I'm not sure of the best way to format the journal component of a bibliography entry, i.e., whether the entire journal name should be given or just the ISO4 abbreviation
- Should I use abbreviations or the actual words when referencing items within the thesis, i.e., "Chpt." or "Chapter", "Fig." or "Figure", "Tab." or "Table"?

## Caveats/things to note

- Currently, I use the font "Garamond Expert with New TX Math" for the main text (i.e., with the package `garamondx`). If compiling the document on Overleaf, this should already be installed. However, with TeX Live on Mac, it is not. To circumvent this, I need to follow the instructions at <http://tug.org/fonts/getnonfreefonts/:>

```bash
curl --remote-name https://www.tug.org/fonts/getnonfreefonts/install-getnonfreefonts
sudo texlua install-getnonfreefonts
getnonfreefonts --user -a
```

- Thesis template comes from [here](https://www.overleaf.com/latex/templates/university-of-bristol-thesis-template/kzqrfvyxxcdm). Has been built upon
- The BibTeX backend of my choice is `biber` with the `biblatex` package since it's much more modern that the `bibtex`/`natbib` combination
- External helpful documents regarding LaTeX, thesis writing (Bristol-specific and general), etc. can be found in [helpful_docs/](helpful_docs/)
- HEP particles are typeset using the `hepnames` package. With the `italic` option, they are rendered in italics. The default is upright. If I decide to change the style, I can just edit the line that imports the package in [thesismain.tex](./thesismain.tex)
- Compiling [thesismain.tex](./thesismain.tex) in TeXShop can misbehave when new references or glossary terms are added, possibly due to conflicts or file changes when the hyperlinks are applied. If this is the case, run [trash_aux_files.sh](./trash_aux_files.sh) to wipe all of the auxiliary files and recompile

## Formatting guidelines

The following are some notes on formatting guidelines, just to remain consistent throughout the document and writing process:

- To add a shorter caption for a figure in the List of Figures, add the shorter caption inside square brackets before the main one, i.e., `\caption[Reduced caption]{Full caption}`. Avoid a full stop at the end of a reduced caption since it looks ugly in the table of contents, and omit references/citations from short captions
- Use a tilde `~` instead of a space between words and their references, and between numbers/quantities and their units to prevent linebreaks separating them. Between a number and its unit, I can also use `\,` for a thin space (i.e., separation smaller than a traditional space)
- In the bibliography, the current sorting method I use is by author's last name. As such, in entries where the author is repeated (e.g., "CMS Collaboration"), the author's name will be replaced by a long dash. If undesired, it should be possible to change it either with an option/different sorting method, or maybe a different backend
- For when to write numbers in words or numerals, see <https://www.scribbr.com/academic-writing/numbers/> for help
- For references at the end of a sentence, cite _before_ the full stop
- When explicitly referring to a reference with "Ref.", use `\citenum{}` instead of `\cite{}` so that the number isn't wrapped in square brackets
- For quotation marks, open the quote with a double backtick. Close with two single quotes so that the style of the opening and closing quotation marks match
- When to use hyphens, en-dashes and em-dashes: <https://www.chicagomanualofstyle.org/qanda/data/faq/topics/HyphensEnDashesEmDashes/faq0002.html>
- More formatting/stylistic guildelines can be found in <https://zenodo.org/record/3228336> (also [locally](helpful_docs/thesis-writing-gotchas.pdf))

## Draft versions of the pdf

When sending a draft version of the pdf, e.g., to my supervisor, add "draft" in the `\documentclass` line with the other options. This turns on a draft watermark with the date the pdf was made, and adds line numbers for easier referencing to specific points. Also, use footnotes to mark any questions/concerns, etc. instead of comments in the tex file.
