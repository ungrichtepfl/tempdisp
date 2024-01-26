#!/bin/bash

set -euxo pipefail

# Build the project
arduino-cli compile --fqbn arduino:samd:mkr1000 tempdisp.ino

# Flash the project
sudo chmod 777 /dev/ttyACM0 && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:samd:mkr1000 tempdisp.ino
