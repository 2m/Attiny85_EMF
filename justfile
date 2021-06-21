flash:
  avrdude -p attiny85 -c usbasp -U flash:w:Attiny85_EMF.ino.hex:i -F -P usb
