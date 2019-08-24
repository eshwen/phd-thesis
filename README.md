# phd-thesis


Repository containing everything related to my thesis.


## Immediate to-do

- Add my thesis outline from my third year report into document and make chapter directories/tex files accordingly
- Take things from lab book that should be useful for thesis and add in
- Get higher res Bristol crest for title page and replace current one (make sure sizing is correct)
- Once initial template is sorted and stable, create another release. Then import into Overleaf for simple editing


## Useful links

- Thesis guidelines from the University: http://www.bristol.ac.uk/academic-quality/pg/pgrcode/annex4/
- Common pitfalls when writing HEP theses: https://www.scribd.com/document/401311835/Common-Gotchas-in-HEP-Thesis-Writing
- CMS guidelines for authors: https://twiki.cern.ch/twiki/bin/viewauth/CMS/Internal/PubGuidelines
- For choosing fonts: https://thesiswhisperer.com/2016/03/30/what-font-should-i-choose-for-my-thesis/, http://www.indesignskills.com/inspiration/fonts-for-books/, [LaTeX Serif Font Catalogue](https://tug.org/FontCatalogue/seriffonts.html), [Google's serif font catalogue](https://fonts.google.com/?category=Serif)
- Glossary info: https://en.wikibooks.org/wiki/LaTeX/Glossary
- Previous Bristol CMS theses for reference: [Lana's](https://github.com/Lana-B/Thesis), [Alex Titterton's](https://www.dropbox.com/sh/a859z9b7jlfmum4/AAC2CjjkLGmbeSIp5H5gQbEIa?dl=0)


## Questions/comments

- Do I need to abide by CMS standards and formatting (e.g., British/Americanised words, using upright letters for quarks instead of in math mode)? If so, will need to include the ptdr-definitions.sty file from lab book folder
- What should the title of the thesis be? "Dark matter searches at CMS at sqrt(s) = 13 TeV" sounds a bit boring and generic. And should there be a subtitle?
- Can I use different colours for links (from hyperref package), e.g., urls, in Table of Contents, etc.? Or should it all be black/more muted colours?
- Use hyperlinking in this README for the different sections as I add to it


## Caveats/things to note

- Currently, I use the font "Garamond Expert with New TX Math" for the main text (i.e., with the package `garamondx`). If compiling the document on Overleaf, this should already be installed. However, with TeX Live on Mac, it is not. To circumvent this, I need to follow the instructions at http://tug.org/fonts/getnonfreefonts/:

```bash
curl --remote-name https://www.tug.org/fonts/getnonfreefonts/install-getnonfreefonts
sudo texlua install-getnonfreefonts
getnonfreefonts --user -a
```
