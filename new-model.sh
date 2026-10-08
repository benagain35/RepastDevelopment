#!/usr/bin/env bash
# usage: ./new-model.sh NAME
set -e
name="$1"
[ -z "$name" ] && { echo "usage: ./new-model.sh NAME"; exit 1; }
[ -e "$name" ] && { echo "$name already exists"; exit 1; }
mkdir -p "$name/src" "$name/include" "$name/props"
printf 'MODEL = %s\ninclude ../Makefile.common\n' "$name" > "$name/Makefile"
printf 'objects/\nbin/\n' > "$name/.gitignore"
echo "created $name/ : .cpp/.h go in src/, config.props and model.props in props/"
