# Libespm

A free software library for reading and writing .esp and .esm plugin files.

## WHAT THIS IS?

A fork of `libespm` by <a href="https://github.com/WrinklyNinja/libespm">WrinklyNinja</a>, based on most recent <a href="https://github.com/WrinklyNinja/libespm/commit/fe6b7b8540d79b223646dbe183f6f89af6475aa0">commit</a> (2014-Dec-28).

I have <b>rolled back some unnecessary changes made by author which prevented `libespm` from being compiled on VS2010</b>, therefore also prevented from using Windows XP as developer platform (VS2012 requires Windows 7 SP1)..

Original `libespm` was changed to use C++ 11 <a href="https://msdn.microsoft.com/en-ca/library/vstudio/hh567368.aspx">`Range-Based For Loop`</a> in multiple places during 2 commits (2014-Jun-21):
* <a href="https://github.com/WrinklyNinja/libespm/commit/192ec639cde0367e06c6a26a38b79bd27e50fc71">First set of C++11 changes</a>
* <a href="https://github.com/WrinklyNinja/libespm/commit/811499369dcdb49eac0250b1fa6f30aee62d024a">Another batch of C++11 changes.</a>.

Those changes were just for convenience placing artifical limit on usage..

So this forked version <b>can now be used in VS2010 - using Windows XP development platform</b>.<br>
Though it (likelly) will not compile in older versions like VS2008, due other C++ 11 changes..

## Introduction

Libespm can currently read data from plugins for the following games:

* TES III: Morrowind
* TES IV: Oblivion
* TES V: Skyrim
* Fallout 3
* Fallout: New Vegas

Libespm was first created by deaths_soul (AKA MCP), then forked by myself (WrinklyNinja) and pretty much rewritten, though the structure of the library has only changed a little.

Libespm requires the following Boost libraries:

* Filesystem (built)
* Iostreams
* String Algorithms
* Lexical Cast

At the moment the libespm itself is header-only, so just make sure that those libraries are accessible in your project build settings.

Support for compressed record fields requires zlib to be accessible in your project build settings, and the `USING_ZLIB` preprocessor definition.

## Design Notes

The general idea is of a generic backend that's used to parse (and write) the files, with more specialised structures to interpret the data. Everything gets namespaced according to its specificity, so:

* Generic stuff is found at `espm`.
* Game stuff is found at `espm::tes3`, `espm::tes4`, `espm::tes5`, `espm::fo3`, `espm::fonv` for Morrowind, Oblivion, Skyrim, Fallout 3 and Fallout: New Vegas respectively.
* Specific record and field structures would be found in sub-namespaces of each game's namespace, so Skyrim's TES4 record interface would be the structure `espm::tes5::TES4::Record` while the record's ONAM interface would be the structure `espm::tes5::TES4::ONAM`.

The reasoning is that different records contain different fields for different purposes, and they also contain fields with matching names but different data (eg. for Skyrim, `ONAM` in `TES4` is not the same as `ONAM` in `LCSR`). Records also differ between games, eg. the `TES4` record has no `ONAM` field in Oblivion, but does in Skyrim. Field specialisations therefore need to be defined per-record, and records need to be defined per-game. Hence the namespace structure used.

Of course, although there are quite a lot of differences between games and records, there are also quite a lot of similarities, so to prevent code duplication stuff gets imported across namespaces. For example, the `MAST` fields for the `TES4` record in Oblivion, Fallout 3, Fallout: New Vegas and Skyrim are identical, so they are defined in `espm::tes4::TES4` and the other namespaces just import from there using `using espm::tes4::TES4::MAST;`.
