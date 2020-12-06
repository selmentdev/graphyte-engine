dotnet run --project .\generate\Generate.csproj -Profile:.\profiles\main.jsonc -Platform:Windows -Generator:FastBuild -Toolchain:MSVC -OutputPath:".generated\fastbuild"

tools\FastBuild\windows-x64\FBuild.exe -config ".generated\fastbuild/Graphyte-Windows-MSVC.bff"
