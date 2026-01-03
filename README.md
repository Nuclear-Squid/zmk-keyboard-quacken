# Quacken ZMK Module

A Zephyr module to build your own ZMK firmware for the Quacken.


## Build With GitHub Actions

This is the recommended method for most users.

### In a Nutshell

- [create a GitHub account](https://github.com/signup) if you don’t already have one
- fork this repository
- modify the `.keymap` file (see the [customizing ZMK](https://zmk.dev/docs/customization) documentation)
- save, commit, push

Your firmware will now be built automatically by GitHub’s CI:

- check the `Actions` tab
- wait for the latest action task to complete
- click on this task
- download the `.uf2` artifact
- [flash](#flash)

### Using github.com

TODO

### Using GitHub-Desktop

TODO

### Using `zmk-cli`

See <https://zmk.dev/docs/user-setup>.


## Build Locally

Advanced users and developers may prefer to build their firmware locally,
especially for debugging purposes.

### Setup

We need [a local ZMK clone with its Zephyr toolchain](https://zmk.dev/docs/development/local-toolchain/setup/native).

First [install all Zephyr dependencies]() — for Ubuntu it’d be:

```bash
sudo apt install --no-install-recommends \
  git cmake ninja-build gperf ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel \
  xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1
```

Then proceed with ZMK:

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
uv pip install -r zephyr/scripts/requirements-base.txt

# install Zephyr SDK (optionally in a separate folder), this takes a while
cd zephyr
west sdk install
```

### Build

Once the ZMK/Zephyr toolchain is set, the firmware is built as follows:

```bash
cd /path/to/zmk/app
west build -p \
  -b quacken_flex \
  -- -DZMK_EXTRA_MODULES=/home/user/path/to/zmk-keyboard-quacken
```

The firmware can be found in `zmk/app/build/zephyr/zmk.uf2` and is ready to be [flashed](#flash).

Note: do NOT use `~` in the `ZMK_EXTRA_MODULES` path, you’d get a `not a valid zephyr module` error.

### Debug

To enable USB logging, add `-S zmk-usb-logging`:

```bash
cd /path/to/zmk/app
west build -p \
  -b quacken_flex \
  -S zmk-usb-logging \
  -- -DZMK_EXTRA_MODULES=/home/user/path/to/zmk-keyboard-quacken
```

After flashing, you can track the USB logs for every keypress on a serial monitor (e.g. `/dev/ttyACM0` on Linux).


## Flash

See <https://zmk.dev/docs/user-setup#flash-uf2-files>.
