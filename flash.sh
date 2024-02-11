#!/bin/bash

set -euxo pipefail

echo "Setting up permissions for /dev/ttyACM0..."
sudo chmod 777 /dev/ttyACM0

echo "Building the project..."
arduino-cli compile --fqbn arduino:samd:mkr1000 tempdisp.ino

echo "Uploading the project..."
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:samd:mkr1000 tempdisp.ino
