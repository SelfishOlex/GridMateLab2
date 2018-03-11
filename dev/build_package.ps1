function LyBuildPackage () {
    Remove-Item .\gridmateplayers_pc_paks\ -Recurse -Force
    .\BuildGridMatePlayers_Paks_PC.bat
    .\lmbr_waf.bat build_win_x64_vs2015_release -p game_and_engine
    Copy-Item .\Bin64vc140.Release\ .\gridmateplayers_pc_paks\ -Recurse -Force -Verbose
    .\BuildShaderPak_DX11.bat
    Copy-Item .\Build\pc\GridMatePlayers\*.pak .\gridmateplayers_pc_paks\gridmateplayers\ -Force -Verbose
}
