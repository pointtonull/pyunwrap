#!/bin/sh
NOTEBOOK="~/documentos/carlos/apuntes/zim"
PAGE="Home:Seminario:TODO"
zim --export --template Presentation --output=docs "$NOTEBOOK" "$PAGE"
awk '
    {
        gsub("file:///usr/share/zim/", "")
    }
    /./
' docs/TODO.html > docs/TODO.tmp

mv docs/TODO.tmp docs/TODO.html
git add docs/TODO.html
git commit -m "updated TODO"
git push
