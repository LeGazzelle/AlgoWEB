file(REMOVE_RECURSE
  "libboost_regex.pdb"
  "libboost_regex.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/boost_regex.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
