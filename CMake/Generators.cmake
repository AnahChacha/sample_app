macro(normalize_paths INPUT_FILE)
    string(REGEX REPLACE "\\.in$" "" output_file_name ${INPUT_FILE})
    get_filename_component(input_file_path ${INPUT_FILE} ABSOLUTE)
    get_filename_component(output_dir ${input_file_path} DIRECTORY)
    set(output_file ${output_dir}/${output_file_name})
endmacro()

macro(generate_vcproj_file INPUT_TEMPLATE_FILE HEADER_FILES SOURCE_FILES)
    message("-- Generating .vcproj file")
    normalize_paths(${INPUT_TEMPLATE_FILE}) # remember to call this
    set(SOURCE_ITEMS "")
    foreach(source_item ${SOURCE_FILES})
        set(SOURCE_ITEMS "${SOURCE_ITEMS}    <ClCompile Include=\"${source_item}\" />\n")
    endforeach()
    foreach (header_item ${HEADER_FILES})
        set(HEADER_ITEMS "${HEADER_ITEMS}    <ClCompile Include=\"${header_item}\" />\n")
    endforeach ()
    configure_file(${input_file_path} ${output_file}) # on-path
    configure_file(${input_file_path} "${PROJECT_NAME}.vcproj") # for build
    message("-- Generating .vcproj file  SUCCESS")
endmacro()

macro(generate_sln_file INPUT_TEMPLATE_FILE THIS_PROJECT_NAME)
    message("-- Generating .sln file")
    normalize_paths(${INPUT_TEMPLATE_FILE}) # remember to call this
    set(THIS_PROJECT_NAME ${THIS_PROJECT_NAME})
    configure_file(${input_file_path} ${output_file}) # on-path
    configure_file(${input_file_path} "${THIS_PROJECT_NAME}.sln") # for build
    message("-- Generating .sln file SUCCESS")
endmacro()