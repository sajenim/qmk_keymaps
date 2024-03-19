# QMK Keymaps

Personal keymaps for programmable keyboards. I currently use [canary](https://github.com/Apsu/Canary) layout and am working on implementing a [magic](https://github.com/Ikcelaks/keyboard_layouts/blob/main/magic_sturdy/magic_sturdy.md) key to minimize SFB and improve flow.

## Keyboards
- [Keychron Q4](https://www.keychron.com/products/keychron-q4-qmk-via-custom-mechanical-keyboard):
My gateway to QMK, 60% hotswappable with CNC machined body, i still use this for gaming and to retain qwerty muscle memory.
- [Corne Cherry](https://github.com/foostan/crkbd)
My intro to building keyboards, 3x6 column stagger with 3 thumb keys. This keyboard got me into alt layouts and 3D printing (case).

## Todo
- [Gerkin](https://www.40percent.club/2016/11/gherkin.html):
30 key keyboard by the 40% club
- [Dactyl Manuform](https://github.com/abstracthat/dactyl-manuform):
The dactyl manuform is a parameterized, split-hand, concave, columnar, ergonomic keyboard.

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
