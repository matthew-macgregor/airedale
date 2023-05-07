# Airedale - Deterministic Password Generator

Airedale is a deterministic password generator written in modern C++ (C++17).
Most password managers focus on the idea of an encrypted "vault" to store
passwords, but the vault remains something that can be stolen. Airedale takes
a different approach: generating the password only when you need it. There's
nothing to store and nothing to be stolen.

**Attention: Airedale is just a toy program currently and the pseudo-random
number generation is not cryptographically secure.

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
- C++17 compiler.

Unzip the boost library to `boost_1_81_0` in the vendor directory.

Clone libsodium to the vendor folder and follow the build instructions for your
platform (using Zig is a great option). On Windows, it's also simple to build
libsodium with Visual Studio.

You can also use a system or vcpkg copy of the dependencies, but you will need to
modify the makefile accordingly.

### Password Policy

- AN00: Alpha numeric characters only.
- AN01: Alpha numeric with basic special characters.
- AN02 (default): Alpha numeric with many special characters.

### Unix/Linux Build

```sh
make
```

Known to build successfully with the following compilers:

- Apple clang version 14.0.0 (clang-1400.0.29.202) / macOS 12.6.1
- ...

### Is Airedale Cryptographically Secure?

USE AIREDALE AT YOUR OWN RISK, see [LICENSE](./LICENSE) for details.

Assume that it is not. The initial proof of concept implementation uses 
`mt19937` and a CRC32 checksum, neither of which are secure. I've required the
`--insecure` flag on the command line to call this out.

Future plans include switching to a CSPRNG to resolve this issue.

There is an argument that given the fact that passwords *should* be hashed on
the diverse destination systems that there's a low risk of leaking enough bytes
to form a sample (for Mersenne Twister that sample size is 623, should anyone
even be looking).

### TODO
- Implement a CSPRNG.
- Tests.

### Similar projects:

- [gokey](https://github.com/cloudflare/gokey)