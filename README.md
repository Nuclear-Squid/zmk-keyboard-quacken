# Quacken ZMK Module

A Zephyr module to build your own ZMK firmware for the Quacken.


## Build With GitHub Actions

This is the recommended method for most users.

### In a Nutshell

- [create a GitHub account](https://github.com/signup) if you don’t already have one
- fork this repository
- modify the `keymaps/quacken.keymap` file (see the [customizing ZMK](https://zmk.dev/docs/customization) documentation)
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

When done, symlink the ZMK folder in the local `zmk-keyboard-quacken` folder,
so that the build script can use this ZMK/Zephyr setup:

```bash
cd /path/to/zmk-keyboard-quacken
ln -s /path/to/zmk .
```

### Build

Once the ZMK/Zephyr toolchain is set, the Quacken firmware is built as follows:

```bash
./build {flex,zero} [optional_C++_flags]
```

- `flex` or `zero` relates to the Quacken variant in use
- `optional_C++_flags` enables keymap options defined in `build.yml`

Examples:

```bash
# build the default Quacken Zero firmware
./build zero

# build the default Quacken Flex firmware
./build flex

# build a Quacken Flex firmware with homerow-mods
./build flex -DDUAL_KEYS=HOME_ROW_MODS
```

The firmware (`zmk_quacken_{flex,zero}.uf2`) can be found in the current directory and is ready to be [flashed](#flash).

### Debug

To enable USB logging, uncomment the `USB_LOGGING` line in the `build` script.

After flashing, you can track the USB logs for every keypress on a serial monitor (e.g. `/dev/ttyACM0` on Linux).


## Flash

See <https://zmk.dev/docs/user-setup#flash-uf2-files>.
