# TODO list

[ ] option for skipping unit tests when generating projects
[ ] option for skipping content creation tools
[ ] add precompiled headers to unit tests - right now MSVC tends to hung TestVersino.cxx for too long, espc. on ARM64
[ ] check clang-cl toolchain
[ ] unit tests for math sublibrary
[ ] refactor `SplatN` in way which will allow to specify target type too
[ ] `BitCompareEquals` - rethink this API for booleans, because in few cases we need to explicitely compare VectorN by bits! Not just BoolN
[ ] replace few places with `std::bit_cast`
[ ] move few bit-related functions to `notstd::` namespace and replace them when C++20 will ship on supported compilers
[ ] think over removing not supported configurations: we should support just
    [ ] windows-x64
    [ ] windows-arm64
    [ ] linux-x64
    [ ] linux-arm64
    [ ] nx-arm64 (someday)
    [ ] xbox-one-x64
    [ ] xbox-series?-x64
    [ ] ps4-x64
    [ ] ps5-x64
    [ ] android-arm64
