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

  mv "$QMK_PATH/$1_$2.hex" "$WORK_PATH"
}

prepare_qmk
build "$KEYBOARD" "$KEYMAP"
