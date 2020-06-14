Get-ChildItem -Path ".\engine", ".\game" -Include "*.cxx", "*.hxx" -Recurse | ForEach-Object {
    Write-Host $_.FullName
    clang-format.exe -i -style=file $_.FullName 
}
