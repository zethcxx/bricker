--: Headers ---------------------------------------------
set_project ("Bricker")
set_version ("0.1.0"  )
set_xmakever("2.8.0"  )

--: Options ---------------------------------------------
option("pinfo")
    set_default(false)
    set_showmenu(true)
option_end()


--: Includes --------------------------------------------
includes("./xmake/rules/*.lua") -- or only rule specify


--: Configs ---------------------------------------------
add_repositories("local-repo ./xmake/")
add_moduledirs("./xmake/modules/")

set_policy("build.c++.modules"    , true)
set_policy("build.c++.modules.std", true)

--: Rules -----------------------------------------------
add_rules("vscode.compile_commands")


--: Deps ------------------------------------------------
add_requires("lbyte.stx v0.2.0", {configs = { use_modules = true }})


--: Targets ---------------------------------------------
target( "main" )
    set_default  (true    )
    set_languages("c++23" )
    set_kind     ("binary")
    set_basename ("exec"  )

    add_files( "app/main.cpp", "./src/**/*.cppm")
    add_packages("lbyte.stx")

    on_config( "actions.configure"   )
    on_run   ( "actions.run_process" )

