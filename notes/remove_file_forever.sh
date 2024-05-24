#!/bin/sh


#will completely remove the file's contents from the index. This means that on commit the file will be removed from the HEAD commit. (If the file was only added to the index and not yet tracked this is a "no-op".)
git rm --cached ${1}

#resets the contents of the file in the index to be the same as the head commit. This means that on commit no changes will be committed to the file. This operation is not valid if there is no tracked version of the file in the HEAD commit.
#git reset -- ${1}


#delete from all branches, warning, this cause remote problems
#git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch "${1}"' --prune-empty --tag-name-filter cat -- --all
