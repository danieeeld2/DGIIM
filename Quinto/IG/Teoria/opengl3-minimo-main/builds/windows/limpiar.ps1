# Script para borrar los ejecutables y los archivos OBJ creados al compilar

Launch-VsDevShell.ps1 -SkipAutomaticLocation

Write-Host -ForegroundColor green "LIMPIAR"

Push-Location -Path .\cmake
cmake --build . --target clean
cmake --build . --config release --target clean
Pop-Location 
Remove-Item -Force -Recurse bin/Debug*, bin/Release*
Write-Host -ForegroundColor green 'Se han eliminado todos los archivos producidos al compilar'

