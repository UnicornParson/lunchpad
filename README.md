# lunchpad
arduino based lunchpad

##desktop app
### requirements
python packages
 - pyautogui
 - pyserial

#tips and tricks
## ports list
python3.8 -c "import serial.tools.list_ports;print(list(map(str, serial.tools.list_ports.comports())))"
