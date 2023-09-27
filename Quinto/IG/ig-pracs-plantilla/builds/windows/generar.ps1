

Write-Host -ForegroundColor green 'GENERAR archivos de compilación'
Launch-VsDevShell.ps1 -SkipAutomaticLocation

Push-Location .\bin
Remove-Item Debug*, Release*  -Force -Recurse 
Pop-Location

Push-Location .\cmake
Remove-Item * -Force -Recurse -Exclude ".gitignore"
cmake ..
Pop-Location 
Write-Host -ForegroundColor green 'Se han generado los archivos de compilación'

