project('soloud', 'cpp', 'c')

inc_dirs = include_directories(
  'include',
)

sources = [
  'src/audiosource/monotone/soloud_monotone.cpp',
  'src/audiosource/sfxr/soloud_sfxr.cpp',
  'src/audiosource/speech/darray.cpp',
  'src/audiosource/speech/klatt.cpp',
  'src/audiosource/speech/resonator.cpp',
  'src/audiosource/speech/tts.cpp',
  'src/audiosource/speech/soloud_speech.cpp',
  'src/audiosource/tedsid/sid.cpp',
  'src/audiosource/tedsid/ted.cpp',
  'src/audiosource/tedsid/soloud_tedsid.cpp',
  'src/audiosource/vic/soloud_vic.cpp',
  'src/audiosource/wav/soloud_wavstream.cpp',
  'src/audiosource/wav/stb_vorbis.c',
  'src/audiosource/wav/soloud_wav.cpp',

  'src/filter/soloud_bassboostfilter.cpp',
  'src/filter/soloud_biquadresonantfilter.cpp',
  'src/filter/soloud_dcremovalfilter.cpp',
  'src/filter/soloud_echofilter.cpp',
  'src/filter/soloud_fftfilter.cpp',
  'src/filter/soloud_flangerfilter.cpp',
  'src/filter/soloud_lofifilter.cpp',

  'src/core/soloud_audiosource.cpp',
  'src/core/soloud_bus.cpp',
  'src/core/soloud_core_3d.cpp',
  'src/core/soloud_core_basicops.cpp',
  'src/core/soloud_core_faderops.cpp',
  'src/core/soloud_core_filterops.cpp',
  'src/core/soloud_core_getters.cpp',
  'src/core/soloud_core_setters.cpp',
  'src/core/soloud_core_voicegroup.cpp',
  'src/core/soloud_core_voiceops.cpp',
  'src/core/soloud.cpp',
  'src/core/soloud_fader.cpp',
  'src/core/soloud_fft.cpp',
  'src/core/soloud_fft_lut.cpp',
  'src/core/soloud_file.cpp',
  'src/core/soloud_filter.cpp',
  'src/core/soloud_thread.cpp',
]

soloud_dependencies = []

add_project_arguments('-DWITH_SDL2_STATIC', language: 'cpp')
sources += [
  'src/backend/sdl2_static/soloud_sdl2_static.cpp',
]
soloud_dependencies += [
  dependency('sdl2'),
]

add_project_arguments('-DWITH_NULL', language: 'cpp')
sources += [
  'src/backend/null/soloud_null.cpp',
]

soloud_lib = library(
  'soloud',
  sources,
  include_directories: inc_dirs,
  dependencies: soloud_dependencies,
)

soloud_dep = declare_dependency(
  link_with: soloud_lib,
  include_directories: inc_dirs,
)
