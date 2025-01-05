################################################################################
# Messages
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(OUT_FILE ON)
if (OUT_FILE)
    set(OUTPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/out.info")
    file(WRITE ${OUTPUT_FILE} "")
    message(STATUS "Ecritures des information dans ${OUTPUT_FILE}")
    message("Test")
endif ()
function(message_info msg)
    if(OUT_FILE)
        # Définit le chemin du fichier de sortie
        # Ajoute le message dans le fichier
        file(APPEND ${OUTPUT_FILE} "${msg}\n")
    else ()
        message(STATUS msg)
    endif ()
endfunction()