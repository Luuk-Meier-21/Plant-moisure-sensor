#!/bin/bas

case $1 in

  "arduino")
    cd ./plant-saver-arduino
    arduino-cli compile --fqbn arduino:avr:uno
    arduino-cli compile --fqbn arduino:avr:uno
    ;;

  "esp")
    STATEMENTS
    ;;
  *)
    echo "Please provide a target."
    ;;
esac