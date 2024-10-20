#!/usr/bin/env sh

OLD_WD=$PWD
# Move us out of src/ or subfolders if we're in there
if [[ $PWD == */src* ]]; then
  while [[ $PWD == */src* ]]; do
    cd ..
  done
fi

cargo build --release --all-features --target thumbv7em-none-eabihf &&
rust-objcopy -O ihex target/thumbv7em-none-eabihf/release/rusti rusti.hex &&
teensy_loader_cli --mcu=TEENSY41 -w rusti.hex
