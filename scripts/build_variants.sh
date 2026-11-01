#!/usr/bin/env bash
# Builds the 8 firmware variants of one target/layout/OS and zips them.
# Run from the root of a west workspace separate from this repo, initialized from a copy
# of its config/: `mkdir ws && cp -R <quacken>/config ws/ && cd ws && west init -l config && west update`.
# Output: $OUT_DIR/zmk_quacken_<target>_<layout>.<os>.zip
set -euo pipefail

TARGET=$1 # flex | zero
LAYOUT=$2 # qwerty | qwerty_intl | qwerty_lafayette | dvorak | azerty | ergol | erglace | bepo | bepolar
OS=$3     # pc | mac

QUACKEN_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
OUT_DIR=${OUT_DIR:-$PWD}
BUILD_DIR=${BUILD_DIR:-$(mktemp -d)}

case $TARGET in
flex) BOARD=(-b quacken_flex); SHIELD=() ;;
zero) BOARD=(-b sparkfun_pro_micro_rp2040//zmk); SHIELD=(-DSHIELD=quacken_zero) ;;
*) echo "unknown target: $TARGET" >&2; exit 1 ;;
esac

case $OS in
pc) OS_FLAGS="" ;;
mac) OS_FLAGS=";-DMACOS" ;;
*) echo "unknown OS: $OS" >&2; exit 1 ;;
esac

NAME="zmk_quacken_${TARGET}_${LAYOUT}"
STAGE=$(mktemp -d)
PRISTINE=(-p) # first build pristine, the next ones incremental

build() { # <file suffix> <hold-tap> <extra cpp flags>
	west build "${PRISTINE[@]}" -s zmk/app -d "$BUILD_DIR" "${BOARD[@]}" -S studio-rpc-usb-uart -- \
		"${SHIELD[@]}" \
		-DCONFIG_ZMK_STUDIO=y \
		-DZMK_CONFIG="$QUACKEN_DIR/config" \
		-DZMK_EXTRA_MODULES="$QUACKEN_DIR" \
		-DDTS_EXTRA_CPPFLAGS="-DKB_LAYOUT_${LAYOUT^^};-DHT_$2$OS_FLAGS$3"
	cp "$BUILD_DIR/zephyr/zmk.uf2" "$STAGE/${NAME}[${OS}]_$1.uf2"
	PRISTINE=()
}

for vim in "" _vim; do
	VIM_FLAGS=${vim:+;-DVIM_NAVIGATION}
	build "ez$vim" NONE "$VIM_FLAGS"
	build "tt$vim" THUMB_TAPS "$VIM_FLAGS"
	build "hrm$vim" HOME_ROW_MODS "$VIM_FLAGS"
	build "2tk$vim" TWO_THUMB_KEYS "$VIM_FLAGS"
done

(cd "$STAGE" && python3 -m zipfile -c "$OUT_DIR/$NAME.$OS.zip" ./*.uf2)
rm -r "$STAGE"
echo "$OUT_DIR/$NAME.$OS.zip"
