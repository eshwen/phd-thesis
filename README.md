# phd-thesis

Repository containing everything related to my thesis.

## Table of Contents

- [phd-thesis](#phd-thesis)
  - [Immediate to-do items](#immediate-to-do-items)
  - [Useful links](#useful-links)
  - [General questions and comments](#general-questions-and-comments)
  - [Caveats and things to note](#caveats-and-things-to-note)
  - [Formatting guidelines](#formatting-and-style-guidelines)
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

## Caveats and things to note

- Currently, I use the font "Garamond Expert with New TX Math" for the main text (i.e., with the package `garamondx`). If compiling the document on Overleaf, this should already be installed. However, with TeX Live on Mac, it is not. To circumvent this, I need to follow the instructions at <http://tug.org/fonts/getnonfreefonts/:>

```bash
curl --remote-name https://www.tug.org/fonts/getnonfreefonts/install-getnonfreefonts
sudo texlua install-getnonfreefonts
getnonfreefonts --user -a
# If the above doesn't work (sometimes the microtype package kinda fails to map things properly), try
sudo getnonfreefonts --sys -a
updmap-sys
# If those two don't resolve it, additionally run
updmap-user
```

- Thesis template comes from [here](https://www.overleaf.com/latex/templates/university-of-bristol-thesis-template/kzqrfvyxxcdm). Has been built upon
- The BibTeX backend of my choice is `biber` with the `biblatex` package since it's much more modern that the `bibtex`/`natbib` combination
- External helpful documents regarding LaTeX, thesis writing (Bristol-specific and general), etc. can be found in [helpful_docs/](helpful_docs/)
- HEP particles are typeset using the `hepnames` package. With the `italic` option, they are rendered in italics. The default is upright. If I decide to change the style, I can just edit the line that imports the package in [thesismain.tex](./thesismain.tex)
- Compiling [thesismain.tex](./thesismain.tex) in TeXShop can misbehave when new references or glossary terms are added, possibly due to conflicts or file changes when the hyperlinks are applied. If this is the case, run [trash_aux_files.sh](./trash_aux_files.sh) to wipe all of the auxiliary files and recompile
- Compiling [thesismain.tex](./thesismain.tex) in Visual Studio Code needs some edits to the LaTeX Workshop extension to get the glossary to compile properly. I can copy the snippet from [vscode_settings.json](vscode_settings.json) into my Visual Studio Code `settings.json` to fix it

## Formatting and style guidelines

The following are some notes on formatting guidelines and style, just to remain consistent throughout the document and writing process:

- To add a shorter caption for a figure/table in the List of Figures/Tables, add it inside square brackets before the main one, i.e., `\caption[Short caption]{Full caption}`
  - Avoid a full stop at the end of a short caption since it looks ugly in the table of contents, and omit references/citations from short captions for the same reason
- For the text that appears in reference to items in the thesis' Table of Contents (short captions or the regular caption if a short one isn't used, chapters, sections, subsections, etc.), try to avoid referencing glossary and acronym terms (instead just write the normal words---`CMS` instead of `\acrshort{cms}`). Otherwise, the internal links generated can take take a user to that definition in the glossary/acronym page if they accidentally click the referenced term
- Use a tilde `~` instead of a space between words and their references to prevent line breaks separating them
  - Between a number and its unit, I should use `\,` for a thin space (i.e., separation smaller than a traditional space)
- For when to write numbers in words or numerals, see <https://www.scribbr.com/academic-writing/numbers/> for help
- For references, cite _before_ any punctuation (such as a full stop)
  - For footnotes on the other hand, the reference should come _after_ punctuation
- When explicitly referring to a reference with "Ref.", use `\citenum{}` instead of `\cite{}` so that the number isn't wrapped in square brackets
- When declaring an equation environment, leave at most a single blank line between the text preceding and succeeding the equation. Otherwise, asymmetric vertical space before or after the equation may be left
- For quotation marks, open the quote with a double backtick. Close with two single quotes so that the style of the opening and closing quotation marks match
- When to use hyphens, en-dashes and em-dashes: <https://www.chicagomanualofstyle.org/qanda/data/faq/topics/HyphensEnDashesEmDashes/faq0002.html>
- Where appropriate, use small caps to refer to software programs. If the software is an acronym, use lowercase letters (e.g., "CMSSW" would be `\textsc{cmssw}`)
- When introducing new, lesser-known scientific terms or definitions, I can do so in italics, e.g., `\emph{pileup}`
  - If, on the other hand, it is more of a colloquialism or something specific to the experiment (especially if it's a word that's used in everyday language) wrap it in quotation marks, e.g., ```barrel''`
  - Italics are still to use for emphasis, but use them sparingly as it should, in most cases, be obvious from the syntax
- More formatting/stylistic guildelines can be found in <https://zenodo.org/record/3228336> (also [locally](helpful_docs/thesis-writing-gotchas.pdf))

## Draft versions of the pdf

Before sending a draft version of the pdf, e.g., to my supervisor, compile with the following:

- Add "draft" in the `\documentclass` line with the other options. This turns on a draft watermark with the date the pdf was made, and adds line numbers for easier referencing to specific points
- Use footnotes to mark any questions/concerns, etc. instead of comments in the tex file. Ideally, these will be in a different colour to the normal footnotes in the document. But I've been having problems coverting both the label and the text to the same colour
