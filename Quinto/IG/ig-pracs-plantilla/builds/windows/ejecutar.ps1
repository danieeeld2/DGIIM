## Ejecuta la versión de debug
## Si no existe el ejecutable: da error y sale


Launch-VsDevShell.ps1 -SkipAutomaticLocation

if ( !(Test-Path ./bin/Debug/ejecutable.exe))
{
    Write-Host -ForegroundColor red "Error: el ejecutable no se ha creado. Usa 'Compilar y ejecutar'"
    return
}

Write-Host -ForegroundColor green "EJECUTAR"

chcp 65001  ## --> hace que la salida del .exe se vea correcta (esa salida es UTF-8)
./bin/Debug/ejecutable.exe
Write-Host -ForegroundColor green "Se ha terminado la ejecución del programa"
