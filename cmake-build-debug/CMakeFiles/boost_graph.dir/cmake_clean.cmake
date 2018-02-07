file(REMOVE_RECURSE
  "libboost_graph.pdb"
  "libboost_graph.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/boost_graph.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
