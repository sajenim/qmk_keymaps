/* Copyright 2022 @ sajenim (https://github.com/sajenim)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Emerge */
#define SEARCH    "sudo emerge --search "
#define INSTALL   "sudo emerge --ask "
#define REMOVE    "sudo emerge --ask --deselect "
#define UPDATE    "sudo emerge --sync"
#define DEPCLEAN  "sudo emerge --ask --depclean"
#define UPGRADE   "sudo emerge --ask --update --deep --newuse --with-bdeps=y @world"

