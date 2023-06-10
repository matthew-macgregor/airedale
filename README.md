# Airedale - Deterministic Password Generator

Airedale is a deterministic password generator written in modern C++ (C++17).
Most password managers focus on the idea of an encrypted "vault" to store
passwords, but the vault remains something that can be stolen. Airedale takes
a different approach: generating the password only when you need it. There's
nothing to store and nothing to be stolen.

**Attention: Airedale is a personal project. I make no guarantees about its
suitability for any purpose or about its stability.**

### License

Airedale is licensed under the GPLv3.

    This program is free software: you can redistribute it and/or modify it 
    under the terms of the GNU General Public License as published by the Free 
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
    more details.

    You should have received a copy of the GNU General Public License along 
    with this program (see LICENSE). If not, see <https://www.gnu.org/licenses/>.

### Building

- [Boost 1.81.0](https://www.boost.org/users/history/version_1_81_0.html)
- [Libsodium 1.0.18](https://github.com/jedisct1/libsodium/releases/tag/1.0.18-RELEASE)
- C++20 compiler
- [vcpkg](https://vcpkg.io/en/)


#### CMake + vcpkg

Use vcpkg to install dependencies:

```sh
# Windows
vcpkg install --triplet x64-windows-static boost-crc boost-random boost-algorithm libsodium

# macOS 
vcpkg install --triplet x64-osx boost-crc boost-random boost-algorithm libsodium

# FreeBSD
vcpkg install --triplet x64-freebsd boost-crc boost-random boost-algorithm libsodium
```

Set `VCPKG_ROOT` environment variable.

```sh
# Be sure to change the path to the directory where you cloned vcpkg.

# bash
export VCPKG_ROOT="$HOME/Code/repos/vcpkg"

# tcsh (BSD)
setenv VCPKG_ROOT "$HOME/Code/repos/vcpkg"
```

Build using CMake:

CMake presets that are defined:
- `windows-debug`
- `osx-debug`
- `freebsd-debug`

```sh
cmake -S . -B build --preset {preset}
cmake --build build
```

### Password Policy

- AN00: Alpha numeric characters only.
- AN01: Alpha numeric with basic special characters.
- AN02 (default): Alpha numeric with many special characters.

### Unix/Linux Build

```sh
make -f makefile.make
```

### MSVC Build

```ps1
nmake /f makefile.nmake
```

Known to build successfully with the following compilers:

- Apple clang version 14.0.0 (clang-1400.0.29.202) / macOS 12.6.1
- gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04) / WSL Ubuntu 22.04
- MSVC Microsoft (R) C/C++ Optimizing Compiler Version 19.35.32217.1 for x64 / Windows 11

### Is Airedale Cryptographically Secure?

USE AIREDALE AT YOUR OWN RISK, see [LICENSE](./LICENSE) for details. This command line utility
is not intended for use as a password generator for production systems. This is a personal project
and the code base has not been audited for security.

The default for password generation uses BLAKE2b from the libsodium cryptographic library.

MersienneTwister `mt19937` is provided as a baseline implementation that is easily portable 
to just about any language or platform. The mt implementation is behind a `--insecure|-i` flag.

> Are you a paleontologist? I desperately need a paleontologist.

If cryptography is your strong suit and you're interested in making the project more useful, let
me know.

### TODO
- Tests.
- Color console output.

### Similar projects:

- [gokey](https://github.com/cloudflare/gokey)
