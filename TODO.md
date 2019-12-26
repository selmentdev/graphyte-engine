# TODO list

[ ] option for skipping unit tests when generating projects
[ ] option for skipping content creation tools
[ ] add precompiled headers to unit tests - right now MSVC tends to hung TestVersino.cxx for too long, espc. on ARM64
[ ] check clang-cl toolchain
[ ] unit tests for math sublibrary
[ ] refactor `SplatN` in way which will allow to specify target type too
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
