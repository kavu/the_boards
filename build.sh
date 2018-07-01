#!/usr/bin/env bash

set -e

WORK_PATH=$(pwd)
QMK_PATH="$WORK_PATH/qmk"
KEYBOARD=${1:?"You must pass Keyboard name as an argument!"}
KEYMAP=${2:?"You must pass Keymap name as an argument!"}

prepare_qmk() {
  git submodule update
}

# $1 is keyboard name
# $2 is keymap name
build() {
  docker run -it --rm \
    -e subproject="" \
    -e keymap="$2" \
    -e keyboard="$1" \
    -v "$WORK_PATH/keyboards/$1:/qmk/keyboards/$1/keymaps/$2" \
    -v "$QMK_PATH:/qmk" \
    qmk

  FILES=("$QMK_PATH/"*.hex)
  for f in "${FILES[@]}"
  do
    mv "${f}" "$WORK_PATH"
  done
}

prepare_qmk
build "$KEYBOARD" "$KEYMAP"
