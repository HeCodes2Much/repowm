<div align="center">
    <h1>repowm</h1>
    <p>Window manager for linux</p>
</div>

# Initial look

<img src="https://github.com/The-Repo-Club/repowm/blob/screenshots/screenshots/initial_look.png">
<img src="https://github.com/The-Repo-Club/repowm/blob/screenshots/screenshots/col_layout.png">

<img src="https://github.com/The-Repo-Club/repowm/blob/screenshots/screenshots/occ_act_tags.png">
(empty workspaces have their color greyed out)

- NOTE: This is vanilla dwm bar (status2d patch for setting colors) not dwmblocks or polybar.
  <img src="https://github.com/The-Repo-Club/repowm/blob/screenshots/screenshots/repowm.png">

# Requirements

- imlib2
- xsetroot package (status2d uses this to add colors on dwmbar)
- FiraCode Nerd Font or any nerd font but dont forget to set it in config.def.h
- Material Design Icons Font - [link](https://github.com/Templarian/MaterialDesign-Font/blob/master/MaterialDesignIconsDesktop.ttf)
- Make sure to setup your terminal's theme accordingly do repowm's theme such as nord, onedark etc...

## Other requirements

- picom
- feh
- acpi
- repomenu

# Installation

**For Arch** it can be founded in [RepoClub Repository](https://arch.therepo.club/) \
**For Gentoo** refer to the [XDream's Repository](https://github.com/XDream8/dreamsrepo) \
**Recommended Method**

```sh
$ git clone https://github.com/The-Repo-Club/repowm.git
$ cd repowm
$ sudo make install
```

[Download latest release](https://github.com/The-Repo-Club/repowm/releases/)

# Features

This is just a quick list of some features. For a full list and explanation,
please refer to the documentation.

- General

  - hybrid-wm: tiling and floating mode
  - Keyboard and Mouse based workflows
  - start menu (remomenu)
  - full multi monitor support
  - status2d color status
  - tag system
  - repobar script
  - indicators
  - shutdown menu
  - system tray
  - window gaps
  - restart function

- Patches

  - barpadding
  - bottomstack
  - cfacts
  - dragmfact
  - dragcfact
  - fibonacii
  - gaplessgrid
  - horizgrid
  - movestack
  - vanity gaps
  - colorful tags
  - statuspadding
  - status2d
  - underline tags
  - notitle
  - preserveonrestart

# Change themes

- Bar : config.def.h (line 42)

# is this dwm?

repowm is a fork of [DWM](https://dwm.suckless.org) and can be used as a drop in replacement, maintaining all dmenu behavior and making all extra features optional
