# Quacken ZMK Module

## Build With GitHub (recommended)

TODO

## Build Locally (advanced users)

This requires a local ZMK clone with its Zephyr toolchain:

```bash
# clone ZMK
git clone https://github.com/zmkfirmware/zmk.git
cd zmk

# activate a venv and install west, this might take a while
uv init
uv add west
source .venv/bin/activate
west init -l app
west update

# install dependencies
uv pip instal zephyr/scripts/requirements-base.txt
```

Once the ZMK/Zephyr toolchain is set, the firmware is built as follows:

```bash
cd /path/to/zmk/app
west build -p \
  -b quacken_flex \
  -S zmk-usb-logging \
  -- -DZMK_EXTRA_MODULES=/path/to/zmk-keyboard-quacken
```

The `-S zmk-usb-logging` argument helps debugging but is not required.
