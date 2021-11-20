#!/bin/bash

# Check dcmtk lib installed via apt

PKGS=(
  "libdcmtk-dev"  # to read images with dcmtk
  "libeigen3-dev" # To make operations with fuzzy-c-means
)

echo "Checking dependencies..."
for pkg in "${PKGS[@]}"; do
  PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $pkg|grep "install ok installed")
  if [ "" = "$PKG_OK" ]; then
    echo "❌ $pkg is not installed. Setting up $pkg."
    sudo apt-get --yes install $pkg
  else
    echo "✅ $pkg is already installed."
  fi
done
