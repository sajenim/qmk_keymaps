# QMK Keymaps

Personal keymaps for programmable keyboards.

## Keyboards
- [Keychron Q4](https://www.keychron.com/products/keychron-q4-qmk-via-custom-mechanical-keyboard)
- [Corne Cherry](https://github.com/foostan/crkbd)

## In Progress
- [Void30](https://github.com/victorlucachi/void30)
- [Dactyl Manuform](https://github.com/abstracthat/dactyl-manuform)

## Keymaps

## Pictures

## Install
Follow the [getting started](https://docs.qmk.fm/#/newbs_getting_started) docs to install [QMK Firmware](https://docs.qmk.fm/#/)

    # Clone the keymaps
    git clone https://github.com/sajenim/qmk_keymaps.git
    
    # Merge our keymaps into qmk_firmware
    rsync --recursive qmk_keymaps/keyboards/ qmk_firmware/keyboards/

    # Compile the firmware
    qmk compile -kb crkbd -km sajenim
