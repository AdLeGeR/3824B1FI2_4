create_project_lib(Table)

target_sources(Table PRIVATE
    table_vector.cpp
)

target_sources(Table PRIVATE
    table_AVL.cpp
)

target_sources(Table PRIVATE
    table_hash.cpp
)