# vatsim-manager
### *A VATSIM client install manager for Linux*
![License](https://img.shields.io/github/license/wiggleforlife/vatsim-manager?style=for-the-badge)
![Repo size](https://img.shields.io/github/repo-size/wiggleforlife/vatsim-manager?style=for-the-badge)
![Current version](https://img.shields.io/aur/version/vatsim-manager?style=for-the-badge)
![AUR maintainers](https://img.shields.io/aur/maintainer/vatsim-manager?style=for-the-badge)

Created by Cian Ormond with no endorsements by VATSIM staff members. For more info, run `vatsim-manager -L`.

### Current feature list
* Install and uninstall clients

### Planned feature list
* Configure xPilot's AppConfig with user input
* Keep track of installed clients, versions and paths
  * Disallow uninstalling absent clients
  * Confirm before reinstalling present clients
* Manage `winetricks` and `wine` settings in a custom `WINEPREFIX` for ATC clients

### Included clients
![xPilot version](https://img.shields.io/github/v/release/xpilot-project/xpilot?include_prereleases&label=xPilot&style=flat-square)  
![Swift version](https://img.shields.io/github/v/release/swift-project/pilotclient?include_prereleases&label=Swift&style=flat-square)
<!--TODO use version from VERSIONS-->

### Dependencies
* libCURL >=7.68.0
* jsoncpp >=1.7.4
* PkgConfig >=0.29.1

### Installation
* [vatsim-manager](https://aur.archlinux.org/packages/vatsim-manager) on the Arch User Repository
* Build from [source](https://github.com/wiggleforlife/vatsim-manager/tree/release)
  * `git clone https://github.com/wiggleforlife/vatsim-manager.git`
  * `git switch release`
  * `mkdir build && cd build`
  * `cmake ..`
  * `make`
  * `sudo` or `doas mv vatsim-manager /usr/bin/`

### Contribution
* Fork this repository and checkout a branch with the name of the patch
* Create a draft pull request to `wiggleforlife/vatsim-manager/master` with the intended changes
* Make your changes
* Mark the pull request as completed
