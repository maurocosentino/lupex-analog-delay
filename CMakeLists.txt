cmake_minimum_required(VERSION 3.24)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" LUPEX_VERSION LIMIT_COUNT 1)

project(Lupex VERSION ${LUPEX_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(LUPEX_ENABLE_TESTS "Enable Lupex test targets" OFF)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    message(FATAL_ERROR "JUCE submodule is missing. Run: git submodule update --init --recursive")
endif()

add_subdirectory(JUCE)

juce_add_plugin(LupexDelay
    COMPANY_NAME "Fauz Audio"
    BUNDLE_ID "com.fauzaudio.lupex"
    PLUGIN_MANUFACTURER_CODE Faud
    PLUGIN_CODE Lupx
    FORMATS VST3
    PRODUCT_NAME "Lupex Delay"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
    VST3_CATEGORIES Fx Delay Stereo
        VST3_AUTO_MANIFEST FALSE
)

target_sources(LupexDelay
    PRIVATE
        source/dsp/DelayLine.cpp
        source/dsp/BBDFilter.cpp
        source/dsp/TapeEmulator.cpp
        source/dsp/LupexEngine.cpp
        source/dsp/WowFlutter.cpp
        source/dsp/WowFlutter.h
        source/parameters/LupexParameters.cpp
        source/plugin/PluginProcessor.cpp
        source/plugin/PluginEditor.cpp
        source/ui/LupexKnob.cpp
        source/ui/LupexToggle.cpp
        source/ui/PedalLookAndFeel.cpp
        source/ui/BypassButton.cpp
        source/ui/DelayDisplay.cpp
        source/dsp/DelayLine.h
        source/dsp/BBDFilter.h
        source/dsp/TapeEmulator.h
        source/dsp/LupexEngine.h
        source/parameters/LupexParameters.h
        source/parameters/ParameterIDs.h
        source/plugin/PluginProcessor.h
        source/plugin/PluginEditor.h
        source/ui/LupexKnob.h
        source/ui/LupexToggle.h
        source/ui/PedalLookAndFeel.h
        source/ui/BypassButton.h
        source/ui/DelayDisplay.h
)

juce_add_binary_data(LupexAssets
        SOURCES
        assets/images/background.png
        assets/images/knob.png
        assets/images/switch_toggle.png
        assets/images/footswitch_up.png
        assets/images/footswitch_down.png
        assets/images/screenshot.png
)

target_include_directories(LupexDelay
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

target_compile_definitions(LupexDelay
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(LupexDelay
    PRIVATE
        LupexAssets
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

if(LUPEX_ENABLE_TESTS)
    enable_testing()

    add_executable(LupexTests
            tests/DelayLineTest.cpp
            tests/BBDFilterTest.cpp
            tests/ParametersTest.cpp
            source/dsp/DelayLine.cpp
            source/dsp/BBDFilter.cpp
            source/dsp/TapeEmulator.cpp
            source/dsp/WowFlutter.cpp
            source/dsp/LupexEngine.cpp
    )

    target_include_directories(LupexTests
            PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/source"
    )

    target_compile_definitions(LupexTests
            PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_CURL=0
    )

    target_link_libraries(LupexTests
            PRIVATE
            Catch2::Catch2WithMain
            juce::juce_core
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(LupexTests)
endif()
