@echo off

dotnet run --project .\generate\Generate.csproj --configuration Debug -- --toolchain "MSVC" --generator "FastBuild" --platform "Windows" --profile "./profiles/main2.jsonc" --log "d:/log.txt"
REM -Profile:".\profiles\main2.jsonc" -Platform:"Windows" -Generator:"FastBuild" -Toolchain:"MSVC" -OutputPath:".generated\fastbuild" -NoLogo
REM dotnet run --project .\generate\Generate.csproj --configuration Release -Profile:.\profiles\main2.jsonc -Platform:Windows -Generator:FastBuild -Toolchain:MSVC -OutputPath:".generated\fastbuild"

REM tools\FastBuild\windows-x64\FBuild.exe -config ".generated\fastbuild/Graphyte-Windows-MSVC.bff" Target-MSVC-X64-Windows-GxBase-Debug
