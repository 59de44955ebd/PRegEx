# PRegEx
PRegEx - Regular Expression Xtra for Director (archive)

This repository is an archive of [Chris Thorman](https://gitlab.com/cthorman)'s xtra PRegEx, a free and open source Xtra that brings the power of Perl regular expressions and list handling to Lingo. It was originally hosted at [openxtras.org](https://openxtras.org/pregex/). To make compiling and testing as simple as possible, this repository contains slightly rearranged versions of the original code bases.

The xtra used to be available for both Windows and Macintosh/macOS, however since only Windows still supports running Director and Director projectors, this repository only contains projects and code for the Windows versions of PRegEx. The original sources, including the Macintosh part, can be found in folder [src-org](src-org/).

## Versions

- PRegEx [1.0](1.0/) supports Director 7 to 10.x.
- PRegEx [2.0](2.0/) supports Director 11 and later

## Compiling

Compiling both xtra versions requires Visual Studio 2017 or later. Instead of opening the Visual Studio solutions in the IDE you can also compile the release versions directly by running the appropriate `make_<vs-studio-version>.cmd` script at the root of the 1.0 resp. 2.0 folder.

PRegEx 2.0 uses pcre and iconv libs that have to be compiled with Mingw32/MSYS2. For convenience precompiled versions are provided, so there is no other dependency than Visual Studio. The code for those libs can be found in [pregex-v2.0-rev-0167-20081207.zip](src-org/pregex-v2.0-rev-0167-20081207.zip).

## Testing

After compiling the xtra you can use the Director projectors `PRegExTest.exe` in folder `test` (both inside the 1.0 and 2.0 folders) to run a test suite. The 1.0 version is a Director 10.1, the 2.0 version a Director 11.5 projector.
