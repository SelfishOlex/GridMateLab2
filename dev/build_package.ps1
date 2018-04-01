function LyReleasePackage () {
    .\lmbr_waf.bat build_win_x64_vs2015_profile -p all
    .\lmbr_waf.bat build_win_x64_vs2015_release -p game_and_engine

    if (Test-Path -Path .\myproject_pc_paks\) {
        Remove-Item .\myproject_pc_paks\ -Recurse -Force
    }

    .\BuildMyProject_Paks_PC.bat
    Copy-Item .\Bin64vc140.Release\ `
        -Destination .\myproject_pc_paks\ -Recurse -Force -Verbose
    .\BuildShaderPak_DX11.bat
    Copy-Item .\Build\pc\MyProject\*.pak `
        -Destination .\myproject_pc_paks\myproject\ `
        -Force -Verbose
}
