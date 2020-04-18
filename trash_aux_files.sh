#!/bin/bash

# Remove all auxiliary files created by compiling thesis, including glossary and bibliography files

this_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
for file in ${this_dir}/thesismain.*; do
    if [[ $file == "${this_dir}/thesismain.tex" ]] || [[ $file == "${this_dir}/thesismain.pdf" ]]; then
	    continue
    else
	    rm $file
    fi
done
