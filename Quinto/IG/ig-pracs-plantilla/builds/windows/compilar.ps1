## Compilar la versión de 'debug'
## Si los archivos de compilación no están creados, los crea antes.


Write-Host -ForegroundColor green 'COMPILAR'
Launch-VsDevShell.ps1 -SkipAutomaticLocation

Push-Location -Path .\cmake

if ((! (Test-Path "CMakeFiles")) -or (!(Test-Path "CMakeCache.txt")))
{
    Write-Host -ForegroundColor green 'Generando archivos de compilación'
    cmake ..
    Write-Host -ForegroundColor green 'Archivos de compilación generados'
    
}
cmake --build .
$exit_code = ${LASTEXITCODE} 
Pop-Location 
Write-Host -ForegroundColor green "Se ha terminado la compilación. Resultado == ${exit_code}"
exit $exit_code