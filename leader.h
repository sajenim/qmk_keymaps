// Here we keep our leader key strings

// Gentoo
#define SEARCH   "emerge --search "
#define INSTALL  "sudo emerge --ask --verbose "
#define REMOVE   "sudo emerge --ask --verbose --depclean "
#define UPDATE   "sudo emaint --auto sync\n"
#define UPGRADE  "sudo emerge --ask --verbose --update --deep --newuse --with-bdeps=y @world\n"
#define DEPCLEAN "sudo emerge --ask --verbose --depclean\n"
