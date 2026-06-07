cmake_minimum_required(VERSION 3.21)

project(proyecto_gym_vs2022 LANGUAGES CXX)

# ------------------------------------------------------------------
#  Estandar de C++ y opciones de Qt
# ------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Procesado automatico de Qt: moc (Q_OBJECT), rcc (recursos), uic (.ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ------------------------------------------------------------------
#  Localizar Qt 6 (Widgets + Network para el modulo de IA asincrono)
# ------------------------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# ------------------------------------------------------------------
#  Fuentes
#  Se recogen todos los .cpp/.h de la carpeta src/.
# ------------------------------------------------------------------
file(GLOB PROYECTO_FUENTES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# ------------------------------------------------------------------
#  Ejecutable (qt_add_executable habilita el despliegue de Qt6)
# ------------------------------------------------------------------
qt_add_executable(proyecto_gym_vs2022
    ${PROYECTO_FUENTES}
)

target_include_directories(proyecto_gym_vs2022 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(proyecto_gym_vs2022 PRIVATE
    Qt6::Widgets
    Qt6::Network
)

# En Windows: aplicacion GUI (sin consola negra detras).
set_target_properties(proyecto_gym_vs2022 PROPERTIES
    WIN32_EXECUTABLE ON
)

# ------------------------------------------------------------------
#  Copiar los .txt semilla junto al ejecutable tras compilar, de modo
#  que la aplicacion encuentre datos al iniciar (la primera vez).
# ------------------------------------------------------------------
set(DATOS_SEMILLA
    "${CMAKE_CURRENT_SOURCE_DIR}/data/clientes.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/turnos.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/reservas.txt"
)

foreach(ARCHIVO ${DATOS_SEMILLA})
    if(EXISTS "${ARCHIVO}")
        add_custom_command(TARGET proyecto_gym_vs2022 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${ARCHIVO}"
                "$<TARGET_FILE_DIR:proyecto_gym_vs2022>"
        )
    endif()
endforeach()

# ------------------------------------------------------------------
#  Despliegue de DLLs de Qt en Windows (windeployqt) tras compilar.
#  Permite ejecutar el .exe sin configurar el PATH de Qt manualmente.
# ------------------------------------------------------------------
if(WIN32)
    find_program(WINDEPLOYQT_EXE windeployqt HINTS "${Qt6_DIR}/../../../bin")
    if(WINDEPLOYQT_EXE)
        add_custom_command(TARGET proyecto_gym_vs2022 POST_BUILD
            COMMAND "${WINDEPLOYQT_EXE}"
                    --no-translations
                    "$<TARGET_FILE:proyecto_gym_vs2022>"
            COMMENT "Desplegando las DLLs de Qt con windeployqt..."
        )
    endif()
endif()
