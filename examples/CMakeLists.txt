add_executable(grammatical_evolution grammatical_evolution.cc)
target_link_libraries(grammatical_evolution ${RAW_LIB_NAME} ${RAW_TO_LINK})

add_executable(evolve_word evolve_word.c)
target_link_libraries(evolve_word ${RAW_LIB_NAME} ${RAW_TO_LINK})
