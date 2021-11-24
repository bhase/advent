# What is it?

Electronic calendar similar to a word clock

## Microcontoller
It is an ESP32 board
TODO describe HW setup and SW setup
### Software
* get esp-idf (github.com:espressif/esp-idf.git)
* before usage call 'export.sh' in the installation directory

## Doing
Time based on sntp with ESP32, controlling LEDs with MAX7221 (maybe shift
registers)

Body and word plate laser cut

## Laser cut fonts
created the font string with [stencilfy](https://stencilfy.herokuapp.com/)
based on the article in [medium.com](https://scientiffic.medium.com/stencilfy-creating-laser-cutter-friendly-type-b7b8ef1831ec)

## Text
16 columns, 12 lines (3 IC total)
For text see vimwiki entry Adventkalender, but can be found also in the
inkscape svgs.

## Boxes and Divider
created the basic box and divider with
[boxes.py UniversalBox](https://festi.info/boxes.py/UniversalBox?language=en)
[boxes.py TrayDivider](https://festi.info/boxes.py/TrayInsert?language=en)

# Improvements
- randomize which text is shown
- adjustable display brightness
